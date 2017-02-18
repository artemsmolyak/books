#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "data.h"
#include "QTextCursor"


//enum Mode {
//    add,
//    edit
//};

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

 //   Q_PROPERTY(bool bold READ bold WRITE setBold NOTIFY boldChanged)
//    Q_PROPERTY(bool italic READ italic WRITE setItalic NOTIFY italicChanged)
//    Q_PROPERTY(bool underline READ underline WRITE setUnderline NOTIFY underlineChanged)
//    Q_PROPERTY(int fontSize READ fontSize WRITE setFontSize NOTIFY fontSizeChanged)
//    Q_PROPERTY(QStringList defaultFontSizes READ defaultFontSizes NOTIFY defaultFontSizesChanged)


    bool bold() const;
//    bool italic() const;
//    bool underline() const;
//    int fontSize() const;
//    QStringList defaultFontSizes() const;



public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

    void setEditMode(Data data);
    void setAddMode();
    void reset();

signals:
    void newItemIsReady(Data data);
    void editItemIsReady(Data data);

private slots:
    void on_cancelButton_released();
    void on_okButton_released();
    void on_changeBookCoverButton_released();

private:
    Ui::Dialog *ui;
    QPixmap bookCoverPixmap;
    //Mode mode;

    //QQuickItem *m_target;
    QTextCursor textCursor() const;

    QTextDocument *m_doc;
    int m_cursorPosition;
    int m_selectionStart;
    int m_selectionEnd;
};

#endif // DIALOG_H
