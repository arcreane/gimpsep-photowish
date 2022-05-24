//
// Created by Julien Thomas on 15/05/2022.
//

#ifndef GIMP_DISPLAYLABEL_H
#define GIMP_DISPLAYLABEL_H

#include <QLabel>
#include <QRubberBand>
#include <QMouseEvent>

class DisplayLabel : public QLabel{
private :

    QRubberBand *rubberBand;
    QPoint origin;
    QPoint clickPoint;
    Qt::MouseButton lastClickedButton;
    QRect *selectedRect = nullptr;

public:
    explicit DisplayLabel(QWidget *parent);
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void enableMouseSelection();
    void disableMouseSelection();

    QRect *getSelectedRect() const;
    QRubberBand *getRubberBand() const;

};


#endif //GIMP_DISPLAYLABEL_H
