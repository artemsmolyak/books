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
    ui->assesmentWidget->setUseMouse(true);
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::setEditMode(Data data)
{
    mode = edit;
    setWindowTitle("Edit mode");

    qDebug() << "!" << data.getDate();

    ui->dateEdit->setText(data.getDate());
    ui->authorEdit->setText(data.getAuthorName());
    //ui->assesEdit->setText(data.getAssessment());

    QPixmap pix = data.getBookCoverPixmap();
    pix = pix.scaled(ui->bookCoverLabel->width(),
                                ui->bookCoverLabel->height(), Qt::IgnoreAspectRatio);
    ui->bookCoverLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->bookCoverLabel->setPixmap(pix);

    ui->titleEdit->setText(data.getBookTitle());
    ui->reviewEdit->setText(data.getReview());
}

void Dialog::setAddMode()
{
    mode = add;
    setWindowTitle("add new book");
    reset();
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


void Dialog::workWithData()
{
    qDebug() << "click";

    close();

    if (mode == add)
    {
        setWindowTitle("Add mode");

        QString assessment = "";//ui->assesEdit->text();
        QString  author = ui->authorEdit->text();
        QString  title  = ui->titleEdit->text();
        QString   date = ui->dateEdit->text();
        QString  review = ui->reviewEdit->toPlainText();

        reset();

        emit newItemIsReady(Data(assessment, author, title,
                                 date, review, bookCoverPixmap));
    }
    else if (mode == edit)
    {
        QString assessment = "";//ui->assesEdit->text();
        QString  author = ui->authorEdit->text();
        QString  title  = ui->titleEdit->text();
        QString   date = ui->dateEdit->text();
        QString  review = ui->reviewEdit->toPlainText();
        const QPixmap *bookCoverPix = ui->bookCoverLabel->pixmap();

         emit editItemIsReady(Data(assessment, author, title,
                                   date, review, *bookCoverPix));
    }

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
