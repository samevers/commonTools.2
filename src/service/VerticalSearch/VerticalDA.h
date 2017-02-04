#ifndef MUSIC_H_
#define MUSIC_H_

#include "general.h"
#include "../../segment/Segment.h"
#include "Index_da.h"
#include "../..//index/inv_index/doc_index.h"
#include "Da_Search.h"
#include "../../include/service_log.hpp"
using namespace WHITE_BLACK_DA;

class MUSIC{
public:
	MUSIC();
	~MUSIC();

	//int Init(const char* dir_base);
	//int Init(const char* dir_base,  string& DA_IndexFile_DLG,Darts::DoubleArray* DaIndex); // data directory
	int Init(const char* dir_base,  string& DA_IndexFile_DLG); // data directory
	int Release();
	int Normalize_(const char* query);
	int IndexOutcome(const char* query);//, std::ofstream& FILE_TEACHER);
	int MakeResponse(const char* query, const char* anwser);
public:
	SEGMENT_1 * seg;
private:
	DA_SEARCH *daSearch;
	int loadDic(const char* dir_base);
	std::map<std::string, int> Hash_punc;
};



#endif
