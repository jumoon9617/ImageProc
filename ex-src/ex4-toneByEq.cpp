// 演習1 グレースケール画像

#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>

using namespace std;

void calcDst(cv::Mat src, cv::Mat &dst) {
    dst = cv::Mat(cv::Size(src.cols, src.rows), CV_8UC1);
    for(int j = 0; j < src.rows; j++) {
        uchar *p = src.ptr(j);
        uchar *q = dst.ptr(j);
        for(int i = 0; i < src.cols; i++) {
            if(p[i] <= 85)
                q[i] = cv::saturate_cast<uchar>(2 * p[i]);
            else
                q[i] = cv::saturate_cast<uchar>(0.5 * p[i] + 128);
        }
    }
}

void processImage(char *name) {
    cv::Mat image = cv::imread(name);
    cv::Mat gray, result;
    if(image.empty()) {
        cout << "画像ファイルを読み込めませんでした" << endl;
        return;
    }
    cv::cvtColor(image, gray, cv::COLOR_RGB2GRAY);
    calcDst(gray, result);
    cv::imshow("Input", image);
    cv::imshow("Grays", gray);
    cv::imshow("Result", result);
    cv::waitKey();
}

int main(int argc, char **argv) {
    if(argc < 2) {
        processImage("sample.jpg");
    } else {
        processImage(argv[1]);
    }
    return 0;
}
