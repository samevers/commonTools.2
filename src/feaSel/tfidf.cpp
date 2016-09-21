#include "tfidf.h"
#include <math.h>

using namespace std;

TF_IDF::TF_IDF()
{
	num_doc = 0;
}
TF_IDF::~TF_IDF()
{
	tf.clear();
	idf.clear();
	tf_idf.clear();
}
int TF_IDF::Init()
{
}

int TF_IDF::Train_data_count(vector<string>& filenames)
{
	ifstream infile;
	for(int i = 0; i < filenames.size(); i ++)
	{
		string trainfile = filenames[i];
		cerr << "[INFO] FILE : " << trainfile << endl;
		infile.open(trainfile.c_str(), ios::in);
		if(!infile)
		{
			cerr << "[ERROR] Fail to open input file." << endl;
			return -1;
		}
	
		string line;
		string word;
		vector<string> vec;
		map<string, int64_t> tmp;
		map<string, int64_t> termNum;
		map<string, int64_t>::iterator iter;
		int64_t termTotal = 0;
		tmp.clear();
		termNum.clear();
		while(getline(infile, line))
		{
			spaceGary::StringTrim(line);
			spaceGary::StringSplit(line, vec, " ");
	
			for(int i = 0; i < vec.size(); i++)
			{
				word = vec[i];
				tmp[word] = 1;
				termNum[word]++;
				termTotal ++;
			}
		
		}
		// tf
		for(iter = termNum.begin(); iter != termNum.end(); iter ++)
		{
			word = iter->first;
			int64_t freq = iter->second;
			double tfValue = (double)freq/(double)termTotal;
			tf[make_pair(word,trainfile)] = tfValue;
		}

		// idf	
		for(iter = tmp.begin(); iter != tmp.end(); iter++)
		{
			df[iter->first]++;
		}
		num_doc++;
		infile.close();
	}
	return 0;
}


int TF_IDF::Tf_Idf_Count()
{
	string word;
	map<pair<string,string>,double>::iterator iter;
	for(iter = tf.begin(); iter != tf.end(); iter++)
	{
		word = iter->first.first;
		string cla = iter->first.second;
		if(df[word] < 1)
			continue;

		double tfValue = iter->second;
		double idfValue = (double)num_doc/(double)df[word];
		//cout << "----------------------------------------" << endl;
		//cout <<"tf = " << tfValue << "\tidf = " << idfValue << endl;
		idfValue = log(idfValue+ 0.001);
		//cout << "word:" << word << "\tcla:" << cla << endl;
		//cout <<"tf = " << tfValue << "\tidf = " << idfValue << endl;
		double weight = tfValue*idfValue;
		tf_idf[make_pair(word,cla)] = weight;
	}
	return 0;
}

int TF_IDF::Output_Tf_Idf(string& outputfile)
{
	ofstream outfile;
	outfile.open(outputfile.c_str(), ios::out);
	if(!outfile)
	{
		cerr << "[ERROR] Fail to build output file." << endl;
		return -1;
	}

	map<pair<string,string>, double >::iterator iter;
	for(iter = tf_idf.begin(); iter != tf_idf.end(); iter++)
	{
		string word = iter->first.first;
		string cla = iter->first.second;
		double tfidfValue = iter->second;
		outfile << "cla:" << cla<<"\tterm:" << word << "\ttfidfValue:" << tfidfValue << endl;
	}
	outfile.close();
	return 0;
}
int TF_IDF::run(vector<string>& filenames, string& outputfile)
{
	Train_data_count(filenames);
	Tf_Idf_Count();
	Output_Tf_Idf(outputfile);

	return 0;
}

int main(int argc, char** argv)
{
	if(argc < 2)
	{
		cerr << "[ERROR] Please input a directory that ur training file more than 2 classes, and outputfile name. e.g.," << endl;
		cerr << "\t./tfidf testdata tfidf.txt" << endl;
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

	// ----------------------------//
	TF_IDF tfIdf;
	tfIdf.Init();
	tfIdf.run(filenames, outputfile);

	return 0;
}
