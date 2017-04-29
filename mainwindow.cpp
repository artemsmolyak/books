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
#include "QToolBar"
#include "QTextCharFormat"
#include "QStyleFactory"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Window)
{
    ui->setupUi(this);

    setWindowTitle("bookshelf!");

    dialogAddEdit = new EditDialog(this);
    addQuotesDialog = new AddQuotesDialog(this);
    settingsWindow = new SettingsWindow(this);
    modelTitle = new QStandardItemModel(this);
    modelQuotes = new QStringListModel(this);

    currentTab = reviewTab;
    currentMode = add;


    connect(ui->addBtn, SIGNAL(clicked(bool)), this, SLOT(addModeStart()));
    connect(ui->editBtn, SIGNAL(clicked(bool)), this, SLOT(editModeStart()));
    connect(dialogAddEdit, SIGNAL(newItemIsReady(Data)), this, SLOT(addEditNewItem(Data)));
    connect(ui->deleteButton, SIGNAL(clicked(bool)), this, SLOT(deleteItem()));
    connect(ui->titlelistView, SIGNAL(clicked(QModelIndex)), this, SLOT(chooseListIndex(QModelIndex)));
    connect(ui->tabWidget, SIGNAL(tabBarClicked(int)), this, SLOT(on_changeTab_released(int)));
    connect(addQuotesDialog, SIGNAL(saveQuoteSignal(QString)), this, SLOT(saveQuote(QString)));
    connect(ui->settingsButton, SIGNAL(clicked(bool)), settingsWindow, SLOT(show()));
    connect(ui->lineEdit, SIGNAL(textChanged(QString)), this, SLOT(searching()));
    connect(ui->sortComboBox, SIGNAL(activated(int)), this, SLOT(sort(int)));
    connect(settingsWindow, SIGNAL(saveXmlButtonClick()), this, SLOT(saveXml()));
    connect(settingsWindow, SIGNAL(changeStyle(int)), this, SLOT(changeStyle(int)));

    dbConnect();
    guiSettings();
    getInformationFromDb();
}




void MainWindow::guiSettings()
{
    ui->assesmentWidget->setUseMouse(false);
    ui->toRightButton->setEnabled(false);
    ui->sortComboBox->clear();

    ui->sortComboBox->addItem("By date added");
    ui->sortComboBox->addItem("By title");
    ui->tabWidget->setCurrentIndex(0);


    ui->titlelistView->setWordWrap(true);
    ui->quotesListView->setWordWrap(true);


    ui->titlelistView->setViewMode(QListView::ListMode);
    ui->titlelistView->setIconSize(QSize(24, 24));


    ui->titlelistView->setModel(modelTitle);
    ui->quotesListView->setModel(modelQuotes);

    ui->tabWidget->setTabEnabled(0, true);
    ui->tabWidget->setTabEnabled(1, false);

    setGeneralInformationOnMainWindow();

    ui->editBtn->setEnabled(false);
    ui->deleteButton->setEnabled(false);
    ui->widget_3->setEnabled(false);
    ui->assesmentWidget->setVisible(false);
    ui->labelPic->setVisible(false);


    ui->textEdit->setAlignment(  Qt::AlignCenter );
    ui->textEdit->setAlignment(  Qt::AlignCenter );
    ui->textEdit->setTextBackgroundColor(Qt::lightGray);

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

bool MainWindow::readXml(QString path)
{
    qDebug() << "reading xml";

    QFile in(path);
    if(!in.open(QFile::ReadOnly | QFile::Text))
    {
      qDebug() << "file not open for read!";
      return false;
    }

    QXmlStreamReader reader;
    reader.setDevice(&in);

    while(!reader.atEnd() && !reader.error())
    {
        qDebug() <<"text start "<< reader.text().toString();

        QXmlStreamReader::TokenType token = reader.readNext();

        if(token == QXmlStreamReader::StartDocument) {
            qDebug() << "StartDoc";
            continue;
        }



        if (token == QXmlStreamReader::StartElement) {
            qDebug() << "StartReader";
            if  (reader.name() == "book") {
                qDebug() << "Book";
                QString assesment = reader.attributes().value("assesment").toString();
                QString authorName = reader.attributes().value("author").toString();
                QString bookTitle =  reader.attributes().value("title").toString();
                QString date = reader.attributes().value("date").toString();
                QString  review = reader.attributes().value("review").toString();
                QString imageQString = reader.attributes().value("picture").toString();

                QByteArray textByte =  QByteArray::fromBase64(imageQString.toLocal8Bit());

                QPixmap pix;
                pix.loadFromData(textByte, "png");

                //                Data tmpData(assesment, authorName, bookTitle,
                //                             date,  review, pix);
                //dataList.append(tmpData);
                //dataStringList.append(tmpData.toString());

            }
        }

        reader.readNext();

        qDebug() <<"text end "<< reader.text().toString();
    }

    in.close();

   return true;
}


bool MainWindow::dbConnect()
{
    // initialize the database
    QSqlError err = initDb();

    if (!isGenresTableEXISTS()) createGenresTable();
    if (!isBookMainsTableEXISTS()) createBookMainsTable();
    if (!isQuotesTableEXISTS()) createQuotesTable();

    return true;
}

void MainWindow::getInformationFromDb()
{
    QSqlQuery query;
    getAllBooksFromDB();
    query.exec("SELECT * FROM genres");
   genreList.clear();

    while (query.next()) {
        QString value = query.value(1).toString();
         genreList.append(value);
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

void MainWindow::clearDataListMain()
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

    if (currentsBooksIndexList.length() == 0)
        return -1;

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

Data MainWindow::findBookByTitle(QString title)
{
    int i = 0;
    foreach (Data data, dataListMain) {
        if (title == data.getBookTitle())
            return data;
        ++i;
    }
    return Data();
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

    for(int i = 0; i < modelTitle->rowCount(); i++)
    {
        QStandardItem *item = modelTitle->item(i);
        delete item;
    }

    modelTitle->clear();

    //QStringList titleList;
    int i = 0;
    bool flag = true;
    foreach (Data data, dataList) {
       // titleList << data.getBookTitle();

        QStandardItem *item = new QStandardItem(data.getBookTitle());
        item->setIcon(data.getBookCoverPixmap());
        if (flag)
        {
            QBrush brush(QColor(255, 239, 213));
            item->setBackground(brush);
        }
        flag = !flag;
        modelTitle->setItem(i++, 0, item);
    }
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
                                 " bookCoverPixmap = ? ,"
                                 " typePic = ? "
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
               data.getTypePic(),
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

bool MainWindow::isGenresTableEXISTS()
{
    QSqlQuery query;

    query.exec("SELECT name FROM sqlite_master WHERE type='table' AND name='genres';");

     while (query.next()) {
         return true;
     }
     return false;
}

bool MainWindow::isBookMainsTableEXISTS()
{
    QSqlQuery query;

    query.exec("SELECT name FROM sqlite_master WHERE type='table' AND name='books';");

     while (query.next()) {
         return true;
     }
     return false;
}

bool MainWindow::isQuotesTableEXISTS()
{
    QSqlQuery query;

    query.exec("SELECT name FROM sqlite_master WHERE type='table' AND name='quotes';");

     while (query.next()) {
         return true;
     }
     return false;
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
                              "typePic varchar, "
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
                            "review, bookCoverPixmap, dateAdded, typePic)"
                            "values(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)"));


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
                         inByteArrayBookCover,
                         QDateTime::currentDateTime().date(),
                         type);

   return q.lastError();
}

bool MainWindow::checkDataBeforeSave(Data data)
{
return true;
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

void MainWindow::updateSecondaryWindowsForCurrentBook(Data currentData)
{
    QPixmap pic = currentData.getBookCoverPixmap();
    if (pic.isNull())
             pic.load(":empty.png");

    if (pic.width() > widthPic || pic.height() > heightPic)
        pic = pic.scaled(QSize(widthPic, heightPic), Qt::KeepAspectRatio);

    ui->labelPic->setAlignment(Qt::AlignCenter);
    ui->labelPic->setPixmap(pic);


    ui->assesmentWidget->setAssesment(currentData.getRateInt());


    ui->commonText->setText("");    

    ui->commonText->setWordWrap(true);

    ui->mainIdeaLbl->setWordWrap(true);
    ui->mainIdeaLbl->setText("<i>" + currentData.getMainIdea()+"</i>");

    //QString str = "<b>" + currentData.getMainIdea() + "</b>" + "<br><br>";
    QString str =  " <style>"
            "h4 {"
             "background: #F5DEB3;  /* #FFEFD5;  Цвет фона под заголовком */"
             // "color: green; /* Цвет текста */"
            // "padding: 2px; /* Поля вокруг текста */"
            "}"
           "</style>"
           "<br> <h4>   </h4><br>";

    str += "<b>authors:  </b>" + currentData.getAuthorsName()  + "<br>";
    str += "<h4>  </h4><br>";
    str += "<b>date read:  </b>" + currentData.getDateF().toString("dd.MM.yyyy") + "<br>";
    str += "<h4>  </h4><br>";

    QString genreString = getGenreById(currentData.getGenre());
    str += "<b>genre:  </b>" + genreString  + "<br>";
    str += "<h4></h4><br>";

   //  str += "<b>date added:  </b>" + currentData.getDateAdded().toString("dd.MM.yyyy") + "<br>";
   //  str += "<h4></h4>";

    ui->commonText->setText(str);
}

void MainWindow::getAllBooksFromDB()
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

         QDate dateAdded = query.value(12).toDate();

         QPixmap pic;
         pic.loadFromData(picArray);

         //QImageReader reader(picArray);
         QString type = query.value(13).toString(); //reader.format();


         Data data(id, title, authors, mainIdea, rateInt, genreId, pages,
                           dateS, dateF, tagsList, review, pic, type, dateAdded);

         dataList.append(data);
     }

     fillMainWinFromDataBase(dataList);
     dataListMain = dataList;
}

void MainWindow::repaintReviewForCurrentBook(Data currentData)
{
    ui->textEdit->setHtml(currentData.getReview());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setGeneralInformationOnMainWindow()
{
    getAllBooksFromDB();

    const QString str = "in database  "
             + QString::number(dataListMain.length())
                + " books,  choose one or add a new";

    ui->textEdit->setPlainText(str);
}



void MainWindow::saveXml()
{

    qDebug() << "save xml";

    getAllBooksFromDB();

    QFile xmlFile(pathXml);

    if (xmlFile.exists())
    {
        qDebug() << "file exists";
    }
    else
    {
        qDebug() << "file doesn't exist";
    }


    if (xmlFile.isOpen())
    {
        qDebug() << "file was open";
        xmlFile.close();
    }

    QFileDevice::FileError err = QFileDevice::NoError;

    if (!xmlFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << xmlFile.errorString();
        qDebug() << "file not open for save";

        return;
    }


    QXmlStreamWriter xml(&xmlFile);
    xml.setAutoFormatting(true);


    xml.writeStartDocument();
    xml.writeStartElement("books");


    QList <Data> datalst = dataListMain;

    for(int i = 0; i < datalst.length(); i++)
    {
        Data data = datalst.at(i);

        QString rate = QString::number(data.getRateInt());
        QString authorName = data.getAuthorsName();
        QString bookTitle = data.getBookTitle();
        QString dateStart = data.getDateS().toString("dd.MM.yyyy");
        QString dateFinish = data.getDateF().toString("dd.MM.yyyy");
        QString review = data.getReview();

        QString dataAdded = data.getDateAdded().toString("dd.MM.yyyy");
        QString genre = getGenreById(data.getGenre());
        QString pages = QString::number(data.getPages());
        QString mainIdea = data.getMainIdea();

        //QPixmap bookPic = data.getBookCoverPixmap();
        //QString bookCoverQString = convertQPixmapToQString(bookPic);
        qint32  id = data.getId();


        xml.writeStartElement("book");
        xml.writeCharacters (QString::number(id));
        xml.writeAttribute("title", bookTitle);
        xml.writeAttribute("author", authorName);
        xml.writeAttribute("rate", rate);
        xml.writeAttribute("dateStart", dateStart);
        xml.writeAttribute("dateFinish", dateFinish);
        xml.writeAttribute("review", review);

        xml.writeAttribute("dataAdded", dataAdded);
        xml.writeAttribute("genre", genre);
        xml.writeAttribute("pages", pages);
        xml.writeAttribute("mainIdea", mainIdea);
        //xml.writeAttribute("picture", bookCoverQString);


        qDebug() << "assesment "<< rate
                 <<" authorName "<< authorName
                <<" bookTitle "<< bookTitle
                 <<" date "<< dateStart
                 << " review "<<  review;

        xml.writeEndElement();
    }


    xml.writeEndElement();
    xml.writeEndDocument();

    xmlFile.close();
    if (xmlFile.error())
    {
        qDebug() << "file error!";
        return;
    }

    qDebug() << "file is ok!";

  xmlFile.close();

  QMessageBox msgBox;
  msgBox.setText("xml saved");
  msgBox.exec();

}

void MainWindow::addEditNewItem(Data data)
{
    if (currentMode == add)
    {

        qDebug() << " getNewItem !!! " <<data.toString() << dataListMain.length();

        checkDataBeforeSave(data);

        QSqlError error =  saveItemInDatabase(data);
        if (error.type() != QSqlError::NoError)
        {
            QMessageBox msgBox;
            msgBox.setText("Problems with save in database");
            msgBox.exec();
        }

        getAllBooksFromDB();

        if (dataListMain.length() != 0)
        {
            updateSecondaryWindowsForCurrentBook(data); //Count from 1
            repaintReviewForCurrentBook(data);  //focus on last added. Count from 1

            showHiddenWidgets();
        }

    }
    else if (currentMode == edit)
    {
        QSqlError error =  updateBookTable(data);
        qDebug() << error.text();
        qDebug() <<"";

        getAllBooksFromDB();    //we need update after edit
        updateSecondaryWindowsForCurrentBook(data);
        repaintReviewForCurrentBook(data);  //focus on last added
    }
}

void MainWindow::chooseListIndex(QModelIndex index)
{
    showHiddenWidgets();

    QMap<int, QVariant> map = modelTitle->itemData(index);

    QVariant titleBook = map[0].toString();
    Data currentData = findBookByTitle(titleBook.toString());

    if(currentTab == reviewTab)
    {
        ui->textEdit->setHtml(currentData.getReview());
        updateSecondaryWindowsForCurrentBook(currentData);
    }
    else if (currentTab == quotesTab)
    {
        repaintQuoteView();
        updateSecondaryWindowsForCurrentBook(currentData);
    }
}

void MainWindow::showHiddenWidgets()
{
    if (!ui->tabWidget->isTabEnabled(0))
            ui->tabWidget->setTabEnabled(0, true);

    if (!ui->tabWidget->isTabEnabled(1))
             ui->tabWidget->setTabEnabled(1, true);

    if (!ui->editBtn->isEnabled())
          ui->editBtn->setEnabled(true);

    if (!ui->deleteButton->isEnabled())
         ui->deleteButton->setEnabled(true);

    if (!ui->widget_3->isEnabled())
        ui->widget_3->setEnabled(true);

    if (!ui->assesmentWidget->isVisible())
        ui->assesmentWidget->setVisible(true);

    if (!ui->labelPic->isVisible())
         ui->labelPic->setVisible(true);

}

QString MainWindow::getGenreById(int id)
{
    switch(id - 1)  //it's id from 1
    {
    case 0:
        return QString("Biographies");
    case 1:
        return QString("Autobiographies");
    case 2:
        return QString("Fantasy");
    case 3:
        return QString("Science");
    case 4:
        return QString("Horror");
    case 5:
        return QString("Romance");
    case 6:
        return QString("Action and Adventure");
    case 7:
        return QString("Drama");
    case 8:
        return QString("Science fiction");
    case 9:
        return QString("Psychology");
    case 10:
        return QString("Humor and Comedy");
    case 11:
        return QString("Historical Fiction");
    case 12:
        return QString("In foreign language");
    case 13:
        return QString("Computer Science");
    case 14:
        return QString("Classic literature");
    case 15:
        return QString("Fiction");

     default:
        return QString();

    }
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

        if (currentBookNumber == -1) //it means we haven't any current book yet
        {
            QMessageBox msgBox;
            msgBox.setText("you have not selected any books");
            msgBox.exec();

            currentTab = reviewTab;
            ui->tabWidget->setTabEnabled(1, false);
        }
        else
        {
            currentTab = quotesTab;
            int currentBookID =  getIDFromBookNumber(currentBookNumber);
            modelQuotes->removeRows(0, modelQuotes->rowCount());
            QList <Quote> lst = getListQuoteForBook(currentBookID);
            QStringList quotesBook = QListQuotesToQStringList(lst);
            modelQuotes->setStringList(quotesBook);
        }
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

void MainWindow::changeStyle(int type)
{
    switch (type) {
    case 0:
       this->setStyleSheet("");
        dialogAddEdit->setStyleSheet("");
        settingsWindow->setStyleSheet("");
        break;

    case 1:
    {

         this->setStyle(QStyleFactory::create("Fusion"));

        QFile File(":/styles/QTDark.css"); //QTDark
        if (File.open(QFile::ReadOnly))
        {
            QString StyleSheet = QLatin1String(File.readAll());
            this->setStyleSheet(StyleSheet);
            dialogAddEdit->setStyleSheet(StyleSheet);
            settingsWindow->setStyleSheet(StyleSheet);

        }
        else
        {
            qDebug() << "can't find style css";
        }
    }
        break;

    case 2:
    {

        QFile File(":/styles/black.css");
        if (File.open(QFile::ReadOnly))
        {
            QString StyleSheet = QLatin1String(File.readAll());
            this->setStyleSheet(StyleSheet);


            dialogAddEdit->setStyleSheet(StyleSheet);
            settingsWindow->setStyleSheet(StyleSheet);
        }
        else
        {
            qDebug() << "can't find style css";
        }
    }
        break;


    default:
        break;
    }

}

void MainWindow::searching()
{
    qDebug()<<"serching "<< ui->lineEdit->text();
    QString findStr = ui->lineEdit->text();

    QList<Data> dataList;


     qDebug() << "size " << dataListMain.length();

    foreach (Data data, dataListMain) {
    if (data.getBookTitle().toLower().contains(findStr))
        dataList.append(data);
    }

    fillMainWinFromDataBase(dataList);

}

void MainWindow::sort(int sortValue)
{
    qDebug() << "sort "<< sortValue;

    switch (sortValue) {
    case 0:
        //modelTitle->sort(1, Qt::AscendingOrder);
        getAllBooksFromDB();

        break;
    case 1:
        modelTitle->sort(0, Qt::AscendingOrder);
        break;
    case 2:

    default:
        break;
    }


}


void MainWindow::editModeStart()
{
     currentMode = edit;

     if (currentTab == reviewTab)
     {
              QModelIndexList currentsBooksIndex = ui->titlelistView->selectionModel()->selectedIndexes();

              qDebug() <<"INDEX:  "<< currentsBooksIndex;

              if (!currentsBooksIndex.isEmpty())
              {

                  QMap<int, QVariant> map = modelTitle->itemData(currentsBooksIndex.at(0));

                  QVariant titleBook = map[0].toString();
                  Data currentData = findBookByTitle(titleBook.toString());

                  if (currentData.getIsEmpty())
                  {
                      QMessageBox msgBox;
                      msgBox.setText("Please choose book for edit in list");
                      msgBox.exec();
                  }
                  else
                  {
                      //Data currentData = dataListMain.at(currentBook - 1);
                      dialogAddEdit->setGenre(genreList);
                      dialogAddEdit->viewDataForEdit(currentData);
                      dialogAddEdit->show();
                  }
              }
              else
              {
                  QMessageBox msgBox;
                  msgBox.setText("Please choose book for edit in list");
                  msgBox.exec();
              }
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
        dialogAddEdit->setGenre(genreList);
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

        QModelIndexList currentsBooksIndex = ui->titlelistView->selectionModel()->selectedIndexes();

        if (currentsBooksIndex.isEmpty())
        {
            QMessageBox msgBox;
            msgBox.setText("Please choose book for delete in list");
            msgBox.exec();
        }
        else
        {
            QMap<int, QVariant> map = modelTitle->itemData(currentsBooksIndex.at(0));
            QVariant titleBook = map[0].toString();
            Data currentData = findBookByTitle(titleBook.toString());

            QMessageBox msgBox;
            msgBox.setText("Warning! You are going to delete book " + titleBook.toString());
            msgBox.setInformativeText("Do you really want it?");
            msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
            int ret = msgBox.exec();

            switch (ret) {
            case QMessageBox::Yes:
                qDebug() <<  deleteBookFromDB(currentData.getId());

                getAllBooksFromDB();    //we need update after edit

                guiSettings();
                // updateSecondaryWindowsForCurrentBook(currentBook);
                // repaintReviewForCurrentBook(currentBook);  //focus on last added

                break;
            case QMessageBox::Cancel:
                break;
            default:
                break;
            }
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
