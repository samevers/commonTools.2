#ifndef __ISPORN_HEAD__
#define __ISPORN_HEAD__


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

class textCategorization{
private:

	std::map<std::string, double> hash_y_prob;
	std::vector<std::map<std::pair<std::string, std::string>, double > > hash_model;
	std::map<std::string,long int> hash_term_num;
	std::map<std::string,long int> hash_gram_num;
	std::map<std::string,int> hash_stop;
public:
	std::map<std::string,long int> hash_fea;
	int loadStop(std::string filename);
	int init();
	int LoadModels();
	int load_wordDist_model(std::string modelfile);//, std::map<std::string, double>& hash_y_prob, std::map<pair<std::string, std::string>, double >& hash_model);
	double predict_wordDist(std::string query, std::vector<std::string>& termList);
	inline void release(){
	}
	
};


#endif
