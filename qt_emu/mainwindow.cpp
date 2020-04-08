#include "mainwindow.h"

#include <QPainter>
#include <QTimer>

#include "../mcu_gui/core/font/font.h"

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

    MemoryPaintEngine engine(buffer_);
    SimplePainter painter(engine);

    TransformedPainter painter2(painter, TransformMatrix::rotate(0) * TransformMatrix::move(300, 100));
    painter2.drawPoint({0, 0});
    Label lbl("A B", FontType::MONOTYPE_MID_FONT);
    lbl.paint(painter2);

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
