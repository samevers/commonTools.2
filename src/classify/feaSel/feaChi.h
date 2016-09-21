#ifndef __FeaChiECT_HEAD__
#define __FeaChiECT_HEAD__

#include "../../include/gary_common/gary_string.h"
#include <fstream>
using namespace std;

class FeaChi{
	public:
		FeaChi();
		~FeaChi();
		int Init();
		int OutputFea(const char* filename);
		int CHI(vector<string>& filenames);
	private:
		int loadChiFile(const char* filename);
		int loadChiData(vector<string>& filenames);
	private:
		map<pair<string,string>,int64_t> trainInfo;
		map<string,int64_t> DocumentNumOfTerm;
		map<string,int64_t> DocumentNumOfCla;
		int64_t totalDocumentNum;
		map<pair<string, string>, double> feaCHI;


};
#endif
