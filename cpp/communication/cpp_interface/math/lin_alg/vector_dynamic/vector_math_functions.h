
#ifndef VECTOR_MATH_FUNCTIONS_H_
#define VECTOR_MATH_FUNCTIONS_H_

#include <cmath>
#include <cstdarg>
#include <cstdlib>
#include <utility>

#include "logging.h"
#include "math/math_core.h"

namespace plot_tool
{
template <typename T> bool any(const Vector<T>& v)
{
    bool b = false;
    for (size_t k = 0; k < v.size(); k++)
    {
        b = b || v(k);
    }
    return b;
}

template <typename T> bool all(const Vector<T>& v)
{
    bool b = true;
    for (size_t k = 0; k < v.size(); k++)
    {
        b = b && v(k);
    }
    return b;
}

template <typename T> Vector<size_t> findIndicesOfNonZeroElements(const Vector<T>& v)
{
    std::vector<size_t> std_vec;
    for (size_t k = 0; k < v.size(); k++)
    {
        if (v(k))
        {
            std_vec.push_back(k);
        }
    }
    const Vector<size_t> vres = std_vec;
    return vres;
}

template <typename T> Vector<T> concatenate(const std::initializer_list<Vector<T>>& init_list)
{
    size_t new_length = 0;

    for (auto le : init_list)
    {
        new_length = new_length + le.size();
    }
    Vector<T> vres(new_length);

    size_t idx = 0;
    for (auto le : init_list)
    {
        for (size_t k = 0; k < le.size(); k++)
        {
            vres(idx) = le(k);
            idx++;
        }
    }

    return vres;
}

template <typename T> Vector<T> round(const Vector<T>& vin)
{
    assert(vin.size() > 0);
    Vector<T> v(vin.size());
    for (size_t k = 0; k < vin.size(); k++)
    {
        v(k) = std::round(vin(k));
    }

    return v;
}

template <typename T> T max(const Vector<T>& vin)
{
    assert(vin.size() > 0);
    T max_val = vin(0);
    for (size_t k = 1; k < vin.size(); k++)
    {
        max_val = std::max(vin(k), max_val);
    }

    return max_val;
}

template <typename T> Vector<T> abs(const Vector<T>& vin)
{
    assert(vin.size() > 0);
    Vector<T> vout(vin.size());

    for (size_t k = 0; k < vin.size(); k++)
    {
        vout(k) = std::fabs(vin(k));
    }

    return vout;
}

template <typename T> T maxAbs(const Vector<T>& vin)
{
    assert(vin.size() > 0);
    T max_val = std::fabs(vin(0));
    for (size_t k = 1; k < vin.size(); k++)
    {
        max_val = std::max(std::fabs(vin(k)), max_val);
    }

    return max_val;
}

template <typename T> T minAbs(const Vector<T>& vin)
{
    assert(vin.size() > 0);
    T min_val = std::fabs(vin(0));
    for (size_t k = 1; k < vin.size(); k++)
    {
        min_val = std::min(std::fabs(vin(k)), min_val);
    }

    return min_val;
}

template <typename T> T min(const Vector<T>& vin)
{
    assert(vin.size() > 0);
    T min_val = vin(0);
    for (size_t k = 1; k < vin.size(); k++)
    {
        min_val = std::min(vin(k), min_val);
    }

    return min_val;
}

template <typename T> Vector<T> log10(const Vector<T>& vin)
{
    assert(vin.size() > 0);
    Vector<T> v(vin.size());
    for (size_t k = 0; k < vin.size(); k++)
    {
        v(k) = std::log10(vin(k));
    }

    return v;
}

template <typename T> Vector<T> pow(const Vector<T>& vin, const T e)
{
    assert(vin.size() > 0);
    Vector<T> v(vin.size());
    for (size_t k = 0; k < vin.size(); k++)
    {
        v(k) = std::pow(vin(k), e);
    }

    return v;
}

template <typename T> Vector<T> log(const Vector<T>& vin)
{
    assert(vin.size() > 0);
    Vector<T> v(vin.size());
    for (size_t k = 0; k < vin.size(); k++)
    {
        v(k) = std::log(vin(k));
    }

    return v;
}

template <typename T> Vector<T> exp(const Vector<T>& vin)
{
    assert(vin.size() > 0);
    Vector<T> v(vin.size());
    for (size_t k = 0; k < vin.size(); k++)
    {
        v(k) = std::exp(vin(k));
    }

    return v;
}

template <typename T> Vector<T> cos(const Vector<T>& vin)
{
    assert(vin.size() > 0);
    Vector<T> v(vin.size());
    for (size_t k = 0; k < vin.size(); k++)
    {
        v(k) = std::cos(vin(k));
    }

    return v;
}

template <typename T> Vector<T> sin(const Vector<T>& vin)
{
    assert(vin.size() > 0);
    Vector<T> v(vin.size());
    for (size_t k = 0; k < vin.size(); k++)
    {
        v(k) = std::sin(vin(k));
    }

    return v;
}

template <typename T>
Vector<T> linspaceFromPointsAndCount(const T x0, const T x1, const size_t num_values)
{
    assert(num_values > 0);
    Vector<T> v(num_values);

    const T dx = (x1 - x0) / static_cast<T>(num_values - 1);
    v(0) = x0;

    for (size_t k = 1; k < num_values; k++)
    {
        v(k) = v(k - 1) + dx;
    }

    return v;
}

template <typename T>
Vector<T> linspaceFromPointIncAndCount(const T x0, const T dx, const size_t num_values)
{
    assert(num_values > 0);
    Vector<T> v(num_values);

    v(0) = x0;

    for (size_t k = 1; k < num_values; k++)
    {
        v(k) = v(k - 1) + dx;
    }

    return v;
}

template <typename T> Vector<T> linspaceFromPointsAndInc(const T x0, const T x1, const T dx)
{
    assert(dx > 0);
    assert(x1 > x0);

    const size_t num_values = (x1 - x0) / dx;

    return linspaceFromPointsAndCount(x0, x1, num_values);
}

template <typename T> T sum(const Vector<T>& vin)
{
    assert(vin.size() > 0);

    T s = vin(0);
    for (size_t k = 1; k < vin.size(); k++)
    {
        s = s + vin(k);
    }

    return s;
}

template <typename T> T mean(const Vector<T>& vin)
{
    assert(vin.size() > 0);

    return sum(vin) / static_cast<T>(vin.size());
}

template <typename T> T variance(const Vector<T>& vin)
{
    assert(vin.size() > 0);

    const T m = mean(vin);

    T s = 0.0;
    for (size_t k = 0; k < vin.size(); k++)
    {
        s = s + (vin(k) - m) * (vin(k) - m);
    }
    ASSERT(false) << "Function is broken currently!";

    return s / static_cast<T>(vin.size());
}

template <typename T> T rootMeanSquare(const Vector<T>& vin)
{
    assert(vin.size() > 0);

    T s = 0.0;
    for (size_t k = 0; k < vin.size(); k++)
    {
        s = s + vin(k) * vin(k);
    }

    return std::sqrt(s / static_cast<T>(vin.size()));
}

template <typename T> Vector<T> uniformRandom(const size_t num_elements, const int res = 10000)
{
    Vector<T> vout(num_elements);
    const T inverse_res = 1.0 / static_cast<T>(res - 1);

    for (size_t k = 0; k < num_elements; k++)
    {
        vout(k) = static_cast<T>(rand() % res) * inverse_res;
    }

    return vout;
}

template <typename T> Vector<T> uniformRandomInt(const size_t num_elements, const int max_num)
{
    Vector<T> vout(num_elements);
    const int max_num_increased = max_num + 1;

    for (size_t k = 0; k < num_elements; k++)
    {
        vout(k) = static_cast<T>(rand() % max_num_increased);
    }

    return vout;
}

inline Vector<size_t> randomPermutation(const size_t num_elements)
{
    Vector<size_t> v_numbers(num_elements);
    Vector<float> v_rand = uniformRandom<float>(num_elements);

    for (size_t k = 0; k < num_elements; k++)
    {
        v_numbers(k) = k;
    }

    bool done = false;

    while (!done)
    {
        bool did_swap = false;
        for (size_t k = 0; k < num_elements - 1; k++)
        {
            if (v_rand(k) > v_rand(k + 1))
            {
                const float temp = v_rand(k);
                v_rand(k) = v_rand(k + 1);
                v_rand(k + 1) = temp;

                const size_t temp_i = v_numbers(k);
                v_numbers(k) = v_numbers(k + 1);
                v_numbers(k + 1) = temp_i;

                did_swap = true;
            }
        }
        if (!did_swap)
        {
            done = true;
        }
    }

    return v_numbers;
}

template <typename T> Vector<size_t> sortedIndices(const Vector<T>& vin)
{
    Vector<size_t> v_indices(vin.size());
    Vector<T> v_temp(vin);

    for (size_t k = 0; k < vin.size(); k++)
    {
        v_indices(k) = k;
    }

    bool done = false;

    while (!done)
    {
        bool did_swap = false;
        for (size_t k = 0; k < vin.size() - 1; k++)
        {
            if (v_temp(k) > v_temp(k + 1))
            {
                const T temp = v_temp(k);
                v_temp(k) = v_temp(k + 1);
                v_temp(k + 1) = temp;

                const size_t temp_i = v_indices(k);
                v_indices(k) = v_indices(k + 1);
                v_indices(k + 1) = temp_i;

                did_swap = true;
            }
        }
        if (!did_swap)
        {
            done = true;
        }
    }

    return v_indices;
}

template <typename T>
std::pair<Vector<T>, Vector<size_t>> sortValuesAndIndices(const Vector<T>& vin)
{
    Vector<size_t> v_indices(vin.size());
    Vector<T> v_values(vin);

    for (size_t k = 0; k < vin.size(); k++)
    {
        v_indices(k) = k;
    }

    bool done = false;

    while (!done)
    {
        bool did_swap = false;
        for (size_t k = 0; k < vin.size() - 1; k++)
        {
            if (v_values(k) > v_values(k + 1))
            {
                const T temp = v_values(k);
                v_values(k) = v_values(k + 1);
                v_values(k + 1) = temp;

                const size_t temp_i = v_indices(k);
                v_indices(k) = v_indices(k + 1);
                v_indices(k + 1) = temp_i;

                did_swap = true;
            }
        }
        if (!did_swap)
        {
            done = true;
        }
    }

    return std::pair<Vector<T>, Vector<size_t>>(v_values, v_indices);
}

template <typename Y, typename T> Vector<Y> roundAndCast(const Vector<T>& vin)
{
    Vector<Y> vout(vin.size());
    for (size_t k = 0; k < vin.size(); k++)
    {
        vout(k) = static_cast<Y>(std::round(vin(k)));
    }

    return vout;
}

template <typename T> Vector<T> integerLinspace(const T x0, const T x1)
{
    const T num_values = static_cast<int>(x1 - x0 + static_cast<T>(1));
    ASSERT(num_values > 0);
    Vector<T> v(num_values);

    v(0) = x0;
    for (size_t k = 1; k < num_values; k++)
    {
        v(k) = v(k - 1) + static_cast<T>(1);
    }

    return v;
}

template <typename T> Vector<T> vectorWithOnes(const size_t num_values)
{
    Vector<T> v(num_values);
    const T one_casted = static_cast<T>(1);
    for (size_t k = 0; k < num_values; k++)
    {
        v(k) = one_casted;
    }
    return v;
}

}  // namespace plot_tool

#endif