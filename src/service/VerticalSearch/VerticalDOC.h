#ifndef VERTICAL_DOC_H_
#define VERTICAL_DOC_H_

#include "general.h"
#include "../../segment/Segment.h"
#include "Index_da.h"
#include "../..//index/inv_index/doc_index.h"
#include "Doc_Search.h"
#include "../../include/service_log.hpp"
using namespace WHITE_BLACK_DA;

class VERTICAL_DOC{
public:
	VERTICAL_DOC();
	~VERTICAL_DOC();

	//int Init(const char* dir_base);
	//int Init(const char* dir_base,  string& DA_IndexFile_DLG,Darts::DoubleArray* DaIndex); // data directory
	int Init(const char* dir_base,  const string& DA_IndexFile_DLG); // data directory
	int Release();
	int Normalize_(const char* query);
	int IndexOutcome(const char* query);//, std::ofstream& FILE_TEACHER);
	int MakeResponse(const char* query, const char* anwser);
	int show_results(size_t query_length, map<int, string>& da_vec, string& anwser);
public:
	SEGMENT_1 * seg;
private:
	DOC_SEARCH *docSearch;
	int loadDic(const char* dir_base);
	std::map<std::string, int> Hash_punc;
};



#endif
