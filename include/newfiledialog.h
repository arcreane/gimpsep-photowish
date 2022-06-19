//
// Created by Julien Thomas on 04/05/2022.
//

#ifndef GIMP_NEWFILEDIALOG_H
#define GIMP_NEWFILEDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <opencv2/opencv.hpp>
#include "Image.h"


QT_BEGIN_NAMESPACE
namespace Ui { class NewFileDialog; }
QT_END_NAMESPACE

class NewFileDialog : public QDialog {
Q_OBJECT

public:
    explicit NewFileDialog(QWidget *parent = nullptr,
                           Image *source=nullptr,
                           Image *secondImage=nullptr,
                           QLabel *destinationLabel=nullptr,
                           QPixmap *pixmap=nullptr,
                           double *scaleFactor=nullptr);
    ~NewFileDialog() override;


private:
    Ui::NewFileDialog *ui;
    Image *m_source;
    Image *m_secondImage;
    QLabel *m_destinationLabel;
    QPixmap *m_pixmap;
    double *m_scaleFactor;
    int selectedWidth = 1080;
    int selectedHeight = 960;
    QColor *selectedColor;
    QLineEdit *widthEdit;
    QLineEdit *heightEdit;


public slots:
    void on_selectColorButton_clicked();
    void on_createButton_clicked();
};


#endif //GIMP_NEWFILEDIALOG_H
