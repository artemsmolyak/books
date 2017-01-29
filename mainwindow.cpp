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
#include "dialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Window) //, dialog(new Dialog)
{
    ui->setupUi(this);
    dialog = new Dialog();
    guiSettings();
    connect(dialog, SIGNAL(newItemIsReady(Data)), this, SLOT(getNewItem(Data)));
    connect(ui->tableView, SIGNAL(clicked(QModelIndex)), this, SLOT(chooseListIndex(QModelIndex)));
    ui->labelPic->setPixmap(QPixmap("://empty.png"));
    readXml();

    tableModel = new TableModel(dataList);

    QSortFilterProxyModel * sortModel = new QSortFilterProxyModel(this);
    sortModel->setSourceModel(tableModel);
    sortModel->setFilterKeyColumn(0);

    ui->tableView->setModel(sortModel);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setColumnHidden(3, true);
    ui->tableView->setColumnHidden(4, true);

    ui->tableView->resizeRowsToContents();
}

void MainWindow::guiSettings()
{
    ui->sortComboBox->addItem("By author");
    ui->sortComboBox->addItem("By title");
    ui->sortComboBox->addItem("By id");
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
    qDebug() << "reading";

    QFile in(path);
    if(!in.open(QFile::ReadOnly | QFile::Text))
    {
      qDebug() << "file not open for read!";
      return false;
    }

    QXmlStreamReader reader;
    reader.setDevice(&in);
    //reader.readNext();
    while(!reader.atEnd() && !reader.error())
    {
        qDebug() <<"text start "<< reader.text().toString();

        QXmlStreamReader::TokenType token = reader.readNext();

        if(token == QXmlStreamReader::StartDocument) {
            qDebug() << "StartDoc";
            continue;
        }

        if(token == QXmlStreamReader::StartElement) {
            qDebug() << "StartReader";
            if(reader.name() == "book") {
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

                Data tmpData(assesment, authorName, bookTitle,
                             date,  review, pix);

                dataList.append(tmpData);
                dataStringList.append(tmpData.toString());

            }
        }

        reader.readNext();

        qDebug() <<"text end "<< reader.text().toString();
    }


    updateDataList();

    in.close();

   return true;

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::saveXml()
{
    QFile xmlFile("C:\\Users\\Artyom\\Documents\\books\\resource\\books.xml");   //

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


    QList <Data> datalst = tableModel->getList();

    for(int i = 0; i < datalst.length(); i++)
    {
        Data data = datalst.at(i);

        QString assessment = data.getAssessment();
        QString authorName = data.getAuthorName();
        QString bookTitle = data.getBookTitle();
        QString date = data.getDate();
        QString review = data.getReview();
        QPixmap bookPic = data.getBookCoverPixmap();
        QString bookCoverQString = convertQPixmapToQString(bookPic);
        qint32  id = data.getId();


        xml.writeStartElement("book");
        xml.writeAttribute("assesment", assessment);
        xml.writeAttribute("author", authorName);
        xml.writeAttribute("title", bookTitle);
        xml.writeAttribute("date", date);
        xml.writeAttribute("review", review);
        xml.writeAttribute("picture", bookCoverQString);
        xml.writeCharacters (QString::number(id));
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

}

void MainWindow::getNewItem(Data data)
{
    qDebug() << " getNewItem !!! " <<data.toString();


    int row = tableModel->rowCount(QModelIndex());
    tableModel->insertRows(row, 1);


    QModelIndex index = tableModel->index(row, 0);

    QVariant variant  = QVariant::fromValue(data);

    tableModel->setData(index, variant, Qt::EditRole);




    saveXml();


//    dataModel->insertRows(row, 1);
//    dataModel->insertRows(row, 1);

//    QModelIndex index = dataModel->index(row);
//    dataModel->setData(index, QVariant("!!!!"));


//    for(QString str: dataStringList)
//        qDebug() << str;

    //updateDataList();
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

    QStringList list;

    for(int i = 0; i < tableModel->columnCount(index) - 1; i++)
    {
        QModelIndex newIn  = tableModel->index(index.row(), i);

        QVariant QV = tableModel->data(newIn, Qt::DisplayRole);
        list << QV.toString();
    }

    ui->reviewtextEdit->document()->setPlainText(list.at(3));
    ui->additionalWin1->setText(list.at(5));
    ui->additionalWin2->setText(list.at(4));


    QModelIndex newIn  = tableModel->index(index.row(), 6);

    QVariant QV = tableModel->data(newIn, Qt::DisplayRole);

    QPixmap pix = qvariant_cast<QPixmap>(QV);

    //QString picQString = list.at(6);
//    QByteArray textByte =  QByteArray::fromBase64(picQString.toLocal8Bit());
//    QPixmap pix;
//    pix.loadFromData(textByte, "png");
//    qDebug() <<"pix size "<< pix.size();
    pix = pix.scaled(200, 200);
    ui->labelPic->setPixmap(pix);
    ui->labelPic->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

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
