//
// Created by Julien Thomas on 29/04/2022.
//

#ifndef GIMP_CONTRASTTOOL_H
#define GIMP_CONTRASTTOOL_H

#include <QWidget>
#include <QLabel>
#include <QSlider>
#include <opencv2/opencv.hpp>
#include "Image.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ContrastTool; }
QT_END_NAMESPACE

class ContrastTool : public QWidget {
Q_OBJECT

public:
    explicit ContrastTool(QWidget *parent,Image *source, Image *imageToContrast, QLabel *destinationLabel, QPixmap *pixmap,double *scaleFactor);
    ~ContrastTool() override;

private:
    Ui::ContrastTool *ui;
    Image *m_source;
    Image *m_imageToContrast;
    QLabel *m_destinationLabel;
    QPixmap *m_pixmap;
    QSlider *slider;
    double *m_scaleFactor;

private slots:
    void on_slider_valueChanged();
};


#endif //GIMP_CONTRASTTOOL_H
