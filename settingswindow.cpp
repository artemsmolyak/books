#include "settingswindow.h"
#include "QLabel"
#include "QPushButton"
#include "QLineEdit"
#include "QGridLayout"
#include "QDebug"
#include "QDir"
#include "QComboBox"


SettingsWindow::SettingsWindow(QWidget *parent):QDialog(parent)
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


    QLabel * stylesLabel = new QLabel("Style: ");
    QComboBox * stylesCombobox = new QComboBox();
    stylesCombobox->addItem("light");
    stylesCombobox->addItem("dark");
    stylesCombobox->addItem("dark2");



    QLabel * version = new QLabel("Version: ");
    QLabel * versionLabel = new QLabel("1.0");

    QLabel * author = new QLabel("You can email to author: ");
    QLabel * email = new QLabel("osckyg@mail.ru");

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


    gridLayout->addWidget(stylesLabel, 4, 0, 1, 1);
    gridLayout->addWidget(stylesCombobox, 4, 1, 1, 2);


    gridLayout->addWidget(version, 5, 0, 1, 1);
    gridLayout->addWidget(versionLabel, 5, 1, 1, 2);


    gridLayout->addWidget(author, 6, 0, 1, 1);
    gridLayout->addWidget(email, 6, 1, 1, 2);

    gridLayout->addWidget(okBtn, 7, 3, 1, 1);

    setLayout(gridLayout);

    connect(saveXmlButton, SIGNAL(clicked(bool)), this, SIGNAL(saveXmlButtonClick()));
    connect(saveXmlButton, SIGNAL(clicked(bool)), this, SLOT(test()));
    connect(okBtn, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(stylesCombobox, SIGNAL(currentIndexChanged(int)), this, SIGNAL(changeStyle(int)));

}

void SettingsWindow::test()
{
    qDebug() <<"save";
}
