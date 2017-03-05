#include "assesment.h"
#include "ui_assesment.h"
#include <QDebug>
#include <QMouseEvent>
#include <QCursor>

Assesment::Assesment(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Assesment)
    , _isUseMouse(true)
    , _isEstimating(true)
    , _assesment(-1)

{
    ui->setupUi(this);
    setMouseTracking(true);
    ui->firstStar->setMouseTracking(true);
    ui->secondStar->setMouseTracking(true);
    ui->thirdStar->setMouseTracking(true);
    ui->fourthStar->setMouseTracking(true);
    ui->fifthStar->setMouseTracking(true);
}

Assesment::~Assesment()
{
    delete ui;
}

void Assesment::setAssesment(int assesment)
{
    switch (assesment) {
    case 0:
        fillStars(false, false, false, false, false);
        break;
    case 1:
        fillStars(true, false, false, false, false);
        break;
    case 2:
        fillStars(true, true, false, false, false);
        break;
    case 3:
        fillStars(true, true, true, false, false);
        break;
    case 4:
        fillStars(true, true, true, true, false);
        break;
    case 5:
        fillStars(true, true, true, true, true);
        break;
    default:
        fillStars(false, false, false, false, false);
        break;
    }
    _assesment = assesment;
}

int Assesment::getAssesment()
{
    return _assesment;
}

void Assesment::setUseMouse(bool isUse)
{
    _isUseMouse = isUse;
}

void Assesment::mousePressEvent(QMouseEvent *me)
{
    Q_UNUSED(me);
    if (_isEstimating == false || _isUseMouse == false) {
        return;
    }

    int x = (mapFromGlobal(QCursor().pos())).x();

    if (x < ui->firstStar->x()) {
       setAssesment(0);
    }
    else if (x >= ui->firstStar->x() && x < ui->secondStar->x()) {
       setAssesment(1);
    }
    else if (x >= ui->secondStar->x() && x < ui->thirdStar->x()) {
        setAssesment(2);
    }
    else if (x >= ui->thirdStar->x() && x < ui->fourthStar->x()) {
        setAssesment(3);
    }
    else if (x >= ui->fourthStar->x() && x < ui->fifthStar->x()) {
        setAssesment(4);
    }
    else if (x >= ui->fifthStar->x()) {
        setAssesment(5);
    }
}

//void Assesment::mousePressEvent(QMouseEvent *me)
//{
//    Q_UNUSED(me);
//    if (_isUseMouse) {
//        _isEstimating ? _isEstimating = false : _isEstimating = true;
//    }
//}

void Assesment::fillStars(bool isFillFirstStar, bool isFillSecondStar, bool isFillThirdStar, bool isFillFourthStar, bool isFillFifthStar)
{
    isFillFirstStar ?  ui->firstStar->setPixmap(QPixmap("://star_fill.png")) : ui->firstStar->setPixmap(QPixmap("://star_no_fill.png"));
    isFillSecondStar ? ui->secondStar->setPixmap(QPixmap("://star_fill.png")) : ui->secondStar->setPixmap(QPixmap("://star_no_fill.png"));
    isFillThirdStar ?  ui->thirdStar->setPixmap(QPixmap("://star_fill.png")) : ui->thirdStar->setPixmap(QPixmap("://star_no_fill.png"));
    isFillFourthStar ? ui->fourthStar->setPixmap(QPixmap("://star_fill.png")) : ui->fourthStar->setPixmap(QPixmap("://star_no_fill.png"));
    isFillFifthStar ?  ui->fifthStar->setPixmap(QPixmap("://star_fill.png")) : ui->fifthStar->setPixmap(QPixmap("://star_no_fill.png"));
}
