#include "mainwindow.h"
#include <QApplication>
#include "QDebug"
#include "addquotesdialog.h"
#include "settingswindow.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;


    QFile File(":/styles/QTDark.css");
     if (File.open(QFile::ReadOnly))
     {
     QString StyleSheet = QLatin1String(File.readAll());
      w.setStyleSheet(StyleSheet);
     }
     else
     {
         qDebug() << "!";
     }

    w.showMaximized();

   qDebug() << "";


    return a.exec();
}
