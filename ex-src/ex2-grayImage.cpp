// 演習1_カラー画像をグレースケール化して表示

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

void grayImage(char *name) {
    cv::Mat image = cv::imread(name);
    cv::Mat gray;
    if(image.empty()) {
        cout << "画像ファイルを読み込めませんでした" << endl;
        return;
    }

    cv::cvtColor(image, gray, cv::COLOR_RGB2GRAY);
    cv::imshow("Input", image);
    cv::imshow("Output", gray);
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