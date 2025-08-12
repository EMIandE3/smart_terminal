/******************************************************************
Copyright © Deng Zhimao Co., Ltd. 2021-2030. All rights reserved.
* @projectName   video_server
* @brief         mainwindow.h
* @author        Deng Zhimao
* @email         dengzhimao@alientek.com
* @link          www.openedv.com
* @date          2021-11-19
*******************************************************************/
#ifndef VIDEO_MONITOR_H
#define VIDEO_MONITOR_H

#include <QMainWindow>
#include <QLabel>
#include <QImage>
#include <QPushButton>
#include <QHBoxLayout>
#include <QCheckBox>

#include "capture_thread.h"

class Monitor : public QMainWindow
{
    Q_OBJECT

public:
    explicit Monitor(QWidget *parent = nullptr);
    ~Monitor();

private:
    /* 用于显示捕获到的图像 */
    QLabel *videoLabel;

    /* 摄像头线程 */
    CaptureThread *captureThread;

    /* 开始捕获图像按钮 */
    QPushButton *startCaptureButton;

    /* 用于开启本地图像显示 */
    QCheckBox *checkBox1;

    /* 用于开启网络广播 */
    QCheckBox *checkBox2;

    /* 重写大小事件 */
    void resizeEvent(QResizeEvent *event) ;
//    void resizeEvent(QResizeEvent *event) override;

private slots:
    /* 显示图像 */
    void showImage(QImage);

    /* 开始采集按钮被点击 */
    void startCaptureButtonClicked(bool);
};
#endif // MAINWINDOW_H
