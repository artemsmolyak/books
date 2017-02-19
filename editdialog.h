#ifndef EDITDIALOG_H
#define EDITDIALOG_H
#include "QDialog"
#include <QObject>
#include "QComboBox"
#include "QDateEdit"
#include "data.h"
#include "assesment.h"
#include "QPlainTextEdit"
#include "QFontComboBox"


enum Mode {
    add,
    edit
};


class EditDialog : public QDialog
{
     Q_OBJECT

private:
    Mode mode;

    QString typePic;
    QPixmap *pixmapPic;

    QPushButton * picButton;
    QComboBox * genreCombobox;
    QDateEdit * dateStart;
    QDateEdit * dateFinish;
    QSize minSizePic;
    Assesment * rate;
    QLineEdit * authorsText;
    QLineEdit * mainIdeaText;
    QLineEdit * titleText;
    QLineEdit * numberOfPagesText;
    QLineEdit * tagsText;
    QPlainTextEdit * reviewText;
    QFontComboBox * fontComboBox;


public:
    explicit EditDialog();
    void setGenre(QHash<int, QString> genreHash);
    void setStartDate();
    void setFinishDate();
    void setPicDefault();
    void reset();

    QLineEdit *getMainIdeaText() const;
    void setMainIdeaText(QLineEdit *value);


public slots:
    void actionBold();
    void actionCenter();
    void actionItalic();
    void actionJustify();
    void actionLeft();
    void actionRigth();
    void actionUnder();

    void addBookPic();
    QString getFileType(QString pathFilePic);

    void getNewItem(Data data);
    void editItem(Data data);

    void on_SaveButton_released();

  signals:
    void newItemIsReady(Data data);
    void editItemIsReady(Data data);

};

#endif // EDITDIALOG_H
