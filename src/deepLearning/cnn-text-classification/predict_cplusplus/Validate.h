#ifndef __IMIAGECONVMODEL_H__
#define __IMIAGECONVMODEL_H__

#include <vector>
#include <iconv.h>
#include <fstream>
#include <string>
#include <cassert>
#include <sys/time.h>
#include <iostream>
#include <map>
#include "include/gary_common/gary_string.h"
#include "Platform/log.h"
#include "../QueryOptimizer/service_log.hpp"
#include "worker.hpp"

class CONVIMAGE_C{
private:
	float *embd, *cw3, *cw4, *cw5, *cb3, *cb4, *cb5, *ow, *ob, *convidres;
	std::map<std::string, int> idmap;
	int32_t dimnum; 
	int32_t filnum;
	int32_t padnum;
	int32_t filid;
	int32_t padid;
	int32_t embdNum;
	float ModelConvThreshold;

public:
	CONVIMAGE_C();
	~CONVIMAGE_C();

	//static CONVIMAGE_C* getInstance();
	//static void releaseInstance();
	int LoadModel(const char * filename);
	int Validate(std::vector<std::string> queryseg, float& score0, float& score1);
	int IntentWeight(std::vector<std::string>& queryseg,
			const char* query,
			std::map<std::string, ClassInfo>& classmap, Worker *worker,
			std::string& vrname);
	int LoadConvModel(std::string& ModelPathConv);
	int PrintPara();
};
#endif
