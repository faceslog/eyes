//
// Created by faces on 08/02/2021.
//
#include "FaceDetector.h"

FaceDetector::FaceDetector() :  confidence_threshold(0.5), input_image_height(300), input_image_width(300), scale_factor(1.0), mean_values({104.0, 177.0, 123.0}) {

    // Note that the variables MODEL_CONFIGURATION_FILE and MODEL_WEIGHTS_FILE are passed in via cmake
    network = cv::dnn::readNetFromCaffe(FACE_DETECTION_CONFIGURATION, FACE_DETECTION_WEIGHTS);

    if(network.empty())
    {
        std::ostringstream ss;
        ss << "Failed to load network with the following settings:\n"
        << "Configuration: " + std::string(FACE_DETECTION_CONFIGURATION) + "\n"
        << "Binary: " + std::string(FACE_DETECTION_WEIGHTS) + "\n";
        throw std::invalid_argument(ss.str());
    }

}

std::vector<cv::Rect> FaceDetector::detect_face_rectangle(const cv::Mat &frame) {

    // Transform the input image into a data blob so we take care of rescaling the image
    // to the correct input size for the network. It also subtract the mean value in each color channel
    cv::Mat input_blob = cv::dnn::blobFromImage(frame,
                                                 scale_factor,
                                                cv::Size(input_image_width, input_image_height),
                                                 mean_values,
                                                false,
                                                false);

    // Forward our data and save the result
    network.setInput(input_blob, "data");
    cv::Mat detection = network.forward("detection_out");
    cv::Mat detection_matrix(detection.size[2], detection.size[3], CV_32F, detection.ptr<float>());

    // We iterate through the rows of the matrix. Each rows contains one detection. While iterating we check if
    // the confidence value exceeds our threshold. If so, we construct a cv::Rect and save it in the result vector faces
    std::vector<cv::Rect> faces;

    for(int i{0}; i < detection_matrix.rows; i++)
    {
        float confidence = detection_matrix.at<float>(i, 2);

        if(confidence < confidence_threshold) continue;

        int x_left_bottom = static_cast<int>(detection_matrix.at<float>(i, 3) * static_cast<float>(frame.cols));
        int y_left_bottom = static_cast<int>(detection_matrix.at<float>(i, 4) * static_cast<float>(frame.rows));
        int x_right_top = static_cast<int>(detection_matrix.at<float>(i,5) * static_cast<float>(frame.cols));
        int y_right_top = static_cast<int>(detection_matrix.at<float>(i,6) * static_cast<float>(frame.rows));

        faces.emplace_back(x_left_bottom, y_left_bottom, (x_right_top - x_left_bottom), (y_right_top - y_left_bottom));
    }

    return faces;
}


