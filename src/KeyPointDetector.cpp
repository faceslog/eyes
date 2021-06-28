//
// Created by faces on 28/06/2021.
//
#include "KeyPointDetector.h"

/**
 * We create a new cv::face::FacemarkLBF model.
 * Then we load the model configuration from the KEY_POINT_DETECTION_MODEL variable we passed in via CMake.
 * */
KeyPointDetector::KeyPointDetector()
{
    face_mark = cv::face::FacemarkLBF::create();
    face_mark->loadModel(KEY_POINT_DETECTION_MODEL);
}

/**
 * To adhere to the API of cv::face::Facemark::fit(), we transform our input to a cv::InputArray.
 * Then we call the models fit function and return the detected points.
 * */
std::vector<std::vector<cv::Point2f>> KeyPointDetector::detect_key_points
(
        const std::vector<cv::Rect> &face_rectangles,
        const cv::Mat &image) const
{
    cv::InputArray faces_as_input_array(face_rectangles);
    std::vector<std::vector<cv::Point2f> > key_points;
    face_mark->fit(image, faces_as_input_array,key_points);

    return key_points;
}


