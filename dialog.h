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
    void clearAllFields();
    ~Dialog();

private:
    Ui::Dialog *ui;
    QPixmap bookCoverPixmap;

signals:
    void newItemIsReady(Data data);
    void testEmit(Data string);

public slots:
    void addNewItem();
    void savePicture();

private slots:
    void on_cancelButton_released();
};

#endif // DIALOG_H
