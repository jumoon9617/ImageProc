// 第9回演習5 「細線化」

#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;

// 画素数を数える関数
int calculateLineLength(const cv::Mat &image);

int main(int argc, char *argv[]) {
    // コマンド引数で画像ファイルを取得
    if(argc != 2) {
        cerr << "使い方: " << argv[0] << " <画像ファイル>" << endl;
        return -1;
    }

    // 画像ファイルを読み込む
    string imagePath = argv[1];
    cv::Mat image = cv::imread(imagePath, cv::IMREAD_GRAYSCALE);

    if(image.empty()) {
        cerr << "画像を読み込めませんでした: " << imagePath << endl;
        return -1;
    }

    // 細線化画像を表示
    cv::imshow("Skeleton Image", image);
    cv::waitKey(0);

    // 細線化画像の白画素数をカウント
    int lineLength = calculateLineLength(image);
    cout << "紐の長さ（白画素数）: " << lineLength << endl;

    return 0;
}

// 画素数を数える関数
int calculateLineLength(const cv::Mat &image) {
    // 白画素（255）の数をカウント
    int white_pixels = cv::countNonZero(image);
    return white_pixels;
}
