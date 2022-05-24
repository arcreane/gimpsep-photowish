//
// Created by Julien Thomas on 11/05/2022.
//

#ifndef GIMP_IMAGE_H
#define GIMP_IMAGE_H

#include <opencv2/opencv.hpp>

class Image {
private:
    cv::Mat *m_matrix;
    int *m_brightness;
    double *m_contrast;

public:
    Image(cv::Mat *matrix);
    cv::Mat *getMatrix() const;
    void setMatrix(cv::Mat matrix);
    int *getBrightness() const;
    void setBrightness(int brightness);
    double *getContrast() const;
    void setContrast(double contrast);


};


#endif //GIMP_IMAGE_H
