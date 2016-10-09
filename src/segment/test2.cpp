#include "wordSegment.h"
#include "general.h"
#include "../include/gary_common/gary_string.h"
#include <vector>

using namespace std;

const int32_t MAXLEN_ = 20480;

int main(int arg, char** argv)
{
	if(arg !=  2)
	{
		cerr << "[INFO] Please input a filename!" << endl;
		return -1;
	}
	string inputfile = argv[1];
	ifstream infile;
	infile.open(inputfile.c_str(), ios::in);
	if(!infile)
	{
		cerr << "[ERROR] Fail to open filename!" << endl;
		return -1;
	}
	string line;
	char dest[MAXLEN_];
	// init segment
	wordSegment * seg;
	seg = wordSegment::getInstance();
	seg->Init();
	while(getline(infile, line))
	{
		spaceGary::StringTrim(line);
		//°ë½Ç×ªÈ«½Ç
		vector<string> seg_parts;
		memset(dest,0x00,MAXLEN_);
		cerr << "=----------1" << endl;
		EncodingConvertor::getInstance()->dbc2gchar(
			line.c_str(),
			(gchar_t*)dest,
			MAXLEN_/2,
			true);
		string gQuery(dest);
		seg->Segment_(gQuery,seg_parts);
		cerr << "=----------2" << endl;
		for(int i = 0; i < seg_parts.size(); i++)
		{
			cout << seg_parts[i] << " ";
		}
		cout << endl;
	}
	wordSegment::releaseInstance();
	return 0;
}
