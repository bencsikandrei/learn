#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <memory>
#include <functional>
#include <type_traits>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

char const* keys
{
"{help h usage ? | | print this message}"
"{@video | | Video file, if not defined try to use webcamera}"
};

void releaseCapture(cv::VideoCapture* vc) {
	vc->release();
}

using videoCaptureRelease_t = void(cv::VideoCapture*);

typedef void(*releasePtrFunc)(cv::VideoCapture*);

template <typename T>
struct Type;

int main(int argc, char** argv) {
	// Videos
	cv::CommandLineParser parser { argc, argv, keys };
	parser.about("Video or Webcam");
	// Get some of the params if they exist
	if(parser.has("help")) {
			parser.printMessage();
	}
	std::string videoFile { parser.get<std::string>(0) };
	// Check if params are OK
	if(not parser.check()) {
		parser.printErrors();
		return 0;
	}

	cv::VideoCapture cap;
	if(not videoFile.empty()) {
		cap.open(videoFile);
	}
	else {
		cap.open(0);
	}
	// Check if opened
	if(not cap.isOpened()) {
		std::cerr << "Can not open capture device\n";
		return -1;
	}
	// Open a window
	cv::namedWindow("Video", 1);
	for(;;) {
		cv::Mat videoFrame{};
		cap >> videoFrame; // Frame
		cv::imshow("Video", videoFrame);
		if(cv::waitKey(30) >= 0) break;
	}
	// Wait for input indefinetely
	cap.release();
	return 0;
}
