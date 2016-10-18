#include "knn.h"
#include "../../Similarity/editDist/EditDist.h"

using namespace std;
EditDist ed;

KNN_::KNN_()
{
	thres = 1;
	dimension = 0;
}
KNN_::~KNN_()
{
	;
}

int KNN_::readFile(string filename, vector<vector<string> >& dataVec)
{
	ifstream infile;
	_INFO("Read File : %s",  filename.c_str());
	if(spaceGary::open_f(filename, infile) == -1)
	{
		_ERROR("Fail to open file %s\n", filename.c_str());
		return -1;
	}

	string line;
	dataVec.clear();
	vector<string> weightArr;
	int lineNum = 0;
	while(getline(infile,line))
	{
		spaceGary::StringTrim(line);
		weightArr.clear();
		spaceGary::StringSplit(line, weightArr, " ");
		dataVec.push_back(weightArr);
		if(lineNum ++ % 50 == 0)
			_INFO("%d\n", lineNum);
	}

	infile.close();

	return lineNum;
}
int KNN_::gen_dot(string filename, vector<vector<string> >& dataVec)
{
	int lineNum = readFile(filename, dataVec);
	if(lineNum == -1)
	{
		_ERROR("Fail to readFile() ...\n");
		return -1;
	}else
		_INFO("readFile() is ok ...");

	return 0;
}

int KNN_::nearest(vector<string>& predictVec, vector<vector<string> >& dataVec)
{
	int i, min_i;
	int d, min_d;

	for (i = 0; i < dataVec.size(); i++)
	{
		d = ed.edit(predictVec,dataVec[i]);
		if (d < min_d)
		{
			min_d = d;
			min_i = i;
		}
	}

	return min_d;
}

//int KNN_::genVector(string line, vector<string>& weightArrDou)
//{
//	vector<string> weightArr;
//	spaceGary::StringSplit(line, weightArr, " ");
//	int eleNumInLine = 0;
//	for (int i = 0; i < weightArr.size(); i++)
//	{
//		int32_t w = spaceGary::toDouble(weightArr[i]);
//		if(w > 0)
//		{
//			eleNumInLine ++;
//		}
//		weightArrDou.push_back(w);
//		weightArr.clear();
//	}
//	return 0;
//}
#define PTS 100000
#define K 11
int KNN_::Run_(string filename, string predictFile)
{
	int i;
	// gen vector
	_INFO("Read File : %s",  filename.c_str());
	vector<vector<string> > dataVec;
	if(gen_dot(filename,dataVec) == -1)
		return -1;
	_INFO("readFile is ok ...");

	ifstream inputPredict;
	if(spaceGary::open_f(predictFile, inputPredict) == -1)
	{
		_ERROR("Fail to open file <%s>", predictFile.c_str());
		return -1;
	}
	string line;
	vector<string> predictVec;
	while(getline(inputPredict, line))
	{
		spaceGary::StringTrim(line);
		spaceGary::StringSplit(line, predictVec, " ");
		//genVector(line, predictVec);
		int d = nearest(predictVec, dataVec);
		cout << d << "\t" << line << endl;
	}

	return 0;
}
