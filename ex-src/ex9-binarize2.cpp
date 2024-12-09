// 第9回演習2 「2値化」

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

void showHelp() {
    cout << "操作方法:\n"
         << " u : 閾値を増加\n"
         << " d : 閾値を減少\n"
         << " s : 現在の2値化画像をファイルに保存\n"
         << " q : プログラムを終了\n";
}

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

    // 初期設定
    int thresholdValue = 128;
    cv::Mat otsuBinary;
    double otsuThresh = cv::threshold(grayImage, otsuBinary, 0, 255,
                                      cv::THRESH_BINARY | cv::THRESH_OTSU);

    showHelp();

    cv::Mat fixedBinary;
    while(true) {
        // 現在の閾値で2値化
        cv::threshold(grayImage, fixedBinary, thresholdValue, 255,
                      cv::THRESH_BINARY);

        // 結果の表示
        cv::imshow("元のグレースケール画像", grayImage);
        cv::imshow("大津の2値化", otsuBinary);
        cv::imshow("閾値 " + to_string(thresholdValue) + " の2値化",
                   fixedBinary);

        char key = static_cast<char>(cv::waitKey(0));
        if(key == 'u') {
            // 閾値を増加
            thresholdValue = min(thresholdValue + 1, 255);
            cout << "閾値を増加: " << thresholdValue << endl;
        } else if(key == 'd') {
            // 閾値を減少
            thresholdValue = max(thresholdValue - 1, 0);
            cout << "閾値を減少: " << thresholdValue << endl;
        } else if(key == 's') {
            // ファイルに保存
            string outputFilename;
            cout << "保存するファイル名を入力してください: ";
            cin >> outputFilename;
            cv::imwrite(outputFilename, fixedBinary);
            cout << "ファイルに保存しました: " << outputFilename << "\n";
        } else if(key == 'q') {
            // プログラムを終了
            break;
        } else {
            cout << "無効な入力です。もう一度試してください。\n";
            showHelp();
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
