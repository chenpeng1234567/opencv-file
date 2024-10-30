#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int func_save()
{
	Mat img;
    // 选择摄像头
	VideoCapture video(2);

    // 判断是否打开
	if (!video.isOpened())
	{
		cout << "摄像头打开失败" << endl;
		return -1;
	}
    
    // 写入 mat 类
	video >> img;
    
    // 判断是否为空
	if (img.empty())
	{
		cout << "没有获取到图像" << endl;
		return -1;
	}

    // 判断视频颜色
	bool isColor = (img.type() == CV_8UC3);

    // 设置写入格式
	VideoWriter writer;
	int codec = VideoWriter::fourcc('M', 'J', 'P', 'G');

    // 设置写入帧数
	double fps = 25.0;
	
    // 设置输出路径 文件名
	string filename = "img/live.avi";
    
	writer.open(filename, codec, fps, img.size(), isColor);
	
	if (!writer.isOpened())
	{
		cout << "打开失败" << endl;
	}
	while (true)
	{
        // 判断是否继续在传数据
		if (!video.read(img))
		{
			cout << "摄像头读取完成" << endl;
			break;
		}

        // 写入 img 
		writer.write(img);

        // 显示
		imshow("Live", img);
        
        // exc 退出
		char c = waitKey(50);
		if (c == 27)
		{
			break; 
		}
	}
    
    // 释放资源
	writer.release();
	video.release();
	return 1;
}

int main()
{
    func_save();
    return 0;
}
