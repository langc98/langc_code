#pragma once
#include<omp.h>
#include"Constants.h"
#include"ExponentialMechanism.h"

class kCenter :public ExponentialMechanism
{
public:
	kCenter();
	~kCenter();
	vector<int> GetSolution(int IsPrivate, double eps);
	double CalcValueF(vector<int>& S, int node);
	void GetId(int num);
	double lambda;
	int id;
};


