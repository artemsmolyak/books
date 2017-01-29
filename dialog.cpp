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
    connect(ui->okButton, SIGNAL(clicked(bool)), this, SLOT(workWithData()));
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
    mode = edit;
    setWindowTitle("Edit mode");

    qDebug() << "!" << data.getDate();

    ui->dateEdit->setText(data.getDate());
    ui->authorEdit->setText(data.getAuthorName());
    ui->assesEdit->setText(data.getAssessment());

    QPixmap pix = data.getBookCoverPixmap();
    pix = pix.scaled(ui->bookCoverLbl->width(),
                                ui->bookCoverLbl->height(), Qt::IgnoreAspectRatio);
    ui->bookCoverLbl->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->bookCoverLbl->setPixmap(pix);

    ui->titleEdit->setText(data.getBookTitle());
    ui->reviewEdit->setText(data.getReview());
}

void Dialog::setAddMode()
{
    mode = add;
    setWindowTitle("add new book");
    clearAllFields();
}

Dialog::~Dialog()
{
    qDebug() << "delete dialog";

    delete ui;
}

void Dialog::workWithData()
{
    qDebug() << "click";

    close();

    if (mode == add)
    {
        setWindowTitle("Add mode");

        QString assessment = ui->assesEdit->text();
        QString  author = ui->authorEdit->text();
        QString  title  = ui->titleEdit->text();
        QString   date = ui->dateEdit->text();
        QString  review = ui->reviewEdit->toPlainText();

        clearAllFields();

        emit newItemIsReady(Data(assessment, author, title,
                                 date, review, bookCoverPixmap));
    }
    else if (mode == edit)
    {
        QString assessment = ui->assesEdit->text();
        QString  author = ui->authorEdit->text();
        QString  title  = ui->titleEdit->text();
        QString   date = ui->dateEdit->text();
        QString  review = ui->reviewEdit->toPlainText();
        const QPixmap *bookCoverPix = ui->bookCoverLbl->pixmap();

         emit editItemIsReady(Data(assessment, author, title,
                                   date, review, *bookCoverPix));
    }

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
