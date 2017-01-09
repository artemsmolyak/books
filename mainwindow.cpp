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


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Window) //, dialog(new Dialog)
{

    Dialog * dialog = new Dialog();

    ui->setupUi(this);
    guiSettings();

    //connect(this->ui->,  SIGNAL(clicked(bool)), this, SLOT(saveXml()));

    connect(ui->addBtn, SIGNAL(clicked(bool)), dialog, SLOT(show()));
    connect(dialog, SIGNAL(newItemIsReady(Data)), this, SLOT(getNewItem(Data)));
    connect(this, SIGNAL(hideDialog()), dialog, SLOT(hide()));

    ui->labelPic->setPixmap(QPixmap("C:\\Users\\Artyom\\Documents\\books\\resource\\empty.png"));

            //saveXml();
    readXml();

    dataModel = new QStringListModel(this);
    dataModel->setStringList(dataStringList);

    QSortFilterProxyModel * sortModel = new QSortFilterProxyModel(this);
    sortModel->setSourceModel(dataModel);
    sortModel->setFilterKeyColumn(0);

    ui->listView->setModel(sortModel);




}

void MainWindow::guiSettings()
{
    ui->sortComboBox->addItem("По автору");
    ui->sortComboBox->addItem("По названию");
    ui->sortComboBox->addItem("По дате прочтения");
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
                QString  annotation = reader.attributes().value("annotation").toString();

                Data tmpData(assesment, authorName, bookTitle, date, annotation);

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
    QFile xmlFile("C:\\Users\\Artyom\\Documents\\books\\books.xml");
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
    qDebug() << " getNewItem !!! ";
    dataList.append(data);
    updateDataList();

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
