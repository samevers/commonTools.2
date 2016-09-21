#ifndef __NAIVE_BAYES_
#define __NAIVE_BAYES_

#include "general.h"
#include <string>

//using namespace general_;

using namespace std;

namespace naive_bayes_{
int InitRexPattern();
int allIsPuncCharactor(const char* query);
int allIsEngCharactor(const char* query);
int allIsNumCharactor(const char* query);


class word_gram{
private:

	int trainfile_statistic_word(ifstream& infile, map<string,long int>& hash_y_num, long int &total_y_num, map<pair<string,string>, long int>& hash_term_y_num,map<pair<string,string>, long int>& hash_gram_y_num,map<string,long int>& hash_termnum_of_y, map<string, long int>& hash_gramnum_of_y);
	map<string, double> hash_y_prob;
	map<pair<string, string>, double > hash_model;
	map<string,long int> hash_term_num;
	map<string,long int> hash_gram_num;
	map<string,int> hash_stop;
public:
	map<string,long int> hash_fea;
	int loadStop(std::string filename);
	int init();
	int train_word_gram(string train_file);
	int load_wordDist_model(string modelfile);//, map<string, double>& hash_y_prob, map<pair<string, string>, double >& hash_model);
	int predict_wordDist(string testfile, string modelfile);
	inline void release(){
		hash_y_prob.clear();
		hash_model.clear();
		hash_fea.clear();
		hash_term_num.clear();
		hash_gram_num.clear();
		hash_stop.clear();
	}
	
};

}

#endif
