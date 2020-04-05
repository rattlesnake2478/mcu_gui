#include "mainwindow.h"

#include <QPainter>
#include <QTimer>

#include "../mcu_gui/app/gauges/lamp.h"
#include "../mcu_gui/core/layout.h"
#include "../mcu_gui/core/linear/matrix.h"

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

    const Triangle tr{{0, 20}, {10, 20}, {5, 0}};


    auto verts = FloatMatrix::fromVertexes({tr.p1.pos(), tr.p2.pos(), tr.p3.pos()});
    auto move = TransformMatrix::move(50, 100);
    auto rotate = TransformMatrix::rotate(45);
    auto result = verts * rotate * move;
    auto newVerts = result.toVertexes();

    MemoryPainter painter(buffer_);
    painter.setPen(COLOR_RED);
    painter.draw(Triangle{Point{newVerts[0]}, Point{newVerts[1]}, Point{newVerts[2]}});


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
