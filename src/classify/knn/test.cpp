#include "knn.h"

using namespace std;

int main(int argc, char** argv)
{
	if(argc != 3)
	{
		_ERROR("Parameters is not correct.\nPlease Input two files.");
		return -1;
	}
	string predictFile = argv[1];
	string QueueFile = argv[2];
	
	KNN_ knn;
	knn.Run_(predictFile, QueueFile);

	return 0;
}
