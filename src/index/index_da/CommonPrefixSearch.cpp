#include "CommonPrefixSearch.h"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

#include "../../include/gary_common/gary_string.h"
#include "../../include/service_log.hpp"
#include "./Index_da.h"
using namespace std;
using namespace spaceGary;
//using namespace spaceCommonPrefixSearch;

CommonPrefixSearch::CommonPrefixSearch()
{
}

CommonPrefixSearch::~CommonPrefixSearch() 
{
}

// 对原始数据建立索引
//输入file格式 query\t prefix|postfix
int32_t CommonPrefixSearch::MakeIndex(
		const char *file
		)
{
	//从输入文件中将数据读出
	FILE * fp_in = fopen(file, "r");
	if (NULL == fp_in) 
	{
		cerr << "can't not open file:" << file <<endl;
		return -1;
	}

	char line[10240];
	int32_t boost_num = 0;
	vector<EntryTmp> da_nodes;
	while (fgets(line, 10240, fp_in)) 
	{
		string str_line = line;
		StringTrim(str_line);
		vector<string> parts_vect;
		StringSplit(str_line, parts_vect, "\t");

		if (parts_vect.size() < 2)
			continue;

		string query = parts_vect[0];
		StringTrim(query);
		string value = parts_vect[1];
		StringTrim(value);
	
		//_INFO("query : %s", query.c_str());
		//_INFO("value : %s", value.c_str());
		if (query.length() > kMaxStrLen) 
		{
			cerr << "black query len max error:" << line;
			continue;
		}
		da_nodes.push_back(EntryTmp(query,value));
	}
	fclose(fp_in);

	// 对phrase结果进行排序
	sort(da_nodes.begin(), da_nodes.end());
//	for(int i = 0; i < da_nodes.size(); i++)	
//	{
//		cout << da_nodes[i].query << "\t" << da_nodes[i].value << endl;
//	}
//	return -1;
	//vector<const char *> da_key_vect;
	vector<int32_t> da_value_vect;
	int index = 0;
	for(vector<EntryTmp>::iterator
			it = da_nodes.begin();
			it != da_nodes.end();
			++it)
	{
		da_key_vect.push_back(it->query.c_str());
		da_value_vect.push_back(index);
		m_da_key_vect.push_back(it->query);
		m_da_value_vect.push_back(it->value);
		//_INFO("da_key_vect.push_back( %s )", it->query.c_str());
		//_INFO("da_value_vect.push_back( %d )", index);
		++index;
	}

	if(m_darts.build(da_key_vect.size(),
				&da_key_vect[0], 0, 
				&da_value_vect[0], NULL) != 0)
	{
		fprintf(stderr, "build da error!\n");
		return -1;
	}

	fprintf(stderr,"load [%s] dict ok!\n",file);
	return 0;
}

int32_t CommonPrefixSearch::ExactSearch(
		const string& query,
		string& hit,
		string& value
		)
{
	Darts_0_32::DoubleArray::result_type result;
	m_darts.exactMatchSearch(query.c_str(),result);
	if(result >= 0)
	{
		hit = m_da_key_vect[result];
		value = m_da_value_vect[result];
	}
	return result;
}


int32_t CommonPrefixSearch::GetCommonPrefixSearch(
		const std::string& query,
		std::string& hit_string,
		std::string& hit_value,
		int32_t max_hit_num)
{
	hit_value = "";
	hit_string = "";
	for(size_t i = 0; i < query.size()/2; ++i)
	{
		string tmp_query = query.substr(i*2);
		vector<string> hit;
		vector<string> hit_value_vect;
		CommonPrefixSearch_(
				tmp_query.c_str(),
				hit,
				hit_value_vect,
				max_hit_num);
		if(hit.size() > 0)
		{
			int max_len = 0;
			int max_index = 0;
			for(size_t i = 0; i < hit.size(); ++i)
			{
				if(hit[i].size() > max_len)
				{
					max_len = hit[i].size();
					max_index = i;
				}
			}

			hit_string = hit[max_index];
			hit_value = hit_value_vect[max_index];
			return 1;
		}
	//	if(hit_string_vect.size() + hit.size() <= max_hit_num)
	//	{
	//		hit_string_vect.insert(hit_string_vect.end(),hit.begin(),hit.end());
	//		hit_value_vect.insert(hit_value_vect.end(),hit_value.begin(),hit_value.end());
	//	}
	//	else
	//	{
	//		for(size_t j = 0; j < hit.size(); j++)
	//		{
	//		}
	//	}
	}

	return 0;
}


int32_t CommonPrefixSearch::GetCommonPrefixSearch(
		const std::string& query,
		std::vector<std::string>& hit_string_vect,
		std::vector<std::string>& hit_value_vect,
		int32_t max_hit_num)
{
	hit_string_vect.clear();
	hit_value_vect.clear();
	//_INFO("query == %s", query.c_str());
	for(size_t i = 0; i < query.size()/2; ++i)
	{
		//string tmp_query = query.substr(i*2,query.length() - i*2);
		string tmp_query = query.substr(i*2);
		//_INFO("tmp_query = %s", tmp_query.c_str());
		vector<string> hit;
		vector<string> hit_value;
		CommonPrefixSearch_(
				tmp_query.c_str(),
				hit,
				hit_value,
				max_hit_num);
		if(hit_string_vect.size() + hit.size() <= max_hit_num)
		{
			hit_string_vect.insert(
					hit_string_vect.end(),
					hit.begin(),
					hit.end()
					);
			hit_value_vect.insert(
					hit_value_vect.end(),
					hit_value.begin(),
					hit_value.end()
					);
		}
		else
		{
			for(size_t j = 0; j < hit.size(); j++)
			{
				if(hit_string_vect.size() >= max_hit_num)
				{
					fprintf(stderr,"match size over %d\n",max_hit_num);
					return 0;
				}
				else
				{
					hit_string_vect.push_back(hit[j]);
					hit_value_vect.push_back(hit_value[j]);
				}
			}
		}
	}

	return 0;
}
int32_t CommonPrefixSearch::GetCommonPrefixSearchSeg(
		const std::string& query,
		const std::vector<std::string>& seg_terms,
		std::vector<std::string>& hit_string_vect,
		std::vector<std::string>& hit_value_vect,
		int32_t max_hit_num)
{
	hit_string_vect.clear();
	hit_value_vect.clear();
	size_t index = 0;
	for(size_t i = 0; i < seg_terms.size(); ++i)
	{
		if(index > query.size())
		{
			hit_string_vect.clear();
			hit_value_vect.clear();
			return -1;
		}
		string tmp_query = query.substr(index);
		//fprintf(stderr,"tmp_query=[%s] index=[%d]\n",tmp_query.c_str(),index);
		index += seg_terms[i].size();

		vector<string> hit;
		vector<string> hit_value;
		CommonPrefixSearch_(
				tmp_query.c_str(),
				hit,
				hit_value,
				max_hit_num);
		if(hit_string_vect.size() + hit.size() <= max_hit_num)
		{
			hit_string_vect.insert(
					hit_string_vect.end(),
					hit.begin(),
					hit.end()
					);
			hit_value_vect.insert(
					hit_value_vect.end(),
					hit_value.begin(),
					hit_value.end()
					);
		}
		else
		{
			for(size_t j = 0; j < hit.size(); j++)
			{
				if(hit_string_vect.size() >= max_hit_num)
				{
					fprintf(stderr,"match size over %d\n",max_hit_num);
					return 0;
				}
				else
				{
					hit_string_vect.push_back(hit[j]);
					hit_value_vect.push_back(hit_value[j]);
				}
			}
		}
	}

	return 0;
}

int32_t CommonPrefixSearch::CommonPrefixSearch_(
		const string& query,
		std::vector<std::string>& hit_string_vect,
		std::vector<std::string>& hit_value_vect,
		int32_t max_hit_num
		)
{
	Darts_0_32::DoubleArray::result_type* result_value =
		new Darts_0_32::DoubleArray::result_type[max_hit_num];
	if(result_value == NULL)
	{
		fprintf(stderr,"alloc result value buffer error!,alloc size is [%d]\n",max_hit_num);
		return -1;
	}

	hit_string_vect.clear();
	//_INFO("query-2 = %s", query.c_str());
	size_t ret_value = m_darts.commonPrefixSearch(
			query.c_str(),result_value,max_hit_num);
	//_INFO("ret_value = %d", ret_value);

	//fprintf(stderr,"33333,ret_value=[%d]\n",ret_value);
	for(size_t i = 0; i < ret_value; i++)
	{
		//_INFO("da_key_vect = %s", da_key_vect[result_value[i]]);
		//_INFO("result_value[%d] = %d",i, result_value[i]);
		if(m_da_key_vect.size() <= result_value[i] || 
				m_da_value_vect.size() <= result_value[i])
		{
			//_INFO("result_value[%d] = %d, continue.",i, result_value[i]);
			continue;
		}

		//_INFO("m_da_key_vect = %s", m_da_key_vect[result_value[i]].c_str());
		//_INFO("m_da_value_vect = %s", m_da_value_vect[result_value[i]].c_str());

		hit_string_vect.push_back(m_da_key_vect[result_value[i]]);
		hit_value_vect.push_back(m_da_value_vect[result_value[i]]);
	}

	delete []result_value;

	return hit_string_vect.size();
}


// 在双数组上游走
int32_t CommonPrefixSearch::Traverse(
		const char * key, size_t & node_pos, 
		size_t &key_pos, size_t length) 
{
	return 
		m_darts.traverse(key, node_pos, key_pos, length);

}

