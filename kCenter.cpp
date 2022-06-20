#include"kCenter.h"

kCenter::kCenter() :ExponentialMechanism()
{
	lambda = 1;
	id = 1;
}


kCenter::~kCenter()
{
}

vector<int> kCenter::GetSolution(int IsPrivate, double eps)
{
	vector<int> S;
	srand((unsigned)time(0) - id * 3600);
	S.push_back(rand() % Constants::NumOfNodes);
//	S.push_back(0);

	vector<pair<double, pair<int, int>>> OptionSet;
	OptionSet.reserve(Constants::NumOfNodes + 1);
	for (int i = 1; i < Constants::K; ++i)
	{
		vector<int> used(Constants::NumOfNodes, 0);
		for (int v : S)
			used[v] = 1;
		//double MinDist = 1e9;
		pair<int, int> u = { -2,0 };
		
		if (Constants::Alg == 1)
		{
			for (int j = 0; j < Constants::NumOfNodes; ++j)
			{
				if (find(S.begin(), S.end(), j) != S.end())
					continue;
				double MinDist = CalcValueF(S, j);
				OptionSet.push_back(make_pair(MinDist, make_pair(j, 0)));
			}
		}
		else
		{
			int numR = 1.0 * (Constants::NumOfNodes + 1.0 - i) / (Constants::K + 1.0 - i) * log(Constants::K / Constants::Beta);
			numR = min(numR, Constants::NumOfNodes - i);
			vector<int> R;
			int iR = 0;
		//	int id = omp_get_thread_num();
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
				double MinDist = CalcValueF(S, R[j]);
				OptionSet.push_back(make_pair(MinDist, make_pair(R[j], 0)));
			}
		}
		u = { -2,0 };

		if (IsPrivate) {
			u = ChooseMaxPrivate(OptionSet, lambda, eps, id);
		}
		else {
			u = ChhooseMax(OptionSet);
		}
		S.push_back(u.first);
		OptionSet.clear();
	}
	return S;
//	if (IsPrivate) 
//		Constants::PrivateS = S;
//	else 
//		Constants::NonPrivateS = S;
}

double kCenter::CalcValueF(vector<int>& S, int node)
{
	int nS = S.size();
	double Radius = 0.0;
	int left = node < 0 ? 0 : node;
	int right = node < 0 ? Constants::NumOfNodes : (node + 1);
	for (int j = left; j < right; ++j)
	{
		double MinDist = 1e8;
		int index = 0;
		for (int k = 0; k < nS; ++k)
		{
			if (S[k] == j)
			{
				index = 1;
				break;
			}
			if (MinDist >= Constants::MinDist[j][S[k]])
			{
				MinDist = Constants::MinDist[j][S[k]];
			}
		}
		if (index)
			continue;
		Radius = max(Radius, MinDist);
	}
	return Radius;
}

void kCenter::GetId(int num)
{
	id = num;
}