#include"Constants.h"

Constants::Constants()
{
}

Constants::~Constants()
{
}

double Constants::Eps = 1;
double Constants::Beta = 0.1;
int Constants::Alg = 1;
int Constants::DataSet = 5;
int Constants::NumOfNodes = 10000;
int Constants::K = 5;
int Constants::IsMinDist = 1;

vector<string> Constants::FileNamePrefix = { "Facebook", "WikiVote", "Uber" };
vector<int> Constants::PrivateS;
vector<int> Constants::NonPrivateS;
vector<int> Constants::PrivateSPre;
vector<int> Constants::NonPrivateSPre;
vector<vector<double>> Constants::MinDist;
vector<int> Constants::StepSize = { 5,5,5 };