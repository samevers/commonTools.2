#include "readWav.h"
#include "../include/service_log.hpp"
#include "../Similarity/editDist/EditDist.h"
#include "headDTW.h"
#include <algorithm>
#include <sstream>
#include "decodeAmr.h"
#include "similarity.h"
#include "../include/gary_common/gary_common.h"

using namespace std;

#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))
#define ABS(a) ((a)>0?(a):(-(a)))

int main(int argc, char** argv)
{
	if(argc != 2)
	{
		_ERROR("Please input 2 files.");
		return -1;
	}

	string file1 = argv[1];

	Similarity sim;
	string dataPath = "./data";
	_INFO("Begin to load voice database...");
	sim.loadData(dataPath);
	_INFO("Over loading voice database...");
	_INFO("...");
	_INFO("...");
	_INFO("...");
	if(sim.amr2wavOp(file1) == -1)
	{
		return -1;
	}
	string fileAmr1 = file1 + ".wav";
	string emotion;
	if(sim.CalSimilarity(fileAmr1, emotion) == -1)
	{
		return -1;
	}
	_INFO("Emotion : %s" , emotion);


	return 0;
}





