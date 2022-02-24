#pragma once
#include<iostream>
#include<vector>
#include<set>
#include<algorithm>
#include<iterator>
#include"Constants.h"
#include"kMedian.h"
#include"kCenter.h"

class CalcMetrics
{
public:
	CalcMetrics();
	~CalcMetrics();
	double CalcARI();
	double CalcNMI();
	double CalcF(int IsPrivate);
	vector<vector<int>> GetClusters(int IsPrivate);
	void Calc_ns();

	vector<vector<int>> PrivateC;
	vector<vector<int>> NonPrivateC;
	vector<vector<int>> ns;
};

