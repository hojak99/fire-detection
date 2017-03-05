#include <opencv2\opencv.hpp>
#include <vector>

// 움직이는 픽셀 인식하는 메소드
cv::Mat	pixelMotion();

// 불 RGB 인식하는 메소드
cv::Mat fireRGB(cv::Mat frame);

int main()
{
	cv::VideoCapture video("test_fire_2.mp4");

	// 비디오의 FPS 를 가져온다.
	int videoFPS = video.get(CV_CAP_PROP_FPS);

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
		cv::cvtColor(originalFrame, originalFrame, CV_BGR2YCrCb);

		// 주변 픽셀들의 값을 이용해 평균을 적용하여 잡음 제거함
		cv::medianBlur(originalFrame, resultFrame, 3);
		resultFrame = fireRGB(resultFrame);
			
		// 윈도우 창에 비디오 영상 프레임을 받는 변수를 이용해 출력
		cv::imshow("OriginalVideo", originalFrame);
		cv::imshow("ResultVideo", resultFrame);	

		// videoFPS 값마다 검사. "esc" 키를 눌렀을 시에 break
		if (cv::waitKey(33) == 27) {
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



/*
	움직이는 픽셀들 중 불에 대한 RGB 값들을 검사하여 불을 인식 시킨다.
	추후에 연기 인식도 추가.
*/
cv::Mat pixelMotion()
{
	return cv::Mat();
}

cv::Mat fireRGB(cv::Mat frame)
{
	std::vector<cv::Mat> channels;

	// 채널 분리. BGR 순서대로 분리된다.
	cv::split(frame, channels);
	
	double maxVal = 0;
	double minVal = 0;

	IplImage *redChannelImg = new IplImage(channels[2]);

	cvMaxS(redChannelImg, 150, redChannelImg);

	// R 채널 반환
	//channels[2] = cv::cvarrToMat(redChannelImg);
	
	return channels[2];
}