#include <stdio.h>
#include <stdlib.h>
#include "HttpClient.hpp"
#include "HttpRequest.hpp"
#include <service_log.hpp>
#include <strings.h>
#include <sys/time.h>
#include <string>
#include <fstream>
#include <vector>
#include "../include/gary_common/gary_string.h"
//#include "gtest/gtest.h"
//#include "gflags/gflags.h"
//#include "glog/logging.h"
#include <iostream>
#include "../jsoncpp/json/json.h"
extern "C" {
//#include <interf_dec.h>
#include "../include/opencore-amr/amrnb/interf_dec.h"
}

//using namespace ns_chaoli_utility;

using namespace std;

string FLAGS_query = "dahuashueihu";
string FLAGS_input = "query.input";
/* From WmfDecBytesPerFrame in dec_input_format_tab.cpp */
const int sizes[] = { 12, 13, 15, 17, 19, 20, 26, 31, 5, 6, 5, 5, 0, 0, 0, 0 };


int postdo(string& line)
{
	int loc;
	while((loc = line.find("\r")) != -1)
	{
		line = line.replace(loc, 1, "");
	}
	return 0;
}

int readAmr2int16(string& filename, string& speechLine) {

	FILE* in = fopen(filename.c_str(), "rb");
	if (!in) {
		_ERROR("Fail to open file < %s >" ,filename.c_str());
		return -1;
	}
	char header[6];
	int n = fread(header, 1, 6, in);
	if (n != 6 || memcmp(header, "#!AMR\n", 6)) {
		_ERROR("Bad header, amr2wav FAILS.");
		return 1;
	}

	void* amr = Decoder_Interface_init();
	string content = "";
	stringstream os;
	os.str("");
	while (true) {
		uint8_t buffer[500];
		/* Read the mode byte */
		n = fread(buffer, 1, 1, in);
		if (n <= 0)
			break;
		/* Find the packet size */
		int size = sizes[(buffer[0] >> 3) & 0x0f];
		if (size <= 0)
			break;
		n = fread(buffer + 1, 1, size, in);

		if (n != size)
			break;

		/* Decode the packet */
		int16_t outbuffer[160];
		Decoder_Interface_Decode(amr, buffer, outbuffer, 0);
		for (int i = 0; i < 160; i++) 
		{
			os << outbuffer[i] << "\t";
			//cout << outbuffer[i];
		}
		os << "##_##";
	}
	speechLine = os.str();
	//cout << speechLine << endl; 
	fclose(in);
	Decoder_Interface_exit(amr);
	return 0;
}


int test_file()
{
    HttpClient client(50, 50, 300);
    client.connect_server("127.0.0.1", 20166);
    //client.connect_server("10.138.76.30", 65668);
	
	string s;
	int line_num = 0;
	vector<string> parts;
	timeval start_time,end_time;

	string filename = "amr.amr";
	string voiceContent;
	readAmr2int16(filename, voiceContent);//
	//cout << voiceContent << endl;
	Json::Value root;
	Json::Value array_obj;
	Json::Value item;
	
	root["amrVoice"] = voiceContent;
	//cerr << root["amrVoice"] << endl;
	//root["query"] = UrlEncode("hello server");
	//root["request_id"]=UrlEncode("httpclient");
	string send_str = root.toStyledString();

   	HttpRequest req(HTTP10, POST, "/mspider");
	req.fillContent(
			send_str.size(),
			send_str.c_str());
   	char buf[409600];
   	int len = -1;
   	req.dump_to_buff(buf, 409600, len);

	//cout<<"send buffer len is : "<<len<<endl;
	//cout<<"send buffer is:\n"<<buf<<endl;

	//string query = root["query"].toStyledString();
	//cerr<<"send query is:\n"<<UrlDecode(query)<<endl;

	//_INFO("encode http request cost %d",WASTE_TIME_US(start_time));
	std::string header;
	char body_buf[40960];
	uint32_t body_len = 0;
   	client.send(buf, len);
	
	return 0;
	//_INFO("send http request cost %d",WASTE_TIME_US(start_time));
	int32_t ret = client.recv(
			header,
			body_buf,
			40960,
			body_len
			);
//	_INFO("recevie result cost %d",WASTE_TIME_US(start_time));

	//cout << "header:" <<
	//	header << endl;
	//cout << "body len:" <<
	//	body_len << endl;
	//cout << "body buf:" <<
	//	body_buf << endl;

	string content_buf = body_buf;
	cout << content_buf << endl;

	int32_t index_pos = content_buf.find("{");

	if(index_pos != -1)
		{
			content_buf = content_buf.substr(index_pos);
		}
		else
		{
			cerr << "find error!" << endl;
			return 0;
		}

		//_INFO("[query=%s,cost=%d]",parts[0].c_str(),WASTE_TIME_US(start_time));

		Json::Reader reader;
		Json::Value value;
		if(reader.parse(content_buf, value))
		{
			cout << "value size:" << 
			value["test"].size() << endl;
			string temp_str = value["test"].asString();
			cout << "result is:" << temp_str << endl;
		}
		else
		{
			cerr << "parse error!" << endl;
		}

		//_INFO("parse result cost %d",WASTE_TIME_US(start_time));

	//	sleep(1);

	//}
	client.disconnect();

	return 0;
}


int main(int argc, char* argv[]) 
{
//	google::AllowCommandLineReparsing();
//	google::ParseCommandLineFlags(&argc, &argv, true);
//	::testing::InitGoogleTest(&argc, argv);
//	google::InitGoogleLogging(argv[0]);
//	FLAGS_log_dir = "../../log";
	/*
    sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_port = htons(62668);
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
	*/
	time_t m_now = time(NULL);
	//cout << m_now << endl;
	timeval rule_stime;
	gettimeofday(&rule_stime, NULL);
	//cout << rule_stime.tv_sec << endl;
	int num = 0;
	if(argc < 2 )
	{
		while(num++ < 1)
			test_file();
	}
	else
	{
	//	FLAGS_query = argv[1];

	//    HttpClient client(50, 500, 500);
	//    client.connect_server("127.0.0.1", 62666);
	//    //client.connect_server("10.16.129.100", 62666);
	//
	//	timeval start_time;
	//	gettimeofday(&start_time,NULL);
	//
	//	Json::Value root;
	//	Json::Value array_obj;
	//	Json::Value item;
	//
	//	root["query"] = UrlEncode(FLAGS_query);
	//	root["request_id"]=UrlEncode("httpclient");
	//
	//	string send_str = root.toStyledString();
	//
	//	//cout << "send_str:" << send_str;
	//
	//    HttpRequest req(HTTP10, POST, "/mspider");
	//	req.fillContent(
	//			send_str.size(),
	//			send_str.c_str());
	//    char buf[40960];
	//    int len = -1;
	//    req.dump_to_buff(buf, 40960, len);
	//	//_INFO("encode http request cost %d",WASTE_TIME_US(start_time));
	//
	//	std::string header;
	//	char body_buf[40960];
	//	uint32_t body_len = 0;
	//    client.send(buf, len);
	//
	//	//_INFO("send http request cost %d",WASTE_TIME_US(start_time));
	//
	//	int32_t ret = client.recv(
	//			header,
	//			body_buf,
	//			40960,
	//			body_len
	//			);
	//
	//	//_INFO("recevie result cost %d",WASTE_TIME_US(start_time));
	//
	//	//cout << "header:" <<
	//	//	header << endl;
	//	//cout << "body len:" <<
	//	//	body_len << endl;
	//	//cout << "body buf:" <<
	//	//	body_buf << endl;
	//
	//	string content_buf = body_buf;
	//
	//	int32_t index_pos = content_buf.find("{");
	//
	//	if(index_pos != -1)
	//	{
	//		content_buf = content_buf.substr(index_pos);
	//	}
	//	else
	//	{
	//		cerr << "find error!" << endl;
	//		return 0;
	//	}
	//	
	//	//_INFO("send and receive cost %d",WASTE_TIME_US(start_time));
	//	_INFO("[query=%s,cost=%d]",FLAGS_query.c_str(),WASTE_TIME_US(start_time));
	//
	//	//Json::Reader reader;
	//	//Json::Value value;
	//	//if(reader.parse(content_buf, value))
	//	//{
	//	//	cout << "value size:" << 
	//	//		value["psmt_outputs"].size() << endl;
	//	//	for(int32_t i = 0; i < 
	//	//			value["psmt_outputs"].size(); i++)
	//	//	{
	//	//		string temp_str = UrlDecode(value["psmt_outputs"][i]["dest"].asString());
	//	//		cout << "result is:" << temp_str << endl;
	//	//	}
	//	//}
	//	//else
	//	//{
	//	//	cerr << "parse error!" << endl;
	//	//}

	//	client.disconnect();
	//
		//_INFO("parse result cost %d",WASTE_TIME_US(start_time));
	}


	//fprintf(stdout, "%s\n", buf);
 //   _INFO("req str=\n%s", buf);
    return 0;
}
