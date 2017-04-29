#ifndef DATA_H
#define DATA_H

#include "QString"
#include "QObject"
#include "QPixmap"
#include "QDate"

class Data
{
   // static int size;


private:
    QString bookTitle;
    QString authorsName;
    QString mainIdea;
    QStringList tagsList;

    QDate dateS;
    QDate dateF;
    QDate dateAdded;
    QString review;
    QPixmap bookCoverPixmap;
    QString typePic;

    int rateInt;
    int genre;
    int pages;
    int id;
    bool isEmpty;



public:

    Data(int id, QString title, QString authors, QString mainIdea,
         int rateInt, int genre, int pages,
         QDate dateS, QDate dateF,
         QStringList tagsList,
         QString  review, QPixmap bookCoverPixmap, QString typePic, QDate dateAdded);

    Data();

    QString toString();

    QString getAuthorsName() const;
    void setAuthorsName(const QString &value);
    QString getBookTitle() const;
    void setBookTitle(const QString &value);

    QDate getDateS() const;
    QDate getDateF() const;

    QString getReview() const;
    void setAnnotation(const QString &value);
    int getId() const;
    void setId(int value);
    QPixmap getBookCoverPixmap() const;
    void setBookCoverPixmap(const QPixmap &value);

    void setDateS(const QDate &value);
    void setDateF(const QDate &value);

    QString getMainIdea() const;
    void setMainIdea(const QString &value);
    int getRateInt() const;
    void setRateInt(int value);
    int getGenre() const;
    void setGenre(int value);
    int getPages() const;
    void setPages(int value);
    QStringList getTagsList() const;
    void setTagsList(const QStringList &value);
    QString getTypePic() const;
    void setTypePic(const QString &value);
    QDate getDateAdded() const;
    void setDateAdded(const QDate &value);
    bool getIsEmpty() const;
    void setIsEmpty(bool value);
};
Q_DECLARE_METATYPE(Data);

//

#endif // DATA_H
