#include "FaceDetector.h"
#include "KeyPointDetector.h"
#include "Config.h"

int main() {

    cv::VideoCapture video_capture;
    cv::Scalar color(RGB_COLOR);
    cv::Mat frame;

    FaceDetector face_detector;
    KeyPointDetector keypoint_detector;
    bool is_running = true;
    bool is_keypoint_toggle = false;

    if(!video_capture.open(0)) return 0;

    while(is_running)
    {
        video_capture >> frame;

        // Get faces in rect
        auto rectangles = face_detector.detect_face_rectangle(frame);
        if(not is_keypoint_toggle)
        {
            // Draw only Rectangles
            for(const auto &r : rectangles)
            {
                cv::rectangle(frame, r, color, RECT_THICKNESS);
            }
        }
        else
        {
            // Draw Key points faces
            auto keypoint_faces = keypoint_detector.detect_key_points(rectangles, frame);
            // For each faces we draw their key points
            for (const auto &face :keypoint_faces)
            {
                for (const cv::Point2f &keypoint : face) {
                    cv::circle(frame, keypoint, KEYPOINT_RADIUS, color, KEYPOINT_THICKNESS);
                }
            }
        }

        imshow("Frame - Press ESC to Quit", frame);
        // Press ESC to break the loop
        switch (cv::waitKey(10))
        {
            case ESC_KEY:
                is_running = false;
                break;
            case F1_KEY:
                is_keypoint_toggle = !is_keypoint_toggle;
                break;
            default:
                break;
        }
    }

    cv::destroyAllWindows();
    video_capture.release();

    return 0;
}
