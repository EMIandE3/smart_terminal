/******************************************************************
Copyright © Deng Zhimao Co., Ltd. 1990-2021. All rights reserved.
* @projectName   17_sqlite_example
* @brief         switchbutton.h
* @author        Deng Zhimao
* @email         1252699831@qq.com
* @net           www.openedv.com
* @date          2021-05-14
*******************************************************************/
#ifndef SWITCHBUTTON_H
#define SWITCHBUTTON_H

#include <QWidget>
#include <QTimer>

class SwitchButton : public QWidget
{
    Q_OBJECT

public:
    explicit SwitchButton(QWidget *parent = nullptr);

    /* 返回开关状态 - 打开：true 关闭：false */
    bool isToggled() const;

    /* 设置开关状态 */
    void setToggle(bool checked);

    /* 设置背景颜色 */
    void setBackgroundColor(QColor color);

    /* 设置选中颜色 */
    void setCheckedColor(QColor color);

    /* 设置不可用颜色 */
    void setDisbaledColor(QColor color);

protected:
    /* 绘制开关 */
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    /* 鼠标按下事件 */
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

    /* 鼠标释放事件 - 切换开关状态、发射toggled()信号 */
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

    /* 大小改变事件 */
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

    /* 缺省大小 */
    QSize sizeHint() const Q_DECL_OVERRIDE;
    QSize minimumSizeHint() const Q_DECL_OVERRIDE;

signals:
    /* 状态改变时，发射信号 */
    void toggled(bool checked);

private slots:
    /* 状态切换时，用于产生滑动效果 */
    void onTimeout();

private:
    /* 是否选中 */
    bool m_bChecked;

    /* 背景颜色 */
    QColor m_background;

    /* 选中颜色 */
    QColor m_checkedColor;

    /* 不可用颜色 */
    QColor m_disabledColor;

    /* 拇指颜色 */
    QColor m_thumbColor;

    /* 圆角 */
    qreal m_radius;

    /* x点坐标 */
    qreal m_nX;

    /* y点坐标 */
    qreal m_nY;

    /* 高度 */
    qint16 m_nHeight;

    /* 外边距 */
    qint16 m_nMargin;

    /* 定时器 */
    QTimer m_timer;
};
#endif // SWITCHBUTTON_H
