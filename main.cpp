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
		cout << "��һ��ͼƬ���: ";
		cin >> imgName1;
		cout << "�ڶ���ͼƬ���: ";
		cin >> imgName2;
		stringstream ss1, ss2;
		ss1 << "C:\\����\\��������־���Ͼ�-RH\\visualized\\" << imgName1 << ".visualized.jpg";
		ss2 << "C:\\����\\��������־���Ͼ�-RH\\visualized\\" << imgName2 << ".visualized.jpg";
		cout << ss1.str() << endl << ss2.str() << endl;

		Mat srcImage1 = imread(ss1.str(), 0);
		Mat srcImage2 = imread(ss2.str(), 0);

		if (srcImage1.empty())
		{
			std::cout << "ͼ��1����ʧ�ܣ�" << std::endl;
			system("pause");
			return -1;
		}
		if (srcImage2.empty())
		{
			std::cout << "ͼ��2����ʧ�ܣ�" << std::endl;
			system("pause");
			return -1;
		}

		/*   ����Ӧ��ֵ��
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


		//����ֱ��ͼ�������
		MatND dstHist1, dstHist2;
		int dims = 1;
		float hranges[] = { 0, 255 };
		const float* ranges[] = { hranges };
		int size = 256;
		int channels = 0;

		//�����һ��ͼ���ֱ��ͼ����һ��
		calcHist(&hi1_clone, 1, &channels, Mat(), dstHist1, dims, &size, ranges);
		double  count1 = 0;
		for (int i = 0; i < 160; i++)
		{
			count1 = count1 + dstHist1.at<float>(i); //why float?
		}
		normalize(dstHist1, dstHist1, 0, 1, NORM_MINMAX, -1, Mat());

		//����ڶ���ͼ���ֱ��ͼ����һ��
		calcHist(&hi2_clone, 1, &channels, Mat(), dstHist2, dims, &size, ranges);
		double  count2 = 0;
		for (int i = 0; i < 160; i++)
		{
			count2 = count2 + dstHist2.at<float>(i); //why float?
		}
		normalize(dstHist2, dstHist2, 0, 1, NORM_MINMAX, -1, Mat());

		//��������ͼ�����ض�
		double hi1_hi2 = compareHist(dstHist1, dstHist2, CV_COMP_INTERSECT);

		//cout << "count = " << count << endl;
		//cout << "dstHist1.rows * dstHist1.cols = " << hi1_clone.rows * hi1_clone.cols << endl;

		double ratio1 = (count1 / (hi1_clone.rows * hi1_clone.cols)) * 100;
		cout << imgName1 << ": " << "0-160�Ҷ�ֵռ��Ϊ = " << ratio1 << "%"<< endl;

		double ratio2 = (count2 / (hi2_clone.rows * hi2_clone.cols)) * 100;
		cout << imgName2 << ": " << "0-160�Ҷ�ֵռ��Ϊ = " << ratio2 << "%" << endl;

		cout << "����ֱ��ͼ��ͼƬ1_ͼƬ2��ض�Ϊ: = " << hi1_hi2 << endl;

		cout << "����q�˳���������������: ";
		cin >> input;
	}


	return 0;
}
