#ifndef __KMEANS_HEAD_H__
#define __KMEANS_HEAD_H__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <math.h>
#include "../../include/service_log.hpp"
#include "../../include/gary_common/gary_string.h"
#include "../../include/gary_common/gary_common.h"
#include "../../include/gary_common/gary_math.h"

class KMEANS_{
	private:
		int dimension;
		std::map<int, std::vector<int> > clusterSet;
		std::vector<int> dataVecEleNum;//每个文本向量中词的个数
		std::vector<int> centEleNum;	// cent中每个文本向量中词的个数
		int eleNumInLine;
		double thres;
	public:
		KMEANS_(int clusterNum, double thresValue = 0.001);
		~KMEANS_();
	public:
		int n_cluster;

	public:
		int readFile(std::string filename, std::vector<std::vector<double> >& dataVec);
		int gen_dot(std::string filename, std::vector<std::vector<double> >& dataVec);
		double distDot(std::vector<double> a, std::vector<double> b);
		int InitCent(std::vector<std::vector<double> > dataVec, std::vector<std::vector<double> >& cent);
		int nearest(std::vector<double>& dot, int dotEleNum, std::vector<std::vector<double> >& cent, double *d2, double& cost);
		int cluster(std::vector<std::vector<double> >& dataVec, std::vector<std::vector<double> >& cent, double& cost);
		int Cent(std::vector<std::vector<double> > dataVec, std::vector<std::vector<double> >& cent);
		int Run_(std::string filename);
};

#endif

