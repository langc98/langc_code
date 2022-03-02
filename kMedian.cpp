#include"kMedian.h"

kMedian::kMedian() :ExponentialMechanism()
{
	lambda = 1;
}

kMedian::~kMedian()
{
}

void kMedian::GetSolution(int IsPrivate, double eps)
{
	int pos = -1;
	double valueF = 0.0;
	vector<int> S;
	srand((unsigned)time(NULL));
	vector<pair<double, int>> OptionSet;
	for (int i = 0; i < Constants::K; ++i)
	{
		for (int j = 1; j < Constants::NumOfNodes; ++j)
		{
			if (find(S.begin(), S.end(), j) != S.end())
				continue;
			S.push_back(j);
			pos = j;
			double value = CalcValueF(S);
			S.pop_back();
			OptionSet.push_back(make_pair(value - valueF, pos));
		}
		int u = -2;
		if (IsPrivate) {
			u = ChooseMaxPrivate(OptionSet, lambda, eps);
		}
		else {
			u = ChhooseMax(OptionSet);
		}
		S.push_back(u);
		valueF = CalcValueF(S);
		OptionSet.clear();
	}
	if (IsPrivate)
		Constants::PrivateS = S;
	else
		Constants::NonPrivateS = S;
}

double kMedian::CalcValueF(vector<int>& S)
{
	S.push_back(0);
	int nS = S.size();
	double sum = 0.0;
	for (int j = 1; j < Constants::NumOfNodes; ++j)
	{
		double MinDist = 1e9;
		for (int k = 0; k < nS; ++k)
		{
			if (S[k] == j)
			{
				MinDist = 0;
				break;
			}
			if (MinDist > Constants::MinDist[j][S[k]])
			{
				MinDist = Constants::MinDist[j][S[k]];
			}
		}
		sum += (Constants::MinDist[0][j] - MinDist);
	}
	S.pop_back();
	return sum / (Constants::NumOfNodes - 1.0);
}

double kMedian::CalcValueL(vector<int>& S)
{
	int nS = S.size();
	double sum = 0.0;
	for (int j = 1; j < Constants::NumOfNodes; ++j)
	{
		double MinDist = 1e9;
		for (int k = 0; k < nS; ++k)
		{
			if (S[k] == j)
			{
				MinDist = 0;
				break;
			}
			if (MinDist > Constants::MinDist[j][S[k]])
			{
				MinDist = Constants::MinDist[j][S[k]];
			}
		}
		sum += MinDist;
	}
	return sum / (Constants::NumOfNodes - 1.0);
}
