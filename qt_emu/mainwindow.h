#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "../mcu_gui/core/painter.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(uint16_t width=480u, uint16_t height=270u);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *);

private:
    uint16_t height_, width_;
    McuGui::Color *buffer_;
    QTimer *paintTimer_;
    QImage *mainImage_;
};
#endif // MAINWINDOW_H
