#include "VerticalDOC.h"
#include "EditDist.h"
#include <stdlib.h>
using namespace std;



const static string FILE_PUNC = "punc/punc.txt";
const static int threshold = 50;			// data[i].length()/query.length()，太大的话，表示查找失败；
static queue<string> context;				// 保存上下文
static map<string, int> hash_context;		// 保存上下文

//
VERTICAL_DOC::VERTICAL_DOC()
{
	EncodingConvertor::initializeInstance();
	analysis::DicTree::instance()->loadDic();
}
VERTICAL_DOC::~VERTICAL_DOC()
{
	Release();
}
int VERTICAL_DOC::loadDic(const char* dir_base)
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
//int VERTICAL_DOC::Init(const char* dir_base, string& DOC_IndexFile_DLG,Darts::DoubleArray* DaIndex) // data directory
int VERTICAL_DOC::Init(const char* dir_base, const string& DOC_IndexFile_DLG) // data directory
{
	// Load dicts	
	if(loadDic(dir_base) == -1)
	{
		return -1;
	}
	seg = SEGMENT_1::getInstance();
	seg->Init();

	// docSearch
	string index_file =  DOC_IndexFile_DLG;
	_INFO("docSearch file : %s", index_file.c_str());
	docSearch = new DOC_SEARCH();
	if(docSearch->Init(index_file.c_str()) == -1)
	{
		return -1;
	}

	return 0;
}

int VERTICAL_DOC::Release() 
{
	seg->Release();
	docSearch->Release();
	if(docSearch != NULL)
	{
		delete docSearch;
		docSearch = NULL;
	}
}
int VERTICAL_DOC::Normalize_(const char* query)
{
	;
}

int VERTICAL_DOC::IndexOutcome(const char* query)//, ofstream& FILE_TEACHER)
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
	vector<string> data;
	DlgResult doc_result;
	docSearch->GetIndexResults(query_, doc_result, seg);
	data = doc_result.data;
	
	EditDist ed;
	vector<int> sortED;
	map<int, string> cadidate_sort;
	sortED.clear();
	cadidate_sort.clear();
	vector<string> tmp;
	tmp = data;
	ed.EditSort(query,tmp,cadidate_sort, sortED, seg);
	// show results
	string anwser;
	show_results(query_.length(), cadidate_sort, anwser);
	cadidate_sort.clear();
	sortED.clear();

	cerr << "============================ END ==================================" << endl;
	return 0;
}
int VERTICAL_DOC::show_results(size_t query_length, map<int, string>& da_vec, string& anwser)
{
	map<int, string>::iterator iter;
	vector<string> values;
	string singer, song, album;
	map<string, string> anwser_hash;
	map<string, string>::iterator iter_;
	vector<string> tmp;
	vector<string> anwser_vec;
	int32_t nearest_dis = 10000;
	int32_t dis;
	for(iter = da_vec.begin(); iter != da_vec.end(); iter++)
	{
		anwser_vec.clear();
		anwser_hash.clear();
		cerr << "out: " << iter->first << "\t" << iter->second << endl;
		if(iter->first > 5)
		{
			cerr << "[NOTE] Cannot find the shortest and most similar QUESTION!" << endl;
			break;
		}
		anwser = iter->second;
		spaceGary::StringSplit(anwser,anwser_vec, "###");
		if(anwser.length() < 1)
		{
			cerr << "[NOTE] length of anwser is too short!" << endl;
			return 0;
		}
		for(int i = 0; i < anwser_vec.size(); i++)
		{
			if((dis = anwser_vec[i].length() < query_length ? 
						query_length - anwser_vec[i].length(): anwser_vec[i].length() - query_length) < nearest_dis)
			{
				anwser = anwser_vec[i];
				_INFO("Nearest cadidate : %s", anwser.c_str());
				nearest_dis = dis;
			}
		}
		cerr << "----------------------------------------------------------------------------------------------------------------------------" << endl;
		break;
	}
	return 0;
}

