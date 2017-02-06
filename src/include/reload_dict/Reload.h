#ifndef RELOAD_H
#define RELOAD_H

#include "QueryClass.h"
#include <ace/Singleton.h>
#include <ace/Synch.h>
#include <ace/Task.h>

class ReloadDict: public ACE_Task<ACE_SYNCH>
{
public:
	static ReloadDict* instance ()
	{
		return ACE_Singleton<ReloadDict, ACE_Recursive_Thread_Mutex>::instance();
	}
	virtual int open (unsigned int internal_black_white_list_reload_interval);
	virtual int stopTask ();
	virtual int svc (void);

protected :
	bool m_svc_active;
	unsigned int m_refresh_interval;
	QueryClass *_query_class;
};
#endif
