#include"ReadFile.h"

ReadFile::ReadFile()
{
	num = 0;
	if(Constants::IsMinDist)
		FileName = "./data/MinDist_" + Constants::FileNamePrefix[Constants::DataSet] + ".txt";
	else
		FileName = "./data/" + Constants::FileNamePrefix[Constants::DataSet] + ".txt";
	//ChooseDataSet();
}

ReadFile::~ReadFile()
{
}

void ReadFile::GetMatrix()
{
	
	ifstream infile(FileName);
	/*
	for (string line; getline(infile, line);)
	{
		istringstream ins(line);
		int u = 0, v = 0;
		double w = 0.0;
		ins >> u >> v >> w;
		num = max(num, u);
		num = max(num, v);
	}
	Constants::NumOfNodes = num + 1;
	*/
	//Graph_Data.resize(Constants::NumOfNodes, vector<double>(Constants::NumOfNodes, 100000));
	//Constants::Graph.resize(Constants::NumOfNodes, vector<double>(Constants::NumOfNodes, 100000));
	Constants::MinDist.resize(Constants::NumOfNodes, vector<double>(Constants::NumOfNodes, 100000));
	infile.close();
	ifstream infile2(FileName);
	for (string line; getline(infile2, line);)
	{
		istringstream ins(line);
		int u = 0, v = 0;
		double w = 0.0;
		ins >> u >> v >> w;
		//Graph_Data[u][v] = w;
		//Graph_Data[v][u] = w;
		if (Constants::DataSet == 6)
			w /= 10000;
		//Constants::Graph[u][v] = w;
		//Constants::Graph[v][u] = w;
		Constants::MinDist[u][v] = w;
		Constants::MinDist[v][u] = w;
	}
	infile2.close();
	//Constants::Graph = Graph_Data;
}

