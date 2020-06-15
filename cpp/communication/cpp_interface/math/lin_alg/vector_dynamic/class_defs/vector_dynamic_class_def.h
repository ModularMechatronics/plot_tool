#ifndef PLOT_TOOL_VECTOR_DYNAMIC_CLASS_H_
#define PLOT_TOOL_VECTOR_DYNAMIC_CLASS_H_

#include <iterator>

namespace plot_tool
{
template <typename T> class Vector
{
protected:
    T* data_;
    size_t vector_length_;
    bool is_allocated_;

public:
    Vector();
    Vector(const size_t vector_length);
    Vector(const Vector<T>& v);
    Vector(Vector<T>&& v);
    template <typename Y> Vector(const Vector<Y>& v);

    Vec2D<T> toVec2D() const;
    Vec3D<T> toVec3D() const;
    Vec4D<T> toVec4D() const;

    Vector(const std::initializer_list<T>& il);
    Vector(const std::vector<T>& v);

    ~Vector();

    Vector<T>&& move();

    Vector<T>& operator=(const Vector<T>& v);
    Vector<T>& operator=(Vector<T>&& v);
    T& operator()(const size_t idx);
    const T& operator()(const size_t idx) const;
    T& operator()(const EndIndex& end_idx);
    const T& operator()(const EndIndex& end_idx) const;

    template <typename Y> Vector<T> operator()(const Vector<Y>& idx_vector) const;
    Vector<T> operator()(const IndexSpan& idx_span) const;

    void removeElementAtIndex(const size_t idx);
    void removeElementsAtIndices(const IndexSpan& idx_span);
    size_t size() const;
    size_t numElements() const;
    bool isAllocated() const;
    void fill(const T& val);
    void resize(const size_t vector_length);
    size_t endIndex() const;
    T* getDataPointer() const;

    void pushBack(const T& new_value);
    void pushFront(const T& new_value);
    void insertAtIndex(const T& new_value, const size_t idx);

    void setInternalData(T* const input_ptr, const size_t num_elements);

    void sort();
    Vector<T> sorted() const;
    Vector<T> normalized() const;
    Vector<T> vectorBetweenPoints(const Point<T>& end_point) const;
    Vector<T> normalizedVectorBetweenPoints(const Point<T>& end_point) const;
    T squaredNorm() const;
    T norm() const;
    Matrix<T> outerProduct(const Vector<T>& v) const;
    Point<T> mirrorPointInThis(const Point<T>& point_to_mirror) const;
    T angleBetweenVectors(const Vector<T>& v) const;
    Matrix<T> toColumnVectorMat() const;
    Matrix<T> toRowVectorMat() const;
    size_t countNumNonZeroElements() const;

    T* begin() const;
    T* end() const;
    Vector<size_t> findIndicesOf(const T& item_to_find) const;
    template <typename Y> Vector<T>& operator=(const Vector<Y>& rhs);

    T max() const;
    T min() const;
    T sum() const;
};
}  // namespace plot_tool

#endif
