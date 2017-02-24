#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QString"
#include "QXmlStreamWriter"
#include "QDebug"
#include "QFile"
#include "QPixmap"
#include "QSortFilterProxyModel"
#include "QStringListModel"
#include "QBuffer"
#include "QMessageBox"
#include "QSqlDatabase"
#include "QSqlError"
#include "initdb.h"
#include "editdialog.h"
#include "QImageReader"
#include "addquotesdialog.h"
#include "QPair"
#include "QStandardItemModel"
#include "string.h"
#include "quote.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Window)
{
    ui->setupUi(this);
    ui->assesmentWidget->setUseMouse(false);
    dialogAddEdit = new EditDialog;
    addQuotesDialog = new AddQuotesDialog;
    settingsWindow = new SettingsWindow();
    modelTitle = new QStringListModel();
    modelQuotes = new QStringListModel();
    currentTab = reviewTab;
    currentMode = add;
    guiSettings();

    //

    connect(ui->addBtn, SIGNAL(clicked(bool)), this, SLOT(addModeStart()));
    connect(ui->editBtn, SIGNAL(clicked(bool)), this, SLOT(editModeStart()));
    connect(dialogAddEdit, SIGNAL(newItemIsReady(Data)), this, SLOT(addEditNewItem(Data)));
    connect(ui->deleteButton, SIGNAL(clicked(bool)), this, SLOT(deleteItem()));
    connect(ui->titlelistView, SIGNAL(clicked(QModelIndex)), this, SLOT(chooseListIndex(QModelIndex)));
    connect(ui->tabWidget, SIGNAL(tabBarClicked(int)), this, SLOT(on_changeTab_released(int)));
    connect(addQuotesDialog, SIGNAL(saveQuoteSignal(QString)), this, SLOT(saveQuote(QString)));
    connect(ui->settingsButton, SIGNAL(clicked(bool)), settingsWindow, SLOT(show()));

    dbConnect();
    getInfFromDb();


    //    readXml();
    //    tableModel = new TableModel(dataList);
    //    QSortFilterProxyModel * sortModel = new QSortFilterProxyModel(this);
    //    sortModel->setSourceModel(tableModel);
    //    sortModel->setFilterKeyColumn(0);
    //    ui->tableView->setModel(sortModel);

    guiSettings();

    setChooseFirstColumn();

    setWindowIcon(QIcon("://bookPic.jpg"));

}

void MainWindow::guiSettings()
{
    ui->sortComboBox->addItem("By title");
    ui->sortComboBox->addItem("By date read");
    ui->tabWidget->setCurrentIndex(0);


    ui->titlelistView->setModel(modelTitle);
    ui->quotesListView->setModel(modelQuotes);

//    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
//    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

//    ui->tableView->setColumnHidden(0, true);
//    ui->tableView->setColumnHidden(2, true);
//    ui->tableView->setColumnHidden(3, true);
//    ui->tableView->setColumnHidden(4, true);
//    ui->tableView->setColumnHidden(5, true);
//    ui->tableView->setColumnHidden(6, true);

//    ui->tableView->resizeColumnsToContents();
//    ui->tableView->resizeRowsToContents();

    //ui->tableView->setColumnWidth(0, 20);
}

void MainWindow::setChooseFirstColumn()
{


}

QString MainWindow::convertQPixmapToQString(QPixmap pic)
{
    QByteArray bArray;
    QBuffer buffer(&bArray);
    buffer.open(QIODevice::WriteOnly);
    pic.save(&buffer, "PNG");
    QString photoString(bArray.toBase64());
    return photoString;
}

QPixmap MainWindow::convertQStringToQPixmap(QString pic)
{
    QByteArray textByte =  QByteArray::fromBase64(pic.toLocal8Bit());
    QPixmap pix;
    pix.loadFromData(textByte, "png");
    return pix;
}

bool MainWindow::readXml()
{
//    qDebug() << "reading";

//    QFile in(path);
//    if(!in.open(QFile::ReadOnly | QFile::Text))
//    {
//      qDebug() << "file not open for read!";
//      return false;
//    }

//    QXmlStreamReader reader;
//    reader.setDevice(&in);

//    while(!reader.atEnd() && !reader.error())
//    {
//        qDebug() <<"text start "<< reader.text().toString();

//        QXmlStreamReader::TokenType token = reader.readNext();

//        if(token == QXmlStreamReader::StartDocument) {
//            qDebug() << "StartDoc";
//            continue;
//        }



//        if(token == QXmlStreamReader::StartElement) {
//            qDebug() << "StartReader";
//            if(reader.name() == "book") {
//                qDebug() << "Book";
//                QString assesment = reader.attributes().value("assesment").toString();
//                QString authorName = reader.attributes().value("author").toString();
//                QString bookTitle =  reader.attributes().value("title").toString();
//                QString date = reader.attributes().value("date").toString();
//                QString  review = reader.attributes().value("review").toString();
//                QString imageQString = reader.attributes().value("picture").toString();

//                QByteArray textByte =  QByteArray::fromBase64(imageQString.toLocal8Bit());

//                QPixmap pix;
//                pix.loadFromData(textByte, "png");

//                Data tmpData(assesment, authorName, bookTitle,
//                             date,  review, pix);


//                qDebug() << "assesment "<< assesment
//                         <<" authorName "<< authorName
//                        <<" bookTitle "<< bookTitle
//                         <<" date "<< date
//                         << " review "<<  review;


//                dataList.append(tmpData);
//                dataStringList.append(tmpData.toString());

//            }
//        }

//        reader.readNext();

//        qDebug() <<"text end "<< reader.text().toString();
//    }


//    updateDataList();

//    in.close();

   return true;

}

void MainWindow::showMainInformation()
{

}

bool MainWindow::dbConnect()
{

    // initialize the database
     QSqlError err = initDb();


//     qDebug() << "**************************************";
//     qDebug() << (createGenresTable()).text();
//     qDebug() << (createBookMainsTable()).text();
//     qDebug() << (createQuotesTable()).text();
//    // qDebug() << (createTagsTable()).text();
//     qDebug() << "**************************************";


qDebug() << "err " << err.text();

//    if (err.type() != QSqlError::NoError) {
//        showError(err);
//        return;
//    }


}

void MainWindow::getInfFromDb()
{
    QSqlQuery query;

    //get in from books

    qDebug() << "from db " <<query.size();

    getALlBooksFromDB();

    query.exec("SELECT * FROM genres");

    while (query.next()) {
        QString name = query.value(0).toString();
        QString value = query.value(1).toString();
        genreHash[name.toInt()] = value;
    }

    getQuotes();
}


QSqlError MainWindow::getQuotes()
{
    quotesList.clear();
    QSqlQuery query;
    query.exec("SELECT * FROM quotes");
    while (query.next()) {        
        int idQuote = query.value(0).toInt();
        QString value = query.value(1).toString();
        int nameBookId = query.value(2).toInt();

        Quote quoteTmp(idQuote, value, nameBookId);
        quotesList.append(quoteTmp);
    }

    return QSqlError();
}

void MainWindow::updateDataListMain()
{
    dataListMain.clear();

}

int MainWindow::getCurrentQuoteCountFrom1()
{
    QModelIndexList currentQuoteIndexes = ui->quotesListView->selectionModel()->selectedIndexes();
    QModelIndex currentIndex = currentQuoteIndexes.at(0);
    qDebug() << "selected " << currentIndex.row();

    return currentIndex.row() + 1;
}

int MainWindow::getCurrentBookCountFrom1()
{
    QModelIndexList currentsBooksIndexList = ui->titlelistView->selectionModel()->selectedIndexes();
    return currentsBooksIndexList.at(0).row() + 1;  //cause we count in db from 1,  NOT from 0!
}

int MainWindow::getIDFromBookNumber(int bookNumber)
{
    Data data =  dataListMain.at(bookNumber - 1);
    return data.getId();
}

int MainWindow::getIDFromQuoteNumber(int quoteNumber)
{
    int currentBookNumber = getCurrentBookCountFrom1();
    int idBook = getIDFromBookNumber(currentBookNumber);


    QList <Quote> listOneQuote = getListQuoteForBook(idBook);

    Quote quoteCurrent = listOneQuote.at(quoteNumber - 1);

    return quoteCurrent.getIdQuote();
}

QList<Quote> MainWindow::getListQuoteForBook(int idBook)
{
    QList <Quote> lst;
    foreach (auto quote, quotesList) {
        if (quote.getIdBook() == idBook)
            lst.append(quote);
    }
    return lst;
}

QStringList MainWindow::QListQuotesToQStringList(QList<Quote> list)
{
    QStringList stringList;
    foreach (auto quote, list) {
        stringList << quote.getQuoteString();
    }
    return stringList;
}





void MainWindow::fillMainWinFromDataBase(QList<Data> dataList)
{
    QStringList titleList;
    foreach (Data data, dataList) {
        titleList << data.getBookTitle();
    }

    modelTitle->setStringList(titleList);
}

QSqlError MainWindow::createGenresTable()
{   
    QSqlQuery q;

    if (!q.exec(QLatin1String("create table if not exists genres"
                              "(id integer primary key,"
                              " name varchar)")))
        return q.lastError();


    if (!q.prepare(QLatin1String("insert into genres"
                                 " (name) "
                                 "values(?)")))
        return q.lastError();

    QVariant sfictionID = addGenre(q, QLatin1String("Science Fiction"));
    QVariant comedyID = addGenre(q, QLatin1String("Comedy"));
    QVariant fictionID = addGenre(q, QLatin1String("Fiction"));
    QVariant fantasyID = addGenre(q, QLatin1String("Fantasy"));
    QVariant dramaID = addGenre(q, QLatin1String("Drama"));
    QVariant horrorID = addGenre(q, QLatin1String("Horror"));
    QVariant nonfictionID = addGenre(q, QLatin1String("Non-fiction"));
    QVariant realisticFictionID = addGenre(q, QLatin1String("Realistic fiction"));
    QVariant romanceID = addGenre(q, QLatin1String("Romance novel"));
    QVariant satireID = addGenre(q, QLatin1String("Satire"));
    QVariant tragedyID = addGenre(q, QLatin1String("Tragedy"));
    QVariant tragicomedyID = addGenre(q, QLatin1String("Tragicomedy"));

     qDebug() <<" createGenresTable ok";

    return q.lastError();
}

QSqlError MainWindow::updateBookTable(Data data)
{

    QSqlQuery q;

    if (!q.prepare(QLatin1String("update books "
                                 " SET "
                                 " title = ? , "
                                 " authors = ?, "
                                 " mainIdea = ? , "
                                 " rateInt = ? , "
                                 " genreId = ? , "
                                 " pages = ? , "
                                 " dateS = ? , "
                                 " dateF = ? , "
                                 " tagsList = ? , "
                                 " review = ? , "
                                 " bookCoverPixmap = ? "
                                 "WHERE id = ?")))
        return q.lastError();



    QString title = data.getBookTitle();
    QString authors = data.getAuthorsName();
    QString mainIdea = data.getMainIdea();
    int rateInt = data.getRateInt();
    int genre = data.getGenre();
    int pages = data.getPages();
    QDate dateS = data.getDateS();
    QDate dateF = data.getDateF();
    QStringList tagsList = data.getTagsList();
    QString tags = tagsList.join(", ");
    QString  review = data.getReview();
    QPixmap bookCoverPixmap = data.getBookCoverPixmap();
    QString type = data.getTypePic();
    QByteArray inByteArrayBookCover;
    QBuffer inBuffer(&inByteArrayBookCover);
    inBuffer.open(QIODevice::WriteOnly);

    std::string fname = type.toStdString();
    char * cstrType = new char [fname.size() + 1];
    strcpy( cstrType, fname.c_str() );
    bookCoverPixmap.save(&inBuffer, cstrType);

    int id = data.getId();


    updateBook(q,
               title,
               authors,
               mainIdea,
               rateInt,
               genre,
               pages,
               dateS,
               dateF,
               tags,
               review,
               inByteArrayBookCover,
               id);

    return q.lastError();

}


QSqlError MainWindow::deleteQuoteFromDB(int id)
{
     QSqlQuery q;

     if (!q.prepare(QLatin1String("DELETE FROM quotes WHERE id = ?")))
         return q.lastError();

      deleteQuote(q, id);

      return q.lastError();
}



QSqlError MainWindow::deleteBookFromDB(int id)
{
     QSqlQuery q;

     q.exec("PRAGMA foreign_keys = ON;");

     if (!q.prepare(QLatin1String("DELETE FROM books WHERE id = ?")))
         return q.lastError();


      deleteBook(q, id);

      return q.lastError();
}

QSqlError MainWindow::createBookMainsTable()
{
    QSqlQuery q;
    q.exec("PRAGMA foreign_keys = ON;");


    if (!q.exec(QLatin1String("create table IF not EXISTS books"
                              "(id integer primary key, "
                              "title varchar, "
                              "authors varchar,"
                              "mainIdea TEXT, "
                              "rateInt integer, "
                              "genreId integer, "
                              "pages integer, "
                              "dateS date, "
                              "dateF date, "
                              "tagsList TEXT, "
                              "review TEXT, "
                              "bookCoverPixmap BLOB, "
                              "dateAdded date, "
                              "FOREIGN KEY(genreId) REFERENCES genres(id)"
                              ")")))
        return q.lastError();

       qDebug() <<" createBookMainsTable ok";

    return q.lastError();
}

QSqlError MainWindow::createQuotesTable()
{
    QSqlQuery q;

    q.exec("PRAGMA foreign_keys = ON;");

    if (!q.exec(QLatin1String("create table if not exists quotes"
                              "(id integer primary key,"
                              "text varchar,"
                              "idBooks integer, "
                              "FOREIGN KEY(idBooks) REFERENCES books(id) "
                              "ON DELETE CASCADE)")))
        return q.lastError();

       qDebug() << "createQuotesTable ok";

       return q.lastError();

}

QSqlError MainWindow::createTagsTable()
{
    QSqlQuery q;

    if (!q.exec(QLatin1String("create table if not exists tags"
                              "(id integer primary key,"
                              "text varchar,"
                              "idBooks integer, "
                              "FOREIGN KEY(idBooks) REFERENCES books(id))")))
        return q.lastError();
}

QSqlError MainWindow::saveItemInDatabase(Data data)
{
    QString title = data.getBookTitle();
    QString authors = data.getAuthorsName();
    QString mainIdea = data.getMainIdea();
    int rateInt = data.getRateInt();
    int genre = data.getGenre();
    int pages = data.getPages();
    QDate dateS = data.getDateS();
    QDate dateF = data.getDateF();
    QStringList tagsList = data.getTagsList();
    QString tags = tagsList.join(", ");
    QString  review = data.getReview();
    QPixmap bookCoverPixmap = data.getBookCoverPixmap();
    QString type = data.getTypePic();


    QSqlQuery q;
    q.prepare(QLatin1String("insert into books "
                            "(title, authors, mainIdea, "
                            "rateInt, genreId, pages, "
                            "dateS, dateF, tagsList, "
                            "review, bookCoverPixmap)"
                            "values(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)"));


    QByteArray inByteArrayBookCover;
    QBuffer inBuffer(&inByteArrayBookCover);
    inBuffer.open(QIODevice::WriteOnly);

    std::string fname = type.toStdString();
    char * cstrType = new char [fname.size() + 1];
    strcpy( cstrType, fname.c_str() );
    bookCoverPixmap.save(&inBuffer, cstrType);


   qDebug() << "size " << inBuffer.size();


   QVariant id = addItem(q,
                         title,
                         authors,
                         mainIdea,
                         rateInt,
                         genre,
                         pages,
                         dateS,
                         dateF,
                         tags,
                         review,
                         inByteArrayBookCover);

   return q.lastError();
}

void MainWindow::repaintQuoteView()
{
    modelQuotes->removeRows(0, modelQuotes->rowCount());

    getQuotes();

    int currentBookNumber = getCurrentBookCountFrom1();

    int currentBookID = getIDFromBookNumber(currentBookNumber);

    QList <Quote> lst = getListQuoteForBook(currentBookID);

    QStringList quotesBook = QListQuotesToQStringList(lst);

    modelQuotes->setStringList(quotesBook);
}

void MainWindow::updateSecondaryWindowsForCurrentBook(int currentBookCountFrom1)
{
    Data currentData = dataListMain.at(currentBookCountFrom1 - 1);
    QPixmap pic = currentData.getBookCoverPixmap();
    if (pic.isNull())
             pic.load(":empty.png");

    if (pic.width() > widthPic || pic.height() > heightPic)
        pic = pic.scaled(QSize(widthPic, heightPic), Qt::KeepAspectRatio);

    ui->labelPic->setAlignment(Qt::AlignCenter);
    ui->labelPic->setPixmap(pic);


    ui->assesmentWidget->setAssesment(currentData.getRateInt());

    ui->commonText->setText(currentData.getPages() + " pages "
                                                     "\n\n authors: " + currentData.getAuthorsName() +
                                                     "\n\n tags: " + currentData.getTagsList().join(",") +
                                                     "\n\n date: " + currentData.getDateS().toString("dd.MM.yyyy") +
                                                     "\n\n date: " + currentData.getDateF().toString("dd.MM.yyyy") +
                                                     "\n\n genre: " + currentData.getGenre() +
                                                     "\n\n date added: " + currentData.getDateAdded().toString("dd.MM.yyyy"));

}

void MainWindow::getALlBooksFromDB()
{
    QSqlQuery query;

    //get inf from books table
    query.exec("SELECT * FROM books");

    QList <Data> dataList;
    dataListMain.clear();

     while (query.next()) {
         int id = query.value(0).toInt();
         QString title = query.value(1).toString();
         QString authors = query.value(2).toString();
         QString mainIdea = query.value(3).toString();

         int rateInt = query.value(4).toInt();
         int genreId = query.value(5).toInt();
         int pages = query.value(6).toInt();

         QDate dateS = query.value(7).toDate();
         QDate dateF = query.value(8).toDate();

         QString tagsString = query.value(9).toString();
         QStringList tagsList = tagsString.split(", ");

         QString review = query.value(10).toString();

         QByteArray picArray = query.value(11).toByteArray();

         QPixmap pic;
         pic.loadFromData(picArray);
         QImageReader reader(picArray);
         QString type = reader.format();


         Data data(id, title, authors, mainIdea, rateInt, genreId, pages,
                           dateS, dateF, tagsList, review, pic, type);

         dataList.append(data);
     }

     fillMainWinFromDataBase(dataList);
     dataListMain = dataList;
}

void MainWindow::repaintReviewForCurrentBook(int currentBookCountFrom1)
{
    Data currentData = dataListMain.at(currentBookCountFrom1 - 1);
    ui->plainTextEdit->setPlainText(currentData.getReview());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::saveXml()
{
//    QFile xmlFile(path);

//    if (xmlFile.exists())
//    {
//        qDebug() << "file exists";
//    }
//    else
//    {
//        qDebug() << "file doesn't exist";
//    }


//    if (xmlFile.isOpen())
//    {
//        qDebug() << "file was open";
//        xmlFile.close();
//    }

//    QFileDevice::FileError err = QFileDevice::NoError;

//    if (!xmlFile.open(QIODevice::WriteOnly | QIODevice::Text))
//    {
//        qDebug() << xmlFile.errorString();
//        qDebug() << "file not open for save";

//        return;
//    }


//    QXmlStreamWriter xml(&xmlFile);
//    xml.setAutoFormatting(true);


//    xml.writeStartDocument();
//    xml.writeStartElement("books");


//    QList <Data> datalst = tableModel->getList();

//    for(int i = 0; i < datalst.length(); i++)
//    {
//        Data data = datalst.at(i);

//        QString assesment = data.getAssessment();
//        QString authorName = data.getAuthorName();
//        QString bookTitle = data.getBookTitle();
//        QString date = data.getDate();
//        QString review = data.getReview();
//        QPixmap bookPic = data.getBookCoverPixmap();
//        QString bookCoverQString = convertQPixmapToQString(bookPic);
//        qint32  id = data.getId();


//        xml.writeStartElement("book");
//        xml.writeAttribute("assesment", assesment);
//        xml.writeAttribute("author", authorName);
//        xml.writeAttribute("title", bookTitle);
//        xml.writeAttribute("date", date);
//        xml.writeAttribute("review", review);
//        xml.writeAttribute("picture", bookCoverQString);
//        xml.writeCharacters (QString::number(id));


//        qDebug() << "assesment "<< assesment
//                 <<" authorName "<< authorName
//                <<" bookTitle "<< bookTitle
//                 <<" date "<< date
//                 << " review "<<  review;



//        xml.writeEndElement();
//    }


//    xml.writeEndElement();
//    xml.writeEndDocument();

//    xmlFile.close();
//    if (xmlFile.error())
//    {
//        qDebug() << "file error!";
//        return;
//    }

//    qDebug() << "file is ok!";

//  xmlFile.close();

}

void MainWindow::addEditNewItem(Data data)
{
    if (currentMode == add)
    {

    qDebug() << " getNewItem !!! " <<data.toString() << dataListMain.length();

    saveItemInDatabase(data);
    getALlBooksFromDB();

    ui->titlelistView->setCurrentIndex(modelTitle->index(dataListMain.length() - 1));

    updateSecondaryWindowsForCurrentBook(dataListMain.length()); //Count from 1
    repaintReviewForCurrentBook(dataListMain.length());  //focus on last added. Count from 1


    }
    else if (currentMode == edit)
    {
        QSqlError error =  updateBookTable(data);
        qDebug() << error.text();
        qDebug() <<"";

        int currentBookCountFrom1 = getCurrentBookCountFrom1();
        getALlBooksFromDB();    //we need update after edit

       updateSecondaryWindowsForCurrentBook(currentBookCountFrom1);
       repaintReviewForCurrentBook(currentBookCountFrom1);  //focus on last added

    }
}

void MainWindow::updateDataList()
{

}

void MainWindow::testSlot(Data mes)
{
    qDebug() << "test Slot " << mes.toString();
}

void MainWindow::chooseListIndex(QModelIndex index)
{
    qDebug() << "here" <<index.row() << index.column();

    int currentBookCountFrom1 = index.row() + 1;
    Data currentData = dataListMain.at(index.row());

    if(currentTab == reviewTab)
    {
        //ui->mainIdea->setText(currentData.getMainIdea());
        ui->plainTextEdit->setPlainText(currentData.getReview());

    updateSecondaryWindowsForCurrentBook(currentBookCountFrom1);
    }
    else if (currentTab == quotesTab)
    {
        repaintQuoteView();
        updateSecondaryWindowsForCurrentBook(currentBookCountFrom1);
    }
}


void MainWindow::on_addButton_released()
{

}

void MainWindow::on_deleteButton_released()
{

}

void MainWindow::on_updateButton_released()
{

}

void MainWindow::on_changeTab_released(int tab)
{
    qDebug() << "tab "<<tab;
    if (tab == reviewTab)
    {
       currentTab = reviewTab;
    }
    else if (tab == quotesTab)
    {
       int currentBookNumber = getCurrentBookCountFrom1();

       int currentBookID =  getIDFromBookNumber(currentBookNumber);

       currentTab = quotesTab;

       modelQuotes->removeRows(0, modelQuotes->rowCount());

       QList <Quote> lst = getListQuoteForBook(currentBookID);

       QStringList quotesBook = QListQuotesToQStringList(lst);

       modelQuotes->setStringList(quotesBook);
    }

}

void MainWindow::showAddDialog()
{
    qDebug() << "showAddDialog";

    if (currentTab == reviewTab)
    {      
            dialogAddEdit->show();
    }
    else if (currentTab == quotesTab)
    {
        editModeStart();
    }
}

void MainWindow::saveQuote(QString quote)
{
    if (currentMode == add)
    {
        int currentBookNumber = getCurrentBookCountFrom1();
        int currentBookID = getIDFromBookNumber(currentBookNumber);
        QSqlQuery q;
        q.prepare(QLatin1String("insert into quotes "
                                "(text, idBooks)"
                                "values(?, ?)"));


        QVariant id = addQuote(q,
                               quote,
                               currentBookID);

        repaintQuoteView();
    }
    else if (currentMode == edit)
    {
         int currentQuoteNumber = getCurrentQuoteCountFrom1();
         int idQuote = getIDFromQuoteNumber(currentQuoteNumber);

         QSqlQuery q;
//         if (
                 q.prepare(QLatin1String("UPDATE quotes "
                                 "SET "
                                 "text = ? "
                                 "WHERE id = ?"));
//                 )
//            return q.lastError();


         QSqlError error =  updateQuote(q,
                                   quote,
                                   idQuote);

         repaintQuoteView();

    }
}


void MainWindow::editModeStart()
{
     currentMode = edit;

     if (currentTab == reviewTab)
     {
         int currentBook = getCurrentBookCountFrom1();
         Data currentData = dataListMain.at(currentBook - 1);
         dialogAddEdit->setGenre(genreHash);
         dialogAddEdit->viewDataForEdit(currentData);
         dialogAddEdit->show();
     }
     else if (currentTab == quotesTab)
     {
         int currentBookNumber = getCurrentBookCountFrom1();
         int currentBookID = getIDFromBookNumber(currentBookNumber);

         QList <Quote> lst = getListQuoteForBook(currentBookID);

         int currentQuoteNumber = getCurrentQuoteCountFrom1();

         Quote quote = lst.at(currentQuoteNumber - 1);

         addQuotesDialog->viewData(quote.getQuoteString());
         addQuotesDialog->show();
     }

}

void MainWindow::addModeStart()
{
    currentMode = add;

    if (currentTab == reviewTab)
    {
        dialogAddEdit->setGenre(genreHash);
        dialogAddEdit->setStartDate();
        dialogAddEdit->setFinishDate();
        dialogAddEdit->setPicDefault();

        dialogAddEdit->show();
    }
    else if (currentTab == quotesTab)
    {
        addQuotesDialog->show();
    }

}

void MainWindow::editItem(Data data)
{
    //emit
}

void MainWindow::deleteItem()
{
    if (currentTab == reviewTab)
    {
        QModelIndexList currentsBooksIndexList = ui->titlelistView->selectionModel()->selectedIndexes();
        int curentBookInt = currentsBooksIndexList.at(0).row();
        Data currentData = dataListMain.at(curentBookInt);

        QMessageBox msgBox;
        msgBox.setText("Warning! You are going to delete line " + QString::number(curentBookInt ));
        msgBox.setInformativeText("Do you really want it?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
        int ret = msgBox.exec();

        switch (ret) {
        case QMessageBox::Yes:
            qDebug()<< "index for delete " << curentBookInt;
            qDebug() <<  deleteBookFromDB(currentData.getId());

            getALlBooksFromDB();    //we need update after edit

            //?  updateSecondaryWindowsForCurrentBook(currentBook);
            //?  repaintReviewForCurrentBook(currentBook);  //focus on last added

            break;
        case QMessageBox::Cancel:
            break;
        default:
            break;
        }

    }
    else if (currentTab == quotesTab)
    {
        int quoteNumber = getCurrentQuoteCountFrom1();
        int quoteID = getIDFromQuoteNumber(quoteNumber);

        QMessageBox msgBox;
        msgBox.setText("Warning! You are going to delete quote " + QString::number(quoteNumber));
        msgBox.setInformativeText("Do you really want it?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
        int ret = msgBox.exec();

        switch (ret) {
        case QMessageBox::Yes:
        {
            qDebug()<< "index for delete " << quoteNumber;
            qDebug() << deleteQuoteFromDB(quoteID);

            //we need update after delete
            repaintQuoteView() ;
        }

            break;

        case QMessageBox::Cancel:
            break;
        default:
            break;
        }
    }
}
