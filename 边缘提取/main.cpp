#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

// 函数：提取特定颜色的轮廓
void findColorContours(Mat& frame, Scalar lower, Scalar upper, const string& colorName) {
    Mat mask, morph, edges;
    
    // 创建颜色掩模
    inRange(frame, lower, upper, mask);

    // 形态学操作：消除噪点
    Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5));
    morphologyEx(mask, morph, MORPH_OPEN, kernel); // 开运算
    morphologyEx(morph, morph, MORPH_CLOSE, kernel); // 闭运算

    // 边缘检测
    Canny(morph, edges, 100, 200);

    // 查找轮廓
    vector<vector<Point>> contours;
    findContours(edges, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    // 绘制轮廓
    for (size_t i = 0; i < contours.size(); i++) {
        if (contourArea(contours[i]) > 100) { // 忽略面积过小的轮廓
            drawContours(frame, contours, (int)i, Scalar(255, 255, 255), 2);
        }
    }

    imshow(colorName + " Contours", frame);
}

int main() {
    // 打开摄像头
    VideoCapture cap(2);
    if (!cap.isOpened()) {
        cout << "无法打开摄像头" << endl;
        return -1;
    }

    Mat frame, hsv;

    while (true) {
        cap >> frame; // 从摄像头捕获图像
        if (frame.empty()) break;

        // 转换为HSV色彩空间
        cvtColor(frame, hsv, COLOR_BGR2HSV);

        // 定义红色、蓝色、白色的HSV范围
        Scalar lower_red(0, 100, 100), upper_red(10, 255, 255);    // 红色
        Scalar lower_blue(100, 150, 0), upper_blue(140, 255, 255); // 蓝色
        Scalar lower_white(0, 0, 200), upper_white(180, 30, 255);  // 白色

        // 提取红色轮廓
        findColorContours(frame, lower_red, upper_red, "Red");

        // 提取蓝色轮廓
        findColorContours(frame, lower_blue, upper_blue, "Blue");

        // 提取白色轮廓
        findColorContours(frame, lower_white, upper_white, "White");

        if (waitKey(30) >= 0) break;
    }

    return 0;
}
