#include "mainwindow.h"
#include <QApplication>
#include "QDebug"
#include "addquotesdialog.h"
#include "settingswindow.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;




    w.showMaximized();

   qDebug() << "";


    return a.exec();
}
