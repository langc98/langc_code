#include"CalcMetrics.h"


CalcMetrics::CalcMetrics()
{
	PrivateC = GetClusters(1);
	NonPrivateC = GetClusters(0);
	ns.resize(Constants::K, vector<int>(Constants::K, 0));
	Calc_ns();
}

CalcMetrics::~CalcMetrics()
{
}

double CalcMetrics::CalcARI()
{
	vector<vector<int>> n_ij = ns;
	vector<int> a(Constants::K, 0);
	vector<int> b(Constants::K, 0);
	for (int i = 0; i < Constants::K; ++i)
	{
		for (int j = 0; j < Constants::K; ++j)
		{
			a[i] += ns[i][j];
			b[j] += ns[i][j];
		}
	}
	for (int i = 0; i < Constants::K; ++i)
	{
		for (int j = 0; j < Constants::K; ++j)
		{
			n_ij[i][j] = ns[i][j] * (ns[i][j] - 1) / 2;
		}
		a[i] = a[i] * (a[i] - 1) / 2;
		b[i] = b[i] * (b[i] - 1) / 2;
	}
	int Cn2 = Constants::NumOfNodes * (Constants::NumOfNodes - 1) / 2;
	int aSum = 0, bSum = 0, nsSum = 0;
	for (int i = 0; i < Constants::K; ++i)
	{
		for (int j = 0; j < Constants::K; ++j)
		{
			nsSum += n_ij[i][j];
		}
		aSum += a[i];
		bSum += b[i];
	}
	double ARI = 1.0 * (1.0 * nsSum - 1.0 * aSum * bSum / Cn2) / ((0.5 * aSum + 0.5 * bSum) - 1.0 * aSum * bSum / Cn2);
	return ARI;
}

double CalcMetrics::CalcNMI()
{
	vector<vector<double>> P(Constants::K, vector<double>(Constants::K, 0.0));
	vector<double> Pa(Constants::K, 0.0);
	vector<double> Pb(Constants::K, 0.0);
	for (int i = 0; i < Constants::K; ++i)
	{
		for (int j = 0; j < Constants::K; ++j)
		{
			P[i][j] = 1.0 * ns[i][j] / Constants::NumOfNodes;
		}
	}
	for (int i = 0; i < Constants::K; ++i)
	{
		for (int j = 0; j < Constants::K; ++j)
		{
			Pa[i] += P[i][j];
			Pb[j] += P[i][j];
		}
	}
	double MI = 0.0;
	for (int i = 0; i < Constants::K; ++i)
	{
		for (int j = 0; j < Constants::K; ++j)
		{
			if (P[i][j] == 0)
				continue;
			MI += P[i][j] * log(P[i][j] / Pa[i] / Pb[j]);
		}
	}
	double HX = 0.0, HY = 0.0;
	for (int i = 0; i < Constants::K; ++i)
	{
		if(Pa[i]!=0)
			HX -= Pa[i] * log(Pa[i]);
		if(Pb[i]!=0)
			HY -= Pb[i] * log(Pb[i]);
	}
	double NMI = 2 * MI / (HX + HY);

	return NMI;
}

double CalcMetrics::CalcF(int IsPrivate)
{
	double F = 0.0;
	if (Constants::Alg == 2) //kMedian
	{
		kMedian* km = new kMedian();
		if (IsPrivate == 0)
			F = km->CalcValueF(Constants::NonPrivateS);
		else
			F = km->CalcValueF(Constants::PrivateS);
	}
	else
	{
		kCenter* kc = new kCenter();
		if (IsPrivate == 0)
			F = kc->CalcValueF(Constants::NonPrivateS, -1);
		else
			F = kc->CalcValueF(Constants::PrivateS, -1);
	}
	/*
	else if (Constants::Alg == 1) //kCenter
	{
		vector<int> S;
		if (IsPrivate == 0)
			S = Constants::NonPrivateS;
		else
			S = Constants::PrivateS;
		double MaxDist = 0;
		for (int j = 0; j < Constants::NumOfNodes; ++j)
		{
			for (int k = 0; k < Constants::K; ++k)
			{
				if (S[k] == j)
					continue;
				if (MaxDist < Constants::MinDist[j][S[k]])
				{
					MaxDist = Constants::MinDist[j][S[k]];
				}
			}
		}
		F = MaxDist;
	}
	*/
	return F;
}

vector<vector<int>> CalcMetrics::GetClusters(int IsPrivate)
{
	vector<int> S;
	if (IsPrivate)
		S = Constants::PrivateS;
	else
		S = Constants::NonPrivateS;
	vector<vector<int>> C(Constants::K);
	int index = Constants::Alg - 1;
	for (int i = index; i < Constants::NumOfNodes; ++i)
	{
		double min_dist = 1e9;
		int pos = -1;
		for (int j = 0; j < Constants::K; ++j)
		{
			if (i == S[j]) {
				pos = j;
				break;
			}
			if (min_dist >= Constants::MinDist[i][S[j]])
			{
				min_dist = Constants::MinDist[i][S[j]];
				pos = j;
			}
		}
		C[pos].push_back(i);
	}
	return C;
}

void CalcMetrics::Calc_ns()
{
	for (int i = 0; i < Constants::K; ++i)
	{
		for (int j = 0; j < Constants::K; ++j)
		{
			vector<int> Ci = NonPrivateC[i];
			vector<int> Cj = PrivateC[j];
			vector<int> C;
			set_intersection(Ci.begin(), Ci.end(), Cj.begin(), Cj.end(), inserter(C, C.begin()));
			ns[i][j] = C.size();
		}
	}
}