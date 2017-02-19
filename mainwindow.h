#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dialog.h"
#include "data.h"
#include "qstringlistmodel.h"
#include "tablemodel.h"
#include "QDir"
#include "QSqlError"
#include "editdialog.h"
#include "addquotesdialog.h"
#include "QPair"
#include "QStringListModel"

class Dialog;

namespace Ui {
class Window;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QString path = QDir::homePath() + "/books.xml";
    Dialog * dialog; //to delete
    QStringListModel* model;

    EditDialog * dialogAddEdit;
    AddQuotesDialog addQuotesDialog;

    QList <Data> dataListMain;
    //QStringList dataStringList;

    int currentBook;
    int tabNow = 0;

    QHash <int, QString> genreHash;
    QList <QPair <int, QString>> quotesList;


    TableModel * tableModel;
    QModelIndex indexEdit;

     //QSqlRelationalTableModel *model;

public:
    explicit MainWindow(QWidget *parent = 0);
    void guiSettings();
    QString convertQPixmapToQString(QPixmap pic);
    QPixmap convertQStringToQPixmap(QString pic);

    void setChooseFirstColumn();
    bool readXml();
    void editMode();    
    void showMainInformation();


   //DataBase
    bool dbConnect();
    void getInfFromDb();
    void fillMainWinFromDataBase(QList <Data> dataList);


    QSqlError createGenresTable();
    QSqlError createBookMainsTable();
    QSqlError createQuotesTable();
    QSqlError createTagsTable();

    QSqlError saveItemInDatabase(Data data);

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
    void on_changeTab_released(int tab);

    void showAddDialog();
};

#endif // MAINWINDOW_H
