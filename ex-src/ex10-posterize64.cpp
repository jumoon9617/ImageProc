// 第10回演習1 限定色表示
// 22FI102 堀江和馬

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void posterize64(const string &filename) {
    // 画像を読み込む
    Mat img = imread(filename);
    if(img.empty()) {
        cerr << "Error: Could not open or find the image!" << endl;
        return;
    }

    Mat posterized = img.clone();

    for(int y = 0; y < img.rows; y++) {
        for(int x = 0; x < img.cols; x++) {
            Vec3b &pixel = posterized.at<Vec3b>(y, x);

            for(int c = 0; c < 3; c++) {
                pixel[c] = (pixel[c] / 64) * 64 + 32;
            }
        }
    }

    imshow("Original Image", img);
    imshow("Posterized Image", posterized);

    imwrite("posterized_image.jpg", posterized);

    waitKey();
}

int main(int argc, char **argv) {
    if(argc < 2) {
        posterize64("sample.jpg");
    } else {
        posterize64(argv[1]);
    }
    return 0;
}
