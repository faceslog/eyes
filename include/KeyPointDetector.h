//
// Created by faces on 28/06/2021.
//

#ifndef OPENCV_EYES_KEYPOINTDETECTOR_H
#define OPENCV_EYES_KEYPOINTDETECTOR_H

#include "opencv4/opencv2/opencv.hpp"
#include "opencv4/opencv2/face.hpp"

class KeyPointDetector
{
public:
    explicit KeyPointDetector();
    // Detect face key points within a rectangle inside an image
    // @param face_rectangles Rectangles that contain faces
    // @param image Image in which we want to detect key points
    // @return List of face key points for each face rectangle
    std::vector<std::vector<cv::Point2f>> detect_key_points(const std::vector<cv::Rect>& face_rectangles, const cv::Mat &img) const;

private:
    cv::Ptr<cv::face::Facemark> face_mark;
};
#endif //OPENCV_EYES_KEYPOINTDETECTOR_H
