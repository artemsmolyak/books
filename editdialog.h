#ifndef EDITDIALOG_H
#define EDITDIALOG_H
#include "QDialog"
#include <QObject>
#include "QComboBox"
#include "QDateEdit"
#include "data.h"
#include "assesment.h"
#include "QPlainTextEdit"

enum Mode {
    add,
    edit
};


class EditDialog : public QDialog
{
     Q_OBJECT

private:
    Mode mode;

    QPushButton * picButton;
    QComboBox * genreCombobox;
    QDateEdit * dateStart;
    QDateEdit * dateFinish;
    QSize minSizePic;
    Assesment * rate;
    QLineEdit * authorText;
    QLineEdit * mainIdeaText;
    QLineEdit * titleText;
    QLineEdit * numberOfPagesText;
    QLineEdit * tagsText;
    QPlainTextEdit * reviewText;


public:
    EditDialog();
    void setGenre(QList<QString> listGenre);
    void setStartDate();
    void setFinishDate();
    void setPicDefault();
    void reset();

public slots:
    void actionBold();
    void actionCenter();
    void actionItalic();
    void actionJustify();
    void actionLeft();
    void actionRigth();
    void actionUnder();

    void addBookPic();

    void getNewItem(Data data);
    void editItem(Data data);

    void on_SaveButton_released();

  signals:
    void newItemIsReady(Data data);
    void editItemIsReady(Data data);

};

#endif // EDITDIALOG_H
