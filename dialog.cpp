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

    emit newItemIsReady(Data(assessment, author, title, date, review, bookCoverPixmap));
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
