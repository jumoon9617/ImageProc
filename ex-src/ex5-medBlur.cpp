#include <opencv2/opencv.hpp>
#include <string>

using namespace std;

void medBlur(char *name, int ksize) {
    if(ksize <= 0 || ksize % 2 == 0) {
        cout << "カーネルサイズは正の奇数です" << endl;
        return;
    }

    cv::Mat image = cv::imread(name);
    if(image.empty()) {
        cout << "画像ファイルを読み込めませんでした" << endl;
        return;
    }

    cv::Mat gray;
    cv::cvtColor(image, gray, cv::COLOR_RGB2GRAY);

    cv::Mat medImage;
    cv::medianBlur(gray, medImage, ksize);

    cv::imshow("input", image);
    cv::imshow("gray", gray);
    cv::imshow("medImage", medImage);

    cv::waitKey(0);
}

int main(int argc, char **argv) {
    if(argc != 3) {
        return -1;
    }

    int ksize = atoi(argv[2]);
    medBlur(argv[1], ksize);

    return 0;
}