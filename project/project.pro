QT       += core gui network multimedia multimediawidgets charts sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
#CONFIG += console

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwidget.cpp

HEADERS += \
    mainwidget.h

FORMS += \
    mainwidget.ui


# x86
#INCLUDEPATH += /home/alientek/opencv/opencv-3.4.1/build/include
#LIBS +=  -L/home/alientek/opencv/opencv-3.4.1/build/lib/ -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_videoio \
#        -lopencv_imgcodecs -lopencv_core -lopencv_calib3d -lopencv_features2d -lopencv_video -lopencv_ml \
#        -lopencv_objdetect -lopencv_flann


## mqtt lib
#unix:!macx: LIBS += -L$$PWD/lib/x86_qtmqtt/lib/ -lQt5Mqtt

#INCLUDEPATH += $$PWD/lib/x86_qtmqtt/src/.
#DEPENDPATH += $$PWD/lib/x86_qtmqtt/.


# arm
CONFIG += link_pkgconfig
PKGCONFIG += opencv
PKGCONFIG += gtk+-3.0
INCLUDEPATH += /opt/fsl-imx-x11/4.1.15-2.1.0/sysroots/cortexa7hf-neon-poky-linux-gnueabi/usr/include

# mqtt lib
unix:!macx: LIBS += -L$$PWD/lib/arm_qtmqtt/lib/ \
                    /home/alientek/project_1/imx6ull_project-master/project/lib/arm_qtmqtt/lib/libQt5Mqtt.so.5.12.9

INCLUDEPATH += $$PWD/lib/arm_qtmqtt/src/.
DEPENDPATH += $$PWD/lib/arm_qtmqt/.



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

include(./form/form.pri)
include(./hardware/hardware.pri)

INCLUDEPATH += $$PWD/hardware
INCLUDEPATH += $$PWD/form

#DISTFILES += \
#    lib/open_lib/opencv_3.4.1/x86_opencv/lib/libopencv_calib3d.so \
#    lib/open_lib/opencv_3.4.1/x86_opencv/lib/libopencv_calib3d.so.3.4.1 \
#    lib/open_lib/opencv_3.4.1/x86_opencv/lib/libopencv_core.so \
#    lib/open_lib/opencv_3.4.1/x86_opencv/lib/libopencv_core.so.3.4.1 \
#    lib/open_lib/opencv_3.4.1/x86_opencv/lib/libopencv_dnn.so \
#    lib/open_lib/opencv_3.4.1/x86_opencv/lib/libopencv_dnn.so.3.4.1 \
#    lib/open_lib/opencv_3.4.1/x86_opencv/lib/libopencv_features2d.so \
#    lib/open_lib/opencv_3.4.1/x86_opencv/lib/libopencv_features2d.so.3.4.1 \
#    lib/open_lib/opencv_3.4.1/x86_opencv/lib/libopencv_flann.so \
#    lib/open_lib/opencv_3.4.1/x86_opencv/lib/libopencv_flann.so.3.4.1 \
#    lib/open_lib/opencv_3.4.1/x86_opencv/lib/libopencv_highgui.so \
#    lib/open_lib/opencv_3.4.1/x86_opencv/lib/libopencv_highgui.so.3.4.1 \
#    lib/open_lib/opencv_3.4.1/x86_opencv/lib/libopencv_imgcodecs.so \
#    lib/open_lib/opencv_3.4.1/x86_opencv/lib/libopencv_imgcodecs.so.3.4.1 \
#    lib/open_lib/opencv_3.4.1/x86_opencv/lib/libopencv_imgproc.so \
#    lib/open_lib/opencv_3.4.1/x86_opencv/lib/libopencv_imgproc.so.3.4.1 \
#    lib/open_lib/opencv_3.4.1/x86_opencv/lib/libopencv_ml.so \
#    lib/open_lib/opencv_3.4.1/x86_opencv/lib/libopencv_ml.so.3.4.1 \
#    lib/open_lib/opencv_3.4.1/x86_opencv/lib/libopencv_objdetect.so \
#    lib/open_lib/opencv_3.4.1/x86_opencv/lib/libopencv_objdetect.so.3.4.1 \
#    lib/open_lib/opencv_3.4.1/x86_opencv/lib/libopencv_photo.so \
#    lib/open_lib/opencv_3.4.1/x86_opencv/lib/libopencv_photo.so.3.4.1 \
#    lib/open_lib/opencv_3.4.1/x86_opencv/lib/libopencv_shape.so \
#    lib/open_lib/opencv_3.4.1/x86_opencv/lib/libopencv_shape.so.3.4.1 \
#    lib/open_lib/opencv_3.4.1/x86_opencv/lib/libopencv_stitching.so \
#    lib/open_lib/opencv_3.4.1/x86_opencv/lib/libopencv_stitching.so.3.4.1 \
#    lib/open_lib/opencv_3.4.1/x86_opencv/lib/libopencv_superres.so \
#    lib/open_lib/opencv_3.4.1/x86_opencv/lib/libopencv_superres.so.3.4.1 \
#    lib/open_lib/opencv_3.4.1/x86_opencv/lib/libopencv_video.so \
#    lib/open_lib/opencv_3.4.1/x86_opencv/lib/libopencv_video.so.3.4.1 \
#    lib/open_lib/opencv_3.4.1/x86_opencv/lib/libopencv_videoio.so \
#    lib/open_lib/opencv_3.4.1/x86_opencv/lib/libopencv_videoio.so.3.4.1 \
#    lib/open_lib/opencv_3.4.1/x86_opencv/lib/libopencv_videostab.so \
#    lib/open_lib/opencv_3.4.1/x86_opencv/lib/libopencv_videostab.so.3.4.1

