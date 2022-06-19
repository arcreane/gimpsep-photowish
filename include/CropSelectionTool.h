//
// Created by Julien Thomas on 15/05/2022.
//

#ifndef GIMP_CROPSELECTIONTOOL_H
#define GIMP_CROPSELECTIONTOOL_H

#include <QWidget>
#include <Qlabel>
#include <QVBoxLayout>
#include "../include/DisplayLabel.h"
#include "../include/Image.h"

class CropSelectionTool : public QWidget {
Q_OBJECT
private:
    QLabel *messageLabel;
    QVBoxLayout *layout;
    DisplayLabel *imageLabel;
    Image *m_source;
    Image *m_imageToCrop;
    QPixmap *m_pixmap;
    double *m_scaleFactor;
public:
    explicit CropSelectionTool(QWidget *parent,
                               DisplayLabel *label,
                               Image *source,
                               Image *imageToCrop,
                               QPixmap *pixmap,
                               double *scaleFactor);
    void keyPressEvent(QKeyEvent *event) override;
    void cropImage();
    void updatePixmap();
};


#endif //GIMP_CROPSELECTIONTOOL_H
