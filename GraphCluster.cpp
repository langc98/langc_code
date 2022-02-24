#include<iostream>
#include<fstream>
#include<vector>
#include<map>
#include<string>

#include"Constants.h"
#include"ReadFile.h"
#include"GetMinDist.h"
#include"kCenter.h"
#include"kMedian.h"
#include"GetArgs.h"
#include"ExponentialMechanism.h"
#include"CalcMetrics.h"

using namespace std;





int main(int argc, char* argv[])
{
    GetArgs* args = new GetArgs();
    args->ParseArgs(argc, argv);

    ReadFile* rf = new ReadFile();
    rf->GetMatrix();
    if (Constants::IsMinDist)
    {
        Constants::MinDist = Constants::Graph;
    }
    else
    {
        GetMinDist* gmd = new GetMinDist();
        gmd->CalcMinDist();
    }

    kCenter* kc = new kCenter();
    kMedian* km = new kMedian();

    switch (Constants::Alg)
    {
    case 1: //k-Center
        kc->GetSolution(1);
        kc->GetSolution(0);
        break;
    case 2: //k-Median
        km->GetSolution(1);
        km->GetSolution(0);
        break;
    default: //k-Center
        kc->GetSolution(1);
        kc->GetSolution(0);
        break;
    }

    CalcMetrics* cm = new CalcMetrics();
    double ARI = cm->CalcARI();
    double NMI = cm->CalcNMI();
    vector<double> valueF(2);
    for (int i = 0; i < 2; ++i)
    {
        valueF[i] = cm->CalcF(i);
    }
    string ResultFile = "./result/ResultFile_Data_" + to_string(Constants::DataSet) 
        + "_Alg_" + to_string(Constants::Alg) 
        + "_Eps_" + to_string((int)(Constants::Eps * 10)) + ".txt";
    ofstream out(ResultFile, ios::out);
    out << Constants::Eps << " " << ARI << " " << NMI << " " << valueF[0] << " " << valueF[1] << endl;
    out.close();
    return 0;
}

