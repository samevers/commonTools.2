#include "EditDist.h"
#include <iostream>
#include "segment/wordSegment.h"
#include "../../include/gary_common/gary_math.h"
#include "../../../web_segmentor/WordSegmentor4/IQSegmentor/IQDic.h"

using namespace std;
analysis::QuerySegmentor wordseg;

int main(int args, char* argv[])
{
	EditDist ed;
	wordSegment *seg;
	seg = wordSegment::getInstance();
	seg->Init();
	wordseg.open(analysis::DicTree::instance(), analysis::IQDic::instance());
	
	string line;
	string str1;
	string str2;
	int num = 1;
	while(getline(cin, line))// cin
	{
		int loc;
		if((loc = line.find("\t")) != -1)
		{
			str1 = line.substr(0,loc);
			str2 = line.substr(loc+1, line.length() - loc - 1);
		}
		string strtmp1 = str1;
		string strtmp2 = str2;
		spaceGary::deleteSpace(strtmp1);
		spaceGary::deleteSpace(strtmp2);

		// Term Importance
		vector <string> vec1;
		vector <string> vec2;
		vector <PAIR> impVec1;
		vector <PAIR> impVec2;
		seg->Segment_Imp_(strtmp1.c_str(), vec1, impVec1);
		seg->Segment_Imp_(strtmp2.c_str(), vec2, impVec2);
		//  Most Important term mush be contained in the pair query.
		int isContain = 0;
		if (impVec1.size() > 0)
			if(impVec1[0].first != "" && strtmp2.find(impVec1[0].first) != -1)
				isContain++;
		if (impVec2.size() > 0)
			if(impVec2[0].first != "" && strtmp1.find(impVec2[0].first) != -1)
				isContain++;

		if(isContain < 2)
			continue;

		//
		spaceGary::StringSplit(str1, vec1, " ");
		spaceGary::StringSplit(str2, vec2, " ");
		int dist = ed.edit(vec1,vec2);
		
		//if(dist >= str1.length()/2 || dist >= str2.length()/2)
		if(dist >= strtmp1.length() || dist >= strtmp2.length())
			continue;
		//double d = double(2*dist)/double(str1.length() + str2.length());
		double d = double(2*dist)/double(spaceGary::GMin(strtmp1.length(), strtmp2.length()));
		//
		cerr << "str1\t"<< strtmp1<< "\t" << strtmp1.length() << "\tstrtmp2\t"<< strtmp2<< "\t"<< strtmp2.length() <<"\tdist:\t" << d << endl;
		cout<< strtmp1<< "\t" << strtmp2 << "\t";
		cout << dist << endl;
	}
	wordSegment::releaseInstance();
	return 0;
}
