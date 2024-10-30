#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    // 打开摄像头
    VideoCapture cap(2);
    if (!cap.isOpened()) {
        cout << "无法打开摄像头" << endl;
        return -1;
    }

    Mat frame, gray, result;

    // 创建形态学核
    Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5));

    while (true) {
        cap >> frame; // 从摄像头捕获图像
        if (frame.empty()) break;

        cvtColor(frame, gray, COLOR_BGR2GRAY);

        // 腐蚀
        erode(gray, result, kernel);
        imshow("Erosion - 腐蚀", result);

        // 膨胀
        dilate(gray, result, kernel);
        imshow("Dilation - 膨胀", result);

        // 开运算
        morphologyEx(gray, result, MORPH_OPEN, kernel);
        imshow("Opening - 开运算", result);

        // 闭运算
        morphologyEx(gray, result, MORPH_CLOSE, kernel);
        imshow("Closing - 闭运算", result);

        // 形态学梯度
        morphologyEx(gray, result, MORPH_GRADIENT, kernel);
        imshow("Morphological Gradient", result);

        // 顶帽
        morphologyEx(gray, result, MORPH_TOPHAT, kernel);
        imshow("Top Hat", result);

        // 黑帽
        morphologyEx(gray, result, MORPH_BLACKHAT, kernel);
        imshow("Black Hat", result);

        if (waitKey(30) >= 0) break;
    }

    return 0;
}
