#include "readWav.h"
#include "../include/service_log.hpp"
#include "../Similarity/editDist/EditDist.h"
#include "headDTW.h"
#include <algorithm>
#include <sstream>
#include "decodeAmr.h"
#include "similarity.h"
#include "../include/gary_common/gary_common.h"
#include <sys/time.h>
extern "C" {
//#include <interf_dec.h>
#include "opencore-amr/amrnb/interf_dec.h"
}

using namespace std;

#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))
#define ABS(a) ((a)>0?(a):(-(a)))

static const int window = 6;// 因为app 每10s发送一个监控内容，默认取一分钟的监控结果作为情感判断依据；


/* From WmfDecBytesPerFrame in dec_input_format_tab.cpp */
const int sizes[] = { 12, 13, 15, 17, 19, 20, 26, 31, 5, 6, 5, 5, 0, 0, 0, 0 };


Similarity::Similarity()
{
}
Similarity::~Similarity()
{
}
//
//
int Similarity::loadData(string& dirs)
{
	cry = 0;
	smile = 0;
	silent = 0;
	// Load speech data base.
	vector<string> fileSmile;
	string dirSmile = dirs + "/smile";
	spaceGary::allFiles(dirSmile, fileSmile);
	vector<string> fileCry;
	string dirCry = dirs + "/cry";
	spaceGary::allFiles(dirCry, fileCry);

	wavStruct ws;
	vector<double> floatOut_new;
	for(int i = 0; i < fileSmile.size(); i++)
	{
		string file = "data/smile/" + fileSmile[i];
		_INFO("file in dir<smile> : %s", file.c_str());
		vector<double> floatOut;
		vector<string> data;
		int32_t size;
		
		_INFO("BEGIN TO PROCESS FILE");
		if(ws.readWav(file, data, floatOut, size) == -1)
		{
			_ERROR("Fail to read file: %s", file.c_str());
			return -1;
		}
		int32_t begin;
		int32_t end;
		if(ws.postProcessingFloatSequence(floatOut, begin, end, size, floatOut_new) == -1)
			return -1;
		if((double)floatOut_new.size()/(double)floatOut.size() < 0.2)// 静音,忽略
			continue;
		dataFloatSmile.push_back(floatOut_new);
	}
	for(int i = 0; i < fileCry.size(); i++)
	{
		string file = "data/cry/" + fileCry[i];
		_INFO("file in dir<smile> : %s", file.c_str());
		vector<double> floatOut;
		vector<string> data;
		int32_t size;
		
		_INFO("BEGIN TO PROCESS FILE");
		if(ws.readWav(file, data, floatOut, size) == -1)
		{
			_ERROR("Fail to read file: %s", file.c_str());
			return -1;
		}
		int32_t begin;
		int32_t end;
		if(ws.postProcessingFloatSequence(floatOut, begin, end, size, floatOut_new) == -1)
			return -1;
		if((double)floatOut_new.size()/(double)floatOut.size() < 0.2)// 静音，忽略
			continue;
		dataFloatCry.push_back(floatOut_new);
	}

	return 0;
}
int Similarity::amr2wavOp(string& filename)
{
	DecodeAmr *decodeAmr = new DecodeAmr();
	if(decodeAmr->amr2wav(filename) == -1)
	{
		_ERROR("Fail to convert amr 2 wav format.");
		return -1;
	}
	return 0;
}

int Similarity::readAmr2int16(string& filename, string& speechLine) {

	FILE* in = fopen(filename.c_str(), "rb");
	if (!in) {
		_ERROR("Fail to open file < %s >" ,filename.c_str());
		return -1;
	}
	char header[6];
	int n = fread(header, 1, 6, in);
	if (n != 6 || memcmp(header, "#!AMR\n", 6)) {
		_ERROR("Bad header, amr2wav FAILS.");
		return 1;
	}
	//cout << "header : " << header << endl;

	
	void* amr = Decoder_Interface_init();
	string content = "";
	stringstream os;
	os.str("");
	while (true) {
		uint8_t buffer[500];
		/* Read the mode byte */
		n = fread(buffer, 1, 1, in);
		if (n <= 0)
			break;
		//cout << "buffer : " << buffer << endl;
		/* Find the packet size */
		int size = sizes[(buffer[0] >> 3) & 0x0f];
		if (size <= 0)
			break;
		n = fread(buffer + 1, 1, size, in);
		//cout << "buffer + 1 : " << buffer + 1 << endl;

		if (n != size)
			break;

		/* Decode the packet */
		int16_t outbuffer[160];
		Decoder_Interface_Decode(amr, buffer, outbuffer, 0);
		//cout << "outbuffer: " << endl;
		for (int i = 0; i < 160; i++) 
		{
			os << outbuffer[i] << "\t";
			//cout << outbuffer[i];
		}
		os << "##_##";
	}
	speechLine = os.str();
	cout << speechLine << endl; 
	fclose(in);
	Decoder_Interface_exit(amr);
	return 0;
}

int Similarity::readint16toWav(string path, string& line) {
	string outfilename = path + ".wav";
	WavWriter wav(outfilename.c_str(), 8000, 16, 1);

	/* Convert to little endian and write to wav */
	vector<string> vec;
	spaceGary::StringSplit(line, vec, "##_##");
	for (int i = 0; i < vec.size() - 1; i++)
	{
		vector<string> vv;
		spaceGary::StringSplit(vec[i], vv, "\t");
		uint8_t littleendian[320];
		uint8_t* ptr = littleendian;
		if(vv.size() != 160)
		{
			cerr << "ERROR. vv size != 160" << endl;
			return -1;
		}
		for (int j = 0; j < 160; j++) {
			stringstream os;
			os.str("");
			os << vv[j];
			int16_t v;
			os >> v;
			*ptr++ = (v >> 0) & 0xff;
			*ptr++ = (v >> 8) & 0xff;
		}
		wav.writeData(littleendian, 320);
	}
	return 0;
}

//int Similarity::JudgeEmotion(string& sequence, string& emotion)
//{
//	ofstream outputfile;
//	outputfile.open("sequencefile.txt",ios::out);
//	outputfile << sequence;
//	outputfile.close();
//
//	vector<string> vec;
//	//spaceGary::StringSplit(sequence, vec, " ");
//}

int Similarity::CalSimilarity(string& file1, string& emotion)
{
	vector<double> float1;
	vector<string> data1;
	unsigned long size1;
	
	wavStruct ws;
	_INFO("BEGIN TO PROCESS FILE1");
	if(ws.readWav(file1, data1, float1, size1) == -1)
	{
		_ERROR("Fail to read file1: %s", file1.c_str());
		return -1;
	}
	_INFO("BEGIN TO PROCESS SIMILARITY.");
	
	// Silent
	int32_t zeroWav = 0;
	for(int32_t i = 0; i < float1.size(); i++)
	{
		if(float1[i] == 0)
			zeroWav ++;
	}
	if((double)zeroWav/(double)float1.size() > 0.8)
	{
		emotion = "silent";
		return 0;
	}
//	EditDist ed;
//	_INFO("SIZE OF DATA1: %lld", data1.size());
//	_INFO("SIZE OF DATA2: %lld", data2.size());
//	int dis = ed.edit(data1,data2);
//	_INFO("Distance of 1 and 2 = %lld", dis);

	// vector distance
	//cout << float1.size()<< endl;
//	_INFO("SIZE OF FLOAT1 : lld%", float1.size());
//	double dist = 0;
//	for(unsigned long i = 0; i < float1.size(); i ++)
//	{
//		dist += float1[i]>float2[i]?(float1[i] - float2[i]):(float2[i]-float1[i]);
//	}
//	dist = dist/(double)float1.size();
	int32_t begin1, end1;
	int32_t size_1;
	_INFO("Processing float1 ...");
	vector<double> float1_new;
	if(ws.postProcessingFloatSequence(float1, begin1, end1, size_1, float1_new) == -1)
		return -1;
	// test
//	for(int i = begin1; i < end1; i++)
//	{
//		cout << "---" << float1[i] << endl;
//	}
//	cout << "====================" << endl;
//	for(int i = begin2; i < end2; i++)
//	{
//		cout << "---" << float2[i] <<endl;
//	}
//

//	for(int i = begin1; i < MIN(begin1+1000,end1); i++)
//	{
//		cout << "---" << float1[i] << endl;
//	}
//	cout << "====================" << endl;
//	for(int i = begin2; i < MIN(begin2 + 1000,end2); i++)
//	{
//		cout << "---" << float2[i] <<endl;
//	}
//	return 0;
	// DTW
	DTW_ dtw;
	_INFO("Make DTWDistanceFun ...");
	int32_t step = 100;
	double distSmile = 0.0;
	for(int i = 0; i < dataFloatSmile.size(); i++)
	{
		_INFO("SMILE : Size of database float vector : %d, and Size of input voice float vector : %d", dataFloatSmile[i].size(), float1_new.size());
		double d = dtw.DTWDistanceFun(dataFloatSmile[i], float1_new,step/30);
		distSmile += d;
	}
	distSmile /= (double)dataFloatSmile.size();

	double distCry = 0.0;
	for(int i = 0; i < dataFloatCry.size(); i++)
	{
		_INFO("CRY : Size of database float vector : %d, and Size of input voice float vector : %d", dataFloatSmile[i].size(), float1_new.size());
		double d = dtw.DTWDistanceFun(dataFloatCry[i], float1_new,step/30);
		distCry += d;
	}
	distCry /= (double)dataFloatCry.size();

	_INFO("Dist from  SMILE = %f" , distSmile);
	_INFO("Dist from  CRY = %f" , distCry);

	emotion = "silent";	// 默认为 silent
	if(distCry > distSmile)
		emotion = "smile";
	else if(distSmile > distCry)
		emotion = "cry";

	_INFO("emotionQueue.size : %d", emotionQueue.size());
	_INFO("Cry= %d", cry);
	_INFO("Smile = %d", smile);
	_INFO("Silent = %d", silent);
	
	// 情感队列
	if(emotionQueue.empty() || emotionQueue.size() < window)	// 若监控内容不足window 个，则直接返回silent;
	{
		emotionQueue.push(emotion);
		if(emotion == "cry")
			cry++;
		else if(emotion == "smile")
			smile ++;
		else if(emotion == "silent")
			silent ++;

		emotion = "silent";
		return 0;
	}else
	{
		string front = emotionQueue.front();
		if(front == "cry")
			cry --;
		else if(front == "smile")
			smile --;
		else if(front == "silent")
			silent --;
		emotionQueue.pop();
		
		if(emotion == "cry")
			cry ++;
		else if(emotion == "smile")
			smile ++;
		else if(emotion == "silent")
			silent ++;
		
		emotionQueue.push(emotion);
	}

	if((double)cry/(double)window >= 0.4)
		emotion = "cry";
	else if((double)smile/(double)window >= 0.4)
		emotion = "smile";
	else if((double)silent/(double)window >= 0.4)
		emotion = "silent";
	//int32_t step1 = size_1/step;
	//int32_t step2 = size_2/step;
	//int32_t b1,e1,b2,e2;
	//for(int32_t i = 0; i < step; i ++)
	//{
	//	b1 = begin1 + step1*i;
	//	//e1 = begin1 + step1*(i+1);
	//	e1 = begin1 + 10000;
	//	b2 = begin2 + step2*i;
	//	//e2 = begin2 + step2*(i+2);
	//	e2 = begin2 + 10000;
	//	if(e1 > end1 || e2 > end2)
	//	{
	//		break;
	//	}
	//	double d = dtw.DTWDistanceFun(float1,b1, e1, float2, b2, e2, step/30);
	//	dist += d;
	//	break;

	//}
	
//	int32_t b1 = begin1;
//	int32_t e1 = end1;//MIN(end1, begin1+ 10000);
//	int32_t b2 = begin2;
//	int32_t e2 = end2;//MIN(end2, begin2+ 10000);
//
//	double d = dtw.DTWDistanceFun(float1,b1,e1, float2, b2, e2, 30);
	//_INFO("AVG dist = %f", dist*1000);

	return 0;
}

//int main(int argc, char** argv)
//{
//	if(argc != 2)
//	{
//		_ERROR("Please input 2 files.");
//		return -1;
//	}
//
//	string file1 = argv[1];
//
//	Similarity sim;
//	string dataPath = "./data";
//	_INFO("Begin to load voice database...");
//	sim.loadData(dataPath);
//	_INFO("Over loading voice database...");
//	_INFO("...");
//	_INFO("...");
//	_INFO("...");
//	if(sim.amr2wavOp(file1) == -1)
//	{
//		return -1;
//	}
//	string fileAmr1 = file1 + ".wav";
//	string emotion;
//	if(sim.CalSimilarity(fileAmr1, emotion) == -1)
//	{
//		return -1;
//	}
//	_INFO("Emotion : %s" , emotion);
//
//
//	return 0;
//}





