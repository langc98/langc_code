#pragma once
#include<omp.h>
#include"Constants.h"
#include"ExponentialMechanism.h"

class kMedian :public ExponentialMechanism
{
public:
	kMedian();
	~kMedian();
	vector<int> GetSolution(int IsPrivate, double eps);
	vector<int> GetSolution(int IsPrivate, double eps, int flag);
	double CalcValueF(vector<int>& S);
	double CalcValueL(vector<int>& S);
	void GetId(int num);
	double lambda;
	int id;
};

