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

    mainImage_ = new QImage(width, height, QImage::Format_ARGB32);
    buffer_ = new McuGui::Color[width * height];
    for(auto i = 0; i< width * height; ++i) buffer_[i] = COLOR_BLACK;

    MemoryPaintEngine engine(buffer_);
    SimplePainter painter(engine);

    QImage image1(":/png/battery_scale.png");
    auto imagePtr1 = (Color*)image1.bits();
    Bitmap volt{imagePtr1, {85, 75}};

    QImage image2(":/png/temp_scale.png");
    auto imagePtr2 = (Color*)image2.bits();
    Bitmap temp{imagePtr2, {85, 75}};

    QImage image3(":/png/typ1.png");
    auto imagePtr3 = (Color*)image3.bits();
    Bitmap tach{imagePtr3, {460, 220}};

    DashboardType1::Data data;
    data.tach = 10000;
    data.hrs=23;
    data.min=30;
    data.temp=120;
    data.voltage=14.5;
    data.speed=89;

    data.lamps.ltl = true;

    DashboardType1 dash(tach, temp, volt);
    dash.setData(data);
    dash.paint(painter);
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
