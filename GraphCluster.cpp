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

using namespace std;





int main(int argc, char* argv[])
{
    int NumOfEps = 10;
    int NumOfRun = 5;
    omp_set_num_threads(7);

    GetArgs* args = new GetArgs();
    args->ParseArgs(argc, argv);
    
    ReadFile* rf = new ReadFile();
    rf->GetMatrix();
    /*
    if (Constants::IsMinDist)
    {
        Constants::MinDist = Constants::Graph;
    }
    else
    {
        GetMinDist* gmd = new GetMinDist();
        gmd->CalcMinDist();
    }
    */

    if (!Constants::IsMinDist) {
        GetMinDist* gmd = new GetMinDist();
        gmd->CalcMinDist();
    }

    #pragma omp parallel for
    for (int i = 1; i <= NumOfEps; ++i)
    {
    //    Constants::Eps = 0.5 * i;
        double eps = 0.5 * i;

        double ARI = 0.0;
        double NMI = 0.0;
        double Purity = 0.0;
        vector<double> valueF = { 0.0,0.0 };

        for (int j = 0; j < NumOfRun; ++j)
        {
            kCenter* kc = new kCenter();
            kMedian* km = new kMedian();

            switch (Constants::Alg)
            {
            case 1: //k-Center
                kc->GetSolution(1, eps);
                kc->GetSolution(0, eps);
                break;
            case 2: //k-Median
                km->GetSolution(1, eps);
                if(j==0)
                    km->GetSolution(0, eps);
                break;
            default: //k-Center
                kc->GetSolution(1, eps);
                kc->GetSolution(0, eps);
                break;
            }

            CalcMetrics* cm = new CalcMetrics();
            ARI += cm->CalcARI();
            NMI += cm->CalcNMI();
            Purity += cm->CalcPurity();
            for (int i = 0; i < 2; ++i)
            {
                valueF[i] += cm->CalcF(i);
            }
        }

        ARI /= NumOfRun;
        NMI /= NumOfRun;
        Purity /= NumOfRun;
        for (int i = 0; i < 2; ++i)
        {
            valueF[i] /= NumOfRun;
        }
        
        string ResultFile = "./result/ResultFile_Data_" + to_string(Constants::DataSet)
            + "_Alg_" + to_string(Constants::Alg)
     //       + "_Eps_" + to_string((int)(Constants::Eps * 10))
            + "_Eps_" + to_string((int)(eps * 10))
            + "_K_" + to_string(Constants::K) + ".txt";
        ofstream out(ResultFile, ios::out);
     //   out << Constants::K << " " << Constants::Eps << " "
        out << Constants::K << " " << eps << " " 
            << ARI << " " << NMI << " " << Purity << " " 
            << valueF[0] << " " << valueF[1] << endl;
        out.close();
    }
    return 0;
}

