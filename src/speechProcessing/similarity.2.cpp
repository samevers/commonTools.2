#include "readWav.h"
#include "../include/service_log.hpp"
#include "../Similarity/editDist/EditDist.h"

int main(int argc, char** argv)
{
	if(argc != 3)
	{
		_ERROR("Please input 2 files.");
		return -1;
	}
	string file1 = argv[1];
	string file2 = argv[2];
	vector<double> float1;
	vector<double> float2;

	vector<string> data1;
	vector<string> data2;
	//unsigned char* data1;
	//unsigned char* data2;
	
	unsigned long size1;
	unsigned long size2;
	
	wavStruct ws;
	_INFO("BEGIN TO PROCESS FILE1");
	if(ws.readWav(file1, data1, float1, size1) == -1)
	{
		_ERROR("Fail to read file1: %s", file1.c_str());
		return -1;
	}
	_INFO("BEGIN TO PROCESS FILE2");
	if(ws.readWav(file2, data2, float2, size2) == -1)
	{
		_ERROR("Fail to read file2: %s", file2.c_str());
		return -1;
	}
	
	// similarity
	_INFO("BEGIN TO PROCESS SIMILARITY.");
	cout << data1.size()<< endl;
	cout << data2.size()<< endl;

//	EditDist ed;
//	_INFO("SIZE OF DATA1: %lld", data1.size());
//	_INFO("SIZE OF DATA2: %lld", data2.size());
//	int dis = ed.edit(data1,data2);
//	_INFO("Distance of 1 and 2 = %lld", dis);

	// vector distance
	cout << float1.size()<< endl;
	cout << float2.size()<< endl;
	_INFO("SIZE OF FLOAT1 : lld%", float1.size());
	_INFO("SIZE OF FLOAT2 : lld%", float2.size());
	if (float1.size() != float2.size())
	{
		_ERROR("float1 != float2, Please check.");
		return -1;
	}
	double dist = 0;
	for(unsigned long i = 0; i < float1.size(); i ++)
	{
		dist += float1[i]>float2[i]?(float1[i] - float2[i]):(float2[i]-float1[i]);
	}
	dist = dist/(double)float1.size();
	_INFO("AVG dist = %f", dist);

	return 0;
}

