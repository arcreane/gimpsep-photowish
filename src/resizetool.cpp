//
// Created by Julien Thomas on 12/05/2022.
//

// You may need to build the project (run Qt uic code generator) to get "ui_ResizeTool.h" resolved

#include <QHBoxLayout>
#include <iostream>
#include <QIntValidator>
#include "../include/resizetool.h"
#include "ui_ResizeTool.h"


ResizeTool::ResizeTool(QWidget *parent,Image *source,
                       Image *resizedImage,
                       QLabel *destinationLabel,
                       QPixmap * pixmap,
                       double *scalefactor) : QWidget(parent), ui(new Ui::ResizeTool) {

    m_source = source;
    m_resizedImage = resizedImage;
    m_destinationLabel = destinationLabel;
    m_pixmap = pixmap;
    m_scaleFactor = scalefactor;

    QLabel *widthLabel = new QLabel("Width",this);
    widthEdit = new QLineEdit(this);
    widthEdit->setValidator(new QIntValidator(0, 10000));
    QLabel *heightLabel = new QLabel("Height",this);
    heightEdit = new QLineEdit(this);
    heightEdit->setValidator(new QIntValidator(0, 10000));
    connect(widthEdit,SIGNAL(textChanged(QString)),this,SLOT(onTextChanged()));
    connect(heightEdit,SIGNAL(textChanged(QString)),this,SLOT(onTextChanged()));

    QVBoxLayout *layout = new QVBoxLayout;
    QWidget *dimension = new QWidget(this);
    QWidget *sliderResize = new QWidget(this);
    QHBoxLayout *dimensionsLayout = new QHBoxLayout(this);
    QHBoxLayout *sliderResizeLayout = new QHBoxLayout(this);

    applyWithFieldsButton = new QPushButton("Apply", this);
    applyWithFieldsButton->setEnabled(false);
    applyWithFieldsButton->setObjectName("applyWithFieldsButton");

    applyWithSliderButton = new QPushButton("Apply", this);
    applyWithSliderButton->setEnabled(false);
    applyWithSliderButton->setObjectName("applyWithSliderButton");

    slider = new QSlider(Qt::Horizontal, this);
    slider->setObjectName("slider");
    slider->setRange(0, 1000);
    slider->setValue(100);

    dimensionsLayout->addWidget(widthLabel);
    dimensionsLayout->addWidget(widthEdit);
    dimensionsLayout->addWidget(heightLabel);
    dimensionsLayout->addWidget(heightEdit);
    dimensionsLayout->addWidget(applyWithFieldsButton);
    dimension->setLayout(dimensionsLayout);

    sliderResizeLayout->addWidget(slider);
    sliderResizeLayout->addWidget(applyWithSliderButton);
    sliderResize->setLayout(sliderResizeLayout);

    layout->addWidget(dimension);
    layout->addWidget(sliderResize);
    this->setLayout(layout);

    ui->setupUi(this);
}

ResizeTool::~ResizeTool() {
    delete ui;
}

void ResizeTool::on_applyWithFieldsButton_clicked() {

    int selectedWidth = widthEdit->text().toInt();
    int selectedHeight = heightEdit->text().toInt();

    cv::resize(*(m_source->getMatrix()),
               *(m_resizedImage->getMatrix()),
               cv::Size(selectedWidth,selectedHeight),
               0,
               0,
               cv::INTER_LINEAR
    );

    updatePixmap();

    widthEdit->clear();
    heightEdit->clear();
    applyWithFieldsButton->setEnabled(false);

}

void ResizeTool::onTextChanged() {
    if(!widthEdit->text().isEmpty() && !heightEdit->text().isEmpty()){
        applyWithFieldsButton->setEnabled(true);
    }
}

void ResizeTool::on_slider_valueChanged(int value) {

    applyWithSliderButton->setEnabled(true);
    widthEdit->clear();
    heightEdit->clear();

    *m_scaleFactor = (double) value/100.0;
    updatePixmap();
}

void ResizeTool::on_applyWithSliderButton_clicked() {

    double resizeFactor = (double) slider->value()/100.0;
    cv::resize(*(m_source->getMatrix()),
               *(m_resizedImage->getMatrix()),
               cv::Size(round(resizeFactor * m_resizedImage->getMatrix()->cols), round(resizeFactor * m_resizedImage->getMatrix()->rows)),
               0,
               0,
               cv::INTER_LINEAR
    );

    //updatePixmap();
    applyWithSliderButton->setEnabled(false);

}

void ResizeTool::updatePixmap(){
    QImage imageUpdate = QImage((uchar*)m_resizedImage->getMatrix()->data,
                                m_resizedImage->getMatrix()->cols,
                                m_resizedImage->getMatrix()->rows,
                                m_resizedImage->getMatrix()->step,
                                QImage::Format_RGB888
    );
    *m_pixmap = QPixmap::fromImage(imageUpdate);
    m_destinationLabel->setPixmap(m_pixmap->scaled(m_pixmap->width()**m_scaleFactor,m_pixmap->height()**m_scaleFactor));
}

