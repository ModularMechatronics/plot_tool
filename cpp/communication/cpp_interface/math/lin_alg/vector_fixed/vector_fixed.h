#ifndef PLOT_TOOL_VECTOR_FIXED_H_
#define PLOT_TOOL_VECTOR_FIXED_H_

#include "math/math_core.h"

namespace plot_tool
{
template <size_t N, typename T> class VectorFixed
{
private:
    T data_[N];
    const size_t vector_length_;

public:
    VectorFixed();
    VectorFixed(const VectorFixed<N, T>& vf);

    size_t size() const;
    void fill(const T& val);

    T& operator()(const size_t idx);
    const T& operator()(const size_t idx) const;
    T& operator()(const EndIndex& end_idx);
    const T& operator()(const EndIndex& end_idx) const;

    size_t endIndex() const;
    size_t countNumNonZeroElements() const;

    T* getDataPointer() const;

    // MatrixFixed<N, N, T> outerProduct(const VectorFixed<N, T>& v) const;
    MatrixFixed<1, N, T> toRowVectorMat() const;
    MatrixFixed<N, 1, T> toColVectorMat() const;
};

template <size_t N, typename T> VectorFixed<N, T>::VectorFixed() : vector_length_(N) {}

template <size_t N, typename T>
VectorFixed<N, T>::VectorFixed(const VectorFixed<N, T>& vf) : vector_length_(N)
{
    for (size_t k = 0; k < N; k++)
    {
        data_[k] = vf(k);
    }
}

template <size_t N, typename T> T* VectorFixed<N, T>::getDataPointer() const
{
    return data_;
}

template <size_t N, typename T> T& VectorFixed<N, T>::operator()(const size_t idx)
{
    assert(idx < vector_length_);
    return data_[idx];
}

template <size_t N, typename T> const T& VectorFixed<N, T>::operator()(const size_t idx) const
{
    assert(idx < vector_length_);
    return data_[idx];
}

template <size_t N, typename T> T& VectorFixed<N, T>::operator()(const EndIndex& end_idx)
{
    const size_t idx = static_cast<size_t>(static_cast<int>(vector_length_) - 1 + end_idx.offset);
    assert(idx < vector_length_);
    return data_[idx];
}

template <size_t N, typename T>
const T& VectorFixed<N, T>::operator()(const EndIndex& end_idx) const
{
    const size_t idx = static_cast<size_t>(static_cast<int>(vector_length_) - 1 + end_idx.offset);
    assert(idx < vector_length_);
    return data_[idx];
}

template <size_t N, typename T> void VectorFixed<N, T>::fill(const T& val)
{
    for (size_t k = 0; k < vector_length_; k++)
    {
        data_[k] = val;
    }
}

template <size_t N, typename T> size_t VectorFixed<N, T>::countNumNonZeroElements() const
{
    size_t cnt = 0;
    for (size_t k = 0; k < vector_length_; k++)
    {
        if (data_[k])
        {
            cnt++;
        }
    }
    return cnt;
}

template <size_t N, typename T> size_t VectorFixed<N, T>::endIndex() const
{
    return vector_length_ - 1;
}

template <size_t N, typename T>
std::ostream& operator<<(std::ostream& os, const VectorFixed<N, T>& v)
{
    std::string s = "[ ";
    for (size_t k = 0; k < v.size(); k++)
    {
        s = s + std::to_string(v(k));
        if (k != v.size() - 1)
        {
            s = s + ", ";
        }
    }
    s = s + " ]";
    os << s;

    return os;
}

template <size_t N, typename T>
T operator*(const VectorFixed<N, T>& v0, const VectorFixed<N, T>& v1)
{
    assert(v0.size() == v1.size());
    T d = 0.0;
    for (size_t k = 0; k < v0.size(); k++)
    {
        d = d + v0(k) * v1(k);
    }
    return d;
}

template <size_t N, typename T> VectorFixed<N, T> operator*(const T& f, const VectorFixed<N, T>& v)
{
    VectorFixed<N, T> v_res(v.size());
    for (size_t k = 0; k < v.size(); k++)
    {
        v_res(k) = f * v(k);
    }
    return v_res;
}

template <size_t N, typename T> VectorFixed<N, T> operator*(const VectorFixed<N, T>& v, const T& f)
{
    VectorFixed<N, T> v_res(v.size());
    for (size_t k = 0; k < v.size(); k++)
    {
        v_res(k) = f * v(k);
    }
    return v_res;
}

template <size_t N, typename T> VectorFixed<N, T> operator/(const VectorFixed<N, T>& v, const T& f)
{
    VectorFixed<N, T> v_res(v.size());
    for (size_t k = 0; k < v.size(); k++)
    {
        v_res(k) = v(k) / f;
    }
    return v_res;
}

template <size_t N, typename T> VectorFixed<N, T> operator/(const T& f, const VectorFixed<N, T>& v)
{
    VectorFixed<N, T> v_res(v.size());
    for (size_t k = 0; k < v.size(); k++)
    {
        v_res(k) = f / v(k);
    }
    return v_res;
}

template <size_t N, typename T> VectorFixed<N, T> operator+(const VectorFixed<N, T>& v, const T& f)
{
    VectorFixed<N, T> v_res(v.size());
    for (size_t k = 0; k < v.size(); k++)
    {
        v_res(k) = v(k) + f;
    }
    return v_res;
}

template <size_t N, typename T> VectorFixed<N, T> operator+(const T& f, const VectorFixed<N, T>& v)
{
    VectorFixed<N, T> v_res(v.size());
    for (size_t k = 0; k < v.size(); k++)
    {
        v_res(k) = v(k) + f;
    }
    return v_res;
}

template <size_t N, typename T> VectorFixed<N, T> operator-(const VectorFixed<N, T>& v, const T& f)
{
    VectorFixed<N, T> v_res(v.size());
    for (size_t k = 0; k < v.size(); k++)
    {
        v_res(k) = v(k) - f;
    }
    return v_res;
}

template <size_t N, typename T> VectorFixed<N, T> operator-(const T& f, const VectorFixed<N, T>& v)
{
    VectorFixed<N, T> v_res(v.size());
    for (size_t k = 0; k < v.size(); k++)
    {
        v_res(k) = f - v(k);
    }
    return v_res;
}

template <size_t N, typename T> VectorFixed<N, T> operator-(const VectorFixed<N, T>& v)
{
    VectorFixed<N, T> v_res(v.size());
    for (size_t k = 0; k < v.size(); k++)
    {
        v_res(k) = -v(k);
    }
    return v_res;
}

template <size_t N, typename T>
VectorFixed<N, T> operator+(const VectorFixed<N, T>& v0, const VectorFixed<N, T>& v1)
{
    assert(v0.size() == v1.size());
    VectorFixed<N, T> v_res(v0.size());
    for (size_t k = 0; k < v0.size(); k++)
    {
        v_res(k) = v0(k) + v1(k);
    }
    return v_res;
}

template <size_t N, typename T>
VectorFixed<N, T> operator-(const VectorFixed<N, T>& v0, const VectorFixed<N, T>& v1)
{
    assert(v0.size() == v1.size());
    VectorFixed<N, T> v_res(v0.size());
    for (size_t k = 0; k < v0.size(); k++)
    {
        v_res(k) = v0(k) - v1(k);
    }
    return v_res;
}

template <size_t N, typename T>
VectorFixed<N, bool> operator==(const VectorFixed<N, T>& v0, const VectorFixed<N, T>& v1)
{
    assert(v0.size() == v1.size());
    VectorFixed<N, bool> v_res(v0.size());
    for (size_t k = 0; k < v0.size(); k++)
    {
        v_res(k) = v0(k) == v1(k);
    }
    return v_res;
}

template <size_t N, typename T>
VectorFixed<N, bool> operator==(const VectorFixed<N, T>& v, const T& s)
{
    VectorFixed<N, bool> v_res(v.size());
    for (size_t k = 0; k < v.size(); k++)
    {
        v_res(k) = v(k) == s;
    }
    return v_res;
}

template <size_t N, typename T>
VectorFixed<N, bool> operator==(const T& s, const VectorFixed<N, T>& v)
{
    VectorFixed<N, bool> v_res(v.size());
    for (size_t k = 0; k < v.size(); k++)
    {
        v_res(k) = v(k) == s;
    }
    return v_res;
}

template <size_t N, typename T>
VectorFixed<N, bool> operator!=(const VectorFixed<N, T>& v0, const VectorFixed<N, T>& v1)
{
    assert(v0.size() == v1.size());
    VectorFixed<N, bool> v_res(v0.size());
    for (size_t k = 0; k < v0.size(); k++)
    {
        v_res(k) = v0(k) != v1(k);
    }
    return v_res;
}

template <size_t N, typename T>
VectorFixed<N, bool> operator!=(const VectorFixed<N, T>& v, const T& s)
{
    VectorFixed<N, bool> v_res(v.size());
    for (size_t k = 0; k < v.size(); k++)
    {
        v_res(k) = v(k) != s;
    }
    return v_res;
}

template <size_t N, typename T>
VectorFixed<N, bool> operator!=(const T& s, const VectorFixed<N, T>& v)
{
    VectorFixed<N, bool> v_res(v.size());
    for (size_t k = 0; k < v.size(); k++)
    {
        v_res(k) = v(k) != s;
    }
    return v_res;
}

template <size_t N, typename T>
VectorFixed<N, bool> operator<(const VectorFixed<N, T>& v0, const VectorFixed<N, T>& v1)
{
    assert(v0.size() == v1.size());
    VectorFixed<N, bool> v_res(v0.size());
    for (size_t k = 0; k < v0.size(); k++)
    {
        v_res(k) = v0(k) < v1(k);
    }
    return v_res;
}

template <size_t N, typename T>
VectorFixed<N, bool> operator<(const VectorFixed<N, T>& v, const T& s)
{
    VectorFixed<N, bool> v_res(v.size());
    for (size_t k = 0; k < v.size(); k++)
    {
        v_res(k) = v(k) < s;
    }
    return v_res;
}

template <size_t N, typename T>
VectorFixed<N, bool> operator<(const T& s, const VectorFixed<N, T>& v)
{
    VectorFixed<N, bool> v_res(v.size());
    for (size_t k = 0; k < v.size(); k++)
    {
        v_res(k) = s < v(k);
    }
    return v_res;
}

template <size_t N, typename T>
VectorFixed<N, bool> operator>(const VectorFixed<N, T>& v0, const VectorFixed<N, T>& v1)
{
    assert(v0.size() == v1.size());
    VectorFixed<N, bool> v_res(v0.size());
    for (size_t k = 0; k < v0.size(); k++)
    {
        v_res(k) = v0(k) > v1(k);
    }
    return v_res;
}

template <size_t N, typename T>
VectorFixed<N, bool> operator>(const VectorFixed<N, T>& v, const T& s)
{
    VectorFixed<N, bool> v_res(v.size());
    for (size_t k = 0; k < v.size(); k++)
    {
        v_res(k) = v(k) > s;
    }
    return v_res;
}

template <size_t N, typename T>
VectorFixed<N, bool> operator>(const T& s, const VectorFixed<N, T>& v)
{
    VectorFixed<N, bool> v_res(v.size());
    for (size_t k = 0; k < v.size(); k++)
    {
        v_res(k) = s > v(k);
    }
    return v_res;
}

template <size_t N, typename T>
VectorFixed<N, bool> operator<=(const VectorFixed<N, T>& v0, const VectorFixed<N, T>& v1)
{
    assert(v0.size() == v1.size());
    VectorFixed<N, bool> v_res(v0.size());
    for (size_t k = 0; k < v0.size(); k++)
    {
        v_res(k) = v0(k) <= v1(k);
    }
    return v_res;
}

template <size_t N, typename T>
VectorFixed<N, bool> operator<=(const VectorFixed<N, T>& v, const T& s)
{
    VectorFixed<N, bool> v_res(v.size());
    for (size_t k = 0; k < v.size(); k++)
    {
        v_res(k) = v(k) <= s;
    }
    return v_res;
}

template <size_t N, typename T>
VectorFixed<N, bool> operator<=(const T& s, const VectorFixed<N, T>& v)
{
    VectorFixed<N, bool> v_res(v.size());
    for (size_t k = 0; k < v.size(); k++)
    {
        v_res(k) = s <= v(k);
    }
    return v_res;
}

template <size_t N, typename T>
VectorFixed<N, bool> operator>=(const VectorFixed<N, T>& v0, const VectorFixed<N, T>& v1)
{
    assert(v0.size() == v1.size());
    VectorFixed<N, bool> v_res(v0.size());
    for (size_t k = 0; k < v0.size(); k++)
    {
        v_res(k) = v0(k) >= v1(k);
    }
    return v_res;
}

template <size_t N, typename T>
VectorFixed<N, bool> operator>=(const VectorFixed<N, T>& v, const T& s)
{
    VectorFixed<N, bool> v_res(v.size());
    for (size_t k = 0; k < v.size(); k++)
    {
        v_res(k) = v(k) >= s;
    }
    return v_res;
}

template <size_t N, typename T>
VectorFixed<N, bool> operator>=(const T& s, const VectorFixed<N, T>& v)
{
    VectorFixed<N, bool> v_res(v.size());
    for (size_t k = 0; k < v.size(); k++)
    {
        v_res(k) = s >= v(k);
    }
    return v_res;
}

template <size_t N, typename T>
VectorFixed<N, bool> operator&&(const VectorFixed<N, T>& v0, const VectorFixed<N, T>& v1)
{
    assert(v0.size() == v1.size());
    VectorFixed<N, bool> v_res(v0.size());
    for (size_t k = 0; k < v0.size(); k++)
    {
        v_res(k) = v0(k) && v1(k);
    }
    return v_res;
}

template <size_t N, typename T>
VectorFixed<N, bool> operator&&(const VectorFixed<N, T>& v, const T& s)
{
    VectorFixed<N, bool> v_res(v.size());
    for (size_t k = 0; k < v.size(); k++)
    {
        v_res(k) = v(k) && s;
    }
    return v_res;
}

template <size_t N, typename T>
VectorFixed<N, bool> operator&&(const T& s, const VectorFixed<N, T>& v)
{
    VectorFixed<N, bool> v_res(v.size());
    for (size_t k = 0; k < v.size(); k++)
    {
        v_res(k) = s && v(k);
    }
    return v_res;
}

template <size_t N, typename T>
VectorFixed<N, bool> operator||(const VectorFixed<N, T>& v0, const VectorFixed<N, T>& v1)
{
    assert(v0.size() == v1.size());
    VectorFixed<N, bool> v_res(v0.size());
    for (size_t k = 0; k < v0.size(); k++)
    {
        v_res(k) = v0(k) || v1(k);
    }
    return v_res;
}

template <size_t N, typename T>
VectorFixed<N, bool> operator||(const VectorFixed<N, T>& v, const T& s)
{
    VectorFixed<N, bool> v_res(v.size());
    for (size_t k = 0; k < v.size(); k++)
    {
        v_res(k) = v(k) || s;
    }
    return v_res;
}

template <size_t N, typename T>
VectorFixed<N, bool> operator||(const T& s, const VectorFixed<N, T>& v)
{
    VectorFixed<N, bool> v_res(v.size());
    for (size_t k = 0; k < v.size(); k++)
    {
        v_res(k) = s || v(k);
    }
    return v_res;
}

template <size_t N, typename T> VectorFixed<N, bool> operator!(const VectorFixed<N, T>& v)
{
    VectorFixed<N, bool> v_res(v.size());
    for (size_t k = 0; k < v.size(); k++)
    {
        v_res(k) = !v(k);
    }
    return v_res;
}

}  // namespace plot_tool

#endif
