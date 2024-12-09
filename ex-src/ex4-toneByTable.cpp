// 演習2 コントラスト変換

#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>

using namespace std;

void calcToneCurve(vector<int> &toneCurve) {
    for(int i = 0; i < toneCurve.size(); i++) {
        toneCurve[i] = 255 - i;
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
    calcToneCurve(gray, result);
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
