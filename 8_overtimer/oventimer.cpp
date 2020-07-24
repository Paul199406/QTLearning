#include <QDateTime>
#include <QMouseEvent>
#include <QPainter>
#include <QTimer>
#include <cmath>
#include <QDebug>

#ifndef M_PI
#define M_PI 3.14159265359
#endif

#include "oventimer.h"

const double DegreesPerMinute = 7.0;
const double DegreesPerSecond = DegreesPerMinute / 60;
const int MaxMinutes = 45;
const int MaxSeconds = MaxMinutes * 60;
const int UpdateInterval = 5;

OvenTimer::OvenTimer(QWidget *parent)
    : QWidget(parent)
{
    finishTime = QDateTime::currentDateTime();

    updateTimer = new QTimer(this);//用来每隔5秒刷新窗口部件的外观
    connect(updateTimer, SIGNAL(timeout()), this, SLOT(update()));

    finishTimer = new QTimer(this);//在定时器到0时发射timeout()信号
    finishTimer->setSingleShot(true);//只需要执行一次
    connect(finishTimer, SIGNAL(timeout()), this, SIGNAL(timeout()));
    connect(finishTimer, SIGNAL(timeout()), updateTimer, SLOT(stop()));//定时器停止工作时停止更新窗口部件

    QFont font;
    font.setPointSize(8);//设置字体为8磅
    setFont(font);
}

//设置烤箱定时器的时间为给定秒数
void OvenTimer::setDuration(int secs)
{
    secs = qBound(0, secs, MaxSeconds);

    //保存日期和时间，避免了凌晨12点之前并且完成时间在下一天而产生的折回缺陷
    finishTime = QDateTime::currentDateTime().addSecs(secs);

    if (secs > 0) {
        updateTimer->start(UpdateInterval * 1000);//更新绘图的间隔
        finishTimer->start(secs * 1000);//完成时间
    } else {
        updateTimer->stop();
        finishTimer->stop();
    }
    update();//调用update，用新的间隔时间重绘窗口部件
}

//返回定时器完成前剩余的秒数
int OvenTimer::duration() const
{

    int secs = QDateTime::currentDateTime().secsTo(finishTime);
    if (secs < 0)
        secs = 0;
    return secs;
}

//当用户点击窗口部件时，即设置定制时间
void OvenTimer::mousePressEvent(QMouseEvent *event)
{
    QPointF point = event->pos() - rect().center();
    double theta = std::atan2(-point.x(), -point.y()) * 180.0 / M_PI;
    setDuration(duration() + int(theta / DegreesPerSecond));//设置新的持续时间
    update();//重绘
}

void OvenTimer::paintEvent(QPaintEvent * /* event */)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    int side = qMin(width(), height());

    //设置视口为窗口部件中最大的正方形：如果没有设置视口为正方形，则窗口部件被缩放为
    //非正方形的矩形时，烤箱定时器就会变成椭圆。为了避免这种变形，必须把视口和窗口
    //设置为具有相同纵横比的矩形
    painter.setViewport((width() - side) / 2, (height() - side) / 2,
                        side, side);
    //设置窗口为（-50，-50，100，100）
    painter.setWindow(-50, -50, 100, 100);

    draw(&painter);
}

void OvenTimer::draw(QPainter *painter)
{
    static const int triangle[3][2] = {
        { -2, -49 }, { +2, -49 }, { 0, -47 }
    };
    QPen thickPen(palette().foreground(), 1.5);
    QPen thinPen(palette().foreground(), 0.5);
    QColor niceBlue(150, 150, 200);

    painter->setPen(thinPen);
    painter->setBrush(palette().foreground());
    painter->drawPolygon(QPolygon(3, &triangle[0][0]));

    QConicalGradient coneGradient(0, 0, -90.0);
    coneGradient.setColorAt(0.0, Qt::darkGray);
    coneGradient.setColorAt(0.2, niceBlue);
    coneGradient.setColorAt(0.5, Qt::white);
    coneGradient.setColorAt(1.0, Qt::darkGray);

    painter->setBrush(coneGradient);
    painter->drawEllipse(-46, -46, 92, 92);

    QRadialGradient haloGradient(0, 0, 20, 0, 0);
    haloGradient.setColorAt(0.0, Qt::lightGray);
    haloGradient.setColorAt(0.8, Qt::darkGray);
    haloGradient.setColorAt(0.9, Qt::white);
    haloGradient.setColorAt(1.0, Qt::black);

    painter->setPen(Qt::NoPen);
    painter->setBrush(haloGradient);
    painter->drawEllipse(-20, -20, 40, 40);

    QLinearGradient knobGradient(-7, -25, 7, -25);
    knobGradient.setColorAt(0.0, Qt::black);
    knobGradient.setColorAt(0.2, niceBlue);
    knobGradient.setColorAt(0.3, Qt::lightGray);
    knobGradient.setColorAt(0.8, Qt::white);
    knobGradient.setColorAt(1.0, Qt::black);

    painter->rotate(duration() * DegreesPerSecond);
    painter->setBrush(knobGradient);
    painter->setPen(thinPen);
    painter->drawRoundRect(-7, -25, 14, 50, 99, 49);

    for (int i = 0; i <= MaxMinutes; ++i) {
        if (i % 5 == 0) {
            painter->setPen(thickPen);
            painter->drawLine(0, -41, 0, -44);
            painter->drawText(-15, -41, 30, 30,
                              Qt::AlignHCenter | Qt::AlignTop,
                              QString::number(i));
        } else {
            painter->setPen(thinPen);
            painter->drawLine(0, -42, 0, -44);
        }
        painter->rotate(-DegreesPerMinute);
    }
}
