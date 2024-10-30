#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
    system("color F0");   // 更改界面颜色
    VideoCapture video("img/test.mp4");

    // 判断视频是否打开
    if (video.isOpened())
    {
        cout << "视频中图像的宽度=" << video.get(CAP_PROP_FRAME_WIDTH) << endl;
        cout << "视频中图像的高度=" << video.get(CAP_PROP_FRAME_HEIGHT) << endl;
        cout << "视频帧率=" << video.get(CAP_PROP_FPS) << endl;
    }
    else
    {
        cout << "请确认视频文件名称是否正确" << endl;
        return -1;
    }

    // 获取帧率并确保其大于 0
    double fps = video.get(CAP_PROP_FPS);
    if (fps <= 0)
    {
        fps = 30;  // 如果获取失败，默认设置为 30 FPS
    }

    // 循环播放视频
    while (true)
    {
        Mat frame;
        video >> frame;

        // 如果视频结束，退出循环
        if (frame.empty())
        {
            break;
        }

        // 显示当前帧
        imshow("video", frame);

        // 根据帧率等待
        if (waitKey(1000 / fps) == 27)  // 按 ESC 键退出
        {
            break;
        }
    }

    waitKey(0);
    return 0;
}
