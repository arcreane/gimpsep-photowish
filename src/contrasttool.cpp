//
// Created by Julien Thomas on 29/04/2022.
//

// You may need to build the project (run Qt uic code generator) to get "ui_ContrastTool.h" resolved

#include <QVBoxLayout>
#include "../include/contrasttool.h"
#include "ui_ContrastTool.h"


ContrastTool::ContrastTool(QWidget *parent,Image *source, Image *imageToContrast, QLabel *destinationLabel,QPixmap *pixmap,double *scaleFactor) :
        QWidget(parent), ui(new Ui::ContrastTool) {

    m_source = source;
    m_imageToContrast = imageToContrast;
    m_destinationLabel = destinationLabel;
    m_pixmap = pixmap;
    m_scaleFactor = scaleFactor;

    QLabel *sliderName = new QLabel(this);
    sliderName->setText("Contrast");
    slider = new QSlider(Qt::Horizontal,this);
    slider->setObjectName("slider");
    slider->setRange(100, 300);
    slider->setValue(*(imageToContrast->getContrast())*100);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(sliderName);
    layout->addWidget(slider);
    layout->setAlignment(Qt::AlignCenter);
    this->setLayout(layout);
    ui->setupUi(this);
}

ContrastTool::~ContrastTool() {
    delete ui;
}

void ContrastTool::on_slider_valueChanged() {
    double contrast = (double)slider->value()/100.0;
    m_imageToContrast->setContrast(contrast);

    m_source->getMatrix()->convertTo(*(m_imageToContrast->getMatrix()),
                                     -1,
                                     contrast,
                                     *(m_imageToContrast->getBrightness())
    );

    QImage imageUpdate = QImage((uchar*)m_imageToContrast->getMatrix()->data,
                                m_imageToContrast->getMatrix()->cols,
                                m_imageToContrast->getMatrix()->rows,
                                m_imageToContrast->getMatrix()->step,
                                QImage::Format_RGB888
    );
    *m_pixmap = QPixmap::fromImage(imageUpdate);
    m_destinationLabel->setPixmap(m_pixmap->scaled(m_pixmap->width()**m_scaleFactor,m_pixmap->height()**m_scaleFactor));
}

