#include "mainwindow.h"
#include <QApplication>
#include "QDebug"
#include "addquotesdialog.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.showMaximized();

qDebug() << "";

    return a.exec();
}
