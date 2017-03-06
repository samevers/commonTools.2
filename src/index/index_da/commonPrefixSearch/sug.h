#ifndef SUGGUESTION_HEAD_H__
#define SUGGUESTION_HEAD_H__

#include "../include/general.h"
#include "Index_da.h"
#include "darts.h"

class SUGGUESTION{
	public:
		SUGGUESTION();
		~SUGGUESTION();
	private:
		Darts::DoubleArray* sugDa; // 
		char * sugDaBuf;
		uint32_t sugDaLen;
	public:
		int Init();
		int Release();
		int getSugguestion(const char*  query, std::vector<std::string>& sugs);
};



#endif
