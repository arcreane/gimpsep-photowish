//
// Created by Julien Thomas on 15/05/2022.
//

#include "../include/DisplayLabel.h"

DisplayLabel::DisplayLabel(QWidget * parent) : QLabel(parent){
    rubberBand = new QRubberBand(QRubberBand::Rectangle, this);
    disableMouseSelection();
}

void DisplayLabel::mousePressEvent(QMouseEvent *event){
    lastClickedButton = event->button();
    if (lastClickedButton == Qt::LeftButton)
    {
        origin = event->pos();
        rubberBand->setGeometry(QRect(origin, clickPoint));
        rubberBand->show();
    }
}

void DisplayLabel::mouseMoveEvent(QMouseEvent *event){
    if(rubberBand != nullptr)
    {
        if (this->underMouse())
        {
            if (lastClickedButton == Qt::LeftButton)
            {
                QPoint mouseCurrentPoint = event->pos();
                rubberBand->setGeometry(QRect(origin, mouseCurrentPoint).normalized());
            }
        }
    }
}

void DisplayLabel::mouseReleaseEvent(QMouseEvent *event){
    QPoint tempOrigin = QPoint();
    lastClickedButton = Qt::MiddleButton;
//    if(rubberBand != nullptr)
//    {
////        rubberBand->hide();
////        rubberBand->clearMask();
//    }

    //selectedRect = new QRect(tempOrigin,event->pos()-origin);
    selectedRect = new QRect(origin,event->pos());
}

void DisplayLabel::enableMouseSelection() {
    this->setAttribute(Qt::WA_TransparentForMouseEvents,false);
}

void DisplayLabel::disableMouseSelection() {
    this->setAttribute(Qt::WA_TransparentForMouseEvents);
}

QRect *DisplayLabel::getSelectedRect() const {
    return selectedRect;
}

QRubberBand *DisplayLabel::getRubberBand() const {
    return rubberBand;
}
