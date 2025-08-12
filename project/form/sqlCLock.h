/******************************************************************
Copyright © Deng Zhimao Co., Ltd. 1990-2021. All rights reserved.
* @projectName   17_sqlite_example
* @brief         mainwindow.h
* @author        Deng Zhimao
* @email         1252699831@qq.com
* @net           www.openedv.com
* @date          2021-05-15
*******************************************************************/
#ifndef SQLCLOCK_H
#define SQLCLOCK_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMainWindow>
#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QListWidget>
#include <QLabel>
#include <QTime>
#include <QSqlTableModel>
#include "numberpicker.h"
#include "switchbutton.h"

class NumberPicker;
class SwitchButton;

/* ListWiget项结构体 */
struct ItemObjectInfo {
    /* 闹钟开关 */
    SwitchButton *switchButton;
    /* Widget容器 */
    QWidget *widget;
    /* 水平布局 */
    QHBoxLayout *hBoxLayout;
};


class sqlCLock : public QMainWindow
{
    Q_OBJECT

public:
    sqlCLock(QWidget *parent = nullptr);
    ~sqlCLock();

private:

    /* 数据库连接类 */
    QSqlDatabase sqlDatabase;

    /* 数据库操作模型 */
    QSqlTableModel *model;

    /* 时针选择器 */
    NumberPicker *hourPicker;

    /* 分钟选择器 */
    NumberPicker *minutePicker;

    /* 弹出选择时间对话框 */
    QDialog *alarmDialog;

    /* 水平布局 */
    QHBoxLayout *hBoxLayout[3];

    /* 垂直布局 */
    QVBoxLayout *vBoxLayout[2];

    /* 显示闹钟列表 */
    QListWidget *listWidget;

    /* 主Widget */
    QWidget *mainWidget;

    /* 底部Wiget */
    QWidget *bottomWidget;

    /* 弹出对话框布局窗口选择时间容器 */
    QWidget *timeWidget;

    /* 弹出对话框布局窗口按钮容器 */
    QWidget *btWidget;

    /* 添加闹钟按钮 */
    QPushButton *addAlarm;

    /* 确认按钮 */
    QPushButton *yesButton;

    /* 取消按钮 */
    QPushButton *cancelButton;

    /* listWiget项信息存储 */
    QVector<ItemObjectInfo> itemObjectInfo;

private slots:
    /* 添加闹钟按钮被点击 */
    void addAlarmClicked();

    /* 列表被点击 */
    void listWidgetItemClicked(QListWidgetItem *);

    /* 确认按钮被点击 */
    void yesButtonClicked();

    /* 取消按钮被点击 */
    void cancelButtonClicked();

    /* 开关按钮点击 */
    void switchButtonClicked(bool);
};
#endif // MAINWINDOW_H
