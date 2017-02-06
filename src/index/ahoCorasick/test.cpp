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
//vector<string> authorKeysVec;
int authorLens[MAX_NOVEL_AUTHOR];
int32_t authorKeyCount;
map<string,double> novel_author;

static const string Punctuations = "�����������������������������������������������ܡ����������������������������^�[��ޣ��ߣۣݣ�";
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
//ģʽ����������second - first �������ǰ������first ��ͬ�����ǰ������first С����ǰ
bool sortFunc(const std::pair<unsigned, int>& iter1, const std::pair<unsigned, int>& iter2) {
	if (iter1.second - iter1.first > iter2.second - iter2.first) return true;
	if (iter1.second - iter1.first < iter2.second - iter2.first) return false;
	//������ȣ�������ǰ
	if (iter1.first < iter2.first) return true;
	return false;
}

int main(int argc, char ** argv)
{
	if(argc < 2)
	{
		_ERROR("Please input a filename!\n");
		return -1;
	}
	string filename = argv[1];

	loadPunctuations();
	loadScoreMap(filename, novel_author);
	authorKeyCount = 0;
	int32_t num = 0;
	for (std::map<std::string, double>::iterator it = novel_author.begin(); it != novel_author.end(); ++it) {
		std::string author = it->first;
		//if(authorKeyCount > MAX_NOVEL_AUTHOR)
		//	authorKeys = (char*)realloc(authorKeys, authorKeyCount*sizeof(char*));
		authorKeys[authorKeyCount] = new char[author.size() + 1];
		strcpy(authorKeys[authorKeyCount], author.c_str());
		authorKeys[authorKeyCount][author.size()] = '\0';
		authorLens[authorKeyCount] = author.size();
		authorKeyCount++;
		num++;
	}
	_INFO("Size of novel_author map = %d", novel_author.size());
	_INFO("num = %d", num);
	_INFO("Size of authorKeys = %d", authorKeyCount);
	authorKeyCount = num;

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
	string strkeyword;
	std::vector<std::pair<unsigned, int> > wordIndex;
	std::vector<std::pair<int, int> > posIndex; 
	//while(getline(infile,line))
	while(getline(cin,line))
	{
		_INFO("line= %s", line.c_str());
		TrimPunctuation(line, strkeyword);
		line = strkeyword;
		_INFO("post line= %s", line.c_str());
		if(line.length() < 2)
			continue;
		wordIndex.clear();
		authorAho.search(line.c_str(), line.size(), wordIndex);
		posIndex.clear();
		for (std::vector<std::pair<unsigned, int> >::iterator it = wordIndex.begin(); it != wordIndex.end(); ++it) {
			int end = it->second;
			if (end % 2 != 0) continue;	// ģʽ������������Ϊȫ�ǣ��±������ż����
			int beg = end - authorLens[it->first];
			//if (!(beg == 0 || end == gQuery.size())) continue; // �����������ʱ������λ��ͷ��β
			//if ((end - beg) < 4) continue; 	// ��������������Ϊ4
			posIndex.push_back(std::make_pair(beg, end));
		}
		sort(posIndex.begin(), posIndex.end(), sortFunc);
		string author;
		if (posIndex.size() < 1) {
			author = "";
			cerr << "[debug_sam] 1 Cannot find an author:" << line << endl;
			continue;
		} else { //����һ���������ɸ����ߵ�query���ҳ�����������������ߡ�
			for(int i = 0; i < posIndex.size(); i++)
			{
				int beg = posIndex[i].first;
				int end = posIndex[i].second;
				if (beg >= 0 && end >= beg) {
					author = line.substr(beg, end - beg);
					cerr << "[debug_sam] author = " << author << endl;
				}
				std::map<std::string, double>::iterator it = novel_author.find(author);
				if (author.size() == 0 || it == novel_author.end()) {
					fprintf(stderr, "find author error [%s] %d %d\n", author.c_str(), beg, end);
					author = "";
					continue;
				} 

			}
//			int beg = posIndex[0].first;
//			int end = posIndex[0].second;
//			if (beg >= 0 && end >= beg) {
//				author = line.substr(beg, end - beg);
//				cerr << "[debug_sam] author = " << author << endl;
//			}
//			std::map<std::string, double>::iterator it = novel_author.find(author);
//			if (author.size() == 0 || it == novel_author.end()) {
//				fprintf(stderr, "find author error [%s] %d %d\n", author.c_str(), beg, end);
//				author = "";
//				continue;
//			} 
		}
	}
	infile.close();

	return 0;
}
