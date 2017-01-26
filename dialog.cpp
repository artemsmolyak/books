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
    connect(ui->changeBookCoverButton, SIGNAL(clicked(bool)), SLOT(savePicture()));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::reset()
{
    ui->dateEdit->clear();
    ui->titleEdit->clear();
    ui->authorEdit->clear();
    ui->assesEdit->clear();
    ui->bookCoverLbl->setPixmap(QPixmap("://empty.png"));
    ui->reviewEdit->clear();
}

void Dialog::savePicture()
{
    QString str = QFileDialog::getOpenFileName(0, "Open Dialog", "/", "*.bmp *.png *.jpg");
    qDebug() << "выбран файл "<< str;
    bookCoverPixmap = QPixmap(str).scaled(ui->bookCoverLbl->size(), Qt::KeepAspectRatio);
    ui->bookCoverLbl->setPixmap(bookCoverPixmap);
}

void Dialog::on_cancelButton_released()
{
    this->hide();
}

void Dialog::on_okButton_released()
{
    QString assessment = ui->assesEdit->text();
    QString author = ui->authorEdit->text();
    QString title  = ui->titleEdit->text();
    QString date = ui->dateEdit->text();
    QString review = ui->reviewEdit->toPlainText();

    emit newItemIsReady(Data(assessment, author, title, date, review, bookCoverPixmap));
}
