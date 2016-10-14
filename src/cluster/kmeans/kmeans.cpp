#include "kmeans.h"

using namespace std;

KMEANS_::KMEANS_(int clusterNum, double thresValue)
{
	n_cluster = clusterNum;
	thres = thresValue;
	dimension = 0;
}
KMEANS_::~KMEANS_()
{
	;
}

int KMEANS_::readFile(string filename, vector<vector<double> >& dataVec)
{
	ifstream infile;
	_INFO("Read File : %s",  filename.c_str());
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
		//cerr << "size of line = " << weightArr.size() << endl;
		eleNumInLine = 0;
		for (int i = 0; i < weightArr.size(); i++)
		{
			double w = spaceGary::toDouble(weightArr[i]);
			if(w > 0)
			{
				eleNumInLine ++;
			}
			weightArrDou.push_back(w);

			// To get Max element of each column.
			if(maxEleVector.size() > 0)
			{
				if(weightArrDou[i] > maxEleVector[i])
					maxEleVector[i] == weightArrDou[i];
			}
		}
		dataVec.push_back(weightArrDou);
		dataVecEleNum.push_back(eleNumInLine);
		if(lineNum ++ % 10 == 0)
			_INFO("%d\n", lineNum);
		if (dimension == 0)
			dimension = weightArr.size();
		else if(dimension != weightArr.size())
		{
			_ERROR("Dimension of the input file, is not consistent.\n");
			return -1;
		}

		// To get Max element of each column.
		if(maxEleVector.size() == 0)
		{
			maxEleVector = weightArrDou;
		}
	}

	infile.close();

	return lineNum;
}
int KMEANS_::gen_dot(string filename, vector<vector<double> >& dataVec)
{
	int lineNum = readFile(filename, dataVec);
	if(lineNum == -1)
	{
		_ERROR("Fail to readFile() ...\n");
		return -1;
	}else
		_INFO("readFile() is ok ...");

//	_INFO("PRINT dataVec Content :");
//	for(int i = 0; i < dataVec.size(); i++)
//	{
//		for (int j = 0; j < dataVec[i].size(); j++)
//			cout << dataVec[i][j] << " ";
//		cout << endl;
//	}

	return 0;
}

double KMEANS_::distDot(vector<double> a, vector<double> b)
{
	if(a.size() != b.size())
	{
		_ERROR("SIZE of a and b is not equal...\n");
		return -1;
	}

	double sumSquare = 0;
	for(int i = 0; i < a.size(); i++)
	{
		//sumSquare += spaceGary::GAbs_(a[i] , b[i]);
		sumSquare += (a[i] - b[i])*(a[i] - b[i]);
	}

	double dist = sqrt(sumSquare);
	return dist;
}

int KMEANS_::InitCentAverage(vector<vector<double> > dataVec, vector<vector<double> >& cent)
{
	// maxEleVector

	if (n_cluster > dataVec.size())
	{
		_ERROR("n_cluster is too large....\n");
		return -1;
	}
	vector<double> tmp(dimension,0);
	vector<double> step(dimension,0);
	for(int j = 0; j < dimension; j++)
	{
		step[j] = maxEleVector[j]/(double)(n_cluster+1);
	}
	for (int i = 0; i < n_cluster; i ++)
	{
		int eleNoneZero = 0;
		for(int j = 0; j < dimension; j++)
		{
			tmp[j] += step[j];
			if (tmp[j] != 0)
				eleNoneZero++;
		}
		cent.push_back(tmp);
		centEleNum.push_back(eleNoneZero);
	}
	cout << "Print InitCentAverage():" << endl;
	for(int i = 0; i < cent.size(); i++)
	{
		for(int j = 0; j < cent[i].size(); j++)
			cout << cent[i][j] << " ";
		cout << endl;
	}
	cout << endl;
	return 0;
}


int KMEANS_::InitCent(vector<vector<double> > dataVec, vector<vector<double> >& cent)
{
	if (n_cluster > dataVec.size())
	{
		_ERROR("n_cluster is too large....\n");
		return -1;
	}

	for (int i = 0; i < n_cluster; i ++)
	{
		cent.push_back(dataVec[i]);
		centEleNum.push_back(dataVecEleNum[i]);
	}

	return 0;
}

int KMEANS_::nearest(vector<double>& dot, int dotEleNum, vector<vector<double> >& cent, double *d2, double& cost)
{
	int i, min_i;
	vector<double> c;
	double d, min_d;

	min_d = HUGE_VAL;
	min_i = 0;
	for (int i = 0; i < cent.size(); i++)
	{
		if (min_d > (d = distDot(cent[i], dot)/(double)(dotEleNum + centEleNum[i]))) {
			min_d = d; min_i = i;
		}
	}
	if (d2) *d2 = min_d;
	// cout << "distDot : " << distDot(cent[min_i], dot) << "\tdotEleNum : " << dotEleNum << "\tcentEleNum : " << centEleNum[min_i] << "\tdist : " << min_d << endl;
	cost += min_d;
	return min_i;
}
int KMEANS_::cluster(vector<vector<double> >& dataVec, vector<vector<double> >& cent, double& cost)
{
	vector<double> dot;
	double *d2;
	int nearestCluster;
	clusterSet.clear();
	for (int i = 0; i < dataVec.size(); i++)
	{
		dot = dataVec[i];
		int dotEleNum = dataVecEleNum[i];
		nearestCluster = nearest(dot,dotEleNum, cent, d2,cost);
		clusterSet[nearestCluster].push_back(i);

//		cout << "current dot : ";
//		for(int j = 0; j < dot.size(); j++)
//			cout << dot[j] << " ";
//		cout << endl;
//		cout << "nearest cent : ";
//		for(int j = 0; j < cent[nearestCluster].size(); j++)
//			cout << cent[nearestCluster][j] << " ";
//		cout << endl << endl;

	}

	return 0;
}

int KMEANS_::Cent(vector<vector<double> > dataVec, vector<vector<double> >& cent)
{
//	if (cent.size() != clusterSet.size())
//	{
//		_ERROR("cent.size != clusterSet.size, please check.\n");
//		return -1;
//	}
	
	vector<int> vecset;
	map<int,vector<int> >::iterator iter;
	for (iter = clusterSet.begin(); iter != clusterSet.end(); iter++)
	{
		int j = iter->first;// center
		centEleNum[j] = 0;
		vecset = iter->second;// children vec position
		for(int col = 0; col < dimension; col++)
		{
			double sum = 0;
			for (int i =0; i < vecset.size(); i++)
			{
				int chi = vecset[i];
				//_INFO("i = %d, col = %d ----4", i,col);
				//_INFO("size of clusterSet[%d].size = %d", i,clusterSet[i].size());
				sum += dataVec[chi][col];
			}
			double value = sum/(double)vecset.size();
			cent[j][col] = value;
			if(cent[j][col] != 0)
			{
				centEleNum[j] ++;
			}
		}
	}

	// print cent content
	cout << "PRINT cent Content :" << endl;
	for(int i = 0; i < cent.size(); i++)
	{
		for (int j = 0; j < cent[i].size(); j++)
			cout << cent[i][j] << " ";
		cout << endl;
	}
	cout << endl;


	return 0;
}

#define PTS 100000
#define K 11
int KMEANS_::Run_(string filename)
{
	int i;
	// gen vector
	_INFO("begin to load data and generate vectors ...");
	vector<vector<double> > dataVec;
	_INFO("Read File : %s",  filename.c_str());
	if(gen_dot(filename,dataVec) == -1)
		return -1;
	_INFO("gen_dot() is ok ...");

	// select century dots
	vector<vector<double> > cent;
	_INFO("Make InitCent() ...");
	if(InitCent(dataVec,cent) == -1)// Outperforms InitCentAverage() method.
		return -1;
	_INFO("InitCent() is ok ...");

	double precost = 0;
	double cost = PTS;
	int iter = 1;
	while(1)
	{
		cost = 0;
		//_INFO("Begin to make cluster() ...");
		if(cluster(dataVec, cent,cost) == -1)
			return -1;
		//_INFO("cluster() is over ...");
		
		// reSelect century dots
		//_INFO("Begin to make Cent() ...");
		if(Cent(dataVec, cent) == -1)
			return -1;
		//_INFO("Cent() is over ...");

		double gabs = spaceGary::GAbs_(cost,precost);
		_INFO("iter = %d, cost = %f, precost = %f, GAbs = %f", iter++, cost, precost, gabs);
		if (gabs < thres)
		{
			break;
		}
		precost = cost;
	}

	// cluster outcome
	ofstream outfile;
	string outFile = filename + ".cluster";
	if(spaceGary::Build_f(outFile, outfile) == -1)
		return -1;
	for(int j = 0; j < cent.size(); j++)
	{
		outfile << "cent dot : ";
		for(int i = 0; i < cent[j].size(); i++)
			outfile << cent[j][i] << " ";
		outfile << endl;
		
		for(int c = 0; c< clusterSet[j].size(); c++)
		{
			int kk = clusterSet[j][c];
			outfile << "\tline:" << kk+1 << "\t";
			for(int cc = 0; cc < dimension; cc++)
				outfile << dataVec[kk][cc] << " ";
			outfile << endl;
		}
		outfile << endl<< endl;
	}
	outfile.close();

	return 0;
}
