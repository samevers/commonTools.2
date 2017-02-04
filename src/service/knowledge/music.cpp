#include "dialogue.h"
using namespace std;

const char* TEACHER_FILE = "../../../data/LearnDlg/learn.log";
// 采用docSearch，可以使得用户Query 不受语序的影响。
const static string Knowledge_DA_IndexFile_DLG = "../../../data/index_dir/knowledge.da.index";
const static string Knowledge_DOC_IndexFile_DLG = "../../../data/index_dir/knowledge.doc.index";



const char* dir_path = "../../../";
int main(int arg, char** argv)
{
	DIALOGUE dlg;
	cerr << "[INFO] Begin to Init dlg" << endl;
	string docFile = Knowledge_DOC_IndexFile_DLG;
	string daFile = Knowledge_DA_IndexFile_DLG;
	if(dlg.Init(dir_path,docFile, daFile) == -1)
	{
		cerr << "[ERROR] Fail to dlg.init()" << endl;
		return -1;
	}
	cerr << "[INFO] Init dlg OK" << endl;
	//string query = argv[1];
	string query;

	// Build a teacher file.
	/*ofstream FILE_TEACHER;
	FILE_TEACHER.open(TEACHER_FILE,ios::out);
	if(!FILE_TEACHER)
	{
		cerr << "[test.cpp][ERROR] Fail to build new learning file." << endl;
		return -1;
	}
	*/
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
			dlg.IndexOutcome(query.c_str());//, FILE_TEACHER);
		}
	}
	//FILE_TEACHER.close();

	return 0;
}
