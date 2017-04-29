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
    explicit SettingsWindow(QWidget * parent);

 signals:
    void saveXmlButtonClick();
    void  changeStyle(int);

public slots:
   void test();

};

#endif // SETTINGSWINDOW_H
