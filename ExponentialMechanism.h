#pragma once
#include<vector>
#include<map>
#include<algorithm>
#include<cmath>
#include<ctime>
#include<random>
#include<omp.h>
#include"Constants.h"

using namespace std;
class ExponentialMechanism
{
public:
	ExponentialMechanism();
	~ExponentialMechanism();

	pair<int, int> ChooseMaxPrivate(vector<pair<double, pair<int, int>>>& OptionSet, double lambda, double eps, int id);
	pair<int, int> ChhooseMax(vector<pair<double, pair<int, int>>>& OptionSet);
};

