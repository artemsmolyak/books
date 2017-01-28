#include "dialog.h"
#include "ui_dialog.h"
#include "QDebug"
#include "QFileDialog"
#include "QBuffer"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    //connect(ui->buttonBox, SIGNAL(clicked(QAbstractButton*)), this, SLOT(addNewItem()));
    //connect(ui->okButton, SIGNAL(clicked(bool)), SLOT(close()));
    connect(ui->okButton, SIGNAL(clicked(bool)), this, SLOT(addNewItem()));

    connect(ui->changeBookCoverButton, SIGNAL(clicked(bool)), SLOT(savePicture()));


}

void Dialog::clearAllFields()
{
    ui->dateEdit->clear();
    ui->authorEdit->clear();
    ui->assesEdit->clear();
    ui->bookCoverLbl->clear();
    ui->titleEdit->clear();
    ui->reviewEdit->clear();
}

Dialog::~Dialog()
{
    qDebug() << "delete dialog";

    delete ui;
}

void Dialog::addNewItem()
{
    qDebug() << "click";

    close();

    QString assessment = ui->assesEdit->text();
    QString  author = ui->authorEdit->text();
    QString  title  = ui->titleEdit->text();
    QString   date = ui->dateEdit->text();
    QString  review = ui->reviewEdit->toPlainText();

    clearAllFields();

    qDebug() << "bookCoverPixmap size " << bookCoverPixmap.size();

//    QByteArray bArray;
//    QBuffer buffer(&bArray);
//    buffer.open(QIODevice::WriteOnly);
//    bookCoverPixmap.save(&buffer, "PNG");

//    qDebug() <<"buf "<< buffer.size();
//    QString photoString(bArray.toBase64());

//    qDebug() << "!!in add new Item ";
//    qDebug() << "!in add new Item " << photoString.length();
  //  qDebug() << "in add new Item " << photoString; //<< photoString.size();

    emit newItemIsReady(Data(assessment, author, title,
                             date, review, bookCoverPixmap));
}

void Dialog::savePicture()
{
    QString str = QFileDialog::getOpenFileName(0, "Open Dialog", "/", "*.png");
    qDebug() << "выбран файл "<< str;
    bookCoverPixmap = QPixmap(str);
    ui->bookCoverLbl->setPixmap(bookCoverPixmap);
}



void Dialog::on_cancelButton_released()
{
    this->hide();
}
