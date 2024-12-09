// 演習2 回転・拡縮

#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>

using namespace std;

// 引数で示す角度だけ反時計回りに回転する関数
void rotateScale(char *fileName, int angle, int centerX, int centerY,
                 float scale) {
    cv::Mat image = cv::imread(fileName);
    if(image.empty()) {
        std::cout << "画像読み込み失敗" << std::endl;
        return;
    }

    cv::Point center;   // 回転中心は
    center.x = centerX; // 画像の中心
    center.y = centerY;

    // 2次元のアフィン変換(ここでは回転)行列を求める
    //	Mat cv::getRotationMatrix2D	(Point2f center, double angle, double
    // scale) 	center: 入力画像における回転中心（座標原点は左上） 	angle:
    // 度単位で表される回転角度(正の値は，反時計回りの回転) 	scale:
    // 等方性スケーリング係数 	出力: 2×3 の出力行列へのポインタ
    cv::Mat mapMatrix = cv::getRotationMatrix2D(center, (double)angle, scale);
    cout << "Matrix row No.0 = " << mapMatrix.at<double>(0, 0) << ", "
         << mapMatrix.at<double>(0, 1) << ", " << mapMatrix.at<double>(0, 2)
         << endl;
    cout << "Matrix row No.1 = " << mapMatrix.at<double>(1, 0) << ", "
         << mapMatrix.at<double>(1, 1) << ", " << mapMatrix.at<double>(1, 2)
         << endl;

    // 画像のアフィン変換を行う
    //	void cv::warpAffine	(InputArray src, OutputArray dst, InputArray M,
    //		Size dsize, [int flags = INTER_LINEAR,
    //		[int	borderMode = BORDER_CONSTANT, [const Scalar &
    // borderValue = Scalar()]]]) 	src:入力画像 	dst:出力画像 	M: 2行 x
    // 3列 の変換行列 	dsize: 出力画像のサイズ 	flags: 補間手法 (default
    // cv::INTER_LINEAR (線形補間)) 	borderMode: 対応のとれない点を埋める方法
    //(default 0)
    //  borderValue: 対応のとれない点を埋める値(cv::BORDER_CONSTANTの場合)
    cv::Mat result;
    cv::warpAffine(image, result, mapMatrix, cv::Size(image.cols, image.rows));

    cv::imshow("Input", image);
    cv::imshow("Rotated", result);
    cv::waitKey();
}

int main(int argc, char *argv[]) {
    float defaultScale = 1.0;
    char *args[6] = {argv[0], "sample.jpg", "0", "0", "0", "1.0"};

    if(argc >= 2)
        args[1] = argv[1]; // 引数での入力画像指定
    if(argc >= 3)
        args[2] = argv[2]; // 引数での角度指定
    if(argc >= 4)
        args[3] = argv[3]; // 引数での回転の中心x座標指定
    if(argc >= 5)
        args[4] = argv[4]; // 引数での回転の中心y座標指定
    if(argc >= 6)
        args[5] = argv[5]; // 引数での拡縮率指定

    rotateScale(args[1], atoi(args[2]), atoi(args[3]), atoi(args[4]),
                atoi(args[5]));
    return 0;
}
