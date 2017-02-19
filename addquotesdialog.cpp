#include "addquotesdialog.h"
#include "QGridLayout"
#include "QTextEdit"
#include "QPushButton"


AddQuotesDialog::AddQuotesDialog()
{

    QGridLayout * layout = new  QGridLayout;

    QTextEdit * text = new QTextEdit;

    QPushButton * saveBtn =new QPushButton("save");
    QPushButton * cancelBtn = new QPushButton("cancel");


    layout->addWidget(text, 0, 0, 1, 2);
    layout->addWidget(saveBtn, 1, 0, 1, 1);
    layout->addWidget(cancelBtn, 1, 1, 1, 1);

   setLayout(layout);
}
