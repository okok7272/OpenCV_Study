#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int ac, char** av) {

	Mat color_img = imread("C:\\Users\\4DiVision\\Downloads\\Lenna.png");
	Mat grayscale_img;

	cvtColor(color_img, grayscale_img, COLOR_BGR2GRAY);

	imshow("color_img", color_img);
	imshow("grayscale_img", grayscale_img);
	waitKey(0);

	return 0;
}
