// 演習1 入力画像に平均化フィルタ、ガウシアンフィルタを適用して表示

#include <opencv2/opencv.hpp>
#include <string>

using namespace std;

void blur() {}

void filter(char *name) {
    cv::Mat image = cv::imread(name);
    cv::Mat blurImage3;
    cv::Mat blurImage7;
    cv::Mat gaussianImage3;
    cv::Mat gaussianImage7;

    if(image.empty()) {
        cout << "画像ファイルを読み込めませんでした" << endl;
        return;
    }

    // 平均化フィルタ
    cv::blur(image, blurImage3, cv::Size(3, 3));
    cv::blur(image, blurImage7, cv::Size(7, 7));
    // ガウシアンフィルタ
    cv::blur(image, gaussianImage3, cv::Size(3, 3));
    cv::blur(image, gaussianImage7, cv::Size(7, 7));

    cv::imshow("input", image);
    cv::imshow("blur-3*3", blurImage3);
    cv::imshow("blur-7*7", blurImage7);
    cv::imshow("gaussian-3*3", gaussianImage3);
    cv::imshow("gaussian-7*7", gaussianImage7);

    cv::waitKey();
}

int main(int argc, char **argv) {
    if(argc < 2) {
        filter("sample.jpg");
    } else {
        filter(argv[1]);
    }
    return 0;
}