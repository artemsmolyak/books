#include "addquotesdialog.h"
#include "QGridLayout"
#include "QTextEdit"
#include "QPushButton"


AddQuotesDialog::AddQuotesDialog()
{

    QGridLayout * layout = new  QGridLayout;

    quoteTextEdit = new QTextEdit;

    QPushButton * saveBtn =new QPushButton("save");
    QPushButton * cancelBtn = new QPushButton("cancel");


    layout->addWidget(quoteTextEdit, 0, 0, 1, 2);
    layout->addWidget(saveBtn, 1, 0, 1, 1);
    layout->addWidget(cancelBtn, 1, 1, 1, 1);

    setLayout(layout);

    connect(saveBtn, SIGNAL(clicked(bool)), this, SLOT(saveQuoteSlot()));
}

void AddQuotesDialog::viewData(QString quote)
{
    quoteTextEdit->setText(quote);
}

void AddQuotesDialog::saveQuoteSlot()
{
   hide();
   emit saveQuoteSignal(quoteTextEdit->toPlainText());
   quoteTextEdit->clear();
}
