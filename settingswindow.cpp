#include "settingswindow.h"
#include "QLabel"
#include "QPushButton"
#include "QLineEdit"
#include "QGridLayout"
#include "QDebug"


SettingsWindow::SettingsWindow()
{

    QLabel * labelDatabasePath = new QLabel("database: ");
    QLineEdit * dbPathEdit = new QLineEdit();
    QPushButton * setDBPath = new QPushButton("set BD path");


    QLabel * labelXmlPath = new QLabel("xml: ");
    QLineEdit * xmlPathEdit = new QLineEdit();
    QPushButton * setXMLPath = new QPushButton("set xml path");

    saveXmlButton = new QPushButton("save xml");


    QPushButton * drobAllTables = new QPushButton("drop all tables");


    QGridLayout * gridLayout  = new QGridLayout();
    gridLayout->addWidget(labelDatabasePath, 0, 0, 1, 1);
    gridLayout->addWidget(dbPathEdit, 0, 1, 1, 1);
    gridLayout->addWidget(setDBPath, 0, 2, 1, 2);

    gridLayout->addWidget(labelXmlPath, 1, 0, 1, 1);
//    gridLayout->addWidget(xmlPathEdit, 1, 1, 1, 1);
//    gridLayout->addWidget(setXMLPath, 1, 2, 1, 1);
    gridLayout->addWidget(saveXmlButton, 1, 3, 1, 1);


    gridLayout->addWidget(drobAllTables, 2, 3, 1, 1);

    setLayout(gridLayout);

    connect(saveXmlButton, SIGNAL(clicked(bool)), this, SIGNAL(saveXmlButtonClick()));
    connect(saveXmlButton, SIGNAL(clicked(bool)), this, SLOT(test()));
}

void SettingsWindow::test()
{
    qDebug() <<"save";
}
