// 演習2_RGBカラー画像をHSVカラーが画像に変換してSチャネルの値を2倍にしてRGBカラーに戻す

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

    // sチャネルの値を2倍に
    cv::Mat sImage = matArray[1];
    double baseMag = 2.0;
    cv::Mat multiplySImage;
    cv::Mat dstImage;
    cv::multiply(sImage, baseMag, multiplySImage);
    matArray[1] = multiplySImage;
    cv::merge(matArray, 3, dstImage);

    // BGRカラーに
    cv::Mat s2Image;
    cv::cvtColor(dstImage, s2Image, cv::COLOR_HSV2BGR);

    cv::imshow("colorImage", bgrImage);
    cv::imshow("dstImage", dstImage);
    cv::imshow("s2-bgrImage", s2Image);
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