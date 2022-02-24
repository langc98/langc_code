#include"ExponentialMechanism.h"

ExponentialMechanism::ExponentialMechanism()
{
	//srand((unsigned)time(NULL));
}

ExponentialMechanism::~ExponentialMechanism()
{
}

int ExponentialMechanism::ChooseMaxPrivate(vector<pair<double,int>>& OptionSet, double lambda, double eps)
{
	int node = -1;
	sort(OptionSet.begin(), OptionSet.end());
	int size = OptionSet.size();
	vector<double> entry(size, 0.0);
	double sum = 0.0;
	for (int i = 0; i < size; ++i)
	{
		entry[i] = exp(0.5 * OptionSet[i].first * eps / lambda);
		sum += entry[i];
	}
	for (int i = 0; i < size; ++i)
		entry[i] /= sum;
	//srand((unsigned)time(NULL));
	//double r = 1.0 * (rand() % 1000) / 1000;
	default_random_engine rn(time(NULL));
	uniform_real_distribution<double> dis(0.0, 1.0);
	double r = dis(rn);
	sum = 0.0;
	for (int i = 0; i < size; ++i)
	{
		sum += entry[i];
		if (sum >= r)
		{
			node = OptionSet[i].second;
			break;
		}
	}
	return node;
}

int ExponentialMechanism::ChhooseMax(vector<pair<double, int>>& OptionSet)
{
	sort(OptionSet.begin(), OptionSet.end());
	int size = OptionSet.size();
	return OptionSet[size - 1].second;
}
