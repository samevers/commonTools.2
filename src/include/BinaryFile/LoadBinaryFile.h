#ifndef FILEOP_HEAD_H__
#define FILEOP_HEAD_H__

#include "general.h"
#include "darts-clone.h"
class FILEOP{
	public:
		FILEOP();
		~FILEOP();
	public:
		//template < class T >
		//bool write_binary_file(std::vector<T>& input, std::string& outfileName);
		bool WriteBinaryFileTest(std::vector<float>& input, std::string& outfileName);
		bool LoadBinaryFileTest(const char* BinaryFile,float *&pLikely, int32_t& column);


		bool WriteBinaryFile(std::vector<std::vector<float> >& input, std::string& outfileName);
		bool LoadBinaryFile(const char* binary_key,const char* binary_value,Darts::DoubleArray* &pQuery,float **&pLikely,int &querycount);
	public:

};

#endif
