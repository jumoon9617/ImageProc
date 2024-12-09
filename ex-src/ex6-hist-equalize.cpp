/* 演習6 ヒストグラム平坦化 */

#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

using namespace std;

void manualEqualizeHist(const cv::Mat &src, cv::Mat &dst) {
    dst = src.clone();
    int hist[256] = {0};

    // (1) ヒストグラムの計算
    for(int i = 0; i < src.rows; ++i) {
        for(int j = 0; j < src.cols; ++j) {
            int pixelVal = src.at<uchar>(i, j);
            hist[pixelVal]++;
        }
    }

    // (2) 累積分布を計算
    int cumulativeHist[256] = {0};
    cumulativeHist[0] = hist[0];
    for(int i = 1; i < 256; ++i) {
        cumulativeHist[i] = cumulativeHist[i - 1] + hist[i];
    }

    // (3) ルックアップテーブル(LUT)を作成
    int totalPixels = src.rows * src.cols;
    uchar LUT[256] = {0};
    for(int i = 0; i < 256; ++i) {
        LUT[i] =
            cv::saturate_cast<uchar>(255.0 * cumulativeHist[i] / totalPixels);
    }

    // (4) LUTを使用してピクセル値を変換
    for(int i = 0; i < src.rows; ++i) {
        for(int j = 0; j < src.cols; ++j) {
            dst.at<uchar>(i, j) = LUT[src.at<uchar>(i, j)];
        }
    }
}

// BGRそれぞれのチャンネルにヒストグラム平坦化を適用
void equalizeBGR(const cv::Mat &src, cv::Mat &dst) {
    vector<cv::Mat> bgrChannels;
    cv::split(src, bgrChannels);

    // B、G、Rそれぞれに平坦化
    for(int i = 0; i < 3; ++i) {
        manualEqualizeHist(bgrChannels[i], bgrChannels[i]);
    }

    // チャンネルを再結合
    cv::merge(bgrChannels, dst);
}

// HSV空間でVチャンネルにヒストグラム平坦化を適用
void equalizeHSV(const cv::Mat &src, cv::Mat &dst) {
    cv::Mat hsv;
    cv::cvtColor(src, hsv, cv::COLOR_BGR2HSV);

    vector<cv::Mat> hsvChannels;
    cv::split(hsv, hsvChannels);

    // Vチャンネルに平坦化
    manualEqualizeHist(hsvChannels[2], hsvChannels[2]);

    // HSVチャンネルを再結合してBGRに変換
    cv::merge(hsvChannels, hsv);
    cv::cvtColor(hsv, dst, cv::COLOR_HSV2BGR);
}

int main(int argc, char *argv[]) {
    string filename = (argc > 1) ? argv[1] : "sample.jpg";
    cv::Mat src = cv::imread(filename);

    if(src.empty()) {
        cerr << "Error: Could not open or find the image." << endl;
        return -1;
    }

    // BGRそれぞれのチャンネルにヒストグラム平坦化を適用
    cv::Mat bgrEqualized;
    equalizeBGR(src, bgrEqualized);

    // HSV空間でVチャンネルにのみヒストグラム平坦化を適用
    cv::Mat hsvEqualized;
    equalizeHSV(src, hsvEqualized);

    // 結果を表示
    cv::imshow("Original Image", src);
    cv::imshow("Equalized BGR Channels", bgrEqualized);
    cv::imshow("Equalized HSV (V channel only)", hsvEqualized);

    cv::waitKey(0);
    return 0;
}
