#include"CalcMetrics.h"


CalcMetrics::CalcMetrics()
{
//	PrivateC = GetClusters(1,1);
//	NonPrivateC = GetClusters(0,0);
	ns.resize(Constants::K, vector<int>(Constants::K, 0));
//	Calc_ns();
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

double CalcMetrics::CalcDBI(vector<int>& S)
{	
	vector<double> R(Constants::K, 0.0);
	
	vector<vector<int>> C = GetClusters(S);
	for (int i = 0; i < Constants::K; ++i)
	{
		vector<int> Ci = C[i];
		double SumDis = 0.0;
		int nCi = Ci.size();
		for (int u : Ci)
		{
			if (u == S[i])
				continue;
			SumDis += Constants::MinDist[u][S[i]];
		}
		R[i] = SumDis / nCi;
	}
	double sum = 0.0;
	for (int i = 0; i < Constants::K; ++i)
	{
		double ma = 0.0;
		double value = 0.0;
		for (int j = 0; j < Constants::K; ++j)
		{
			if (i == j)
				continue;
			value = (R[i] + R[j]) / Constants::MinDist[S[i]][S[j]];
			if (ma < value)
			{
				ma = value;
			}
		}
		sum += ma;
	}
	double DBI = sum / Constants::K;
	return DBI;
}

double CalcMetrics::CalcSCI(vector<int>& S)
{
	vector<vector<int>> C = GetClusters(S);
	map<int, double> a, b,s;
	for (int i = 0; i < Constants::K; ++i)
	{
		int n = C[i].size();
		if (n == 1)
		{
			a[C[i][0]] = 0;
			continue;
		}
		for (int ii = 0; ii < n; ++ii)
		{
			double sum = 0;
			for (int jj = 0; jj < n; ++jj)
			{
				if (ii != jj)
				{
					sum = sum + Constants::MinDist[C[i][ii]][C[i][jj]];
				}

			}
			sum = sum / (n - 1.0);
			a[C[i][ii]] = sum;
		}
	}
	for (int i = 0; i < Constants::K; ++i)
	{
		
		int ni = C[i].size();
		for (int ii = 0; ii < ni; ++ii)
		{
			double dis = 1e5;
			for (int j = 0; j < Constants::K; ++j)
			{
				if (i == j)
					continue;

				int nj = C[j].size();
				double sum = 0;
				for (int jj = 0; jj < nj; ++jj)
				{
					sum = sum + Constants::MinDist[C[i][ii]][C[j][jj]];
				}
				sum = sum / nj;
				dis = min(dis, sum);
			}
			b[C[i][ii]] = dis;
		}
	}
	double sum = 0;
	int num = a.size();
	int index = (Constants::Alg - 1) / 2;
	for (int i = index; i < num; ++i)
	{
		sum = sum + (b[i] - a[i]) / max(a[i], b[i]);
	}
	sum = sum / (0.0 + num - index);
	double SCI = sum;
	return SCI;
}

double CalcMetrics::CalcDVI(vector<int>& S)
{

	vector<vector<int>> C = GetClusters(S);

	double maxdis = 0;
	for (int i = 0; i < Constants::K; ++i)
	{
		int n = C[i].size();
		for (int ii = 0; ii < n; ++ii)
		{
			for (int jj = 0; jj < n; ++jj)
			{
				if (ii == jj)
					continue;
				maxdis = max(maxdis, Constants::MinDist[C[i][ii]][C[i][jj]]);
			}
		}
	}
	double mindis = 1e5;
	/*
	for (int i = 0; i < Constants::K; ++i)
	{
		for (int j = 0; j < Constants::K; ++j)
		{
			if (i == j)
				continue;
			mindis = min(mindis, Constants::MinDist[S[i]][S[j]]);
		}
	}
	*/
	for (int i = 0; i < Constants::K; ++i)
	{
		int ni = C[i].size();
		for (int j = i+1; j < Constants::K; ++j)
		{
			int nj = C[j].size();
			for(int ii=0;ii<ni;++ii)
				for(int jj=0;jj<nj;++jj)
					mindis = min(mindis, Constants::MinDist[C[i][ii]][C[j][jj]]);
		}
	}
	double DVI = mindis / maxdis;
	return DVI;
}


double CalcMetrics::CalcPurity()
{
	int sum = 0;
	for (int i = 0; i < Constants::K; ++i)
	{
		int max_com = 0;
		for (int j = 0; j < Constants::K; ++j)
		{
			max_com = max(max_com, ns[j][i]);
		}
		sum += max_com;
	}
	double Purity = 1.0 * sum / Constants::NumOfNodes;
	return Purity;
}


double CalcMetrics::CalcF(vector<int>& S)
{
	double F = 0.0;
	if (Constants::Alg >= 3) //kMedian
	{
		kMedian* km = new kMedian();
		F = km->CalcValueL(S);
		delete km;
	}
	else
	{
		kCenter* kc = new kCenter();
		F = kc->CalcValueF(S, -1);
		delete kc;
	}
	return F;
}

vector<vector<int>> CalcMetrics::GetClusters(vector<int>& S)
{
	vector<vector<int>> C(Constants::K);
	int index = (Constants::Alg - 1) / 2;
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

void CalcMetrics::Calc_ns(vector<int>& PrivateS, vector<int>& NonPrivateS)
{
	PrivateC = GetClusters(PrivateS);
	NonPrivateC = GetClusters(NonPrivateS);
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

void CalcMetrics::GetResults(vector<int>& PrivateS, vector<int>& NonPrivateS, vector<vector<double>>& res, int pos)
{

	res[0][pos] = CalcDBI(NonPrivateS);	//DBI
	res[1][pos] = CalcDBI(PrivateS);	//DBI
	res[2][pos] = CalcDVI(NonPrivateS);	//DVI
	res[3][pos] = CalcDVI(PrivateS);	//DVI
	res[4][pos] = CalcSCI(NonPrivateS);	//SCI
	res[5][pos] = CalcSCI(PrivateS);	//SCI
	res[6][pos] = CalcF(NonPrivateS);		//value F non-private
	res[7][pos] = CalcF(PrivateS);		//value F private
}