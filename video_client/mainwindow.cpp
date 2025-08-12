#include "mainwindow.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    /* 设置背景颜色为黑色 */
    QColor color = QColor(Qt::black);
    QPalette p;
    p.setColor(QPalette::Window, color);
    this->setPalette(p);

    udpSocket = new QUdpSocket(this);
    /* 绑定端口号 */
    udpSocket->bind(QHostAddress::Any, 8888);

    videoLabel = new QLabel(this);
    videoLabel->resize(640, 480);
    videoLabel->setText("未获取到图像数据");
    videoLabel->setStyleSheet("QWidget {color: white;}");
    videoLabel->setAlignment(Qt::AlignCenter);
    connect(udpSocket, SIGNAL(readyRead()), this,SLOT(videoUpdate()));

    this->setGeometry(0, 0, 800, 480);
}

MainWindow::~MainWindow()
{
}

void MainWindow::videoUpdate()
{
    QByteArray datagram;

    /* 数据大小重置 */
    datagram.resize(udpSocket->pendingDatagramSize());

    /* 数据存放到datagram中 */
    udpSocket->readDatagram(datagram.data(), datagram.size());

    QByteArray decryptedByte;
    decryptedByte = QByteArray::fromBase64(datagram.data());

    QImage image;
    image.loadFromData(decryptedByte);

    /* 显示图像 */
    videoLabel->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)
    videoLabel->move((this->width() - 640) / 2, (this->height() - 480) / 2);
}

