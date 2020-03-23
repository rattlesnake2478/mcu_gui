QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

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
    ../mcu_gui/app/components/digit_segment.cpp \
    ../mcu_gui/app/gauges/gauge.cpp \
    ../mcu_gui/app/gauges/lamp.cpp \
    ../mcu_gui/app/gauges/segment_indicator.cpp \
    ../mcu_gui/core/layout.cpp \
    ../mcu_gui/core/painter.cpp \
    ../mcu_gui/core/widget.cpp \
    main.cpp \
    mainwindow.cpp


HEADERS += \
    ../mcu_gui/app/components/digit_segment.h \
    ../mcu_gui/app/components/lamps.h \
    ../mcu_gui/app/gauges/gauge.h \
    ../mcu_gui/app/gauges/lamp.h \
    ../mcu_gui/app/gauges/segment_indicator.h \
    ../mcu_gui/core/color32.h \
    ../mcu_gui/core/layout.h \
    ../mcu_gui/core/painter.h \
    ../mcu_gui/core/primitives.h \
    ../mcu_gui/core/types.h \
    ../mcu_gui/core/widget.h \
    mainwindow.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
