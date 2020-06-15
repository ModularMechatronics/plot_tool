#ifndef PLOT_TOOL_VECTOR_MATRIX_DYNAMIC_H_
#define PLOT_TOOL_VECTOR_MATRIX_DYNAMIC_H_

#include <cmath>

#include "logging.h"
#include "math/lin_alg/matrix_dynamic/matrix_dynamic.h"
#include "math/lin_alg/vector_dynamic/vector_dynamic.h"
#include "math/lin_alg/vector_low_dim/vec2d.h"
#include "math/lin_alg/vector_low_dim/vec3d.h"
#include "math/lin_alg/vector_low_dim/vec4d.h"
#include "math/math_core.h"
#include "math/misc/math_macros.h"

namespace plot_tool
{
template <typename T> void Matrix<T>::addToAllCols(const Matrix<T>& m)
{
    ASSERT(is_allocated_) << "Matrix not allocated!";
    ASSERT(m.isAllocated()) << "Matrix not allocated!";
    ASSERT(num_rows_ == m.rows()) << "Error in dimension!";
    ASSERT(m.cols() == 1) << "Error in dimension!";

    for (size_t c = 0; c < num_cols_; c++)
    {
        for (size_t r = 0; r < num_rows_; r++)
        {
            data_[r * num_cols_ + c] = data_[r * num_cols_ + c] + m(r, 0);
        }
    }
}

template <typename T> void Matrix<T>::addToAllRows(const Matrix<T>& m)
{
    ASSERT(is_allocated_) << "Matrix not allocated!";
    ASSERT(m.isAllocated()) << "Matrix not allocated!";
    ASSERT(num_cols_ == m.cols()) << "Error in dimension!";
    ASSERT(m.rows() == 1) << "Error in dimension!";

    for (size_t r = 0; r < num_rows_; r++)
    {
        for (size_t c = 0; c < num_cols_; c++)
        {
            data_[r * num_cols_ + c] = data_[r * num_cols_ + c] + m(0, c);
        }
    }
}

template <typename T> void Matrix<T>::addToAllCols(const Vector<T>& v)
{
    ASSERT(is_allocated_) << "Matrix not allocated!";
    ASSERT(v.isAllocated()) << "Vector not allocated!";
    ASSERT(num_rows_ == v.size()) << "Error in dimension!";

    for (size_t c = 0; c < num_cols_; c++)
    {
        for (size_t r = 0; r < num_rows_; r++)
        {
            data_[r * num_cols_ + c] = data_[r * num_cols_ + c] + v(r);
        }
    }
}

template <typename T> void Matrix<T>::addToAllRows(const Vector<T>& v)
{
    ASSERT(is_allocated_) << "Matrix not allocated!";
    ASSERT(v.isAllocated()) << "Vector not allocated!";
    ASSERT(num_cols_ == v.size()) << "Error in dimension!";

    for (size_t r = 0; r < num_rows_; r++)
    {
        for (size_t c = 0; c < num_cols_; c++)
        {
            data_[r * num_cols_ + c] = data_[r * num_cols_ + c] + v(c);
        }
    }
}

template <typename T> void Matrix<T>::addToCol(const size_t col_idx, const Vector<T>& v)
{
    ASSERT(v.size() == num_rows_);
    for (size_t r = 0; r < num_rows_; r++)
    {
        data_[r * num_cols_ + col_idx] = data_[r * num_cols_ + col_idx] + v(r);
    }
}

template <typename T> void Matrix<T>::addToRow(const size_t row_idx, const Vector<T>& v)
{
    ASSERT(v.size() == num_cols_);
    for (size_t c = 0; c < num_cols_; c++)
    {
        data_[row_idx * num_cols_ + c] = data_[row_idx * num_cols_ + c] + v(c);
    }
}

template <typename T> void Matrix<T>::addToCol(const size_t col_idx, const Matrix<T>& m)
{
    ASSERT((m.rows() == 1) || (m.cols() == 1));

    if (m.rows() == 1)
    {
        ASSERT(m.cols() == num_rows_);

        for (size_t r = 0; r < num_rows_; r++)
        {
            data_[r * num_cols_ + col_idx] = data_[r * num_cols_ + col_idx] + m(0, r);
        }
    }
    else
    {
        ASSERT(m.rows() == num_rows_);

        for (size_t r = 0; r < num_rows_; r++)
        {
            data_[r * num_cols_ + col_idx] = data_[r * num_cols_ + col_idx] + m(r, 0);
        }
    }
}

template <typename T> void Matrix<T>::addToRow(const size_t row_idx, const Matrix<T>& m)
{
    ASSERT((m.rows() == 1) || (m.cols() == 1));

    if (m.rows() == 1)
    {
        ASSERT(m.cols() == num_cols_);

        for (size_t c = 0; c < num_cols_; c++)
        {
            data_[row_idx * num_cols_ + c] = data_[row_idx * num_cols_ + c] + m(0, c);
        }
    }
    else
    {
        ASSERT(m.rows() == num_cols_);

        for (size_t c = 0; c < num_cols_; c++)
        {
            data_[row_idx * num_cols_ + c] = data_[row_idx * num_cols_ + c] + m(c, 0);
        }
    }
}

template <typename T> void Matrix<T>::hCat(const Vector<T>& v)
{
    ASSERT(is_allocated_) << "Matrix not allocated!";
    ASSERT(v.isAllocated()) << "Vector not allocated!";
    ASSERT(num_rows_ == v.size()) << "Mismatch in number of cols!";

    T* temp_data;
    DATA_ALLOCATION(temp_data, num_rows_ * (num_cols_ + 1), T, "Matrix");

    for (size_t r = 0; r < num_rows_; r++)
    {
        for (size_t c = 0; c < num_rows_; c++)
        {
            temp_data[r * num_cols_ + c] = data_[r * num_cols_ + c];
        }
    }

    num_cols_ = num_cols_ + 1;

    for (size_t r = 0; r < num_rows_; r++)
    {
        temp_data[r * num_cols_ + num_cols_ - 1] = v(r);
    }

    delete[] data_;
    data_ = temp_data;
}

template <typename T> void Matrix<T>::vCat(const Vector<T>& v)
{
    ASSERT(is_allocated_) << "Matrix not allocated!";
    ASSERT(v.isAllocated()) << "Vector not allocated!";
    ASSERT(num_rows_ == v.size()) << "Mismatch in number of cols!";

    T* temp_data;
    DATA_ALLOCATION(temp_data, (num_rows_ + 1) * num_cols_, T, "Matrix");

    for (size_t r = 0; r < num_rows_; r++)
    {
        for (size_t c = 0; c < num_rows_; c++)
        {
            temp_data[r * num_cols_ + c] = data_[r * num_cols_ + c];
        }
    }

    num_rows_ = num_rows_ + 1;

    for (size_t c = 0; c < num_rows_; c++)
    {
        temp_data[(num_rows_ - 1) * num_cols_ + c] = v(c);
    }

    delete[] data_;
    data_ = temp_data;
}

template <typename T> void Matrix<T>::hCat(const Vec2D<T>& v)
{
    this->hCat(v.toVector());
}

template <typename T> void Matrix<T>::vCat(const Vec2D<T>& v)
{
    this->vCat(v.toVector());
}

template <typename T> void Matrix<T>::hCat(const Vec3D<T>& v)
{
    this->hCat(v.toVector());
}

template <typename T> void Matrix<T>::vCat(const Vec3D<T>& v)
{
    this->vCat(v.toVector());
}

template <typename T> void Matrix<T>::hCat(const Vec4D<T>& v)
{
    this->hCat(v.toVector());
}

template <typename T> void Matrix<T>::vCat(const Vec4D<T>& v)
{
    this->vCat(v.toVector());
}

template <typename T> void Matrix<T>::hCat(const Matrix<T>& m)
{
    ASSERT(is_allocated_);
    ASSERT(m.isAllocated());
    ASSERT(m.rows() == num_rows_);
    const size_t new_num_cols = num_cols_ + m.cols();

    T* temp_data;
    DATA_ALLOCATION(temp_data, num_rows_ * new_num_cols, T, "Matrix");

    for (size_t r = 0; r < num_rows_; r++)
    {
        for (size_t c = 0; c < num_cols_; c++)
        {
            temp_data[r * new_num_cols + c] = data_[r * num_cols_ + c];
        }
    }

    for (size_t r = 0; r < num_rows_; r++)
    {
        for (size_t c = num_cols_; c < new_num_cols; c++)
        {
            temp_data[r * new_num_cols + c] = m(r, c - num_cols_);
        }
    }
    delete data_;
    data_ = temp_data;
    num_cols_ = new_num_cols;
}

template <typename T> void Matrix<T>::vCat(const Matrix<T>& m)
{
    ASSERT(is_allocated_);
    ASSERT(m.isAllocated());
    ASSERT(m.cols() == num_cols_);
    const size_t new_num_rows = num_rows_ + m.rows();

    T* temp_data;
    DATA_ALLOCATION(temp_data, new_num_rows * num_cols_, T, "Matrix");

    for (size_t r = 0; r < num_rows_; r++)
    {
        for (size_t c = 0; c < num_cols_; c++)
        {
            temp_data[r * num_cols_ + c] = data_[r * num_cols_ + c];
        }
    }

    for (size_t r = num_rows_; r < new_num_rows; r++)
    {
        for (size_t c = 0; c < num_cols_; c++)
        {
            temp_data[r * num_cols_ + c] = m(r - num_rows_, c);
        }
    }
    delete data_;
    data_ = temp_data;
    num_rows_ = new_num_rows;
}

template <typename T> Matrix<T> hCat(const Matrix<T>& m, const Vector<T>& v)
{
    ASSERT(m.isAllocated()) << "Matrix not allocated!";
    ASSERT(v.isAllocated()) << "Vector not allocated!";

    ASSERT(m.rows() == v.size()) << "Mismatch in number of cols!";

    Matrix<T> mres(m.rows(), m.cols() + 1);

    for (size_t r = 0; r < m.rows(); r++)
    {
        for (size_t c = 0; c < m.cols(); c++)
        {
            mres(r, c) = m(r, c);
        }
    }

    for (size_t r = 0; r < m.rows(); r++)
    {
        mres(r, mres.lastColIdx()) = v(r);
    }

    return mres;
}

template <typename T> Matrix<T> vCat(const Matrix<T>& m, const Vector<T>& v)
{
    ASSERT(m.isAllocated()) << "Matrix not allocated!";
    ASSERT(v.isAllocated()) << "Vector not allocated!";

    ASSERT(m.cols() == v.size()) << "Mismatch in number of cols!";

    Matrix<T> mres(m.rows() + 1, m.cols());

    for (size_t r = 0; r < m.rows(); r++)
    {
        for (size_t c = 0; c < m.cols(); c++)
        {
            mres(r, c) = m(r, c);
        }
    }

    for (size_t c = 0; c < m.cols(); c++)
    {
        mres(mres.lastRowIdx(), c) = v(c);
    }

    return mres;
}

template <typename T> Matrix<T> hCat(const Vector<T>& v, const Matrix<T>& m)
{
    Matrix<T> m0(v.size(), 1);
    return vCat(m0, m);
}

template <typename T> Matrix<T> vCat(const Vector<T>& v, const Matrix<T>& m)
{
    Matrix<T> m0(1, v.size());
    return vCat(m0, m);
}

template <typename T> Matrix<T> hCat(const Matrix<T>& m, const Vec4D<T>& v)
{
    Vector<T> vg = v.toVector();
    return hCat(m, vg);
}

template <typename T> Matrix<T> vCat(const Matrix<T>& m, const Vec4D<T>& v)
{
    Vector<T> vg = v.toVector();
    return vCat(m, vg);
}

template <typename T> Matrix<T> hCat(const Matrix<T>& m, const Vec3D<T>& v)
{
    Vector<T> vg = v.toVector();
    return hCat(m, vg);
}

template <typename T> Matrix<T> vCat(const Matrix<T>& m, const Vec3D<T>& v)
{
    Vector<T> vg = v.toVector();
    return vCat(m, vg);
}

template <typename T> Matrix<T> hCat(const Matrix<T>& m, const Vec2D<T>& v)
{
    Vector<T> vg = v.toVector();
    return hCat(m, vg);
}

template <typename T> Matrix<T> vCat(const Matrix<T>& m, const Vec2D<T>& v)
{
    Vector<T> vg = v.toVector();
    return vCat(m, vg);
}

template <typename T> Matrix<T> hCat(const Vec4D<T>& v, const Matrix<T>& m)
{
    Vector<T> vg = v.toVector();
    return hCat(vg, m);
}

template <typename T> Matrix<T> vCat(const Vec4D<T>& v, const Matrix<T>& m)
{
    Vector<T> vg = v.toVector();
    return vCat(vg, m);
}

template <typename T> Matrix<T> hCat(const Vec3D<T>& v, const Matrix<T>& m)
{
    Vector<T> vg = v.toVector();
    return hCat(vg, m);
}

template <typename T> Matrix<T> vCat(const Vec3D<T>& v, const Matrix<T>& m)
{
    Vector<T> vg = v.toVector();
    return vCat(vg, m);
}

template <typename T> Matrix<T> hCat(const Vec2D<T>& v, const Matrix<T>& m)
{
    Vector<T> vg = v.toVector();
    return hCat(vg, m);
}

template <typename T> Matrix<T> vCat(const Vec2D<T>& v, const Matrix<T>& m)
{
    Vector<T> vg = v.toVector();
    return vCat(vg, m);
}

template <typename T> Matrix<T> Vector<T>::outerProduct(const Vector<T>& v) const
{
    assert(vector_length_ == v.size());
    Matrix<T> mat(vector_length_, vector_length_);

    for (size_t r = 0; r < vector_length_; r++)
    {
        for (size_t c = 0; c < vector_length_; c++)
        {
            mat(r, c) = data_[r] * v(c);
        }
    }

    return mat;
}

template <typename T> Matrix<T> Vector<T>::toColumnVectorMat() const
{
    Matrix<T> mres(vector_length_, 1);

    for (size_t r = 0; r < vector_length_; r++)
    {
        mres(r, 0) = data_[r];
    }

    return mres;
}

template <typename T> Matrix<T> Vector<T>::toRowVectorMat() const
{
    Matrix<T> mres(1, vector_length_);

    for (size_t c = 0; c < vector_length_; c++)
    {
        mres(0, c) = data_[c];
    }

    return mres;
}

// Vec234D

template <typename T> Matrix<T> Vec2D<T>::outerProduct(const Vec2D<T>& v) const
{
    Vector<T> vv0 = toVector();
    Vector<T> vv1 = v.toVector();

    return vv0.outerProduct(vv1);
}

template <typename T> Matrix<T> Vec3D<T>::outerProduct(const Vec3D<T>& v) const
{
    Vector<T> vv0 = toVector();
    Vector<T> vv1 = v.toVector();

    return vv0.outerProduct(vv1);
}

template <typename T> Vec4D<T> Vector<T>::toVec4D() const
{
    ASSERT(is_allocated_) << "Error, parent vector not allocated!";
    ASSERT(vector_length_ >= 4) << "Error, parent vector not of size 4 or larger!";
    Vec4D<T> v(data_[0], data_[1], data_[2], data_[3]);
    return v;
}

template <typename T> Vec3D<T> Vector<T>::toVec3D() const
{
    ASSERT(is_allocated_) << "Error, parent vector not allocated!";
    ASSERT(vector_length_ >= 3) << "Error, parent vector not of size 3 or larger!";
    Vec3D<T> v(data_[0], data_[1], data_[2]);
    return v;
}

template <typename T> Vec2D<T> Vector<T>::toVec2D() const
{
    ASSERT(is_allocated_) << "Error, parent vector not allocated!";
    ASSERT(vector_length_ >= 2) << "Error, parent vector not of size 2 or larger!";
    Vec2D<T> v(data_[0], data_[1]);
    return v;
}

template <typename T> Matrix<T> Vec4D<T>::outerProduct(const Vec4D<T>& v) const
{
    Vector<T> vv0 = toVector();
    Vector<T> vv1 = v.toVector();

    return vv0.outerProduct(vv1);
}

template <typename T> Vector<T> Vec2D<T>::toVector() const
{
    const Vector<T> v({x, y});
    return v;
}

template <typename T> Vector<T> Vec3D<T>::toVector() const
{
    const Vector<T> v({x, y, z});
    return v;
}

template <typename T> Vector<T> Vec4D<T>::toVector() const
{
    const Vector<T> v({x, y, z, w});
    return v;
}

template <typename T> Matrix<T> Vec3D<T>::toCrossProductMatrix() const
{
    Matrix<T> m(3, 3);
    m(0, 0) = 0.0;
    m(0, 1) = -z;
    m(0, 2) = y;

    m(1, 0) = z;
    m(1, 1) = 0.0;
    m(1, 2) = -x;

    m(2, 0) = -y;
    m(2, 1) = x;
    m(2, 2) = 0.0;
    return m;
}

template <typename T> Vec3D<T> crossProductMatrixToVec3D(const Matrix<T>& m)
{
    return Vec3D<T>(m(2, 1), m(0, 2), m(1, 0));
}

template <typename T>
AxisAngle<T> estimateRotationFromTwoVectors(const Vec3D<T>& v_unrotated, const Vec3D<T>& v_rotated)
{
    Vec3D<T> rotation_vector = v_unrotated.crossProduct(v_rotated);
    T phi = v_unrotated.angleBetweenVectors(v_rotated);

    return AxisAngle<T>(phi, rotation_vector.x, rotation_vector.y, rotation_vector.z);
}

}  // namespace plot_tool

#endif
