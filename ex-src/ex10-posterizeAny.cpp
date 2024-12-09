// 第10回演習2 BGRの各チャネル分割数をコマンド引数で指定
// 22FI102 堀江和馬

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void posterizeAny(const string &filename, int divisions) {
    // 画像を読み込む
    Mat img = imread(filename);
    if(img.empty()) {
        cerr << "Error: Could not open or find the image!" << endl;
        return;
    }

    // 各チャネルの1区間のサイズ
    int step = 256 / divisions;

    // 画像のサイズと型を維持して新しいマットを作成
    Mat posterized = img.clone();

    // 各画素を量子化
    for(int y = 0; y < img.rows; y++) {
        for(int x = 0; x < img.cols; x++) {
            Vec3b &pixel = posterized.at<Vec3b>(y, x);

            for(int c = 0; c < 3; c++) { // B, G, Rの3チャネル
                pixel[c] = (pixel[c] / step) * step +
                           step / 2; // 量子化し、中央値に補正
            }
        }
    }

    imshow("Original Image", img);
    imshow("Posterized Image", posterized);

    imwrite("posterized_image.jpg", posterized);

    waitKey();
}

int main(int argc, char **argv) {
    int divisions = 4;

    if(argc < 2) {
        cout << "Usage: " << argv[0] << " <image path> [divisions]" << endl;
        cout << "Example: " << argv[0] << " sample.jpg 4" << endl;
        return 1;
    }

    if(argc > 2) {
        if(divisions < 1 || divisions > 128) {
            cerr << "Error: Divisions must be between 1 and 128." << endl;
            return 1;
        }
    }

    posterizeAny(argv[1], divisions);

    return 0;
}
