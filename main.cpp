#include "mainwindow.h"
#include <QApplication>
#include "dialog.h"
#include "QDebug"




int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.showMaximized();

qDebug() << "";

    return a.exec();
}
