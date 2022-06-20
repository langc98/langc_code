#pragma once
#include"Constants.h"
#include<iostream>
#include<fstream>

class WriteToFile
{
public:
	WriteToFile();
	~WriteToFile();
	void WriteFile(double eps, vector<double> res, int flag);
};

