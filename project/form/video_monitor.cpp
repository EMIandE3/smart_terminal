/******************************************************************
Copyright © Deng Zhimao Co., Ltd. 2021-2030. All rights reserved.
* @projectName   video_server
* @brief         mainwindow.cpp
* @author        Deng Zhimao
* @email         dengzhimao@alientek.com
* @link          www.openedv.com
* @date          2021-11-19
*******************************************************************/
#include "video_monitor.h"

Monitor::Monitor(QWidget *parent)
    : QMainWindow(parent)
{
    this->setGeometry(0, 0, 800, 480);

    videoLabel = new QLabel(this);
    videoLabel->setText("未获取到图像数据或未开启本地显示");
    videoLabel->setStyleSheet("QWidget {color: white;}");
    videoLabel->setAlignment(Qt::AlignCenter);
    videoLabel->resize(640, 480);

    checkBox1 = new QCheckBox(this);
    checkBox2 = new QCheckBox(this);

    checkBox1->resize(120, 50);
    checkBox2->resize(120, 50);

    checkBox1->setText("本地显示");
    checkBox2->setText("开启广播");

    checkBox1->setStyleSheet("QCheckBox {color: yellow;}"
                             "QCheckBox:indicator {width: 40; height: 40;}");
    checkBox2->setStyleSheet("QCheckBox {color: yellow;}"
                             "QCheckBox:indicator {width: 40; height: 40}");

    /* 按钮 */
    startCaptureButton = new QPushButton(this);
    startCaptureButton->setCheckable(true);
    startCaptureButton->setText("开始采集摄像头数据");

    /* 设置背景颜色为黑色 */
    QColor color = QColor(Qt::black);
    QPalette p;
    p.setColor(QPalette::Window, color);
    this->setPalette(p);

    /* 样式表 */
    startCaptureButton->setStyleSheet("QPushButton {background-color: white; border-radius: 30}"
                                      "QPushButton:pressed  {background-color: red;}");

    captureThread = new CaptureThread(this);

    connect(startCaptureButton, SIGNAL(clicked(bool)), captureThread, SLOT(setThreadStart(bool)));
    connect(startCaptureButton, SIGNAL(clicked(bool)), this, SLOT(startCaptureButtonClicked(bool)));
    connect(captureThread, SIGNAL(imageReady(QImage)), this, SLOT(showImage(QImage)));
    connect(checkBox1, SIGNAL(clicked(bool)), captureThread, SLOT(setLocalDisplay(bool)));
    connect(checkBox2, SIGNAL(clicked(bool)), captureThread, SLOT(setBroadcast(bool)));
}

Monitor::~Monitor()
{
}

void Monitor::showImage(QImage image)
{
    videoLabel->setPixmap(QPixmap::fromImage(image));
}

void Monitor::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)
    startCaptureButton->move((this->width() - 200) / 2, this->height() - 80);
    startCaptureButton->resize(200, 60);
    videoLabel->move((this->width() - 640) / 2, (this->height() - 480) / 2);
    checkBox1->move(this->width() - 120, this->height() / 2 - 50);
    checkBox2->move(this->width() - 120, this->height() / 2 + 25);
}

void Monitor::startCaptureButtonClicked(bool start)
{
    if (start)
        startCaptureButton->setText("停止采集摄像头数据");
    else
        startCaptureButton->setText("开始采集摄像头数据");
}

