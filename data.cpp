#include "data.h"
#include "qstringlist.h"
#include "QDebug"


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

QString Data::getTypePic() const
{
    return typePic;
}

void Data::setTypePic(const QString &value)
{
    typePic = value;
}

QDate Data::getDateAdded() const
{
    return dateAdded;
}

void Data::setDateAdded(const QDate &value)
{
    dateAdded = value;
}

bool Data::getIsEmpty() const
{
    return isEmpty;
}

void Data::setIsEmpty(bool value)
{
    isEmpty = value;
}

Data::Data(int id, QString title, QString authors, QString mainIdea, int rateInt,
           int genre, int pages, QDate dateS, QDate dateF, QStringList tagsList,
           QString review, QPixmap bookCoverPixmap, QString typePic, QDate dateAdded):
  id(id), bookTitle(title), authorsName(authors), mainIdea(mainIdea), rateInt(rateInt),
  genre(genre), pages(pages), dateS(dateS), dateF(dateF), tagsList(tagsList),
  review(review), bookCoverPixmap(bookCoverPixmap), typePic(typePic), dateAdded(dateAdded)
{
    isEmpty = false;
}



Data::Data()
{
    isEmpty = true;
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
                   review);
}

