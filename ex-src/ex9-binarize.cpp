// 第9回演習1 「2値化」

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

void binarize(const string &filename) {
    // 画像ファイルの読み込み
    cv::Mat colorImage = cv::imread(filename, cv::IMREAD_COLOR);

    if(colorImage.empty()) {
        cerr << "画像を読み込めませんでした: " << filename << endl;
        return;
    }

    // カラー画像をグレースケールに変換
    cv::Mat grayImage;
    cv::cvtColor(colorImage, grayImage, cv::COLOR_BGR2GRAY);

    // 大津の2値化
    cv::Mat otsuBinary;
    double otsuThresh = cv::threshold(grayImage, otsuBinary, 0, 255,
                                      cv::THRESH_BINARY | cv::THRESH_OTSU);

    // 閾値128での2値化
    cv::Mat fixedBinary;
    cv::threshold(grayImage, fixedBinary, 128, 255, cv::THRESH_BINARY);

    // 結果の表示
    cv::imshow("元のグレースケール画像", grayImage);
    cv::imshow("大津の2値化", otsuBinary);
    cv::imshow("閾値128の2値化", fixedBinary);

    cout << "大津の2値化の閾値: " << otsuThresh << "\n";

    while(true) {
        char key = static_cast<char>(cv::waitKey(0));
        if(key == 'q') {
            break;
        } else {
            cout << "無効な入力です。もう一度試してください。\n";
        }
    }

    // ウィンドウを破棄
    cv::destroyAllWindows();
}

int main(int argc, char **argv) {
    if(argc != 2) {
        cerr << "使い方: " << argv[0] << " <画像ファイル名>\n";
        return -1;
    }

    // コマンド引数で指定されたファイル名をbinarize関数に渡して処理
    string filename = argv[1];
    binarize(filename);

    return 0;
}
