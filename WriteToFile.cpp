#include"WriteToFile.h"

WriteToFile::WriteToFile()
{
}

WriteToFile::~WriteToFile()
{
}

void WriteToFile::WriteFile(double eps, vector<double> res, int flag)
{
    string ResultFile = "./result/ResultFile_Flag_" + to_string(flag)
        + "_Data_" + to_string(Constants::DataSet)
        + "_Alg_" + to_string(Constants::Alg)
       + "_Eps_" + to_string((int)(Constants::Eps * 10))
//        + "_Eps_" + to_string((int)(eps * 10))
        + "_K_" + to_string(Constants::K) + ".txt";
    ofstream out(ResultFile, ios::out);
    out << Constants::K << " " << Constants::Eps << " "
 //   out << Constants::K << " " << eps << " "
        << res[0] << " " << res[1] << " " << res[2] << " "
        << res[3] << " " << res[4] << " " << res[5] << " "
        << res[6] << " " << res[7] << endl;
    out.close();
}