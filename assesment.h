#ifndef ASSESMENT_H
#define ASSESMENT_H

#include <QWidget>

namespace Ui {
class assesment;
}

class assesment : public QWidget
{
    Q_OBJECT

public:
    explicit assesment(QWidget *parent = 0);
    ~assesment();

protected:
    void mouseMoveEvent(QMouseEvent * me);

private:
    Ui::assesment *ui;
};

#endif // ASSESMENT_H
