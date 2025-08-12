/******************************************************************
Copyright © Deng Zhimao Co., Ltd. 1990-2021. All rights reserved.
* @projectName   NumberPicker
* @brief         numberpicker.cpp
* @author        Deng Zhimao
* @email         1252699831@qq.com
* @net           www.openedv.com
* @date          2021-05-14
*******************************************************************/
#include <QMouseEvent>
#include <QDebug>
#include "numberpicker.h"
#include <QPainter>

NumberPicker::NumberPicker(QWidget *parent) :
    /* 最小值默认为0 */
    minRange(0),

    /* 最大值默认60 */
    maxRange(60),

    /* 当前值默认0 */
    currentValue(0),

    /* 按下标志位为假 */
    isDragging(false),

    /* 默认偏移量为0 */
    deviation(0),

    /* 数值越大 */
    numSize(15),

    /* 间隔为1 */
    interval(1),

    /* 默认分成3格 */
    devide(3),

    /* 默认颜色黑色 */
    numberColor(0, 0, 0)
{
    setParent(parent);
    setMinimumSize(50, 150);
    homingAni = new QPropertyAnimation(this, "deviation");
    homingAni->setDuration(300);
    homingAni->setEasingCurve(QEasingCurve::OutQuad);
}

NumberPicker::~NumberPicker()
{

}

void NumberPicker::setRange(int min, int max)
{
    minRange = min;
    maxRange = max;
    if (currentValue < min) {
        currentValue = min;
    }
    if (currentValue > max) {
        currentValue = max;
    }
    repaint();
}

int NumberPicker::readValue()
{
    return currentValue;
}

void NumberPicker::mousePressEvent(QMouseEvent *e)
{
    homingAni->stop();
    isDragging = true;
    mouseSrcPos = e->pos().y();
    QWidget::mousePressEvent(e);
}

void NumberPicker::mouseMoveEvent(QMouseEvent *e)
{
    if (isDragging){
        deviation = e->pos().y() - mouseSrcPos;

        /* 若移动速度过快，则进行限制 */
        if (deviation > (height() - 1) / devide) {
            deviation = (height() - 1) / devide;
        } else if (deviation < -(height() - 1) / devide) {
            deviation = -( height() - 1) / devide;
        }

        emit deviationChange(deviation / ((height() - 1) / devide));
        repaint();
    }
}

void NumberPicker::mouseReleaseEvent(QMouseEvent *)
{
    if (isDragging) {
        isDragging = false;
        homing();
    }
}

void NumberPicker::wheelEvent(QWheelEvent *e)
{
    if (e->delta() > 0) {
        deviation = (this->height() - 1) / devide;
    } else {
        deviation = -(this->height() - 1) / devide;
    }

    homing();
    repaint();
}

void NumberPicker::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    int Height = height() - 1;

    if (deviation >= Height / devide && currentValue > minRange ) {
        mouseSrcPos += Height / devide;
        deviation -= Height / devide;
        currentValue -= interval;
        /* 负数处理 */
        if (currentValue < 0)
            currentValue = maxRange + currentValue;
    }

    if (deviation <= -Height / devide && currentValue < maxRange ) {
        mouseSrcPos -= Height / devide;
        deviation += Height / devide;
        currentValue += interval;
    }

    if (qAbs(int(currentValue)) >= int(maxRange))
        currentValue = minRange;

    paintNum(painter, qAbs(int(currentValue + maxRange) % maxRange),
             deviation);

    paintNum(painter,
             qAbs((currentValue - interval + maxRange) % maxRange),
             deviation - Height / devide);

    paintNum(painter,
             qAbs((currentValue + interval + maxRange) % maxRange),
             deviation + Height / devide);

    for (int i = 2; i <= devide / 2; ++i) {
        if (qAbs(currentValue - interval * i) >= minRange) {
            paintNum(painter,
                     qAbs((currentValue - interval * i + maxRange)
                          % maxRange),
                     deviation - Height / devide * i);
        }

        if (qAbs(currentValue + interval * i) <= maxRange) {
            paintNum(painter,
                     qAbs((currentValue + interval * i + maxRange)
                          % maxRange),
                     deviation + Height / devide * i);
        }
    }
}

void NumberPicker::paintNum(QPainter &painter, int num, int deviation)
{
    int Width = width() - 1;
    int Height = height() - 1;

    /* 偏移量越大，数字越小 */
    //int size = (Height - qAbs(deviation)) / numSize;
    int size = (Height - qAbs(deviation)) * numSize / 80;
    int transparency = 255 - 255 * qAbs(deviation) / Height;
    int height = Height / devide;
    int y = Height / 2 + deviation - height / 2;

    QFont font;
    font.setPixelSize(size);
    painter.setFont(font);
    painter.setPen(QColor(numberColor.red(),
                          numberColor.green(),
                          numberColor.blue(),
                          transparency));

    if ( y >= 0 && y + height < Height) {
        //painter.drawRect(0, y, Width, height);
        if (num < 10)
            painter.drawText(QRectF(0, y, Width, height),
                             Qt::AlignCenter,
                             "0" + QString::number(num, 'f', 0));
        else
            painter.drawText(QRectF(0, y, Width, height),
                             Qt::AlignCenter,
                             QString::number(num, 'f', 0));
    }
}

void NumberPicker::homing()
{
    if (deviation > height() / 10) {
        homingAni->setStartValue((height() - 1 ) / 8 - deviation);
        homingAni->setEndValue(0);
        currentValue -= interval;
    } else if (deviation > -height() / 10) {
        homingAni->setStartValue(deviation);
        homingAni->setEndValue(0);
    } else if (deviation < -height() / 10) {
        homingAni->setStartValue(-(height() - 1) / 8 - deviation);
        homingAni->setEndValue(0);
        currentValue += interval;
    }

    emit currentValueChanged(currentValue);
    homingAni->start();
}

int NumberPicker::readDeviation()
{
    return deviation;
}

void NumberPicker::setDeviation(int n)
{
    deviation = n;
    repaint();
}

void NumberPicker::setNumSize(int size)
{
    numSize = size;
    repaint();
}

void NumberPicker::setInterval(int n)
{
    interval = n;
    repaint();
}

void NumberPicker::setDevide(int n)
{
    devide = n;
    repaint();
}

void NumberPicker::setNumberColor(QRgb rgb)
{
    numberColor.setRgb(rgb);
    repaint();
}

void NumberPicker::setValue(int value)
{
    if (value < minRange || value > maxRange) {
        qDebug()<<"数值设置必须在"<<minRange
               <<"和"<<maxRange<<"之间"<<endl;
        return;
    }
    currentValue = value;
    repaint();
}
