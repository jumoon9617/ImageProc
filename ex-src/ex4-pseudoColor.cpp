#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
#include <vector>

using namespace std;

void applyToneCurve(const cv::Mat &gray, cv::Mat &result) {
    result = cv::Mat::zeros(gray.size(), CV_8UC3);

    for(int y = 0; y < gray.rows; y++) {
        for(int x = 0; x < gray.cols; x++) {
            int pixelValue = gray.at<uchar>(y, x);
            int b, g, r;

            if(pixelValue < 64) {
                b = 255;
            } else if(pixelValue < 128) {
                b = -4 * pixelValue + 512;
            } else {
                b = 0;
            }

            if(pixelValue < 64) {
                g = 4 * pixelValue;
            } else if(pixelValue < 192) {
                g = 255;
            } else {
                g = -4 * pixelValue + 1020;
            }

            if(pixelValue < 128) {
                r = 0;
            } else if(pixelValue < 192) {
                r = 4 * pixelValue - 512;
            } else {
                r = 255;
            }

            result.at<cv::Vec3b>(y, x) = cv::Vec3b(b, g, r);
        }
    }
}

void processImage(const char *name) {
    cv::Mat image = cv::imread(name);
    cv::Mat gray, result;
    if(image.empty()) {
        cout << "画像ファイルを読み込めませんでした" << endl;
        return;
    }

    cv::cvtColor(image, gray, cv::COLOR_RGB2GRAY);

    applyToneCurve(gray, result);

    cv::imshow("Input", image);
    cv::imshow("Grayscale", gray);
    cv::imshow("Pseudo-color Result", result);
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
