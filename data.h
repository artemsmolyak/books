#ifndef DATA_H
#define DATA_H

#include "QString"
#include "QObject"
#include "QPixmap"


class Data
{
    static int size;

private:

    QString assessment;
    QString authorName;
    QString bookTitle;
    QString date;
    QString review;
    QPixmap bookCoverPixmap;
    int id;


public:
    Data( QString assessment,  QString authorName,
          QString bookTitle, QString date, QString annotation, QPixmap bookCoverPixmap);
    Data( QString assessment,  QString authorName,
          QString bookTitle, QString date, QString annotation);

    Data();
    QString toString();


    QStringList toQStringList();

    QString getAssessment() const;
    void setAssessment(const QString &value);
    QString getAuthorName() const;
    void setAuthorName(const QString &value);
    QString getBookTitle() const;
    void setBookTitle(const QString &value);
    QString getDate() const;
    QString getReview() const;
    void setAnnotation(const QString &value);
    int getId() const;
    void setId(int value);
};
Q_DECLARE_METATYPE(Data);

//

#endif // DATA_H
