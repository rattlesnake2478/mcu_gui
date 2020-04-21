#ifndef LAYOUT_H
#define LAYOUT_H

#include "widget.h"

namespace McuGui {

class GridLayout: public WidgetContainer {
public:
    GridLayout(Dimension cell_size, uint8_t rows = 4, uint8_t cols = 4, Dimension margin = {10, 10}):
        cell_size_(cell_size),
        rows_(rows),
        cols_(cols),
        margin_(margin)
    {};

    bool addWidget(const AbstractWidget* w, uint8_t row, uint8_t col) {
        if (row >= rows_) return false;
        if (col >= cols_) return false;
        Position pos = getPosition(row, col);
        addElement(w, pos);
        return true;
    };

protected:
    Position getPosition(uint8_t row, uint8_t col) const;
    Dimension cell_size_;
    uint8_t rows_;
    uint8_t cols_;
    Dimension margin_;
};

class HLayout: public GridLayout {
public:
    HLayout(Dimension cell_size, uint8_t cols = 4, SizeType margin = 10):
        GridLayout(cell_size, 1, cols, {margin, 0})
    {};

    bool addWidget(const AbstractWidget* w, uint8_t col) {
        return GridLayout::addWidget(w, 0, col);
    }
};

class VLayout: public GridLayout {
public:
    VLayout(Dimension cell_size, uint8_t rows = 4, SizeType margin = 10):
        GridLayout(cell_size, rows, 1, {margin, 0})
    {};

    bool addWidget(const AbstractWidget* w, uint8_t row) {
        return GridLayout::addWidget(w, row, 0);
    }
};

} // End namespace McuGui

#endif // LAYOUT_H
