#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "data.h"

enum Mode {
    add,
    edit
};

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT
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
    Mode mode;
};

#endif // DIALOG_H
