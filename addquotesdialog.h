#ifndef ADDQUOTESDIALOG_H
#define ADDQUOTESDIALOG_H
#include "QDialog"
#include "QString"
#include "QTextEdit"


class AddQuotesDialog : public QDialog
{
    Q_OBJECT

private:
     QTextEdit * quote;

public:
    explicit AddQuotesDialog();


signals:
   void saveQuoteSignal(QString);


public slots:
   void saveQuoteSlot();


};

#endif // ADDQUOTESDIALOG_H
