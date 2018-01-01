#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "data.h"
#include "qstringlistmodel.h"
#include "QDir"
#include "QSqlError"
#include "editdialog.h"
#include "addquotesdialog.h"
#include "QPair"
#include "QStringListModel"
#include "quote.h"
#include "settingswindow.h"
#include "QStandardItemModel"


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
    QAction *actionSave;
    QAction *actionTextBold;
    QAction *actionTextUnderline;
    QAction *actionTextItalic;
    QAction *actionTextColor;
    QAction *actionAlignLeft;
    QAction *actionAlignCenter;
    QAction *actionAlignRight;
    QAction *actionAlignJustify;
    QAction *actionUndo;
    QAction *actionRedo;



    // recomended size of book's pic
    int widthPic = 300;
    int heightPic = 400;

    QString pathXml = QDir::homePath() + "/books.xml";
    QString pathDataBase = QDir::homePath() + "/books.sqlite";

    QStandardItemModel* modelTitle;
    QStringListModel* modelQuotes;

    EditDialog * dialogAddEdit;
    AddQuotesDialog * addQuotesDialog;
    SettingsWindow * settingsWindow;

    QList <Data> dataListMain;
    Mode currentMode;
    TabWindow currentTab;

    QList <QString> genreList;
    QList <Quote> quotesList;


    QModelIndex indexEdit;


public:
    explicit MainWindow(QWidget *parent = 0);


    //GUI
    void guiSettings();
    void editMode();
    void repaintQuoteView();
    void updateSecondaryWindowsForCurrentBook(Data data); //it's rate-window and pic-windows
    void clearDataListMain();
    void repaintReviewForCurrentBook(Data currentData);
    void setGeneralInformationOnMainWindow();
    void showHiddenWidgets();


    //convert
    QString convertQPixmapToQString(QPixmap pic);
    QPixmap convertQStringToQPixmap(QString pic);


    //xml
    bool readXml(QString path);



    // current

    int getCurrentQuoteCountFrom1();
    int getCurrentBookCountFrom1();
    int getIDFromBookNumber(int bookNumber);
    int getIDFromQuoteNumber(int quoteNumber);
    Data findBookByTitle(QString title);
    QString getGenreById(int id);

    //Quote
    QList <Quote> getListQuoteForBook(int idBook);
    QStringList QListQuotesToQStringList(QList <Quote> list);


   //DataBase
    bool dbConnect();
    void getInformationFromDb();
    void fillMainWinFromDataBase(QList <Data> dataList);
    QSqlError getQuotes();
    QSqlError deleteQuoteFromDB(int id);
    QSqlError createGenresTable();
    QSqlError createBookMainsTable();
    QSqlError createQuotesTable();
    QSqlError createTagsTable();
    QSqlError updateBookTable(Data data);
    QSqlError deleteBookFromDB(int id);

    bool isGenresTableEXISTS();
    bool isBookMainsTableEXISTS();
    bool isQuotesTableEXISTS();

    QSqlError saveItemInDatabase(Data data);
    bool checkDataBeforeSave(Data data);
    void getAllBooksFromDB();  //it needs after add new item



    ~MainWindow();






private:
    Ui:: Window *ui;


signals:
    void hideDialog();


public  slots:
    void saveXml();
    void addEditNewItem(Data data);
    void chooseListIndex(QModelIndex index);
    void editModeStart();
    void addModeStart();
    void editItem(Data data);
    void deleteItem();

    void on_changeTab_released(int tab);

    void showAddDialog();
    void saveQuote(QString quote);

    void changeStyle(int type);

    void searching();
    void sort(int sortValue);
};

#endif // MAINWINDOW_H
