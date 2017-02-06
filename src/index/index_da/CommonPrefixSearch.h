#ifndef CONTAIN_SEARCH_H_
#define CONTAIN_SEARCH_H_

#include <string>
#include <vector>
#include <stdint.h>

//namespace spaceCommonPrefixSearch{
#include "darts.h"

//建索引辅助结构
struct EntryTmp{
	std::string query;
	std::string value;

	bool operator < (const EntryTmp& other) const
	{
		return query.compare(other.query) < 0;
	}

	EntryTmp(const std::string& init_query, 
			const std::string& init_value)
	{
		query = init_query;
		value = init_value;
	}
};

//黑名单 
class CommonPrefixSearch 
{
public:

	CommonPrefixSearch();
	~CommonPrefixSearch();
public:
	std::vector<const char *> da_key_vect;
public:
	// 释放资源
	int32_t Release();

	// 对原始数据建立索引
	int32_t MakeIndex(const char * file);

	int32_t ExactSearch(
			const std::string& query,
			std::string& hit,
			std::string& value);
	int32_t CommonPrefixSearch_(
			const std::string& query,
			std::vector<std::string>& hit_string_vect,
			std::vector<std::string>& hit_value_vect,
			int32_t max_hit_num);

	//得到所有在query中出现的字典条目
	// query输入必须为全角字符
	int32_t GetCommonPrefixSearch(
			const std::string& query,
			std::string& hit_string,
			std::string& hit_value,
			int32_t max_hit_num = 1024);

	int32_t GetCommonPrefixSearch(
			const std::string& query,
			std::vector<std::string>& hit_strings,
			std::vector<std::string>& hit_values,
			int32_t max_hit_num = 1024);

	int32_t GetCommonPrefixSearchSeg(
			const std::string& query,
			const std::vector<std::string>& seg_terms,
			std::vector<std::string>& hit_strings,
			std::vector<std::string>& hit_values,
			int32_t max_hit_num = 1024);


	// 在双数组上游走
	int32_t Traverse(
			const char *key, 
			size_t &node_pos, 
			size_t &key_pos, 
			size_t length = 0);

private:
    Darts_0_32::DoubleArray m_darts; 
	std::vector<std::string> m_da_key_vect;
	std::vector<std::string> m_da_value_vect;

	static const int kMaxStrLen = 1024;
	
}; //CommonPrefixSearch

//}
#endif


