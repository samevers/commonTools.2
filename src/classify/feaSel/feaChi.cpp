#include "feaChi.h"
#include <algorithm>
#include <dirent.h>

#define DEBUG_ON 1
FeaChi::FeaChi()
{
}
FeaChi::~FeaChi()
{
}
int FeaChi::Init()
{
	totalDocumentNum = 0;
}

/*
int FeaChi::readFiles(string dirname, vector<string>& filenames)
{
	DIR *pDir;
	struct dirent* ent = NULL;
	int level = 2;
	pDir = opendir(dirname.c_str());
	if(pDir == NULL)
	{
		cerr << "[ERROR] readFiles the dirname is error!" << endl;
		return -1;
	}
	while(NULL != (ent = readdir(pDir)))
	{
		if(ent->d_type == 8)
		{
			for (int i = 0; i < level; i ++)
			{
				cout <<"-";
			}
			cout << ent->d_name << endl;
		}else
		{
			if(strcmp(ent->d_name, ".") == 0 || 
				strcmp(ent->d_name,"..") == 0)
				continue;
			// directory
			//string _path(dirname);
			//string _dirName(ent->d_name);
			//string fullDirPath = _path + "/" + _dirName;
			string filename = dirname + "/" + ent->d_name;
			filenames.push_back(filename);
		}
	}
	return 0;
}
*/
// Load file content of each class
int FeaChi::loadChiFile(const char* filename)
{
	string cla = filename;
	ifstream infile;
	infile.open(filename, ios::in);
	if(!infile)
	{
		cerr << "[ERROR] loadChiFile() is error!" << endl;
		return -1;
	}
	string line;
	vector<string> terms;
	map<string,int> isIn;
	while(getline(infile,line))
	{
		isIn.clear();
		spaceGary::StringTrim(line);
		spaceGary::StringSplit(line, terms, " ");
		for(int i = 0; i < terms.size(); i++)
		{
			string word = terms[i];
			if(isIn.find(word) != isIn.end())
			{
				isIn[word]++;
				continue;
			}else
				isIn[word] = 1;
			trainInfo[make_pair(word,cla)] ++;
			DocumentNumOfTerm[word] ++;
		}
		DocumentNumOfCla[cla]++;
		totalDocumentNum++;
	}
	return 0;
}

int FeaChi::loadChiData(vector<string>& filenames)
{
	int64_t totalDocumentNum = 0;
	if(filenames.size() < 2)
	{
		cerr << "[ERROR] File number is 2, at least." << endl;
		return -1;
	}
	 for(int i = 0; i < filenames.size(); i++)
	 {
	 	string filename = filenames[i];
		loadChiFile(filename.c_str());
	 }
	 return 0;
}

int FeaChi::CHI( vector<string>& filenames)
{
	loadChiData(filenames);
	map<pair<string,string>, int64_t>::iterator iter;
	for(iter = trainInfo.begin(); iter != trainInfo.end(); iter ++)
	{
		string term = iter->first.first;
		string cla  = iter->first.second;
		int64_t A = iter->second;
		int64_t B = DocumentNumOfTerm[term] - A;
		int64_t C = DocumentNumOfCla[cla] - A;
		int64_t D = totalDocumentNum - A - B - C;
		int64_t AD = A * D;
		int64_t BC = B * C;
		int64_t A_B = A + B;
		int64_t C_D = C + D;
		int64_t fractions = AD - BC;
		int64_t numerate = A_B*C_D;
		int64_t N = A + B + C + D;
		fractions = fractions/N;
		double weight = (double)(fractions*fractions)/(double)(numerate);
		feaCHI[make_pair(term,cla)] = weight;
	}
	
	return 0;
}
int FeaChi::OutputFea(const char* filename)
{
	ofstream outfile;
	outfile.open(filename, ios::out);
	if(!outfile)
	{
		cerr << "[ERROR] Fail to build OutputFea file." << endl;
		return -1;
	}
	map<pair<string,string>, double>::iterator iter;
	for(iter = feaCHI.begin(); iter != feaCHI.end(); iter++)
	{
		string term = iter->first.first;
		string cla = iter->first.second;
		double weight = iter->second;
		outfile << term << "\t" << cla << "\t" << weight << endl;
	}
	outfile.close();
	return 0;
}
/*
 * Train files have to be segmented content.
 * Have to be more than 2 files, each file is a class.
 * Features: Only consider terms appears in all the classes files, at the same time.
 */
int main(int argc, char** argv)
{
	if(argc < 2)
	{
		cerr << "[ERROR] Please input a directory that ur training file more than 2 classes, and outputfile name. e.g.," << endl;
		cerr << "\t./feaAbs testdata feaCHI.txt" << endl;
		return -1;
	}
	string dirname= argv[1];
	string outputfile = argv[2];
	if (dirname == "")
	{
		cerr << "[ERROR] INPUT Direcotry is NULL, Please check!" << endl;
		return -1;
	}
	vector<string> filenames;
	spaceGary::readFiles(dirname, filenames);
#if DEBUG_ON
	for(int i = 0; i < filenames.size(); i++)
		cerr << "FILE: " << filenames[i] << endl;
#endif
	FeaChi feasel;
	feasel.Init();
	feasel.CHI(filenames);
	feasel.OutputFea(outputfile.c_str());
	return 0;
}
