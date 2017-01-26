#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QString"
#include "QXmlStreamWriter"
#include "QDebug"
#include "QFile"
#include "QPixmap"
#include "QSortFilterProxyModel"
#include "QStringListModel"
#include "dialog.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Window) //, dialog(new Dialog)
{
    ui->setupUi(this);
    dialog = new Dialog();
    guiSettings();
    //connect(this->ui->,  SIGNAL(clicked(bool)), this, SLOT(saveXml()));

    connect(dialog, SIGNAL(newItemIsReady(Data)), this, SLOT(getNewItem(Data)));
    connect(this, SIGNAL(hideDialog()), dialog, SLOT(hide()));
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

bool MainWindow::readXml()
{
    qDebug() << "reading";

    QFile in(path);
    if(!in.open(QFile::ReadOnly | QFile::Text))
    {
      qDebug() << "file not open";
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


//                QString assessment;
//                QString authorName;
//                QString bookTitle;
//                QString date;
//                QString annotation;


                QString assesment = reader.attributes().value("assesment").toString();
                QString authorName = reader.attributes().value("author").toString();
                QString bookTitle =  reader.attributes().value("name").toString();
                QString date = reader.attributes().value("date").toString();
                QString  review = reader.attributes().value("annotation").toString();
                //QString imageQString = reader.attributes().value("picture").toString();

//                QByteArray text;
//                text.fromBase64()
//                QPixmap::from

                Data tmpData(assesment, authorName, bookTitle,
                             date,  review);

                dataList.append(tmpData);
                dataStringList.append(tmpData.toString());

            }
        }


        reader.readNext();

        qDebug() <<"text end "<< reader.text().toString();
    }


    updateDataList();


   return true;

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::saveXml()
{
    QFile xmlFile("://books.xml");
    if (!xmlFile.open(QIODevice::ReadWrite))
    {
        qDebug() << "file not open";
        return;
    }


    QXmlStreamWriter xml(&xmlFile);
    xml.setAutoFormatting(true);


    QString assessment = "ui->assesment->text()""";
    QString authorName = "ui->author->text()";
    QString bookName = "ui->name->text()";
    QString date = "ui->date->text()";
    QString annotation = "ui->annotation->toPlainText()";

    xml.writeStartDocument();
    xml.writeStartElement("books");

    xml.writeStartElement("book");
    xml.writeAttribute("assesment", assessment);
    xml.writeAttribute("author", authorName);
    xml.writeAttribute("name", bookName);
    xml.writeAttribute("date", date);
    xml.writeAttribute("annotation", annotation);
    xml.writeCharacters ("Student 1");
    xml.writeEndElement();

    xml.writeStartElement("book");
    xml.writeAttribute("assesment", "2");
    xml.writeAttribute("author", authorName);
    xml.writeAttribute("name", bookName);
    xml.writeAttribute("date", date);
    xml.writeAttribute("annotation", annotation);
    xml.writeCharacters ("Student 1");
    xml.writeEndElement();


    xml.writeStartElement("book");
    xml.writeAttribute("assesment", "3");
    xml.writeAttribute("author", authorName);
    xml.writeAttribute("name", bookName);
    xml.writeAttribute("date", date);
    xml.writeAttribute("annotation", annotation);
    xml.writeCharacters ("Student 1");
    xml.writeEndElement();

    xml.writeEndElement();
    xml.writeEndDocument();

    xmlFile.close();
    if (xmlFile.error())
    {
        qDebug() << "file error!";
        return;
    }

    qDebug() << "file is ok!";



}

void MainWindow::getNewItem(Data data)
{
    qDebug() << " getNewItem !!! " <<data.toString();


    int row = tableModel->rowCount(QModelIndex());
    tableModel->insertRows(row, 1);
    QModelIndex index = tableModel->index(row, 0);
    tableModel->setData(index, QVariant("!!!!"), 0);



//    dataModel->insertRows(row, 1);
//    dataModel->insertRows(row, 1);

//    QModelIndex index = dataModel->index(row);
//    dataModel->setData(index, QVariant("!!!!"));


//    for(QString str: dataStringList)
//        qDebug() << str;

    //updateDataList();
    emit hideDialog();
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

    for(int i = 0; i < 5; i++)
    {
        QModelIndex newIn  = tableModel->index(index.row(), i);

        QVariant QV = tableModel->data(newIn, Qt::DisplayRole);
        list << QV.toString();
    }

    ui->reviewtextEdit->document()->setPlainText(list.at(3));
    ui->additionalWin1->setText(list.at(4));
    ui->additionalWin2->setText(list.at(4));

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
