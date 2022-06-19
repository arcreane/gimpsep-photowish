//
// Created by Julien Thomas on 18/05/2022.
//

#include <QMdiSubWindow>
#include "../include/DrawingTool.h"

DrawingTool::DrawingTool(QWidget *parent,
                         DisplayLabel *label,
                         Image *imageToBeDrawnOn,
                         QPixmap *pixmap,
                         double *scaleFactor) {

    this->setFocus();
    m_imageToBeDrawnOn = imageToBeDrawnOn;
    m_pixmap = pixmap;
    m_scaleFactor = scaleFactor;

    imageLabel = label;
    //imageLabel->enableMouseSelection();
    //imageLabel->setCursor(Qt::CrossCursor);
    colorPicker = new QColorDialog();
    colorPicker->setWindowFlags(Qt::Widget);
    colorPicker->setOption(QColorDialog::DontUseNativeDialog);

    pencilButton = new QPushButton(this);
    QPixmap pencilPixmap = QPixmap("://resources/images/pencil_button.png");
    pencilButton->setIcon(QIcon(pencilPixmap));
    pencilButton->setMaximumWidth(this->width()*0.15);
    pencilButton->setIconSize(pencilPixmap.scaled(this->width()*0.15,this->height()*0.15,Qt::KeepAspectRatio).rect().size());

    eraserButton = new QPushButton(this);
    QPixmap eraserPixmap = QPixmap("://resources/images/eraser.png");
    eraserButton->setIcon(QIcon(eraserPixmap));
    eraserButton->setMaximumWidth(this->width()*0.15);
    eraserButton->setIconSize(eraserPixmap.scaled(this->width()*0.15,this->height()*0.15,Qt::KeepAspectRatio).rect().size());

    layout = new QHBoxLayout;
    layout->addWidget(colorPicker);
    layout->addWidget(pencilButton);
    layout->addWidget(eraserButton);
    layout->setAlignment(Qt::AlignCenter);
    this->setLayout(layout);
}

void DrawingTool::mousePressEvent(QMouseEvent *event) {
    
}

void DrawingTool::updatePixmap() {
    QImage imageUpdate = QImage((uchar*)m_imageToBeDrawnOn->getMatrix()->data,
                                m_imageToBeDrawnOn->getMatrix()->cols,
                                m_imageToBeDrawnOn->getMatrix()->rows,
                                m_imageToBeDrawnOn->getMatrix()->step,
                                QImage::Format_RGB888
    );
    *m_pixmap = QPixmap::fromImage(imageUpdate);
    imageLabel->setPixmap(m_pixmap->scaled(m_pixmap->width()**m_scaleFactor,m_pixmap->height()**m_scaleFactor));
}
