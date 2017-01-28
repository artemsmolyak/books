#include "assesment.h"
#include "ui_assesment.h"
#include <QDebug>
#include <QMouseEvent>

assesment::assesment(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::assesment)
{
    ui->setupUi(this);
    setMouseTracking(true);
}

assesment::~assesment()
{
    delete ui;
}

void assesment::mouseMoveEvent(QMouseEvent *me)
{
    if (me->pos().x() < ui->firstStar->pos().x()) {
        ui->firstStar->setPixmap(QPixmap("://star_no_fill.png"));
        ui->secondStar->setPixmap(QPixmap("://star_no_fill.png"));
        ui->thirdStar->setPixmap(QPixmap("://star_no_fill.png"));
        ui->fourthStar->setPixmap(QPixmap("://star_no_fill.png"));
        ui->fifthStar->setPixmap(QPixmap("://star_no_fill.png"));
    }
    else if (me->pos().x() > ui->firstStar->pos().x() && me->pos().x() < ui->secondStar->pos().x()) {
        ui->firstStar->setPixmap(QPixmap("://star_fill.png"));
        ui->secondStar->setPixmap(QPixmap("://star_no_fill.png"));
        ui->thirdStar->setPixmap(QPixmap("://star_no_fill.png"));
        ui->fourthStar->setPixmap(QPixmap("://star_no_fill.png"));
        ui->fifthStar->setPixmap(QPixmap("://star_no_fill.png"));
        qDebug() << "First star";
    }
    else if (me->pos().x() > ui->secondStar->pos().x() && me->pos().x() < ui->thirdStar->pos().x()) {
        ui->firstStar->setPixmap(QPixmap("://star_fill.png"));
        ui->secondStar->setPixmap(QPixmap("://star_fill.png"));
        ui->thirdStar->setPixmap(QPixmap("://star_no_fill.png"));
        ui->fourthStar->setPixmap(QPixmap("://star_no_fill.png"));
        ui->fifthStar->setPixmap(QPixmap("://star_no_fill.png"));
        qDebug() << "Second star";
    }
    else if (me->pos().x() > ui->thirdStar->pos().x() && me->pos().x() < ui->fourthStar->pos().x()) {
        ui->firstStar->setPixmap(QPixmap("://star_fill.png"));
        ui->secondStar->setPixmap(QPixmap("://star_fill.png"));
        ui->thirdStar->setPixmap(QPixmap("://star_fill.png"));
        ui->fourthStar->setPixmap(QPixmap("://star_no_fill.png"));
        ui->fifthStar->setPixmap(QPixmap("://star_no_fill.png"));
        qDebug() << "Third star";
    }
    else if (me->pos().x() > ui->fourthStar->pos().x() && me->pos().x() < ui->fifthStar->pos().x()) {
        ui->firstStar->setPixmap(QPixmap("://star_fill.png"));
        ui->secondStar->setPixmap(QPixmap("://star_fill.png"));
        ui->thirdStar->setPixmap(QPixmap("://star_fill.png"));
        ui->fourthStar->setPixmap(QPixmap("://star_fill.png"));
        ui->fifthStar->setPixmap(QPixmap("://star_no_fill.png"));
        qDebug() << "Fourth star";
    }
    else if (me->pos().x() > ui->fifthStar->pos().x()) {
        ui->firstStar->setPixmap(QPixmap("://star_fill.png"));
        ui->secondStar->setPixmap(QPixmap("://star_fill.png"));
        ui->thirdStar->setPixmap(QPixmap("://star_fill.png"));
        ui->fourthStar->setPixmap(QPixmap("://star_fill.png"));
        ui->fifthStar->setPixmap(QPixmap("://star_fill.png"));
        qDebug() << "Fifth star";
    }

}
