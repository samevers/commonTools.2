#ifndef __NAIVE_BAYES_
#define __NAIVE_BAYES_

#include "general.h"

//using namespace general_;



namespace naive_bayes_{

class naive_bayes{
private:
	int trainfile_statistic(ifstream& infile, map<string,int>& hash_y_num, int &total_y_num, map<pair<string,string>, long int>& hash_term_y_num);
	map<string, double> hash_y_prob;
	map<pair<string, string>, double > hash_model;
	map<string,long int> hash_term_num;
public:
	map<string,int> hash_fea;
	int Init();
	int loadFeatureFile();
	int train_naiveBayes(string train_file);
	int load_naive_model(string modelfile);//, map<string, double>& hash_y_prob, map<pair<string, string>, double >& hash_model);
	int predict_naivebayes(string testfile, string modelfile);
	inline void release(){
		hash_y_prob.clear();
		hash_model.clear();
		hash_fea.clear();
		hash_term_num.clear();
	}
	
};

}

#endif
