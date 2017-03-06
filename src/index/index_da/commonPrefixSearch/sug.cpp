#include "sug.h"
#include "../include/service_log.hpp"

using namespace std;
using namespace WHITE_BLACK_DA;


const static string SugFilePath = "sugFile.dat";
const static string SugIndexFilePath = "sugFile.index";
const static int kMaxCommonPrefixNum = 10;

SUGGUESTION::SUGGUESTION()
{}
SUGGUESTION::~SUGGUESTION()
{
	Release();
}

int SUGGUESTION::Init()
{
	WhiteBlackList_ sugOp;
	int ret;
	//ret = sugOp.MakeIndex(SugFilePath.c_str(), SugIndexFilePath.c_str(), "extend");
	if(ret != 0)
	{
		_ERROR("Make Index of Sugguestion error.");
	}
	sugDa =  new Darts::DoubleArray();
	ret = sugOp.LoadIndex(SugIndexFilePath.c_str(), sugDa,sugDaBuf,sugDaLen );
	if (ret != 0)
	{
		_ERROR("Fail to LoadIndex() of sug index file.");
	}
	_INFO("Load sug index file ok.");

	return 0;
}
int SUGGUESTION::Release()
{
	if(sugDa != NULL)
	{
		delete sugDa;
		sugDa = NULL;
	}
	if(sugDaBuf != NULL)
	{
		delete sugDaBuf;
		sugDaBuf = NULL;
	}
	return 0;
}
int SUGGUESTION::getSugguestion(const char* query, vector<string>& sugs)
{
	Darts::DoubleArray::result_type all_result[kMaxCommonPrefixNum];
	_INFO("QUERY = %s", query);
	for(int i = 0; i < strlen(query); i++)
	{
		cout << "query = " << query + i << endl;
		size_t result_num = sugDa->commonPrefixSearch(
				query + i, all_result, kMaxCommonPrefixNum);
		_INFO("result_num of commonPrefixSearch = %d", result_num);
	
		if(result_num > kMaxCommonPrefixNum)
		{
			result_num = kMaxCommonPrefixNum;
		}
		if (result_num == 0)
		{
			_INFO("Cannot find any sugguestion in the history.");
		}
	
		Darts::DoubleArray::result_type ret_value;
		for(size_t j = 0; j < result_num; j++)
		{
			ret_value = all_result[j];
			cout << sugDaBuf[ret_value] << endl;
			//sugs.push_back(sug);
		}
	}
	return 0;
}
