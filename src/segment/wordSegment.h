#ifndef __SOGOU_QUERYCLASS_H
#define __SOGOU_QUERYCLASS_H

#include <set>
#include <map>
#include <vector>
#include "Platform/encoding/support.h"
#include "Platform/encoding/EncodingConvertor.h"
#include "Platform/encoding/stringmatch/AhoCorasick.h"
//#include "WordSegmentor4/CommonSegmentor/WordSegmentor.h"
#include "Platform/encoding.h"
#include "Platform/gchar.h"
#include "WordSegmentor4/IQSegmentor/IndexSegmentor.h"
#include "WordSegmentor4/IQSegmentor/QuerySegmentor.h"
#include "WordSegmentor4/IQSegmentor/IQSegmentor.h"
#include "WordSegmentor.h"
#include "GraphSegmentor.h"


typedef std::pair<std::string, int32_t> PAIR;

class wordSegment{
	private:
		analysis::TGraph m_graph_segment;
		EncodingConvertor* ec;
		analysis::DicTree* dictree;
		analysis::IQDic* iqdic;
		
		WordSegmentor* segmentor;
		GraphSegmentor* graphSeg;
		analysis::QuerySegmentor wordseg;

	public:
		wordSegment();
		~wordSegment();
		static wordSegment *ddinstance;
		static wordSegment* getInstance();
		static void releaseInstance();
	public:
		int32_t Segment_(std::string& query, std::vector<std::string>& parts);
		int Segment_Imp_(const char* query, std::vector<std::string>& termList, std::vector<PAIR>& outVec);
		int highImp_(const char* query, std::vector<std::string>& termList, analysis::WordSegmentorInfo* parsed, std::vector<PAIR>& outVec);
		int32_t Init();
		int32_t Release();
};


#endif
