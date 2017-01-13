#include "Validate.h"

using namespace std;

#define INPUT "input.log"
#define NAMEINPUT "name.log"
#define SPEEDINPUT "testspeed.log"
#define DIFFINPUT "testdiff.log"

const static string DATA_BASE = "./data/base/";
const static string QUERYCLASS_DIR = "./data/base/analysis/";
const static string BASE_DIR="queryclass";

// void splitString(std::string& inputStr, char splitChar, std::vector<std::string>& outStrVec) {
//     string::size_type loc_start = inputStr.find_first_not_of(splitChar);
//     string::size_type loc_stop = loc_start;
//     while(loc_stop != string::npos)
//     {
//         loc_stop = inputStr.find_first_of(splitChar, loc_start);
//         if (loc_stop != string::npos)
//             outStrVec.push_back(inputStr.substr(loc_start, loc_stop - loc_start));
//         else
//             outStrVec.push_back(inputStr.substr(loc_start));
//         loc_start = inputStr.find_first_not_of(splitChar, loc_stop);
//         loc_stop = loc_start;
//     }
// }


CONVIMAGE_C::CONVIMAGE_C()
{
		int32_t dimnum_= 100;
		int32_t filnum_ = 128;
		int32_t padnum_ = 12;
	   	int32_t filid_ = 0;
		int32_t padid_ = 1;
		int32_t embdNum_ = 100000;
	   	float ModelConvThreshold_ = 15.0;
		dimnum = dimnum_;
		filnum = filnum_;
		padnum = padnum_;
		padid = padid_;
		filid = filid_;
		embdNum = embdNum_;
		ModelConvThreshold = ModelConvThreshold_;
}

CONVIMAGE_C::~CONVIMAGE_C()
{
		if(embd != NULL)
		{
				delete embd;
		}
		if(cw3 != NULL)
		{
				delete cw3;
		}
		if(cw4 != NULL)
		{
				delete cw4;
		}
		if(cw5 != NULL)
		{
				delete cw5;
		}
		if(cb3 != NULL)
		{
				delete cb3;
		}
		if(cb4 != NULL)
		{
				delete cb4;
		}
		if(cb5 != NULL)
		{
				delete cb5;
		}
		if(ow != NULL)
		{
				delete ow;
		}
		if(ob != NULL)
		{
				delete ob;
		}
		if(convidres != NULL)
		{
				delete convidres;
		}

		idmap.clear();
}
/*
CONVIMAGE_C* CONVIMAGE_C::getInstance(){
	if(!imageInstance){
		imageInstance=new CONVIMAGE_C();
	}
	return imageInstance;
}

void CONVIMAGE_C::releaseInstance(){
	if(imageInstance){
		delete imageInstance;
		imageInstance=NULL;
	}
}
*/


//float *embd, *cw3, *cw4, *cw5, *cb3, *cb4, *cb5, *ow, *ob;
//map<string, int> idmap;
//const int dimnum = 100;
//const int filnum = 128;
//const int padnum = 12;
//int filid = 0;
//int padid = 1;
int CONVIMAGE_C::PrintPara(){
	cerr << "[parameter of model]" << endl;
	cerr << "[dimnum] = " << dimnum << endl;
	cerr << "[filnum] = " << filnum << endl;
	cerr << "[padnum] = " << padnum << endl;
	cerr << "[ModelConvThreshold] = " << ModelConvThreshold << endl;
	cerr << "[idmap] size = " << idmap.size() << endl;
	cerr << "[embd]:" << endl;
	for(int i = 0; i < 2; i++)
		cerr << ob[i] << " ";
	cerr << endl;
	cerr << "[embd]:" << endl;
	for(int i = 0; i < dimnum; i++)
		cerr << embd[i] << " ";
	cerr << endl;

	cerr << "[cw3]:" << endl;
	for(int i = 0; i < filnum; i++)
		cerr << cw3[i] << " ";
	cerr << endl;

	cerr << "[cw4]:" << endl;
	for(int i = 0; i < filnum; i++)
		cerr << cw4[i] << " ";
	cerr << endl;

	cerr << "[cw5]:" << endl;
	for(int i = 0; i < filnum; i++)
		cerr << cw5[i] << " ";
	cerr << endl;

	cerr << "[cb3]:" << endl;
	for(int i = 0; i < filnum; i++)
		cerr << cb3[i] << " ";
	cerr << endl;

	cerr << "[cb4]:" << endl;
	for(int i = 0; i < filnum; i++)
		cerr << cb4[i] << " ";
	cerr << endl;

	cerr << "[cb5]:" << endl;
	for(int i = 0; i < filnum; i++)
		cerr << cb5[i] << " ";
	cerr << endl;

	cerr << "[ow]:" << endl;
	for(int i = 0; i < filnum; i++)
		cerr << ow[i] << " ";
	cerr << endl;

	cerr << "[ob]:" << endl;
	for(int i = 0; i < 2; i++)
		cerr << ob[i] << " ";
	cerr << endl;

	cerr << "[convidres]:" << endl;
	for(int i = 0; i < 100; i++)
		cerr << convidres[i] << " ";
	cerr << endl;


	return 0;
}
int CONVIMAGE_C::LoadModel(const char * filename){
	cerr << "[LoadModel] conv : " << filename << endl;
    ifstream filein;
    string line;
    filein.open(filename, ifstream::in);
    if(! filein){
		return -1;
    }
    if(!getline(filein, line))
	{
		cerr << "[ERROR] [Validate] Model file is illegal." << endl;
		return -1;
	}
	// dimnum	filnum
	vector<string> paramVec;
	spaceGary::StringSplit(line, paramVec, "\t");
	dimnum = spaceGary::toInt(paramVec[0]);
	filnum = spaceGary::toInt(paramVec[1]);
	padnum = spaceGary::toInt(paramVec[2]);
	ModelConvThreshold = spaceGary::toDouble(paramVec[3]);
	embdNum = spaceGary::toInt(paramVec[4]);

	embd =new float[embdNum * dimnum];
	cw3 = new float[filnum*dimnum*3];
	cw4 = new float[filnum*dimnum*4];
	cw5 = new float[filnum*dimnum*5];
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
    while( getline(filein, line)){
        vec.clear();
		spaceGary::StringSplit(line, vec, "\t");
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
	return 0;
}
int CONVIMAGE_C::Validate(vector<string> queryseg, float& score0, float& score1){
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
	//！！正式上线时可以加上对hit比例的判断
	//printf("hit=%f,len=%d\n", hit, len);
	
	float convres[filnum*3];
	for(int i = 0 ; i < filnum*3; i++)
		convres[i] = 0;
	int convsum = 0;
	for(int convnum = 3; convnum<=5;convnum++){
		//float * cw;
		float * cb;
		if(convnum == 3){
			//cw=cw3;
			cb=cb3;
		}else if(convnum == 4){
			//cw=cw4;
			cb=cb4;
		}else if(convnum == 5){
			//cw=cw5;
			cb=cb5;
		}
		//[3,100,1,128]
    	for(int f = 0; f < filnum; f++){
			float relu = -999;
    	    for(int i = 0 ; i + convnum - 1 < padnum && i <= len; i++){
    	        float res = 0;
    	        for(int j = i; j < i + convnum; j++){
					res += convidres[(j-i+convsum) * filnum + f + querym[j] * (3+4+5) * filnum];
    	        }
    	        if(res > relu)
    	            relu = res;
    	    }
    	    convres[(convnum-3)*filnum + f] = relu + cb[f];
    	}
		convsum += convnum;
	}
    for(int i = 0; i < filnum * 3; i++){
        score0 += convres[i] * ow[i*2+0];
        score1 += convres[i] * ow[i*2+1];
    }
    score0 += ob[0];
    score1 += ob[1];
	return 0;
}
int CONVIMAGE_C::IntentWeight(vector<string>& queryseg,
				const char* query,
				std::map<std::string, ClassInfo>& classmap,
				Worker * worker,
				string& vrname) {
	float score0, score1;
	if(queryseg.size() >= 10)
	{
			return 0;
	}
    Validate(queryseg, score0, score1);
	float w;
	w = score1 - score0;
	if(w > ModelConvThreshold)
	{
			SS_DEBUG((LM_INFO, "[Validate::%s][%016llx] Obtain %s Intent\n", __FUNCTION__, worker->request_id, vrname.c_str()));
			classmap[vrname].reform = query;
			classmap[vrname].data = query;
			classmap[vrname].score = 0.9;
			classmap[vrname].final = 0.9;
			classmap[vrname].qofinal = 0.9;
			if(vrname == "image")
				classmap[vrname].vr_level = 3;
			if(vrname == "video")
				classmap[vrname].vr_level = 4;

	}
	return 0;
}

int CONVIMAGE_C::LoadConvModel(string& ModelPathConv) 
{
	if(LoadModel(ModelPathConv.c_str()) == -1){
		cerr << "[Validate] ERROR: Fail to load Converlution image model, and Return!" << endl;
		return -1;
	}
 	return 0;
}
