// 演習3 射影変換

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

int key = -1;
cv::Point startp;  // 矩形の始点
cv::Point secondp; // 矩形の第2点
cv::Point thirdp;  // 矩形の第3点
cv::Point endp;    // 矩形の終点
cv::Mat pers_mat;  // 射影変換用3x3行列
int p_count = 0;   // 左マウスクリックのカウント

void onFourMouseClicks(int event, int x, int y, int flag, void *param) {
    using namespace cv;
    Mat *mat = static_cast<Mat *>(param);
    Mat c = mat->clone();

    switch(event) {
    case cv::MouseEventTypes::EVENT_LBUTTONDOWN:
        if(p_count == 0) {
            cout << "始点：(" << x << " , " << y << ")" << endl;
            startp = Point(x, y);
            p_count++;
        } else if(p_count == 1) {
            cout << "第2点：(" << x << " , " << y << ")" << endl;
            secondp = Point(x, y);
            p_count++;
        } else if(p_count == 2) {
            cout << "第3点：(" << x << " , " << y << ")" << endl;
            thirdp = Point(x, y);
            p_count++;
        } else if(p_count == 3) {
            cout << "終点：(" << x << " , " << y << ")" << endl;
            endp = Point(x, y);
            p_count++;

            // 射影変換
            Mat outImg = Mat::zeros(c.rows, c.cols, CV_8UC3);
            const Point2f src_pt[] = {startp, secondp, thirdp, endp};
            const Point2f dst_pt[] = {Point2f(0.0, 0.0), Point2f(c.cols, 0.0),
                                      Point2f(c.cols, c.rows),
                                      Point2f(0.0, c.rows)};

            pers_mat = getPerspectiveTransform(src_pt, dst_pt);
            warpPerspective(*mat, outImg, pers_mat, outImg.size());
            imshow("Perspective Image", outImg);
        }
        break;

    case cv::MouseEventTypes::EVENT_MOUSEMOVE:
        if(p_count == 1) {
            line(c, startp, Point(x, y), Scalar(0, 250, 0), 2);
        } else if(p_count == 2) {
            line(c, startp, secondp, Scalar(0, 250, 0), 2);
            line(c, secondp, Point(x, y), Scalar(0, 250, 0), 2);
        } else if(p_count == 3) {
            line(c, startp, secondp, Scalar(0, 250, 0), 2);
            line(c, secondp, thirdp, Scalar(0, 250, 0), 2);
            line(c, thirdp, Point(x, y), Scalar(0, 250, 0), 2);
        }
        imshow("mouse input window", c);
        break;
    }
}

// マウスクリックした4点を入力画像と同サイズの画像の4隅に射影変換する
void perspective(char *fileName) {
    cv::Mat image = cv::imread(fileName);
    if(image.empty()) {
        cout << "画像読み込み失敗" << endl;
        return;
    }
    cv::namedWindow("mouse input window");

    cv::setMouseCallback("mouse input window", onFourMouseClicks,
                         (void *)&image);

    cv::imshow("mouse input window", image);

    while(cv::waitKey() != 'q')
        ;
}

int main(int argc, char *argv[]) {
    if(argc < 2)
        perspective("sample.jpg");
    else
        perspective(argv[1]);
    return 0;
}
