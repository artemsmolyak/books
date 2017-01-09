#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dialog.h"
#include "data.h"
#include "qstringlistmodel.h"

namespace Ui {
//class MainWindow;
class Window;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QString path = "C:\\Users\\Artyom\\Documents\\books\\books.xml";
    Dialog * dialog;
    QList <Data> dataList;
    QStringList dataStringList;

    QStringListModel *dataModel;

public:
    explicit MainWindow(QWidget *parent = 0);
    void guiSettings();


    bool readXml();

    ~MainWindow();

private:
    Ui:: Window *ui;


signals:
    void hideDialog();


public  slots:
    void saveXml();
    void getNewItem(Data data);
    void updateDataList();
    void testSlot(Data);

};

#endif // MAINWINDOW_H
