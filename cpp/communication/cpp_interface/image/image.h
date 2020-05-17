#ifndef PLOT_TOOL_IMAGE_CORE_H_
#define PLOT_TOOL_IMAGE_CORE_H_

#include <assert.h>
#include <stdint.h>

#include <iostream>

#include "logging.h"
#include "math/math.h"

namespace plot_tool
{
/* **** Data structures declarations **** */

template <typename T> class ImageC1
{
private:
    T* data;
    size_t width;
    size_t height;
    size_t num_rows;
    size_t num_cols;
    bool is_allocated;

public:
    ImageC1();
    ImageC1(const size_t num_rows_, const size_t num_cols_);
    ~ImageC1();

    T& operator()(const size_t r, const size_t c);
    const T& operator()(const size_t r, const size_t c) const;

    bool isAllocated() const;
    size_t rows() const;
    size_t cols() const;

    void reallocate(const size_t num_rows_, const size_t num_cols_);

    void multiply(T factor);
    void divide(T divisor);
    void add(T term);
    void fill(T fill_val);
    void mapBetween(T image_min, T image_max, T min_value, T max_value);
    Vector<size_t> getHistogram() const;
    Vector<T> getImageCol(const size_t col) const;
    Vector<T> getImageRow(const size_t row) const;
    void getSubImage(ImageC1<T>& sub_image,
                     const size_t from_row,
                     const size_t from_col,
                     const size_t width,
                     const size_t height) const;
    size_t numElements() const;
    T* getDataPointer() const;
};

template <typename T> ImageC1<T>::~ImageC1()
{
    if (is_allocated)
    {
        delete[] data;
        is_allocated = false;
        num_rows = 0;
        num_cols = 0;
    }
}

template <typename T> ImageC1<T>::ImageC1() : num_rows(0), num_cols(0), is_allocated(false) {}

template <typename T> ImageC1<T>::ImageC1(const size_t num_rows_, const size_t num_cols_)
{
    data = new T[num_rows_ * num_cols_];
    num_rows = num_rows_;
    num_cols = num_cols_;
    is_allocated = true;
}

template <typename T> void ImageC1<T>::reallocate(const size_t num_rows_, const size_t num_cols_)
{
    if (is_allocated)
    {
        delete[] data;
        is_allocated = false;
        num_rows = 0;
        num_cols = 0;
    }

    data = new T[num_rows_ * num_cols_];
    num_rows = num_rows_;
    num_cols = num_cols_;
    is_allocated = true;
}

template <typename T>
void ImageC1<T>::mapBetween(T image_min, T image_max, T min_value, T max_value)
{
    const T factor = (max_value - min_value) / (image_max - image_min);
    for (int idx = 0; idx < num_rows * num_cols; idx++)
    {
        data[idx] = data[idx] * factor + min_value;
    }
}

template <typename T> size_t ImageC1<T>::rows() const
{
    return num_rows;
}

template <typename T> size_t ImageC1<T>::cols() const
{
    return num_cols;
}

template <typename T> size_t ImageC1<T>::numElements() const
{
    return num_rows * num_cols;
}

template <typename T> T* ImageC1<T>::getDataPointer() const
{
    return data;
}

template <typename T> Vector<T> ImageC1<T>::getImageCol(const size_t col) const
{
    Vector<T> image_col(num_rows);
    for (size_t r = 0; r < num_rows; r++)
    {
        image_col(r) = data[r * num_cols + col];
    }

    return image_col;
}

template <typename T> Vector<T> ImageC1<T>::getImageRow(const size_t row) const
{
    Vector<T> image_row(num_cols);
    for (size_t c = 0; c < num_cols; c++)
    {
        image_row(c) = data[row * num_cols + c];
    }

    return image_row;
}

template <typename T> Vector<size_t> ImageC1<T>::getHistogram() const
{
    Vector<size_t> histogram(255);

    for (size_t k = 0; k < histogram.size(); k++)
    {
        histogram(k) = 0;
    }

    for (size_t r = 0; r < num_rows; r++)
    {
        for (size_t c = 0; c < num_cols; c++)
        {
            histogram(data[r * num_cols + c]) += 1;
        }
    }
    return histogram;
}

template <typename T>
void ImageC1<T>::getSubImage(ImageC1<T>& sub_image,
                             const size_t from_row,
                             const size_t from_col,
                             const size_t width,
                             const size_t height) const
{
    assert(from_row + height < num_rows);
    assert(from_col + width < num_cols);

    sub_image.resize(height, width);
    for (size_t r = 0; r < height; r++)
    {
        for (size_t c = 0; c < width; c++)
        {
            sub_image(r, c) = data[(r + from_row) * num_cols + c + from_col];
        }
    }
}

template <typename T> void ImageC1<T>::multiply(T factor)
{
    for (size_t idx = 0; idx < num_rows * num_cols; idx++)
    {
        data[idx] = data[idx] * factor;
    }
}

template <typename T> void ImageC1<T>::fill(T fill_val)
{
    for (size_t idx = 0; idx < num_rows * num_cols; idx++)
    {
        data[idx] = fill_val;
    }
}

template <typename T> void ImageC1<T>::divide(T divisor)
{
    const T division_factor = 1.0 / divisor;
    for (size_t idx = 0; idx < num_rows * num_cols; idx++)
    {
        data[idx] = data[idx] * division_factor;
    }
}

template <typename T> void ImageC1<T>::add(T term)
{
    for (size_t idx = 0; idx < num_rows * num_cols; idx++)
    {
        data[idx] = data[idx] + term;
    }
}

template <typename T> T& ImageC1<T>::operator()(const size_t r, const size_t c)
{
    assert(r < num_rows && "Row index is larger than num_rows-1!");
    assert(c < num_cols && "Column index is larger than num_cols-1!");

    return data[r * num_cols + c];
}

template <typename T> const T& ImageC1<T>::operator()(const size_t r, const size_t c) const
{
    assert(r < num_rows && "Row index is larger than num_rows-1!");
    assert(c < num_cols && "Column index is larger than num_cols-1!");

    return data[r * num_cols + c];
}

template <typename T> bool ImageC1<T>::isAllocated() const
{
    return is_allocated;
}

}  // namespace plot_tool

#endif
