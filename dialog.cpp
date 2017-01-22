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
    connect(ui->okButton, SIGNAL(clicked(bool)), this, SLOT(addNewItem()));
    connect(ui->changeBookCoverButton, SIGNAL(clicked(bool)), SLOT(savePicture()));


}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::addNewItem()
{
    qDebug() << "click";

    QString assessment = ui->assesEdit->text();
    QString  author = ui->authorEdit->text();
    QString  title  = ui->titleEdit->text();
    QString   date = ui->dateEdit->text();
    QString  review = ui->reviewEdit->toPlainText();

    qDebug() << "bookCoverPixmap size " << bookCoverPixmap.size();

    QByteArray bArray;
    QBuffer buffer(&bArray);
    buffer.open(QIODevice::WriteOnly);
    bookCoverPixmap.save(&buffer, "PNG");

    qDebug() <<"buf "<< buffer.size();
    QString photoString(bArray.toBase64());

    qDebug() << "!!in add new Item ";
    qDebug() << "!in add new Item " << photoString.length();
  //  qDebug() << "in add new Item " << photoString; //<< photoString.size();

    emit newItemIsReady(Data(assessment, author, title,
                             date, review, bookCoverPixmap, photoString));
}

void Dialog::savePicture()
{
    QString str = QFileDialog::getOpenFileName(0, "Open Dialog", "/", "*.bmp *.png *.jpg");
    qDebug() << "выбран файл "<< str;
    bookCoverPixmap = QPixmap(str);
    ui->bookCoverLbl->setPixmap(bookCoverPixmap);
}



void Dialog::on_cancelButton_released()
{
    this->hide();
}
