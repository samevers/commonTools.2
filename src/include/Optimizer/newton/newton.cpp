#include "newton.h"
#include <math.h>
#include "../../service_log.hpp"
#include "../../gary_common/gary_math.h"
using namespace std;

NEWTON_::NEWTON_(float ydst_, float thres, int32_t iterLimit_ )
{
	threshold = thres;
	iterLimit = iterLimit_;
	preY = 0;
	preDeri = 0;
	ydst = ydst_;
	_INFO("threshold = %f, iterLimit = %d", threshold, iterLimit);
}
NEWTON_::~NEWTON_()
{}

int NEWTON_::Init()
{
}

int NEWTON_::Release()
{
	;
}

float NEWTON_::func(float x0)
{
	//float y0 = 2 * pow(x0,3) + pow(x0,2) + x0 + 1;
	float y0 = 1+ cos(3*x0)+ 1;
	return y0;
}
// f(x) = 2x^3 + x^2 + x + 1
// derivative = 6x*x + 2*x + 1;
float NEWTON_::Derivative(float x0)
{
	//float derivative = 6 * pow(x0,2) + 2 * x0 + 1;
	float derivative = -3*sin(3*x0);
	return derivative;
}


// Calculate the miValue of the function.
float NEWTON_::Converge(float xInit)
{
	float x0 = xInit;
	float y0 = func(x0);
	_INFO("x = %f, y = %f", x0, y0);
	int32_t iterNum = 0;
	while(iterNum++ < iterLimit)
	{
		_INFO("iter = %d", iterNum);
		float derivative = Derivative(x0);
		y0 = func(x0);
		
		float x = x0 - y0 / derivative;
		_INFO("new x = %f", x);
		float y = func(x);
		_INFO("new y = %f", y);
		_INFO("new derivative = %f", derivative);
	
		_INFO("preY = %f , y = %f, preX = %f, x = %f, abs change = %f", preY, y,preX, x, spaceGary::GAbs_(preX, x));
		if(iterNum > 10 && spaceGary::GAbs_(y, ydst) < threshold)
		{
			_INFO("when x = %f, y = %f  is most close to ydst:%f", x, y, ydst);
			return x;
		}
		preY = y;
		preX = x;
		preDeri = derivative;
		x0 = x;
	}	
	return 0;
}

int main()
{
	// EXLANATION:
	// Init value of x = 2.5
	// when abs(y-ydst) <= 0.01, break;
	// Iter num <= 200;
	// Dest: when y is most close to ydst, x should be what value ?
	NEWTON_ nt(2.5, 0.01, 200);
	nt.Init();

	float x0 = 0.25;
	float x_close = nt.Converge(x0);
	_INFO("x_close = %f", x_close);
	return 0;

}
