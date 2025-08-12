/******************************************************************
Copyright © Deng Zhimao Co., Ltd. 1990-2021. All rights reserved.
* @projectName   17_sqlite_example
* @brief         switchbutton.cpp
* @author        Deng Zhimao
* @email         1252699831@qq.com
* @net           www.openedv.com
* @date          2021-05-14
*******************************************************************/
#include "switchbutton.h"

#include <QPainter>
#include <QMouseEvent>

SwitchButton::SwitchButton(QWidget *parent)
    : QWidget(parent),
      m_bChecked(false),
      m_background(Qt::gray),
      m_checkedColor(34, 131, 246),
      m_disabledColor(190, 190, 190),
      m_thumbColor(Qt::gray),
      m_radius(12.5),
      m_nHeight(16),
      m_nMargin(3)
{
    /* 鼠标滑过光标形状 - 手型 */
    setCursor(Qt::PointingHandCursor);

    /* 连接信号槽 */
    connect(&m_timer, SIGNAL(timeout()),
            this, SLOT(onTimeout()));
}

/* 绘制开关 */
void SwitchButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setRenderHint(QPainter::Antialiasing);

    QPainterPath path;
    QColor background;
    QColor thumbColor;
    qreal dOpacity;
    /* 可用状态 */
    if (isEnabled()) {
        /* 打开状态 */
        if (m_bChecked) {
            background = m_checkedColor;
            thumbColor = m_checkedColor;
            dOpacity = 0.600;
            /* 关闭状态 */
        } else {
            background = m_background;
            thumbColor = m_thumbColor;
            dOpacity = 0.800;
        }
        /* 不可用状态 */
    } else {
        background = m_background;
        dOpacity = 0.260;
        thumbColor = m_disabledColor;
    }
    /* 绘制大椭圆 */
    painter.setBrush(background);
    painter.setOpacity(dOpacity);
    path.addRoundedRect(QRectF(m_nMargin,
                               m_nMargin, width() - 2 * m_nMargin,
                               height() - 2 * m_nMargin),
                        m_radius, m_radius);
    painter.drawPath(path.simplified());

    /* 绘制小椭圆 */
    painter.setBrush(thumbColor);
    painter.setOpacity(1.0);
    painter.drawEllipse(QRectF(m_nX - (m_nHeight / 2),
                               m_nY - (m_nHeight / 2),
                               height(),
                               height()));
}

/* 鼠标按下事件 */
void SwitchButton::mousePressEvent(QMouseEvent *event)
{
    if (isEnabled()) {
        if (event->buttons() & Qt::LeftButton) {
            event->accept();
        } else {
            event->ignore();
        }
    }
}

/* 鼠标释放事件 - 切换开关状态、发射toggled()信号 */
void SwitchButton::mouseReleaseEvent(QMouseEvent *event)
{
    if (isEnabled()) {
        if ((event->type() == QMouseEvent::MouseButtonRelease)
                && (event->button() == Qt::LeftButton)) {
            event->accept();
            m_bChecked = !m_bChecked;
            emit toggled(m_bChecked);
            m_timer.start(10);
        } else {
            event->ignore();
        }
    }
}

/* 大小改变事件 */
void SwitchButton::resizeEvent(QResizeEvent *event)
{
    m_nX = m_nHeight / 2;
    m_nY = m_nHeight / 2;
    QWidget::resizeEvent(event);
}

/* 默认大小 */
QSize SwitchButton::sizeHint() const
{
    return minimumSizeHint();
}

/* 最小大小 */
QSize SwitchButton::minimumSizeHint() const
{
    return QSize(2 * (m_nHeight + m_nMargin),
                 m_nHeight + 2 * m_nMargin);
}

/* 切换状态 - 滑动 */
void SwitchButton::onTimeout()
{
    if (m_bChecked) {
        m_nX += 1;
        if (m_nX >= width() - m_nHeight - m_nHeight / 2 ) {
            m_timer.stop();
            m_nX -= 1;
        }
    } else {
        m_nX -= 1;
        if (m_nX <= m_nHeight / 2) {
            m_timer.stop();
            m_nX += 1;
        }
    }
    update();
}

/* 返回开关状态 - 打开：true 关闭：false */
bool SwitchButton::isToggled() const
{
    return m_bChecked;
}

/* 设置开关状态 */
void SwitchButton::setToggle(bool checked)
{
    m_bChecked = checked;
    m_timer.start(10);
}

/* 设置背景颜色 */
void SwitchButton::setBackgroundColor(QColor color)
{
    m_background = color;
}

/* 设置选中颜色 */
void SwitchButton::setCheckedColor(QColor color)
{
    m_checkedColor = color;
}

/* 设置不可用颜色 */
void SwitchButton::setDisbaledColor(QColor color)
{
    m_disabledColor = color;
}
