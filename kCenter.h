#pragma once
#include"Constants.h"
#include"ExponentialMechanism.h"

class kCenter :public ExponentialMechanism
{
public:
	kCenter();
	~kCenter();
	void GetSolution(int IsPrivate);
	double CalcValueF(vector<int>& S, int node);
	double lambda;
};

