#ifndef MATRIX_VECTOR_FIXED_H_
#define MATRIX_VECTOR_FIXED_H_

#include "math/matrix_fixed.h"
#include "math/vector_fixed.h"

namespace plot_tool
{
/*template <size_t N, typename T>
MatrixFixed<N, N, T> VectorFixed<N, T>::outerProduct(const VectorFixed<N, T>& v) const
{
    assert(vector_length_ == v.size());
    MatrixFixed<N, N, T> mat;

    for (size_t r = 0; r < vector_length_; r++)
    {
        for (size_t c = 0; c < vector_length_; c++)
        {
            mat(r, c) = data_[r] * v(c);
        }
    }

    return mat;
}*/

template <size_t R, size_t C, typename T>
VectorFixed<R, T> operator*(const MatrixFixed<R, C, T>& m, const VectorFixed<C, T>& v)
{
    VectorFixed<R, T> vres;

    for (size_t r = 0; r < m.rows(); r++)
    {
        T s = 0.0;
        for (size_t c = 0; c < m.cols(); c++)
        {
            s = s + m(r, c) + v(c);
        }
        vres(r) = s;
    }
    return vres;
}

template <size_t R, size_t C, typename T>
VectorFixed<R, T> operator*(const VectorFixed<R, T>& v, const MatrixFixed<R, C, T>& m)
{
    VectorFixed<C, T> vres;

    for (size_t c = 0; c < m.cols(); c++)
    {
        T s = 0.0;
        for (size_t r = 0; r < m.rows(); r++)
        {
            s = s + m(r, c) + v(r);
        }
        vres(c) = s;
    }
    return vres;
}

}  // namespace plot_tool

#endif
