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
    ui->assesmentWidget->setUseMouse(true);
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
    ui->assesmentWidget->setAssesment(0);
    ui->bookCoverLabel->setPixmap(QPixmap("://empty.png"));
    ui->reviewEdit->clear();
}

void Dialog::savePicture()
{
    QString str = QFileDialog::getOpenFileName(0, "Open Dialog", "/", "*.png");
    qDebug() << "выбран файл "<< str;
    bookCoverPixmap = QPixmap(str).scaled(ui->bookCoverLabel->size(), Qt::KeepAspectRatio);
    ui->bookCoverLabel->setPixmap(bookCoverPixmap);
}

void Dialog::on_cancelButton_released()
{
    this->hide();
    this->reset();
}

void Dialog::on_okButton_released()
{
    QString assessment = QString::number(ui->assesmentWidget->getAssesment());
    QString author = ui->authorEdit->text();
    QString title  = ui->titleEdit->text();
    QString date = ui->dateEdit->text();
    QString review = ui->reviewEdit->toPlainText();

    emit newItemIsReady(Data(assessment, author, title, date, review, bookCoverPixmap));
    this->hide();
    this->reset();
}
