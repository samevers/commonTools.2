#ifndef _VR_BASE_H_
#define _VR_BASE_H_

#include <string>
#include <cstring>
#include <vector>
#include <iostream>
#include <stdarg.h>
#include <time.h>
#include <sys/time.h>
#include <boost/algorithm/string.hpp>
#include "sso_string/sso_string.h"

#define MAXTERMCOUNT 500
#define MAXQUERYLEN 80
#define MAXWORDLEN 1000
#define MINWORDLEN 2
#define MAXLINELEN 2000
#define HIT_THRES 0.00001
#define BACKTRACKMAX 8

#define WORD_MATCHPARAM_COUNT 1
#define WORD_RANKPARAM_COUNT 5

#define DEBUG_STATUS 0
#define ERROR_STATUS 0
#define LOG_STATUS 0

//VR来源类别
const int VR_SOURCE_WEB = 1;  //网页
const int VR_SOURCE_WAP = 1 << 1;  //无线
const int VR_SOURCE_IE = 1 << 2;  //IE工具栏
const int VR_SOURCE_YYZS = 1 << 3;  //语音助手
const int VR_SOURCE_IME= 1 << 4;  //输入法
const int VR_SOURCE_BAIKE = 1 << 5;  //百科
const int VR_SOURCE_FINGER = 1 << 6;  //指间搜索
const int VR_SOURCE_BLBS = 1 << 7;  //边聊边搜
const int VR_SOURCE_APP = 1 << 8;  //搜索APP
const int VR_SOURCE_ALL = (VR_SOURCE_WEB | VR_SOURCE_WAP | VR_SOURCE_IE | VR_SOURCE_YYZS | VR_SOURCE_IME | VR_SOURCE_BAIKE | VR_SOURCE_FINGER | VR_SOURCE_BLBS | VR_SOURCE_APP);

static int GetTimeOfDay(struct timeval* tvl, struct timezone* tmp) {
	if (LOG_STATUS > 0)  {
		gettimeofday(tvl, tmp);
	}
	return 0;
}

static int GetTimeDiff(timeval end, timeval start) {
	return (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
}

static int ERR_INFO(const char *fmt, ...) {
        if (ERROR_STATUS != 1) return 1;
        
        va_list argp;
        fprintf(stderr, "[ERROR]:");
        va_start(argp, fmt);
        vfprintf(stderr, fmt, argp);
        va_end(argp);
        fprintf(stderr, "\n");
        return 0;
}       

static int DEBUG_INFO(const char *fmt, ...) {
        if (DEBUG_STATUS != 1) return 1;
        
        va_list argp;
        fprintf(stderr, "[DEBUG]:");
        va_start(argp, fmt);
        vfprintf(stderr, fmt, argp);
        va_end(argp);
        fprintf(stderr, "\n");
        return 0;
}

static int LOGS_INFO(const char *fmt, ...) {
        if (LOG_STATUS != 1) return 1;

        va_list argp;
        fprintf(stdout, "[LOG]:");
        va_start(argp, fmt);
        vfprintf(stdout, fmt, argp);
        va_end(argp);
        fprintf(stdout, "\n");
        return 0;
}

struct WordParamP
{
        const char* m_WordB;
	//const char* m_Data;
        int m_Count;
        double m_MatchValues[WORD_MATCHPARAM_COUNT];
        double m_RankValues[WORD_RANKPARAM_COUNT];
};

typedef struct DocInfoS {
        const char *wordA;
        const WordParamP* wordParam;
} DocInfo;

/*
#define NLP_VRCOUNT 45
static const my_sso_string NLP_VR_MARK[NLP_VRCOUNT] = {
	"map",
//	"map",						// 多点本地
//	"map",						// 多点跨地
//	"music",
	"music.general",
	"music.lyrics",
	"music.general",
	"music.lyrics",
	"video",
	"video",
	"image",	
	"planeticket_null",				// 机票无日期
	"planeticket_date",				// 机票带日期
	"planeticket_date",				// 机票带日期
	"planeticket_date",				// 机票带日期
	"planeticket_date",				// 机票带日期
	"idcard",
	"exchangerate",
	"exchangerate",
	"fangchan",
	"fangchan.zf",
	"fangchan.esf",
	"phonenumber",
	"job",
	"xingzuo",
	"calculator",
	"measure_exchange",
	"calendar",
	"calendar",
	"ip_area",
	"translate",
	"shop",
	"phonenumber",
	"shop.shoe",
	"shop.book",
	"fixedphonenumber",
	"shop.group",
	"novel",
	"novel.leixing",
	"novel.zuozhe",
	//"softgame",
	//"game",
	"app",
	"app.ios",
	"map.interval",
	"expressnumber",
	"barCode",
	"sucai",
	"shop",
	"shop.comment"
};

static const char* NLP_VR_NAME[NLP_VRCOUNT] = {
	"INTERNAL.MAP.ALL",
//	"EXTERNAL.MAP.MLOCAL",
//	"EXTERNAL.MAP.MPLACE",
//	"INTERNAL.MUSIC.ALL",
	"INTERNAL.YINYUE.QQMUSIC",
	"INTERNAL.YINYUE.QQMUSIC",
	"INTERNAL.MUSIC.ALL",
	"INTERNAL.MUSIC.ALL",
	"INTERNAL.VIDEO.ALL",
	"INTERNAL.SOGOU.VIDEO",
	"INTERNAL.IMAGE.ALL",
	"EXTERNAL.TAOBAO.CN_FLIGHT_FLASH",
	"EXTERNAL.QUNAR.CITYTOCITYD",
	"WIRELESS.JIPIAO.LINE",
	"WIRELESS.JIPIAO.SINGLE",
	"EXTERNAL.JIPIAO.INTERNATIONALLINE",
	"EXTERNAL.IDCARD.ALL",
	"EXTERNAL.HUILV.ALL",
	"WIRELESS.huilv.all",
	"INTERNAL.HOUSE.ALL",
	"INTERNAL.HOUSE.RENT",
	"INTERNAL.HOUSE.ESF",
	"EXTERNAL.PHONENUMBER.ALL",
	"INTERNAL.ZHAOPIN.ALL",
	"EXTERNAL.XINGZUO",
	"EXTERNAL.JISUANQI.ALL",
	"EXTERNAL.DULIANGHENG.ALL",
	"EXTERNAL.WANIANLI.QO",
	"EXTERNAL.WANNIANLI.DANGTIAN",
	"EXTERNAL.IPCHAXUN.QO",
	"EXTERNAL.TRANSLATION.LONG",
	"INTERNAL.SHOP.ALL",
	"INTERNAL.PHONENUMBER.ALL",
	"INTERNAL.SHOP.ALL",
	"INTERNAL.SHOP.ALL",
	"INTERNAL.PHONENUMBER.ALL",
	"INTERNAL.TUANGOU.ALL",
	"INTERNAL.SOGOU.BOOK",
	"WIRELESS.XIAOSHUO.LEIXING",
	"WIRELESS.XIAOSHUO.ZUOZHE",
	//"INTERNAL.APP.ALL",
	//"INTERNAL.APP.ALL",
	"INTERNAL.APP.ALL",
	"INTERNAL.IOS.DANDIAN",
	"INTERNAL.MAP.INTERVAL1",
	"EXTERNAL.KUAIDI.NUM2",
	"INTERNAL.TIAOMA.KUAIPAI",
	"INTERNAL.SUCAI.ALL",
	"INTERNAL.SHOP.COMMENT",
	"INTERNAL.SHOP.COMMENT"
};
*/

//const int SOSO_NOVEL_EXTERNAL_VR_COUNT = 9;
//static const my_sso_string SOSO_NOVEL_EXTERNAL_VR[SOSO_NOVEL_EXTERNAL_VR_COUNT] = {  //按优先级由高到低，这些VR需要归一化
//	"INTERNAL.SOSOXIAOSHUO.SOSO",
//	"INTERNAL.SOSOXIAOSHUO.REMEN",
//	"INTERNAL.SOSOXIAOSHUO.ZUIXIN",
//	"INTERNAL.SOSOXIAOSHUO.YELLOW",
//	"INTERNAL.SOSOXIAOSHUO.LEIBIEMING",
//	"INTERNAL.SOSOXIAOSHUO.LEIBIEMING2",
//	"WIRELESS.XIAOSHUO.LEIXING",
//	"WIRELESS.XIAOSHUO.ZUOZHE",
//	"INTERNAL.SOGOU.BOOK"
//};
//
//static const my_sso_string SOSO_NOVEL_EXTERNAL_VR_DATA[SOSO_NOVEL_EXTERNAL_VR_COUNT] = {  //data域中要填的内容
//	"SOSO",
//	"REMEN",
//	"ZUIXIN",
//	"YELLOW",
//	"LEIBIEMING",
//	"LEIBIEMING",
//	"LEIBIEMING",
//	"ZUOZHEMING",
//	"SHUMING"
//};


typedef enum {
	SAME_REGION_FORMAT_BEGIN=0,  
	SAME_REGION_FORMAT_DEFAULT,
	SAME_REGION_FORMAT_COUNT
} SAME_REGION_FORMAT; 

//static const unsigned short PhraseSep = 0xa1a1;    // 

typedef enum {
	RETURN_PARAM_BEGIN=0,                               
	TERM_WEIGHT_PARAM=0,				//      词的权重
	WORDLIST_PARAM1,
	WORDLIST_PARAM2,
	WORDLIST_PARAM3,
	WORDLIST_PARAM4,
	WORDLIST_PARAM5,
	RETURN_PARAM_COUNT
} RETURN_PARAM_ENUM;                                     //      wordlist中的匹配参数,目前有1个

typedef struct RetRecordS{
	my_sso_string query;
	my_sso_string classID;
	my_sso_string syn_list;
	int classNo;
	int rankType;
	int expireTime;
	int isLoc;
	my_sso_string data;
	my_sso_string gid;
	double params[RETURN_PARAM_COUNT];
	int vrFlag;  //10(2)为无线vr，11(3)为网页vr
	int accurateType;  //是否展精准VR
	my_sso_string accurateAttr;  //精准属性
	my_sso_string district;  //原无线使用
	my_sso_string sortRules;
	my_sso_string group_sort;
	my_sso_string tplid;
	int abtest;
	my_sso_string innerFixRank;
	int sortPriority;
	int hitPriority;
	int itemNum;
	int maxGroupNum;
	int group_by;
	int shWhite;
	int shBlack;
	int vr_level;
    //ximin 2014/10/24
    my_sso_string isGps;
	my_sso_string searchScope;
	my_sso_string gpsItemNum;
	int pageTurn;
	int isOrder;
	int sum_status;
	int use_oriword;
	int isRegion;  //是否是地域信息  region为2或4,则为1
	my_sso_string parentId;
	my_sso_string index;
	my_sso_string flowArea;
	my_sso_string flowTag;
	int is_business;
	//add by lsk 20160422
	my_sso_string innerSource;//从内部vr转过来的内部vr tag
	//yy
	int mergeIndex; //merge需求的时候，序号表示优先级

	RetRecordS(){
		classNo = 0;
		rankType = 0;
		expireTime = 0;
		isLoc = 0;
		vrFlag = 0;  //10(2)为无线vr，11(3)为网页vr
		accurateType = 0;  //是否展精准VR
		abtest = 0;
		sortPriority = 0;
		hitPriority = 0;
		itemNum = 0;
		maxGroupNum = 0;
		group_by = 0;
		shWhite = 0;
		shBlack = 0;
		vr_level = 0;
		pageTurn = 0;
		isOrder = 0;
		sum_status = 0;
		use_oriword = 0;
		is_business = 0;
		isRegion = 0;  //是否是地域信息  region为2或4,则为1
		mergeIndex = 0; //merge需求的时候，序号表示优先级
	}


} RetRecord;

//xieyubin  voice xml node
typedef struct VoiceRecordS {
	my_sso_string query;
	my_sso_string tplid; //新样式精准通用模板号
        my_sso_string answerTpl; //语音播报答案模板
        my_sso_string answerOP;  //语音播报答案操作集合
        my_sso_string tplContent; //精准通用模板中具体填写的内容
	my_sso_string jingzhunId;	
	int priority; //优先级

}VoiceRecord;


typedef struct InnerVrInfoS {
	my_sso_string query;
	my_sso_string data;
	my_sso_string innerFixRank;
	int shWhite;
	int shBlack;
	int vr_level;
}InnerVrInfo;

enum PatternManagerType {
	NORMAL,
	INST
};

typedef enum {
	NOT_ACCURATE=0,
	ALL_ACCURATE,  //完全精准
	PART_ACCURATE,  //部分精准
	ATTRIBUTE_ACCURATE  //属性精准
} ACCURATE_TYPE;  //精准VR类别

typedef enum {
	MATCH_PARAM_BEGIN=0,                               
	TERM_WEIGHT=0,					//	词的权重
	MATCH_PARAM_COUNT
} MATCH_PARAM_ENUM;					//	wordlist中的匹配参数,目前有1个

typedef enum {
	RANK_PARAM_BEGIN=0,
	PARAM1=0,                                  	//      词表参数1
	PARAM2,						//      词表参数2
	PARAM3,						//      词表参数3
	PARAM4,						//      词表参数4
	PARAM5,						//      词表参数5
	RANK_PARAM_COUNT                               
} RANK_PARAM_ENUM;                                     //      wordlist中的词表参数,目前有5个

typedef enum {
	HIT_TYPE_BEGIN=0,
	SUB_HIT=0,					//	命中后缀
	PRE_HIT,					//	命中前缀
	COV_HIT,					//	包含命中
	HIT_HIT,					//	精确命中
	FUZ_HIT,					//	模糊命中
	OCV_HIT,
	HIT_TYPE_COUNT
} HIT_TYPE_ENUM;

typedef enum {
	REFINE_TYPE_BEGIN=0,
	DEL_REFINE = 0,				//	删除匹配词
	SUB_REFINE,					//	保留后缀+匹配词
	PRE_REFINE,					//	保留前缀+匹配词
	DELSUB_REFINE,				//	保留后缀
	DELPRE_REFINE,				//	保留前缀
	RPLA_REFINE,                //	替换wordB
	RPLB_REFINE,				//	替换wordA
	NONE_REFINE,				//	不做refine
	REFINE_TYPE_COUNT
} REFINE_TYPE_ENUM;

typedef enum {
	LOGICAL_OP_TYPE_BEGIN=0,
	AND_OP = 0,					//	&&
	OR_OP,						//	||
	NONE_OP,					//	无操作
	LOGICAL_OP_TYPE_COUNT
} LOGICAL_OP_TYPE_ENUM;

typedef enum {
	RULE_ACTION_BEGIN=0,
	FORB_ACTION = 0,			//	命中则不出VR
	SHOW_ACTION,				//  命中则出VR，且参与打分
	RANK_ACTION,				//	命中则出VR，且确定排序
	ACCU_ACTION,				//	分数积累超1.0则出VR
	REFINE_ACTION,
	RULE_ACTION_COUNT
} RULE_ACTION_ENUM;

typedef enum {
	CONF_STAT_BEGIN=0,
	START_STAT = 0,				//	conf文件最外层
	MUTEX_STAT,				//	声明互斥规则
	PATTERN_STAT,				//	声明pattern
	RULE_STAT,				//	声明rule
	STEP_STAT,				//	声明step
	TIMESTAMP_STAT,			//声明timestamp
	CONF_STAT_COUNT
} CONF_STAT_ENUM;

typedef enum {
	WORD_BEGIN = 0,
	MUTEX_WORD=0,
	PATTERN_WORD,
	RULE_WORD,
	STEP_WORD,
	NEW_WORD,
	END_WORD,
	TIMESTAMP_WORD,
	WORD_COUNT
} RESERVED_WORD_ENUM;

typedef enum {
	COMMAND_BEGIN = 0,
	RULE_VRTYPE_COMMAND = 0,
	RULE_NAME_COMMAND,
	RULE_ACTION_COMMAND,
	PATTERN_NAME_COMMAND,
	PATTERN_WORDLIST_NAME_COMMAND,
	DATA_TYPE_COMMAND,
	HIT_OP_COMMAND,
	HIT_TYPE_COMMAND,
	HIT_REFINE_COMMAND,
	HIT_REVERSE_COMMAND,
	REFINE_METHOD_COMMAND,
	RULE_PARAM_COMMAND,
	HIT_PARAM_COMMAND,
	EXTRACT_TYPE_COMMAND,
	FORMAT_TYPE_COMMAND,
	KEY_COUNT_COMMAND,
	BACKTRACK_TYPE_COMMAND,
	RULE_VALUE_REALTIME_COMMAND,
	REGION_COMMAND,
	COMMAND_COUNT
} COMMAND_ENUM;

typedef enum {
	BOOL_BEGIN =0,
	TRUE_BOOL = 0,
	FALSE_BOOL,
	BOOL_COUNT
} BOOL_ENUM;

typedef enum {
	REFINE_METHOD_BEGIN=0,
	FILT_REFINE_METHOD=0,
	EXTRACT_REFINE_METHOD,
	NONE_REFINE_METHOD,
	REFORM_REFINE_METHOD,
	REFINE_METHOD_COUNT
} REFINE_METHOD_ENUM;

typedef enum {
	DATA_TYPE_BEGIN=0,
	MAP_DATA_TYPE = 0,
	LIST_DATA_TYPE,
	INDEX_DATA_TYPE,
	OCV_DATA_TYPE,
	INVERT_DATA_TYPE,
	DATA_TYPE_COUNT
} DATA_TYPE_ENUM;

typedef enum {
	FORMAT_TYPE_BEGIN=0,
	WORDB_PARAM_TYPE = 0,           //      WORDA和WORDB均做归一化
	MATCH_PARAM_TYPE,
	RANK_PARAM_TYPE,
	VRWORDLIST_PARAM_TYPE,          //      WORDA归一化，WORDB不处理
	NONE_PARAM_TYPE,                //      WORDA归一化，无参数
	BINARY_PARAM_TYPE,
	FORMAT_TYPE_COUNT,
	REGION_SAME_TYPE
} FORMAT_TYPE_ENUM;

typedef enum {
	EXTRACT_TYPE_BEGIN=0,
	CONTI_EXTRACT_TYPE = 0,
	SPLIT_EXTRACT_TYPE,
	NONE_EXTRACT_TYPE,
	EXTRACT_TYPE_COUNT
} EXTRACT_TYPE_ENUM;

typedef enum {
        BACKTRACK_TYPE_BEGIN=0,
        CON_NORMAL_TYPE = 0,
	CON_SPECIAL_TYPE,
        SYN_TYPE,
        KEY_TYPE,
	RKEY_TYPE,
	SHOW_TYPE,
	SUB_TYPE,
	OTHER_TYPE,
        BACKTRACK_TYPE_COUNT
} BACKTRACK_TYPE_ENUM;

static const char * HIT_TYPE_NAME[HIT_TYPE_COUNT] = {
	"SUB",
	"PRE",
	"COV",
	"HIT",
	"FUZ",
	"OCV"
};

static const char * REFINE_TYPE_NAME[REFINE_TYPE_COUNT] = {
	"DEL",
	"SUB",
	"PRE",
	"DELSUB",
	"DELPRE",
	"RPLA",
	"RPLB",
	"NONE"
};

static const char * LOGICAL_OP_TYPE_NAME[LOGICAL_OP_TYPE_COUNT] = {
	"AND",
	"OR",
	"NONE"
};

static const char* RULE_ACTION_NAME[RULE_ACTION_COUNT] = {
	"FORB",
	"SHOW",
	"RANK",
	"ACCU",
	"REFINE"
};

static const char * RESERVED_WORD_NAME[WORD_COUNT] = {
	"MUTEX",
	"PATTERN",
	"RULE",
	"STEP",
	"NEW",
	"END",
	"TIMESTAMP"
};

#define SEPERATE_WORD_COUNT 9
static const char SEPERATE_WORD_NAME[SEPERATE_WORD_COUNT] = {
	'|',
	' ',
	'	',
	'\n',
	'<',
	'>',
	'#',
	'=',
	'+'
};

static const char* COMMAND_NAME[COMMAND_COUNT] = {
	"RULE_VRTYPE",
	"RULE_NAME",
	"RULE_ACTION",
	"PATTERN_NAME",
	"PATTERN_WORDLIST",
	"DATA_TYPE",
	"HIT_OP",
	"HIT_TYPE",
	"HIT_REFINE",
	"HIT_REVERSE",
	"REFINE_METHOD",
	"RULE_PARAM",
	"HIT_PARAM",
	"EXTRACT_TYPE",
	"FORMAT_TYPE",
	"KEY_COUNT",
	"BACKTRACK_TYPE",
	"RULE_VALUE_REALTIME",
	"REGION"
};

static const char* BOOL_NAME[BOOL_COUNT] = {
	"TRUE",
	"FALSE"
};

static const char* REFINE_METHOD_NAME[REFINE_METHOD_COUNT] = {
	"FILT",
	"EXTRACT",
	"NONE",
	"REFORM"
};

static const char* DATA_TYPE_NAME[DATA_TYPE_COUNT] = {
	"MAP",
	"LIST",
	"INDEX",
	"OCV",
	"INVERT"
};

static const char* FORMAT_TYPE_NAME[FORMAT_TYPE_COUNT] = {
	"WORDB",
	"MATCH",
	"RANK",
	"VRWORDLIST",
	"NONE",
	"BINARY"
};

static const char* EXTRACT_TYPE_NAME[EXTRACT_TYPE_COUNT] = {
	"CONTI_EXTRACT",
	"SPLIT_EXTRACT",
	"NONE_EXTRACT"
};

static const char* BACKTRACK_TYPE_NAME[BACKTRACK_TYPE_COUNT] = {
	"CON_NORMAL",
	"CON_SPECIAL",
	"SYN",
	"KEY",
	"RKEY",
	"SHOW",
	"SUB",
	"OTHER"
};

static int SplitWord(const my_sso_string& Word, const my_sso_string& Sep, std::vector<my_sso_string>& RetList) {
	RetList.clear();
	my_sso_string wordPiece;
	int startPos = 0;
	int endPos = 0;
	while ((endPos = Word.find(Sep, startPos)) != my_sso_string::npos) {
		wordPiece = Word.substr(startPos, endPos - startPos);
		RetList.push_back(wordPiece);
		startPos = endPos + Sep.length();
	}
	RetList.push_back(Word.substr(startPos, Word.length() - startPos));
	return RetList.size();
}

static int PruneSuffix(my_sso_string &location) {
    int subCount = 26;
    static const char* subList[] = {"省", "市", "自治区", "自治县", "自治州", "直辖市", "维吾尔族", "壮族", "苗族", "彝族",
        "土家族", "藏族", "地区", "朝鲜族", "羌族", "布依族", "侗族", "哈尼族", "傣族", "白族",
        "景颇族", "傈僳族", "回族", "蒙古族", "维吾尔", "哈萨克"};

    bool isHit = true;
    while (isHit) {
        isHit = false;
        const char* pStr = location.c_str();
        int strLen = location.length();
        for (int i = 0; i < subCount; i ++) {
            int subLen = strlen(subList[i]);
            if (subLen > location.length()) continue;
            int index = 0;
            while ((index < subLen) && (pStr[strLen - index - 1] == subList[i][subLen - index - 1])) index ++;

            if (index >= subLen) {
                isHit = true;
                location = location.substr(0, strLen-subLen);
                //_INFO("%s",location.c_str());
                break;
            }
        }
    }
    return 0;
}

static int GetPieceCount(const my_sso_string& Word, const my_sso_string& Sep) {
	int startPos = 0;
	int pieceCount = 1;
//	std::cerr<<"Before dapart:"<<Word<<std::endl;
	while ((startPos = Word.find(Sep,startPos)) != my_sso_string::npos) {
		pieceCount++;
		startPos = startPos + Sep.length();
//		std::cerr<<"Split at: "<<startPos<<"\t";	
	}
//	std::cerr<<std::endl;
	return pieceCount;
}

static int GetVRType(const my_sso_string ClassID) {
	if (ClassID.length() <= 0) return -1;

	char ch = (ClassID.c_str())[0];
	if ((ch >= '1') && (ch <= '2')) {
		return (ch - '0');
	}
	return -1;
}

static my_sso_string FiltRegionInfo(my_sso_string& RegionInfo) {//只保留具体城市名或省名
	my_sso_string regionInfo = "";
	int pos = RegionInfo.find("\t");
	if (pos != my_sso_string::npos) {
		regionInfo = RegionInfo.substr(pos+1);
	}
	else {
		regionInfo = RegionInfo;
	}

	if ((pos = regionInfo.find("市")) == regionInfo.size()-2) {
		regionInfo = regionInfo.substr(0,pos);
	}

        if ((pos = regionInfo.find("地区")) == regionInfo.size()-4) {
                regionInfo = regionInfo.substr(0,pos);
        }

	return regionInfo;
}

#endif
