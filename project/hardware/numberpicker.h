/******************************************************************
Copyright © Deng Zhimao Co., Ltd. 1990-2021. All rights reserved.
* @projectName   NumberPicker
* @brief         numberpicker.h
* @author        Deng Zhimao
* @email         1252699831@qq.com
* @net           www.openedv.com
* @date          2021-05-14
*******************************************************************/
#ifndef NUMBERPICKER_H
#define NUMBERPICKER_H

#include <QMainWindow>
#include <QPropertyAnimation>

class NumberPicker : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(int deviation READ readDeviation WRITE setDeviation )
public:
    NumberPicker(QWidget *parent = nullptr);
    ~NumberPicker();

    /* 设置最大值与最小值的范围 */
    void setRange(int min, int max);

    /* 读取当前值 */
    int readValue();

protected:
    void mousePressEvent(QMouseEvent *);

    void mouseMoveEvent(QMouseEvent *);

    void mouseReleaseEvent(QMouseEvent *);

    void wheelEvent(QWheelEvent *);

    void paintEvent(QPaintEvent *);

public:
    /* 描绘数字 */
    void paintNum(QPainter &painter, int num, int deviation);

    /* 使选中的数字回到屏幕中间 */
    void homing();

    /* 鼠标移动偏移量，默认为0 */
    int readDeviation();

    /* 设置偏移量 */
    void setDeviation(int n);

    /* 设置字体大小 */
    void setNumSize(int);

    /* 设置间隔大小 */
    void setInterval(int);

    /* 设置分格数量，一般设置为3、5、7... */
    void setDevide(int);

    /* 设置数字颜色,设置rgb的数值 */
    void setNumberColor(QRgb rgb);

    /* 设置当前值 */
    void setValue(int value);

signals:

    void currentValueChanged(int value);

    void deviationChange(int deviation);

private:
    /* 最小值 */
    int minRange;

    /* 最大值 */
    int maxRange;

    /* 当前选中的值 */
    int currentValue;

    /* 鼠标是否按下 */
    bool isDragging;

    /* 偏移量,记录鼠标按下后移动的垂直距离 */
    int deviation;

    /* 鼠标按下的垂直位置 */
    int mouseSrcPos;

    /* 数字大小 */
    int numSize;

    /* 动画 */
    QPropertyAnimation *homingAni;

    /* 间隔大小 */
    int interval;

    /* 分格数量 */
    int devide;

    /* 数字颜色 */
    QColor numberColor;
};
#endif // NUMBERPICKER_H
