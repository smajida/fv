#ifndef _IOFILE_H
#define _IOFILE_H

#include <iostream>
#include <fstream>
#include <vector>

typedef struct{
	string path1;
	string path2;
}imgPath;

class iofile
{
public:
	iofile(int n, int m);
	void coupleImg_org();		// 组织图像
	void posCoupleImg_org();	// 组织正样本对
	void negCoupleImg_org();	// 组织负样本对
	void extCoupleImg_path();	// 提取正、负样本对路径

	void extCoupleImg_path(string &path1, string &path2, int nth, bool type);

private:
	int N;						// N个人
	int M;						// 每个人M张人脸图像
	int posCoupleSize;
	int negCoupleSize;
	vector<imgPath> posImg;		// 正样本图像对路径
	vector<imgPath> negImg;		// 负样本图像对路径
	vector<string> allPath;		// 所有图像的路径
};

iofile::iofile(int n, int m)
{
	N = n;
	M = m;
	posCoupleSize = N * M * (M - 1) / 2;
	negCoupleSize = (N * M) * (N * M - 1) / 2 - posCoupleSize;
	coupleImg_org();
}

void iofile::coupleImg_org()
{
	// 列出所有图像的路径
	system("dir ORL\\*.pgm /a-d /o-n /b /s >pathFile.simple");

	string str;
	ifstream pathFile("pathFile.simple");
	while(!pathFile.eof())
	{
		getline(pathFile, str);
		allPath.push_back(str);
	}
	pathFile.close();

	posCoupleImg_org();
	negCoupleImg_org();
}

void iofile::posCoupleImg_org()
{	
	// 正样本
	ofstream posFile("coupleFace.positive");

	posFile << posCoupleSize << endl;
	for (int k = 0; k < N; ++k)
	{
		for (int i = 0; i < M; ++i)
		{
			for (int j = i + 1; j < M; ++j)
			{
				posFile << i + k * M << '\t' << j + k * M << endl;
			}
		}
	}
	posFile.close();
}

void iofile::negCoupleImg_org()
{
	// 负样本
	ofstream negFile("coupleFace.negative");

	negFile << negCoupleSize << endl;
	for (int i = 0; i < (N - 1) * M; ++i)
	{
		int k = i / M + 1;
		for (int j = k * M; j < N * M; ++j)
		{
			negFile << i << '\t' << j << endl;
		}
	}
	negFile.close();
}

void iofile::extCoupleImg_path()
{
	ifstream posFile("coupleFace.positive");
	int num1 = 0;
	posFile >> num1;
	while(num1--)
	{
		int index1 = 0, index2 = 0;
		posFile >> index1 >> index2;
		imgPath imgCouplePath;
		imgCouplePath.path1 = allPath[index1];
		imgCouplePath.path2 = allPath[index2];
		posImg.push_back(imgCouplePath);
	}
	posFile.close();

	ifstream negFile("coupleFace.negative");
	int num2 = 0;
	negFile >> num2;
	while(num2--)
	{
		int index1 = 0, index2 = 0;
		negFile >> index1 >> index2;
		imgPath imgCouplePath;
		imgCouplePath.path1 = allPath[index1];
		imgCouplePath.path2 = allPath[index2];
		negImg.push_back(imgCouplePath);
	}
	negFile.close();
}

void iofile::extCoupleImg_path(string &path1, string &path2, int nth, bool type)
{
	string coupleImg_path;

	if (type)	coupleImg_path = "coupleFace.positive";
	else		coupleImg_path = "coupleFace.negative";

	ifstream pnFile(coupleImg_path);
	int index1 = 0, index2 = 0;
	do
	{
		pnFile >> index1 >> index2;
	}while(nth--);
	path1 = allPath[index1];
	path2 = allPath[index2];
}




#endif