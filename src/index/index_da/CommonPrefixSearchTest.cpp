#include "CommonPrefixSearch.h"
#include "../../include/service_log.hpp"
#include <iostream>
using namespace std;

int main(int argc, char** argv)
{
	CommonPrefixSearch cs;
	string filename = "containSearch.txt";
	cs.MakeIndex(filename.c_str());

	if(argc < 2)
	{
		_ERROR("PLEASE INPUT A QUERY.");
		return -1;
	}
	string query = argv[1];
	string hit;
	string value;
	cs.ExactSearch(query,hit,value);
	_INFO("---->hit: %s\n", hit.c_str());
	_INFO("---->value: %s\n", value.c_str());

	cerr << "----------------------------------------------------------------"<< endl;

	int32_t max_hit_num = 10;
	
	cs.GetCommonPrefixSearch(query, hit, value ,max_hit_num);
	_INFO("===>hit: %s\n", hit.c_str());
	_INFO("===>value: %s\n", value.c_str());
	cerr << "----------------------------------------------------------------"<< endl;

	vector<string> hit_string_vect;
	vector<string> hit_value_vect;
	cs.GetCommonPrefixSearch(query, hit_string_vect, hit_value_vect,max_hit_num);
	_INFO("hit_string_vect ....");
	for(int i = 0; i < hit_string_vect.size(); i++)
	{
		_INFO("+++++>%s\n", hit_string_vect[i].c_str());
	}
	_INFO("hit_value_vect ....");
	for(int i = 0; i < hit_value_vect.size(); i++)
	{
		_INFO("++++>%s\n", hit_value_vect[i].c_str());
	}
	cerr << "----------------------------------------------------------------"<< endl;


	return 0;
}
