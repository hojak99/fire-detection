#include <opencv2\opencv.hpp>

int main()
{
	cv::VideoCapture video("test_fire_2.mp4");

	// 비디오를 열지 못할 시에 "Can not open video" 출력
	if (!video.isOpened()) {
		std::cout << "Can not open video" << std::endl;
		return 0;
	}

	// 비디오 프레임을 담을 Mat형 변수
	cv::Mat originalFrame;
	cv::Mat resultFrame;

	// "FireVideo"라는 윈도우 창을 생성
	cv::namedWindow("OriginalVideo", cv::WINDOW_AUTOSIZE);
	cv::namedWindow("ResultVideo", cv::WINDOW_AUTOSIZE);

	while (1) {

		// 비디오 영상 프레임을 frame 변수에 받기
		video >> originalFrame;

		// 주변 픽셀들의 값을 이용해 평균을 적용하여 잡음 제거함
		cv::medianBlur(originalFrame, resultFrame, 5);

		// 윈도우 창에 비디오 영상 프레임을 받는 변수를 이용해 출력
		cv::imshow("OriginalVideo", originalFrame);
		cv::imshow("ResultVideo", resultFrame);

		// "esc" 키를 눌렀을 시에 break
		if (cv::waitKey(30) == 27) {
			break;
		}
	}

	// 윈도우 창 모두 삭제
	cv::destroyAllWindows();
	// Mat 형 변수 release;
	originalFrame.release();
	resultFrame.release();

	video.release();

	return 0;
}

