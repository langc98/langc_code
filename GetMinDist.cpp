#include"GetMinDist.h"

GetMinDist::GetMinDist()
{
    //min_dist = Constants::Graph;
    FileName = Constants::FileNamePrefix[Constants::DataSet];
    //ChooseDataSet();
}

GetMinDist::~GetMinDist()
{
}

void GetMinDist::CalcMinDist()
{
    for (int k = 0; k < Constants::NumOfNodes; ++k) 
    {
        for (int i = 0; i < Constants::NumOfNodes; ++i) 
        {
            for (int j = 0; j < Constants::NumOfNodes; ++j) 
            {
                //if (min_dist[i][j] > min_dist[i][k] + min_dist[k][j]) 
                //{
                //   min_dist[i][j] = min_dist[i][k] + min_dist[k][j];
                //}
                if (Constants::MinDist[i][j] > Constants::MinDist[i][k] + Constants::MinDist[k][j])
                {
                    Constants::MinDist[i][j] = Constants::MinDist[i][k] + Constants::MinDist[k][j];
                }
            }
        }
    }
    //Constants::MinDist = min_dist;
    string DataFile = "./data/MinDist_" + FileName + ".txt";
    ofstream out(DataFile, ios::out);
    for (int i = 0; i < Constants::NumOfNodes; ++i)
    {
        for (int j = i + 1; j < Constants::NumOfNodes; ++j)
        {
        //    if(min_dist[i][j] < 100000)
        //        out << i << " " << j << " " << min_dist[i][j] << endl;
            out << i << " " << j << " " << Constants::MinDist[i][j] << endl;
        }
    }
    out.close();
}

void GetMinDist::ChooseDataSet()
{
    switch (Constants::DataSet)
    {
    case 1:
        FileName = "Facebook";
        break;
    case 2:
        FileName = "Hamsterster";
        break;
    case 3:
        FileName = "WikiVote";
        break;
    case 4:
        FileName = "NYroad";
        break; 
    default:
        FileName = "WikiVote";
        break;
    }
}