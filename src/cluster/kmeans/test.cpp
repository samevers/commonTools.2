#include "kmeans.h"
#include "service_log.hpp"

int main(int argc, char** argv)
{
	if(argc != 3)
	{
		_ERROR("Parameters is wrong. Please Check.");
		_ERROR("NOTE : Two Parameters must be offered!");
		return -1;
	}
	string filename = argv[1];
	string clusterNum = argv[2];
	int n_cluster = spaceGary::toInt(clusterNum);
	cerr << "Read File : "<< filename << endl;
	cerr << "n_cluster : "<< n_cluster<< endl;
	KMEANS_ km(n_cluster);
	km.Run_(filename);

	return 0;
}
