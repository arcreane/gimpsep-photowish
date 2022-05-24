//
// Created by Julien Thomas on 12/05/2022.
//

#ifndef GIMP_RESIZETOOL_H
#define GIMP_RESIZETOOL_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMouseEvent>
#include <QSlider>
#include <opencv2/opencv.hpp>
#include "Image.h"


QT_BEGIN_NAMESPACE
namespace Ui { class ResizeTool; }
QT_END_NAMESPACE

class ResizeTool : public QWidget {
Q_OBJECT

public:
    explicit ResizeTool(QWidget *parent = nullptr,
                        Image *source=nullptr,
                        Image *resizedImage=nullptr,
                        QLabel *destinationLabel=nullptr,
                        QPixmap * pixmap=nullptr,
                        double *scalefactor=nullptr);

    ~ResizeTool() override;
    void updatePixmap();


private:
    Ui::ResizeTool *ui;
    QLineEdit *widthEdit;
    QLineEdit *heightEdit;
    QPushButton *applyWithFieldsButton;
    QPushButton *applyWithSliderButton;
    QSlider *slider;

    Image *m_source;
    Image *m_resizedImage;
    QLabel *m_destinationLabel;
    QPixmap* m_pixmap;
    double *m_scaleFactor;

private slots:
    void on_applyWithFieldsButton_clicked();
    void on_applyWithSliderButton_clicked();
    void onTextChanged();
    void on_slider_valueChanged(int value);
};


#endif //GIMP_RESIZETOOL_H
