# smart_terminal

## 概述：

本项目是基于https://github.com/Acoucou/imx6ull_project项目做的二次开发，首先修改了相关makefile文件配置和ubuntu库文件配置，使得该项目的**基本功能**能够正常实现。之后，在此基础上实现了**视频局域网广播功能**和**SQLite时钟定时功能**，并补足了该项目初版时由于缺少摄像头ov5640而导致缺少相关**摄像头硬件验证**的问题，此外，还修改了**icm20608硬件驱动配置**，使之能够正常运行。如有相关问题，可发邮件至22331171@zju.edu.cn进行交流。

## 项目目的

1、基于arm-Linux开发一款嵌入式智能终端

2、集合轮播图、OpenCV图像处理、摄像头驱动及opencv人脸识别、板级硬件（LED灯、蜂鸣器、光距离红外、加速度计）、本地音频播放、本地视频播放、MQTT物联网传输、UDP视频流广播和SQLite定时等各种模块，可用于智能硬件的各种场景

## 项目架构

![](./img/1.png)

常见的项目架构如下：

### 项目配置（config）

.pro文件

.pri文件

config.h文件

### 硬件层（base层）

提供连通硬件各种接口，底层接口。可以再按底层驱动方式进行细分类。可分类如下：

字符设备、块设备、网络设备

### 中间控制层（middle control层）

提供各种APP层需要的**接口（API）函数**，可细分如下：

open sources(开源库)

network（网络接口）

hardware（硬件读写）

media（媒体，音视频等）

### APP层（UI表单层）

APP层逻辑编写，如各种控制事件，UI交互逻辑

### **项目资源（resources）**

项目的资源管理，如图片，样式，字体库等等。可分类如下：

img、style、font

以上框架是笔者个人理解，仅做参考

## 项目移植

### 1、开发板网络连接

本项目涉及到通信，因此需要做好开发板的局域网连接，由于笔者所处的环境中均是使用的无线校园网上网，因此采用了**电脑 WiFi 上网，开发板和电脑直连**的方式连接局域网。网络拓扑结构如下：

![](./img/6.png)

虚拟机中设置两个网卡，一个网卡为桥接模式，另一个网卡为NAT模式。桥接模式的网卡选择桥接至外部网线中。最终可实现开发板、虚拟机和主机三者之间的通信，并且虚拟机和主机均可上网。

### 2、文件传输

虚拟机和主机之间的文件传输可使用**FileZilla Client软件**，需要设置虚拟机能上网网卡的ip。虚拟机和开发板之间的文件传输可使用 **tftp** 或 **nfs** 协议。tftp适用于传输小文件，nfs适用于大文件和工程传输，命令示例如下：

```
tftp -g -r test.c（文件名） 192.168.10.100
```

```
mount -t nfs -o nolock,nfsvers=3 192.168.10.100:/home/alientek/linux/nfs（虚拟机共享文件夹路径） files/（开发板需要挂载的文件路径）
```

### 3、makefile文件修改

当在自己的配置环境中移植该工程时，由于本工程的makefile在编译部分第三方库时使用的是绝对路径，因此要对arm和x86文件夹下的makefile中的对应路径进行修改。可进行如下的更换：

```
/home/coucou/Desktop/my_project  换为 /home/alientek/project_1/imx6ull_project-master
/home/coucou/linux/opencv-3.4.1 换为 /home/alientek/opencv/opencv-3.4.1
/home/coucou/linux/qtmqtt-5.12.9 换为 /home/alientek/qtmqtt/qtmqtt-5.12.9
/linux/opencv-3.4.1 换为 /opencv/opencv-3.4.1

以下为arm中多出的：
/home/coucou/linux/qt/qt-everywhere-src-5.12.9 换为 /home/alientek/qt5.12.9/qt-everywhere-src-5.12.9
/home/coucou/linux/qt/tslib-1.21 换为 /home/alientek/linux/IMX6ULL/tool/tslib-1.21
/home/coucou/linux/gcc-linaro-7.5.0-2019.12-x86_64_arm-linux-gnueabihf/arm-linux-gnueabihf/include/c++/7.5.0 换为 /home/alientek/linux/tool/arm-linux-gnueabihf-gcc/gcc-linaro-4.9.4-2017.01-x86_64_arm-linux-gnueabihf/arm-linux-gnueabihf/include/c++/4.9.4

/home/coucou/linux/gcc-linaro-7.5.0-2019.12-x86_64_arm-linux-gnueabihf/arm-linux-gnueabihf/include 换为 /home/alientek/linux/tool/arm-linux-gnueabihf-gcc/gcc-linaro-4.9.4-2017.01-x86_64_arm-linux-gnueabihf/arm-linux-gnueabihf/include
/home/coucou/linux/gcc-linaro-7.5.0-2019.12-x86_64_arm-linux-gnueabihf/lib/gcc/arm-linux-gnueabihf/7.5.0/include-fixed 换为 /home/alientek/linux/tool/arm-linux-gnueabihf-gcc/gcc-linaro-4.9.4-2017.01-x86_64_arm-linux-gnueabihf/lib/gcc/arm-linux-gnueabihf/4.9.4/include-fixed

/home/coucou/linux/gcc-linaro-7.5.0-2019.12-x86_64_arm-linux-gnueabihf/lib/gcc/arm-linux-gnueabihf/7.5.0/include 换为 /home/alientek/linux/tool/arm-linux-gnueabihf-gcc/gcc-linaro-4.9.4-2017.01-x86_64_arm-linux-gnueabihf/lib/gcc/arm-linux-gnueabihf/4.9.4/include

/home/coucou/linux/gcc-linaro-7.5.0-2019.12-x86_64_arm-linux-gnueabihf/arm-linux-gnueabihf/libc/usr/include 换为 /home/alientek/linux/tool/arm-linux-gnueabihf-gcc/gcc-linaro-4.9.4-2017.01-x86_64_arm-linux-gnueabihf/arm-linux-gnueabihf/libc/usr/include

/linux/qt/qt-everywhere-src-5.12.9 换为 /qt5.12.9/qt-everywhere-src-5.12.9
```

### 4、第三方库移植

本实验中额外用到的第三方库主要有opencv、mqtt。这两个库可参照原作者的库文件，结合网上的资料进行移植，主要可以分为./config、make、make install三步。此外，还需要用到gphoto2和gtk3库。**注意，编译这些库文件时需要用到交叉编译**。配置交叉编译环境，并在交叉编译时制定ARCH和CROSS_COMPLIE，也即：

```
ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf-
```

当交叉编译完成后，需要将第三方库放置于开发板的指定位置，并设置环境变量，运行QT编译出的build文件夹下的arm可执行文件。例如命令如下：

```
export LD_LIBRARY_PATH=/home/alientek/gphoto2/:/home/alientek/gtk3/
cd /home/alientek/project_1/imx6ull_project-master/build-project-ATK_I_MX6U-Debug/
./project
```

### 5、x86和arm环境下工程构建

当在x86上运行时，在project.pro文件中采用如下头文件和库文件路径：

```
INCLUDEPATH += /home/alientek/opencv/opencv-3.4.1/build/include
LIBS +=  -L/home/alientek/opencv/opencv-3.4.1/build/lib/ -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_videoio -lopencv_imgcodecs -lopencv_core -lopencv_calib3d -lopencv_features2d -lopencv_video -lopencv_ml -lopencv_objdetect -lopencv_flann

#mqtt lib
unix:!macx: LIBS += -L$$PWD/lib/x86_qtmqtt/lib/ -lQt5Mqtt
INCLUDEPATH += $$PWD/lib/x86_qtmqtt/src/.
DEPENDPATH += $$PWD/lib/x86_qtmqtt/.
```

当在arm上运行时，在project.pro文件中采用如下头文件和库文件路径：CONFIG += link_pkgconfig

```
PKGCONFIG += opencv
PKGCONFIG += gtk+-3.0
INCLUDEPATH += /opt/fsl-imx-x11/4.1.15-2.1.0/sysroots/cortexa7hf-neon-poky-linux-gnueabi/usr/include

#mqtt lib
unix:!macx: LIBS += -L$$PWD/lib/arm_qtmqtt/lib/ /home/alientek/project_1/imx6ull_project-master/project/lib/arm_qtmqtt/lib/libQt5Mqtt.so.5.12.9
INCLUDEPATH += $$PWD/lib/arm_qtmqtt/src/.
DEPENDPATH += $$PWD/lib/arm_qtmqt/.
```

### 6、gdb调试

（1）开发板上运行gdbserver，执行如下命令：

```
gdbserver 192.168.10.100:2001 gdbtest //启动开发板上的 gdbserver
```

虚拟机上通过如下命令启动gdb：

```
arm-linux-gdb gdbtest
```

之后在(gdb)行输入如下命令连接到开发板上：

```
target remote 192.168.1.50:2001 //连接到开发板上
```

连接成功之后，可用常见的gdb命令进行调试。如l、b、c、n等

此外，还可以使用**backtrace、addr2line、objdump、readelf**等工具进行调试。

（2）还可以利用虚拟机上的vscode进行调试，具有图形化界面的便利性，但这时就只能进行断点调试，无法利用上一行的加粗的工具了

vscode中调试需要配置launch.json文件，配置该文件的如下项目：

①、name：调试的项目名
②、program：需要调试的应用程序可执行文件路径。
③、cwd：需要调试的应用程序源码路径。
④、miDebuggerPath：此项需要手动添加，用于指定所使用的交叉编译器 gdb 路径。
⑤、miDebuggerServerAddress：此项需要手动添加，远程 gdbserver 服务器地址。

### 7、linux内核模块开发与裁剪

当把linux内核的驱动以module的格式写好之后，交叉编译会生成.ko文件，此时交叉编译需要指定内核环境，需要与开发板的内核环境保持一致，包括u-boot、zImage、rootfs、dtb都需要保持一致，否则编译好的ko驱动会无法在开发板上运行。

内核的裁剪可以从删减自启过程中不需要的驱动入手，可从makefile入手，也可从图形化配置入手，具体命令如下：

```
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- distclean

make imx_alientek_emmc_defconfig ARCH=arm CROSS_COMPILE=$CROSS_COMPILE --defconfig=arch/arm/configs/imx_alientek_emmc_defconfig

make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- menuconfig

make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- all -j16
```

### 8、工程说明

arm和x86文件夹包含对应架构下的库文件，video_client文件夹包含MQTT客户端项目，project文件夹为主工程，两个build文件夹包含两种架构下的编译结果文件

## 项目测试

### 板载连接图：

![](./img/5.png)

### 轮播图测试：

![](./img/6.jpg)

### opencv图像处理算子测试：

![](./img/7.jpg)

### 摄像头和人脸识别测试：

![](./img/8.jpg)

![](./img/9.jpg)

### 板载硬件测试：

#### LED灯、蜂鸣器：

![](./img/11.jpg)

#### 光距离红外传感器：

![](./img/10.jpg)

#### 加速度计传感器：

![](./img/12.jpg)

### 音频播放和视频播放测试：

![](./img/13.jpg)

![](./img/14.jpg)

### MQTT通信测试：

#### 开发板端：

![](./img/15.jpg)

![](./img/16.jpg)

#### 虚拟机（服务器端）：

```
sudo service mosquitto start //启动服务
sudo service mosquitto status //查看服务状态
sudo service mosquitto stop //停止服务
```

#### 主机端：

![](./img/2.png)

![](./img/3.png)

### 视频流UDP广播测试

#### 开发板端：

![](./img/17.jpg)

![](./img/18.jpg)

#### 主机端：

![](./img/4.png)

### SQLite时钟定时测试：

![](./img/19.jpg)

![](./img/20.jpg)

## 项目参考

https://github.com/Acoucou/imx6ull_project

https://gitee.com/feiyangqingyun/QWidgetDemo