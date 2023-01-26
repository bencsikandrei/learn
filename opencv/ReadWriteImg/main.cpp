#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

int main() {
	// Read images
	cv::Mat color { cv::imread("../img/lena1.jpg") };
	cv::Mat gray { cv::imread("../img/lena1.jpg", false) };
	// Write an image
	cv::imwrite("lenaGray.jpg", gray);
	// Get a pixel
	int row { color.rows - 1 };
	int col { color.cols - 1 };

	// Get one pixel as a Vec3b
	cv::Vec3b pixel { color.at<cv::Vec3b>(row, col) };

	// Print a pixel info
	std::cout << "Pixel value (BGR) : ("
		<< static_cast<int>(pixel[0]) << ','
		<< static_cast<int>(pixel[1]) << ','
		<< static_cast<int>(pixel[2]) << ')'
		<< '\n';

	// Show an image
	cv::imshow("Color image", color);
	cv::imshow("Grayscale", gray);

	// Wait for input indefinetely
	cv::waitKey(0);
	return 0;
}
