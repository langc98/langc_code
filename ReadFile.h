#pragma once
#include"Constants.h"
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<cmath>
#include<algorithm>
#include<ctime>

class ReadFile
{
public:
	ReadFile();
	~ReadFile();

	vector<vector<double>> Graph_Data;
	void ChooseDataSet();
	void GetMatrix();
	
	int num;
	string FileName;
};

