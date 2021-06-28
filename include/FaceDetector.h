//
// Created by faces on 08/02/2021.
//

#ifndef OPENCV_EYES_FACEDETECTOR_H
#define OPENCV_EYES_FACEDETECTOR_H

#include <vector>
#include <string>
#include <sstream>

#include "opencv4/opencv2/opencv.hpp"
#include "opencv4/opencv2/dnn.hpp"

class FaceDetector {

public:
    explicit FaceDetector();
    /**
     * Detect faces in an image frame
     * @param frame Image to detect faces in
     * @return Vector of detected faces
     */
     std::vector<cv::Rect> detect_face_rectangle(const cv::Mat &frame);

private:
    // Face detection network
    cv::dnn::Net network;
    // Input image width
    const int input_image_width;
    // Input image height
    const int input_image_height;
    // Scale factor when creating the image blob
    const double scale_factor;
    // Mean normalization values network was trained with
    const cv::Scalar mean_values;
    // Face detection confidence threshold
    const float confidence_threshold;
};

#endif //OPENCV_EYES_FACEDETECTOR_H
