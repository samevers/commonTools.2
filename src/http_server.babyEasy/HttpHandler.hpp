#ifndef HANDLER_HPP
#define HANDLER_HPP
#include "HttpResponse.hpp"
#include "worker.hpp"
#include "configuration.hpp"
#include "../locate_getresult/locate_getresult.h"
#include <string>
#include <iostream>
#include <vector>
#include <sys/time.h>
#include "../speechProcessing/similarity.h"
//#include "Da_Search.h"
//#include "Doc_Search.h"

//#include "../query_rewrite/query_rewrite.h"

class Http_Server;

namespace httpserver {

class HttpHandler 
{
    public:
		HttpHandler();
		~HttpHandler();
        virtual int open(Configuration config) {
            return 0;
        }
        int setServer(Http_Server* server);
        virtual int handle_worker(Worker* worker);

		int32_t generate_json_result(
				std::string & json_result, int babyStatus, string& fromObject, string& listen);

	public:
		Similarity *sim;
		int babyStatus;
		int babyStatusNum;
		string  command;
		string motherAudio;
		string babyVoice;
		int code;

		timeval lastCommandTime;
		timeval curCommandTime;
    protected:
        Http_Server* m_server;
        virtual int generate_response(Worker* worker);

	private:
		//LocationResultGet *m_location_result;
		//DA_SEARCH *da_search;
		//DOC_SEARCH *doc_search;

		std::vector<ResultData> locateResult;
		std::string UrlEncode(const std::string& str);
		
		//RewriteResult * m_rewrite_result;
		//ns_query_rewrite::QueryRewrite * 
		//	m_query_rewrite;
};

} // namespace httpserver

#endif
