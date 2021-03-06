#include "common.h"
#include <windows.h>
#include <psapi.h>
#pragma comment(lib,"psapi.lib")

using namespace std;

// 将int转换成string 
string itos(int i)
{
    stringstream s;
    s << i;
    return s.str();
}

void CalFPR_TPR(float &FPR, float &TPR, float &rr, const std::vector<float> &labelSet, const std::vector<float> &similSet, const float hold)
{
    int pos_number = 0, neg_number = 0, rig_number = 0;

    FPR = 0, TPR = 0;

    //计算正负样本个数
    for(int i=0; i<labelSet.size(); i++)
    {
        if(labelSet[i] == 1.0)
        {
            pos_number++;
        }
        else
        {
            neg_number++;
        }
    }

    // FPR and TPR
    // 负样本的错误率 以及 正样本的正确率
    for(int i=0; i<labelSet.size(); i++)
    {
        float yi = similSet[i]>=hold ? 1.0 : -1.0;
        if ((yi == 1.0) && (labelSet[i] == -1.0))	//实际不是同一个人，却认为是同一个人 的样本数
        {
            FPR += 1;
        }

        if ((yi == 1.0) && (labelSet[i] == 1.0))	//实际是同一个人，也认为是同一个人 的样本数
        {
            TPR += 1;
        }

		rig_number += (yi==labelSet[i] ? 1 : 0);
    }

    FPR = FPR / neg_number;
    TPR = TPR / pos_number;
	rr = float(rig_number) / (pos_number + neg_number);
}


void showMemoryInfo(void)
{
    HANDLE handle=GetCurrentProcess();
    PROCESS_MEMORY_COUNTERS pmc;
    GetProcessMemoryInfo(handle,&pmc,sizeof(pmc));
    cout<<"内存使用:"<<pmc.WorkingSetSize/1000 <<"K/"<<pmc.PeakWorkingSetSize/1000<<"K + "<<pmc.PagefileUsage/1000 <<"K/"<<pmc.PeakPagefileUsage/1000 <<"K"<<endl;
}
