#include "data.h"
#include "qstringlist.h"

Data::Data(QString assessment, QString authorName,
           QString bookTitle, QString date,
           QString annotation):
      assessment(assessment),
      authorName(authorName),
      bookTitle(bookTitle),
      date(date),
     annotation(annotation)
{


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
