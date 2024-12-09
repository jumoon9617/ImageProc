// 演習1_BGRカラー画像のHSVカラー画像に変換、HSVそれぞれのチャネルをグレースケール画像として表示

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

void bgr2hsv(char *name) {
    cv::Mat bgrImage = cv::imread(name);
    if(bgrImage.empty()) {
        cout << "画像ファイルを読み込めませんでした" << endl;
        return;
    }
    // hsvへの変換
    cv::Mat hsvImage;
    cv::cvtColor(bgrImage, hsvImage, cv::COLOR_BGR2HSV);

    // 各チャネルをグレースケール画像に
    cv::Mat matArray[3];
    cv::split(hsvImage, matArray);
    cv::imshow("hue", matArray[0]);
    cv::imshow("saturation", matArray[1]);
    cv::imshow("value", matArray[2]);
    cv::waitKey();
}

int main(int argc, char **argv) {
    if(argc < 2) {
        bgr2hsv("sample.jpg");
    } else {
        bgr2hsv(argv[1]);
    }
    return 0;
}