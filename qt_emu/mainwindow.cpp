#include "mainwindow.h"

#include <QPainter>
#include <QTimer>

#include "../mcu_gui/app/gauges/lamp.h"
#include "../mcu_gui/core/layout.h"

using namespace McuGui;

MainWindow::MainWindow(uint16_t width, uint16_t height)
    : QMainWindow(nullptr), height_(height), width_(width)
{
    this->setFixedSize(width, height);

    paintTimer_ = new QTimer;
    paintTimer_->setInterval(100);
    this->connect(paintTimer_, SIGNAL(timeout()), SLOT(repaint()));
    paintTimer_->start();

    mainImage_ = new QImage(width, height, QImage::Format_RGB32);
    buffer_ = new McuGui::Color[width * height];

    MemoryPainter painter(buffer_);
    painter.setLocalOrigin({0, 50});

    GridLayout layout(Lamp::StandartDimension, 3, 2);
    auto ltLamp = LeftTurnLamp();
    auto rtLamp = RightTurnLamp();
    auto nLamp= NeutralLamp();
    auto hLamp = HighBeamLamp();
    auto bLamp = BatteryLamp();
    auto tLamp = TempLamp();
    layout.addWidget(&ltLamp, 0, 0);
    layout.addWidget(&rtLamp, 0, 1);
    layout.addWidget(&nLamp, 1, 0);
    layout.addWidget(&hLamp, 1, 1);
    layout.addWidget(&bLamp, 2, 0);
    layout.addWidget(&tLamp, 2, 1);

    ltLamp.setValue(true);
    rtLamp.setValue(true);
    nLamp.setValue(true);
    hLamp.setValue(true);
    bLamp.setValue(true);
    tLamp.setValue(true);

    layout.paint(painter);

//    painter.setLocalOrigin({240, 136}); // center
//    TempLamp lamp1;
//    TempLamp lamp2;
//    lamp1.setValue(true);
//    lamp1.paint(painter);
//    painter.setLocalOrigin({290, 136});
//    lamp2.paint(painter);

}

MainWindow::~MainWindow()
{
    delete[] buffer_;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    McuGui::Color *line;
    for(int y=0; y<height_; y++)
    {
        line=(McuGui::Color*)mainImage_->scanLine(y);
        for(int x=0; x<width_; x++)
        {
            line[x]=buffer_[x+y*width_];
        }
    }
    QPainter painter(this);
    painter.drawImage(0,0,*mainImage_);
}
