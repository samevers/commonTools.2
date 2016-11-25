/***dtwrecoge.h*********************************************************************/
#ifndef dtwrecoge_h
#define dtwrecoge_h

#include<stdio.h>
#include<math.h>
#include <string>
#include <vector>
#include <map>
using namespace std;

//#define DTWMAXNUM 2000
#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))
#define ABS(a) ((a)>0?(a):(-(a)))
#define DTWVERYBIG 100000000.0

class DTW_{

	public:
		DTW_();
		~DTW_();
	public:
		/*****************************************************************************/
		/* DTWDistance，求两个数组之间的匹配距离
		/* A,B分别为第一第二个数组，I，J为其数组长度，r为匹配窗口的大小
		/* r的大小一般取为数组长度的1/10到1/30
		/* 返回两个数组之间的匹配距离,如果返回－1.0，表明数组长度太大了
		/*****************************************************************************/
		// double DTWDistanceFun(double *A,int32_t I,double *B,int32_t J,int32_t r);
		double DTWDistanceFun(vector<double>& A, vector<double>& B,int32_t r);
		double DTWDistanceFun(vector<double>& A, int32_t& begin1, int32_t& end1, vector<double>& B, int32_t& begin2, int32_t& end2, int32_t r);
		
		/*****************************************************************************/
		/* DTWTemplate，进行建立模板的工作
		/* 其中A为已经建立好的模板，我们在以后加入训练样本的时候，
		/* 以已建立好的模板作为第一个参数，I为模板的长度，在这个模板中不再改变
		/* B为新加入的训练样本，J为B的长度，turn为训练的次数，在第一次
		/* 用两个数组建立模板时，r为1，这是出于权值的考虑
		/* temp保存匹配最新训练后的模板，建议temp[DTWMAXNUM]，函数返回最新训练后模板的长度
		/* 如果函数返回-1，表明训练样本之间距离过大，需要重新选择训练样本，
		/* tt为样本之间距离的阈值，自行定义
		/*****************************************************************************/
		int32_t DTWTemplate(double *A,int32_t I,double *B,int32_t J,double *temp,int32_t turn,double tt,double *rltdistance);

	public:
		double **dtwpath;
		double **distance;

};


#endif
