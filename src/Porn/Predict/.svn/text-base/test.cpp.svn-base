#include "isPorn.h"
#include "gary_string.h"
#include "gary_common.h"

using namespace std;

int main()
{
	textCategorization tc;
	tc.init();
	string test = "天海 翼 一丝 不挂 裸照 操逼";
	while(getline(cin, test))
	{
		vector<string> vec;
		spaceGary::StringSplit(test, vec, " ");
		double confidence = tc.predict_wordDist(test, vec);
		cout << "[INFO] Confidence = " << confidence  << "\t";
		if(confidence < 0)
		{
			cout << "query:" << test << "\tis porn." << endl;
		}else
			cout << "query:" << test << endl;

	}
	return 0;
}
