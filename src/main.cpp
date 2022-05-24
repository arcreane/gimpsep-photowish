#include <QCoreApplication>
#include <QDebug>
#include <QApplication>
#include "../include/root.h"

using namespace ui;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Root root = Root();
    root.show();
    return QApplication::exec();
}
