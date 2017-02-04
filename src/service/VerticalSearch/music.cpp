#include "VerticalDA.h"
#include "VerticalDOC.h"
using namespace std;

const char* TEACHER_FILE = "../../../data/LearnDlg/learn.log";
// 采用docSearch，可以使得用户Query 不受语序的影响。
const static string SINGER_DA_IndexFile_DLG = "../../../data/index_dir/singerInfo.out.index";
const static string SONG_DA_IndexFile_DLG = "../../../data/index_dir/songInfo.out.index";
const static string SINGERSONG_DOC_IndexFile_DLG = "../../../data/index_dir/singerSong.doc.index";


const char* dir_path = "../../../";
int main(int arg, char** argv)
{
	VERTICAL_DOC vd;
	vd.Init(dir_path, SINGERSONG_DOC_IndexFile_DLG);


	MUSIC singerDlg;
	_INFO("Begin to Init singer dlg");
	string singerDaFile = SINGER_DA_IndexFile_DLG;
	//Darts::DoubleArray *singerIndex;
	//if(singerDlg.Init(dir_path,singerDaFile,singerIndex) == -1)
	if(singerDlg.Init(dir_path,singerDaFile) == -1)
	{
		cerr << "[ERROR] Fail to singer dlg.init()" << endl;
		return -1;
	}
	_INFO("Init singer dlg OK" );

	// song
	MUSIC songDlg;
	_INFO("Begin to Init song dlg");
	string songDaFile = SONG_DA_IndexFile_DLG;
	//Darts::DoubleArray *songIndex;
	if(songDlg.Init(dir_path,songDaFile) == -1)
	{
		cerr << "[ERROR] Fail to song dlg.init()" << endl;
		return -1;
	}
	_INFO("Init song dlg OK");
	
	//string query = argv[1];
	string query;
	cerr << "[PLEASE INPUT A QUERY]:" << endl;
	while(true)
	{
		cerr << "[INPUT]:" << endl;
		while(cin >> query)
		{
			if(query == "exit")
			{
				cerr << "[THANKS FOR VISITING HUZI PARK]" << endl << "[WELCOME ANY TIME TO BACK]"<< endl << "[I'LL MISS U.]" << endl << "[C U ~]" << endl;
				return 0;
			}
			cerr << "---------------------------------[DOC]--------------------------------------------------------" << endl;
			vd.IndexOutcome(query.c_str());
			cerr << "---------------------------------[SINGER]--------------------------------------------------------" << endl;
			singerDlg.IndexOutcome(query.c_str());//, FILE_TEACHER);
			cerr << "---------------------------------[SONG]--------------------------------------------------------" << endl;
			songDlg.IndexOutcome(query.c_str());//, FILE_TEACHER);
			cerr << "--------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
		}
	}
	//FILE_TEACHER.close();

	return 0;
}
