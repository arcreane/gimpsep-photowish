//
// Created by Julien Thomas on 28/04/2022.
//
#include <QFileDialog>
#include <QResource>
#include "../include/brightnesstool.h"
#include "../include/contrasttool.h"
#include "../include/newfiledialog.h"
#include "../include/root.h"
#include "ui_Root.h"
#include "../include/resizetool.h"
#include "../include/CropSelectionTool.h"
#include <opencv2/opencv.hpp>


namespace ui {

    QSize Root::sizeHint() const {
        return {700, 500};
    }

    Root::Root() : ui(new Ui::Root) {
        setMinimumSize(Root::sizeHint()*0.9);

        centralWidget = new QWidget;
        setCentralWidget(centralWidget);

        workspace = new QWidget;
        imageDisplayLabel = new DisplayLabel(workspace);
        imageDisplayLabel->setAlignment(Qt::AlignCenter);
        imageDisplayLabel->setStyleSheet("background-color: #424242;");
        toolPanel = new QWidget(workspace);
        toolPanel->setMaximumHeight(workspace->height()*0.3);
        toolPanel->setStyleSheet("background-color: #363636;");
        QVBoxLayout *toolLayout = new QVBoxLayout;
        toolLayout->setAlignment(Qt::AlignCenter);
        toolPanel->setLayout(toolLayout);


        QVBoxLayout *workspaceLayout = new QVBoxLayout;
        workspaceLayout->addWidget(imageDisplayLabel);
        workspaceLayout->addWidget(toolPanel);
        workspace->setLayout(workspaceLayout);

        toolbar = new QToolBar(this);
        toolbar->setOrientation(Qt::Vertical);

        layout = new QHBoxLayout();
        layout->addWidget(workspace);
        layout->addWidget(toolbar);
        centralWidget->setLayout(layout);

        createActions();
        createMenus();
        
        source = new Image(new cv::Mat);
        treatedImage = new Image(new cv::Mat);
        imagePath = new std::string;
        qImage = new QImage;
        pixMap = new QPixmap;

        ui->setupUi(this);
    }

    Root::~Root() {
        delete ui;
    }

    void Root::createActions() {
        newAct = new QAction(tr("&New"), this);
        newAct->setShortcuts(QKeySequence::New);
        newAct->setStatusTip(tr("Create a new file"));
        connect(newAct, &QAction::triggered, this, &Root::newFile);

        openAct = new QAction(tr("&Open"), this);
        openAct->setShortcuts(QKeySequence::Open);
        openAct->setStatusTip(tr("Open file from disk"));
        connect(openAct, &QAction::triggered, this, &Root::open);

        saveAct = new QAction(tr("&Save"), this);
        saveAct->setShortcuts(QKeySequence::Save);
        saveAct->setStatusTip(tr("Save file"));
        connect(saveAct, &QAction::triggered, this, &Root::save);

        saveAsAct = new QAction(tr("&Save as"), this);
        saveAsAct->setShortcuts(QKeySequence::SaveAs);
        saveAsAct->setStatusTip(tr("Save file as <name.extension>"));
        connect(saveAsAct, &QAction::triggered, this, &Root::saveAs);

        aboutAct = new QAction(tr("&information"), this);
        aboutAct->setStatusTip(tr("more information"));
        connect(aboutAct, &QAction::triggered, this, &Root::about);

        aboutQtAct = new QAction(tr("&Qt Framework"), this);
        aboutQtAct->setStatusTip(tr("more information on Qt library"));
        connect(aboutQtAct, &QAction::triggered, this, &Root::aboutQt);

        undoAct = new QAction(tr("&Undo"), this);
        undoAct->setShortcuts(QKeySequence::Undo);
        undoAct->setStatusTip(tr("Undo action"));
        connect(undoAct, &QAction::triggered, this, &Root::undo);

        redoAct = new QAction(tr("&Redo"), this);
        redoAct->setShortcuts(QKeySequence::Redo);
        redoAct->setStatusTip(tr("Redo action"));
        connect(redoAct, &QAction::triggered, this, &Root::redo);

        copyAct = new QAction(tr("&Copy"), this);
        copyAct->setShortcuts(QKeySequence::Copy);
        copyAct->setStatusTip(tr("Copy"));
        connect(copyAct, &QAction::triggered, this, &Root::copy);

        pasteAct = new QAction(tr("&Paste"), this);
        pasteAct->setShortcuts(QKeySequence::Paste);
        pasteAct->setStatusTip(tr("Paste"));
        connect(pasteAct, &QAction::triggered, this, &Root::paste);

        cutAct = new QAction(tr("&Cut"), this);
        cutAct->setShortcuts(QKeySequence::Cut);
        cutAct->setStatusTip(tr("Cut"));
        connect(cutAct, &QAction::triggered, this, &Root::cut);

        zoomInAct = new QAction(tr("&Zoom in"), this);
        zoomInAct->setShortcuts(QKeySequence::ZoomIn);
        zoomInAct->setStatusTip(tr("Zoom In"));
        connect(zoomInAct, &QAction::triggered, this, &Root::zoomIn);

        zoomOutAct = new QAction(tr("&Zoom out"), this);
        zoomOutAct->setShortcuts(QKeySequence::ZoomOut);
        zoomOutAct->setStatusTip(tr("Zoom Out"));
        connect(zoomOutAct, &QAction::triggered, this, &Root::zoomOut);


        QAction *brightnessAct = toolbar->addAction(QIcon("://resources/icons/brightness.png"),"");
        connect(brightnessAct, &QAction::triggered, this, &Root::triggerBrightnessTool);

        QAction *resizeAct = toolbar->addAction(QIcon("://resources/icons/resize.png"),"");
        connect(resizeAct, &QAction::triggered, this, &Root::triggerResizeTool);

        QAction *cropAct = toolbar->addAction(QIcon("://resources/icons/scissors.png"),"");
        connect(cropAct, &QAction::triggered, this, &Root::triggerCropTool);

        QAction *contrastAct = toolbar->addAction(QIcon("://resources/icons/contrast.png"),"");
        connect(contrastAct, &QAction::triggered, this, &Root::triggerContrastTool);

        QAction *filterAct = toolbar->addAction(QIcon("://resources/icons/filter.png"),"");
        connect(filterAct, &QAction::triggered, this, &Root::triggerFilterTool);

        QAction *panoramaAct = toolbar->addAction(QIcon("://resources/icons/panorama.png"),"");
        connect(panoramaAct, &QAction::triggered, this, &Root::triggerPanoramaTool);


    }

    void Root::createMenus() {
        fileMenu = menuBar()->addMenu(tr("&File"));
        fileMenu->addAction(newAct);
        fileMenu->addAction(openAct);
        fileMenu->addSeparator();
        fileMenu->addAction(saveAct);
        fileMenu->addAction(saveAsAct);
        fileMenu->addSeparator();

        editMenu = menuBar()->addMenu(tr("&Edit"));
        editMenu->addAction(undoAct);
        editMenu->addAction(redoAct);
        editMenu->addSeparator();
        editMenu->addAction(cutAct);
        editMenu->addAction(copyAct);
        editMenu->addAction(pasteAct);
        editMenu->addSeparator();
        editMenu->addAction(zoomInAct);
        editMenu->addAction(zoomOutAct);

        helpMenu = menuBar()->addMenu(tr("&Help"));
        helpMenu->addAction(aboutAct);
        helpMenu->addAction(aboutQtAct);

    }

    void Root::newFile() {
        NewFileDialog *dialog = new NewFileDialog(this,
                                                  source,
                                                  treatedImage,
                                                  imageDisplayLabel,
                                                  pixMap,
                                                  &scaleFactor
        );
        dialog->exec();
    }

    void Root::open() {
        QString imageName = QFileDialog::getOpenFileName(
                this,
                tr("Open Image"),
                "/home",
                tr("Image Files (*.png *.jpg *.bmp *.jpeg)")
        );
        *imagePath = imageName.toStdString();
        source->setMatrix(cv::imread(*imagePath));
        treatedImage->setMatrix(cv::imread(*imagePath));

        //to avoid red and blue channel to swap during conversion to QImage
        cvtColor(*(source->getMatrix()), *(source->getMatrix()), cv::COLOR_BGR2RGB);
        cvtColor(*(treatedImage->getMatrix()), *(treatedImage->getMatrix()), cv::COLOR_BGR2RGB);
        *qImage = QImage((uchar *) source->getMatrix()->data,
                         source->getMatrix()->cols,
                         source->getMatrix()->rows,
                         source->getMatrix()->step,
                         QImage::Format_RGB888
        );
        *pixMap = QPixmap::fromImage(*qImage);

        imageDisplayLabel->setPixmap(*pixMap);
    }

    void Root::save() {

    }

    void Root::saveAs() {

    }

    void Root::about() {

    }

    void Root::undo() {

    }

    void Root::redo() {

    }

    void Root::cut() {

    }

    void Root::copy() {

    }

    void Root::paste() {

    }

    void Root::aboutQt() {

    }

    void Root::zoomIn(){
        scaleFactor *= 1.25;
        imageDisplayLabel->setPixmap(pixMap->scaled(pixMap->width()*scaleFactor,pixMap->height()*scaleFactor));
    }

    void Root::zoomOut(){
        scaleFactor *= 0.8;
        imageDisplayLabel->setPixmap(pixMap->scaled(pixMap->width()*scaleFactor,pixMap->height()*scaleFactor));
    }

    void Root::triggerBrightnessTool() {
        BrightnessTool *brightnessTool = new BrightnessTool(
                toolPanel,
                source,
                treatedImage,
                imageDisplayLabel,
                pixMap,
                &scaleFactor
        );
        clearLayout(toolPanel->layout());
        toolPanel->layout()->addWidget(brightnessTool);

    }

    void Root::triggerResizeTool() {
        ResizeTool *resizeTool = new ResizeTool(toolPanel,
                                                source,
                                                treatedImage,
                                                imageDisplayLabel,
                                                pixMap,
                                                &scaleFactor
        );
        clearLayout(toolPanel->layout());
        toolPanel->layout()->addWidget(resizeTool);
    }

    void Root::triggerContrastTool() {
        ContrastTool *contrastTool = new ContrastTool(
                toolPanel,
                source,
                treatedImage,
                imageDisplayLabel,
                pixMap,
                &scaleFactor
        );
        clearLayout(toolPanel->layout());
        toolPanel->layout()->addWidget(contrastTool);
    }

    void Root::triggerFilterTool() {

    }

    void Root::triggerPanoramaTool() {

    }

    void Root::triggerCropTool() {
        CropSelectionTool *cropSelectionTool = new CropSelectionTool(this,
                                                                     imageDisplayLabel,
                                                                     source,
                                                                     treatedImage,
                                                                     pixMap,
                                                                     &scaleFactor
        );
        clearLayout(toolPanel->layout());
        toolPanel->layout()->addWidget(cropSelectionTool);
    }

    void Root::clearLayout(QLayout *layoutToBeCleared) {
        if (layoutToBeCleared == nullptr)
            return;
        QLayoutItem *item;
        while((item = layoutToBeCleared->takeAt(0))) {
            if (item->layout()) {
                clearLayout(item->layout());
                delete item->layout();
            }
            if (item->widget()) {
                delete item->widget();
            }
            delete item;
        }
    }


//    #ifndef QT_NO_CONTEXTMENU
//    void Root::contextMenuEvent(QContextMenuEvent *event) {
//        QMenu menu(this);
//        menu.addAction(cutAct);
//        menu.addAction(copyAct);
//        menu.addAction(pasteAct);
//        menu.exec(event->globalPos());
//    }
//    #endif // QT_NO_CONTEXTMENU
} // ui
