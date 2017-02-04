#include "commonTalk.h"
#include "../include/service_log.hpp"
#include "../segment/Segment.h"
int main(int argc, char** argv)
{
	if(argc < 2)
	{
		_ERROR("Please input a Query.");
		return -1;
	}
	string query = argv[1];
	_INFO("Query : %s", query.c_str());

	commonTalk ct;
	ct.Init("../../../data/base/querymatch");
	long long request_id = 1;
	SEGMENT_1* wordSeg;
	wordSeg = SEGMENT_1::getInstance();
	wordSeg->Init();
	map<string, ClassInfo> classmap;
	_INFO("Let's make a response ...");
	ct.commonTalkResponse(query,request_id, wordSeg,classmap);
	_INFO("Response is made ...");
	map<string, ClassInfo>::iterator iter;
	_INFO("------------------------ OUT COMES. -------------------------------------");
	for(iter = classmap.begin(); iter != classmap.end(); iter++)
	{
		if(iter->second.score > 0)
			_INFO("TALK CLASS:%s" , iter->first.c_str());
	}
	return 0;
}
