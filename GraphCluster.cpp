#include<iostream>
#include<fstream>
#include<vector>
#include<map>
#include<string>
#include<omp.h>

#include"Constants.h"
#include"ReadFile.h"
#include"GetMinDist.h"
#include"kCenter.h"
#include"kMedian.h"
#include"GetArgs.h"
#include"ExponentialMechanism.h"
#include"CalcMetrics.h"
#include"WriteToFile.h"

using namespace std;

int main(int argc, char* argv[])
{
    int NumOfRun = 20;

    GetArgs* args = new GetArgs();
    args->ParseArgs(argc, argv);
    delete args;
    vector<int> nums_nodes{ 4039,7115,10000 };
    Constants::NumOfNodes = nums_nodes[Constants::DataSet];

    ReadFile* rf = new ReadFile();
    rf->GetMatrix();
    delete rf;
    if (!Constants::IsMinDist) {
        GetMinDist* gmd = new GetMinDist();
        gmd->CalcMinDist();
        delete gmd;
    }
    Constants::Eps = Constants::Eps * 0.5;
    double eps = Constants::Eps / Constants::K;

    vector<double> res1(8, 0.0);
    vector<double> res2(8, 0.0);
    vector<vector<double>>ans1(8, vector<double>(NumOfRun, 0.0));
    vector<vector<double>>ans2(8, vector<double>(NumOfRun, 0.0));

    omp_set_num_threads(20);
    #pragma omp parallel for
    for (int j = 1; j <= NumOfRun; ++j)
    {
        kCenter* kc = new kCenter();
        kMedian* km = new kMedian();
        CalcMetrics* cm = new CalcMetrics();
        vector<int> PrivateS;
        vector<int> NonPrivateS;
        vector<int> PrivateSPre;
        vector<int> NonPrivateSPre;
        if (Constants::Alg <= 2)
        {
            //k-Center
            kc->GetId(j);
            PrivateS = kc->GetSolution(1, eps);
            NonPrivateS = kc->GetSolution(0, eps);
            cm->GetResults(PrivateS, NonPrivateS, ans1, j - 1);
        }
        else
        {
            //k-Median
            km->GetId(j);
            PrivateS = km->GetSolution(1, eps);
            NonPrivateS = km->GetSolution(0, eps);
            PrivateSPre = km->GetSolution(1, eps, 0);
            NonPrivateSPre = km->GetSolution(0, eps, 0);
            cm->GetResults(PrivateS, NonPrivateS, ans1, j - 1);
            cm->GetResults(PrivateSPre, NonPrivateSPre, ans2, j - 1);
        }
        delete kc;
        delete km;
        delete cm;
    }
    for (int t = 0; t < 8; ++t)
    {
        for (int r = 0; r < NumOfRun; ++r)
        {
            res1[t] += ans1[t][r];
            res2[t] += ans2[t][r];
        }
        res1[t] /= NumOfRun;
        res2[t] /= NumOfRun;
    }
    WriteToFile* wf = new WriteToFile();
    wf->WriteFile(eps * Constants::K, res1, 1);
    if (Constants::Alg >= 3)
        wf->WriteFile(eps * Constants::K, res2, 0);
    delete wf;
    return 0;
}

