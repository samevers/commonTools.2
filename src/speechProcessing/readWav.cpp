#include "readWav.h"
#include <sstream>
#include "../include/service_log.hpp"

#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))
#define ABS(a) ((a)>0?(a):(-(a)))

//Ҫ��int main()��ǰ����Ϻ�������������Ϊ��ĺ���д��main�����ĺ���
int hex_char_value(char ss);
int hex_to_decimal(const char* s);
//string hex_to_binary(char* szHex);

string char2string(unsigned char input)
{
	stringstream os;
	os << input;
	string output;
	os >> output;
	return output;
}
wavStruct::wavStruct()
{
}
wavStruct::~wavStruct()
{
}

//int readWav(string& filename, unsigned char* data, vector<double>& float_data_vec, unsigned long size)
int wavStruct::readWav(string& filename, vector<string>& data, vector<double>& float_data_vec, unsigned long size)
{
	fstream fs;
	wavStruct WAV;
	fs.open(filename.c_str(), ios::binary | ios::in);
	
	if(!fs)
	{
		_ERROR("Fail to open file %s", filename.c_str());
		return -1;
	}
	fs.seekg(0, ios::end);		//��c++���÷�������ļ���С
	WAV.file_size = fs.tellg();
 
	fs.seekg(0x14);
	fs.read((char*)&WAV.channel, sizeof(WAV.channel));
 
	fs.seekg(0x18);
	fs.read((char*)&WAV.frequency, sizeof(WAV.frequency));
 
	fs.seekg(0x1c);
	fs.read((char*)&WAV.Bps, sizeof(WAV.Bps));
 
	fs.seekg(0x22);
	fs.read((char*)&WAV.sample_num_bit, sizeof(WAV.sample_num_bit));
 
	fs.seekg(0x28);
	fs.read((char*)&WAV.data_size, sizeof(WAV.data_size));
 
	WAV.data = new unsigned char[WAV.data_size];
	fs.seekg(0x2c);
	fs.read((char *)WAV.data, sizeof(char)*WAV.data_size);

	_INFO("Over making read OPs...");
	unsigned long dataSize = WAV.data_size;
	for (unsigned long i = 0; i<dataSize; i = i++)
	{
		string d = char2string(WAV.data[i]);
		data.push_back(d);
		//�ұ�Ϊ���
		unsigned long data_low = WAV.data[i];
		unsigned long data_high = WAV.data[i + 1];
		double data_true = data_high * 256 + data_low;
		long data_complement = 0;	   
		//ȡ��˵����λ������λ��
		int my_sign = (int)(data_high / 128);
		if (my_sign == 1)
		{
			data_complement = data_true - 65536;
		}
		else
		{
			data_complement = data_true;
		}
		setprecision(4);
		double float_data = (double)(data_complement/(double)32768);	
		float_data_vec.push_back(float_data);
	}
	fs.close();
 
	delete[] WAV.data;
	//system("pause");
 
}

int wavStruct::postProcessingFloatSequence(vector<double>& float1, int32_t& begin, int32_t& end, int32_t& size, vector<double>& float_new)
{
	// Delete '0' in the beginning and the end.
	if(float1.size() == 0)
	{
		_ERROR("Size of speech sequence is illegal. Please check!");
		return -1;
	}
	begin = 0;
	end = float1.size();
	while(end > begin)
	{
		if(float1[begin] == 0)
			begin ++;
		if(float1[end] == 0)
			end --;
		if(float1[begin] != 0 && float1[end] != 0)
			break;
	}
	
//	while(end > begin)
//	{
//		if(float1[end] == 0)
//			end --;
//		else
//			break;
//	}
	if(end == begin)
	{
		_ERROR("The wav file has no voice in.");
		return -1;
	}
	size = end + 1 - begin;
	//cout << "size = " << size << endl;
	//for(int32_t i = begin ; i <= end; i++)
	//{
	//	cout << float1[i] << " ";
	//}
	//cout << endl;
	float_new.clear();
	int32_t i = begin;
	while(i <= end)
	{
		float_new.push_back(float1[i++]);
	}

	return 0;
}
int hex_char_value(char c)
{
	if (c >= '0' && c <= '9')
		return c - '0';
	else if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	else if (c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
	//assert(0);
	return 0;
}
int hex_to_decimal(char* szHex)
{
	int len = 2;
	int result = 0;
	for (int i = 0; i < len; i++)
	{
		result += (int)pow((float)16, (int)len - i - 1) * hex_char_value(szHex[i]);
	}
	return result;
}
/*
string hex_to_binary(char* szHex)
{
	int len = 2;
	string result;
	for (int i = 0; i < len;i++)
}
*/
