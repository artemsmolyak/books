#ifndef DATA_H
#define DATA_H

#include "QString"
#include "QObject"
#include "QPixmap"
#include "QDate"

class Data
{
    static int size;

private:
    QString bookTitle;
    QString assessment;
    QString authorsName;
    QString mainIdea;
    QStringList tagsList;

    QDate dateS;
    QDate dateF;
    QString review;
    QPixmap bookCoverPixmap;
    int rateInt;
    int genre;
    int pages;
    qint32 id;


public:

    Data(QString title, QString authors, QString mainIdea,  int rateInt, int genre,
         int pages, QDate dateS, QDate dateF, QStringList tagsList, QString  review);

    Data(QString assessment,  QString authorName,
          QString bookTitle, QString date, QString annotation,
          QPixmap bookCoverPixmap);

    Data(qint32 id, QString assessment,  QString authorName,
          QString bookTitle, QString date, QString annotation,
          QPixmap bookCoverPixmap);

    Data();

    QString toString();

    QStringList toQStringList();

    QString getAssessment() const;
    void setAssessment(const QString &value);
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
};
Q_DECLARE_METATYPE(Data);

//

#endif // DATA_H
