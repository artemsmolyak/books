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

QString Data::getAnnotation() const
{
    return annotation;
}

void Data::setAnnotation(const QString &value)
{
    annotation = value;
}

int Data::getId() const
{
    return id;
}

void Data::setId(int value)
{
    id = value;
}

Data::Data(QString assessment, QString authorName,
           QString bookTitle, QString date,
           QString annotation):
    assessment(assessment),
      authorName(authorName),
      bookTitle(bookTitle),
      date(date),
     annotation(annotation)
{
    qDebug() <<" size "<< size;
   id = size;
   size++;
}

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
                   annotation);
}

QStringList Data::toQStringList()
{
    QStringList h;

   return h;
}
