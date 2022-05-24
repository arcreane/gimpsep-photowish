//
// Created by Julien Thomas on 28/04/2022.
//

#ifndef GIMP_BRIGHTNESSTOOL_H
#define GIMP_BRIGHTNESSTOOL_H

#include <QWidget>
#include <QSlider>
#include <QLabel>
#include <opencv2/opencv.hpp>
#include "Image.h"


QT_BEGIN_NAMESPACE
namespace Ui { class BrightnessTool; }
QT_END_NAMESPACE

class BrightnessTool : public QWidget {
Q_OBJECT

public:
    explicit BrightnessTool(QWidget *parent, Image *source, Image *imageToLighten, QLabel *destinationLabel,QPixmap* pixmap,double *scaleFactor);
    ~BrightnessTool() override;

private:
    Ui::BrightnessTool *ui;
    Image *m_source;
    Image *m_imageToLighten;
    QLabel *m_destinationLabel;
    QPixmap* m_pixmap;
    QSlider *slider;
    double *m_scaleFactor;

private slots:
    void on_slider_valueChanged();
};


#endif //GIMP_BRIGHTNESSTOOL_H
