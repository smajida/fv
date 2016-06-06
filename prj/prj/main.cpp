#include <iostream>
#include <vector>

#include "cfeature.h"
#include "cmodelDemo.h"
#include "wrap.h"

static int TRAIN_NUM=10;			//训练图像个数

using namespace std;

int main(void)
{
	vector<CFeature> featureSet(TRAIN_NUM);	//特征集

	//1).提取所有图像的特征
	for(int i=0; i<TRAIN_NUM; i++)
	{
		int img1 = i, img2 = i+1;
		ImgWrap imgWrap1(&img1), imgWrap2(&img2);					//将img1 img2包装起来

		featureSet[i] = CFeature(new ImgWrap(), new ImgWrap());

		/*finish:
		img1 img2空间释放，所以imgWrap1, imgWrap2中的指针所指会被释放
		imgWrap1, imgWrap2的空间释放
		至此不需要的内存完全被回收
		*/
	}

	//2).训练模型
	CModelInt *model = new CModelDemo();
	model->train(featureSet);
	model->storeModel("modelDemo");

	//3).读取模型
	model->readModel("modelDemo");

	return 0;
}