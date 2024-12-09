// 第9回演習4 「ノイズ除去」

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

// 画像処理を行う関数
void morpho(const std::string &filename) {
    // 画像ファイルの読み込み
    cv::Mat originalImage = cv::imread(filename, cv::IMREAD_GRAYSCALE);

    if(originalImage.empty()) {
        cerr << "画像を読み込めませんでした: " << filename << endl;
        return;
    }

    // 二値画像に変換
    cv::Mat binaryImage;
    cv::threshold(originalImage, binaryImage, 128, 255, cv::THRESH_BINARY);

    cv::Mat currentImage = binaryImage.clone();

    while(true) {
        // 現在の画像を表示
        cv::imshow("現在の画像", currentImage);
        char key = static_cast<char>(cv::waitKey(0));

        if(key == 'e') {
            // erodeを適用
            cv::erode(currentImage, currentImage, cv::Mat());
            cout << "erodeを適用しました。\n";
        } else if(key == 'd') {
            // dilateを適用
            cv::dilate(currentImage, currentImage, cv::Mat());
            cout << "dilateを適用しました。\n";
        } else if(key == 's') {
            // ファイルに保存
            string outputFilename;
            cout << "保存するファイル名を入力してください: ";
            cin >> outputFilename;
            cv::imwrite(outputFilename, currentImage);
            cout << "ファイルに保存しました: " << outputFilename << "\n";
        } else if(key == 'r') {
            // 最初の状態にリセット
            currentImage = binaryImage.clone();
            cout << "画像を最初の状態に戻しました。\n";
        } else if(key == 'q') {
            // プログラムを終了
            break;
        } else {
            cout << "無効な入力です。もう一度試してください。\n";
        }
    }

    cv::destroyAllWindows();
}

int main(int argc, char **argv) {
    if(argc != 2) {
        cerr << "使い方: " << argv[0] << " <画像ファイル名>\n";
        return -1;
    }

    // コマンド引数で指定されたファイル名をmorpho関数に渡して処理
    string filename = argv[1];
    morpho(filename);

    return 0;
}
