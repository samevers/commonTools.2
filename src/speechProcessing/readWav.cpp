#include "readWav.h"
#include <sstream>
//要在int main()的前面加上函数的声明，因为你的函数写在main函数的后面
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
 
	fs.seekg(0, ios::end);		//用c++常用方法获得文件大小
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

	//for (unsigned long i =0; i<WAV.data_size; i = i + 2)
	unsigned long dataSize = WAV.data_size;
	unsigned long end = dataSize - 1;
	bool leftzero = 1;
	bool rightzero = 1;
	for (unsigned long i = 0; i<dataSize; i = i++)
	{
		if(WAV.data[i] != 0)
		{
			leftzero = 0;
		}
	
		if(WAV.data[end] != 0)
			rightzero = 0;
		if(rightzero == 1)
			dataSize --;
		if(end >= i)
			end --;

		if(leftzero == 1 )
			continue;


		if(WAV.data[i] != '0')
		{
			string d = char2string(WAV.data[i]);
			data.push_back(d);
		}
		//右边为大端
		unsigned long data_low = WAV.data[i];
		unsigned long data_high = WAV.data[i + 1];
		double data_true = data_high * 256 + data_low;
		long data_complement = 0;	   
		//取大端的最高位（符号位）
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
