//
// Created by Julien Thomas on 15/05/2022.
//

#include <QPainter>
#include <QMessageBox>
#include "../include/CropSelectionTool.h"

CropSelectionTool::CropSelectionTool(QWidget *parent,
                                     DisplayLabel *label,
                                     Image *source,
                                     Image *imageToCrop,
                                     QPixmap *pixmap,
                                     double *scaleFactor) : QWidget(parent) {

    this->setFocus();
    m_source = source;
    m_imageToCrop = imageToCrop;
    m_pixmap = pixmap;
    m_scaleFactor = scaleFactor;

    imageLabel = label;
    imageLabel->enableMouseSelection();
    imageLabel->setCursor(Qt::CrossCursor);
    messageLabel = new QLabel("Select the area you want to crop",this);
    layout = new QVBoxLayout;
    layout->addWidget(messageLabel);
    this->setLayout(layout);
}

void CropSelectionTool::keyPressEvent(QKeyEvent *event) {
    if( ((event->key() == Qt::Key_Enter) || (event->key() == Qt::Key_Return)) && imageLabel->getRubberBand() != nullptr){
        cropImage();
    }
}

void CropSelectionTool::cropImage() {
    QRect *rubberBandRect = imageLabel->getSelectedRect();
    QRect *pixmapRect = new QRect((imageLabel->width()-m_pixmap->width())/2,
                                 (imageLabel->height()-m_pixmap->height())/2,
                                 m_pixmap->width(),
                                 m_pixmap->height());

    imageLabel->getRubberBand()->hide();

    if(rubberBandRect->intersects(*pixmapRect)){
        //TODO : adapt with scaleFactor so the crop is correct when the image is zoomed in/out
        QRect intersection = *rubberBandRect & *pixmapRect;
        //using image coordinates to crop, not label coordinates
        intersection.adjust(-pixmapRect->x(),-pixmapRect->y(),-pixmapRect->x(),-pixmapRect->y());
        cv::Rect croppingRect = cv::Rect(intersection.x(),
                                         intersection.y(),
                                         intersection.width(),
                                         intersection.height()
        );
        *(m_imageToCrop->getMatrix()) = cv::Mat(*(m_imageToCrop->getMatrix()),croppingRect);
        updatePixmap();
        //TODO : Apply button should be considered to modify source image as brightness/contrast are based upon source
        //apply button + dialog to confirm saying no going backwards (for now tho)
    }
    else{
        QMessageBox msgBox;
        msgBox.setText("Please select at least one pixel...");
        msgBox.exec();
    }
}

void CropSelectionTool::updatePixmap(){
    QImage imageUpdate = QImage((uchar*)m_imageToCrop->getMatrix()->data,
                                m_imageToCrop->getMatrix()->cols,
                                m_imageToCrop->getMatrix()->rows,
                                m_imageToCrop->getMatrix()->step,
                                QImage::Format_RGB888
    );
    *m_pixmap = QPixmap::fromImage(imageUpdate);
    imageLabel->setPixmap(m_pixmap->scaled(m_pixmap->width()**m_scaleFactor,m_pixmap->height()**m_scaleFactor));
}
