#ifndef MATRIX_DYNAMIC_CLASS_H_
#define MATRIX_DYNAMIC_CLASS_H_

namespace plot_tool
{
template <typename T> class Matrix
{
protected:
    T* data_;
    size_t num_rows_;
    size_t num_cols_;
    bool is_allocated_;

public:
    Matrix();
    Matrix(const size_t num_rows, const size_t num_cols);
    Matrix(const Matrix<T>& m);
    Matrix(const std::vector<std::vector<T>>& vm);
    Matrix(const std::initializer_list<std::initializer_list<T>>& il);
    Matrix(Matrix<T>&& m);
    Matrix(const T a[3][3]);
    ~Matrix();

    Matrix<T>&& move();

    T& operator()(const size_t r, const size_t c);
    const T& operator()(const size_t r, const size_t c) const;
    T& operator()(const size_t idx);
    const T& operator()(const size_t idx) const;

    Matrix<T> operator()(const size_t row, const IndexSpan& col_idx_span) const;
    Matrix<T> operator()(const IndexSpan& row_idx_span, const size_t col) const;
    Matrix<T> operator()(const IndexSpan& row_idx_span, const IndexSpan& col_idx_span) const;

    T& operator()(const EndIndex& row_end_idx, const size_t c);
    const T& operator()(const EndIndex& row_end_idx, const size_t c) const;
    T& operator()(const size_t r, const EndIndex& col_end_idx);
    const T& operator()(const size_t r, const EndIndex& col_end_idx) const;
    Matrix<T>& operator=(const Matrix<T>& m);
    Matrix<T>& operator=(Matrix<T>&& m);

    void removeRowAtIndex(const size_t row_idx);
    void removeRowsAtIndices(const IndexSpan& idx_span);
    void removeColAtIndex(const size_t col_idx);
    void removeColsAtIndices(const IndexSpan& idx_span);
    void resize(const size_t num_rows, const size_t num_cols);
    size_t rows() const;
    size_t cols() const;
    size_t size() const;
    size_t numElements() const;
    void hCat(const Vector<T>& v);
    void vCat(const Vector<T>& v);

    void hCat(const Matrix<T>& m);
    void vCat(const Matrix<T>& m);

    void hCat(const Vec2D<T>& v);
    void vCat(const Vec2D<T>& v);
    void hCat(const Vec3D<T>& v);
    void vCat(const Vec3D<T>& v);
    void hCat(const Vec4D<T>& v);
    void vCat(const Vec4D<T>& v);

    bool isAllocated() const;
    void fill(const T val);
    void switchRows(size_t r0, size_t r1);
    void switchColumns(size_t c0, size_t c1);
    T* getDataPointer() const;
    void setInternalData(T* const input_ptr, const size_t num_rows, const size_t num_cols);
    Matrix<T> getTranspose() const;
    void transpose();

    void addToAllCols(const Vector<T>& v);
    void addToAllRows(const Vector<T>& v);
    void addToAllCols(const Matrix<T>& m);
    void addToAllRows(const Matrix<T>& m);

    void addToCol(const size_t col_idx, const Vector<T>& v);
    void addToRow(const size_t row_idx, const Vector<T>& v);
    void addToCol(const size_t col_idx, const Matrix<T>& m);
    void addToRow(const size_t row_idx, const Matrix<T>& m);

    Vector<T> toVector() const;

    Vector<T> getColumnAsVector(const size_t column_idx) const;
    Vector<T> getRowAsVector(const size_t row_idx) const;
    Matrix<T> getColumn(const size_t column_idx) const;
    Matrix<T> getRow(const size_t row_idx) const;
    size_t lastRowIdx() const;
    size_t lastColIdx() const;

    T max() const;
    T min() const;
    Matrix<T> minAlongCols() const;
    Matrix<T> minAlongRows() const;
    Matrix<T> maxAlongCols() const;
    Matrix<T> maxAlongRows() const;
    T sum() const;
    Matrix<T> sumAlongRows() const;
    Matrix<T> sumAlongCols() const;
};
}  // namespace plot_tool

#endif
