/*******************************************************

* 文件名： gary_string.h
* 功  能： 针对string的封装
* 版  本： version 1.0 2010-3-31
* 修  改：

********************************************************/

#ifndef __GARY_STRING_H_
#define __GARY_STRING_H_

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <sstream>
#include <dirent.h>
using namespace std;

namespace spaceGary
{

//split
inline
bool StringSplit(std::string strItem, std::vector<std::string> &vectRes, const char* splitWord) {
    vectRes.clear();

	std::string::size_type posOnePart, posFindBegin = 0;
	unsigned int nSplitWordLen = strlen(splitWord);
	posOnePart = strItem.find(splitWord);
	
	while (std::string::npos != posOnePart) {
		
		//不能将splitword， 加入到结果中
		if (posOnePart != posFindBegin) {
			vectRes.push_back(strItem.substr(posFindBegin, posOnePart-posFindBegin));
		}
		posFindBegin = posOnePart + nSplitWordLen;
		posOnePart = strItem.find(splitWord, posFindBegin);
	}

	//防止后面出现splitword的情况
	if (posFindBegin < strItem.length()) {
		vectRes.push_back(strItem.substr(posFindBegin));
	}
    
	return true;
};

//seg split
inline
bool SegSplit(std::string strItem, std::vector<std::string> &vectRes, const char* splitWord) {
   
	vectRes.clear();

	std::string::size_type posOnePart, posFindBegin = 0;
	unsigned int nSplitWordLen = strlen(splitWord);
	posOnePart = strItem.find(splitWord);
	bool is_pre_seg = false;

	while (std::string::npos != posOnePart) {
		
		//处理分隔符和原词一致， 并联系出现的情况
		if  (posOnePart == posFindBegin) {
			if (is_pre_seg) {
				vectRes.push_back(splitWord);
			}
			is_pre_seg = true;
		}
		else {
			vectRes.push_back(strItem.substr(posFindBegin, posOnePart-posFindBegin));
			is_pre_seg = false;
		}

		posFindBegin = posOnePart + nSplitWordLen;
		posOnePart = strItem.find(splitWord, posFindBegin);
	}

	//防止后面出现splitword的情况
	if (posFindBegin < strItem.length()) {
		vectRes.push_back(strItem.substr(posFindBegin));
	}
    
	return true;
};

// gbk 编码
// 字符串反转
int reverse_gbk(const string& src, string& dst) {
	dst = "";
	dst.resize(src.length());
	if (dst.length() != src.length() || dst.length()&1) {
		dst = "";
		return -1;
	}
	unsigned short* psrc = (unsigned short*)src.c_str();
	unsigned short* pdst = (unsigned short*)&dst[src.length()-2];
	for (size_t i = dst.length()>>1; i; --i) {
		*pdst-- = *psrc++;
	}
	return 0;
}

int gbkChSub(const std::string& src, std::string& dst, std::map<std::string, std::string>& chMap) {  //双字节字符替换
	if (src.size() % 2 != 0) return -1;  //非双字节
	dst = "";
	for (std::string::size_type i = 0; i < src.size(); i += 2) {
		std::map<std::string, std::string>::iterator it = chMap.find(src.substr(i, 2));
		if (it == chMap.end()) {
			dst += src.substr(i, 2);
		} else {
			dst += it->second;
		}
	}
	return 0;
}

//去除头尾全半角空格
bool trim(string& query) {
    while (query.size() > 0) {
	    if (query.size() >= 2 && query.substr(0, 2) == "　") {
			query.erase(0, 2);
	    } 
	    else if (query.size() >= 1 && query.substr(0, 1) == " ") {
			query.erase(0, 1);
	    }
	    else if (query.size() >= 2 && query.substr(query.size() - 2, 2) == "　") {
			query.erase(query.size() - 2, 2);
	    }
	    else if (query.size() >= 1 && query.substr(query.size() - 1, 1) == " ") {
			query.erase(query.size() - 1, 1);
	    }
	    else {
			break;
	    }
    }
    return true;
}

//trim
inline
bool StringTrim(std::string &strItem) {

 
	const char *pItem = strItem.c_str();
	unsigned int nItemLen = strItem.length();
    if (0 ==  nItemLen) {
		return true;
	}
	int left = 0;
	while (pItem[left] == ' ' || pItem[left] == '\t' || pItem[left] == '\r' || pItem[left] == '\n') {
		left++;
	}

	int right = nItemLen-1;
	while (right >=0 && (pItem[right] == ' ' || pItem[right] == '\t' || pItem[right] == '\r' || pItem[right] == '\n')) {
		right--;
	}

	if (left > right) {
		strItem = "";
	}
	else {
		strItem = strItem.substr(left, right-left+1);
	}

	return true;
}

inline
int GetWordNum(const char *src) {

	int num = 0;

	const char *p = src;
	while (*p) {
		if (*p == ' ') {
			p++;
		}
		while (*p) {
			if (*p < 0) {
				if (*(p + 1) == '\0') {
					return num + 1;
				}
				p += 2;
			}
			else if (*p == ' ') {
				p++;
				num++;
				break;
			}
			else {
				p++;
			}
		}
	}

	return num + 1;
}

inline 
const char* GetTheWord(char *src) {
	
	char *p = src;
	if (*p == ' ') {
		p++;
	}
	while (*p && *p != ' ') {
		if (*p < 0) {
			p += 2;
		}
		else {
			p++;
		}
	}

	*p = 0;

	return src;

}

inline
const char *GetEngWord(const char *query, int &len_eng, int &num_eng_word) {

	int cur_num_eng_word = 0;
	int cur_len_eng = 0;
	len_eng = 0;

	const char *p = query;
	while (*p) {
		if (*p == ' ') {
			
			len_eng = cur_len_eng;
			cur_len_eng++;
			p++;
			cur_num_eng_word++;
			if (cur_num_eng_word >= num_eng_word) {
				break;
			}
			
		}
		else if (*p >= 'a' && *p <= 'z') {
			cur_len_eng++;
			p++;
		}
		else {
			break;
		}
	}

	num_eng_word = cur_num_eng_word;
	if (0 == len_eng) {
		return NULL;
	}

	return query;
	
}
inline
int deleteSpace(std::string& line)
{
	if(line.length() < 1)
		return 0;

	int loc;
	while((loc = line.find(" ")) != -1)
	{
		line.replace(loc,1,"");
	}
	return 0;
}
inline
int deleteStr(std::string& line, const char* str)
{
	if(line.length() < 1)
		return 0;

	int loc;
	while((loc = line.find(str)) != -1)
	{
		line.replace(loc,strlen(str),"");
	}
	return 0;
}
//
inline
std::string toString(int32_t& num)
{
		std::stringstream os;
		os << num;
		std::string out;
		os >> out;

		return out;
}
inline
std::string double2String(double& num)
{
	std::stringstream os;
		os << num;
		std::string out;
		os >> out;

		return out;
}

//
inline
double toDouble(std::string& str)
{
	std::stringstream os;
		os << str;
		double out;
		os >> out;

		return out;
}
//
inline
int toInt(std::string& str)
{
	std::stringstream os;
		os << str;
		int out;
		os >> out;

		return out;
}
inline
int all_substr(std::vector<std::string> segment, std::vector<std::string>& all_sub)
{
	std::string sub;
	if(segment.size() < 1)
		return 0;
	int size = segment.size();
	int K;
	for(int i = 0; i < size; i++)
	{
		sub = "";
		K = (size <= (i + 5) ? size:(i + 5));
		for(int j = i; j < K; j++)
		{
			sub += segment[j];
			all_sub.push_back(sub);
		}
	}
	return 0;
}

inline
int all_substr(std::vector<std::string> segment, std::map<std::string, int32_t>& all_sub)
{
	std::string sub;
	if(segment.size() < 1)
		return 0;
	int size = segment.size();
	int K;
	for(int i = 0; i < size; i++)
	{
		sub = "";
		if(segment[i].length() == 0)
			continue;
		K = (size <= (i + 5) ? size:(i + 5));
		for(int j = i; j < K; j++)
		{
			if(segment[j] == "")
				continue;
			else
				sub += segment[j];
			if(sub.length() > 10)
				break;
			all_sub[sub] += 1;
		}
	}
	return 0;
}

inline
int all_suffix(std::vector<std::string> segment, std::vector<std::string>& all_suffix)
{
	all_suffix.clear();
	std::string sub;
	if(segment.size() < 1)
		return 0;
	int size = segment.size();
	int begin;
	if(size > 10)
	{
		begin = size - 10;
	}else
	{
		begin = 0;
	}
	for(int i = begin; i < size; i++)
	{
		sub = segment[i];
		for(int j = i + 1; j < size; j++)
		{
			sub += segment[j];
		}
		all_suffix.push_back(sub);
	}
	return 0;
}

// Read a directory and files within.
inline
int readFiles(std::string dirname, std::vector<std::string>& filenames)
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
			std::string filename = dirname + "/" + ent->d_name;
			filenames.push_back(filename);
		}
	}
	return 0;
}


};


#endif


