#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dialog.h"
#include "data.h"
#include "qstringlistmodel.h"
#include "tablemodel.h"

namespace Ui {
//class MainWindow;
class Window;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QString path = "://books.xml";
    Dialog * dialog;
    QList <Data> dataList;
    QStringList dataStringList;


    TableModel * tableModel;

    //QStringListModel *dataModel;

public:
    explicit MainWindow(QWidget *parent = 0);
    void guiSettings();
    QString convertQPixmapToQString(QPixmap pic);
    QPixmap convertQStringToQPixmap(QString pic);
    void setChooseFirstColumn();

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
    void chooseListIndex(QModelIndex index);

};

#endif // MAINWINDOW_H
