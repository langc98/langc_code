#pragma once
#include<vector>
#include<string>
using namespace std;

class Constants
{
public:
	Constants();
	~Constants();
	static double Eps;
	static double Beta;
	static int Alg;
	static int DataSet;
	static int NumOfNodes;
	static int K;
	static int IsMinDist;
	static vector<string> FileNamePrefix;
	static vector<int> PrivateS;
	static vector<int> NonPrivateS;
	static vector<int> PrivateSPre;
	static vector<int> NonPrivateSPre;
	static vector<vector<double>> MinDist;
	static vector<int> StepSize;
};

