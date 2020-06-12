#include "mainwindow.h"

#include <QPainter>
#include <QTimer>

#include "../mcu_gui/app/dashboard/dashboard_typ1.h"

using namespace McuGui;

MainWindow::MainWindow(uint16_t width, uint16_t height)
    : QMainWindow(nullptr), height_(height), width_(width)
{
    this->setFixedSize(width, height);

    paintTimer_ = new QTimer;
    paintTimer_->setInterval(100);
    this->connect(paintTimer_, SIGNAL(timeout()), SLOT(repaint()));
    paintTimer_->start();

    mainImage_ = new QImage(width, height, QImage::Format_Indexed8);

    QVector<QRgb> colortable(256);
    auto rawTable = getColorTable();
    for(int i = 0; i < 256; ++i) {
        QRgb val = rawTable[i] | 0xFF000000;
        colortable[i] = val;
    }
    mainImage_->setColorTable(colortable);
    buffer_ = new McuGui::Color[width * height];
    for(auto i = 0; i< width * height; ++i) buffer_[i] = COLOR_BLACK;

    MemoryPaintEngine engine(buffer_);
    SimplePainter painter(engine);
    MovedPainter pnt(painter, 200, 100);

    SegmentIndicator ind1(DigitSegment::Mid, COLOR_GREY);
    SegmentIndicator ind2(DigitSegment::Mid, COLOR_BROWN);
    ind1.setValue(8);
    ind2.setValue(8);
    ind1.paint(pnt);
    pnt.move(40, 0);
    ind2.paint(pnt);

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
    mainImage_->save("./image.png");
}
