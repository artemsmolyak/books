#include "data.h"
#include "qstringlist.h"
#include "QDebug"

int Data::size = 0;

QString Data::getAssessment() const
{
    return assessment;
}

void Data::setAssessment(const QString &value)
{
    assessment = value;
}

QString Data::getAuthorName() const
{
    return authorName;
}

void Data::setAuthorName(const QString &value)
{
    authorName = value;
}

QString Data::getBookTitle() const
{
    return bookTitle;
}

void Data::setBookTitle(const QString &value)
{
    bookTitle = value;
}

QString Data::getDate() const
{
    return date;
}

QString Data::getReview() const
{
    return review;
}

void Data::setAnnotation(const QString &value)
{
    review = value;
}

int Data::getId() const
{
    return id;
}

void Data::setId(int value)
{
    id = value;
}

//Data::Data(QString assessment, QString authorName,
//           QString bookTitle, QString date,
//           QString annotation):
//      assessment(assessment),
//      authorName(authorName),
//      bookTitle(bookTitle),
//      date(date),
//      review(annotation)
//{
//    qDebug() <<" size "<< size;
//   id = size;
//   size++;
//}







QPixmap Data::getBookCoverPixmap() const
{
    return bookCoverPixmap;
}

void Data::setBookCoverPixmap(const QPixmap &value)
{
    bookCoverPixmap = value;
}

void Data::setDate(const QString &value)
{
    date = value;
}

Data::Data(QString assessment, QString authorName,
           QString bookTitle, QString date,
           QString annotation, QPixmap bookCoverPixmap):
      assessment(assessment),
      authorName(authorName),
      bookTitle(bookTitle),
      date(date),
      review(annotation),
      bookCoverPixmap(bookCoverPixmap)
{
    qDebug() <<" size "<< size;
    id = size;
    size++;
}

//Data::Data(QString assessment, QString authorName, QString bookTitle, QString date, QString annotation, QString bookCoverQString):
//assessment(assessment),
//authorName(authorName),
//bookTitle(bookTitle),
//date(date),
//review(annotation),
//bookCoverQString(bookCoverQString)
//{
//    qDebug() <<" size "<< size;
//    id = size;
//    size++;
//}

Data::Data()
{
   id = size;
   size++;
}

QString Data::toString()
{
    return QString(assessment + " " +
                   authorName + " " +
                   bookTitle + " " +
                   date + " +" +
                   review);
}

QStringList Data::toQStringList()
{
    QStringList h;

   return h;
}
