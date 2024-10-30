#ifndef IMG_TOOLS_HPP
#define IMG_TOOLS_HPP

#include <opencv2/opencv.hpp>
#include <vector>

namespace tools {

    // 函数用于绘制给定点的轮廓
    inline void draw_points(cv::Mat& image, const std::vector<cv::Point>& points, const cv::Scalar& color = {0, 255, 0}) {
        for (const auto& point : points) {
            cv::circle(image, point, 2, color, cv::FILLED);
        }
    }

    // 重载函数，用于绘制 RotatedRect 的 4 个角点
    inline void draw_points(cv::Mat& image, const std::vector<cv::Point2f>& points, const cv::Scalar& color = {0, 0, 255}) {
        for (size_t i = 0; i < points.size(); ++i) {
            cv::line(image, points[i], points[(i + 1) % points.size()], color, 2);
        }
    }
    
}

#endif // IMG_TOOLS_HPP
