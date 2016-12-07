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
#include "../mfccDtw/WaveFunction.h"

extern "C" {
//#include <interf_dec.h>
#include "opencore-amr/amrnb/interf_dec.h"
}

using namespace std;

#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))
//#define ABS(a) ((a)>0?(a):(-(a)))
static const int32_t sequenceLength = 155000;	// 截取的非0语音序列最大长度
static const int32_t BIGDIST = 1000000;
static const int window = 1;					// 因为app 每1分钟发送一个监控语音内容，默认取2分钟的监控结果作为情感判断依据；

int32_t A_B_S(int32_t a, int32_t b)
{
	return a > b ? (a - b) : (b - a);
}

/* From WmfDecBytesPerFrame in dec_input_format_tab.cpp */
const int sizes[] = { 12, 13, 15, 17, 19, 20, 26, 31, 5, 6, 5, 5, 0, 0, 0, 0 };


Similarity::Similarity()
{
}
Similarity::~Similarity()
{
}

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
	vector<string> fileSilent;
	string dirSilent = dirs + "/silent";
	spaceGary::allFiles(dirSilent, fileSilent);

	wavStruct ws;

    WaveFunction* a=new WaveFunction(128,13);//每帧多少个采样点，MFCC参数的维数
	vector<vector<float> > mfccs;
	for(int i = 0; i < fileSmile.size(); i++)
	{
		string file = "data/smile/" + fileSmile[i];
		_INFO("file in dir<smile> : %s", file.c_str());

		_INFO("BEGIN TO PROCESS FILE");
		mfccs.clear();
    	mfccs = a->getMFCCs(file);
		dataFloatSmile.push_back(mfccs);
	}

	for(int i = 0; i < fileCry.size(); i++)
	{
		string file = "data/cry/" + fileCry[i];
		_INFO("file in dir<cry> : %s", file.c_str());
		
		_INFO("BEGIN TO PROCESS FILE");
		
		mfccs.clear();
    	mfccs = a->getMFCCs(file);
		dataFloatCry.push_back(mfccs);
	}

	// Silent Loading
	for(int i = 0; i < fileSilent.size(); i++)
	{
		string file = "data/silent/" + fileSilent[i];
		_INFO("file in dir<silent> : %s", file.c_str());
		
		_INFO("BEGIN TO PROCESS FILE");
		mfccs.clear();
    	mfccs = a->getMFCCs(file);
		dataFloatSilent.push_back(mfccs);
	}
	
	_INFO("SIZE OF dataFloatSmile : %d", dataFloatSmile.size());
	_INFO("SIZE OF dataFloatCry : %d", dataFloatCry.size());
	_INFO("SIZE OF dataFloatSilent : %d", dataFloatSilent.size());
	return 0;
}

int Similarity::readint16toWav(string path, string& line) {
	string outfilename = path + ".wav";
	WavWriter wav(outfilename.c_str(), 8000, 16, 1);

	/* Convert to little endian and write to wav */
	vector<string> vec;
	spaceGary::StringSplit(line, vec, "##_##");
	if(vec.size() == 0)
		return -1;
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

int Similarity::CalSimilarity(string& file1, string& emotion)
{
	vector<vector<float> > float1;
	
	_INFO("BEGIN TO PROCESS FILE1");
	_INFO("BEGIN TO PROCESS SIMILARITY.");

    WaveFunction* a=new WaveFunction(128,13);//每帧多少个采样点，MFCC参数的维数
	vector<vector<float> > mfccs;
   	mfccs = a->getMFCCs(file1);

	_INFO("Processing float1 ...");
	// smile
	double distSmile = BIGDIST;
	for(int i = 0; i < MIN(5,dataFloatSmile.size()); i++) 
	{
		float d = a->ComputeDTW(mfccs, dataFloatSmile[i]);
		//d *= 1000.0;
		d *= (double)(A_B_S(mfccs.size() , dataFloatSmile[i].size()) + 1);
		_INFO("d of Smile = %d", d);//A_B_S(mfccs.size(), dataFloatSmile[i].size()));
		//d /=(double)(A_B_S(mfccs.size(), dataFloatSmile[i].size()) + 1);
		d /= (double)(mfccs.size() + dataFloatCry[i].size());
		if(d < distSmile)
			distSmile = d;
		_INFO("distSmile = %f, abs = %d", distSmile, A_B_S(mfccs.size(), dataFloatSmile[i].size()) + 1);
	}
	_INFO("distSmile = %f", distSmile);
	// cry
	double distCry = BIGDIST;
	_INFO("size of input mfccs : %d", mfccs.size());
	for(int i = 0; i < MIN(5,dataFloatCry.size()); i++) 
	{
		_INFO("size of dababase mfccs : %d", dataFloatCry[i].size());
		float d = a->ComputeDTW(mfccs, dataFloatCry[i]);
		_INFO("d of Cry = %d", d);//A_B_S(mfccs.size(), dataFloatCry[i].size()));
		d *= (double)(A_B_S(mfccs.size() , dataFloatCry[i].size()) + 1);
		d /= (double)(mfccs.size() + dataFloatCry[i].size());
		cerr << d << " / " << (A_B_S(mfccs.size() , dataFloatCry[i].size()) + 1) << " = " << d << endl;
		if(d < distCry)
			distCry = d;
		_INFO("distCry = %f, abs = %d", distCry, A_B_S(mfccs.size() , dataFloatCry[i].size()) + 1);

	}
	_INFO("distCry = %f", distCry);

	// silent
	double distSilent = BIGDIST;
	for(int i = 0; i < MIN(5,dataFloatSilent.size()); i++) 
	{
		float d = a->ComputeDTW(mfccs, dataFloatSilent[i]);
		d *= (double)(A_B_S(mfccs.size() , dataFloatSilent[i].size()) + 1);
		//d *= 1000.0;
		_INFO("d of Silent = %d", d);//A_B_S(mfccs.size() , dataFloatSilent[i].size()));
		//d /=(double)(A_B_S(mfccs.size() , dataFloatSilent[i].size())+1);
		//d /= (double)(mfccs.size() + dataFloatSilent[i].size());
		if(d < distSilent)
			distSilent = d;
		distSilent *= 2.5;
		_INFO("distSilent = %f ", distSilent);
		//_INFO("distSilent = %f, abs = %d", distSilent, A_B_S(mfccs.size() , dataFloatSilent[i].size())+1);
	}
	_INFO("distSilent = %f", distSilent);

	_INFO("Dist from  SMILE = %f" , distSmile);
	_INFO("Dist from  CRY = %f" , distCry);
	_INFO("Dist from  SILENT = %f" , distSilent);

	if(distCry > distSmile)
		emotion = "smile";
	else if(distSmile > distCry)
		emotion = "cry";

	if(distSmile >= distSilent && distCry >= distSilent )
		emotion = "silent";

	_INFO("emotionQueue.size : %d", emotionQueue.size());
	_INFO("Cry = %d", cry);
	_INFO("Smile = %d", smile);
	_INFO("Silent = %d", silent);
	
	// 情感队列
//	if(emotionQueue.empty() || emotionQueue.size() < window)	// 若监控内容不足window 个，则直接返回silent;
//	{
//		emotionQueue.push(emotion);
//		if(emotion == "cry")
//			cry++;
//		else if(emotion == "smile")
//			smile ++;
//		else if(emotion == "silent")
//			silent ++;
//
//		emotion = "silent";
//		return 0;
//	}else
//	{
//		string front = emotionQueue.front();
//		if(front == "cry")
//			cry --;
//		else if(front == "smile")
//			smile --;
//		else if(front == "silent")
//			silent --;
//		emotionQueue.pop();
//		
//		if(emotion == "cry")
//			cry ++;
//		else if(emotion == "smile")
//			smile ++;
//		else if(emotion == "silent")
//			silent ++;
//		
//		emotionQueue.push(emotion);
//	}

//	if((double)cry/(double)window >= 0.4)
//		emotion = "cry";
//	else if((double)smile/(double)window >= 0.4)
//		emotion = "smile";
//	else if((double)silent/(double)window >= 0.4)
//		emotion = "silent";
	return 0;
}


