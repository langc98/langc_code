#pragma once
#include<vector>
#include<map>
#include<algorithm>
#include<cmath>
#include<ctime>
#include<random>
#include"Constants.h"

using namespace std;
class ExponentialMechanism
{
public:
	ExponentialMechanism();
	~ExponentialMechanism();

	int ChooseMaxPrivate(vector<pair<double, int>>& OptionSet, double lambda, double eps);
	int ChhooseMax(vector<pair<double, int>>& OptionSet);
};

