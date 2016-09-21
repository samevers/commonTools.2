/*************************************************************************
    > File Name: general_pro.cpp
    > Author: Yonghua HU.
    > Mail: yonghuahu@outlook.com 
    > Created Time: Mon 31 Mar 2014 03:12:34 AM PDT
 ************************************************************************/

#include "general.h"


namespace general_{

// dict
map<string, string> hash_trad_simp;
//string tran2simpfile = "data/simp2tran/simp2trad.txt";

// init
int init_()
{
	if(load_() == -1)
	{
		cerr << "ERROR : frame loading operation is error !" << endl;
		return -1;
	}
}
// release
int release_()
{
	hash_trad_simp.clear();
}

// load resources
int load_()
{
	// tran2simp dict
	/*
	 * ifstream simp2tran_file;
	simp2tran_file.open(tran2simpfile.c_str(), ios::in);
	if(!simp2tran_file)
	{
		cerr << "ERROR : fail to open tran2simp file !" << endl;
		return -1;
	}
	string line;
	vector<string> vec;
	while(getline(simp2tran_file, line))
	{
		if(split_vec(line, ":", vec) == -1)
			continue;
		for(unsigned int i = 1; i < vec.size(); i++)
		{
			if(vec[i].length() > 0 && vec[i] != " ")
				hash_trad_simp[vec[i]] = vec[0]; // hash[tran] = simp;
		}
		vec.clear();
	}
	simp2tran_file.close();
*/	
	return 0;
}
// split
int split_vec (string line, string blank, vector<string>& vec)
{
	if(line.length() < 1)
	{
		return -1;
	}
	int start = 0;
	int end;
	int loc;
	string sub;

	while((end = line.find(blank.c_str(), start)) != -1)
	{
		sub = line.substr(start, end - start);
		if(sub.length() < 1 || sub == blank)
		{
			;
		}else
		{
			vec.push_back(sub.c_str());
		}
		start = end + blank.length();
		if(start >= line.length())
			break;
	}

	if(start < line.length())
	{
		sub = line.substr(start, line.length() - start);
		if(sub.length() > 0)
		{
			vec.push_back(sub.c_str());
		}
	}

	return 0;
}

int split_vec(string line, string blank)
{
	int loc1 =0;
	int loc2 = loc1;
	int num = 0;
	while((loc2 = line.find(blank.c_str(),loc1)) != -1)
	{
		num++;
		loc2 += blank.length();
		loc1 = loc2;
	}

	return num;
}

// 
int split_hash (string line, string blank, map<string, int>& hash_)
{
	if(line.length() < 1)
	{
		return -1;
	}
	int start = 0;
	int end;
	int loc;
	string sub;

	while((end = line.find(blank.c_str(), start)) != -1)
	{
		sub = line.substr(start, end - start);
		if(sub.length() < 1 || sub == blank)
		{
			;
		}else
		{
			hash_[sub.c_str()]++;
		}
		start = end + blank.length();
		if(start >= line.length())
			break;
	}

	if(start < line.length())
	{
		sub = line.substr(start, line.length() - start);
		if(sub.length() > 0)
		{
			hash_[sub.c_str()]++;
		}
	}

	return 0;
}
int split_hash (string line, string blank, map<string, int>& hash_, string& label)
{
	if(line.length() < 1)
	{
		return -1;
	}
	int start = 0;
	int end;
	int loc;
	string sub;
	bool label_ = 0;
	while((end = line.find(blank.c_str(), start)) != -1)
	{
		sub = line.substr(start, end - start);
		if(sub.length() < 1 || sub == blank)
		{
			;
		}else
		{
			if(label_ == 0)
			{
				label = sub;
				label_ = 1;
			}
			hash_[sub.c_str()]++;
		}
		start = end + blank.length();
		if(start >= line.length())
			break;
	}

	if(start < line.length())
	{
		sub = line.substr(start, line.length() - start);
		if(sub.length() > 0)
		{
			hash_[sub.c_str()]++;
		}
	}
	
	if(label_ == 0)
	{
		label = line;
		label_ = 1;
	}

	return 0;
}


int split_ (string line, string blank, map<string, int>& hash_, vector<string>& vec)
{
	if(line.length() < 1)
	{
		return -1;
	}
	int start = 0;
	int end;
	int loc;
	string sub;

	while((end = line.find(blank.c_str(), start)) != -1)
	{
		sub = line.substr(start, end - start);
		if(sub.length() < 1 || sub == blank)
		{
			;
		}else
		{
			hash_[sub.c_str()]++;
			vec.push_back(sub.c_str());
		}
		start = end + blank.length();
		if(start >= line.length())
			break;
	}

	if(start < line.length())
	{
		sub = line.substr(start, line.length() - start);
		if(sub.length() > 0)
		{
			hash_[sub.c_str()]++;
			vec.push_back(sub.c_str());
		}
	}

	return 0;
}

// split Chinese&English string
// the function has much to do with encoding. utf8:3, gbk:2
// ascii code of blank is 32
int split2singleWord_(const string text,vector<string>& singleWord)
{
	if(text.length() == 0)
		return -1;
	string str = text;
	string str_result = "";//用于存储结果字符串
	int i = 0;
	int len = 0;
	while(str.length())
	{
		i = 0;
		len = str.length();//取字符串的长度
		unsigned char ch=(unsigned char)str[0];//取字符串的第一个词
		// blank
		if((int)ch == 32)
		{
			i++;
			if(len <= i)
				break;
			str = str.substr(i,len - i);
			continue;
		}

		if(str[0] > 0 && (unsigned char)str[i] < 128)
		{//如果字符串的第一个单词为西文字符，则处理西文字符
			//如果i小于str的长度且str[i]为西文字符且str[i]不为回车且str[i]不为换行
			if(str[i] == 10 || str[i] == 13)
			{
				i++;
			}else
				while((i < len) && ((unsigned char)str[i] < 128) && (str[i] != 10) && (str[i]!=13) )
				{
					i++;
				}
				str_result =str.substr(0,i);
				singleWord.push_back(str_result);
				if(len <= i)
					break;
				str=str.substr(i,len - i);
				continue;
		}else if(ch < 176)//处理中文非汉字字符
		{
			str_result =str.substr(i,3);
			singleWord.push_back(str_result);
			i += 3;
			if(len <= i)
				break;
			str=str.substr(i,len - i);
			continue;				
		}else
		{
			// 处理纯汉字串
			len = (int)str.length();
			str_result = str.substr(i,3);
			singleWord.push_back(str_result);
			i += 3;
			if(len <= i)
				break;
			str = str.substr(i,len - i);
		}
	}
	return 0;
}

/************************************************/
// whether s is a int value						*/
/************************************************/
bool _is_int(string s)
{
	for(int i = 0; i < s.length(); i++)
	{
		if(strcmp(s.substr(i,1).c_str(),"0") >= 0 && strcmp(s.substr(i,1).c_str(),"9") <= 0)
			;
		else
		{
			cerr << "warning: Sorry, your input file is illegal in format....." << endl;
			return 0;
		}
	}
	return 1;
}

/****************************************/
/*	Open a input file					*/
/****************************************/
int open_f(string filename, ifstream& infile)
{
	if(filename.length() == 0)
	{
		cerr << "ERROR: input file name is NULL....... FALSE !" << endl;
		return -1;
	}

	infile.open(filename.c_str(), ios::in);
	if(!infile)
	{
		cerr << "ERROR: fail to open input file, please check the file is real !" << endl;
		return -1;
	}

	return 0;
}

/****************************************/
/*	Build a new file					*/
/****************************************/
int Build_f(string filename, ofstream& outfile)
{
	if(filename.length() == 0)
	{
		cerr << "ERROR: output file name is NUL !" << endl;
		return -1;
	}

	outfile.open(filename.c_str(), ios::out);
	if(!outfile)
	{
		cerr << "ERROR: fail to build output file, please check !" << endl;
		return -1;
	}

	return 0;
}
// tran2simp for chinese
int tran2simp_(string input, string& output)
{
	;
}

// simp2tran for chinese
int simp2tran_(string input, string& output)
{
	;
}

/*typedef pair<string,double> P_;
int comp_double(const P_& x, const P_& y)
{
	return x.second > y.second;
}
typedef pair<string,int> P_;
int comp_int(const P_& x, const P_& y)
{
	return x.second > y.second;
}
*/

}
