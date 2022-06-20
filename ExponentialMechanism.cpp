#include"ExponentialMechanism.h"

ExponentialMechanism::ExponentialMechanism()
{
	//srand((unsigned)time(NULL));
}

ExponentialMechanism::~ExponentialMechanism()
{
}

pair<int, int> ExponentialMechanism::ChooseMaxPrivate(vector<pair<double, pair<int, int>>>& OptionSet, double lambda, double eps, int id)
{
	sort(OptionSet.begin(), OptionSet.end());
	int size = OptionSet.size();
	pair<int, int> node = OptionSet[size - 1].second;;
	vector<double> entry(size, 0.0);
	double sum = 0.0;
	for (int i = 0; i < size; ++i)
	{
		entry[i] = exp(0.5 * OptionSet[i].first * eps / lambda);
		sum += entry[i];
	}
	for (int i = 0; i < size; ++i)
		entry[i] = entry[i] / sum;
	srand((unsigned)time(0) - id * 3600);
	double r = 1.0 * (rand() % 1000) / 1000;
//	int id = omp_get_thread_num();
//	default_random_engine rn((unsigned)time(0) - id * 3600);
//	uniform_real_distribution<double> dis(0.0, 1.0);
//	double r = dis(rn);
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

pair<int, int> ExponentialMechanism::ChhooseMax(vector<pair<double, pair<int, int>>>& OptionSet)
{
	sort(OptionSet.begin(), OptionSet.end());
	int size = OptionSet.size();
	return OptionSet[size - 1].second;
}
