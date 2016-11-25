#include "readWav.h"
#include "../include/service_log.hpp"
#include "../Similarity/editDist/EditDist.h"
#include "headDTW.h"
#include <algorithm>
using namespace std;


int main(int argc, char** argv)
{
	if(argc != 2)
	{
		_ERROR("Please input 2 files.");
		return -1;
	}
	string file1 = argv[1];
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

	// Delete '0' in the beginning and the end.
	int32_t begin = 0;
	int32_t end = float1.size();
	while(end > begin)
	{
		if(float1[begin] == 0)
			begin ++;
		else
			break;
	}
	while(end > begin)
	{
		if(float1[end] == 0)
			end --;
		else
			break;
	}
	int32_t size = end + 1 - begin;
	cout << "size = " << size << endl;
	for(int32_t i = begin ; i <= end; i++)
	{
		cout << float1[i] << " ";
	}
	cout << endl;
	return 0;
}

