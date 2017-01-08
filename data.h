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

};

#endif // DATA_H
