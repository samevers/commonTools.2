#include "UrlEncodeAndDecode.h"
#include "LoadBinaryFile.h"
#include <iostream>
#include <vector>
using namespace std;

int main()
{
	//string ss = "Æ»¹ûÊÖ»ú";
	//cout << url_encode(ss.c_str()) << endl;
	
	vector<float> v;
	v.push_back(0);
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);

	string outfile = "out.txt";
	FILEOP *fo = new FILEOP();
	cout << "------------1"<< endl;
	fo->WriteBinaryFileTest(v, outfile);
	cout << "------------2"<< endl;

	// load
	float* pLikely;
	int32_t column = 5;
	fo->LoadBinaryFileTest(outfile.c_str(), pLikely, column);
	cout << "------------3"<< endl;
	for(int i = 0; i < 5; i++)
		cout << pLikely[i] << " ";
	cout << endl;
	cout << "------------4"<< endl;

	return 0;
}
