#pragma warning(disable:4996)

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <opencv.hpp>


#include "common.h"
#include "cmodelSVM.h"
#include "cmodelANN.h"
#include "cfeature.h"

#include "iofile.h"

using namespace std;
using namespace cv;

const int predNum = 2000;
const int jumpNum = 2000;

void expect(void)
{
    iofile obj("datalist.FERET",            // ���ݼ�
        "Dataset.FERET",             // ������
        "��ң_Distance.txt",         // ���ƶ�
        "��ң_ROC.txt",              // ROC
        "errInf.log"                // ��־
        );

	vector<CFeature>				featureSet(predNum);    //������
	vector<float>					labelSet(predNum);	    //��ǩ��
	vector<float>					similSet(predNum);	    //���ƶȼ�
	vector<pair<float,float> >		rocSet(100);            //fpr tpr��

	//1).��ȡ�����������������õ���Ӧ��ǩ

    for(int i = 0; i < predNum / 2; i++)
    {
        featureSet[i] = CFeature(obj, jumpNum + i, true);
        labelSet[i] = 1;
        printf("finish %d\n", i + jumpNum);
    }
    for(int i = 0; i < predNum / 2; i++)
    {
        featureSet[i + predNum / 2] = CFeature(obj, jumpNum + i, false);
        labelSet[i + predNum / 2] = -1.0;
        printf("finish %d\n", i + jumpNum);
    }
	//2).����ʶ��ģ��
	//CModelInt *model = new CModelSVM();
	//model->loadModel("svm_model");
    CModelInt *model = new CModelANN();
    model->loadModel("ann_model");
	//3).�����������������ƶ�
	for(int i=0; i<predNum; i++)
	{
		printf("%d\n", i);
		similSet[i] = model->similarity(featureSet[i]);
	}

	//4).��������hold��Ӧ��FPR TPR
	for(int i=0; i<100; i+=1)
	{
		CalFPR_TPR(rocSet[int(i)].first, rocSet[int(i)].second, labelSet, similSet, i*0.01);
	}

	//5).��������ļ�
	/*
	����˵��:
	  1).similSet�������Թ����������ļ�(��Ϊ������ֵ�Ƕ��٣������Զ�����ô��)
	     �����ֵ������0.5�����ǵ�FPR�Ҹ�TPR����ֵ
	  2).rocSet�������Թ���ROC�ı�
	     rocSet[i]ָ��ֵΪi*0.01ʱ��FPR��TPR��rocSet[i]�Ǹ�pair<float, float>���ݣ�first��FPR��ROC���Ǻ��ᣬsecond��TPR��ROC��������
	     FPR��������Ϊ��������ʶ������ʡ���TPR��������Ϊ��������ʶ����ȷ�ʡ�
	*/
    obj.save(similSet);
    obj.save(rocSet);

    delete model;
}