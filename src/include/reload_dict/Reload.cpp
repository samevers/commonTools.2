#include "Reload.h"
#include "../service_log.hpp"


int ReloadDict::open(unsigned int internal_black_white_list_reload_interval)
{
	_query_class = QueryClass::getInstance(); // 代码单例
	m_refresh_interval = internal_black_white_list_reload_interval; // 词典监测时间间隔
	m_svc_active = true;
	_INFO("[ReloadDict::open] success\n");
	return activate(THR_NEW_LWP, 1);
}

int ReloadDict::stopTask()
{
	m_svc_active = false;
	flush();
	wait();
	return 0;
}
int ReloadDict::svc()
{
	int ret = -1;
	unsigned int resttime = m_refresh_interval;
	_INFO("[ReloadDict::svc] begin to loop...\n");
	while(m_svc_active)
	{
		while(resttime-- > 0 && m_svc_active){sleep(1);}
		if(!m_svc_active) {break;} 
		resttime = m_refresh_interval;

		ret = _query_class->reload_white_black_list_();	// 执行加载命令
		_INFO("[ReloadDict::svc] QueryClass::reload_white_black_list_() ret=%d\n",ret);
	}
	
	_INFO("[ReloadDict::svc] exit svc loop success\n");
	return 0;
}

