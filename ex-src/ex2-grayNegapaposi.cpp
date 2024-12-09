// 演習2_グレースケール画像をネガポジ反転

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

void grayN(char *name) {
    cv::Mat image = cv::imread(name);
    cv::Mat gray, grayN;
    if(image.empty()) {
        cout << "画像ファイルを読み込めませんでした" << endl;
        return;
    }

    cv::cvtColor(image, gray, cv::COLOR_RGB2GRAY);
    grayN = ~gray;
    cv::imshow("Input", image);
    cv::imshow("Output-gray", gray);
    cv::imshow("Output-grayN", grayN);
    cv::waitKey();
}

int main(int argc, char **argv) {
    if(argc < 2) {
        grayN("sample.jpg");
    } else {
        grayN(argv[1]);
    }
    return 0;
}