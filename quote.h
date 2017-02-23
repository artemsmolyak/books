#ifndef QUOTE_H
#define QUOTE_H
#include "QString"

class Quote
{
private:
    int idQuote;
    int idBook;
    QString quoteString;


public:
    Quote(int, QString, int);
    int getIdQuote() const;
    void setIdQuote(int value);
    int getIdBook() const;
    void setIdBook(int value);
    QString getQuoteString() const;
    void setQuoteString(const QString &value);
};

#endif // QUOTE_H
