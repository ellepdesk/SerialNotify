#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(serialnotifier);
    QApplication a(argc, argv);
    MainWindow w;
    //w.show();
    QApplication::setQuitOnLastWindowClosed(false);
    return a.exec();
}
