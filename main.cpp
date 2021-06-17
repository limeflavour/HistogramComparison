#include<opencv2/opencv.hpp>
#include<iostream>
#include<string>
using namespace cv;
using namespace std;

int main()
{
	string input = "c";

	while (input != "q")
	{
		string imgName1;
		string imgName2;
		cout << "第一张图片编号: ";
		cin >> imgName1;
		cout << "第二张图片编号: ";
		cin >> imgName2;
		stringstream ss1, ss2;
		ss1 << "C:\\数据\\东西湖区志（上卷）-RH\\visualized\\" << imgName1 << ".visualized.jpg";
		ss2 << "C:\\数据\\东西湖区志（上卷）-RH\\visualized\\" << imgName2 << ".visualized.jpg";
		cout << ss1.str() << endl << ss2.str() << endl;

		Mat srcImage1 = imread(ss1.str(), 0);
		Mat srcImage2 = imread(ss2.str(), 0);

		if (srcImage1.empty())
		{
			std::cout << "图像1加载失败！" << std::endl;
			system("pause");
			return -1;
		}
		if (srcImage2.empty())
		{
			std::cout << "图像2加载失败！" << std::endl;
			system("pause");
			return -1;
		}

		/*   自适应阈值化
		Mat srcImage1Thr;
		adaptiveThreshold(srcImage1, srcImage1Thr, 255, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY, 25, 10);
		Mat srcImage2Thr;
		adaptiveThreshold(srcImage2, srcImage2Thr, 255, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY, 25, 10);
		imshow("srcImage1Thr", srcImage1Thr);
		imshow("srcImage2Thr", srcImage2Thr);
		waitKey(0);
		*/

		Mat hi1_clone = srcImage1.clone();
		Mat hi2_clone = srcImage2.clone();


		//计算直方图所需参数
		MatND dstHist1, dstHist2;
		int dims = 1;
		float hranges[] = { 0, 255 };
		const float* ranges[] = { hranges };
		int size = 256;
		int channels = 0;

		//计算第一张图像的直方图并归一化
		calcHist(&hi1_clone, 1, &channels, Mat(), dstHist1, dims, &size, ranges);
		double  count1 = 0;
		for (int i = 0; i < 160; i++)
		{
			count1 = count1 + dstHist1.at<float>(i); //why float?
		}
		normalize(dstHist1, dstHist1, 0, 1, NORM_MINMAX, -1, Mat());

		//计算第二张图像的直方图并归一化
		calcHist(&hi2_clone, 1, &channels, Mat(), dstHist2, dims, &size, ranges);
		double  count2 = 0;
		for (int i = 0; i < 160; i++)
		{
			count2 = count2 + dstHist2.at<float>(i); //why float?
		}
		normalize(dstHist2, dstHist2, 0, 1, NORM_MINMAX, -1, Mat());

		//计算两张图像的相关度
		double hi1_hi2 = compareHist(dstHist1, dstHist2, CV_COMP_INTERSECT);

		//cout << "count = " << count << endl;
		//cout << "dstHist1.rows * dstHist1.cols = " << hi1_clone.rows * hi1_clone.cols << endl;

		double ratio1 = (count1 / (hi1_clone.rows * hi1_clone.cols)) * 100;
		cout << imgName1 << ": " << "0-160灰度值占比为 = " << ratio1 << "%"<< endl;

		double ratio2 = (count2 / (hi2_clone.rows * hi2_clone.cols)) * 100;
		cout << imgName2 << ": " << "0-160灰度值占比为 = " << ratio2 << "%" << endl;

		cout << "计算直方图得图片1_图片2相关度为: = " << hi1_hi2 << endl;

		cout << "输入q退出，输入其他继续: ";
		cin >> input;
	}


	return 0;
}
