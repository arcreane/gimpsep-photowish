//
// Created by Julien Thomas on 28/04/2022.
//

#ifndef GIMP_ROOT_H
#define GIMP_ROOT_H

#include <QWidget>
#include <iostream>
#include <QMenu>
#include <QMenuBar>
#include <QLabel>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QToolBar>
#include <opencv2/opencv.hpp>
#include "Image.h"
#include "DisplayLabel.h"


namespace ui {
    QT_BEGIN_NAMESPACE
    namespace Ui { class Root; }
    QT_END_NAMESPACE

    class Root : public QMainWindow {
        Q_OBJECT

    public:
        explicit Root();
        [[nodiscard]] QSize sizeHint() const override;
        void clearLayout(QLayout *layoutToBeCleared);
        ~Root() override;

    private:
        Ui::Root *ui;

        void createActions();
        void createMenus();

        QMenu *fileMenu;
        QMenu *editMenu;
        QMenu *helpMenu;

        QAction *newAct;
        QAction *openAct;
        QAction *saveAct;
        QAction *saveAsAct;
        QAction *aboutAct;
        QAction *aboutQtAct;
        QAction *undoAct;
        QAction *redoAct;
        QAction *cutAct;
        QAction *copyAct;
        QAction *pasteAct;
        QAction *zoomInAct;
        QAction *zoomOutAct;
        double scaleFactor = 1;

        QWidget *centralWidget;
        QWidget *workspace;
        DisplayLabel *imageDisplayLabel;
        QWidget *toolPanel;
        QToolBar *toolbar;
        QHBoxLayout *layout;

        Image *source;
        Image *treatedImage;
        std::string *imagePath;
        QImage *qImage;
        QPixmap *pixMap;


        int rootWidth = sizeHint().width();
        int rootHeight = sizeHint().height();


//    protected:
//    #ifndef QT_NO_CONTEXTMENU
//        void contextMenuEvent(QContextMenuEvent *event) override;
//    #endif // QT_NO_CONTEXTMENU

    private slots:
        void newFile();
        void open();
        void save();
        void saveAs();
        void about();
        void aboutQt();
        void undo();
        void redo();
        void cut();
        void copy();
        void paste();
        void zoomIn();
        void zoomOut();

        void triggerBrightnessTool();
        void triggerResizeTool();
        void triggerContrastTool();
        void triggerFilterTool();
        void triggerPanoramaTool();
        void triggerCropTool();
        void triggerDrawTool();


    };
} // ui

#endif //GIMP_ROOT_H
