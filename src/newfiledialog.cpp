//
// Created by Julien Thomas on 04/05/2022.
//

// You may need to build the project (run Qt uic code generator) to get "ui_NewFileDialog.h" resolved

#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QColorDialog>
#include <QPushButton>
#include "../include/newfiledialog.h"
#include "ui_NewFileDialog.h"

#include <iostream>


NewFileDialog::NewFileDialog(QWidget *parent,
                             Image *source,
                             Image *secondImage,
                             QLabel *destinationLabel,
                             QPixmap *pixmap,
                             double *scaleFactor) : QDialog(parent), ui(new Ui::NewFileDialog) {

    m_source = source;
    m_secondImage = secondImage;
    m_destinationLabel = destinationLabel;
    m_pixmap = pixmap;
    selectedColor = new QColor(255,255,255);
    m_scaleFactor = scaleFactor;

    QWidget *dimensionsContainer = new QWidget(this);
    QLabel *widthLabel = new QLabel("Width",dimensionsContainer);
    widthEdit = new QLineEdit(dimensionsContainer);
    QLabel *heightLabel = new QLabel("Height",dimensionsContainer);
    heightEdit = new QLineEdit(dimensionsContainer);
    QHBoxLayout *dimensionsLayout = new QHBoxLayout(dimensionsContainer);

    dimensionsLayout->addWidget(widthLabel);
    dimensionsLayout->addWidget(widthEdit);
    dimensionsLayout->addWidget(heightLabel);
    dimensionsLayout->addWidget(heightEdit);
    dimensionsContainer->setLayout(dimensionsLayout);

    QVBoxLayout *dialogLayout = new QVBoxLayout(this);
    dialogLayout->addWidget(dimensionsContainer);
    QPushButton *selectColorButton = new QPushButton("Select Color",this);
    selectColorButton->setObjectName("selectColorButton");
    dialogLayout->addWidget(selectColorButton);
    QPushButton *createButton = new QPushButton("Create",this);
    createButton->setObjectName("createButton");
    dialogLayout->addWidget(createButton);

    this->setLayout(dialogLayout);

    ui->setupUi(this);
}

NewFileDialog::~NewFileDialog() {
    delete ui;
}

void NewFileDialog::on_selectColorButton_clicked() {
    *selectedColor = QColorDialog::getColor(Qt::white,parentWidget());
}

void NewFileDialog::on_createButton_clicked() {
    selectedWidth = widthEdit->text().toInt();
    selectedHeight = heightEdit->text().toInt();

    *(m_source->getMatrix())= cv::Mat(selectedHeight,
                selectedWidth,
                CV_8UC3,
                cv::Scalar(selectedColor->red(), selectedColor->green(), selectedColor->blue())
    );

    QImage image = QImage((uchar*)m_source->getMatrix()->data,
                          m_source->getMatrix()->cols,
                          m_source->getMatrix()->rows,
                          m_source->getMatrix()->step,
                          QImage::Format_RGB888
    );
    *m_pixmap = QPixmap::fromImage(image);
    m_destinationLabel->setPixmap(*m_pixmap);
    this->close();
}



