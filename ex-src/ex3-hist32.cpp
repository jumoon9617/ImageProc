// 演習4_入力画像の輝度値のヒストグラムを32ビンで表示する

#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>

using namespace std;

// 1ch画像の度数表を作成する関数
void calcHistogram(cv::Mat src, vector<int> &histVector) {
    // 各画素値の頻度を算出
    int rows = src.rows, cols = src.cols;
    for(int y = 0; y < rows; y++) {
        uchar *p = src.ptr(y);
        for(int x = 0; x < cols; x++) {
            int binIndex = p[x] / 8;
            histVector[binIndex]++;
        }
    }
}
// ヒストグラムをコンソールへ出力する関数
void printHistogram(vector<int> &histVector) {
    int length = histVector.size();
    for(int i = 0; i < length; i++) {
        std::cout << i << " : " << histVector[i] << std::endl;
    }
}

void barGraph(cv::Mat hist, vector<int> &histVector) {
    // グラフ幅
    int width = hist.cols;
    // グラフ高さ
    int height = hist.rows;
    // 要素数
    int num = histVector.size();
    cout << "size of histVector: " << num << endl;
    // 最大要素
    int max = histVector[0];
    for(int i = 1; i < num; i++) {
        if(histVector[i] > max)
            max = histVector[i];
    }
    // または int max = *max_element( histVector.begin(), histVector.end() );
    // 棒グラフ配置設計
    double dw = (double)width / (num * 2 + 1); // 棒の幅と間隔を同じに
    cout << "size of bar width: " << dw << endl;
    double dh = (double)height / max; // 度数あたりの高さ画素数
    cout << "height unit: " << dh << endl;

    hist = cv::Scalar::all(255); // 全面白色で初期化
    // 各棒の描画
    for(int i = 0; i < num; i++) {
        double x = dw * (2 * i + 1); // 棒グラフ内描画用x座標
        double y = height - histVector[i] * dh; // 棒グラフ内描画用y座標
        cout << "i, count: " << i << ", " << histVector[i] << endl;
        cv::rectangle(hist, cv::Rect2d(x, y, dw, histVector[i] * dh),
                      cv::Scalar(255, 0, 0), cv::FILLED);
    }
    return;
}

// 1ch画像のヒストグラムをコンソールへ出力する関数
void calcAndPrintHistogram(char **argv) {
    cv::Mat image = cv::imread(argv[1]);
    cv::Mat gray;
    if(image.empty()) {
        std::cout << "画像読み込み失敗" << std::endl;
        return;
    }
    cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY); // グレースケール化
    vector<int> histVector(32);                    // 度数表宣言
    calcHistogram(gray, histVector);               // 度数表作成

    // ウィンドウ設定
    double width = atoi(argv[2]);
    double height = atoi(argv[3]);
    cv::Mat hist(cv::Size(width, height), CV_8UC3);
    // printHistogram(histVector); // ヒストグラムを出力
    barGraph(hist, histVector);
    cv::imshow("image", image);
    cv::imshow("gray", gray);
    cv::imshow("hist", hist);
    cv::waitKey();
}
int main(int argc, char *argv[]) {
    char *args[4] = {argv[0], "sample.jpg", "600", "300"};
    if(argc >= 2)
        args[1] = argv[1];
    if(argc >= 3)
        args[2] = argv[2];
    if(argc >= 4)
        args[3] = argv[3];
    calcAndPrintHistogram(args);
    return 0;
}