#include <vector>
#include <string>
#include <iostream>

#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))
#define ABS(a) ((a)>0?(a):(-(a)))
#define DTWVERYBIG 100000000.0


#define DTWMAXNUM 1000
using namespace std;
double **dtwpath;
//double **distance;


double DTWDistanceFun(vector<double>& A, vector<double>& B,int r)
{
	int I = A.size();
	int J = B.size();
	cerr << "I = " << I << endl;
	cerr << "J = " << J << endl;
	cerr << "r = " << r << endl;

    int i,j;
    double dist;
    int istart,imax;
    double g1,g2,g3;
    int pathsig=1;/*路径的标志*/

    /*检查参数的有效性*/
    if(I>DTWMAXNUM||J>DTWMAXNUM){
        //printf("Too big number\n");
        return -1.0;
    }
   	double** distance = new double*[I+1];
	double** dtwpath = new double*[I+1];
	for(int i = 0; i < I + 1; i++)
	{
		distance[i] = new double[J+1];
		dtwpath[i] = new double[J+1];
	}
    /*进行一些必要的初始化*/
    for(i=0;i<I;i++){
        for(j=0;j<J;j++){
            dtwpath[i][j]=0;
            distance[i][j]=DTWVERYBIG;
        }
    }
    
    /*动态规划求最小距离*/
    /*这里我采用的路径是 -------
                              . |
                            .   |
                          .     |
                        .       |
     */
    distance[0][0]=(double)2*ABS(A[0]-B[0]);
    for(i=1;i<=I;i++){
        distance[i][0]=distance[i-1][0]+ABS(A[i]-B[0]);
    }
    for(j=1;j<=J;j++){
        distance[0][j]=distance[0][j-1]+ABS(A[0]-B[j]);
    }
    
    for(j=1;j<=J;j++){
//        istart=j-r2;
//        if(j<=r2)
//            istart=1;
//        imax=j+r2;
//        if(imax>=I)
//            imax=I-1;
//        
        //for(i=istart;i<=imax;i++){
        for(i=1;i<=I;i++){
            g1=distance[i-1][j]+ABS(A[i]-B[j]);
            g2=distance[i-1][j-1]+2*ABS(A[i]-B[j]);
            g3=distance[i][j-1]+ABS(A[i]-B[j]);
            g2=MIN(g1,g2);
            g3=MIN(g2,g3);
            distance[i][j]=g3;
        }
    }
	cerr << "distance  = " << distance[I-1][J-1] << endl;
    dist=distance[I-1][J-1]*(double)(ABS(I-J)+1)/((double)(I+J + 1));
    return dist;
}/*endDTWDistance*/

int main()
{
	vector<double> vec1;
	vector<double> vec2;
	vec1.push_back(1.0);
	vec1.push_back(2.0);
	vec1.push_back(3.0);
	vec1.push_back(1.0);

	vec2.push_back(11.0);
	vec2.push_back(20.0);
	vec2.push_back(3.0);
	vec2.push_back(3.0);
	vec2.push_back(3.0);
	vec2.push_back(3.0);
	vec2.push_back(3.0);
	vec2.push_back(3.0);
	vec2.push_back(3.0);
	vec2.push_back(3.0);
	vec2.push_back(3.0);
	vec2.push_back(3.0);
	vec2.push_back(3.0);
	vec2.push_back(3.0);
	vec2.push_back(3.0);
	vec2.push_back(3.0);
	vec2.push_back(10.0);
	vec2.push_back(10.0);
	vec2.push_back(10.0);
	vec2.push_back(10.0);
	vec2.push_back(10.0);
	//vec2.push_back(10.0);
	//vec2.push_back(10.0);
	//vec2.push_back(10.0);
	//vec2.push_back(10.0);
	//vec2.push_back(10.0);
	//vec2.push_back(10.0);
	//vec2.push_back(10.0);
	//vec2.push_back(10.0);
	//vec2.push_back(10.0);
	//vec2.push_back(10.0);
	//vec2.push_back(10.0);

	cerr << DTWDistanceFun(vec1, vec2, 0) << endl;
	return 0;
}
