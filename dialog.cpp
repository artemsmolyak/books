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

void Dialog::setEditMode(Data data)
{
    mode = Mode::edit;

    ui->dateEdit->setText(data.getDate());
    ui->authorEdit->setText(data.getAuthorName());
    ui->assesEdit->setText(data.getAssessment());
    ui->bookCoverLbl->setPixmap(data.getBookCoverPixmap());
    ui->titleEdit->setText(data.getBookTitle());
    ui->reviewEdit->setText(data.getReview());
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
