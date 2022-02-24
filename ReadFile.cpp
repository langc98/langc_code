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
	//Graph_Data.resize(Constants::NumOfNodes, vector<double>(Constants::NumOfNodes, 100000));
	Constants::Graph.resize(Constants::NumOfNodes, vector<double>(Constants::NumOfNodes, 100000));
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
		if (Constants::DataSet == 4)
			w /= 10000;
		Constants::Graph[u][v] = w;
		Constants::Graph[v][u] = w;
		//Constants::Graph[u][u] = 0.0;
		//Constants::Graph[v][v] = 0.0;
	}
	infile2.close();
	//Constants::Graph = Graph_Data;
}

void ReadFile::ChooseDataSet()
{
	if (Constants::IsMinDist)
	{
		switch (Constants::DataSet)
		{
		case 1:
			FileName = "./data/MinDist_Facebook.txt";
			break;
		case 2:
			FileName = "./data/MinDist_Hamsterster.txt";
			break;
		case 3:
			FileName = "./data/MinDist_WikiVote.txt";
			break;
		case 4:
			FileName = "./data/NYroad.txt";
			break;
		default:
			FileName = "./data/MinDist_WikiVote.txt";
			break;
		}
	}
	else
	{
		switch (Constants::DataSet)
		{
		case 1:
			FileName = "./data/Facebook.txt";
			break;
		case 2:
			FileName = "./data/Hamsterster.txt";
			break;
		case 3:
			FileName = "./data/WikiVote.txt"; 
			break;
		case 4:
			FileName = "./data/NYroad.txt";
			break;
		default:
			FileName = "./data/WikiVote.txt";
			break;
		}
	}
}
