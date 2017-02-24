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
#include "quote.h"

class Dialog;

namespace Ui {
class Window;
}

enum TabWindow
{
    reviewTab,
    quotesTab
};


class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    // recomended size of book's pic
    int widthPic = 200;
    int heightPic = 300;

    QString pathXml = QDir::homePath() + "/books.xml";
    QString pathDataBase = QDir::homePath() + "/books.sqlite";

    Dialog * dialog; //to delete
    QStringListModel* modelTitle;
    QStringListModel* modelQuotes;

    EditDialog * dialogAddEdit;
    AddQuotesDialog * addQuotesDialog;

    QList <Data> dataListMain;
    //QStringList dataStringList;

    //int currentBook;
    Mode currentMode;
    TabWindow currentTab;

    QHash <int, QString> genreHash;
    QList <Quote> quotesList;


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
    QSqlError getQuotes();   
    void updateDataListMain();
    int getCurrentQuoteCountFrom1();
    int getCurrentBookCountFrom1();
    int getIDFromBookNumber(int bookNumber);
    int getIDFromQuoteNumber(int quoteNumber);


    //Quote
    QList <Quote> getListQuoteForBook(int idBook);
    QStringList QListQuotesToQStringList(QList <Quote> list);

   //DataBase
    bool dbConnect();
    void getInfFromDb();
    void fillMainWinFromDataBase(QList <Data> dataList);
    QSqlError deleteQuoteFromDB(int id);


    QSqlError createGenresTable();
    QSqlError createBookMainsTable();
    QSqlError createQuotesTable();
    QSqlError createTagsTable();
    QSqlError updateBookTable(Data data);
    QSqlError deleteBookFromDB(int id);

    QSqlError saveItemInDatabase(Data data);

    void repaintQuoteView();
    void updateSecondaryWindowsForCurrentBook(int index); //it's rate-window and pic-windows
    void getALlBooksFromDB();  //it needs after add new item
    void repaintReviewForCurrentBook(int index);
    ~MainWindow();

private:
    Ui:: Window *ui;


signals:
    void hideDialog();


public  slots:
    void saveXml();
    void addEditNewItem(Data data);
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
    void saveQuote(QString quote);
};

#endif // MAINWINDOW_H
