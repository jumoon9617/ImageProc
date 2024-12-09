// 演習4_RGBチャネルを分離してGチャネルを反転する

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

void camGrayN(char *name) {
    cv::Mat colorImage = cv::imread(name);
    cv::Mat matArray[3];
    cv::Mat dstImage;
    cv::Mat greenN;
    cv::split(colorImage, matArray);
    if(colorImage.empty()) {
        cout << "画像ファイルを読み込めませんでした" << endl;
        return;
    }

    cv::imshow("RGB image", colorImage);
    // cv::imshow("Blue", matArray[0]);
    // cv::imshow("Green", matArray[1]);
    // cv::imshow("Red", matArray[2]);
    greenN = ~matArray[1];
    matArray[1] = greenN;
    cv::merge(matArray, 3, dstImage);
    cv::imshow("dstImage", dstImage);
    cv::waitKey();
}

int main(int argc, char **argv) {
    if(argc < 2) {
        grayImage("sample.jpg");
    } else {
        grayImage(argv[1]);
    }
    return 0;
}