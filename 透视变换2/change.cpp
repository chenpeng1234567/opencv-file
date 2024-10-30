#include <iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
 
Mat srcImg, dstImg;//原图像、目标图像
Mat resultImg;//结果图像
vector<Point2f> srcPoints, dstPoints;//原图像和目标图像的映射点
int pickNums;//目前已选取的节点
 
void mouseHander(int event, int x, int y, int flags, void* p)
{
    if (event == EVENT_LBUTTONDOWN)//左键按下
    {
        Mat tmp = dstImg.clone();
        if (pickNums == 4)//选取的点超过4个后，下一次点击会实现透视变换
        {
            //执行透视变换
            Mat Trans = getPerspectiveTransform(srcPoints, dstPoints);//由4组映射点得到变换矩阵
            warpPerspective(srcImg, tmp, Trans, Size(tmp.cols, tmp.rows));//执行透视变换
            resultImg = dstImg.clone();
            for (int y = 0; y < dstImg.rows; y++)
            {
                for (int x = 0; x < dstImg.cols; x++)
                {
                    if ((int)tmp.at<Vec3b>(y, x)[0] == 0 && (int)tmp.at<Vec3b>(y, x)[1] == 0 && (int)tmp.at<Vec3b>(y, x)[2] == 0)//像素点全0
                        continue;
                    else//非全0
                    {
                        resultImg.at<Vec3b>(y, x)[0] = tmp.at<Vec3b>(y, x)[0];
                        resultImg.at<Vec3b>(y, x)[1] = tmp.at<Vec3b>(y, x)[1];
                        resultImg.at<Vec3b>(y, x)[2] = tmp.at<Vec3b>(y, x)[2];
                    }
                }
            }
            imshow("虚拟广告牌", resultImg);
            dstPoints.clear();
            pickNums = 0;
        }
        else//选取的节点还没4个
        {
            dstPoints.push_back(Point2f(x, y));
            pickNums++;
            for (int i = 0; i < dstPoints.size(); i++)
            {
                circle(tmp, dstPoints[i], 5, Scalar(0, 215, 255), 3);
            }
            imshow("虚拟广告牌", tmp);
        }
    }
 
}
 
int main()
{
    srcImg = imread("1.png");//透视变换的图像，也就是广告图
 
    //设置原图像的4个映射点
    srcPoints.push_back(Point2f(0, 0));
    srcPoints.push_back(Point2f(srcImg.cols, 0));
    srcPoints.push_back(Point2f(srcImg.cols, srcImg.rows));
    srcPoints.push_back(Point2f(0, srcImg.rows));
 
    dstImg = imread("2.jpg");//背景图
 
    imshow("虚拟广告牌", dstImg);
    //鼠标事件
    setMouseCallback("虚拟广告牌", mouseHander);
    waitKey(0);
    return 0;
}