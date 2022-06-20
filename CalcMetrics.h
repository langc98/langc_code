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
	double CalcDBI(vector<int>& S);
	double CalcSCI(vector<int>& S);
	double CalcDVI(vector<int>& S);
	double CalcPurity();
	double CalcF(vector<int>& S);
	vector<vector<int>> GetClusters(vector<int>& S);
	void Calc_ns(vector<int>& PrivateS, vector<int>& NonPrivates);
	void GetResults(vector<int>& PrivateS, vector<int>& NonPrivateS, vector<vector<double>>& res, int pos);
	vector<vector<int>> PrivateC;
	vector<vector<int>> NonPrivateC;
	vector<vector<int>> ns;
};

