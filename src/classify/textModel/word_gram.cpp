#include "word_gram.h"
#include "general.h"
#include <regex.h>
#include <boost/regex.hpp>
#include "../include/gary_common/gary_string.h"
#include "Platform/bchar.h" 
#include "Platform/encoding.h" 
#include "Platform/encoding/support.h"
#include "Platform/encoding/EncodingConvertor.h"
#include "Platform/encoding/stringmatch/AhoCorasick.h"
#include "Platform/gchar.h"
#include "../word_segmentor/WordSegmentor4/Segmentor/DicTree.h"

/****************************************/
/* NOTE:
/* TRAIN FORMAT: class term1 term2 term3 .... 【NOTE: term* must be different from each other in the current same line!】
/* MODEL FORMAT: term class1:weight1 class2:weight2 .....
/****************************************/



/****************************************/
/*	statistic analysis of train file, and 
/*	count the infomation needed in later calculation.
/****************************************/
using namespace general_;
using namespace std;
namespace naive_bayes_{
//const static string CLASSNAME[] = {"image","video","music","shop","job","novel","soft","wenda","web","fangchan"};
const static string CLASSNAME[] = {"video","image","music","shop","job","novel","soft","wenda","web","fangchan","porn"};
long int total_term_num = 0;
long int total_gram_num = 0;
vector<regex_t> RexPattern;
string stopfile = "./data/stop/stopword.txt";

bool comp_double(const pair<string, double>& x, const pair<string,double>& y)
{
		return x.second > y.second;
}
int Init()
{
	InitRexPattern();
	EncodingConvertor::initializeInstance(); 
    analysis::DicTree::instance()->loadDic();
}
int InitRexPattern()
{
	string englishCharacter = "^((ａ|ｂ|ｃ|ｄ|ｅ|ｆ|ｇ|ｈ|ｉ|ｇ|ｋ|ｌ|ｍ|ｎ|ｏ|ｐ|ｑ|ｒ|ｓ|ｔ|ｕ|ｖ|ｗ|ｘ|ｙ|ｚ| )+)$";
	string numCharacter = "^((１｜２｜３｜４｜５｜６｜７｜８｜９｜０｜　)+)$";
	string puncCharacter = "^((·|！|（|）|【|】|”|“|；|：|《|》|，|。|～|·|！|＠|＃|￥|％|…|…|＆|×|（|（|）|—|—|＋|＝|－|｛|｝|【|】|｜|＼|“|‘|：|；|？|、|》|。|《|，|　|＿|)+)$";

	regex_t pattern;
	for(int i = 0; i < 3; i++)
		RexPattern.push_back(pattern);

	if(regcomp(&RexPattern[0], englishCharacter.c_str(), REG_EXTENDED)!=0){
		cout << "load englishCharacter pattern error [0] !!!" << endl; 
		return false;
	}
	if(regcomp(&RexPattern[1], numCharacter.c_str(), REG_EXTENDED)!=0){
		cout << "load numCharacter pattern error [0] !!!" << endl; 
		return false;
	}
	if(regcomp(&RexPattern[2], puncCharacter.c_str(), REG_EXTENDED)!=0){
		cout << "load numCharacter pattern error [0] !!!" << endl; 
		return false;
	}
	return 0;
}
int allIsEngCharactor(const char* query)
{
	regmatch_t pm[10];
	int res = regexec(&RexPattern[0], query, 10, pm, 0);
	if(res == 0)
	{
		return 1;
	}
	return 0;
}
//
int allIsNumCharactor(const char* query)
{
	regmatch_t pm[10];
	int res = regexec(&RexPattern[1], query, 10, pm, 0);
	if(res == 0)
	{
		return 1;
	}
	return 0;
}
int allIsPuncCharactor(const char* query)
{
	regmatch_t pm[10];
	int res = regexec(&RexPattern[2], query, 10, pm, 0);
	if(res == 0)
	{
		return 1;
	}
	return 0;
}

int word_gram::loadStop(string filename)
{
	ifstream infile;
	infile.open(filename.c_str(),ios::in);
	if(!infile)
	{
		cerr << "ERROR : fail to open stopword file!" << endl;
		//return -1;
	}
	string line;
	while(getline(infile,line))
	{
		spaceGary::StringTrim(line);
		hash_stop[line]++;
	}
	return 0;
}
int word_gram::init()
{
		loadStop(stopfile);
}
int word_gram::trainfile_statistic_word(ifstream& infile, map<string,long int>& hash_y_num, long int &total_y_num, map<pair<string,string>, long int>& hash_term_y_num,map<pair<string,string>, long int>& hash_gram_y_num, map<string, long int>& hash_termnum_of_y, map<string, long int>& hash_gramnum_of_y)
{
	string line;
	string y;
	pair<string, string> p_;
	vector<string> vec;
	string bgram;
	string skip_bgram;
	string trigram;
	int loc = -1;
	string word;
	string word_sub;
	string midword;
	long int pv;
	int num = 0;
	cerr << "in trainfile_statistic_word()" << endl;
	while(getline(infile, line))
	{
		num++;
		if(num % 1000 == 0)
		{
			cerr << num << endl;
		}
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
		
		//半角转全角
		char dest[1024];
		memset(dest,0x00,1024);
		//EncodingConvertor::getInstance()->dbc2gchar(
		/*EncodingConvertor::getInstance()->t2sgchar(
				line.c_str(),
				(gchar_t*)dest,
				1024/2,
				true);
		line = string(dest);	
		*/
		general_::split_vec(line," ",vec);
		if(vec.size() < 1)
		{
			continue;
		}
		hash_termnum_of_y[y] += 1;// y 类总pv数量
		for(int i = 0 ; i < vec.size(); i++)
		{
			if(vec[i].length() < 2)
				continue;
			loc = vec[i].find(":");
			pv = 0;
			if(loc != -1)
			{
				word = vec[i].substr(0,loc);
				pv = atoi(vec[i].substr(loc+1, vec[i].length() - loc - 1).c_str());
				//pv = 1;
				if(hash_stop.find(word) != hash_stop.end()) // stop 
				{
					continue;
				}
				if(pv == 0)
						pv = 1;

			}else
			{
				word = vec[i];
				pv = 1;
				if(hash_stop.find(word) != hash_stop.end()) // stop 
						continue;
			}	

			// word特征，只考虑2字以上。
			if(word.length() > 1)
			{
				if(allIsPuncCharactor(word.c_str()) || word == "$#" || word == "^" || word == "w2v"
						|| allIsEngCharactor(word.c_str()) || allIsNumCharactor(word.c_str())) 
					continue;
				hash_term_y_num[make_pair(word,y)] += pv;// word 在y 类上的pv 数
				hash_term_num[word] += pv;				// word 的总pv 数
				total_term_num += pv;					// 所有类别上的所有词的总pv 数
			}
			// bgram and skip_gram
			if(i < vec.size() - 1)
			{
				if((loc = vec[i+1].find(":")) != -1)
				{
					word_sub = vec[i+1].substr(0,vec[i+1].find(":"));
				}else
					word_sub = vec[i+1];
				if(!allIsPuncCharactor(word.c_str()) && !allIsPuncCharactor(word_sub.c_str()))
				{
					bgram = word + "#_#" + word_sub;
					hash_gram_num[bgram] += pv;					// bgram 的总pv 数
					hash_gram_y_num[make_pair(bgram,y)] += pv;	// bgram 在y 类上的pv 数
					hash_gramnum_of_y[y] += pv;					// y 类上所有bgram的总pv 数
					total_gram_num += pv;						// 所有类别上的所有bgram 的总pv 数
				}
			}
			// skip-bigram
			if(i + 2 < vec.size())
			{
				if((loc = vec[i+2].find(":")) != -1)
				{
					word_sub = vec[i+2].substr(0,vec[i+2].find(":"));
				}else
					word_sub = vec[i+2];
				if(!allIsPuncCharactor(word.c_str()) && !allIsPuncCharactor(word_sub.c_str()))
				{
					skip_bgram = word + "#_#" + word_sub;
					hash_gram_num[skip_bgram] += pv;					// skip_bgram 的总pv 数
					hash_gram_y_num[make_pair(skip_bgram,y)] += pv;	// skip_bgram 在y 类上的pv 数
					hash_gramnum_of_y[y] += pv;					// y 类上所有skip_bgram的总pv 数
					total_gram_num += pv;						// 所有类别上的所有skip_bgram 的总pv 数
				}
			}
			// tri-grams
			if(i + 2 < vec.size())
			{
				if((loc = vec[i+1].find(":")) != -1)
				{
					midword = vec[i+1].substr(0,vec[i+1].find(":"));
				}else
					midword = vec[i+1];
				if(!allIsPuncCharactor(word.c_str()) && 
						!allIsPuncCharactor(word_sub.c_str()) &&
						!allIsPuncCharactor(midword.c_str()) )
				{
					trigram = word + "#_#" + midword + "#_#" + word_sub;
					hash_gram_num[trigram] += pv;					// trigram 的总pv 数
					hash_gram_y_num[make_pair(trigram,y)] += pv;	// trigram 在y 类上的pv 数
					hash_gramnum_of_y[y] += pv;					// y 类上所有trigram的总pv 数
					total_gram_num += pv;						// 所有类别上的所有trigram 的总pv 数
				}
			}
		}
		total_y_num ++;
		hash_y_num[y] ++;
	}

	return 0;
}

/****************************************/
/*	Read the train file.
/****************************************/
int word_gram::train_word_gram(string train_file)
{
	ifstream infile;
	if(general_::open_f(train_file, infile) == -1)
		return -1;
	cerr << "open_f is ok in train_word_gram()" << endl;
	string y;
	map<string,long int> hash_y_num;
	long int total_y_num = 0;
	map<pair<string,string>, long int> hash_term_y_num;
	map<pair<string,string>, long int> hash_gram_y_num;
	map<string, long int> hash_termnum_of_y;
	map<string, long int> hash_gramnum_of_y;
	cerr << "get into trainfile_statistic_word()" << endl;
	trainfile_statistic_word(infile, hash_y_num, total_y_num, hash_term_y_num,hash_gram_y_num,hash_termnum_of_y, hash_gramnum_of_y);

	// Build a model file to output.
	ofstream model_file;
	if(general_::Build_f("model.gram",model_file) == -1)
		return -1;


	// output probability of each class y.
	map<string, long int>::iterator iter_y;
	for(iter_y = hash_y_num.begin(); iter_y != hash_y_num.end(); iter_y++)
	{
		model_file << "##class## " << iter_y->first << " " << (double)(iter_y->second)/(double)total_y_num << endl;
	}


	// calculate the weight of each term
	map<pair<string,string>, long int>::iterator iter;
	// word
	string term;
	double weight;
	for(iter = hash_term_y_num.begin(); iter != hash_term_y_num.end(); iter++)
	{
		term = iter->first.first;
		y = iter->first.second;
		//weight = (double)total_term_num * (double)(iter->second)/((double)hash_term_num[term]*(double)hash_y_num[y]);
		//cout << "num of "<< term << " in class " << y << " is " <<(double)(iter->second) << endl;
		//cout << "num of "<< term << " in all " << " is " <<  hash_term_num[term] << endl;
		//cout << "num of all terms in class " << y << " is " <<  hash_termnum_of_y[y] << endl;
		if(hash_termnum_of_y[y] > 0 && hash_term_num[term] > 0)
		{
			double plus = (double)hash_term_num[term] + (double)hash_termnum_of_y[y];
			weight = plus * (double)(iter->second)*(double)iter->second/((double)hash_term_num[term]*(double)hash_termnum_of_y[y]);
			//weight = (double)100 * (double)iter->second/(double)hash_termnum_of_y[y];
			model_file << term << " " << y << " " << weight  << endl;
		}
	}
	// bgram
	string gram;
	for(iter = hash_gram_y_num.begin(); iter != hash_gram_y_num.end(); iter++)
	{
		gram = iter->first.first;
		y = iter->first.second;
		if(hash_gram_num[gram] > 0 && hash_gramnum_of_y[y] > 0)
		{
			double plus = (double)hash_gram_num[gram] + (double)hash_gramnum_of_y[y];
			//weight = (double)(iter->second)/(double)hash_gram_num[gram]; // model.gram.image.1
			//weight =  (double)(iter->second)/(double)hash_y_num[y];	// model.gram.image.2
			//weight = (double)total_gram_num * (double)(iter->second)/((double)hash_gram_num[gram]*(double)hash_y_num[y]);
			weight = plus * (double)(iter->second)*(double)(iter->second)/((double)hash_gram_num[gram]*(double)hash_gramnum_of_y[y]);
			//weight = (double)100 * (double)(iter->second)/(double)hash_gramnum_of_y[y];
			model_file << gram << " " << y << " " << weight << endl;
		}
	}

	// clear cache.
	hash_y_num.clear();
	hash_term_y_num.clear();
	hash_term_num.clear();
	hash_gram_y_num.clear();
	hash_gram_num.clear();
	hash_termnum_of_y.clear();
	hash_gramnum_of_y.clear();
	infile.close();
	model_file.close();
	return 0;
}

/****************************************/
/*	Load naive bayes model.
/****************************************/
int word_gram::load_wordDist_model(string modelfile)//, map<string, double>& hash_y_prob, map<pair<string, string>, double >& hash_model)
{
	cerr << "INFO : Begin to load model file ...." << endl;
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
		if(tmp.size() < 2)
			continue;
		if(tmp[0] == "##class##")
		{
			general_::string_to_(tmp[2], prob_y);
			hash_y_prob[tmp[1]] = prob_y;
			continue;
		}
		term = tmp[0];
		y = tmp[1];
		general_::string_to_(tmp[2], prob_term_y);
		pir_ = make_pair(term, y);
		hash_model.insert(make_pair(pir_, prob_term_y));
	}
	// clear cache.
	model_f.close();
	tmp.clear();
	cerr << "INFO : Model file is completely loaded ..." << endl;
	return 0;
}


/****************************************/
/*	Load Naive Bayesian classifier model,
/*	and predict new income.
/****************************************/
int word_gram::predict_wordDist(string testfile, string modelfile)
{
	map<string, double>::iterator iter_y;
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
	//map<string, double> scores;
	vector<pair<string, double> > scores;
	int class_size = hash_y_prob.size();
	long int correct_num = 0;
	long int total_num = 0;
	string correct_class = "";
	string max_class = "";
	double max_prob = 0.0;
	string max_class2 = "";
	double max_prob2 = 0.0;
	string bgram;
	string skip_bgram;
	string tri_bgram;
	while(getline(infile, line))
	{
		if(line.length() < 1)
			continue;
		cout << "content = " << line << endl;
		correct_class = "";
		max_class = "";
		max_prob = 0.0;
		max_class2 = "";
		max_prob2 = 0.0;
		vec_tmp.clear();
		general_::split_vec(line," ",vec_tmp);
		if(vec_tmp.size() < 2)
			continue;
		correct_class = vec_tmp[0];
		int fea_num;
		scores.clear();
		for(iter_y = hash_y_prob.begin(); iter_y != hash_y_prob.end(); iter_y++)
		{
			prob_mul = 1.0;
			prob_add = 0.0;
			fea_num = 0;
			y = iter_y->first;
			p = iter_y->second;
			bgram = "";
			skip_bgram = "";
			tri_bgram = "";
			for(int i = 1; i < vec_tmp.size(); i++)
			{
				cout << "vec_tmp[0] = " << vec_tmp[0] << endl;
				if(vec_tmp[i].length() < 4)// not consider short feature words. 
					continue;
				// word term
				if(hash_model.find(make_pair(vec_tmp[i],y)) != hash_model.end())
				{
					prob_mul *= log(hash_model[make_pair(vec_tmp[i],y)]+0.01);
					prob_add += log(hash_model[make_pair(vec_tmp[i],y)]+0.01);
					cout << "term:" << vec_tmp[i] << "\ty:" << y << "\tprob:"<< hash_model[make_pair(vec_tmp[i],y)] << endl;
					fea_num++;
				}
				// bigram
				if(i < vec_tmp.size() - 1)
				{
					bgram = vec_tmp[i] + "#_#" + vec_tmp[i + 1];
					if(hash_model.find(make_pair(bgram,y)) != hash_model.end())
					{
						cout << "bigram prob = " << hash_model[make_pair(bgram,y)] << endl;
						prob_mul *= log(hash_model[make_pair(bgram,y)]+0.01);
						prob_add += log(hash_model[make_pair(bgram,y)]+0.01);
						cout << "bgram:" << bgram << "\ty:"<< y << "\tprob:" << hash_model[make_pair(bgram,y)] << endl;
						fea_num++;
					}
				}
				// skip-gram
				if(i < vec_tmp.size() - 2)
				{
					skip_bgram = vec_tmp[i] + "#_#" + vec_tmp[i+2];
					if(hash_model.find(make_pair(skip_bgram,y)) != hash_model.end())
					{
						cout << "skip-gram prob = " << hash_model[make_pair(skip_bgram,y)] << endl;
						prob_mul *= log(hash_model[make_pair(skip_bgram,y)]+0.01);
						prob_add += log(hash_model[make_pair(skip_bgram,y)]+0.01);
						cout << "skip_bgram:" << skip_bgram << "\ty:"<< y << "\tprob:" << hash_model[make_pair(skip_bgram,y)] << endl;
						fea_num++;
					}

				}
				if(i < vec_tmp.size() - 2)
				{
					tri_bgram = vec_tmp[i] + "#_#" + vec_tmp[i+1] + "#_#" + vec_tmp[i+2];
					if(hash_model.find(make_pair(tri_bgram,y)) != hash_model.end())
					{
						cout << "tri-gram prob = " << hash_model[make_pair(tri_bgram,y)] << endl;
						prob_mul *= log(hash_model[make_pair(tri_bgram,y)]+ 0.01);
						prob_add += log(hash_model[make_pair(tri_bgram,y)]+ 0.01);
						cout << "tri_bgram:" << tri_bgram << "\ty:"<< y << "\tprob:" << hash_model[make_pair(tri_bgram,y)] << endl;
						fea_num++;
					}

				}

			}

			//prob_mul *= p;
			prob_add *= p;
			cout << "class:" << CLASSNAME[atoi(y.c_str())] <<"\tprob_add = " << prob_add << endl;
			prob_add /=(double)fea_num;
			cout << "class_:" <<  CLASSNAME[atoi(y.c_str())] <<"\tprob_add_ = " << prob_add << endl;
			//scores[y] = prob_add;
			scores.push_back(make_pair(y.c_str(),prob_add));
			if(prob_add > max_prob)
			{
				max_class2 = max_class;
				max_prob2 = max_prob;
				max_class = y;
				max_prob = prob_add;
				cout << "max_prob changes to be : " << max_prob << endl;
			}else if(prob_add > max_prob2)
			{
				max_class2 = y;
				max_prob2 = prob_add;
				cout << "max_prob2 changes to be : " << max_prob2 << endl;
			}
			cout << "max_prob:" << max_prob << endl;
			cout << "max_prob2:" << max_prob2 << endl;
			
		}
		//sort(scores.begin(), scores.end(), comp_double);
		//cout << "class_size = " << class_size << endl;
		//map<string,double>::iterator iter;
		//for(iter = scores.begin(); iter != scores.end(); iter++)
		for(int m = 0; m < scores.size(); m++)
		{
			//outfile << CLASSNAME[atoi(iter->first.c_str())] << ":" << iter->second << " ";
			outfile << CLASSNAME[atoi(scores[m].first.c_str())] << ":" << scores[m].second << " ";
		}
		double confidence;
		if(scores.size() > 1)
			confidence = scores[1].second - scores[0].second;
		cout << "TERMINAL OF: "<< line << endl;
		outfile << "\tMAX_CLASS:" << CLASSNAME[atoi(max_class.c_str())] << " MAX_PROB:" << max_prob << " confidence:" << confidence << " || " << line << endl;
		cout << "CORRECT_CLASS: " << CLASSNAME[atoi(correct_class.c_str())] << endl;
		cout << "MAX_CLASS:" << CLASSNAME[atoi(max_class.c_str())] << " MAX_PROB:" << max_prob << endl;
		cout << "MAX_CLASS2:" << CLASSNAME[atoi(max_class2.c_str())] << " MAX_PROB2:" << max_prob2 << endl;
		cout << "max_class = " << max_class << "\tmax_class2 = " << max_class2 << "\tcorrect_class = " << correct_class << endl;
		cout << "max_prob = " << max_prob << "\tmax_prob2 = " << max_prob2 << endl;
		cout << "max_prob2/max_prob = " << max_prob2/max_prob << endl;
		if(max_class != "")
		{
			if(max_class == correct_class)
			{
				correct_num++;
			}
		}else
		{
			continue;
		}
		total_num++;
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
