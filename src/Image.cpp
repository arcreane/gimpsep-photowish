//
// Created by Julien Thomas on 11/05/2022.
//

#include "../include/Image.h"


Image::Image(cv::Mat *matrix) : m_matrix(matrix) {
    m_brightness = new int;
    *m_brightness = 0;

    m_contrast = new double;
    *m_contrast = 1.0;
}

cv::Mat *Image::getMatrix() const {
    return m_matrix;
}

void Image::setMatrix(cv::Mat matrix) {
    *m_matrix = matrix;
}

int *Image::getBrightness() const {
    return m_brightness;
}

void Image::setBrightness(int brightness) {
    *m_brightness = brightness;
}

double *Image::getContrast() const {
    return m_contrast;
}

void Image::setContrast(double contrast) {
    *m_contrast = contrast;
}
