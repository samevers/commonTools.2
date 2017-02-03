#include "commonTalk.h"
using namespace std;
const static int CLASSNUM=14;
const static string CLASSNAME[]={"time","date","note","alarming","mail","message","call","navigate","searchEngine","music","novel","movie","map","sayHi"};


commonTalk::commonTalk(){
	querymatch = QueryMatch::getInstance();
	vClassName.clear();
	for(int i=0; i<CLASSNUM; i++)
	{
		vClassName.push_back(CLASSNAME[i]);
	}

}
commonTalk::~commonTalk(){

	delete querymatch;
}
bool commonTalk::Init(string path){
	// QueryMatch init.
	querymatch->open(path.c_str());
}

int commonTalk::commonTalkResponse(
		string query,
		long long request_id,
		SEGMENT_1* wordSeg,
		map<string,ClassInfo>& classmap)
{
	ClassInfo cInfo;
	cInfo.reform=query;
	cInfo.final=0.0;
	cInfo.qofinal=0.0;
	cInfo.score=0.0;
	cInfo.lexionProb=0.0;
	cInfo.querylogProb=0.0;
	cInfo.querylmProb=0.0;
	cInfo.corpuslmProb=0.0;
	cInfo.websearchProb=0.0;
	cInfo.vssearchProb=0.0;
	cInfo.intensity=0.0;
	cInfo.shWhite = 0;
	cInfo.shBlack = 0;
	cInfo.key = "";
	cInfo.data = "";
	cInfo.blackLabel = "";
	cInfo.isBlack = 0;
	cInfo.whiteLabel = "";
	cInfo.isWhite = 0;
	cInfo.iswapPc = 2;// Ä¬ÈÏpc
	cInfo.vr_level = 0;

	vector<string>::iterator vIterstr;
	for(vIterstr=vClassName.begin(); vIterstr!=vClassName.end(); vIterstr++)
	{
		cInfo.className = *vIterstr;
		classmap[*vIterstr]=cInfo;
	}

	// QueryMatch
	int querylen = query.length();
	vector<ResultData> matchVec;
	_INFO("Query : %s" , query.c_str());
	querymatch->classifyQuery(query.c_str(), query.c_str(),querylen, matchVec,request_id, wordSeg);
	map<string, int> querymatchBlack;
	_INFO("SIZE of matchVec = %d", matchVec.size());
	for(std::vector<ResultData>::iterator it = matchVec.begin(); it != matchVec.end(); it++)
	{
		vector<string> flagVec;
		spaceGary::StringSplit(it->type, flagVec, "@");
		if(flagVec.size() == 2)
		{
			if(flagVec[1] == "black")
			{
				querymatchBlack[flagVec[0]] = 1;
			}
			continue;
		}
		cInfo.className = it->type;
		cInfo.score = 1;
		classmap[cInfo.className] = cInfo;
		_INFO("classname :%s, score : %d",it->type.c_str(),1);
		if(it->black != "0")
		{
			vector<string> flagBlack;
			spaceGary::StringSplit(it->black,flagBlack, "@");
			_INFO("QueryMatch hit black...");
			for(vector<string>::iterator itt = flagBlack.begin(); itt != flagBlack.end(); itt++)
			{
				querymatchBlack[*itt] = 1;
			}
		}
		if(it->white != "0")
		{
			vector<string> flagWhite;
			spaceGary::StringSplit(it->white,flagWhite, "@");
			_INFO("QueryMatch hit white...");
			for(vector<string>::iterator itt = flagWhite.begin(); itt != flagWhite.end(); itt++)
			{
				cInfo.className = *itt;
				classmap[*itt] = cInfo;
			}
		}
	}
	
	return 0;
}

