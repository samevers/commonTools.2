#include "EditDist.h"
#include <iostream>
#include "segment/Segment.h"
using namespace std;

int main(int args, char* argv[])
{
	EditDist ed;
	SEGMENT_1 *seg;
	seg = SEGMENT_1::getInstance();
	seg->Init();

//	string str1 = argv[1];
//	string str2 = argv[2];
	string line;
	string str1;
	string str2;
	while(getline(cin, line))
	{
		int loc;
		if((loc = line.find("\t")) != -1)
		{
			str1 = line.substr(0,loc);
			str2 = line.substr(loc+1, line.length() - loc - 1);
		}
		vector <string> vec1;
		vector <string> vec2;
		// vec1
		bool isContain = 0;
		seg->Segment_(str1,vec1);
		seg->Segment_(str2,vec2);
		for(int i = 0; i < vec1.size(); i++)
			if(str2.find(vec1[i]) != -1)
				isContain = 1;
		if(isContain == 0)
			continue;
		//
		cout<< str1<< "\t" << str2 << "\t";
		cout << ed.Calculate(str1, str2, seg) << endl;
	}
	SEGMENT_1::releaseInstance();
	return 0;
}
