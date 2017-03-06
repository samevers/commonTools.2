#include "sug.h"
#include "../include/service_log.hpp"

using namespace std;

int main(int argc, char** argv)
{
	SUGGUESTION sug;
	_INFO("Start to Init sug.");
	sug.Init();
	_INFO("Init sug OK.");

	string query = argv[1];
	vector<string> vec;
	sug.getSugguestion(query.c_str(), vec);
	if(vec.size() > 0)
	{
		int num = 0;
		for (int i = 0; i < vec.size(); i++)
		{
			_INFO("%d SUG: %s", num++, vec[i].c_str());
		}
	}
	return 0;
}
