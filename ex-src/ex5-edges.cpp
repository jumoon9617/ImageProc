#include <opencv2/opencv.hpp>
#include <string>

using namespace std;

int lowThreshold = 50;
int highThreshold = 150;
int laplacianKsize = 3;

void edgs(cv::VideoCapture &cap) {
    cv::Mat frame, gray, laplacianOutput, cannyOutput;

    cv::namedWindow("Laplacian edge", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Canny edge", cv::WINDOW_AUTOSIZE);

    while(true) {
        cap >> frame;
        if(frame.empty()) {
            cout << "フレームが読み込めません" << endl;
            break;
        }

        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

        laplacianKsize =
            (laplacianKsize % 2 == 1) ? laplacianKsize : laplacianKsize + 1;

        cv::Laplacian(gray, laplacianOutput, laplacianKsize);
        cv::convertScaleAbs(laplacianOutput, laplacianOutput);

        cv::Canny(gray, cannyOutput, lowThreshold, highThreshold);

        cv::imshow("Laplacian edge", laplacianOutput);
        cv::imshow("Canny edge", cannyOutput);

        char key = cv::waitKey(33);
        if(key == 'q') {
            break;
        } else if(key == 'i') {
            laplacianKsize += 2; // 'i'キーでLaplacianカーネルサイズを+2
            cout << "Laplacian kernel size: " << laplacianKsize << endl;
        } else if(key == 'f') {
            laplacianKsize = max(
                1, laplacianKsize - 2); // 'f'キーでLaplacianカーネルサイズを-2
            cout << "Laplacian kernel size: " << laplacianKsize << endl;
        } else if(key == 'u') {
            lowThreshold =
                min(255, lowThreshold + 5); // 'u'キーでCannyの閾値1を+5
            highThreshold = min(255, highThreshold + 5); // 閾値2も+5
            cout << "Canny low threshold: " << lowThreshold
                 << ", high threshold: " << highThreshold << endl;
        } else if(key == 'd') {
            lowThreshold =
                max(0, lowThreshold - 5); // 'd'キーでCannyの閾値1を-5
            highThreshold = max(0, highThreshold - 5); // 閾値2も-5
            cout << "Canny low threshold: " << lowThreshold
                 << ", high threshold: " << highThreshold << endl;
        }
    }

    cv::destroyAllWindows();
}

int main() {
    cv::VideoCapture cap(0);
    if(!cap.isOpened()) {
        cout << "カメラを開けませんでした" << endl;
        return -1;
    }
    edgs(cap);
    cap.release();
    return 0;
}