#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "data.h"


enum Mode
{
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
    void clearAllFields();
    void setEditMode(Data data);
    void setAddMode();
    ~Dialog();

private:
    Ui::Dialog *ui;
    QPixmap bookCoverPixmap;
    Mode mode;

signals:
    void newItemIsReady(Data data);
    void editItemIsReady(Data data);
    void testEmit(Data string);

public slots:
    void workWithData();
    void savePicture();

private slots:
    void on_cancelButton_released();
};

#endif // DIALOG_H
