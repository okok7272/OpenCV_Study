#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int ac, char** av) {


	//Mat : Matrix ���
	//Mat(int rows ��, int cols �� , int type Ÿ��, const Scalar& s �ʱⰪ)
	Mat img_1 = imread("C:\\Users\\4DiVision\\Downloads\\Lenna.png", 0);    //�̹����� grayscale�� �ҷ���
	//Mat imread(const string& filename, int flags=IMREAD_COLOR )
	//IMREAD_ANYCOLOR | IMREAD_ANYDEPTH

	//��� ��ȭ 
	//Mat img_2 = img_1 * 2;
	//Mat img_3 = img_1 / 2;
	Mat img_hist;


	// �̹����� ������׷� ���
	//typedef Mat MatND; core.hpp (version 2.4.8)
	MatND histogram;
	// 3ä�ο��� �������� ������ �����ϰ� 1ä�ο����� �� �Ǵ� ���� ����
	const int* channel_numbers = { 0 }; //ä���� �Ѱ��� 0
	float channel_range[] = { 0.0, 255.0 };//
	const float* channel_ranges = channel_range;
	int number_bins = 255;
	//Histogram ��� �� �׸���                                                                  
	//void calcHist( const Mat* images, int nimages, const int* channels, InputArray mask, SparseMat& hist, int dims, const int* histSize, const float** ranges, bool uniform=true, bool accumulate=false )
	calcHist(&img_1, //�м���� �̹��� array ����
		1, // �����̳� �̹��� ���� , array ����
		channel_numbers, // ������׷��� ����� ä�� ��ȣ
		Mat(),	//mask : ����ũ �ɼ�. Ư���� �̹��� ���� ������׷� ������ ����Ϸ��� mask ����.
				//����ũ ��� �� �ϸ� Mat() �Ǵ� noArray()
				//�����ϴϱ� Mat()
		histogram,	//hist : dims-������ ���Ǵ� ��� ������׷�
					//Mat or SparseMat�� �ڷ���
		1,	//dims : histogram�� ����, 1D�̱⿡ 1
		&number_bins,	// histogram�� �� ������ ũ�� : bin�� ũ�⿡ ���� int�� 
		&channel_ranges	//������׷��� �� ���� ���� ��谪�� �迭�� �迭(���� ������)
		//uniform : true�̸� ��� ������׷�. false�� ��յ� ������׷��ε� �� ��쿣 �� ���� �Ѱ踦 �����ؾ� ��
		//accumalte : true ���� false ����x(default)
	);

	// plot the histogram
	int hist_w = img_1.cols;
	int hist_h = img_1.rows;
	//cvRound : ���������� ��ȯ�Ҷ� �ݿø��� �Ѵ�
	int bin_w = cvRound((double)hist_w / number_bins);	//bin�� ������ ���ϱ� ���� �ݿø�
	//8bit unsinged , 1ä��
	Mat hist_img(hist_h, hist_w, CV_8UC1, Scalar::all(0));
	// ����ȭ
	//void normalize(InputArray src ����ȭ ���� array,
					//OutputArray dst ����ȭ ������ array ��¿�,
					//double alpha = 1,����ȭ ����
					//double beta = 0, ����ȭ ����(���� ����ȭ�� �ƴ� ��� ������)
					//int norm_type = NORM_L2, 
					//int dtype = -1,
					//InputArray mask = noArray())
					//cv2.NORM_MINMAX: alpha�� beta �������� ����ȭ,
					//cv2.NORM_L1 : ��ü ������ ����, cv2.NORM_L2 :���� ���ͷ� ����ȭ, cv2.NORM_INF: �ִ����� ����
	//���󿡼� Ư�� �κп� ���� �ִ� ���� ��ü �������� ���� �����ϰ� �ϵ��� ����� ���
	normalize(histogram, histogram, 0, hist_img.rows, NORM_MINMAX, -1, Mat());
	//NORM_MINMAX: grayscale �� ���� 
	for (int i = 1; i < number_bins; i++)
	{
		//cv2.line(������ �׸� �̹��� img,
		//pt1, pt2,: ������ �������� ����, x,y Ʃ��
		//color : �� ���� �Ǵ� ���,
		//thickness = None ����, 
		//lineType = None �� Ÿ��, 
			//8 (or omitted) - 8-connected line.
			//4 - 4 - connected line.
			//CV_AA - antialiased line.
		//shift = None �׸��� ��ǥ ���� ��� ����)
		line(hist_img,// �̹��� 
			Point(bin_w * (i - 1), hist_h - cvRound(histogram.at<float>(i - 1))), 
			Point(bin_w * (i), hist_h - cvRound(histogram.at<float>(i))), 
			Scalar(255, 0, 0),	//����
			1,	//����
			8, //��Ÿ�� 
			0	//��Һ���
		);
	}
	//void imshow(const string& winname, InputArray mat)
	imshow("Origianl", img_1);
	imshow("Histogram", hist_img);



	// ���� ��
	//imshow("img_mul", img_2);
	//���� ��
	//imshow("img_div", img_3);

	waitKey(0);
	//Ű �Է��� ��ٸ��� �ð� 0 ���Ѵ�� �̿��� ���� ms������ ��ٸ�

	return 0;
}


//#include <opencv2/opencv.hpp>
//
//using namespace cv;
//using namespace std;
//
//int main(int ac, char** av) {
//
//	Mat color_img = imread("C:\\Users\\4DiVision\\Downloads\\Lenna.png");
//	Mat grayscale_img;
//
//	cvtColor(color_img, grayscale_img, COLOR_BGR2GRAY);
//
//	imshow("color_img", color_img);
//	imshow("grayscale_img", grayscale_img);
//	waitKey(0);
//
//	return 0;
//}