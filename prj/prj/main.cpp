#include <iostream>
#include <vector>
#include <string>
#include <opencv.hpp>

#include "cmodelSVM.h"
#include "cfeature.h"
#include "wrap.h"

#include "iofile.h"

static int TRAIN_NUM = 3;			//训练图像对个数

using namespace std;
using namespace cv;


// 将int转换成string 
string itos(int i)
{
	stringstream s;
	s << i;
	return s.str();
}

int main(void)
{
	iofile coupleImgDataSet(40, 10);

	vector<CFeature> featureSet(TRAIN_NUM);	//特征集

	// 1).提取所有图像的特征
	for(int i = 1; i < TRAIN_NUM; i++)
	{
		string img1_path, img2_path;
		coupleImgDataSet.extCoupleImg_path(img1_path, img2_path, i, true);		// 第i对正样本
		//coupleImgDataSet.extCoupleImg_path(img1_path, img2_path, i, false);		// 第i对负样本

		//Mat img1 = imread(img1_path, IMREAD_GRAYSCALE);
		//Mat img2 = imread(img2_path, IMREAD_GRAYSCALE);

		//ImgWrap imgWrap1(&img1), imgWrap2(&img2);

		//featureSet[i] = CFeature(&imgWrap1, &imgWrap2);

		/*finish:
		img空间释放，所以imgWrap中的指针所指会被释放
		至此不需要的内存完全被回收
		*/
	}
	//2).训练模型
	CModelInt *model = new CModelSVM();
	model->train(featureSet);
//	model->saveModel("modelSvm");

	//3).读取模型
//	model->loadModel("modelSvm");

	return 0;
}