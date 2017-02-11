#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dialog.h"
#include "data.h"
#include "qstringlistmodel.h"
#include "tablemodel.h"
#include "QDir"


class Dialog;

namespace Ui {
class Window;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QString path = QDir::homePath() + "/books.xml";
    Dialog * dialog;
    QList <Data> dataList;
    QStringList dataStringList;


    TableModel * tableModel;
    QModelIndex indexEdit;


public:
    explicit MainWindow(QWidget *parent = 0);
    void guiSettings();
    QString convertQPixmapToQString(QPixmap pic);
    QPixmap convertQStringToQPixmap(QString pic);
    void setChooseFirstColumn();
    bool readXml();
    void editMode();

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
    void editModeStart();
    void addModeStart();
    void editItem(Data data);
    void deleteItem();

    void on_addButton_released();
    void on_deleteButton_released();
    void on_updateButton_released();
};

#endif // MAINWINDOW_H
