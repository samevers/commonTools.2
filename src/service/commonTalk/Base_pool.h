#ifndef _BASE_POOL_H_
#define _BASE_POOL_H_

#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <pthread.h>

class BASE_POOL_ITEM  {
public:
	BASE_POOL_ITEM() {used_times = 0;};
	virtual ~BASE_POOL_ITEM(void) {}
public:
	int used_times;
	virtual void Init() {};
	virtual void Clear(int is_new=0) {};
};

class BASE_POOL {
public:
	BASE_POOL()
	{
		alloc_count = 0;
		free_count = 0;
		max_free_count = 1000;
		item_list.clear();
		pthread_mutex_init(&mutex_pool,NULL);
	};
	virtual ~BASE_POOL()
	{
		close();
		pthread_mutex_destroy(&mutex_pool);
	};
	
	int alloc_count;
	int free_count;
	int max_free_count;
public:
	BASE_POOL_ITEM *get()
	{
		BASE_POOL_ITEM *item = NULL;
		pthread_mutex_lock(&mutex_pool);
		if(item_list.size() > 0)
		{
			item = item_list.front();
			item_list.pop_front();
			--free_count;
		}
		pthread_mutex_unlock(&mutex_pool);
		
		if(item == NULL)
		{
			item = newItem();
			if(item != NULL) ++alloc_count;
		}
		if(item != NULL) item->Init();
		//fprintf(stderr,"fmm_test BASE_POOL_ITEM get\n");
		return(item);
	};
	
	void release(BASE_POOL_ITEM *item)
	{
		//fprintf(stderr,"fmm_test BASE_POOL_ITEM release before\n");
		if(item == NULL) return;
			
		item->Clear();
		pthread_mutex_lock(&mutex_pool);
		if(free_count > max_free_count)
		{
			delete item;
			--alloc_count;
		}
		else
		{
			++free_count;
			item_list.push_back(item);
		}
		pthread_mutex_unlock(&mutex_pool);
		//fprintf(stderr,"fmm_test BASE_POOL_ITEM release after\n");
	};
	
	virtual BASE_POOL_ITEM *newItem() = 0;
	
	void close()
	{
		pthread_mutex_lock(&mutex_pool);
		while(item_list.size() > 0)
		{
			BASE_POOL_ITEM *item = item_list.front();
			item_list.pop_front();
			if(item != NULL) delete item;
		}
		pthread_mutex_unlock(&mutex_pool);
	};
private:
	pthread_mutex_t  mutex_pool;
	std::list<BASE_POOL_ITEM *> item_list;
};

#endif


