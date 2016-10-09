/************************************************
 * @yonghuahu 									*
*************************************************/
#ifndef SEGMENT_HEAD_H__
#define SEGMENT_HEAD_H__

#include "../include/general.h"
#include "../include/gary_common/gary_string.h"
#include "../include/string_utils.h"
#include "WordSegmentor4/Segmentor/Graph.h"
#include "Platform/bchar.h" 
#include "Platform/encoding.h" 
#include "Platform/encoding/support.h"
#include "Platform/encoding/EncodingConvertor.h"
#include "Platform/encoding/stringmatch/AhoCorasick.h"
#include "Platform/gchar.h"
#include "../include/service_log.hpp"
#include <boost/algorithm/string.hpp>
#include "../include/common_index.h"
#include "WordSegmentor.h"
#include "WordSegmentor4/IQSegmentor/QuerySegmentor.h"
#include "WordSegmentor4/IQSegmentor/IQSegmentor.h"
#include "WordSegmentor4/Segmentor/Graph.h"


class SEGMENT_1{
	private:
		analysis::TGraph m_graph_segment;
		static SEGMENT_1 *ddinstance;
	public:
		SEGMENT_1();
		~SEGMENT_1();
		static SEGMENT_1* getInstance();
		static void releaseInstance();
		WordSegmentor* segmentor;
		EncodingConvertor* ec;
	public:
		int32_t Segment_(const std::string& query, std::vector<std::string>& parts);
		//int Segment_Imp_(const char* query, std::vector<std::string>& termList, std::vector<PAIR>& outVec, analysis::QuerySegmentor *wordseg);
		//int highImp_(const char* query, std::vector<std::string>& termList, analysis::WordSegmentorInfo* parsed, std::vector<PAIR>& outVec);
		int32_t Init();
		int32_t Release();
};


#endif
