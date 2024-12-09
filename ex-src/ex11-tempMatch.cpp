// 第11回演習2 テンプレートマッチング
// 22FI102 堀江和馬

#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>

using namespace std;

void applyColormapAndDisplay(const cv::Mat &map, const string &windowName) {
    cv::Mat coloredMap;
    cv::applyColorMap(map, coloredMap, cv::COLORMAP_JET);
    cv::imshow(windowName, coloredMap);
}

void templateMatch(const char *fileName, const char *templName) {
    cv::Mat image = cv::imread(fileName);
    if(image.empty()) {
        cerr << "入力画像読み込み失敗" << endl;
        return;
    }
    cv::Mat templ = cv::imread(templName);
    if(templ.empty()) {
        cerr << "テンプレート画像読み込み失敗" << endl;
        return;
    }

    cv::Mat resultSQDIFF, resultCCORR, resultCCOEFF;
    cv::Mat normalizedSQDIFF, normalizedCCORR, normalizedCCOEFF;

    // 各種テンプレートマッチングの実行
    cv::matchTemplate(image, templ, resultSQDIFF, cv::TM_SQDIFF_NORMED);
    cv::matchTemplate(image, templ, resultCCORR, cv::TM_CCORR_NORMED);
    cv::matchTemplate(image, templ, resultCCOEFF, cv::TM_CCOEFF_NORMED);

    // 0～255に正規化
    resultSQDIFF.convertTo(normalizedSQDIFF, CV_8U, 255.0);
    resultCCORR.convertTo(normalizedCCORR, CV_8U, 255.0);
    resultCCOEFF.convertTo(normalizedCCOEFF, CV_8U, 255.0);

    // 疑似カラー化して表示
    cv::imshow("Input", image);
    cv::imshow("Template", templ);

    applyColormapAndDisplay(normalizedSQDIFF, "SQDIFF_NORMED");
    applyColormapAndDisplay(normalizedCCORR, "CCORR_NORMED");
    applyColormapAndDisplay(normalizedCCOEFF, "CCOEFF_NORMED");

    cv::waitKey();
}

int main(int argc, char *argv[]) {
    if(argc < 3) {
        cerr << "使用方法: " << argv[0] << " 入力画像 テンプレート画像" << endl;
    } else {
        templateMatch(argv[1], argv[2]);
    }
    return 0;
}
