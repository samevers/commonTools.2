#include <fstream>
#include <iostream>
#include <sstream>
#include <cmath>
#include <regex.h>
#include "Platform/log.h"
#include "wordSegment.h"

using namespace std;
const static int MAXSTRLEN=1024;
const static int _MAXQUERYLEN=MAXSTRLEN/2;
wordSegment* wordSegment::ddinstance;

bool CompByValue(const PAIR& p1, const PAIR& p2){
	return p1.second > p2.second;
}

wordSegment::wordSegment()
{
	EncodingConvertor::initializeInstance();
	ec = EncodingConvertor::getInstance();
	dictree = analysis::DicTree::instance();
	iqdic = analysis::IQDic::instance();
	segmentor = WordSegmentor::getInstance();
	graphSeg = GraphSegmentor::getInstance();
	iqdic->loadDic();
	dictree->loadDic();

	wordseg.open(analysis::DicTree::instance(), analysis::IQDic::instance());
	analysis::TGraph annseg;
	annseg.open(analysis::DicTree::instance());
}

wordSegment::~wordSegment()
{
}
int wordSegment::Init()
{
}

wordSegment* wordSegment::getInstance(){
	if(!ddinstance){
		ddinstance=new wordSegment();
	}
	return ddinstance;
}
void wordSegment::releaseInstance(){
	if(ddinstance){
		delete ddinstance;
		ddinstance=NULL;
	}
}


int wordSegment::Segment_Imp_(const char* query, vector<string>& termList, vector<PAIR>& outVec)
{
	int querylen = strlen(query);
	if(!query || querylen < 1 || querylen > _MAXQUERYLEN){return false;}
	char buffer[MAXSTRLEN];
	memset(buffer, 0,  MAXSTRLEN);
	int len = ec->t2sgchar(query, (gchar_t*)buffer, _MAXQUERYLEN, true);
	if(len>=_MAXQUERYLEN || len < 0){return false;}
	buffer[len*2] = '\0';
	string gQuery(buffer);
	int glen = strlen(buffer) / 2;

	analysis::WordSegmentorInfo request;
	analysis::WordSegmentorInfo parsed;
	
	segmentor->Segment(&wordseg, buffer, request, parsed, termList);

	highImp_(query, termList, &parsed, outVec);

	return 0;
}

int wordSegment::highImp_(const char* query, vector<string>& termList, analysis::WordSegmentorInfo* parsed, vector<PAIR>& outVec)
{
	// High importance term
	float termImp;
	vector<string> vec_imp;
	map<string, int32_t> hash_imp;
	string MaxTerm;
	double Maxprob = 0.0;
	for(int i =0; i < termList.size(); i++)
	{
		termImp = (float)parsed->termImportance[i];
		if(termList.size() > 2)
		{
			//if(termImp > 1 && termList[i].length() >= 4)// 2个字以上的term 
			if(termImp > 5 )
			{
				hash_imp[termList[i] ] = termImp;
				vec_imp.push_back(termList[i]);
		   		if(Maxprob < termImp)
				{
					MaxTerm = termList[i];
					Maxprob = termImp;
				}
			}
		}else
		{
			//if(termList[i].length() >= 4)// 2个字以上的term 
			{
				hash_imp[termList[i] ] = termImp;
				vec_imp.push_back(termList[i]);
				vec_imp.push_back(termList[i]);
		   		if(Maxprob < termImp)
				{
					MaxTerm = termList[i];
					Maxprob = termImp;
				}
			}
		}
		//cerr << "[debug_sam] seg imp = " << termList[i] << "\t" << ((float)(parsed->termImportance[i]))<< endl;
	}
	vector<PAIR> hash_vec(hash_imp.begin(), hash_imp.end());
	sort(hash_vec.begin(), hash_vec.end(), CompByValue);
	outVec = hash_vec;

	return 0;	
}

int32_t wordSegment::Segment_(string& query,vector<string>& termList )
{
	int32_t num = 0;
	while(getline(cin, query))
	{
		int querylen = query.length();
		num ++;
		if(querylen < 1 ){
			cerr << "[error] querylen is too short : line " << num << endl;
			cout << endl;
			continue;
		}
		char buffer[MAXSTRLEN];
		memset(buffer, 0,  MAXSTRLEN);
		int len = ec->t2sgchar(query.c_str(), (gchar_t*)buffer, MAXSTRLEN/2, true);
		if(len>=MAXSTRLEN/2 || len < 0){
			cerr << "[error] querylen is too long" << endl;
			cout << endl;
			continue;
		}
		buffer[len*2] = '\0';
		string gQuery(buffer);
		int glen = strlen(buffer) / 2;
	
		analysis::WordSegmentorInfo request;
		analysis::WordSegmentorInfo parsed;
		
		segmentor->Segment(&wordseg, buffer, request, parsed, termList);
		for(int i = 0; i < termList.size(); i++)
			cout << termList[i] << " ";
		cout << endl;
	}
	return 0;

}
