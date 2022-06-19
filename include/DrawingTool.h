//
// Created by Julien Thomas on 18/05/2022.
//

#ifndef GIMP_DRAWINGTOOL_H
#define GIMP_DRAWINGTOOL_H

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QColorDialog>
#include "DisplayLabel.h"
#include "Image.h"

class DrawingTool : public QWidget {
Q_OBJECT
private:
    QHBoxLayout *layout;
    QColorDialog *colorPicker;
    DisplayLabel *imageLabel;
    Image *m_imageToBeDrawnOn;
    QPixmap *m_pixmap;
    QPushButton *pencilButton;
    QPushButton *eraserButton;
    double *m_scaleFactor;
public:
    explicit DrawingTool(QWidget *parent,
    DisplayLabel *label,
    Image *imageToBeDrawnOn,
    QPixmap *pixmap,
    double *scaleFactor);

    void mousePressEvent(QMouseEvent *event) override;
    void updatePixmap();

};


#endif //GIMP_DRAWINGTOOL_H
