// 演習3_RGBの各チャネルの分離

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

void split(char *name) {
    cv::Mat colorImage = cv::imread(name);
    cv::Mat matArray[3];
    cv::split(colorImage, matArray);
    if(colorImage.empty()) {
        cout << "画像ファイルを読み込めませんでした" << endl;
        return;
    }

    cv::imshow("RGB image", colorImage);
    cv::imshow("Blue", matArray[0]);
    cv::imshow("Green", matArray[1]);
    cv::imshow("Red", matArray[2]);
    cv::waitKey();
}

int main(int argc, char **argv) {
    if(argc < 2) {
        split("sample.jpg");
    } else {
        split(argv[1]);
    }
    return 0;
}