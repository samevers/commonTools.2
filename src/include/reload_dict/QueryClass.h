#include "../general.h"
#include "Reload.h"
#include <sys/stat.h>
#include <time.h>


int QueryClass::reload_white_black_list_()
{
	stringstream oss;
	oss.str("");
	oss <<QUERYCLASS_DIR << "/" << BASE_DIR << "/" << BLACK_LIST_FILE;
	string blacklist_vrqo;
	oss >> blacklist_vrqo;
	
	oss.clear();
	oss.str("");
	oss <<QUERYCLASS_DIR << "/" << BASE_DIR << "/" << BLACK_LIST_INDEX_FILE;
	string index_file;
	oss >> index_file;
	// black
	struct stat statbuf;	// 文件的时间戳
	time_t file_t;
	int check = 0;
	if(stat(index_file.c_str(), &statbuf) == 0)	// 获取文件时间戳
	{
		file_t = statbuf.st_mtime;
		time_t m_now = time(NULL);
		if(m_now - file_t > 5 && file_t > BlackTimeRecord)	// 当前时间-文件时间戳 大于设定值，则进行reload。
		{
			check += 100;
			check += load_black_list_(blacklist_vrqo, index_file) * 2;	// 执行reload。
			BlackTimeRecord = file_t;
		}
	}
	oss.clear();
	oss.str("");
	oss <<QUERYCLASS_DIR << "/" << BASE_DIR << "/" << WHITE_LIST_FILE;
	string whitelist_vrqo;
	oss >> whitelist_vrqo;
	
	oss.clear();
	oss.str("");
	oss <<QUERYCLASS_DIR << "/" << BASE_DIR << "/" << WHITE_LIST_INDEX_FILE;
	oss >> index_file;
	
	if(stat(index_file.c_str(), &statbuf) == 0)
	{
		file_t = statbuf.st_mtime;
		time_t m_now = time(NULL);
		if(m_now - file_t > 5 && file_t > WhiteTimeRecord)
		{
			check += 10;
			check += load_white_list_(whitelist_vrqo, index_file);
			WhiteTimeRecord = file_t;
		}
	}
	return check;
}	

