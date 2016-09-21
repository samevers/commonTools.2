#ifndef TF_IDF_HEAD_H__
#define TF_IDF_HEAD_H__

#include "../include/general.h"
#include "../include/gary_common/gary_string.h"

class TF_IDF{
	private:
		;
	public:
		int64_t num_doc;
		//std::map<std::string, std::map<std::string, double> > tf;
		std::map<std::pair<std::string, std::string>, double> tf;
		std::map<std::string, int64_t> df;
		std::map<std::string, double> idf;
		//std::map<std::string, std::map<std::string, double> > tf_idf;
		std::map<std::pair<std::string, std::string>, double> tf_idf;
	public:
		TF_IDF();
		~TF_IDF();

		int Init();
		int Train_data_count(std::vector<std::string>& filenames);
		int Tf_Idf_Count();
		int Output_Tf_Idf(std::string& outputfile);
		int run(std::vector<std::string>& filenames, std::string& outputfile);
};
#endif
