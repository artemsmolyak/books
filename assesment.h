#ifndef ASSESMENT_H
#define ASSESMENT_H

#include <QWidget>

namespace Ui {
class Assesment;
}

class Assesment : public QWidget
{
    Q_OBJECT

public:
    explicit Assesment(QWidget *parent = 0);
    ~Assesment();

    void setAssesment(int assesment);
    void setUseMouse(bool isUse);

    int getAssesment();

protected:
    void mousePressEvent(QMouseEvent * me);   //mouseMoveEvent
    //void mousePressEvent(QMouseEvent * me);

private:
    void fillStars(bool isFillFirstStar, bool isFillSecondStar, bool isFillThirdStar, bool isFillFourthStar, bool isFillFifthStar);

private:
    Ui::Assesment *ui;
    bool _isUseMouse;
    bool _isEstimating;
    int _assesment;
};

#endif // ASSESMENT_H
