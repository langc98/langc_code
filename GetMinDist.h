#pragma once
#include<string>
#include<fstream>
#include"Constants.h"


class GetMinDist
{
public:
	GetMinDist();
	~GetMinDist();
	
	vector<vector<double>> min_dist;

	void CalcMinDist();
	void ChooseDataSet();

	string FileName;
};

