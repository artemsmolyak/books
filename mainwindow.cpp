#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QString"
#include "QXmlStreamWriter"
#include "QDebug"
#include "QFile"
#include "dialog.h"
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



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Window)
{
    ui->setupUi(this);
    ui->assesmentWidget->setUseMouse(false);
    dialog = new Dialog(this);
    dialogAddEdit = new EditDialog;
    guiSettings();

    dbConnect();
    getInfFromDb();

//    connect(ui->addBtn, SIGNAL(clicked(bool)), dialog, SLOT(show()));
//    connect(ui->addBtn, SIGNAL(clicked(bool)), this, SLOT(addModeStart()));

    connect(ui->addBtn, SIGNAL(clicked(bool)), dialogAddEdit, SLOT(show()));
    connect(ui->addBtn, SIGNAL(clicked(bool)), this, SLOT(addModeStart()));


    connect(ui->editBtn, SIGNAL(clicked(bool)),  dialog, SLOT(show()));
    connect(ui->editBtn, SIGNAL(clicked(bool)), this, SLOT(editModeStart()));

//    connect(dialog, SIGNAL(newItemIsReady(Data)), this, SLOT(getNewItem(Data)));
//    connect(dialog, SIGNAL(editItemIsReady(Data)), this, SLOT(editItem(Data)));

    connect(dialogAddEdit, SIGNAL(newItemIsReady(Data)), this, SLOT(getNewItem(Data)));
    connect(dialogAddEdit, SIGNAL(editItemIsReady(Data)), this, SLOT(editItem(Data)));


    connect(ui->deleteButton, SIGNAL(clicked(bool)), this, SLOT(deleteItem()));


    connect(ui->titlelistView, SIGNAL(clicked(QModelIndex)), this, SLOT(chooseListIndex(QModelIndex)));

    //connect(ui->tableView, SIGNAL(clicked(QModelIndex)), this, SLOT(chooseListIndex(QModelIndex)));


//    readXml();
//    tableModel = new TableModel(dataList);
//    QSortFilterProxyModel * sortModel = new QSortFilterProxyModel(this);
//    sortModel->setSourceModel(tableModel);
//    sortModel->setFilterKeyColumn(0);
//    ui->tableView->setModel(sortModel);

    guiSettings();

    setChooseFirstColumn();
    //showMainInformation();



    //ui->tableView->resizeRowsToContents();
    setWindowIcon(QIcon("://bookPic.jpg"));

//    EditDialog * eDialog = new EditDialog;
//    eDialog->show();

}

void MainWindow::guiSettings()
{
    ui->sortComboBox->addItem("By title");
    ui->sortComboBox->addItem("By date read");


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
//    QStringList list;

//    for(int i = 0; i < tableModel->columnCount(QModelIndex()) - 1; i++)
//    {
//        QModelIndex newIn  = tableModel->index(0, i);
//        QVariant QV = tableModel->data(newIn, Qt::DisplayRole);
//        list << QV.toString();
//    }

//    ui->reviewtextEdit->document()->setPlainText(list.at(3));
//    ui->additionalWin2->setText(list.at(4));
//    ui->assesmentWidget->setAssesment((list.at(5)).toInt());

//    QModelIndex newIn  = tableModel->index(0, 6);
//    QVariant QV = tableModel->data(newIn, Qt::DisplayRole);
//    QPixmap pix = qvariant_cast<QPixmap>(QV);

//    if (pix.isNull())
//        ui->labelPic->setPixmap(QPixmap("://empty.png"));
//    else
//    {

//        qint32 widgetW = ui->labelPic->width();
//        qint32 widgetH = ui->labelPic->height();
//        qDebug() <<"!"<< widgetW << widgetH;
//        //pix = pix.scaled(widgetW, widgetH, Qt::KeepAspectRatio);
//        ui->labelPic->setPixmap(pix);
//        ui->labelPic->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
//    }

//    QModelIndex index = tableModel->index(0, 1);
//    ui->tableView->setCurrentIndex(index);
//    ui->tableView->setFocus();

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
//     ui->reviewtextEdit->setPlainText("read:" +
//                                      QString::number(dataStringList.length())
//                                      +" books"
//                                      + "\n average read speed:");
}

bool MainWindow::dbConnect()
{

    // initialize the database
     QSqlError err = initDb();


     //qDebug() << (createGenresTable()).text();
     //qDebug() << (createBookMainsTable()).text();
     //qDebug() << (createQuotesTable()).text();
     //qDebug() << (createTagsTable()).text();



qDebug() << "err " << err.text();

//    if (err.type() != QSqlError::NoError) {
//        showError(err);
//        return;
//    }

//    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
//    model->setTable("books");
}

void MainWindow::getInfFromDb()
{
    QSqlQuery query;

    //get in from books
    query.exec("SELECT * FROM books");
    qDebug() << "from db " <<query.size();

    //    ("create table IF not EXISTS books"
    //                                  "(id integer primary key, "
    //                                  "title varchar, "
    //                                  "authors varchar,"
    //                                  "mainIdea TEXT, "
    //                                  "rateInt integer, "
    //                                  "genreId integer, "
    //                                  "pages integer, "
    //                                  "dateS date, "
    //                                  "dateF date, "
    //                                  "tagsList TEXT, "
    //                                  "review TEXT, "
    //                                  "bookCoverPixmap BLOB, "


   QList <Data> dataList;

    while (query.next()) {
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

        Data data(title, authors, mainIdea, rateInt, genreId, pages,
                          dateS, dateF, tagsList, review, pic);

        dataList.append(data);
    }

    fillMainWinFromDataBase(dataList);


    qDebug() << " lenght: " << dataList.length();


//    query.exec("SELECT * FROM authors");
//    qDebug() << "from db " <<query.size();

//    while (query.next()) {
//        QString name = query.value(0).toString();
//        QString value2 = query.value(1).toString();
//        qDebug() << name << value2;
//    }

    query.exec("SELECT * FROM genres");

    QList <QString> listGenre;
    while (query.next()) {
        QString name = query.value(0).toString();
        QString value = query.value(1).toString();
             listGenre.append(value);
    }

    dialogAddEdit->setGenre(listGenre);

    dialogAddEdit->setStartDate();
    dialogAddEdit->setFinishDate();

    dialogAddEdit->setPicDefault();

    //ui->verticalLayout_3->

}

void MainWindow::fillMainWinFromDataBase(QList<Data> dataList)
{
    QStringList titleList;
    foreach (Data data, dataList) {
        titleList << data.getBookTitle();
    }

    QStringListModel* model = new QStringListModel();
    model->setStringList(titleList);

    ui->titlelistView->setModel(model);
    //ui->listView->
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

    return q.lastError();
}

QSqlError MainWindow::createBookMainsTable()
{
    QSqlQuery q;


//    QString title = data.getBookTitle();
//    QString authors = data.getAuthorsName();
//    QString mainIdea = data.getMainIdea();
//    int rateInt = data.getRateInt();
//    int genre = data.getGenre();
//    int pages = data.getPages();
//    QDate dateS = data.getDateS();
//    QDate dateF = data.getDateF();
//    QStringList tagsList = data.getTagsList();
//    QString  review = data.getReview();
//    QPixmap bookCoverPixmap = data.getBookCoverPixmap();



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
                              "FOREIGN KEY(genreId) REFERENCES genres(id))")))
        return q.lastError();
}

QSqlError MainWindow::createQuotesTable()
{
    QSqlQuery q;

    if (!q.exec(QLatin1String("create table if not exists quotes"
                              "(id integer primary key,"
                              "text varchar,"
                              "idBooks integer, "
                              "FOREIGN KEY(idBooks) REFERENCES books(id))")))
        return q.lastError();


        q.prepare(QLatin1String("insert into quotes "
                               "(text, idBooks)"
                               "values(?, ?)"));


       QVariant id = addQuotes(q,
                             QLatin1String("quotes gsdfklgj dkl"),
                             1);

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


        q.prepare(QLatin1String("insert into tags "
                               "(text, idBooks)"
                               "values(?, ?)"));


       QVariant id = addQuotes(q,
                             "Человеку не нужно трех сосен, "
                              "чтобы заблудиться, — "
                              "ему достаточно двух существительных.",
                             1);

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


//    ("create table IF not EXISTS books"
//                                  "(id integer primary key, "
//                                  "title varchar, "
//                                  "authors varchar,"
//                                  "mainIdea TEXT, "
//                                  "rateInt integer, "
//                                  "genreId integer, "
//                                  "pages integer, "
//                                  "dateS date, "
//                                  "dateF date, "
//                                  "tagsList TEXT, "
//                                  "review TEXT, "
//                                  "bookCoverPixmap BLOB, "
//                                  "FOREIGN KEY(genreId) REFERENCES genres(id))")))


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
    bookCoverPixmap.save(&inBuffer);


//QImageReader reader;
//QByteArray nameArray = reader.format();
//QString picFormat = QString::fromLatin1(nameArray.data());


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

void MainWindow::getNewItem(Data data)
{
    qDebug() << " getNewItem !!! " <<data.toString();

    saveItemInDatabase(data);




  /*  int row = tableModel->rowCount(QModelIndex());
    tableModel->insertRows(row, 1);


    QModelIndex index = tableModel->index(row, 0);

    QVariant variant  = QVariant::fromValue(data);

    tableModel->setData(index, variant, Qt::EditRole);


    saveXml();

    emit hideDialog();


    //db


    QSqlQuery q;
    q.prepare(QLatin1String("insert into books "
                            "(title, author, genreId, date, review, assesment)"
                            "values(?, ?, ?, ?, ?, ?)"));


    QVariant id = addItem(q,
                          data.getBookTitle(),                //title
                          data.getAuthorName(),                    //author
                          1,                                          // "genre,"
                          QDate(2012, 12, 12),                        //"data,"
                          data.getReview(),    //"review, "
                          data.getAssessment().toInt());      */                                    // "assesment, ) "

    //return q.lastError();
}

void MainWindow::updateDataList()
{
//    ui->listWidget->clear();

//    for(Data data : dataList)
//    {
//        ui->listWidget->addItem(data.toString());
//    }
}

void MainWindow::testSlot(Data mes)
{
    qDebug() << "test Slot " << mes.toString();
}

void MainWindow::chooseListIndex(QModelIndex index)
{
    qDebug() << "here" <<index.row() << index.column();

//    QStringList list;

//    for(int i = 0; i < tableModel->columnCount(index) - 1; i++)
//    {
//        QModelIndex newIn  = tableModel->index(index.row(), i);

//        QVariant QV = tableModel->data(newIn, Qt::DisplayRole);
//        list << QV.toString();
//    }

//    ui->reviewtextEdit->document()->setPlainText(list.at(3));
//    QString digit = list.at(5);
//    ui->assesmentWidget->setAssesment(digit.toInt());
//    ui->additionalWin2->setText(list.at(4));


//    QModelIndex newIn  = tableModel->index(index.row(), 6);

//    QVariant QV = tableModel->data(newIn, Qt::DisplayRole);

//    QPixmap pix = qvariant_cast<QPixmap>(QV);

// if (pix.isNull())
//        ui->labelPic->setPixmap(QPixmap("://empty.png"));
//    else
//    {

//        qint32 widgetW = ui->labelPic->width();
//        qint32 widgetH = ui->labelPic->height();

//        pix = pix.scaled(widgetW, widgetH, Qt::KeepAspectRatio);
//        ui->labelPic->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
//        ui->labelPic->setPixmap(pix);
//    }

}


void MainWindow::on_addButton_released()
{
    dialog->reset();
    dialog->show();
}

void MainWindow::on_deleteButton_released()
{

}

void MainWindow::on_updateButton_released()
{

}


void MainWindow::editModeStart()
{
    qDebug() << "edit mode";

//    QModelIndexList indexLst = ui->tableView->selectionModel()->selectedIndexes();

//    indexEdit = indexLst.at(0);

//    qDebug() <<" IND "<< indexLst.at(0).row();
//    Data data;

//    QModelIndex newIn  = tableModel->index(indexEdit.row(), 0);
//    QVariant QV = tableModel->data(newIn, Qt::DisplayRole);
//    data.setId(qvariant_cast<qint32>(QV));

//    newIn  = tableModel->index(indexEdit.row(), 1);
//    QV = tableModel->data(newIn, Qt::DisplayRole);
//    data.setBookTitle(qvariant_cast<QString>(QV));

//    newIn  = tableModel->index(indexEdit.row(), 2);
//    QV = tableModel->data(newIn, Qt::DisplayRole);
//    data.setAuthorName(qvariant_cast<QString>(QV));

//    newIn  = tableModel->index(indexEdit.row(), 3);
//    QV = tableModel->data(newIn, Qt::DisplayRole);
//    data.setAnnotation(qvariant_cast<QString>(QV));


//    newIn  = tableModel->index(indexEdit.row(), 4);
//    QV = tableModel->data(newIn, Qt::DisplayRole);
//    data.setDate(qvariant_cast<QString>(QV));

//    newIn  = tableModel->index(indexEdit.row(), 5);
//    QV = tableModel->data(newIn, Qt::DisplayRole);
//    data.setAssessment(qvariant_cast<QString>(QV));

//    newIn  = tableModel->index(indexEdit.row(), 6);
//    QV = tableModel->data(newIn, Qt::DisplayRole);
//    data.setBookCoverPixmap(qvariant_cast<QPixmap>(QV));

//    dialog->setEditMode(data);
}

void MainWindow::addModeStart()
{
    dialog->setAddMode();
}

void MainWindow::editItem(Data data)
{
    QVariant variant  = QVariant::fromValue(data);

    tableModel->setData(indexEdit, variant, Qt::EditRole);

    saveXml();

    //emit
}

void MainWindow::deleteItem()
{
//    QModelIndexList indexLst = ui->tableView->selectionModel()->selectedIndexes();
//    QModelIndex indexEdit = indexLst.at(0);

//    QMessageBox msgBox;
//    msgBox.setText("Warning! You are going to delete line " + QString::number(indexEdit.row() - 1));
//    msgBox.setInformativeText("Do you really want it?");
//    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
//    int ret = msgBox.exec();

//    switch (ret) {
//    case QMessageBox::Yes:
//        qDebug()<< "index for delete " << indexEdit;
//        tableModel->removeRows(indexEdit.row(), 1, indexEdit);
//        saveXml();
//        break;
//    case QMessageBox::Cancel:
//        break;
//    default:
//        break;
//    }


}
