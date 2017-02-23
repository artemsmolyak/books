#include "quote.h"

int Quote::getIdQuote() const
{
    return idQuote;
}

void Quote::setIdQuote(int value)
{
    idQuote = value;
}

int Quote::getIdBook() const
{
    return idBook;
}

void Quote::setIdBook(int value)
{
    idBook = value;
}

QString Quote::getQuoteString() const
{
    return quoteString;
}

void Quote::setQuoteString(const QString &value)
{
    quoteString = value;
}

Quote::Quote(int idQuote, QString quoteString, int idBook):
    idQuote(idQuote), idBook(idBook), quoteString(quoteString)
{

}
