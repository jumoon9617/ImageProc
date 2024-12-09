// 第11回演習1 ハフ変換
// 22FI102 堀江和馬

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

void cannyAndHough(cv::Mat src, cv::Mat &dst, double rho, double theta,
                   int threshold, double minL, double maxLineGap) {
    using namespace cv;

    Mat edges;
    Canny(src, edges, 100, 200, 3);
    cvtColor(edges, dst, COLOR_GRAY2BGR);
    vector<Vec4i> lines;

    HoughLinesP(edges, lines, rho, theta, threshold, minL, maxLineGap);
    for(size_t i = 0; i < lines.size(); i++) {
        line(dst, Point(lines[i][0], lines[i][1]),
             Point(lines[i][2], lines[i][3]), Scalar(0, 0, 255), 2, 8);
    }
}

int main(int argc, char *argv[]) {
    cv::Mat frame;
    cv::VideoCapture cap;
    bool useCamera = true;

    if(argc > 1) {
        // 画像ファイルが指定された場合
        frame = cv::imread(argv[1]);
        if(frame.empty()) {
            cerr << "画像ファイルを読み込めませんでした: " << argv[1] << endl;
            return -1;
        }
        useCamera = false;
    } else {
        // カメラ入力を使用
        cap.open(0);
        if(!cap.isOpened()) {
            cerr << "カメラ入力失敗" << endl;
            return -1;
        }
    }

    cout << "q: 終了, u/d: 閾値 +1/-1, p/m: 最小線分長 +1/-1" << endl;

    int threshold = 100;
    double minL = 50;

    while(true) {
        if(useCamera) {
            cap >> frame; // カメラからの画像を取得
            if(frame.empty()) {
                cerr << "カメラ入力待機中" << endl;
                continue;
            }
        }

        cv::Mat dst;
        cannyAndHough(frame, dst, 1, CV_PI / 180, threshold, minL, 10);

        cv::imshow("Input", frame);
        cv::imshow("Hough Transform", dst);

        char key = (char)cv::waitKey(33);
        if(key == 'q') {
            break;
        } else if(key == 'u') {
            threshold++;
            cout << "閾値(threshold): " << threshold << endl;
        } else if(key == 'd') {
            threshold = max(1, threshold - 1);
            cout << "閾値(threshold): " << threshold << endl;
        } else if(key == 'p') {
            minL++;
            cout << "最小線分長(minL): " << minL << endl;
        } else if(key == 'm') {
            minL = max(1.0, minL - 1);
            cout << "最小線分長(minL): " << minL << endl;
        }
    }

    return 0;
}
