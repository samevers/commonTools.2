#ifndef COMMONTALK_H__
#define COMMONTALK_H__

#include "../include/general.h"
#include "../include/gary_common/gary_common.h"
#include "../segment/Segment.h"
#include "../QueryMatch/QueryMatch.h"
#include "worker.hpp"

class commonTalk{
	public:
		QueryMatch* querymatch;
		std::vector<std::string> vClassName;
	public:
		static commonTalk * getInstance();
		bool Init(std::string path);
		int commonTalkResponse(std::string query,long long request_id, SEGMENT_1* wordSeg,std::map<std::string, ClassInfo>& classmap);

	public:
		commonTalk();
		~commonTalk();
	private:
		
};
#endif

