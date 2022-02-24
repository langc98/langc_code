#include"kCenter.h"

kCenter::kCenter() :ExponentialMechanism()
{
	lambda = 1;
}

kCenter::~kCenter()
{
}

void kCenter::GetSolution(int IsPrivate)
{
	
	vector<int> S;
	srand((unsigned)time(NULL));
	int u = rand() % Constants::NumOfNodes;
	S.push_back(u);
	vector<pair<double, int>> OptionSet;
	for (int i = 1; i < Constants::K; ++i)
	{
		//double MinDist = 1e9;
		int nS = S.size();
		
		for (int j = 0; j < Constants::NumOfNodes; ++j)
		{
			/*
			MaxDist = 0.0;
			int pos = -1;
			int index = 0;
			for (int k = 0; k < nS; ++k)
			{
				if (S[k] == j)
				{
					index = 1;
					break;
				}
				if (MinDist > Constants::MinDist[j][S[k]])
				{
					MinDist = Constants::MinDist[j][S[k]];
					pos = j;
				}
			}
			if (index)
				continue;
			pos = j;
			OptionSet.push_back(make_pair(MinDist, pos));
			*/
			//*
			if (find(S.begin(), S.end(), j) != S.end())
				continue;
			double MinDist = CalcValueF(S, j);
			OptionSet.push_back(make_pair(MinDist, j));
			//*/
		}
		u = -1;
		if (IsPrivate) {
			u = ChooseMaxPrivate(OptionSet, lambda, Constants::Eps);
		}
		else {
			u = ChhooseMax(OptionSet);
		}
		S.push_back(u);
		OptionSet.clear();
	}
	if (IsPrivate) 
		Constants::PrivateS = S;
	else 
		Constants::NonPrivateS = S;
}

double kCenter::CalcValueF(vector<int>& S, int node)
{
	int nS = S.size();
	double Radius = 0.0;
	for (int j = 0; j < Constants::NumOfNodes; ++j)
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
		if (j == node)
		{
			Radius = MinDist;
			break;
		}
		Radius = max(Radius, MinDist);
	}
	return Radius;
}

