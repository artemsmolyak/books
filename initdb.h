#ifndef INITDB_H
#define INITDB_H

#include <QtSql>



//    ("create table IF not EXISTS books"
//                                  "(id integer primary key, "
//                                  "title varchar, "
//                                  "authors varchar,"
//                                  "mainIdea TEXT, "
//                                  "rateInt integer, "
//                                  "genreId integer, "
//                                  "pages integer, "
//                                  "dateS date, "
//                                  "dateF date, "
//                                  "tagsList TEXT, "
//                                  "review TEXT, "
//                                  "bookCoverPixmap BLOB, "


QVariant updateBook(QSqlQuery &q,
                    const QString &title,
                    const QString &authors,
                    const QString &mainIdea,
                    const int &rateInt,
                    const int &genreId,
                    const int &pages,
                    const QDate &dataS,
                    const QDate &dataF,
                    const QString &tagsList,
                    const QString &review,
                    const QByteArray &bookPicBuffer,
                    const int id)
{
    q.addBindValue(title);
    q.addBindValue(authors);
    q.addBindValue(mainIdea);
    q.addBindValue(rateInt);
    q.addBindValue(genreId);
    q.addBindValue(pages);
    q.addBindValue(dataS);
    q.addBindValue(dataF);
    q.addBindValue(tagsList);
    q.addBindValue(review);
    q.addBindValue(bookPicBuffer);
    q.addBindValue(id);

    q.exec();
    qDebug() <<"E: "<< q.lastError().text();
    return q.lastInsertId();

}



QVariant addItem(QSqlQuery &q,
                           const QString &title,
                           const QString &authors,
                           const QString &mainIdea,
                           const int &rateInt,
                           const int &genreId,
                           const int &pages,
                           const QDate &dataS,
                           const QDate &dataF,
                           const QString &tagsList,
                           const QString &review,
                           const QByteArray &bookPicBuffer)
{
    qDebug() << q.lastError().text();

    q.addBindValue(title);
    q.addBindValue(authors);
    q.addBindValue(mainIdea);
    q.addBindValue(rateInt);
    q.addBindValue(genreId);
    q.addBindValue(pages);
    q.addBindValue(dataS);
    q.addBindValue(dataF);
    q.addBindValue(tagsList);
    q.addBindValue(review);
    q.addBindValue(bookPicBuffer);

    q.exec();
    qDebug() <<"E: "<< q.lastError().text();
    return q.lastInsertId();
}

QVariant addGenre(QSqlQuery &q, const QString &name)
{
    q.addBindValue(name);
    q.exec();
    return q.lastInsertId();
}

QVariant addAuthor(QSqlQuery &q, const QString &name, const QDate &birthdate)
{
    q.addBindValue(name);
    q.addBindValue(birthdate);
    q.exec();
    return q.lastInsertId();
}


QVariant addQuote(QSqlQuery &q, const QString &quote, const int &idBooks)
{
    q.addBindValue(quote);
    q.addBindValue(idBooks);
    q.exec();
    return q.lastInsertId();
}



QSqlError initDb()
{
    QSqlDatabase db;

    if (!QSqlDatabase::drivers().contains("QSQLITE"))
    {
        QMessageBox::critical(0, "Unable to load database", "needs the SQLITE driver");
    }
    else
    {
        db = QSqlDatabase::addDatabase("QSQLITE");
        qDebug() << "connect!";
    }

     db.setDatabaseName(QDir::homePath()+"/books.sqlite");



    if (!db.open())
       {
          qDebug() << "Error: connection with database fail" << db.lastError();
       }
       else
       {
          qDebug() << "Database: connection ok";
       }






    QStringList tables = db.tables();


//    if (tables.contains("books", Qt::CaseInsensitive)
//        && tables.contains("authors", Qt::CaseInsensitive))
//        return QSqlError();

//    QSqlQuery q;


//    q.exec("drop table IF EXISTS books");
//    q.exec("drop table IF EXISTS authors");
//    q.exec("drop table IF EXISTS genres");

//    tables = db.tables();


    //  "pic BLOB, "



//    if (!q.exec(QLatin1String("create table authors"
//                              "(id integer primary key,"
//                              " name varchar,"
//                              " birthdate date)")))
//        return q.lastError();




//   tables = db.tables();


//    if (!q.prepare(QLatin1String("insert into authors "
//                                 "(name, birthdate) "
//                                 "values(?, ?)")))
//        return q.lastError();
//    QVariant asimovId = addAuthor(q, QLatin1String("Isaac Asimov"), QDate(1920, 2, 1));
//    QVariant greeneId = addAuthor(q, QLatin1String("Graham Greene"), QDate(1904, 10, 2));
//    QVariant pratchettId = addAuthor(q, QLatin1String("Terry Pratchett"), QDate(1948, 4, 28));



    //if (!


       // return q.lastError();


    //QImage img();






//    addItem(q, QLatin1String("Foundation and Empire"), 1952, asimovId, sfiction, 4);
//    addItem(q, QLatin1String("Second Foundation"), 1953, asimovId, sfiction, 3);
//    addBook(q, QLatin1String("Foundation's Edge"), 1982, asimovId, sfiction, 3);
//    addBook(q, QLatin1String("Foundation and Earth"), 1986, asimovId, sfiction, 4);
//    addBook(q, QLatin1String("Prelude to Foundation"), 1988, asimovId, sfiction, 3);
//    addBook(q, QLatin1String("Forward the Foundation"), 1993, asimovId, sfiction, 3);
//    addBook(q, QLatin1String("The Power and the Glory"), 1940, greeneId, fiction, 4);
//    addBook(q, QLatin1String("The Third Man"), 1950, greeneId, fiction, 5);
//    addBook(q, QLatin1String("Our Man in Havana"), 1958, greeneId, fiction, 4);
//    addBook(q, QLatin1String("Guards! Guards!"), 1989, pratchettId, fantasy, 3);
//    addBook(q, QLatin1String("Night Watch"), 2002, pratchettId, fantasy, 3);
//    addBook(q, QLatin1String("Going Postal"), 2004, pratchettId, fantasy, 3);





    return QSqlError();
}





#endif // INITDB_H
