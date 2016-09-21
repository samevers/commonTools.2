#ifndef __NAIVE_BAYES_
#define __NAIVE_BAYES_

#include "general.h"

//using namespace general_;



namespace naive_bayes_{

class word_dist{
private:
	int trainfile_statistic_word(ifstream& infile, map<string,int>& hash_y_num, int &total_y_num, map<pair<string,string>, long int>& hash_term_y_num);
	map<string, double> hash_y_prob;
	map<pair<string, string>, double > hash_model;
	map<string,long int> hash_term_num;
	map<string,long int> hash_termgram_num;
public:
	map<string,int> hash_fea;
	int train_word_dist(string train_file);
	int load_wordDist_model(string modelfile);//, map<string, double>& hash_y_prob, map<pair<string, string>, double >& hash_model);
	int predict_wordDist(string testfile, string modelfile);
	inline void release(){
		hash_y_prob.clear();
		hash_model.clear();
		hash_fea.clear();
		hash_term_num.clear();
		hash_termgram_num.clear();
	}
	
};

}

#endif
