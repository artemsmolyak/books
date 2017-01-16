#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "data.h"


namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private:
    Ui::Dialog *ui;

signals:
    void newItemIsReady(Data data);
    void testEmit(Data string);

public slots:
    void addNewItem();


private slots:
    void on_cancelButton_released();
};

#endif // DIALOG_H
