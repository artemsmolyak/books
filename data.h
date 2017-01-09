#ifndef DATA_H
#define DATA_H

#include "QString"


class Data
{

private:
    QString assessment;
    QString authorName;
    QString bookTitle;
    QString date;
    QString annotation;


public:
    Data( QString assessment,  QString authorName,
          QString bookTitle, QString date, QString annotation);

    QString toString();


    QStringList toQStringList();

};

#endif // DATA_H
