/*************************************************************************
    > File Name: frame.h
    > Author: Yonghua HU.
    > Mail: yonghuahu@outlook.com 
    > Created Time: Mon 31 Mar 2014 03:10:42 AM PDT
 ************************************************************************/
#ifndef __GENERAL_HEAD_H_
#define __GENERAL_HEAD_H_

#include "common.h"

namespace general_{

// init
int init_();
// release
int release_();
// load resources
int load_();


// split
int split_vec(string line, string blank, vector<string>& vec);
int split_vec(string line, string blank);
int split_hash(string line, string blank, map<string, int>& hash_);
int split_hash (string line, string blank, map<string, int>& hash_, string& label);
int split_ (string line, string blank, map<string, int>& hash_, vector<string>& vec);

// tran2simp for chinese.
int tran2simp_(string input, string& output);
int simp2tran_(string input, string& output);

inline int min_(int a, int b)
{
	return (a <= b ? a : b);
}
inline int max_(int a, int b)
{
	return (a > b ? a : b);
}
inline double max_double(double a, double b)
{
	return (a > b ? a : b);
}
// judge a string is a int type of not.
bool _is_int(string s);

// open a input file
int open_f(string filename, ifstream& infile);
// build a new file
int Build_f(string filename, ofstream& outfile);
// split chinese sentence into single words
int split2singleWord_(const string text,vector<string>& singleWord);



/********************************
 * template functions.
 ********************************/

template <class T>
inline T _min_(T a, T b)
{
	return (a <= b ? a : b);
}

template <class T>
inline T _max_(T a, T b)
{
	return (a > b ? a:b);
}

// convert <string> type to <class T> type
template <class T>
inline void string_to_(string src, T& dest){
	stringstream stream;
	stream << src;
	stream >> dest;
}

template <class T>
inline void string_to_int(string src, T& dest){
	stringstream stream;
	stream << src;
	stream >> dest;
}

// calculate the distance between two points in various dimension
template <class T>
int distance_(vector<T> vec1, vector<T> vec2, T& distance)
{
	if(vec1.size() < vec2.size() || vec1.size() > vec2.size())
	{
		cerr << "ERROR : dimension of the two points is different !" << endl;
		return -1;
	}
	int size = vec1.size();
	T sum_ = 0.0;
	for(unsigned int i = 0; i < size; i++)
	{
		sum_ += pow(vec1[i] - vec2[i], 2);
	}
	distance = sqrt(sum_);
	return 0;
}
/*
int comp_double(const pair<int,double>& x, const pair<int,double>& y)
{
	return x.second > y.second;
}
int comp_int(const pair<int,int>& x, const pair<int,int>& y)
{
	return x.second > y.second;
}
*/

}

#endif
