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

    Mat frame, gray, edges;
    
    // 循环处理每一帧
    while (true) {
        cap >> frame; // 从摄像头捕获图像
        if (frame.empty()) break;

        // 转换为灰度图像
        cvtColor(frame, gray, COLOR_BGR2GRAY);

        // 使用Canny进行边缘检测
        Canny(gray, edges, 100, 200);

        // 查找轮廓
        vector<vector<Point>> contours;
        findContours(edges, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

        // 选择面积最大的轮廓，假设为A4纸
        double maxArea = 0;
        vector<Point> largestContour;
        for (const auto& contour : contours) {
            double area = contourArea(contour);
            if (area > maxArea) {
                maxArea = area;
                largestContour = contour;
            }
        }

        // 只有在找到足够大的轮廓时才进行透视变换
        if (largestContour.size() >= 4) {
            // 对轮廓点进行多边形逼近，得到四边形（A4纸）
            vector<Point> approx;
            approxPolyDP(largestContour, approx, arcLength(largestContour, true) * 0.02, true);

            if (approx.size() == 4) {
                // 将点排序为：左上、右上、右下、左下
                sort(approx.begin(), approx.end(), [](const Point& a, const Point& b) { return a.y < b.y; });
                if (approx[0].x > approx[1].x) swap(approx[0], approx[1]);
                if (approx[2].x < approx[3].x) swap(approx[2], approx[3]);

                // 定义A4纸的真实尺寸
                Point2f srcPoints[] = { approx[0], approx[1], approx[2], approx[3] };
                Point2f dstPoints[] = { Point2f(0, 0), Point2f(210, 0), Point2f(210, 297), Point2f(0, 297) };

                // 获取透视变换矩阵
                Mat transformMatrix = getPerspectiveTransform(srcPoints, dstPoints);

                // 对图像进行透视变换
                Mat transformed;
                warpPerspective(frame, transformed, transformMatrix, Size(210, 297)); // A4尺寸为210x297mm

                // 显示透视变换后的图像
                imshow("Transformed Perspective", transformed);
            }
        }

        imshow("Original Frame", frame); // 显示原始图像

        if (waitKey(30) >= 0) break;
    }

    return 0;
}
