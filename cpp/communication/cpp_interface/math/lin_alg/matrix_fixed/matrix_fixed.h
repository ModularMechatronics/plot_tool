#ifndef MATRIX_FIXED_H_
#define MATRIX_FIXED_H_

#include <initializer_list>
#include <iostream>

namespace plot_tool
{
template <size_t R, size_t C, typename T> class MatrixFixed
{
private:
    T data_[R * C];
    const size_t num_rows_;
    const size_t num_cols_;

public:
    MatrixFixed();
    MatrixFixed(const MatrixFixed<R, C, T>& mf);
    MatrixFixed<R, C, T>(const std::initializer_list<std::initializer_list<T>>& il);
    MatrixFixed<R, C, T>& operator=(const MatrixFixed<R, C, T>& m);

    void switchRows(const size_t r0, const size_t r1);
    void switchCols(const size_t c0, const size_t c1);

    T* getDataPointer() const;
    size_t rows() const;
    size_t cols() const;

    T& operator()(const size_t r, const size_t c);
    const T& operator()(const size_t r, const size_t c) const;
};

template <size_t R, size_t C, typename T>
MatrixFixed<R, C, T>::MatrixFixed() : num_rows_(R), num_cols_(C)
{
    static_assert(R > 0, "Number of rows can't be 0!");
    static_assert(C > 0, "Number of columns can't be 0!");
}

template <size_t R, size_t C, typename T> size_t MatrixFixed<R, C, T>::rows() const
{
    return num_rows_;
}
template <size_t R, size_t C, typename T> size_t MatrixFixed<R, C, T>::cols() const
{
    return num_cols_;
}

template <size_t R, size_t C, typename T>
MatrixFixed<R, C, T>::MatrixFixed(const MatrixFixed<R, C, T>& mf) : num_rows_(R), num_cols_(C)
{
    for (size_t r = 0; r < mf.rows(); r++)
    {
        for (size_t c = 0; c < mf.cols(); c++)
        {
            data_[r * num_cols_ + c] = mf(r, c);
        }
    }
}

template <size_t R, size_t C, typename T>
T& MatrixFixed<R, C, T>::operator()(const size_t r, const size_t c)
{
    ASSERT(r < num_rows_) << "Tried to access element outside of num_rows_!";
    ASSERT(c < num_cols_) << "Tried to access element outside of num_cols_!";
    return data_[r * num_cols_ + c];
}

template <size_t R, size_t C, typename T>
const T& MatrixFixed<R, C, T>::operator()(const size_t r, const size_t c) const
{
    ASSERT(r < num_rows_) << "Tried to access element outside of num_rows_!";
    ASSERT(c < num_cols_) << "Tried to access element outside of num_cols_!";
    return data_[r * num_cols_ + c];
}

template <typename T> MatrixFixed<3, 3, T> rotationMatrixX(const T angle)
{
    const T ca = std::cos(angle);
    const T sa = std::sin(angle);
    MatrixFixed<3, 3, T> rotation_matrix;

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

template <typename T> MatrixFixed<3, 3, T> rotationMatrixY(const T angle)
{
    const T ca = std::cos(angle);
    const T sa = std::sin(angle);
    MatrixFixed<3, 3, T> rotation_matrix;

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

template <typename T> MatrixFixed<3, 3, T> rotationMatrixZ(const T angle)
{
    const T ca = std::cos(angle);
    const T sa = std::sin(angle);
    MatrixFixed<3, 3, T> rotation_matrix;

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

template <typename T> MatrixFixed<2, 2, T> rotationMatrix2D(const T angle)
{
    const T ca = std::cos(angle);
    const T sa = std::sin(angle);
    MatrixFixed<2, 2, T> rotation_matrix;

    rotation_matrix(0, 0) = ca;
    rotation_matrix(0, 1) = -sa;

    rotation_matrix(1, 0) = sa;
    rotation_matrix(1, 1) = ca;

    return rotation_matrix;
}

template <size_t R, size_t C, typename T>
MatrixFixed<R, C, T>& MatrixFixed<R, C, T>::operator=(const MatrixFixed<R, C, T>& m)
{
    if (this != &m)
    {
        for (size_t r = 0; r < m.rows(); r++)
        {
            for (size_t c = 0; c < m.cols(); c++)
            {
                data_[r * num_cols_ + c] = m(r, c);
            }
        }
    }
    return *this;
}

template <size_t R, size_t C, typename T>
MatrixFixed<R, C, T>::MatrixFixed(const std::initializer_list<std::initializer_list<T>>& il)
    : num_rows_(R), num_cols_(C)
{
    ASSERT(il.size() == R) << "Incorrect number of rows for templated matrix size!";
    ASSERT(il.begin()[0].size() == C) << "Incorrect number of columns for templated matrix size!";

    for (size_t r = 0; r < il.size(); r++)
    {
        ASSERT(il.begin()[0].size() == il.begin()[r].size())
            << "All row vectors in input std vectors do not have the same size!";
    }

    for (size_t r = 0; r < il.size(); r++)
    {
        for (size_t c = 0; c < il.begin()[r].size(); c++)
        {
            data_[r * num_cols_ + c] = il.begin()[r].begin()[c];
        }
    }
}

template <size_t R, size_t C, typename T>
std::ostream& operator<<(std::ostream& os, const MatrixFixed<R, C, T>& m)
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

template <size_t R, size_t C, typename T>
void MatrixFixed<R, C, T>::switchRows(const size_t r0, const size_t r1)
{
    assert(r0 < num_rows_ && r1 < num_rows_);

    for (size_t c = 0; c < num_cols_; c++)
    {
        const T tmp_var = data_[num_cols_ * r0 + c];
        data_[num_cols_ * r0 + c] = data_[num_cols_ * r1 + c];
        data_[num_cols_ * r1 + c] = tmp_var;
    }
}

template <size_t R, size_t C, typename T>
void MatrixFixed<R, C, T>::switchCols(const size_t c0, const size_t c1)
{
    assert(c0 < num_cols_ && c1 < num_cols_);

    for (size_t r = 0; r < num_rows_; r++)
    {
        const T tmp_var = data_[num_cols_ * r + c0];
        data_[num_cols_ * r + c0] = data_[num_cols_ * r + c1];
        data_[num_cols_ * r + c1] = tmp_var;
    }
}

template <size_t R, size_t C, typename T> T* MatrixFixed<R, C, T>::getDataPointer() const
{
    return data_;
}

template <size_t R, size_t C0, size_t C1, typename T>
MatrixFixed<R, C0 + C1, T> hCatFixed(const MatrixFixed<R, C0, T>& m0,
                                     const MatrixFixed<R, C1, T>& m1)
{
    MatrixFixed<R, C0 + C1, T> mres;

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

template <size_t R0, size_t R1, size_t C, typename T>
MatrixFixed<R0 + R1, C, T> vCatFixed(const MatrixFixed<R0, C, T>& m0,
                                     const MatrixFixed<R1, C, T>& m1)
{
    MatrixFixed<R0 + R1, C, T> mres;
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

template <size_t R0, size_t C0R1, size_t C1, typename T>
MatrixFixed<R0, C1, T> operator*(const MatrixFixed<R0, C0R1, T>& m0,
                                 const MatrixFixed<C0R1, C1, T>& m1)
{
    MatrixFixed<R0, C1, T> mres;

    for (size_t r = 0; r < mres.rows(); r++)
    {
        for (size_t c = 0; c < mres.cols(); c++)
        {
            T p = 0.0f;
            for (size_t i = 0; i < m0.cols(); i++)
            {
                p = p + m0(r, i) * m1(i, c);
            }
            mres(r, c) = p;
        }
    }
    return mres;
}

// New functions

template <size_t R, size_t C, typename T>
MatrixFixed<R, C, T> operator+(const MatrixFixed<R, C, T>& m0, const MatrixFixed<R, C, T>& m1)
{
    MatrixFixed<R, C, T> res;

    for (size_t r = 0; r < res.rows(); r++)
    {
        for (size_t c = 0; c < res.cols(); c++)
        {
            res(r, c) = m0(r, c) + m1(r, c);
        }
    }
    return res;
}

template <size_t R, size_t C, typename T>
MatrixFixed<R, C, T> operator-(const MatrixFixed<R, C, T>& m0, const MatrixFixed<R, C, T>& m1)
{
    MatrixFixed<R, C, T> res;

    for (size_t r = 0; r < res.rows(); r++)
    {
        for (size_t c = 0; c < res.cols(); c++)
        {
            res(r, c) = m0(r, c) - m1(r, c);
        }
    }
    return res;
}

template <size_t R, size_t C, typename T>
MatrixFixed<R, C, T> operator*(const MatrixFixed<R, C, T>& m, const T f)
{
    MatrixFixed<R, C, T> res;

    for (size_t r = 0; r < res.rows(); r++)
    {
        for (size_t c = 0; c < res.cols(); c++)
        {
            res(r, c) = f * m(r, c);
        }
    }
    return res;
}

template <size_t R, size_t C, typename T>
MatrixFixed<R, C, T> operator*(const T f, const MatrixFixed<R, C, T>& m)
{
    MatrixFixed<R, C, T> res;

    for (size_t r = 0; r < res.rows(); r++)
    {
        for (size_t c = 0; c < res.cols(); c++)
        {
            res(r, c) = f * m(r, c);
        }
    }
    return res;
}

template <size_t R, size_t C, typename T>
MatrixFixed<R, C, T> operator/(const MatrixFixed<R, C, T>& m0, const MatrixFixed<R, C, T>& m1)
{
    MatrixFixed<R, C, T> res;

    for (size_t r = 0; r < res.rows(); r++)
    {
        for (size_t c = 0; c < res.cols(); c++)
        {
            res(r, c) = m0(r, c) / m1(r, c);
        }
    }
    return res;
}

template <size_t R, size_t C, typename T>
MatrixFixed<R, C, T> operator^(const MatrixFixed<R, C, T>& m0, const MatrixFixed<R, C, T>& m1)
{
    MatrixFixed<R, C, T> res;

    for (size_t r = 0; r < res.rows(); r++)
    {
        for (size_t c = 0; c < res.cols(); c++)
        {
            res(r, c) = m0(r, c) * m1(r, c);
        }
    }
    return res;
}

template <size_t R, size_t C, typename T>
MatrixFixed<R, C, T> operator/(const MatrixFixed<R, C, T>& m, const T f)
{
    MatrixFixed<R, C, T> res;

    for (size_t r = 0; r < res.rows(); r++)
    {
        for (size_t c = 0; c < res.cols(); c++)
        {
            res(r, c) = m(r, c) / f;
        }
    }
    return res;
}

template <size_t R, size_t C, typename T>
MatrixFixed<R, C, T> operator/(const T f, const MatrixFixed<R, C, T>& m)
{
    MatrixFixed<R, C, T> res;

    for (size_t r = 0; r < res.rows(); r++)
    {
        for (size_t c = 0; c < res.cols(); c++)
        {
            res(r, c) = f / m(r, c);
        }
    }
    return res;
}

template <size_t R, size_t C, typename T>
MatrixFixed<R, C, T> operator-(const MatrixFixed<R, C, T>& m, const T f)
{
    MatrixFixed<R, C, T> res;

    for (size_t r = 0; r < res.rows(); r++)
    {
        for (size_t c = 0; c < res.cols(); c++)
        {
            res(r, c) = m(r, c) - f;
        }
    }
    return res;
}

template <size_t R, size_t C, typename T>
MatrixFixed<R, C, T> operator-(const T f, const MatrixFixed<R, C, T>& m)
{
    MatrixFixed<R, C, T> res;

    for (size_t r = 0; r < res.rows(); r++)
    {
        for (size_t c = 0; c < res.cols(); c++)
        {
            res(r, c) = f - m(r, c);
        }
    }
    return res;
}

template <size_t R, size_t C, typename T>
MatrixFixed<R, C, T> operator+(const MatrixFixed<R, C, T>& m, const T f)
{
    MatrixFixed<R, C, T> res;

    for (size_t r = 0; r < res.rows(); r++)
    {
        for (size_t c = 0; c < res.cols(); c++)
        {
            res(r, c) = m(r, c) + f;
        }
    }
    return res;
}

template <size_t R, size_t C, typename T>
MatrixFixed<R, C, T> operator+(const T f, const MatrixFixed<R, C, T>& m)
{
    MatrixFixed<R, C, T> res;

    for (size_t r = 0; r < res.rows(); r++)
    {
        for (size_t c = 0; c < res.cols(); c++)
        {
            res(r, c) = m(r, c) + f;
        }
    }
    return res;
}

template <size_t R, size_t C, typename T>
MatrixFixed<R, C, T> operator-(const MatrixFixed<R, C, T>& m)
{
    MatrixFixed<R, C, T> res;

    for (size_t r = 0; r < res.rows(); r++)
    {
        for (size_t c = 0; c < res.cols(); c++)
        {
            res(r, c) = -m(r, c);
        }
    }
    return res;
}

}  // namespace plot_tool

#endif
