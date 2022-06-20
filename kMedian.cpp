#include"kMedian.h"

kMedian::kMedian() :ExponentialMechanism()
{
	lambda = 2;
	id = 1;
}

kMedian::~kMedian()
{
}

vector<int> kMedian::GetSolution(int IsPrivate, double eps)
{
	double valueF = 0.0;
	vector<int> S;
	
//	int id = omp_get_thread_num();
	srand((unsigned)time(0) - id * 3600);
	vector<pair<double, pair<int, int>>> OptionSet;
	OptionSet.reserve(Constants::NumOfNodes + 1);
	for (int i = 0; i < Constants::K; ++i)
	{
		vector<int> used(Constants::NumOfNodes, 0);
		used[0] = 1;
		for (int v : S)
			used[v] = 1;
		if (Constants::Alg == 3)
		{
			for (int j = 1; j < Constants::NumOfNodes; ++j)
			{
				if (find(S.begin(), S.end(), j) != S.end())
					continue;
				S.push_back(j);
				double value = CalcValueF(S);
				S.pop_back();
				OptionSet.push_back(make_pair(value - valueF, make_pair(j, 0)));
			}
		}
		else
		{
			int numR = 1.0 * (Constants::NumOfNodes + 1.0 - i) / (Constants::K + 1.0 - i) * log(Constants::K / Constants::Beta);
			numR = min(numR, Constants::NumOfNodes - 1 - i);
			vector<int> R;
			int iR = 0;
//			int id = omp_get_thread_num();
			srand((unsigned)time(0) - id * 3600);
			while (iR < numR)
			{
				int v = rand() % Constants::NumOfNodes;
				if (!used[v])
				{
					used[v] = 1;
					R.push_back(v);
					++iR;
				}
			}
			for (int j = 0; j < numR; ++j)
			{
				S.push_back(R[j]);
				double value1 = CalcValueF(S);
				S.pop_back();
				OptionSet.push_back(make_pair(value1 - valueF, make_pair(R[j], 0)));
			}
		}
		pair<int, int> u = { -2,0 };
		if (IsPrivate) {
			u = ChooseMaxPrivate(OptionSet, lambda, eps, id);
		}
		else {
			u = ChhooseMax(OptionSet);
		}
		S.push_back(u.first);
		valueF = CalcValueF(S);
		OptionSet.clear();
	}
	return S;
//	if (IsPrivate)
//		Constants::PrivateS = S;
//	else
//		Constants::NonPrivateS = S;
}

vector<int> kMedian::GetSolution(int IsPrivate, double eps, int flag)
{
	double MaxDis = 0;
	for (int i = 1; i < Constants::NumOfNodes; ++i)
	{
		for (int j = i + 1; j < Constants::NumOfNodes; ++j)
		{
			MaxDis = max(MaxDis, Constants::MinDist[i][j]);
		}
	}
	int T = 6 * Constants::K * log(Constants::NumOfNodes - 1);
	double epss = Constants::K * eps / (T + 1.0);
	vector<vector<int>> S(T);
	srand((unsigned)time(0) - id * 3600);
	while (S[0].size() < Constants::K)
	{
		int r = rand() % Constants::NumOfNodes;
		if (r > 0 && find(S[0].begin(), S[0].end(), r) == S[0].end())
		{
			S[0].push_back(r);
		}
	}
	vector<pair<double, pair<int, int>>> OptionSet, valueS;
	OptionSet.reserve(Constants::NumOfNodes + 1);
	valueS.reserve(T + 1);
	valueS.push_back(make_pair(-1 * CalcValueL(S[0]), make_pair(0, 0)));
	for (int t = 1; t < T; ++t)
	{
		S[t] = S[t - 1];
		for (int i = 0; i < Constants::K; ++i)
		{
			int tmp = S[t][i];
			for (int j = 1; j < Constants::NumOfNodes; ++j)
			{
				if (find(S[t].begin(), S[t].end(), j) != S[t].end())
					continue;
				S[t][i] = j;
				double value = -1 * CalcValueL(S[t]);
				S[t][i] = tmp;
				OptionSet.push_back(make_pair(value, make_pair(i, j)));
			}
		}
		pair<int, int> u = { -2,0 };
		if (IsPrivate) {
			u = ChooseMaxPrivate(OptionSet, MaxDis, epss, id);
		}
		else {
			u = ChhooseMax(OptionSet);
		}
		S[t][u.first] = u.second;
		OptionSet.clear();
		valueS.push_back(make_pair(-1 * CalcValueL(S[t]), make_pair(t, 0)));
	}
	pair<int, int> u = { -2,0 };
	if (IsPrivate)
	{
		u = ChooseMaxPrivate(valueS, MaxDis, epss, id);
//		Constants::PrivateSPre = S[u.first];
	}
	else
	{
		u = ChhooseMax(valueS);
//		Constants::NonPrivateSPre = S[u.first];
	}
	return S[u.first];
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

void kMedian::GetId(int num)
{
	id = num;
}