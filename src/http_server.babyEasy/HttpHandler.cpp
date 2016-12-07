#include "HttpHandler.hpp"
#include "http_server.hpp"
#include "../jsoncpp/json/json.h"
//#include "../chaoli_utility/chaoli_utility.h"
#include "../include/service_log.hpp"
#include <iostream>
#include <string>
#include <iomanip>
extern "C" {
#include "../include/opencore-amr/amrnb/interf_dec.h"
}

using namespace std;

//using namespace ns_chaoli_utility;
static string  DIR_BASE = "../../data";
Json::Value item_test;

namespace httpserver 
{


HttpHandler::HttpHandler()
{
	string voiceBasePath = "./data/";
	sim = new Similarity();
	if(sim->loadData(voiceBasePath) == -1)
	{
		_ERROR("Fail to load voice database sequence. Please check!");
	}
	_INFO("Over loading voice database ...");
	//m_location_result = new LocationResultGet();
	//m_location_result->loaddiclocate();		// 加载我的功能词典
/*	
	da_search = new DA_SEARCH();
	doc_search = new DOC_SEARCH();
	da_search.Init(DIR_BASE.c_str());
	doc_search.Init(DIR_BASE.c_str());
*/	
	gettimeofday(&lastCommandTime, NULL);
	motherAudio = "";
	babyVoice = "";
	command = "0";
	babyStatus = 0;
	babyStatusNum = 0;
	code = 0;
}

HttpHandler::~HttpHandler()
{
	//if(NULL != m_location_result)
	//{
	//	delete m_location_result;
	//	m_location_result = NULL;
	//}

	if(NULL != sim)
	{
		delete sim;
		sim = NULL;
	}
	
}


unsigned char ToHex(unsigned char x)
{
	return  x > 9 ? x + 55 : x + 48;
}


std::string HttpHandler::UrlEncode(const std::string& str)
{
    std::string strTemp = "";
    size_t length = str.length();
    for (size_t i = 0; i < length; i++)
    {
        if (isalnum((unsigned char)str[i]) || 
            (str[i] == '-') ||
            (str[i] == '_') || 
            (str[i] == '.') || 
            (str[i] == '~'))
            strTemp += str[i];
        else if (str[i] == ' ')
            strTemp += "+";
        else
        {
            strTemp += '%';
            strTemp += ToHex((unsigned char)str[i] >> 4);
            strTemp += ToHex((unsigned char)str[i] % 16);
        }
    }
    return strTemp;
}


int HttpHandler::handle_worker(Worker* worker) {
    int ret = generate_response(worker);		// 针对 worker 给出的请求内容，进行后台处理；
    m_server->retrieve_worker(worker);			// 将 处理结果 发送给 worker 返回
    return ret;
}

int HttpHandler::setServer(Http_Server* server) {
    m_server = server;
    return 0;
}


/*int32_t HttpHandler::generate_json_result(
		string & json_result)
{
	json_result = "";

	Json::Value root;
	//Json::Value array_psmt_inputs;
	//Json::Value array_psmt_outputs;
	Json::Value array_result_outputs;
	Json::Value item;
	int returnLen = 10;
	if(returnLen > locateResult.size())
	{
		returnLen = locateResult.size();
	}
	cout << returnLen << endl;

	
	for(int i = 0; i < returnLen; i++)
	{
		Json::Value temp_item;
		temp_item["longitude"]=locateResult[i].lng;
		temp_item["latitude"]=locateResult[i].lat;
		temp_item["title"]=UrlEncode(locateResult[i].title);
		temp_item["url"]=UrlEncode(locateResult[i].url);
		temp_item["source"]=UrlEncode(locateResult[i].source);
		//locateResult[i].datatime = "周末";
		temp_item["datetime"]=UrlEncode(locateResult[i].datatime);
		array_result_outputs.append(temp_item);
		cout << locateResult[i].lng << "\t" << locateResult[i].lat << "\t" << locateResult[i].title << endl;
	}
	root["list"] = array_result_outputs;

	json_result = root.toStyledString();
	//cout << json_result << "\tlitao" << endl;
	return 0;
}
*/

int32_t HttpHandler::generate_json_result(
		string & json_result, int babyStatus,string& fromObject, string& listen)
{
	json_result = "";
	Json::Value root;
	Json::Value array_result_outputs;
	Json::Value item;
	// test
	//babyStatus = 2;

	if(fromObject == "baby")	// from baby
	{
		if(listen == "0")
			item["code"] = 0;
		else if(listen == "1")
		{
			_INFO("command = %s, while baby listening ...", command.c_str());
			item["command"] = command;
			item["code"] = 0;
			item["motherAudio"] = motherAudio;
			_INFO("give audio to baby : %s", motherAudio.c_str());
			motherAudio = "";	// 母亲语音赋值后就清空
			command = "0";
		}
		// test
		//item["motherAudio"] = item_test["motherAudio"];
	}else if(fromObject == "mother") // from mother
	{
		if(listen == "0")
			item["code"] = 0;
		else if(listen == "1")
		{
			item["babyStatus"] = babyStatus;
			item["code"] = 0;
		}
	}
	array_result_outputs.append(item);

//	for(int i = 0; i < returnlen; i++)
//	{
//		json::value temp_item;
//		temp_item["longitude"]=locateresult[i].lng;
//		temp_item["latitude"]=locateresult[i].lat;
//		temp_item["title"]=urlencode(locateresult[i].title);
//		temp_item["url"]=urlencode(locateresult[i].url);
//		temp_item["source"]=urlencode(locateresult[i].source);
//		//locateresult[i].datatime = "周末";
//		temp_item["datetime"]=urlencode(locateresult[i].datatime);
//		array_result_outputs.append(temp_item);
//		cout << locateresult[i].lng << "\t" << locateresult[i].lat << "\t" << locateresult[i].title << endl;
//	}
	//root["list"] = array_result_outputs;
	root = item;
	json_result = root.toStyledString();
	_INFO("json_result : %s\tSam", json_result.c_str());
	return 0;
}

// 返回后台处理逻辑的结果
int HttpHandler::generate_response(Worker* worker) 
{
	if(NULL == worker->response)
	{
		worker->response = new HttpResponse(HTTP10,
				SC200);
	}

	string request = 
		worker->content_buf;

	//_INFO("In generate_response, request: %s", request.c_str());
	Json::Reader reader;
	Json::Value value;

//	string query = "";
//	long double longitude;
//	long double latitude;
//	long double distance;
	string audio;
	string listen;
	int isBaby = 1;	// 默认是婴儿，isBaby=0，表示父母；
	if(reader.parse(request, value))
	{
		//query = value["query"].asString();
		if(worker->request_url == "baby")
		{
			listen = value["listen"].asString();	// 监听
			_INFO("listen : %s", listen.c_str());
			if (listen == "0")// 发送婴儿语音
			{
				babyVoice = value["amrVoice"].asString();	// 语音
				if(babyVoice == "")
				{
					_INFO("App gives a blank voice .... ");
					return -1;
				}
				// output file
				ofstream outfile;
				string amrFile = "tmp/tmp.amr";
				outfile.open(amrFile.c_str(), ios::out);
				outfile << babyVoice << endl;
				outfile.close();
				//cerr << "babyVoice = " << babyVoice << endl;
				
				// Similarity
				// generate tmp/tmp.amr.wav
				if(sim->readint16toWav(amrFile, babyVoice) == -1)
					return -1;
				string fileAmr1 = amrFile + ".wav";
				string emotion;
				if(sim->CalSimilarity(fileAmr1, emotion) == -1)
				{
					return -1;
				}
				_INFO("Emotion : %s" , emotion.c_str());
				if(emotion == "silent")
					babyStatus = 1;	// silent
				else if(emotion == "smile" || emotion == "cry" || emotion == "awake")
					babyStatus = 2;	// awake
				else
				{
					_INFO("babyStatus = %d ---", babyStatus);
				}

				string json_result = "";
				generate_json_result(json_result, babyStatus, worker->request_url, listen);		// 生成 json 数据结果
				worker->response->fillContent(json_result.size(), 	// 读取 json 结果，返回给用户；
						json_result.c_str());

			// cry = 3
			}else if(listen == "1")
			{
				if( command == "1" || command == "2" || command == "3")	// 父母指令高于一切
				{
					_INFO("command > 0, command : %s", command.c_str());
				}else
				{
					if(babyStatus == 2)// 孩子醒着
					{
						gettimeofday(&curCommandTime, NULL);	// CommandTime 是 command = 1 的时间；
						if(curCommandTime.tv_sec - lastCommandTime.tv_sec >= 30)
						{
							command = "1";
							lastCommandTime = curCommandTime;
						}else if(curCommandTime.tv_sec - lastCommandTime.tv_sec < 30 )
						{
							command = "0";
						}else if(babyStatusNum == 0)	// 刚打开app，还没有检测到宝宝awake 的状态；
						{
							command = "1";	// 1 : 播放视频
							babyStatusNum = 1;
							lastCommandTime = curCommandTime;
						}
					}
					else if(babyStatus == 1)
						command = "0";	// 0 : 什么都不做
				}				
				
				string json_result = "";
				generate_json_result(json_result, babyStatus, worker->request_url, listen);		// 生成 json 数据结果
				worker->response->fillContent(json_result.size(), 	// 读取 json 结果，返回给用户；
						json_result.c_str());
			}
		}else if (worker->request_url == "mother")
		{
			isBaby = 0;
			listen = value["listen"].asString();	// 监听
			_INFO("listen : %s", listen.c_str());

			if(listen == "0")	// 发送指令
			{
				motherAudio = value["motherAudio"].asString();	// 母亲语音
				_INFO("motherAudio : %s", motherAudio.c_str());
				command = value["command"].asString();	// 1: 播放视频; 2:播放幻灯片; 3:停止一切播放
				code = 0;
				//if(command == "0")	
				//motherAudio = "0000000000000000000000001";
				string json_result = "";
				generate_json_result(json_result, babyStatus, worker->request_url, listen);		// 生成 json 数据结果
				worker->response->fillContent(json_result.size(), 	// 读取 json 结果，返回给用户；
						json_result.c_str());

			}else if(listen == "1")	// 监听
			{
				string json_result = "";
				generate_json_result(json_result, babyStatus, worker->request_url, listen);		// 生成 json 数据结果
				worker->response->fillContent(json_result.size(), 	// 读取 json 结果，返回给用户；
						json_result.c_str());

			}
		}
		//cerr << "babyVoice = " << babyVoice << endl;
	}
	else
	{
		cerr << "parse json error! " << endl;
	}

    return 0;
}



} // namepspace httpserver
