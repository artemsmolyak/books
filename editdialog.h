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
    int idData;

    QString typePic;
    QPixmap pixmapPic;

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
    QTextEdit * reviewText;
    QFontComboBox * fontComboBox;


    //text editor
    //QTextDocument *m_doc;
//    int m_cursorPosition;
//    int m_selectionStart;
//    int m_selectionEnd;

     QAction * actionBold;
     QAction * actionCenter;
     QAction * actionItalic ;
     QAction * actionJustify;
     QAction * actionLeft ;
     QAction * actionRight;
     QAction * actionUnder;

public:
    explicit EditDialog();
    void setGenre(QHash<int, QString> genreHash);
    void setStartDate();
    void setFinishDate();
    void setPicDefault();
    void reset();

    void viewDataForEdit(Data data);

    QLineEdit *getMainIdeaText() const;
    void setMainIdeaText(QLineEdit *value);
    void clearAll();


    //
    void textBold();
    void textItalic();
    void textUnderline();
    void textAlign(QAction *a);
    void mergeFormatOnWordOrSelection(const QTextCharFormat &format);


public slots:
    void slotBold();
    void slotCenter();
    void slotItalic();
    void slotJustify();
    void slotLeft();
    void slotRigth();
    void slotUnder();
    void slotTextAlign(QAction *a);

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
