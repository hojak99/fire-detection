#include <opencv2\opencv.hpp>

int main()
{
	cv::VideoCapture video("test_fire_2.mp4");

	if (!video.isOpened()) {
		std::cout << "Can not open video" << std::endl;
		return 0;
	}

	cv::Mat frame;
	cv::namedWindow("FireVideo", 1);

	while (1) {
		video >> frame;

		cv::imshow("FireVideo", frame);

		if (cv::waitKey(30) == 27) {
			break;
		}
	}

	cv::destroyAllWindows();
	frame.release();

	return 0;
}