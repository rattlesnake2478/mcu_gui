QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

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
#    ../mcu_gui/application/abstract_application.cpp \
#    ../mcu_gui/components/digit_segment.cpp \
#    ../mcu_gui/components/label.cpp \
#    ../mcu_gui/components/time_widget.cpp \
    ../mcu_gui/core/color/colors.cpp \
#    ../mcu_gui/core/font/font.cpp \
#    ../mcu_gui/core/font/verdana/verdana_mid.cpp \
#    ../mcu_gui/core/font/verdana/verdana_number_20.cpp \
#    ../mcu_gui/core/keys/key.cpp \
#    ../mcu_gui/core/keys/key_processor.cpp \
#    ../mcu_gui/core/layout.cpp \
#    ../mcu_gui/core/linear/matrix.cpp \
#    ../mcu_gui/core/paint_engine.cpp \
#    ../mcu_gui/core/painter.cpp \
#    ../mcu_gui/core/painter/paint_device.cpp \
#    ../mcu_gui/core/widget.cpp \
#    ../mcu_gui/dashboard/dashboard_typ1.cpp \
#    ../mcu_gui/dashboard/drz_dashboard.cpp \
#    ../mcu_gui/gauges/arrow_indicator.cpp \
#    ../mcu_gui/gauges/gauge.cpp \
#    ../mcu_gui/gauges/lamp.cpp \
#    ../mcu_gui/gauges/segment_indicator.cpp \
#    ../mcu_gui/gauges/tachometer.cpp \
    ../mcu_gui/core/painter/paint_device.cpp \
    main.cpp \
    mainwindow.cpp


HEADERS += \
#    ../mcu_gui/application/abstract_application.h \
#    ../mcu_gui/components/digit_segment.h \
#    ../mcu_gui/components/label.h \
#    ../mcu_gui/components/lamps.h \
#    ../mcu_gui/components/time_widget.h \
    ../mcu_gui/core/color/colors.h \
    ../mcu_gui/core/color/mac_os_palette.h \
#    ../mcu_gui/core/font/font.h \
#    ../mcu_gui/core/font/verdana/verdana_mid.h \
#    ../mcu_gui/core/font/verdana/verdana_mid_data.h \
#    ../mcu_gui/core/font/verdana/verdana_number_20.h \
#    ../mcu_gui/core/font/verdana/verdana_number_20_data.h \
#    ../mcu_gui/core/keys/key.h \
#    ../mcu_gui/core/keys/key_processor.h \
#    ../mcu_gui/core/layout.h \
#    ../mcu_gui/core/linear/matrix.h \
#    ../mcu_gui/core/paint_engine.h \
#    ../mcu_gui/core/painter.h \
#    ../mcu_gui/core/painter/paint_device.h \
#    ../mcu_gui/core/painter/paint_device.tpp \
#    ../mcu_gui/core/types.h \
#    ../mcu_gui/core/widget.h \
#    ../mcu_gui/dashboard/abstract_dashboard.h \
#    ../mcu_gui/dashboard/dashboard_typ1.h \
#    ../mcu_gui/dashboard/dashboard_types.h \
#    ../mcu_gui/dashboard/drz_dashboard.h \
#    ../mcu_gui/gauges/arrow_indicator.h \
#    ../mcu_gui/gauges/gauge.h \
#    ../mcu_gui/gauges/lamp.h \
#    ../mcu_gui/gauges/segment_indicator.h \
#    ../mcu_gui/gauges/tachometer.h \
    ../mcu_gui/core/painter/paint_device.h \
    ../mcu_gui/core/painter/paint_device.tpp \
    ../mcu_gui/core/types.h \
    mainwindow.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
