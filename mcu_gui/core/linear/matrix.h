#ifndef MATRIX_H
#define MATRIX_H

#include "../types.h"
#include <initializer_list>
#include <vector>

namespace McuGui {

template <typename T> class AbstractMatrix {
public:
    typedef uint8_t SizeType;
    AbstractMatrix(AbstractMatrix& other) = default;

    AbstractMatrix(SizeType rows, SizeType cols): rows_(rows), cols_(cols) {
        data_ = new T[rows*cols];
        for (size_t i = 0; i < rows * cols; ++i) data_[i] = 0;
    }
    AbstractMatrix(SizeType rows, SizeType cols, std::initializer_list<T> vals)
        :AbstractMatrix(rows, cols)
    {
        size_t val_num = rows * cols > vals.size() ? vals.size() : rows * cols;
        auto it = vals.begin();
        for (size_t i = 0; i < val_num; ++i) data_[i] = *(it++);
    }
    virtual ~AbstractMatrix() {
        delete[] data_;
    }
    SizeType rows() const { return rows_; }
    SizeType cols() const { return cols_; }
    T getAt(SizeType row, SizeType col) const {
        if (outOfBounds(row, col)) return 0;
        return data_[calculateOffset(row, col)];
    }
    void setAt(SizeType row, SizeType col, T val) {
        if (outOfBounds(row, col)) return;
        data_[calculateOffset(row, col)] = val;
    }

    AbstractMatrix<T> operator* (const AbstractMatrix<T>& other) {
        AbstractMatrix<T> result(rows_, other.cols_);
        for (SizeType i = 0; i < rows_; ++i) {
            T* c = result.data_ + i * other.cols_;
            for (SizeType j = 0; j < other.cols_; ++j) c[j] = 0;
            for (SizeType k = 0; k < other.rows_; ++k) {
                const T* b = other.data_ + k * other.cols_;
                T a = data_[i*cols_ + k];
                for (SizeType j = 0; j < other.rows(); ++j)
                    c[j] += a * b[j];
            }
        }
        return result;
    }

    static AbstractMatrix<T> identityMatrix(SizeType size) {
        AbstractMatrix<T> result(size, size);
        for (SizeType i = 0; i < size; ++i) result.setAt(i, i, 1);
    }

    static AbstractMatrix<T> fromVertexes(std::vector<Position> verts) {
        AbstractMatrix<T> result(verts.size(), 3);
        size_t index = 0;
        for (auto vert: verts) {
            result.data_[index++] = (T)vert.x;
            result.data_[index++] = (T)vert.y;
            result.data_[index++] = 1;
        }
        return result;
    }

    std::vector<Position> toVertexes() const {
        std::vector<Position> result(rows_);
        size_t offset = 0;
        for(SizeType i = 0; i < rows_; ++i) {
            result[i] = {(CoordType)data_[offset++], (CoordType)data_[offset++]};
            ++offset; // to skip 3d component in vector
        }
        return result;
    }


protected:
    SizeType rows_;
    SizeType cols_;
    bool outOfBounds(SizeType row, SizeType col) const {
        return row >= rows_ || col >= cols_;
    }
    size_t calculateOffset(SizeType row, SizeType col) const {
        return col + rows_ * row;
    }
    T* data_;
};

typedef AbstractMatrix<float> FloatMatrix;

struct TransformMatrix: public FloatMatrix {
    TransformMatrix():FloatMatrix(3,3, {1,0,0,0,1,0,0,0,1}) {} // no transform by default
    TransformMatrix(std::initializer_list<float> list): FloatMatrix(3,3, list) {}

    static TransformMatrix move(CoordType x, CoordType y);
    static TransformMatrix rotate(float angle);
};

} // end namespace McuGui



#endif // MATRIX_H
