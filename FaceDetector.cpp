#include <sstream>
#include <vector>
#include <string>
#include "FaceDetector.h"
#include <opencv2/opencv.hpp>

FaceDetector::FaceDetector() :
    confidence_threshold_(0.5),
    input_image_height_(300),
    input_image_width_(300),
    scale_factor_(1.0),
    mean_values_({ 104., 177.0, 123.0 }) {
    // Note: The variables MODEL_CONFIGURATION_FILE
    // and MODEL_WEIGHTS_FILE are passed in via cmake
    network_ = cv::dnn::readNetFromCaffe(FACE_DETECTION_CONFIGURATION,
        FACE_DETECTION_WEIGHTS);

    if (network_.empty()) {
        std::ostringstream ss;
        ss << "Failed to load network with the following settings:\n"
            << "Configuration: " + std::string(FACE_DETECTION_CONFIGURATION) + "\n"
            << "Binary: " + std::string(FACE_DETECTION_WEIGHTS) + "\n";
        throw std::invalid_argument(ss.str());
    }