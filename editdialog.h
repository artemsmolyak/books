#ifndef EDITDIALOG_H
#define EDITDIALOG_H
#include "QDialog"
#include <QObject>

class EditDialog : public QDialog
{
     Q_OBJECT

private:
    QPushButton * picButton;

public:
    EditDialog();


public slots:
    void actionBold();
    void actionCenter();
    void actionItalic();
    void actionJustify();
    void actionLeft();
    void actionRigth();
    void actionUnder();

    void addBookPic();
};

#endif // EDITDIALOG_H
