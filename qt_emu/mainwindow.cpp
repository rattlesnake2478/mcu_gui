#include "mainwindow.h"

#include <QPainter>
#include <QTimer>

#include "../mcu_gui/app/components/label.h"
#include "../mcu_gui/app/gauges/segment_indicator.h"
#include "../mcu_gui/core/layout.h"
#include "../mcu_gui/app/gauges/lamp.h"
#include "../mcu_gui/app/gauges/arrow_indicator.h"

using namespace McuGui;

MainWindow::MainWindow(uint16_t width, uint16_t height)
    : QMainWindow(nullptr), height_(height), width_(width)
{
    this->setFixedSize(width, height);

    paintTimer_ = new QTimer;
    paintTimer_->setInterval(100);
    this->connect(paintTimer_, SIGNAL(timeout()), SLOT(repaint()));
    paintTimer_->start();

    mainImage_ = new QImage(width, height, QImage::Format_ARGB32);
    buffer_ = new McuGui::Color[width * height];
    for(auto i = 0; i< width * height; ++i) buffer_[i] = COLOR_BLACK;

    MemoryPaintEngine engine(buffer_);
    SimplePainter painter(engine);

    drawDash(painter);
}

void
MainWindow::drawDash(PainterInterface& painter) {
    MovedPainter pnt(painter, 470, 260);
    MultiSegmentIndicator ind(DigitSegment::Huge, COLOR_BLUE, COLOR_WHITE);

    ind.setValue(128);
    ind.paint(pnt);

    LeftTurnLamp ltl;
    RightTurnLamp rtl;
    NeutralLamp nl;
    HighBeamLamp hbl;
    BatteryLamp bl;
    TempLamp tl;

    ltl.setValue(true);
    rtl.setValue(true);
    nl.setValue(true);
    hbl.setValue(true);
    bl.setValue(true);
    tl.setValue(true);

    MovedPainter pnt2(painter, -5, 0);
    MovedPainter pnt3(painter, 334, 0);

    HLayout llayout(Lamp::StandartDimension, 3, 5);
    HLayout rlayout(Lamp::StandartDimension, 3, 5);
    llayout.addWidget(&ltl, 0);
    llayout.addWidget(&nl, 1);
    llayout.addWidget(&bl, 2);
    rlayout.addWidget(&tl, 0);
    rlayout.addWidget(&hbl, 1);
    rlayout.addWidget(&rtl, 2);

    llayout.paint(pnt2);
    rlayout.paint(pnt3);

    QImage image1(":/png/battery_scale.png");
    auto imagePtr1 = (Color*)image1.bits();
    Bitmap bitmap1{imagePtr1, {85, 75}};

    QImage image2(":/png/temp_scale.png");
    auto imagePtr2 = (Color*)image2.bits();
    Bitmap bitmap2{imagePtr2, {85, 75}};

    MovedPainter pnt4(painter, 120, 185);
    auto temp = ArrowIndicator::buildArrowA(bitmap1, 60, 130, false);
    temp.setValue(90);
    temp.paint(pnt4);

    auto bat = ArrowIndicator::buildArrowA(bitmap2, 10, 18, true);
    pnt4.move(0, -90);
    bat.setValue(15.1);
    bat.paint(pnt4);

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
