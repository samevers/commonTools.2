#ifndef __FeaIGECT_HEAD__
#define __FeaIGECT_HEAD__

#include "../../include/gary_common/gary_string.h"
#include <fstream>
using namespace std;

class FeaIG{
	public:
		FeaIG();
		~FeaIG();
		int Init();
		int OutputFea(const char* filename);
		int IG(vector<string>& filenames);
	private:
		int loadIgFile(const char* filename);
		int loadIgData(vector<string>& filenames);
	private:
		map<pair<string,string>, int64_t> trainInfo;
		map<string,int64_t> DocumentNumOfTerm;
		map<string,int64_t> DocumentNumOfCla;
		int64_t totalDocumentNum;
		map<string, double> feaIG;


};
#endif
