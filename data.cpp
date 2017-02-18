#include "data.h"
#include "qstringlist.h"
#include "QDebug"

int Data::size = 0;


QString Data::getAuthorsName() const
{
    return authorsName;
}

void Data::setAuthorsName(const QString &value)
{
    authorsName = value;
}

QString Data::getBookTitle() const
{
    return bookTitle;
}

void Data::setBookTitle(const QString &value)
{
    bookTitle = value;
}

QDate Data::getDateS() const
{
    return dateS;
}

QDate Data::getDateF() const
{
    return dateF;
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


QPixmap Data::getBookCoverPixmap() const
{
    return bookCoverPixmap;
}

void Data::setBookCoverPixmap(const QPixmap &value)
{
    bookCoverPixmap = value;
}

void Data::setDateS(const QDate &value)
{
    dateS = value;
}

void Data::setDateF(const QDate &value)
{
    dateF = value;
}

//QString bookTitle;
//QString authorsName;
//QString mainIdea;
//QStringList tagsList;

//QDate dateS;
//QDate dateF;
//QString review;
//QPixmap bookCoverPixmap;
//int rateInt;
//int genre;
//int pages;
//qint32 id;


QString Data::getMainIdea() const
{
    return mainIdea;
}

void Data::setMainIdea(const QString &value)
{
    mainIdea = value;
}

int Data::getRateInt() const
{
    return rateInt;
}

void Data::setRateInt(int value)
{
    rateInt = value;
}

int Data::getGenre() const
{
    return genre;
}

void Data::setGenre(int value)
{
    genre = value;
}

int Data::getPages() const
{
    return pages;
}

void Data::setPages(int value)
{
    pages = value;
}

QStringList Data::getTagsList() const
{
    return tagsList;
}

void Data::setTagsList(const QStringList &value)
{
    tagsList = value;
}

Data::Data(QString title, QString authors, QString mainIdea, int rateInt,
           int genre, int pages, QDate dateS, QDate dateF, QStringList tagsList,
           QString review, QPixmap bookCoverPixmap):
  bookTitle(title), authorsName(authors), mainIdea(mainIdea), rateInt(rateInt),
  genre(genre), pages(pages), dateS(dateS), dateF(dateF), tagsList(tagsList),
  review(review), bookCoverPixmap(bookCoverPixmap)
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
    return QString(authorsName + " " +
                   bookTitle + " " +
                   mainIdea  + " " +
                   rateInt + " " +
                   genre + " " +
                   pages + " " +
                   dateS.toString("dd.MM.yyyy") + " " +
                   dateF.toString("dd.MM.yyyy") + " " +
                   //tagsList.toStdList() + " " +
                   review);
}

QStringList Data::toQStringList()
{
    QStringList h;

   return h;
}
