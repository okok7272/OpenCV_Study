#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int ac, char** av) {


	//Mat : Matrix 행렬
	//Mat(int rows 행, int cols 열 , int type 타입, const Scalar& s 초기값)
	Mat img_1 = imread("C:\\Users\\4DiVision\\Downloads\\Lenna.png", 0);    //이미지를 grayscale로 불러옴
	//Mat imread(const string& filename, int flags=IMREAD_COLOR )
	//IMREAD_ANYCOLOR | IMREAD_ANYDEPTH

	//명암 변화 
	//Mat img_2 = img_1 * 2;
	//Mat img_3 = img_1 / 2;
	Mat img_hist;


	// 이미지의 히스토그램 계산
	//typedef Mat MatND; core.hpp (version 2.4.8)
	MatND histogram;
	// 3채널에선 세가지의 색상이 가능하고 1채널에서는 흑 또는 백의 색상
	const int* channel_numbers = { 0 }; //채널이 한개라서 0
	float channel_range[] = { 0.0, 255.0 };//
	const float* channel_ranges = channel_range;
	int number_bins = 255;
	//Histogram 계산 및 그리기                                                                  
	//void calcHist( const Mat* images, int nimages, const int* channels, InputArray mask, SparseMat& hist, int dims, const int* histSize, const float** ranges, bool uniform=true, bool accumulate=false )
	calcHist(&img_1, //분석대상 이미지 array 형태
		1, // 영상이나 이미지 개수 , array 형태
		channel_numbers, // 히스토그램을 계산할 채널 번호
		Mat(),	//mask : 마스크 옵션. 특정한 이미지 내의 히스토그램 영역을 사용하려면 mask 생성.
				//마스크 사용 안 하면 Mat() 또는 noArray()
				//사용안하니까 Mat()
		histogram,	//hist : dims-차원의 계산되는 출력 히스토그램
					//Mat or SparseMat의 자료형
		1,	//dims : histogram의 차원, 1D이기에 1
		&number_bins,	// histogram의 각 차원의 크기 : bin의 크기에 대한 int형 
		&channel_ranges	//히스토그램의 각 차원 빈의 경계값의 배열의 배열(이중 포인터)
		//uniform : true이면 등간격 히스토그램. false면 비균등 히스토그램인데 이 경우엔 각 빈의 한계를 지정해야 함
		//accumalte : true 누적 false 누적x(default)
	);

	// plot the histogram
	int hist_w = img_1.cols;
	int hist_h = img_1.rows;
	//cvRound : 정수형으로 변환할때 반올림을 한다
	int bin_w = cvRound((double)hist_w / number_bins);	//bin의 가로폭 구하기 위한 반올림
	//8bit unsinged , 1채널
	Mat hist_img(hist_h, hist_w, CV_8UC1, Scalar::all(0));
	// 정규화
	//void normalize(InputArray src 정규화 이전 array,
					//OutputArray dst 정규화 이후의 array 출력용,
					//double alpha = 1,정규화 구간
					//double beta = 0, 정규화 구간(구간 정규화가 아닌 경우 사용안함)
					//int norm_type = NORM_L2, 
					//int dtype = -1,
					//InputArray mask = noArray())
					//cv2.NORM_MINMAX: alpha와 beta 구간으로 정규화,
					//cv2.NORM_L1 : 전체 합으로 나눔, cv2.NORM_L2 :단위 벡터로 정규화, cv2.NORM_INF: 최댓값으로 나눔
	//영상에서 특정 부분에 몰려 있는 값을 전체 영역으로 골고루 분포하게 하도록 만드는 방법
	normalize(histogram, histogram, 0, hist_img.rows, NORM_MINMAX, -1, Mat());
	//NORM_MINMAX: grayscale 을 위한 
	for (int i = 1; i < number_bins; i++)
	{
		//cv2.line(라인을 그릴 이미지 img,
		//pt1, pt2,: 직선의 시작점과 끝점, x,y 튜플
		//color : 선 색상 또는 밝기,
		//thickness = None 굵기, 
		//lineType = None 선 타입, 
			//8 (or omitted) - 8-connected line.
			//4 - 4 - connected line.
			//CV_AA - antialiased line.
		//shift = None 그리기 좌표 값의 축소 비율)
		line(hist_img,// 이미지 
			Point(bin_w * (i - 1), hist_h - cvRound(histogram.at<float>(i - 1))), 
			Point(bin_w * (i), hist_h - cvRound(histogram.at<float>(i))), 
			Scalar(255, 0, 0),	//색상
			1,	//굵기
			8, //선타입 
			0	//축소비율
		);
	}
	//void imshow(const string& winname, InputArray mat)
	imshow("Origianl", img_1);
	imshow("Histogram", hist_img);



	// 색상 곱
	//imshow("img_mul", img_2);
	//나눈 것
	//imshow("img_div", img_3);

	waitKey(0);
	//키 입력을 기다리는 시간 0 무한대기 이외의 숫자 ms단위로 기다림

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