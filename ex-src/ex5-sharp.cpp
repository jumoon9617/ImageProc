#include <opencv2/opencv.hpp>
#include <string>

using namespace std;

void blur(char *name) {
    cv::Mat image = cv::imread(name);
    if(image.empty()) {
        cout << "画像ファイルを読み込めませんでした" << endl;
        return;
    }
}

int main(int argc, char **argv) {
    if(argc < 2) {
        blur("sample.jpg");
    } else {
        blur(argv[1]);
    }
    return 0;
}