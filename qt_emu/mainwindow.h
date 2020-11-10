#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "../mcu_gui/core/color/colors.h"

using ColorFormat = McuGui::ColorARGB32;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(uint16_t width=480u, uint16_t height=272u);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *);

private:
    uint16_t height_, width_;
    ColorFormat::data_type *buffer_;
    QTimer *paintTimer_;
    QImage *mainImage_;
};
#endif // MAINWINDOW_H
