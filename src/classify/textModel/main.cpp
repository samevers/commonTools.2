/*************************************************
 *
 * Author: 
 * Create time: 2015  5ÔÂ 04 23Ê±49·Ö11Ãë
 * E-Mail: @sogou-inc.com
 * version 1.0
 *
*************************************************/


#include "naive_bayes.h"
using namespace naive_bayes_;



int main(int argc, char** argv)
{

	cerr << "argc = " << argc << endl;
	if(argc == 3)
	{
		string filename = argv[1];
		string model_file = argv[2];
		naive_bayes nb;
		nb.load_naive_model(model_file);
		nb.predict_naivebayes(filename.c_str(), model_file);
		nb.release();
		return 0;
	}else if(argc == 2)
	{
		string train_file = argv[1];
		naive_bayes nb;
		nb.loadFeatureFile();
		nb.train_naiveBayes(train_file);
		nb.release();
		return 0;
	}
}
