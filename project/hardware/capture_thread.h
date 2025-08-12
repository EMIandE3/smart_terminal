/******************************************************************
Copyright © Deng Zhimao Co., Ltd. 2021-2030. All rights reserved.
* @projectName   video_server
* @brief         capture_thread.h
* @author        Deng Zhimao
* @email         dengzhimao@alientek.com
* @link          www.openedv.com
* @date          2021-11-19
*******************************************************************/
#ifndef CAPTURE_THREAD_H
#define CAPTURE_THREAD_H

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#ifdef linux
#include <linux/fb.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <linux/videodev2.h>
#include <linux/input.h>
#endif

#include <QThread>
#include <QDebug>
#include <QPushButton>
#include <QImage>
#include <QByteArray>
#include <QBuffer>
#include <QTime>
#include <QUdpSocket>

#define VIDEO_DEV			"/dev/video1"
#define FB_DEV				"/dev/fb0"
#define VIDEO_BUFFER_COUNT	3

struct buffer_info {
    void *start;
    unsigned int length;
};

class CaptureThread : public QThread
{
    Q_OBJECT

signals:
    /* 准备图片 */
    void imageReady(QImage);
    void sendImage(QImage);

private:
    /* 线程开启flag */
    bool startFlag = false;

    /* 开启广播flag */
    bool startBroadcast = false;

    /* 本地显示flag  */
    bool startLocalDisplay = false;
    void run() override;

public:
    CaptureThread(QObject *parent = nullptr) {
        Q_UNUSED(parent);
    }

public slots:
    /* 设置线程 */
    void setThreadStart(bool start) {
        startFlag = start;
        if (start) {
            if (!this->isRunning())
                this->start();
        } else {
            this->quit();
        }
    }

    /* 设置广播 */
    void setBroadcast(bool start) {
        startBroadcast = start;
    }

    /* 设置本地显示 */
    void setLocalDisplay(bool start) {
        startLocalDisplay = start;
    }
};

#endif // CAPTURE_THREAD_H
