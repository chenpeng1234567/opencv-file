#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    // 打开默认摄像头
    cv::VideoCapture cap(2);
    if (!cap.isOpened()) {
        std::cerr << "无法打开摄像头" << std::endl;
        return -1;
    }

    // 窗口名称
    const std::string windowName = "摄像头实时捕捉";
    const std::string redWindow = "红色区域";
    const std::string blueWindow = "蓝色区域";
    const std::string whiteWindow = "白色区域";

    cv::namedWindow(windowName, cv::WINDOW_AUTOSIZE);
    cv::namedWindow(redWindow, cv::WINDOW_AUTOSIZE);
    cv::namedWindow(blueWindow, cv::WINDOW_AUTOSIZE);
    cv::namedWindow(whiteWindow, cv::WINDOW_AUTOSIZE);

    cv::Mat frame, hsvFrame, redMask, blueMask, whiteMask;

    while (true) {
        // 捕获帧
        cap >> frame;
        if (frame.empty()) {
            std::cerr << "无法捕获帧" << std::endl;
            break;
        }

        // 将 BGR 转换为 HSV 色彩空间
        cv::cvtColor(frame, hsvFrame, cv::COLOR_BGR2HSV);

        // 红色的 HSV 范围
        cv::Mat lowerRedMask, upperRedMask;
        cv::inRange(hsvFrame, cv::Scalar(0, 100, 100), cv::Scalar(10, 255, 255), lowerRedMask);
        cv::inRange(hsvFrame, cv::Scalar(170, 100, 100), cv::Scalar(180, 255, 255), upperRedMask);
        redMask = lowerRedMask | upperRedMask;  // 合并两个红色范围的掩码

        // 蓝色的 HSV 范围
        cv::inRange(hsvFrame, cv::Scalar(100, 150, 50), cv::Scalar(140, 255, 255), blueMask);

        // 白色的 HSV 范围
        cv::inRange(hsvFrame, cv::Scalar(0, 0, 200), cv::Scalar(180, 30, 255), whiteMask);

        // 显示原始图像和提取出的颜色区域
        cv::imshow(windowName, frame);
        cv::imshow(redWindow, redMask);
        cv::imshow(blueWindow, blueMask);
        cv::imshow(whiteWindow, whiteMask);

        //可视化HSV范围
        cv::Mat hsvColor;
        cv::cvtColor(frame, hsvColor, cv::COLOR_BGR2HSV);
        cv::imshow("HSV Frame", hsvColor);

        // 按下 'q' 键退出循环
        if (cv::waitKey(30) == 'q') {
            break;
        }
    }

    // 释放资源
    cap.release();
    cv::destroyAllWindows();
    return 0;
}
