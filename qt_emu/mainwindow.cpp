#include "mainwindow.h"

#include <QPainter>
#include <QTimer>

#include "../mcu_gui/core/painter/paint_device.h"

using namespace McuGui;

MainWindow::MainWindow(uint16_t width, uint16_t height)
    : QMainWindow(nullptr), height_(height), width_(width)
{
    this->setFixedSize(width, height);
    // setup redwaring by timer
    paintTimer_ = new QTimer;
    paintTimer_->setInterval(100);
    this->connect(paintTimer_, SIGNAL(timeout()), SLOT(repaint()));
    paintTimer_->start();

    mainImage_ = new QImage(width, height, QImage::Format_ARGB32);


    // setup McuGui
    buffer_ = new ColorFormat::data_type[width * height];
    MemoryPaintDevice<ColorFormat> device(buffer_, DISPLAY_480_272);

    device.fillRegion({0, 0}, DISPLAY_480_272, ColorFormat::fromConstant(Color::DARK_BLUE));

    QImage image1(":/png/battery_scale.png");
    auto imagePtr1 = (ColorFormat::data_type*)image1.bits();
    MemoryPaintDevice<ColorFormat>::bitmap_type volt{imagePtr1, {85, 75}};

    device.copyBitmap({0, 0}, volt);
}

MainWindow::~MainWindow()
{
    delete[] buffer_;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    ColorFormat::data_type *line;
    for(int y=0; y<height_; y++)
    {
        line=(ColorFormat::data_type*)mainImage_->scanLine(y);
        for(int x=0; x<width_; x++)
        {
            line[x]=buffer_[x+y*width_];
        }
    }
    QPainter painter(this);
    painter.drawImage(0,0,*mainImage_);
}
