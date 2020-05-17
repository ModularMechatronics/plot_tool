
#ifndef MATRIX_DYNAMIC_H_
#define MATRIX_DYNAMIC_H_

#include <cmath>

#include "logging.h"
#include "math/math_core.h"
#include "math/misc/math_macros.h"

namespace plot_tool
{
template <typename T> Matrix<T>& Matrix<T>::operator=(const Matrix<T>& m)
{
    ASSERT(m.isAllocated()) << "Input matrix not allocated before assignment!";
    if (this != &m)
    {
        if (is_allocated_)
        {
            if ((m.rows() != num_rows_) || (m.cols() != num_cols_))
            {
                delete[] data_;
                DATA_ALLOCATION(data_, m.rows() * m.cols(), T, "Matrix");
            }
        }
        else
        {
            DATA_ALLOCATION(data_, m.rows() * m.cols(), T, "Matrix");
        }

        num_rows_ = m.rows();
        num_cols_ = m.cols();

        for (size_t r = 0; r < m.rows(); r++)
        {
            for (size_t c = 0; c < m.cols(); c++)
            {
                data_[r * num_cols_ + c] = m(r, c);
            }
        }

        is_allocated_ = true;
    }
    return *this;
}

template <typename T> Matrix<T>::Matrix(const T a[3][3])
{
    is_allocated_ = true;
    num_rows_ = 3;
    num_cols_ = 3;

    DATA_ALLOCATION(data_, 9, T, "Matrix");
    for (size_t r = 0; r < 3; r++)
    {
        for (size_t c = 0; c < 3; c++)
        {
            data_[r * 3 + c] = a[r][c];
        }
    }
}

template <typename T> Matrix<T>::Matrix(Matrix<T>&& m)
{
    ASSERT(m.isAllocated()) << "Input matrix not allocated!";
    data_ = m.getDataPointer();
    num_rows_ = m.rows();
    num_cols_ = m.cols();

    is_allocated_ = true;
    m.setInternalData(nullptr, 0, 0);
}

template <typename T> Matrix<T>&& Matrix<T>::move()
{
    return std::move(*this);
}

template <typename T> Matrix<T>& Matrix<T>::operator=(Matrix<T>&& m)
{
    if (this != &m)
    {
        ASSERT(m.isAllocated()) << "Input matrix not allocated before assignment!";

        if (is_allocated_)
        {
            delete[] data_;
        }

        num_rows_ = m.rows();
        num_cols_ = m.cols();
        is_allocated_ = true;

        data_ = m.getDataPointer();

        m.setInternalData(nullptr, 0, 0);
    }

    return *this;
}

template <typename T> Matrix<T> rotationMatrixX(const T angle)
{
    const T ca = std::cos(angle);
    const T sa = std::sin(angle);
    Matrix<T> rotation_matrix(3, 3);

    rotation_matrix(0, 0) = 1.0;
    rotation_matrix(0, 1) = 0.0;
    rotation_matrix(0, 2) = 0.0;

    rotation_matrix(1, 0) = 0.0;
    rotation_matrix(1, 1) = ca;
    rotation_matrix(1, 2) = -sa;

    rotation_matrix(2, 0) = 0.0;
    rotation_matrix(2, 1) = sa;
    rotation_matrix(2, 2) = ca;

    return rotation_matrix;
}

template <typename T> Matrix<T> rotationMatrixY(const T angle)
{
    const T ca = std::cos(angle);
    const T sa = std::sin(angle);
    Matrix<T> rotation_matrix(3, 3);

    rotation_matrix(0, 0) = ca;
    rotation_matrix(0, 1) = 0.0;
    rotation_matrix(0, 2) = sa;

    rotation_matrix(1, 0) = 0.0;
    rotation_matrix(1, 1) = 1.0;
    rotation_matrix(1, 2) = 0.0;

    rotation_matrix(2, 0) = -sa;
    rotation_matrix(2, 1) = 0.0;
    rotation_matrix(2, 2) = ca;

    return rotation_matrix;
}

template <typename T> Matrix<T> rotationMatrixZ(const T angle)
{
    const T ca = std::cos(angle);
    const T sa = std::sin(angle);
    Matrix<T> rotation_matrix(3, 3);

    rotation_matrix(0, 0) = ca;
    rotation_matrix(0, 1) = -sa;
    rotation_matrix(0, 2) = 0.0;

    rotation_matrix(1, 0) = sa;
    rotation_matrix(1, 1) = ca;
    rotation_matrix(1, 2) = 0.0;

    rotation_matrix(2, 0) = 0.0;
    rotation_matrix(2, 1) = 0.0;
    rotation_matrix(2, 2) = 1.0;

    return rotation_matrix;
}

template <typename T> Matrix<T> rotationMatrix2D(const T angle)
{
    const T ca = std::cos(angle);
    const T sa = std::sin(angle);
    Matrix<T> rotation_matrix(2, 2);

    rotation_matrix(0, 0) = ca;
    rotation_matrix(0, 1) = -sa;

    rotation_matrix(1, 0) = sa;
    rotation_matrix(1, 1) = ca;

    return rotation_matrix;
}

template <typename T>
Matrix<T>::Matrix() : data_(nullptr), num_rows_(0), num_cols_(0), is_allocated_(false)
{
}

template <typename T>
Matrix<T>::Matrix(const size_t num_rows, const size_t num_cols) : is_allocated_(true)
{
    num_rows_ = num_rows;
    num_cols_ = num_cols;

    DATA_ALLOCATION(data_, num_rows_ * num_cols_, T, "Matrix");
}

template <typename T> Matrix<T>::Matrix(const Matrix<T>& m) : is_allocated_(true)
{
    num_rows_ = m.rows();
    num_cols_ = m.cols();

    DATA_ALLOCATION(data_, m.rows() * m.cols(), T, "Matrix");
    for (size_t r = 0; r < m.rows(); r++)
    {
        for (size_t c = 0; c < m.cols(); c++)
        {
            data_[r * m.cols() + c] = m(r, c);
        }
    }
}

template <typename T> Matrix<T>::Matrix(const std::initializer_list<std::initializer_list<T>>& il)
{
    ASSERT(il.size() > 0) << "Tried to initialize with empty vector matrix!";
    ASSERT(il.begin()[0].size() > 0) << "Tried to initialize with empty vector matrix!";

    for (size_t r = 0; r < il.size(); r++)
    {
        ASSERT(il.begin()[0].size() == il.begin()[r].size())
            << "All row vectors in input std vectors do not have the same size!";
    }

    num_rows_ = il.size();
    num_cols_ = il.begin()[0].size();

    DATA_ALLOCATION(data_, num_cols_ * num_rows_, T, "Matrix");
    is_allocated_ = true;

    for (size_t r = 0; r < il.size(); r++)
    {
        for (size_t c = 0; c < il.begin()[r].size(); c++)
        {
            data_[r * num_cols_ + c] = il.begin()[r].begin()[c];
        }
    }
}

template <typename T> Matrix<T>::Matrix(const std::vector<std::vector<T>>& vm)
{
    ASSERT(vm.size() > 0) << "Tried to initialize with empty vector matrix!";
    ASSERT(vm[0].size() > 0) << "Tried to initialize with empty vector matrix!";

    for (size_t r = 0; r < vm.size(); r++)
    {
        ASSERT(vm[0].size() == vm[r].size())
            << "All row vectors in input std vectors do not have the same size!";
    }

    num_rows_ = vm.size();
    num_cols_ = vm[0].size();

    DATA_ALLOCATION(data_, num_cols_ * num_rows_, T, "Matrix");
    is_allocated_ = true;

    for (size_t r = 0; r < vm.size(); r++)
    {
        for (size_t c = 0; c < vm[r].size(); c++)
        {
            data_[r * num_cols_ + c] = vm[r][c];
        }
    }
}

template <typename T> Matrix<T>::~Matrix()
{
    if (is_allocated_)
    {
        delete[] data_;
        is_allocated_ = false;
    }
}

template <typename T> void Matrix<T>::resize(const size_t num_rows, const size_t num_cols)
{
    if (is_allocated_)
    {
        delete[] data_;
        is_allocated_ = false;
    }

    num_rows_ = num_rows;
    num_cols_ = num_cols;

    DATA_ALLOCATION(data_, num_rows_ * num_cols_, T, "Matrix");
    is_allocated_ = true;
}

template <typename T> void Matrix<T>::switchRows(size_t r0, size_t r1)
{
    assert(r0 < num_rows_ && r1 < num_rows_);
    if (r0 == r1)
    {
        std::cout << "WARNING: When calling \"switchRows\", you tried to switch a row with itself!"
                  << std::endl;
    }

    T tmp_var;
    for (size_t c = 0; c < num_cols_; c++)
    {
        tmp_var = data_[num_cols_ * r0 + c];
        data_[num_cols_ * r0 + c] = data_[num_cols_ * r1 + c];
        data_[num_cols_ * r1 + c] = tmp_var;
    }
}

template <typename T> void Matrix<T>::switchColumns(size_t c0, size_t c1)
{
    assert(c0 < num_cols_ && c1 < num_cols_);
    if (c0 == c1)
    {
        std::cout
            << "WARNING: When calling \"swithCols\", you tried to switch a column with itself!"
            << std::endl;
    }

    T tmp_var;
    for (size_t r = 0; r < num_rows_; r++)
    {
        tmp_var = data_[num_cols_ * r + c0];
        data_[num_cols_ * r + c0] = data_[num_cols_ * r + c1];
        data_[num_cols_ * r + c1] = tmp_var;
    }
}

template <typename T>
void Matrix<T>::setInternalData(T* const input_ptr, const size_t num_rows, const size_t num_cols)
{
    if (input_ptr == nullptr)
    {
        is_allocated_ = false;
    }
    else
    {
        is_allocated_ = true;
    }

    data_ = input_ptr;
    num_rows_ = num_rows;
    num_cols_ = num_cols;
}

template <typename T> T* Matrix<T>::getDataPointer() const
{
    return data_;
}

template <typename T> Matrix<T> vCat(const Matrix<T>& m0, const Matrix<T>& m1)
{
    ASSERT(m0.isAllocated()) << "m0 is not allocated!";
    ASSERT(m1.isAllocated()) << "m1 is not allocated!";
    ASSERT(m0.cols() == m1.cols()) << "Mismatch in number of cols!";

    Matrix<T> mres(m0.rows() + m1.rows(), m0.cols());

    for (size_t r = 0; r < m0.rows(); r++)
    {
        for (size_t c = 0; c < m0.cols(); c++)
        {
            mres(r, c) = m0(r, c);
        }
    }

    for (size_t r = m0.rows(); r < mres.rows(); r++)
    {
        for (size_t c = 0; c < m0.cols(); c++)
        {
            mres(r, c) = m1(r - m0.rows(), c);
        }
    }

    return mres;
}

template <typename T> Matrix<T> hCat(const Matrix<T>& m0, const Matrix<T>& m1)
{
    ASSERT(m0.isAllocated()) << "m0 is not allocated!";
    ASSERT(m1.isAllocated()) << "m1 is not allocated!";
    ASSERT(m0.rows() == m1.rows()) << "Mismatch in number of cols!";

    Matrix<T> mres(m0.rows(), m0.cols() + m1.cols());

    for (size_t r = 0; r < m0.rows(); r++)
    {
        for (size_t c = 0; c < m0.cols(); c++)
        {
            mres(r, c) = m0(r, c);
        }
    }

    for (size_t r = 0; r < m0.rows(); r++)
    {
        for (size_t c = m0.cols(); c < mres.cols(); c++)
        {
            mres(r, c) = m1(r, c - m0.cols());
        }
    }

    return mres;
}

template <typename T> size_t Matrix<T>::lastRowIdx() const
{
    return num_rows_ - 1;
}

template <typename T> size_t Matrix<T>::lastColIdx() const
{
    return num_cols_ - 1;
}

template <typename T> size_t Matrix<T>::rows() const
{
    return num_rows_;
}

template <typename T> size_t Matrix<T>::cols() const
{
    return num_cols_;
}

template <typename T> size_t Matrix<T>::numElements() const
{
    // Returns totalt number of elements in matrix
    return num_rows_ * num_cols_;
}

template <typename T> bool Matrix<T>::isAllocated() const
{
    return is_allocated_;
}

template <typename T> void Matrix<T>::fill(T val)
{
    assert(is_allocated_ && "Tried to fill un allocated vector!");
    for (size_t k = 0; k < num_rows_ * num_cols_; k++)
    {
        data_[k] = val;
    }
}

template <typename T> T& Matrix<T>::operator()(const size_t idx)
{
    assert(idx < (num_cols_ * num_cols_));
    return data_[idx];
}

template <typename T> const T& Matrix<T>::operator()(const size_t idx) const
{
    assert(idx < (num_cols_ * num_cols_));
    return data_[idx];
}

template <typename T> T& Matrix<T>::operator()(const size_t r, const size_t c)
{
    assert(r < num_rows_ && "Row index is larger than num_rows_-1!");
    assert(c < num_cols_ && "Column index is larger than num_cols_-1!");

    return data_[r * num_cols_ + c];
}

template <typename T> const T& Matrix<T>::operator()(const size_t r, const size_t c) const
{
    assert(r < num_rows_ && "Row index is larger than num_rows_-1!");
    assert(c < num_cols_ && "Column index is larger than num_cols_-1!");

    return data_[r * num_cols_ + c];
}

template <typename T> T& Matrix<T>::operator()(const EndIndex& row_end_idx, const size_t c)
{
    const size_t row_idx =
        static_cast<size_t>(static_cast<int>(num_rows_) - 1 + row_end_idx.offset);
    assert((row_idx < num_rows_) && is_allocated_);
    return data_[row_idx * num_cols_ + c];
}

template <typename T>
const T& Matrix<T>::operator()(const EndIndex& row_end_idx, const size_t c) const
{
    const size_t row_idx =
        static_cast<size_t>(static_cast<int>(num_rows_) - 1 + row_end_idx.offset);
    assert((row_idx < num_rows_) && is_allocated_);
    return data_[row_idx * num_cols_ + c];
}

template <typename T> T& Matrix<T>::operator()(const size_t r, const EndIndex& col_end_idx)
{
    const size_t col_idx =
        static_cast<size_t>(static_cast<int>(num_cols_) - 1 + col_end_idx.offset);
    assert((col_idx < num_cols_) && is_allocated_);
    return data_[r * num_cols_ + col_idx];
}

template <typename T>
const T& Matrix<T>::operator()(const size_t r, const EndIndex& col_end_idx) const
{
    const size_t col_idx =
        static_cast<size_t>(static_cast<int>(num_cols_) - 1 + col_end_idx.offset);
    assert((col_idx < num_cols_) && is_allocated_);
    return data_[r * num_cols_ + col_idx];
}

template <typename T>
Matrix<T> Matrix<T>::operator()(const IndexSpan& row_idx_span, const IndexSpan& col_idx_span) const
{
    const size_t new_num_rows = row_idx_span.to - row_idx_span.from + 1;
    const size_t new_num_cols = col_idx_span.to - col_idx_span.from + 1;
    assert((row_idx_span.to < num_rows_) && (col_idx_span.to < num_cols_));
    Matrix<T> mat(new_num_rows, new_num_cols);

    for (size_t r = 0; r < new_num_rows; r++)
    {
        for (size_t c = 0; c < new_num_cols; c++)
        {
            mat(r, c) = data_[(row_idx_span.from + r) * num_cols_ + c + col_idx_span.from];
        }
    }
    return mat;
}

template <typename T>
Matrix<T> Matrix<T>::operator()(const size_t row, const IndexSpan& col_idx_span) const
{
    const size_t new_vec_length = col_idx_span.to - col_idx_span.from + 1;

    assert((row < num_rows_) && (col_idx_span.to < num_cols_));

    Matrix<T> mat(1, new_vec_length);

    for (size_t c = 0; c < new_vec_length; c++)
    {
        mat(0, c) = data_[row * num_cols_ + c + col_idx_span.from];
    }

    return mat;
}

template <typename T>
Matrix<T> Matrix<T>::operator()(const IndexSpan& row_idx_span, const size_t col) const
{
    const size_t new_vec_length = row_idx_span.to - row_idx_span.from + 1;

    assert((row_idx_span.to < num_rows_) && (col < num_cols_));

    Matrix<T> mat(new_vec_length, 1);

    for (size_t r = 0; r < new_vec_length; r++)
    {
        mat(r, 0) = data_[(r + row_idx_span.from) * num_cols_ + col];
    }

    return mat;
}

template <typename T> Matrix<T> operator*(const Matrix<T>& m0, const Matrix<T>& m1)
{
    assert(m0.cols() == m1.rows());
    Matrix<T> res(m0.rows(), m1.cols());

    for (size_t r = 0; r < res.rows(); r++)
    {
        for (size_t c = 0; c < res.cols(); c++)
        {
            T p = 0.0f;
            for (size_t i = 0; i < m0.cols(); i++)
            {
                p = p + m0(r, i) * m1(i, c);
            }
            res(r, c) = p;
        }
    }
    return res;
}

template <typename T> Matrix<T> operator+(const Matrix<T>& m0, const Matrix<T>& m1)
{
    assert(m0.cols() == m1.cols());
    assert(m0.rows() == m1.rows());
    Matrix<T> res(m0.rows(), m1.cols());

    for (size_t r = 0; r < res.rows(); r++)
    {
        for (size_t c = 0; c < res.cols(); c++)
        {
            res(r, c) = m0(r, c) + m1(r, c);
        }
    }
    return res;
}

template <typename T> Matrix<T> operator-(const Matrix<T>& m0, const Matrix<T>& m1)
{
    assert(m0.cols() == m1.cols());
    assert(m0.rows() == m1.rows());
    Matrix<T> res(m0.rows(), m1.cols());

    for (size_t r = 0; r < res.rows(); r++)
    {
        for (size_t c = 0; c < res.cols(); c++)
        {
            res(r, c) = m0(r, c) - m1(r, c);
        }
    }
    return res;
}

template <typename T> Matrix<T> operator*(const Matrix<T>& m, const T f)
{
    Matrix<T> res(m.rows(), m.cols());

    for (size_t r = 0; r < res.rows(); r++)
    {
        for (size_t c = 0; c < res.cols(); c++)
        {
            res(r, c) = f * m(r, c);
        }
    }
    return res;
}

template <typename T> Matrix<T> operator*(const T f, const Matrix<T>& m)
{
    Matrix<T> res(m.rows(), m.cols());

    for (size_t r = 0; r < res.rows(); r++)
    {
        for (size_t c = 0; c < res.cols(); c++)
        {
            res(r, c) = f * m(r, c);
        }
    }
    return res;
}

template <typename T> Matrix<T> operator^(const Matrix<T>& m0, const Matrix<T>& m1)
{
    ASSERT(m0.rows() == m1.rows());
    ASSERT(m0.cols() == m1.cols());

    Matrix<T> res(m0.rows(), m0.cols());

    for (size_t r = 0; r < res.rows(); r++)
    {
        for (size_t c = 0; c < res.cols(); c++)
        {
            res(r, c) = m0(r, c) * m1(r, c);
        }
    }
    return res;
}

template <typename T> Matrix<T> operator/(const Matrix<T>& m0, const Matrix<T>& m1)
{
    ASSERT(m0.rows() == m1.rows());
    ASSERT(m0.cols() == m1.cols());

    Matrix<T> res(m0.rows(), m0.cols());

    for (size_t r = 0; r < res.rows(); r++)
    {
        for (size_t c = 0; c < res.cols(); c++)
        {
            res(r, c) = m0(r, c) / m1(r, c);
        }
    }
    return res;
}

template <typename T> Matrix<T> operator/(const Matrix<T>& m, const T f)
{
    Matrix<T> res(m.rows(), m.cols());

    for (size_t r = 0; r < res.rows(); r++)
    {
        for (size_t c = 0; c < res.cols(); c++)
        {
            res(r, c) = m(r, c) / f;
        }
    }
    return res;
}

template <typename T> Matrix<T> operator/(const T f, const Matrix<T>& m)
{
    Matrix<T> res(m.rows(), m.cols());

    for (size_t r = 0; r < res.rows(); r++)
    {
        for (size_t c = 0; c < res.cols(); c++)
        {
            res(r, c) = f / m(r, c);
        }
    }
    return res;
}

template <typename T> Matrix<T> operator-(const Matrix<T>& m, const T f)
{
    Matrix<T> res(m.rows(), m.cols());

    for (size_t r = 0; r < res.rows(); r++)
    {
        for (size_t c = 0; c < res.cols(); c++)
        {
            res(r, c) = m(r, c) - f;
        }
    }
    return res;
}

template <typename T> Matrix<T> operator-(const T f, const Matrix<T>& m)
{
    Matrix<T> res(m.rows(), m.cols());

    for (size_t r = 0; r < res.rows(); r++)
    {
        for (size_t c = 0; c < res.cols(); c++)
        {
            res(r, c) = f - m(r, c);
        }
    }
    return res;
}

template <typename T> Matrix<T> operator+(const Matrix<T>& m, const T f)
{
    Matrix<T> res(m.rows(), m.cols());

    for (size_t r = 0; r < res.rows(); r++)
    {
        for (size_t c = 0; c < res.cols(); c++)
        {
            res(r, c) = m(r, c) + f;
        }
    }
    return res;
}

template <typename T> Matrix<T> operator+(const T f, const Matrix<T>& m)
{
    Matrix<T> res(m.rows(), m.cols());

    for (size_t r = 0; r < res.rows(); r++)
    {
        for (size_t c = 0; c < res.cols(); c++)
        {
            res(r, c) = m(r, c) + f;
        }
    }
    return res;
}

template <typename T> Matrix<T> operator-(const Matrix<T>& m)
{
    Matrix<T> res(m.rows(), m.cols());

    for (size_t r = 0; r < res.rows(); r++)
    {
        for (size_t c = 0; c < res.cols(); c++)
        {
            res(r, c) = -m(r, c);
        }
    }
    return res;
}

template <typename T> Vector<T> operator*(const Matrix<T>& m, const Vector<T>& v)
{
    assert(m.cols() == v.size());
    Vector<T> res(m.rows());

    for (size_t r = 0; r < m.rows(); r++)
    {
        T p = 0.0f;
        for (size_t c = 0; c < m.cols(); c++)
        {
            p = p + m(r, c) * v(c);
        }
        res(r) = p;
    }
    return res;
}

template <typename T> Vector<T> operator*(const Vector<T>& v, const Matrix<T>& m)
{
    assert(m.rows() == v.size());
    Vector<T> res(m.cols());

    for (size_t c = 0; c < m.cols(); c++)
    {
        T p = 0.0f;
        for (size_t r = 0; r < m.rows(); r++)
        {
            p = p + m(r, c) * v(r);
        }
        res(c) = p;
    }
    return res;
}

template <typename T> void Matrix<T>::transpose()
{
    const Matrix<T> temp_mat = *this;
    std::swap(num_rows_, num_cols_);

    for (size_t r = 0; r < num_rows_; r++)
    {
        for (size_t c = 0; c < num_cols_; c++)
        {
            data_[c * num_cols_ + r] = temp_mat(c, r);
        }
    }
}

template <typename T> Matrix<T> Matrix<T>::getTranspose() const
{
    Matrix<T> res(num_cols_, num_rows_);

    for (size_t r = 0; r < res.rows(); r++)
    {
        for (size_t c = 0; c < res.cols(); c++)
        {
            res(r, c) = data_[c * num_cols_ + r];
        }
    }
    return res;
}

template <typename T> void Matrix<T>::removeRowAtIndex(const size_t row_idx)
{
    ASSERT(is_allocated_) << "Matrix not allocated!";
    ASSERT(row_idx < num_rows_) << "Tried to remove element outside bounds!";

    T* temp_data;

    DATA_ALLOCATION(temp_data, (num_rows_ - 1) * num_cols_, T, "Matrix");

    size_t current_row_idx = 0;

    for (size_t r = 0; r < num_rows_; r++)
    {
        for (size_t c = 0; c < num_cols_; c++)
        {
            if (current_row_idx != row_idx)
            {
                temp_data[current_row_idx * num_cols_ + c] = data_[r * num_cols_ + c];
                current_row_idx++;
            }
        }
    }

    delete[] data_;
    data_ = temp_data;
    num_rows_ = num_rows_ - 1;
}

template <typename T> void Matrix<T>::removeRowsAtIndices(const IndexSpan& idx_span)
{
    ASSERT(is_allocated_) << "Matrix not allocated!";
    ASSERT(idx_span.from <= idx_span.to) << "To index smaller than from index!";
    ASSERT(idx_span.to < num_rows_) << "Tried to remove element outside bounds!";
    if (idx_span.from == idx_span.to)
    {
        LOG_WARNING() << "From and to indices are equal!";
    }

    T* temp_data;

    size_t num_rows_to_remove = idx_span.to - idx_span.from + 1;

    ASSERT((num_rows_ - num_rows_to_remove) > 0) << "Tried to remove all elements!";

    DATA_ALLOCATION(temp_data, (num_rows_ - num_rows_to_remove) * num_cols_, T, "Matrix");

    size_t current_row_idx = 0;

    for (size_t r = 0; r < num_rows_; r++)
    {
        for (size_t c = 0; c < num_cols_; c++)
        {
            if (current_row_idx < idx_span.from || current_row_idx > idx_span.to)
            {
                temp_data[current_row_idx * num_cols_ + c] = data_[r * num_cols_ + c];
                current_row_idx++;
            }
        }
    }

    delete[] data_;
    data_ = temp_data;
    num_rows_ = num_rows_ - num_rows_to_remove;
}

template <typename T> void Matrix<T>::removeColAtIndex(const size_t col_idx)
{
    ASSERT(is_allocated_) << "Matrix not allocated!";
    ASSERT(col_idx < num_cols_) << "Tried to remove element outside bounds!";

    T* temp_data;

    DATA_ALLOCATION(temp_data, num_rows_ * (num_cols_ - 1), T, "Matrix");

    size_t current_col_idx = 0;

    for (size_t r = 0; r < num_rows_; r++)
    {
        for (size_t c = 0; c < num_cols_; c++)
        {
            if (current_col_idx != col_idx)
            {
                temp_data[current_col_idx * (num_cols_ - 1) + c] = data_[r * num_cols_ + c];
                current_col_idx++;
            }
        }
    }

    delete[] data_;
    data_ = temp_data;
    num_cols_ = num_cols_ - 1;
}

template <typename T> void Matrix<T>::removeColsAtIndices(const IndexSpan& idx_span)
{
    ASSERT(is_allocated_) << "Matrix not allocated!";
    ASSERT(idx_span.from <= idx_span.to) << "To index smaller than from index!";
    ASSERT(idx_span.to < num_cols_) << "Tried to remove element outside bounds!";
    if (idx_span.from == idx_span.to)
    {
        LOG_WARNING() << "From and to indices are equal!";
    }

    T* temp_data;

    size_t num_cols_to_remove = idx_span.to - idx_span.from + 1;

    ASSERT((num_cols_ - num_cols_to_remove) > 0) << "Tried to remove all elements!";

    DATA_ALLOCATION(temp_data, num_rows_ * (num_cols_ - num_cols_to_remove), T, "Matrix");

    size_t current_col_idx = 0;

    for (size_t r = 0; r < num_rows_; r++)
    {
        for (size_t c = 0; c < num_cols_; c++)
        {
            if (current_col_idx < idx_span.from || current_col_idx > idx_span.to)
            {
                temp_data[current_col_idx * (num_cols_ - num_cols_to_remove) + c] =
                    data_[r * num_cols_ + c];
                current_col_idx++;
            }
        }
    }

    delete[] data_;
    data_ = temp_data;
    num_cols_ = num_cols_ - num_cols_to_remove;
}

template <typename T> Matrix<T> unitMatrix(const size_t rows, const size_t cols)
{
    Matrix<T> unit_matrix(rows, cols);
    for (size_t r = 0; r < rows; r++)
    {
        for (size_t c = 0; c < cols; c++)
        {
            if (r == c)
            {
                unit_matrix(r, c) = 1.0;
            }
            else
            {
                unit_matrix(r, c) = 0.0;
            }
        }
    }
    return unit_matrix;
}

template <typename T> Matrix<T> zerosMatrix(const size_t rows, const size_t cols)
{
    Matrix<T> zero_matrix(rows, cols);
    for (size_t r = 0; r < rows; r++)
    {
        for (size_t c = 0; c < cols; c++)
        {
            zero_matrix(r, c) = 0.0;
        }
    }
    return zero_matrix;
}

template <typename T> Matrix<T> onesMatrix(const size_t rows, const size_t cols)
{
    Matrix<T> ones_matrix(rows, cols);
    for (size_t r = 0; r < rows; r++)
    {
        for (size_t c = 0; c < cols; c++)
        {
            ones_matrix(r, c) = 1.0;
        }
    }
    return ones_matrix;
}

template <typename T> Matrix<T> filledMatrix(const size_t rows, const size_t cols, T val)
{
    Matrix<T> filled_matrix(rows, cols);
    for (size_t r = 0; r < rows; r++)
    {
        for (size_t c = 0; c < cols; c++)
        {
            filled_matrix(r, c) = val;
        }
    }
    return filled_matrix;
}

template <typename T> void fillMatrixWithArrayRowMajor(Matrix<T>& m, const T* a)
{
    assert(m.isAllocated() && "You must allocate your matrix before filling it!");
    for (size_t r = 0; r < m.rows(); r++)
    {
        for (size_t c = 0; c < m.cols(); c++)
        {
            m(r, c) = a[r * m.cols() + c];
        }
    }
}

template <typename T> void fillMatrixWithArrayColMajor(Matrix<T>& m, const T* a)
{
    assert(m.isAllocated() && "You must allocate your matrix before filling it!");
    for (size_t r = 0; r < m.rows(); r++)
    {
        for (size_t c = 0; c < m.cols(); c++)
        {
            m(r, c) = a[c * m.rows() + r];
        }
    }
}

template <typename T> std::ostream& operator<<(std::ostream& os, const Matrix<T>& m)
{
    std::string s = "";

    for (size_t r = 0; r < m.rows(); r++)
    {
        s = s + "[ ";
        for (size_t c = 0; c < m.cols(); c++)
        {
            s = s + std::to_string(m(r, c));
            if (c != m.cols() - 1)
            {
                s = s + ", ";
            }
        }
        s = s + " ]\n";
    }

    os << s;

    return os;
}

template <typename T> Vector<T> Matrix<T>::getColumnAsVector(const size_t column_idx) const
{
    ASSERT(column_idx < num_cols_) << "Tried to access column outside of matrix bounds!";
    Vector<T> column_vec(num_rows_);

    for (size_t k = 0; k < num_rows_; k++)
    {
        column_vec(k) = data_[num_cols_ * k + column_idx];
    }
    return column_vec;
}

template <typename T> Vector<T> Matrix<T>::getRowAsVector(const size_t row_idx) const
{
    ASSERT(row_idx < num_rows_) << "Tried to access row outside of matrix bounds!";
    Vector<T> row_vec(num_cols_);

    for (size_t k = 0; k < num_cols_; k++)
    {
        row_vec(k) = data_[num_cols_ * row_idx + k];
    }
    return row_vec;
}

template <typename T> Matrix<T> Matrix<T>::getColumn(const size_t column_idx) const
{
    ASSERT(column_idx < num_cols_) << "Tried to access column outside of matrix bounds!";
    Matrix<T> column_mat(num_rows_, 1);

    for (size_t k = 0; k < num_rows_; k++)
    {
        column_mat(k, 0) = data_[num_cols_ * k + column_idx];
    }
    return column_mat;
}

template <typename T> Matrix<T> Matrix<T>::getRow(const size_t row_idx) const
{
    ASSERT(row_idx < num_rows_) << "Tried to access row outside of matrix bounds!";
    Matrix<T> row_mat(1, num_cols_);

    for (size_t k = 0; k < num_cols_; k++)
    {
        row_mat(0, k) = data_[num_cols_ * row_idx + k];
    }
    return row_mat;
}

template <typename T> Vector<T> Matrix<T>::toVector() const
{
    ASSERT(is_allocated_);
    ASSERT((num_rows_ == 1) || (num_cols_ == 1)) << "One dimension must be equal to 1!";
    const size_t num_elements = std::max(num_rows_, num_cols_);
    Vector<T> vres(num_elements);

    for (size_t k = 0; k < num_elements; k++)
    {
        vres(k) = data_[k];
    }

    return vres;
}

template <typename T> T Matrix<T>::max() const
{
    ASSERT_MAT_VALID_INTERNAL();

    T max_val = data_[0];
    for (size_t c = 1; c < num_cols_; c++)
    {
        max_val = std::max(max_val, data_[c]);
    }

    for (size_t r = 1; r < num_rows_; r++)
    {
        T max_val_internal = data_[r * num_cols_];
        for (size_t c = 1; c < num_cols_; c++)
        {
            max_val_internal = std::max(max_val_internal, data_[r * num_cols_ + c]);
        }
        max_val = std::max(max_val, max_val_internal);
    }

    return max_val;
}

template <typename T> T Matrix<T>::min() const
{
    ASSERT_MAT_VALID_INTERNAL();

    T min_val = data_[0];
    for (size_t c = 1; c < num_cols_; c++)
    {
        min_val = std::min(min_val, data_[c]);
    }

    for (size_t r = 1; r < num_rows_; r++)
    {
        T min_val_internal = data_[r * num_cols_];
        for (size_t c = 1; c < num_cols_; c++)
        {
            min_val_internal = std::min(min_val_internal, data_[r * num_cols_ + c]);
        }
        min_val = std::min(min_val, min_val_internal);
    }

    return min_val;
}

template <typename T> Matrix<T> Matrix<T>::minAlongCols() const
{
    // Creates a vector with same number of elements as "num_cols_",
    // and each element in the vector is the min value of its corresponding column
    ASSERT_MAT_VALID_INTERNAL();
    Matrix<T> mres(1, num_cols_);

    for (size_t c = 0; c < num_cols_; c++)
    {
        mres(0, c) = data_[c];
    }

    for (size_t c = 0; c < num_cols_; c++)
    {
        for (size_t r = 1; r < num_rows_; r++)
        {
            mres(0, c) = std::min(mres(0, c), data_[r * num_cols_ + c]);
        }
    }

    return mres;
}

template <typename T> Matrix<T> Matrix<T>::minAlongRows() const
{
    // Creates a vector with same number of elements as "num_rows_",
    // and each element in the vector is the min value of its corresponding row
    ASSERT_MAT_VALID_INTERNAL();
    Matrix<T> mres(num_rows_, 1);

    for (size_t r = 0; r < num_rows_; r++)
    {
        mres(r, 0) = data_[r * num_cols_];
    }

    for (size_t r = 0; r < num_rows_; r++)
    {
        for (size_t c = 1; c < num_cols_; c++)
        {
            mres(r, 0) = std::min(mres(r, 0), data_[r * num_cols_ + c]);
        }
    }

    return mres;
}

template <typename T> Matrix<T> Matrix<T>::maxAlongCols() const
{
    // Creates a vector with same number of elements as "num_cols_",
    // and each element in the vector is the max value of its corresponding column
    ASSERT_MAT_VALID_INTERNAL();
    Matrix<T> mres(1, num_cols_);

    for (size_t c = 0; c < num_cols_; c++)
    {
        mres(0, c) = data_[c];
    }

    for (size_t c = 0; c < num_cols_; c++)
    {
        for (size_t r = 1; r < num_rows_; r++)
        {
            mres(0, c) = std::max(mres(0, c), data_[r * num_cols_ + c]);
        }
    }

    return mres;
}

template <typename T> Matrix<T> Matrix<T>::maxAlongRows() const
{
    // Creates a vector with same number of elements as "num_rows_",
    // and each element in the vector is the min value of its corresponding row
    ASSERT_MAT_VALID_INTERNAL();
    Matrix<T> mres(num_rows_, 1);

    for (size_t r = 0; r < num_rows_; r++)
    {
        mres(r, 0) = data_[r * num_cols_];
    }

    for (size_t r = 0; r < num_rows_; r++)
    {
        for (size_t c = 1; c < num_cols_; c++)
        {
            mres(r, 0) = std::max(mres(r, 0), data_[r * num_cols_ + c]);
        }
    }

    return mres;
}

template <typename T> T Matrix<T>::sum() const
{
    T s = 0.0;
    for (size_t r = 0; r < num_rows_; r++)
    {
        for (size_t c = 0; c < num_cols_; c++)
        {
            s = s + data_[r * num_cols_ + c];
        }
    }
    return s;
}

template <typename T> Matrix<T> Matrix<T>::sumAlongRows() const
{
    Matrix<T> mres(num_rows_, 1);
    for (size_t r = 0; r < num_rows_; r++)
    {
        T s = 0.0;
        for (size_t c = 0; c < num_cols_; c++)
        {
            s = s + data_[r * num_cols_ + c];
        }
        mres(r, 0) = s;
    }
    return mres;
}

template <typename T> Matrix<T> Matrix<T>::sumAlongCols() const
{
    Matrix<T> mres(1, num_cols_);
    for (size_t c = 0; c < num_cols_; c++)
    {
        T s = 0.0;
        for (size_t r = 0; r < num_rows_; r++)
        {
            s = s + data_[r * num_cols_ + c];
        }
        mres(0, c) = s;
    }
    return mres;
}

template <typename T>
Matrix<T> uniqueMatrix(const size_t rows, const size_t cols, const T offset = 0.0)
{
    Matrix<T> mres(rows, cols);
    for (size_t r = 0; r < rows; r++)
    {
        for (size_t c = 0; c < cols; c++)
        {
            mres(r, c) = r * cols + c + offset;
        }
    }
    return mres;
}

}  // namespace plot_tool

#endif
