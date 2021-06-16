#include <opencv4/opencv2/opencv.hpp>
#include "../include/FaceDetector.h"

int main() {

    const int esc_key = 27;
    const int rect_thickness = 4;
    cv::VideoCapture video_capture;
    FaceDetector face_detector;
    cv::Mat frame;

    if(!video_capture.open(0)) return 0;

    while(true)
    {
        video_capture >> frame;

        auto rectangles = face_detector.detect_face_rectangle(frame);
        cv::Scalar color(0, 105, 205);

        for(const auto &r : rectangles)
        {
            cv::rectangle(frame, r, color, rect_thickness);
        }

        imshow("Image", frame);
        // Press ESC to break the loop
        if(cv::waitKey(10) == esc_key)
        {
            break;
        }

    }

    cv::destroyAllWindows();
    video_capture.release();

    return 0;
}
