#include "word_distribute.h"
#include "general.h"
#include "../include/gary_common/gary_string.h"
/****************************************/
/* NOTE:
/* TRAIN FORMAT: class term1 term2 term3 .... ¡¾NOTE: term* must be different from each other in the current same line!¡¿
/* MODEL FORMAT: term class1:weight1 class2:weight2 .....
/****************************************/



/****************************************/
/*	statistic analysis of train file, and 
/*	count the infomation needed in later calculation.
/****************************************/
using namespace general_;

namespace naive_bayes_{
//const static string CLASSNAME[] = {"image","","app","fangchan","game","image","job","web","music","shop","software","sucai","video","web","wenda"};
const static string CLASSNAME[] = {"image","video","music","shop","job","novel","soft","wenda","web","fangchan"};
long int total_term_num = 0;
int word_dist::trainfile_statistic_word(ifstream& infile, map<string,int>& hash_y_num, int &total_y_num, map<pair<string,string>, long int>& hash_term_y_num)
{
	string line;
	string y;
	pair<string, string> p_;
	vector<string> vec;
	int loc = -1;
	while(getline(infile, line))
	{
		vec.clear();
		if(line == "" || line.length() < 4)
			continue;
		// del first space in the line, so that the <y> label is not be calculated.
		if((loc = line.find(" ")) != -1)
		{
			y = line.substr(0,loc);
			line = line.substr(loc+1, line.length() - loc - 1);
		}else
			continue;
		general_::split_vec(line," ",vec);
		if(vec.size() < 1)
		{
			continue;
		}
		for(int i = 0 ; i < vec.size(); i++)
		{
			if(vec[i].length() < 4)
				continue;
			hash_term_y_num[make_pair(vec[i],y)]++;
			hash_term_num[vec[i]]++;
			hash_y_num[y]++;
			total_term_num++;
		}
		total_y_num ++;
	}

	return 0;
}

/****************************************/
/*	Read the train file.
/****************************************/
int word_dist::train_word_dist(string train_file)
{
	ifstream infile;
	if(general_::open_f(train_file, infile) == -1)
		return -1;

	string y;
	map<string,int> hash_y_num;
	int total_y_num = 0;
	map<pair<string,string>, long int> hash_term_y_num;
	trainfile_statistic_word(infile, hash_y_num, total_y_num, hash_term_y_num);

	// Build a model file to output.
	ofstream model_file;
	if(general_::Build_f("model.wordDistribute",model_file) == -1)
		return -1;
	// output probability of each class y.
	map<string, int>::iterator iter_y;
	for(iter_y = hash_y_num.begin(); iter_y != hash_y_num.end(); iter_y++)
	{
		model_file << "##class## " << iter_y->first << " " << (double)(iter_y->second)/(double)total_y_num << endl;
	}
	// calculate the weight of each term
	map<pair<string,string>, long int>::iterator iter;
	string term;
	double weight;
	for(iter = hash_term_y_num.begin(); iter != hash_term_y_num.end(); iter++)
	{
		term = iter->first.first;
		y = iter->first.second;
		weight = (double)total_term_num * (double)(iter->second)/((double)hash_term_num[term]*(double)hash_y_num[y]);
		model_file << term << " " << y << " " << weight * 1000 << endl;
	}
	// clear cache.
	hash_y_num.clear();
	hash_term_y_num.clear();
	infile.close();
	model_file.close();
	return 0;
}

/****************************************/
/*	Load naive bayes model.
/****************************************/
int word_dist::load_wordDist_model(string modelfile)//, map<string, double>& hash_y_prob, map<pair<string, string>, double >& hash_model)
{
	ifstream model_f;
	if(general_::open_f(modelfile, model_f) == -1)
		return -1;

	string line;
	int loc;
	vector<string> tmp;
	double prob_y;
	string term;
	string y;
	double prob_term_y;
	pair<string,string> pir_;
	while(getline(model_f, line))
	{
		tmp.clear();
		general_::split_vec(line," ",tmp);
		if(tmp[0] == "##class##")
		{
			general_::string_to_(tmp[2], prob_y);
			hash_y_prob[tmp[1]] = prob_y;
			continue;
		}
		term = tmp[0];
		y = tmp[1];
		if(term.find("#_#") != -1)
		{
			// cerr << "[INFO] Skip bigram terms, here only consider Unigram as features." << endl;
			continue;
		}

		general_::string_to_(tmp[2], prob_term_y);
		pir_ = make_pair(term, y);
		hash_model.insert(make_pair(pir_, prob_term_y));
	}
	// clear cache.
	model_f.close();
	tmp.clear();

	return 0;
}


/****************************************/
/*	Load Naive Bayesian classifier model,
/*	and predict new income.
/****************************************/
int word_dist::predict_wordDist(string testfile, string modelfile)
{
	map<string, double>::iterator iter_y;
	/*map<string, double> hash_y_prob;
	map<pair<string, string>, double > hash_model;
	if(load_naive_model(modelfile, hash_y_prob, hash_model) == -1)
		return -1;
	*/
	ifstream infile;
	if(general_::open_f(testfile, infile) == -1)
		return -1;
	string output = testfile + ".out";
	ofstream outfile;
	outfile.open(output.c_str(), ios::out);

	string line;
	string y;
	double p;
	vector<string> vec_tmp;
	double prob_mul;
	double prob_add;
	double max_prob = 0.0;
	string max_class = "";
	map<string, double> scores;
	int class_size = hash_y_prob.size();
	int correct_num = 0;
	int total_num = 0;
	string correct_class = "";
	while(getline(infile, line))
	{
		max_prob = 0.0;
		correct_class = "";
		max_class = "";
		vec_tmp.clear();
		total_num++;
		general_::split_vec(line," ",vec_tmp);
		correct_class = vec_tmp[0];
		string term;
		double weight;
		int loc;
		for(iter_y = hash_y_prob.begin(); iter_y != hash_y_prob.end(); iter_y++)
		{
			prob_mul = 1.0;
			prob_add = 0.0;
			y = iter_y->first;
			if(y == "10")// ¹éÒ»»¯ software ºÍ app
				y = "2";
			if(y == "11")
				y = "5";
			p = iter_y->second;
			for(int i = 1; i < vec_tmp.size(); i++)
			{
				if(vec_tmp[i].length() < 4)// not consider short feature words. 
					continue;
				if((loc = vec_tmp[i].find(":")) != -1)
				{
					term = vec_tmp[i].substr(0,loc);
					general_::string_to_(vec_tmp[i].substr(loc+1, vec_tmp[i].length() - loc - 1), weight);
				}else
				{
					term = vec_tmp[i];
					weight = 1.0;
				}
				prob_mul *= hash_model[make_pair(term,y)] * weight;
				prob_add += hash_model[make_pair(term,y)] * weight;
				cout << "term:" << vec_tmp[i] << "\ty:" << y << "\tprob:"<< hash_model[make_pair(vec_tmp[i],y)] << endl;
			}

			prob_mul *= p;
			cout << "class:" << y <<"\tprob_add = " << prob_add << endl;
			prob_add /=(double)vec_tmp.size();
			cout << "class_:" << y <<"\tprob_add_ = " << prob_add << endl;
			scores[y] = prob_add;
			if(prob_add > max_prob)
			{
				max_class = y;
				max_prob = prob_add;
				cout << "max_prob changes to be : " << max_prob << endl;
			}
			cout << "max_prob:" << max_prob << endl;
			
		}
		if(max_class == "10")
			max_class == "2";
		if(max_class == "11")
			max_class = "5";
		//sort(scores.begin(), scores.end(), comp_double);
		//cout << "class_size = " << class_size << endl;
		map<string,double>::iterator iter;
		for(iter = scores.begin(); iter != scores.end(); iter++)
		{
			outfile << CLASSNAME[atoi(iter->first.c_str())] << ":" << iter->second << " ";
		}
		outfile << "\tMAX_CLASS:" << CLASSNAME[atoi(max_class.c_str())] << " MAX_PROB:" << max_prob << " || " << line << endl;
		cout << "max_class = " << max_class << "\tcorrect_class = " << correct_class << endl;
		if(max_class == correct_class)
		{
			correct_num++;
		}
		scores.clear();
		cout << "------------------------" << endl;
	}
	cout << "accuracy = " << (double)correct_num/(double)total_num << endl;
	hash_y_prob.clear();
	hash_model.clear();
	vec_tmp.clear();
	infile.close();
	outfile.close();

	return 0;
}

}
