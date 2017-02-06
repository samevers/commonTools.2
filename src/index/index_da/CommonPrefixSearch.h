#ifndef CONTAIN_SEARCH_H_
#define CONTAIN_SEARCH_H_

#include <string>
#include <vector>
#include <stdint.h>

//namespace spaceCommonPrefixSearch{
#include "darts.h"

//�����������ṹ
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

//������ 
class CommonPrefixSearch 
{
public:

	CommonPrefixSearch();
	~CommonPrefixSearch();
public:
	std::vector<const char *> da_key_vect;
public:
	// �ͷ���Դ
	int32_t Release();

	// ��ԭʼ���ݽ�������
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

	//�õ�������query�г��ֵ��ֵ���Ŀ
	// query�������Ϊȫ���ַ�
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


	// ��˫����������
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


