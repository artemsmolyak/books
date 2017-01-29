#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "data.h"
#include "qstringlistmodel.h"
#include "tablemodel.h"

class Dialog;

namespace Ui {
//class MainWindow;
class Window;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void guiSettings();
    QString convertQPixmapToQString(QPixmap pic);
    QPixmap convertQStringToQPixmap(QString pic);

    bool readXml();

public  slots:
    void saveXml();
    void getNewItem(Data data);
    void updateDataList();
    void testSlot(Data);
    void chooseListIndex(QModelIndex index);

private slots:
    void on_addButton_released();
    void on_deleteButton_released();
    void on_updateButton_released();

private:
    Ui:: Window *ui;
    QString path = "://books.xml";
    Dialog * dialog;
    QList <Data> dataList;
    QStringList dataStringList;
    TableModel * tableModel;

    //QStringListModel *dataModel;
};

#endif // MAINWINDOW_H
