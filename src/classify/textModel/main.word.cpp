/*************************************************
 *
 * Author: 
 * Create time: 2015  5ÔÂ 04 23Ê±49·Ö11Ãë
 * E-Mail: @sogou-inc.com
 * version 1.0
 *
*************************************************/


#include "word_distribute.h"
using namespace naive_bayes_;

int main(int argc, char** argv)
{
	cerr << "argc = " << argc << endl;
	if(argc == 3)
	{
		string filename = argv[1];
		string model_file = argv[2];
		word_dist wd;
		wd.load_wordDist_model(model_file);
		wd.predict_wordDist(filename.c_str(), model_file);
		wd.release();
		return 0;
	}else if(argc == 2)
	{
		string train_file = argv[1];
		word_dist wd;
		wd.train_word_dist(train_file);
		wd.release();

		return 0;
	}
}
