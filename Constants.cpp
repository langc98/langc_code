#include"Constants.h"

Constants::Constants()
{
}

Constants::~Constants()
{
}

double Constants::Eps = 1;
int Constants::Alg = 1;
int Constants::DataSet = 1;
int Constants::NumOfNodes = 0;
int Constants::K = 1;
int Constants::IsMinDist = 0;
vector<string> Constants::FileNamePrefix = { "Hamsterster", "Facebook", "WikiVote", "CaHepTh", "CaHepPh","CaAstroPh", "NYroad" };
vector<int> Constants::PrivateS;
vector<int> Constants::NonPrivateS;
vector<vector<double>> Constants::Graph;
vector<vector<double>> Constants::MinDist;