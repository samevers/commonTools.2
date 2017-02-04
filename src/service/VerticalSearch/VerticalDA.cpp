#include "VerticalDA.h"
#include <stdlib.h>
using namespace std;



const static string FILE_PUNC = "punc/punc.txt";
const static int threshold = 50;			// data[i].length()/query.length()，太大的话，表示查找失败；
static queue<string> context;				// 保存上下文
static map<string, int> hash_context;		// 保存上下文

//
MUSIC::MUSIC()
{
	EncodingConvertor::initializeInstance();
	analysis::DicTree::instance()->loadDic();
}
MUSIC::~MUSIC()
{
	Release();
}
int MUSIC::loadDic(const char* dir_base)
{
	// load punc dict
	ifstream infile;
	string puncFilePath = string(dir_base) + "/data/" + FILE_PUNC;
	_INFO("[INFO] path of punc.txt: %s", puncFilePath.c_str());
	infile.open(puncFilePath.c_str(), ios::in);
	if(!infile)
	{
		cerr << "[ERROR] : Fail to open punc.txt file!" << endl;
		return -1;
	}
	string line;
	while(getline(infile, line))
	{
		spaceGary::StringTrim(line);
		if(line != "" && line != " ")
		{
			Hash_punc[line] ++;
		}
	}
	infile.close();
	//
	
	return 0;
}
//int MUSIC::Init(const char* dir_base, string& DA_IndexFile_DLG,Darts::DoubleArray* DaIndex) // data directory
int MUSIC::Init(const char* dir_base, string& DA_IndexFile_DLG) // data directory
{
	// Load dicts	
	if(loadDic(dir_base) == -1)
	{
		return -1;
	}
	seg = SEGMENT_1::getInstance();
	seg->Init();

	// daSearch
	//DaIndex = new Darts::DoubleArray();
	string index_file =  DA_IndexFile_DLG;
	_INFO("daSearch file : %s", index_file.c_str());
	//if(daSearch->Init(index_file.c_str(),DaIndex) == -1)
	daSearch = new DA_SEARCH();
	if(daSearch->Init(index_file.c_str()) == -1)
	{
		return -1;
	}

	return 0;
}

int MUSIC::Release() 
{
	seg->Release();
	daSearch->Release();
	if(daSearch != NULL)
	{
		delete daSearch;
		daSearch = NULL;
	}
}
int MUSIC::Normalize_(const char* query)
{
	;
}

int MUSIC::IndexOutcome(const char* query)//, ofstream& FILE_TEACHER)
{
	string query_(query);
//		char dest[4096];
//		memset(dest,0x00,4096);
//		EncodingConvertor::getInstance()->dbc2gchar(
//				query,
//				(gchar_t*)dest,
//				4096/2,
//				true);
//	
	cerr << "============================ BEGINE ==================================" << endl;
	_INFO("QUERY:%s", query);
	map<string, string> anwser_hash;
	map<string, string>::iterator iter_;
	vector<string> propertyVec;
	vector<string> tmp;
	daSearch->GetIndexResults(query_, anwser_hash, tmp, seg);
	_INFO("Size of daSearch : %d", anwser_hash.size());
	for(iter_ = anwser_hash.begin(); iter_ != anwser_hash.end(); iter_++)
	{
		//cerr << "| ANWSER:" << iter_->second << endl;
		propertyVec.clear();
		spaceGary::StringSplit(iter_->second, tmp, "|||");
		_INFO("Size of out : %d", tmp.size());
		for(int i = 0; i < tmp.size(); i++)
		{
			spaceGary::StringSplit(tmp[i], propertyVec, "\t");
			for(int i = 0; i < propertyVec.size(); i++)
			{
				//_INFO("%s", propertyVec[i].c_str());
				cerr << "[INFO] " << propertyVec[i].c_str() << endl;
			}
		}
	}
	cerr << "============================ END ==================================" << endl;
	return 0;
}

