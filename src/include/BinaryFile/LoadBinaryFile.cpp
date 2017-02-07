#include <fstream>
#include <iostream>

#include "LoadBinaryFile.h"
#include "service_log.hpp"

using namespace std;

FILEOP::FILEOP()
{}
FILEOP::~FILEOP()
{}


//template < class T >
//bool FILEOP::write_binary_file(std::vector<T>& input, string& outfileName)
bool FILEOP::WriteBinaryFileTest(std::vector<float>& input, string& outfileName)
{
	FILE* FOUT = fopen(outfileName.c_str(), "wb");
	//fwrite(&input[0], sizeof(T),input.size(), FOUT);
	fwrite(&input[0], sizeof(float),input.size(), FOUT);
	fclose(FOUT);

}

bool FILEOP::LoadBinaryFileTest(const char* BinaryFile,float *&pLikely, int32_t& column)
{
	if (NULL == BinaryFile)
	{
		_INFO("binary dict is NULL ");
		return false;
	}

	FILE *fin = fopen(BinaryFile,"rb");
	if (!fin)
	{
		_INFO("Open File %s failed.",BinaryFile);
		return false;
	}
	cout << "=============1" << endl;
	pLikely = new float [column];
	fread(pLikely,sizeof(float),column,fin);
	cout << "=============2" << endl;
	fclose(fin);
	return true;
}

bool FILEOP::WriteBinaryFile(std::vector<vector<float> >& input, string& outfileName)
{
	FILE* FOUT = fopen(outfileName.c_str(), "wb");

	vector<vector<float> >::iterator iter;
	//for(int i = 0; i < input.size(); i++)
	for(iter = input.begin(); iter != input.end(); iter++)
	{
		fwrite(&(*iter)[0], sizeof(float),(*iter).size(), FOUT);
	}
	fclose(FOUT);
	return true;
}



bool FILEOP::LoadBinaryFile(const char* binary_key,const char* binary_value,Darts::DoubleArray* &pQuery,float **&pLikely,int &querycount)
{
	if (NULL == binary_key || NULL == binary_value)
	{
		cerr<< "querylog binary dict is NULL "<<endl;
		return false;
	}
	cerr<<"begine to load querylog binary dict: "<< binary_key << "\t" << binary_value<<endl;

	pQuery=new Darts::DoubleArray();
	int res = pQuery->open(binary_key);
	if (res) 
	{
		cerr << "open file" << binary_key << " failed"  <<endl;
		return false;
	}

	FILE *fin = fopen(binary_value,"rb");
	if (!fin)
	{
		cerr << "open file" << binary_value << " failed" << endl;
		return false;
	}
	int row,colum;
	fread(&row,sizeof(int),1,fin);
	fread(&colum,sizeof(int),1,fin);
	querycount = row;
	pLikely = new float* [row];
	for (int i=0;i<row;i++)
	{
		pLikely[i] = new float [colum];
		fread(pLikely[i],sizeof(float),colum,fin);
	}

	fclose(fin);
	return true;
}
