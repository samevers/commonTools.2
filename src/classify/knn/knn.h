#ifndef _KNN_HEAD_H__
#define _KNN_HEAD_H__

#include "../../include/general.h"
#include "../../include/service_log.hpp"
#include "../../include/gary_common/gary_string.h"
#include "../../include/gary_common/gary_common.h"
#include "../../include/gary_common/gary_math.h"



class KNN_{
	private:
		int dimension;
		int32_t thres;
	public:
		KNN_();
		~KNN_();

	public:
		int readFile(std::string filename, std::vector<std::vector<string> >& dataVec);
		int gen_dot(std::string filename, std::vector<std::vector<string> >& dataVec);
		int nearest(std::vector<string>& predictVec, std::vector<std::vector<string> >& dataVec);
		int genVector(std::string line, std::vector<string>& weightArrDou);

		int Run_(std::string filename,std::string predictFile);

};
#endif

