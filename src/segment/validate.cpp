#include <fstream>
#include <iostream>
#include <sstream>
#include <cmath>
#include <regex.h>
#include "Platform/log.h"
#include "wordSegment.h"
#include <sys/time.h>

using namespace std;
const static int MAXSTRLEN=1024;
const static int _MAXQUERYLEN=MAXSTRLEN/2;


#define INPUT "input.log"
#define NAMEINPUT "name.log"
#define SPEEDINPUT "testspeed.log"
#define DIFFINPUT "testdiff.log"
void splitString(std::string& inputStr, char splitChar, std::vector<std::string>& outStrVec) {
    string::size_type loc_start = inputStr.find_first_not_of(splitChar);
    string::size_type loc_stop = loc_start;
    while(loc_stop != string::npos)
    {
        loc_stop = inputStr.find_first_of(splitChar, loc_start);
        if (loc_stop != string::npos)
            outStrVec.push_back(inputStr.substr(loc_start, loc_stop - loc_start));
        else
            outStrVec.push_back(inputStr.substr(loc_start));
        loc_start = inputStr.find_first_not_of(splitChar, loc_stop);
        loc_stop = loc_start;
    }
}



float *cb3, *cb4, *cb5, *ow, *ob, * convidres;
map<string, int> idmap;
const int dimnum = 100;
const int filnum = 128;
const int padnum = 12;
int filid = 0;
const int layersize = (3+4+5) * filnum;
int padid = 1;
int loadmodel(const char * filename){
    ifstream filein;
    string line;
    filein.open(filename, ifstream::in);
    if(! filein){
		return -1;
    }
	float * embd =new float[261953 * dimnum];
	//float * embd =new float[159220 * dimnum];
	// float * embd =new float[100000 * dimnum];
	float * cw3 = new float[filnum*dimnum*3];
	float * cw4 = new float[filnum*dimnum*4];
	float * cw5 = new float[filnum*dimnum*5];
	cb3 = new float[filnum];
	cb4 = new float[filnum];
	cb5 = new float[filnum];
	ow =  new float[filnum*3*2];
	ob =  new float[2];
    vector <string> vec;
	int cw3idx=0;
	int cw4idx=0;
	int cw5idx=0;
	int owidx=0;
	int idmax=0;
	int32_t num = 1;
    while( getline(filein, line)){
        vec.clear();
        splitString(line, '\t', vec);
        if (vec.size() < 2)
			continue;
		if(vec[1]=="EMBEDDING"){
			int id = atoi(vec[2].c_str());
			idmap[vec[0]] = id;
			if(id>idmax) idmax = id;
			for(int i = 0 ; i < dimnum; i++){
				embd[id*dimnum+i] = atof(vec[i+3].c_str());
			}
		}else if(vec[0]=="convW3"){
			for(int i = 0 ; i < filnum; i++){
				cw3[cw3idx * filnum + i] = atof(vec[i+1].c_str());
			}
			cw3idx++;
		}else if(vec[0]=="convW4"){
			for(int i = 0 ; i < filnum; i++){
				cw4[cw4idx * filnum + i] = atof(vec[i+1].c_str());
			}
			cw4idx++;
		}else if(vec[0]=="convW5"){
			for(int i = 0 ; i < filnum; i++){
				cw5[cw5idx * filnum + i] = atof(vec[i+1].c_str());
			}
			cw5idx++;
		}else if(vec[0]=="convb3"){
			 for(int i = 0; i < filnum; i++)
	             cb3[i] = atof(vec[i+1].c_str());
		}else if(vec[0]=="convb4"){
			 for(int i = 0; i < filnum; i++)
	             cb4[i] = atof(vec[i+1].c_str());
		}else if(vec[0]=="convb5"){
			 for(int i = 0; i < filnum; i++)
	             cb5[i] = atof(vec[i+1].c_str());
		}else if(vec[0]=="outputW"){
			ow[owidx*2+0]=atof(vec[1].c_str());
	        ow[owidx*2+1]=atof(vec[2].c_str());
	        owidx++;
		}else if(vec[0]=="outputb"){
			ob[0]=atof(vec[1].c_str());
			ob[1]=atof(vec[2].c_str());
		}
	}
	filein.close();
	string fil = "<FIL/>";
	string pad = "<PAD/>";
	if(idmap.find(fil)!=idmap.end()){
		filid = idmap[fil];
	}else{
		return -1;
	}
	if(idmap.find(pad)!=idmap.end()){
		padid = idmap[pad];
	}else{
		return -1;
	}
	int midsize = idmax * (3+4+5) * filnum;
	convidres = new float[midsize];
	for(int i = 0 ; i < midsize; i++)
		convidres[i] = 0;
	for(int id = 0 ; id < idmax; id++){
		int convsum = 0;
		for(int convnum = 3; convnum <= 5;convnum++){
			float * cw;
			if(convnum == 3){
				cw=cw3;
			}else if(convnum == 4){
				cw=cw4;
			}else if(convnum == 5){
				cw=cw5;
			}
			//[3,100,1,128]
    		for(int f = 0; f < filnum; f++){
				for(int j = 0; j < convnum; j++){
					float res = 0;
    				for(int k = 0; k < dimnum; k++){
    		    		res += embd[id * dimnum + k] * cw[j * filnum * dimnum + k * filnum + f];
    		    	}
    		    	convidres[(j+convsum) * filnum + f + id * (3+4+5) * filnum] = res;
				}
    		}
			convsum += convnum;
		}
	}

	printf("load finished\n");

	//for(int i =  0; i<idmax;i++){
	//	printf("%d", i);
	//	for(int j = 0 ; j < dimnum; j++){
	//		printf("\t%f", embd[i*dimnum+j]);
	//	}
	//	printf("\n");
	//}
	//for(int i = 0 ; i < owidx; i++){
	//	printf("ow%d\t%f\t%f\n", i, ow[i*2+0], ow[i*2+1]);
	//}
	delete cw3;
	delete cw4;
	delete cw5;
	delete embd;
	return 0;
}
int validate(vector<string> queryseg, float& score0, float& score1){
	score0=score1=0;
	int querym[padnum];
	int len = queryseg.size();
	float hit = 0;
	for(int i = 0 ; i < padnum; i++){
		if(i < len){
			if(idmap.find(queryseg[i]) == idmap.end())
				querym[i] = filid;
			else{
				querym[i] = idmap[queryseg[i]];
				hit++;
			}
		}else{
			querym[i] = padid;
		}
	}
	if(hit/(len+0.001) < 0.6){
		score0 = 0;
		score1 = 0;
		return 0;
	}
	
	const int filsum = filnum*3;
	float convres[filsum];
	memset(convres, 0, sizeof(convres));
	//for(int i = 0 ; i < filsum; i++)
	//	convres[i] = 0;
	int convsum = 0;
	float relu=-999;
	float res = 0;
	int i,j,f;
	float *cb;
	for(int convnum = 3; convnum <= 5; convnum++){
		if(convnum == 3){
			cb = cb3;
		}else if(convnum == 4){
			cb=cb4;
			convsum = 3;
		}else if(convnum == 5){
			cb=cb5;
			convsum = 7;
		}
		const int ilimit = padnum - convnum + 1;
    	for(f = 0; f < filnum; f++){
			relu = -999;
    	    for(i = 0 ; i < ilimit && i <= len; i++){
    	        res = 0;
    	        for(j = i; j < i + convnum; j++){
					res += convidres[(j-i+convsum) * filnum + f + querym[j] * layersize];
    	    	}
    	        if(res > relu)
    	            relu = res;
    	    }
    	    convres[(convnum-3)*filnum + f] = relu + cb[f];
    	}
	}
    for(i = 0; i < filsum; i++){
        score0 += convres[i] * ow[i*2+0];
        score1 += convres[i] * ow[i*2+1];
    }
    score0 += ob[0];
    score1 += ob[1];
	return 0;
}

int predict()
{
	EncodingConvertor::initializeInstance();
	ec = EncodingConvertor::getInstance();
	dictree = analysis::DicTree::instance();
	iqdic = analysis::IQDic::instance();
	segmentor = WordSegmentor::getInstance();
	graphSeg = GraphSegmentor::getInstance();
	iqdic->loadDic();
	dictree->loadDic();
	analysis::QuerySegmentor wordseg;
	wordseg.open(analysis::DicTree::instance(), analysis::IQDic::instance());
	analysis::TGraph annseg;
	annseg.open(analysis::DicTree::instance());

	int32_t num = 0;
	string query;
	while(getline(cin, query))
	{
		int querylen = query.length();
		num ++;
		if(querylen < 1 ){
			cerr << "[error] querylen is too short : line " << num << endl;
			cout << endl;
			continue;
		}
		char buffer[MAXSTRLEN];
		memset(buffer, 0,  MAXSTRLEN);
		int len = ec->t2sgchar(query.c_str(), (gchar_t*)buffer, MAXSTRLEN/2, true);
		if(len>=MAXSTRLEN/2 || len < 0){
			cerr << "[error] querylen is too long" << endl;
			cout << endl;
			continue;
		}
		buffer[len*2] = '\0';
		string gQuery(buffer);
		int glen = strlen(buffer) / 2;
	
		analysis::WordSegmentorInfo request;
		analysis::WordSegmentorInfo parsed;
		vector<string> termList;
		
		segmentor->Segment(&wordseg, buffer, request, parsed, termList);

		// validate
		float score0, score1;
		timeval start,end;
		gettimeofday(&start,NULL);
		validate(termList, score0, score1);
		gettimeofday(&end,NULL);
		float dt = (end.tv_sec*1000*1000 + end.tv_usec - start.tv_sec*1000*1000 - start.tv_usec)/1000.0;
		float w_ = score1 - score0;
		cout << query << "\t" << w_ << "\t" << score1 << "\t" << score0 << "\t" << dt << endl;
	}

	return 0;
}

int main()
{
	cerr << "[INFO] Loading model.videoconv ..."<< endl;
	if(loadmodel("./model.videoconv") == -1){
		return -1;
	}
	// validate
	cerr << "[INFO] Make the processing ..." << endl;
	predict();
	return 0; 

}
