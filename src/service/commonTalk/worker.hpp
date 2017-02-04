#ifndef  QO_WORKER_HPP
#define  QO_WORKER_HPP

#include "string"
#include "socket_handle.hpp"
#include "linked_list.hpp"
#include "sso_string/sso_string.h"
#include <map>
#include "vr_base.h"
#include <set>
#include "Base_pool.h"

#define RECEIVED_QC   1
#define RECEIVED_REQUEST  2
#define RECEIVED_VERTICAL 3
#define MAX_HTTP_CONTENT_LENGTH   40960 
#define MAX_VR_TYPE_LEN      128
#define MAX_TYPE_COUNT       10
#define MAX_QC_LENGTH      256

#define QC_URI  "mspider"
#define REQUEST_URI  "request"
#define VERTICAL_URI "meta_vertical"
#define P_GIF   "p.gif"
#define SEARCHHUB_WAIT_TIME_MS 50	// openhub waits 300ms for qo requests. set to 50 to allow some error

const int QC_NOREQUEST = -9;  //��������QC
const int QC_TIMEOUT = -8;  //����QC��ʱ
const int QC_NODATA = -7;  //QC���Ϊ�գ�������ҪQC���������Ϊqcserver���صȼ�

struct VrType{
	char type[MAX_VR_TYPE_LEN];
	char oriPos;
	char sogouPos;
};

struct YYID{
	unsigned long long high;
	unsigned long long low;
};

struct param_info{
    my_sso_string name;
    my_sso_string value;
};

// for performance monitor
enum TimeSteps
{
	TIMEQC,
	TIMEQCEND,
	TIMEGET,        // request entered Query_Processor
	TIMEBRD,  //before read memcache
	TIMEERD, // after read memcache
	TIMEP1, // phase1 finish
	TIMEP2, // phase2 finish
	TIMEP3, // phase3 finish
	TIMEWT, // after write back memcache
	TIMEGETM,
	TIMEGETMEND,
	TIMEMERGE,
	TIMEMERGEEND,
	TIMESENDPUT,
	TIMESENDSVC,
	TIMEMAX
};

struct ClassInfo {
	double final;
	double qofinal;
	double score;
	double lexionProb;
	double querylogProb;
	double querylmProb;
	double corpuslmProb;
	double websearchProb;
	double vssearchProb;
	double intensity;
	std::string className;
	std::string reform;
	std::string innerFixRank;	// �ڲ�vr��̬����Ĺ���λ��, Ĭ����"NULL"
	int shWhite;				// �������Ƿ�����searchub�Ļ��̰����� 1��ʾ���У�0��ʾ������
	int shBlack;				// �������Ƿ�����searchub�Ļ��̺����� 1��ʾ���У�0��ʾ������
	std::string key;			// item query
	std::string data;			// data
	std::string blackLabel;			// data
	int isBlack;			// 0,no;1,yes;
	std::string whiteLabel;			// data
	int isWhite;			// 0,no;1,yes;
	int iswapPc;				// 1,wap; 2,pc;
	int vr_level;				// vr Ȩ������: 0-5;
	int isMatch;	//�Ƿ�Ϊģ������ʶ��

	int queryMatchBlack; //ģ������ʶ�������

	ClassInfo()
	{
		qofinal=0.0;
		score=0.0;
		lexionProb=0.0;
		querylogProb=0.0;
		querylmProb=0.0;
		corpuslmProb=0.0;
		websearchProb=0.0;
		vssearchProb=0.0;
		intensity=0.0;
		shWhite=0;
		shBlack=0;
		isBlack=0;			// 0,no;1,yes;
		isWhite=0;			// 0,no;1,yes;
		iswapPc=0;				// 1,wap; 2,pc;
		vr_level=0;				// vr Ȩ������: 0-5;
		isMatch=0;	//�Ƿ�Ϊģ������ʶ��
		queryMatchBlack=0; //ģ������ʶ�������
	}
};

class Worker : public BASE_POOL_ITEM
{
	public:
		Worker()
		{
			Clear(1);
		}
		virtual ~Worker()
		{
			if(result_len>0)
				free(result);
			v_vrMap.clear();
			classmap.clear();
			vClass.clear();
			blackPre.clear();
			getvalueTime.clear();
			blackSet.clear();
			voiceMap.clear();
			pthread_rwlock_destroy(&vrlist_rwlock);
		}

		void Clear(int is_new=0) 
		{
			if( 0 == is_new )
			{
				if(result_len > 0)
					free(result);
			}
			result = NULL;
			request_id = 0;
			source = -1;
			handle = NULL;
			result_len = -1;

			qc_switch = "false";

			baidutype_count = -1;
			googletype_count = -1;
			qcserver_string = "";
			runString = "";
			queryString = "";
			vrForQc = false;
			qcserver_level = QC_NOREQUEST;
			qc_timeout = 0;
			
			vrWhite = 0;
			vrBlack = 0;
			need_encode = false;
			is_debug = false;
			is_force = false;
			is_cached = false;
			querySource = 1;  // Ĭ��1��ҳ
			locX = 0;
			locY = 0;
			gps = "";
			secondQuery = "";
			recallVrList = 0;
			recallVrWeb = 0;
			vr_abtest = 0;

			vtlistCount = 0;
			usertimeout = 500;

			 isFromBing = 0;
			 needBing = 0;
			 userArea = "";
			 queryDocArea = "";
			 userCity = "";
			 userIP = "";
			 query_type = "";
			 IPAddr = "";
			 metaKeyword = "";
			 forceType = "";
			 qc_switch = "";
			 qcfreq[0] = 0;
			 qcfreq[1] = 0;
			 yyid.low = 0;
			 yyid.high = 0;
			 metaDbg = false;
			 baidu_qc = "";
			 google_qc = "";
			 gpoint = "";
			 vrqo_cost = 0;	//�ܺ�ʱ
			 vrqo_ret = 0;	//vrqo���ر�־
			 vrqo_i = 0;	//�ڲ���ʱ
			 vrqo_x = 0;	//�ⲿ��ʱ
			 vrqo_ql = 0;	//���г���
			 vrqo_tiq = 0;	//�ڶ����е�ʱ��
			 vrqo_presult = 0;	//����xmlʱ��
			 queryRedirect = "";
			 m_UserArea = "";
			 m_UserAreaID = 0;

			 //add by lsk
			 is_health = false;
			 filterphone = 0;


			 result = NULL;
			 			 
			pthread_rwlock_init(&vrlist_rwlock,NULL);
			for(int i=0; i<TIMEMAX; i++)
			{
				memset(&timeSteps[i],0,sizeof(timeval));
			}
			memset(&receive_time,0,sizeof(timeval));
			memset(&qc_time,0,sizeof(timeval));
			v_vrMap.clear();
			classmap.clear();
			vClass.clear();
			blackPre.clear();
			getvalueTime.clear();
			blackSet.clear();
			voiceMap.clear();

			//add by lsk
			seg_terms.clear();

		}

		void * GetMem(size_t size)
		{
			return malloc(size);
		}
		void FreeMem(void * mem)
		{
			free(mem);
		}

		void PushBackSegTerm(const char* term)
		{
			this->seg_terms.push_back(term);
		}

	public:
		int source;
		timeval receive_time;
		timeval qc_time;
		my_sso_string  request;
		my_sso_string uuid;

		my_sso_string queryString;
		my_sso_string qcserver_string;
		bool vrForQc;
		my_sso_string runString;  //ʵ��������ʱ��string������vrForQcѡ����queryString��qcserver_string

		bool needBing;
		bool isFromBing;
		my_sso_string userArea;
		my_sso_string queryDocArea;
		my_sso_string userCity;
		
		my_sso_string userIP;
		//qcserver���ص�level������
		//-2, ԭ��ѯ���а�����������Ҫ����; -1, ԭ��ѯ�����ж�,����Ҫ�����з־���;0, "��"->"�ġ�֮�����ת���Ľ����ֻ��ǰ̨չʾ������Ϊ���β�ѯ; 1, �����Ŷȵȼ�����2,�����Ŷȵȼ�����3,qcrefine�ľ�������4,�ϲ��ո�õ��ľ�������ֻ��Ϊ���β�ѯʹ��,����ǰ̨չʾ;5.���ڳ�ƴ�������������뷨��ѡ�õ��Ľ����ֻ����ԭ��ѯ�޽���������-3 -4���еĽ����Ҳ������
		int qcserver_level;
		int qcfreq[2];
		my_sso_string query_type;
		my_sso_string IPAddr;
		my_sso_string metaKeyword;
		my_sso_string forceType;
		my_sso_string qc_switch;
		int locID;

		struct YYID yyid;
		bool metaDbg;
		long long request_id;


		my_sso_string baidu_qc;
		my_sso_string google_qc;

		VrType baidutype[MAX_TYPE_COUNT];
		int baidutype_count;
		VrType googletype[MAX_TYPE_COUNT];
		int googletype_count;
		int qc_timeout;
			
        char *  result;
		int result_len;
		bool need_encode;
		bool is_debug;
		bool is_force;
		bool is_cached;
		
		//add by lsk
		bool is_health;
		
		//add by lsk for map phone rec
		int filterphone;
		//ɾ���绰��ʣ���query
		std::string delphone_query;

		SocketHandle * handle;	

		linked_list_node_t task_list_node;

		int vrWhite;
		int vrBlack;
		my_sso_string gpoint;
		double locX;
		double locY;
		int querySource;
		int recallVrWeb;
		int recallVrList;
		//ximin 2014/10/23
		my_sso_string gps;
		my_sso_string secondQuery;
		int vr_abtest;
		//litao207264 2015/03/20
		int vrqo_cost;	//�ܺ�ʱ
		int vrqo_ret;	//vrqo���ر�־
		int vrqo_i;	//�ڲ���ʱ
		int vrqo_x;	//�ⲿ��ʱ
		int vrqo_ql;	//���г���
		int vrqo_tiq;	//�ڶ����е�ʱ��
		int vrqo_presult;	//����xmlʱ��

		//�ⲿvr����ˮ
		int vtlistCount;
		int usertimeout;
		//�洢����ˮ�Ľ����inst vr�Ľ��
		std::vector< std::map<my_sso_string, RetRecord> > v_vrMap;
		std::vector<my_sso_string> blackPre;
		std::set<my_sso_string> blackSet;
		pthread_rwlock_t vrlist_rwlock;
		std::map<std::string, ClassInfo> classmap;
		std::vector<ClassInfo> vClass;
		std::map<int, int> getvalueTime;
		char tmp_result[102400];
		my_sso_string queryRedirect;
		
		my_sso_string m_UserArea;
		int m_UserAreaID;
		std::map<my_sso_string,  VoiceRecord> voiceMap;
		timeval timeSteps[TIMEMAX];



		//�ִʽ��
		std::vector<std::string> seg_terms;
};

class WORKER_POOL : public BASE_POOL
{
	public:
		BASE_POOL_ITEM* newItem() { return new Worker(); }
};

extern WORKER_POOL g_worker_pool;


#endif //QO_WORKER_HPP
