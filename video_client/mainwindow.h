#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUdpSocket>
#include <QLabel>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    /* 用于接收数据 */
    QUdpSocket *udpSocket;

    /* 显示接收的图像数据 */
    QLabel *videoLabel;

    void resizeEvent(QResizeEvent *event) override;

private slots:
    /* 图像更新 */
    void videoUpdate();
};
#endif // MAINWINDOW_H
