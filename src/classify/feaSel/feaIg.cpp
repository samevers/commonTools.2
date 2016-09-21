#include "feaIg.h"
#include <algorithm>
#include <dirent.h>
#include <math.h>
using namespace std;

#define DEBUG_ON 1
FeaIG::FeaIG()
{
}
FeaIG::~FeaIG()
{
}
int FeaIG::Init()
{
	totalDocumentNum = 0;
}

// Load file content of each class
int FeaIG::loadIgFile(const char* filename)
{
	string cla = filename;
	ifstream infile;
	infile.open(filename, ios::in);
	if(!infile)
	{
		cerr << "[ERROR] loadIgFile() is error!" << endl;
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

int FeaIG::loadIgData(vector<string>& filenames)
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
		loadIgFile(filename.c_str());
	 }
	 return 0;
}

int FeaIG::IG( vector<string>& filenames)
{
	loadIgData(filenames);
	// Cal Entropy top
	map<string,int64_t>::iterator iter_;
	double prob;
	double Entropy = 0;
	for(iter_ = DocumentNumOfCla.begin(); iter_ != DocumentNumOfCla.end(); iter_++)
	{
		prob = (double)iter_->second/(double)totalDocumentNum;
		cerr << "prob * log(prob) =  " << prob << " * " << log(prob) << endl;
		Entropy += -(prob*log(prob));
		cerr << "[INFO] Entropy = " << Entropy << endl;
	}
	cerr << "terminal [INFO] Entropy = " << Entropy << endl;
	
	map<string, int64_t>::iterator iter;
	for(iter = DocumentNumOfTerm.begin(); iter != DocumentNumOfTerm.end(); iter ++)
	{
		string term = iter->first;// term or feature,labeled as '1'.
		int64_t termDocuNum = iter->second;// number of that labeled as '1'.
		double prop = (double)termDocuNum/(double)totalDocumentNum;
		//cout << "term:" << term << "\ttermDocuNum:" << termDocuNum << "\ttotalDocumentNum:" << totalDocumentNum << endl;
		// entropy of each term
		double entropy = 0;
		//for(iter_ = DocumentNumOfCla.begin(); iter_ != DocumentNumOfCla.end(); iter_++)
		iter_ = DocumentNumOfCla.begin();
		if(iter_ != DocumentNumOfCla.end())
		{
			string cla  = iter_->first;
			int64_t ClaDocNum = iter->second;
			int64_t termInClaNum;
			if (trainInfo.find(make_pair(term,cla)) != trainInfo.end())
				termInClaNum = trainInfo[make_pair(term,cla)];
			else
				termInClaNum = 0;
			int64_t termNotInClaNum = termDocuNum - termInClaNum;
			//cout << "number of term <" << term << " > in :" << cla << " = " << termInClaNum << endl;
			double p_1 = (double)(termInClaNum+1)/(double)(termDocuNum+1);// prob that term appears in cla.
			double p_0 = (double)(termNotInClaNum+1)/(double)(termDocuNum+1);  // prob that term dont appears in cla.
			//cout << "entropy = " << prop << "* (" <<p_1 << "*"<< log(p_1) << " + " << p_0 << "*" << log(p_0) << endl;
			if(p_1 == 0 || p_0 == 0)
			{
				//cout << "===========================================" << endl;
				//continue;
				// entropy = 0;
			}
			else
				entropy = -1 * (p_1*log(p_1) + p_0*log(p_0));
				//entropy = -prop * (p_1*log(p_1) + p_0*log(p_0));
			//cout << "entropy = " << entropy << endl;
		}
		double ig =  Entropy - entropy ;
		//feaIG[term] = entropy;
		feaIG[term] = ig;
		//cout << "===========================================" << endl;
	}
	
	return 0;
}
int FeaIG::OutputFea(const char* filename)
{
	ofstream outfile;
	outfile.open(filename, ios::out);
	if(!outfile)
	{
		cerr << "[ERROR] Fail to build OutputFea file." << endl;
		return -1;
	}
	map<string, double>::iterator iter;
	//map<string, map<string,double> >::iterator iter;
	for(iter = feaIG.begin(); iter != feaIG.end(); iter++)
	{
		string term = iter->first;
		double weight = iter->second;
		outfile << term << "\t" << weight << endl;
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
		cerr << "\t./feaAbs testdata feaIG.txt" << endl;
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
	FeaIG feasel;
	feasel.Init();
	feasel.IG(filenames);
	feasel.OutputFea(outputfile.c_str());
	return 0;
}
