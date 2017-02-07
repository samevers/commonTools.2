#ifndef NEWTON_METHOD_H__
#define NEWTON_METHOD_H__

#include "../../general.h"

class NEWTON_{

	public:
		NEWTON_(float ydst_, float thres, int32_t iterLimit_ );
		~NEWTON_();

	public:
		float preY;
		float preX;
		float preDeri;
		int32_t iterLimit;
		float threshold;
		float ydst;
	public:
		int Init();
		float func(float x0);
		float Derivative(float x0);
		float Converge(float xInit);
		int Release();
};
#endif

