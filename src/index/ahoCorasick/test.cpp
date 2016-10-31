#include "AhoCorasick.h"
#include "../../include/gary_common/gary_common.h"
#include "../../include/gary_common/gary_string.h"
#include "../../include/service_log.hpp"
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_NOVEL_AUTHOR = 1000000;
const static int MAXSTRLEN = 1024;

char* authorKeys[MAX_NOVEL_AUTHOR];
int authorLens[MAX_NOVEL_AUTHOR];
int authorKeyCount;
map<string,double> novel_author;

//static const string Punctuations = "　～·！＠＃￥％……＆×（）－—＋＝【】｛｝｜＼、；：‘’“”《》，。？、／╚╗＄＾＊＿［］．””’
//static const string Punctuations = "　～·！＠＃￥％……＆×（）－—＋＝【】｛｝｜＼、；：‘’“”《》，。？、／╚╗＄＾＊＿［］．";
//static const string Punctuations  = "~·！@#￥%&*（）——+=-{}【】；’：“《》，。？、";
static const string Punctuations = "";
set<unsigned short>  punctuations;

int loadPunctuations()
{
	unsigned short* ps = (unsigned short*) Punctuations.c_str();
	for (unsigned i = 0; i < Punctuations.length()/2; ++i, ++ps) {
		punctuations.insert(*ps);
	}
	return 0;
}
void TrimPunctuation(string& src, string& dst)
{
	char dest[MAXSTRLEN];
	if(src.length() >= MAXSTRLEN) return;
	unsigned short * p   = (unsigned short *) src.c_str();
	unsigned short * pd   = (unsigned short *) dest;
	for (size_t i = 0; i < src.length()/2; ++p, ++i)
	{
		if (punctuations.find(*p) == punctuations.end())
		{
			*pd++ = *p;
		}
	}
	*pd = 0;
	dst = dest;
}

bool loadScoreMap(std::string &infile, std::map<std::string, double>& scoreMap) {
	ifstream fin(infile.c_str());
	if (!fin) {
		std::cerr << "can't open file: " << infile << std::endl;
		return false;
	}

	std::string line;
	string keyword;
	while (getline(fin, line)) {
		if (line.size() < 1) continue;
		std::string::size_type pos = line.find("\t");
		double score;
		if (pos == std::string::npos)
		{
			keyword = line;
			score = 0;
		}
		else
		{
			keyword = line.substr(0, pos);
			score = atof(line.substr(pos + 1).c_str());
		}

		//char dest[MAXSTRLEN];
		//int glen = ec->t2sgchar(keyword.c_str(), (gchar_t*)dest, MAXSTRLEN / 2, true);
		//if (glen >= MAXSTRLEN / 2) continue;
		//dest[glen * 2] = '\0';
		//keyword = dest;

		//ximin 2014/9/2
		std::string strkeyword;
		TrimPunctuation(keyword, strkeyword);
		std::map<std::string, double>::iterator it = scoreMap.find(strkeyword);
		if(it != scoreMap.end()){
			if(it->second < score){
				scoreMap[strkeyword] = score;
			}
		}
		else{
			scoreMap.insert(make_pair<std::string, double>(strkeyword,score));
		}
	}
	fin.close();
	return true;
}
//模式串排序函数，second - first 最长的在最前，否则，first 相同最长的在前，否则first 小的在前
bool sortFunc(const std::pair<unsigned, int>& iter1, const std::pair<unsigned, int>& iter2) {
	if (iter1.second - iter1.first > iter2.second - iter2.first) return true;
	if (iter1.second - iter1.first < iter2.second - iter2.first) return false;
	//长度相等，看更靠前
	if (iter1.first < iter2.first) return true;
	return false;
}

int main(int argc, char ** argv)
{
	string filename = argv[1];
	if(argc < 2)
	{
		_ERROR("Please input a filename!\n");
		return -1;
	}

	loadPunctuations();
	loadScoreMap(filename, novel_author);
	authorKeyCount = 0;
	for (std::map<std::string, double>::iterator it = novel_author.begin(); it != novel_author.end(); ++it) {
		std::string author = it->first;
		authorKeys[authorKeyCount] = new char[author.size() + 1];
		strcpy(authorKeys[authorKeyCount], author.c_str());
		authorKeys[authorKeyCount][author.size()] = '\0';
		authorLens[authorKeyCount] = author.size();
		++authorKeyCount;
	}
	AhoCorasick authorAho;
	_INFO("Begin to make authorAho.initialize()\n");
	authorAho.initialize(authorKeyCount, authorLens, (const char**)authorKeys);
	_INFO("Over making authorAho.initialize()\n");
	// test
	ifstream infile;
	if(spaceGary::open_f(filename, infile) == -1)
	{
		_ERROR("Fail to open filename %s\n", filename.c_str());
		return -1;
	}

	string line;
	while(getline(infile,line))
	{
		std::vector<std::pair<unsigned, int> > wordIndex;
		authorAho.search(line.c_str(), line.size(), wordIndex);
		std::vector<std::pair<int, int> > posIndex; 
		for (std::vector<std::pair<unsigned, int> >::iterator it = wordIndex.begin(); it != wordIndex.end(); ++it) {
			int end = it->second;
			if (end % 2 != 0) continue;	// 模式串与搜索串均为全角，下标必须是偶数。
			int beg = end - authorLens[it->first];
			//if (!(beg == 0 || end == gQuery.size())) continue; // 保险起见，此时作者名位于头或尾
			//if ((end - beg) < 4) continue; 	// 作者名长度至少为4
			posIndex.push_back(std::make_pair(beg, end));
		}
		sort(posIndex.begin(), posIndex.end(), sortFunc);
		string author;
		if (posIndex.size() < 1) {
			author = "";
			cerr << "[debug_sam] Cannot find an author" << endl;
			return 0;
		} else { //作者只取一个
			int beg = posIndex[0].first;
			int end = posIndex[0].second;
			if (beg >= 0 && end >= beg) {
				author = line.substr(beg, end - beg);
				cerr << "[debug_sam] author = " << author << endl;
			}
			std::map<std::string, double>::iterator it = novel_author.find(author);
			if (author.size() == 0 || it == novel_author.end()) {
				fprintf(stderr, "find author error [%s] %d %d\n", author.c_str(), beg, end);
				author = "";
				cerr << "[debug_sam] Cannot find an author" << endl;
				return 0;
			} 
		}
	}
	infile.close();

	return 0;
}
