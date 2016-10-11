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

using namespace std;

int n_cluster = 10;
map<int, vector<double> > clusterSet;
int dimension = 0;

typedef struct { double x, y; int group; } point_t, *point;

int readFile(string filename, vector<vector<double> >& dataVec)
{
	ifstream infile;
	if(spaceGary::open_f(filename, infile) == -1)
	{
		_ERROR("Fail to open file %s\n", filename);
		return -1;
	}

	string line;
	dataVec.clear();
	vector<string> weightArr;
	vector<double> weightArrDou;
	int lineNum = 0;
	while(getline(infile,line))
	{
		spaceGary::StringTrim(line);
		weightArr.clear();
		weightArrDou.clear();
		spaceGary::StringSplit(line, weightArr, " ");
		for (int i = 0; i < weightArr.size(); i++)
		{
			double w = spaceGary::toDouble(weightArr[i]);
			weightArrDou.push_back(w);
		}
		dataVec.push_back(weightArrDou);
		lineNum ++;
		if (dimension == 0)
			dimension = weightArr.size();
		else if(dimension != weightArr.size())
		{
			_ERROR("Dimension of the input file, is not consistent.\n");
			return -1;
		}
	}

	infile.close();

	return lineNum;
}
int gen_dot(string filename, vector<vector<double> >& dataVec)
{
	int lineNum = readFile(filename, dataVec);
	if(lineNum == -1)
	{
		_ERROR("Fail to readFile() ...\n");
		return -1;
	}
	
	return 0;
}

inline double distDot(vector<double> a, vector<double> b)
{
	if(a.size() != b.size())
	{
		_ERROR("SIZE of a and b is not equal...\n");
		return -1;
	}

	double sumSquare = 0;
	for(int i = 0; i < a.size(); i++)
	{
		sumSquare += (a[i] - b[i])*(a[i] - b[i]);
	}

	double dist = sqrt(sumSquare);
	return dist;
}


inline int
InitCent(vector<vector<double> > dataVec, vector<vector<double> >& cent)
{
	if (n_cluster > dataVec.size())
	{
		_ERROR("n_cluster is too large....\n");
		return -1;
	}

	for (int i = 0; i < n_cluster; i ++)
	{
		cent.push_back(dataVec[i]);
	}

	return 0;
}
inline int
nearest(vector<double>& dot, vector<vector<double> >& cent, double *d2, double& cost)
{
	int i, min_i;
	vector<double> c;
	double d, min_d;

	min_d = HUGE_VAL;
	min_i = 0;
	for (int i = 0; i < cent.size(); i++)
	{
		if (min_d > (d = distDot(cent[i], dot))) {
			min_d = d; min_i = i;
		}
	}
	if (d2) *d2 = min_d;
	cost += min_d;
	return min_i;
}
int cluster(vector<vector<double> >& dataVec, vector<vector<double> >& cent, double& cost)
{
	vector<double> dot;
	double *d2;
	int nearestCluster;
	for (int i = 0; i < dataVec.size(); i++)
	{
		dot = dataVec[i];
		nearestCluster = nearest(dot, cent, d2,cost);
		clusterSet[nearestCluster].push_back(i);
	}

	return 0;
}

int Cent(vector<vector<double> > dataVec, vector<vector<double> >& cent)
{
	if (cent.size() != clusterSet.size())
	{
		_ERROR("cent.size != clusterSet.size, please check.\n");
		return -1;
	}
	
	vector<double> vec;
	map<int,vector<double> >::iterator iter;
	for (iter = clusterSet.begin(); iter != clusterSet.end(); iter++)
	{
		int j = iter->first;// center
		vec = iter->second;// children vec position
		for(int k = 0; k < dimension; k++)
		{
			double sum = 0;
			for (int i =0; i < vec.size(); i++)
			{
				sum += clusterSet[i][k];
			}
			double value = sum/(double)n_cluster;
			cent[j][k] = value;
		}
	}

	return 0;
}

#define PTS 100000
#define K 11
int main(int args, char** argv)
{
	int i;
	// filename
	string filename = argv[1];
	// gen vector
	vector<vector<double> > dataVec;
	gen_dot(filename,dataVec);//
	// select century dots
	vector<vector<double> > cent;
	InitCent(dataVec,cent);//
	
	double thres = 1;
	double cost = PTS;
	//while(cost > thres)
	while(1)
	{
		// cluster
		cluster(dataVec, cent,cost);
		// reSelect century dots
		Cent(dataVec, cent);
		// print cost
		_INFO("COST = %f\n", cost);
	}

	return 0;
}
