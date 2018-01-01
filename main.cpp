#include "mainwindow.h"
#include <QApplication>
#include "QDebug"
#include "addquotesdialog.h"
#include "settingswindow.h"

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg){

    Q_UNUSED(context)

    QFile fMessFile(qApp->applicationDirPath() + "/log.txt");

    if(!fMessFile.open(QIODevice::Append | QIODevice::Text)){
        return;
    }
    QString sCurrDateTime = "[" +
              QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss.zzz") + "]";
    QTextStream tsTextStream(&fMessFile);
    switch(type){
    case QtDebugMsg:
        tsTextStream << QString("%1 Debug - %2").arg(sCurrDateTime).arg(msg);
        break;
    case QtWarningMsg:
        tsTextStream << QString("%1 Warning - %2").arg(sCurrDateTime).arg(msg);
        break;
    case QtCriticalMsg:
        tsTextStream << QString("%1 Critical - %2").arg(sCurrDateTime).arg(msg);
        break;
    case QtFatalMsg:
        tsTextStream << QString("%1 Fatal - %2").arg(sCurrDateTime).arg(msg);
        abort();
    }
    tsTextStream.flush();
    fMessFile.flush();
    fMessFile.close();
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    if (argc > 1 && !strcmp(argv[1], "-log"))
    {
        qDebug() << "log on";
        qInstallMessageHandler(myMessageOutput);
    }


    MainWindow w;
    w.showMaximized();

//    QIcon icon("icons/bookcase.ico");
//    w.setWindowIcon(icon);

    return a.exec();
}


