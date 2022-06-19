//
// Created by Julien Thomas on 28/04/2022.
//

#include <QLabel>
#include <QVBoxLayout>
#include "../include/brightnesstool.h"
#include "ui_BrightnessTool.h"


BrightnessTool::BrightnessTool(QWidget *parent,Image *source, Image *imageToLighten, QLabel *destinationLabel,QPixmap* pixmap, double *scaleFactor) :
        QWidget(parent), ui(new Ui::BrightnessTool) {

    m_source = source;
    m_imageToLighten = imageToLighten;
    m_destinationLabel = destinationLabel;
    m_pixmap = pixmap;
    m_scaleFactor = scaleFactor;

    QLabel *sliderName = new QLabel(this);
    sliderName->setText("Brightness");
    slider = new QSlider(Qt::Horizontal, this);
    slider->setObjectName("slider");
    slider->setRange(-255, 255);
    slider->setValue(*(imageToLighten->getBrightness()));

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(sliderName);
    layout->addWidget(slider);
    layout->setAlignment(Qt::AlignCenter);
    this->setLayout(layout);

    ui->setupUi(this);
}

BrightnessTool::~BrightnessTool() {
    delete ui;
}

void BrightnessTool::on_slider_valueChanged() {
    int brightness = slider->value();
    m_imageToLighten->setBrightness(brightness);

    m_source->getMatrix()->convertTo(*(m_imageToLighten->getMatrix()),
                                     -1,
                                     *(m_imageToLighten->getContrast()),
                                     brightness
    );

    QImage imageUpdate = QImage((uchar*)m_imageToLighten->getMatrix()->data,
                                m_imageToLighten->getMatrix()->cols,
                                m_imageToLighten->getMatrix()->rows,
                                m_imageToLighten->getMatrix()->step,
                                QImage::Format_RGB888
    );
    *m_pixmap = QPixmap::fromImage(imageUpdate);
    m_destinationLabel->setPixmap(m_pixmap->scaled(m_pixmap->width()**m_scaleFactor,m_pixmap->height()**m_scaleFactor));
}

