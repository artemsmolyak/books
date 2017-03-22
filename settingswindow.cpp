#include "settingswindow.h"
#include "QLabel"
#include "QPushButton"
#include "QLineEdit"
#include "QGridLayout"
#include "QDebug"
#include "QDir"


SettingsWindow::SettingsWindow()
{

    QLabel * labelDatabasePath = new QLabel("Database path: ");
    QLabel * dbPathLabel = new QLabel(QDir::homePath() + "/books.sqlite");


//    QPushButton * setDBPath = new QPushButton("set BD path");
//    setDBPath->setEnabled(false);

    QLabel * labelXmlPath = new QLabel("Xml path: ");
    QLabel * xmlPathLabel = new QLabel(QDir::homePath() + "/books.xml");

    saveXmlButton = new QPushButton("Save xml");

    QLabel * searchEngine = new QLabel("Search Engine: ");
    QLabel * searchEngineLabel = new QLabel("Bing Image Search");



    QLabel * syncURL = new QLabel("URL for sync: ");
    QLabel * syncURLLabel = new QLabel("www.");


    QPushButton * okBtn = new QPushButton("Close");


    QGridLayout * gridLayout  = new QGridLayout();
    gridLayout->addWidget(labelDatabasePath, 0, 0, 1, 1);
    gridLayout->addWidget(dbPathLabel, 0, 1, 1, 2);


    gridLayout->addWidget(labelXmlPath, 1, 0, 1, 1);
    gridLayout->addWidget(xmlPathLabel, 1, 1, 1, 2);
    gridLayout->addWidget(saveXmlButton, 1, 3, 1, 1);


    gridLayout->addWidget(searchEngine, 2, 0, 1, 1);
    gridLayout->addWidget(searchEngineLabel, 2, 1, 1, 2);


    gridLayout->addWidget(syncURL, 3, 0, 1, 1);
    gridLayout->addWidget(syncURLLabel, 3, 1, 1, 2);

    gridLayout->addWidget(okBtn, 5, 3, 1, 1);

    setLayout(gridLayout);

    connect(saveXmlButton, SIGNAL(clicked(bool)), this, SIGNAL(saveXmlButtonClick()));
    connect(saveXmlButton, SIGNAL(clicked(bool)), this, SLOT(test()));
    connect(okBtn, SIGNAL(clicked(bool)), this, SLOT(close()));
}

void SettingsWindow::test()
{
    qDebug() <<"save";
}
