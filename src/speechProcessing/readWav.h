#ifndef READ_WAV_HEAD_H__
#define READ_WAV_HEAD_H__

#include <iostream>
#include <fstream>
#include <string.h>
#include<math.h>
#include<cmath>
#include<stdlib.h>
#include <bitset>
#include <iomanip>
#include <vector>
using namespace std;

//struct wav_struct
//{
//	unsigned long file_size;		//文件大小
//	unsigned short channel;			//通道数
//	unsigned long frequency;		//采样频率
//	unsigned long Bps;				//Byte率
//	unsigned short sample_num_bit;	//一个样本的位数
//	unsigned long data_size;		//数据大小
//	unsigned char *data;			//音频数据 ,这里要定义什么就看样本位数了，我这里只是单纯的复制数据
//};
class wavStruct
{
	public:
		wavStruct();
		~wavStruct();
	public:
		unsigned long file_size;		//文件大小
		unsigned short channel;			//通道数
		unsigned long frequency;		//采样频率
		unsigned long Bps;				//Byte率
		unsigned short sample_num_bit;	//一个样本的位数
		unsigned long data_size;		//数据大小
		unsigned char *data;			//音频数据 ,这里要定义什么就看样本位数了，我这里只是单纯的复制数据
	public:
		int readWav(string& filename, vector<string>& data, vector<double>& float_data,unsigned long size);
		int postProcessingFloatSequence(vector<double>& float1, int32_t& begin, int32_t& end, int32_t& size);
};
 
//int readWav(string& filename, unsigned char* data, vector<double>& float_data,unsigned long size);


#endif
