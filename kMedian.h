#pragma once
#include"Constants.h"
#include"ExponentialMechanism.h"

class kMedian :public ExponentialMechanism
{
public:
	kMedian();
	~kMedian();
	void GetSolution(int IsPrivate);
	double CalcValueF(vector<int>& S);
	double valueF;
	double lambda;
};

