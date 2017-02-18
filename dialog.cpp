#include "dialog.h"
#include "ui_dialog.h"
#include "QDebug"
#include "QFileDialog"
#include "QBuffer"
#include "QTextCursor"

bool Dialog::bold() const
{
    QTextCursor cursor = textCursor();
    if (cursor.isNull())
        return false;
    return textCursor().charFormat().fontWeight() == QFont::Bold;
}

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog),
    m_doc(0)
{
    ui->setupUi(this);
    ui->assesmentWidget->setUseMouse(true);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::setEditMode(Data data)
{
    //mode = edit;
//    setWindowTitle("Edit mode");

//    qDebug() << "!" << data.getDate();

//    ui->dateEdit->setText(data.getDate());
//    ui->authorEdit->setText(data.getAuthorName());
//    ui->assesmentWidget->setAssesment(data.getAssessment().toInt());

//    QPixmap pix = data.getBookCoverPixmap();
//    pix = pix.scaled(ui->bookCoverLabel->width(),
//                               ui->bookCoverLabel->height(),  Qt::KeepAspectRatio);
//    ui->bookCoverLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
//    ui->bookCoverLabel->setPixmap(pix);

//    ui->titleEdit->setText(data.getBookTitle());
//    ui->reviewEdit->setText(data.getReview());
}

void Dialog::setAddMode()
{
    //mode = add;
    setWindowTitle("add new book");
    reset();
}

void Dialog::on_cancelButton_released()
{
    this->hide();
    this->reset();
}
void Dialog::on_okButton_released()
{
    //if (mode == add)
//    {
//        setWindowTitle("Add mode");
//        int rate =
//        QString  author = ui->authorEdit->text();
//        QString  title  = ui->titleEdit->text();
//        QString   date = ui->dateEdit->text();
//        QString  review = ui->reviewEdit->toPlainText();



//        emit newItemIsReady
//                   (
//                    Data(QString title, QString authors, QString mainIdea,  int rateInt, int genre,
//                         int pages, QDate dateS, QDate dateF, QStringList tagsList, QString  review);
//                    Data(assessment, author, title, date, review, bookCoverPixmap)
//                   );
//    }
    //else if (mode == edit)
//    {
//        QString assessment = QString::number(ui->assesmentWidget->getAssesment());
//        QString  author = ui->authorEdit->text();
//        QString  title  = ui->titleEdit->text();
//        QString   date = ui->dateEdit->text();
//        QString  review = ui->reviewEdit->toPlainText();
//        const QPixmap *bookCoverPix = ui->bookCoverLabel->pixmap();
//        emit editItemIsReady(Data(assessment, author, title, date, review, *bookCoverPix));
//    }
//    this->hide();
//    this->reset();
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

void Dialog::on_changeBookCoverButton_released()
{
    QString str = QFileDialog::getOpenFileName(0, "Open Dialog", "/", "*.png");
    qDebug() << "выбран файл "<< str;
    bookCoverPixmap = QPixmap(str).scaled(ui->bookCoverLabel->size(), Qt::KeepAspectRatio);
    ui->bookCoverLabel->setPixmap(bookCoverPixmap);
}

QTextCursor Dialog::textCursor() const
{
    if (!m_doc)
        return QTextCursor();

    QTextCursor cursor = QTextCursor(m_doc);
    if (m_selectionStart != m_selectionEnd) {
        cursor.setPosition(m_selectionStart);
        cursor.setPosition(m_selectionEnd, QTextCursor::KeepAnchor);
    } else {
        cursor.setPosition(m_cursorPosition);
    }
    return cursor;
}
