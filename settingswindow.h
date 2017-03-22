#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include "QPushButton"
#include "QDialog"
#include <QObject>

class SettingsWindow : public QDialog
{
    Q_OBJECT

private:
    QPushButton * saveXmlButton;


public:
    SettingsWindow();

 signals:
    void saveXmlButtonClick();
    void  changeStyle(int);

public slots:
   void test();

};

#endif // SETTINGSWINDOW_H
