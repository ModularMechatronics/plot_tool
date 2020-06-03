#ifndef PLOT_TOOL_H_
#define PLOT_TOOL_H_

#include "internal/client.h"
#include "shared/transmission.h"
#include "shared/util_functions.h"

namespace plot_tool
{
inline void figure()
{
    TxList tx_list;
    tx_list.append(Command::FUNCTION, Function::FIGURE);
    tx_list.append(Command::HAS_PAYLOAD, false);

    sendTxList(tx_list);
}

inline void figure(const size_t figure_number)
{
    TxList tx_list;
    tx_list.append(Command::FUNCTION, Function::FIGURE);
    tx_list.append(Command::HAS_PAYLOAD, false);
    tx_list.append(Command::FIGURE_NUM, static_cast<char>(figure_number));

    sendTxList(tx_list);
}

inline void setPosition(const int x, const int y)
{
    TxList tx_list;
    tx_list.append(Command::FUNCTION, Function::POSITION);
    tx_list.append(Command::HAS_PAYLOAD, false);
    tx_list.append(Command::POS2D, Pos2D(x, y));

    sendTxList(tx_list);
}

inline void holdOn()
{
    TxList tx_list;
    tx_list.append(Command::FUNCTION, Function::HOLD_ON);
    tx_list.append(Command::HAS_PAYLOAD, false);

    sendTxList(tx_list);
}

inline void holdOff()
{
    TxList tx_list;
    tx_list.append(Command::FUNCTION, Function::HOLD_OFF);
    tx_list.append(Command::HAS_PAYLOAD, false);

    sendTxList(tx_list);
}

inline void clearFigure()
{
    TxList tx_list;
    tx_list.append(Command::FUNCTION, Function::CLEAR);
    tx_list.append(Command::HAS_PAYLOAD, false);

    sendTxList(tx_list);
}

inline void softClearFigure()
{
    TxList tx_list;
    tx_list.append(Command::FUNCTION, Function::SOFT_CLEAR);
    tx_list.append(Command::HAS_PAYLOAD, false);

    sendTxList(tx_list);
}

inline void view(const float azimuth, const float elevation)
{
    TxList tx_list;
    tx_list.append(Command::FUNCTION, Function::VIEW);
    tx_list.append(Command::HAS_PAYLOAD, false);
    tx_list.append(Command::AZIMUTH, azimuth);
    tx_list.append(Command::ELEVATION, elevation);

    sendTxList(tx_list);
}

inline void axis(const Bound3D& min_bound, const Bound3D& max_bound)
{
    TxList tx_list;
    tx_list.append(Command::FUNCTION, Function::AXES);
    tx_list.append(Command::HAS_PAYLOAD, false);
    tx_list.append(Command::AXES_DIMENSIONS, static_cast<char>(3));
    tx_list.append(Command::AXIS_MIN_MAX_VEC, std::pair<Bound3D, Bound3D>(min_bound, max_bound));

    sendTxList(tx_list);
}

inline void axis(const Bound2D& min_bound, const Bound2D& max_bound)
{
    assert(false && "Function not supported yet...");
    const Bound3D min_bound_3d(min_bound.x, min_bound.y, 0.0);
    const Bound3D max_bound_3d(max_bound.x, max_bound.y, 0.0);

    TxList tx_list;
    tx_list.append(Command::FUNCTION, Function::AXES);
    tx_list.append(Command::HAS_PAYLOAD, false);
    tx_list.append(Command::AXES_DIMENSIONS, static_cast<char>(2));
    tx_list.append(Command::AXIS_MIN_MAX_VEC,
                   std::pair<Bound3D, Bound3D>(min_bound_3d, max_bound_3d));

    sendTxList(tx_list);
}

template <typename T, typename... Us>
void surf(const Matrix<T>& x, const Matrix<T>& y, const Matrix<T>& z, const Us&... settings)
{
    assert(x.isAllocated() && "x is not allocated!");
    assert(y.isAllocated() && "y is not allocated!");
    assert(z.isAllocated() && "z is not allocated!");
    assert((x.rows() > 0) && (x.cols() > 0));
    assert((x.rows() == y.rows()) && (x.cols() == y.cols()));
    assert((x.rows() == z.rows()) && (x.cols() == z.cols()));

    TxList tx_list;
    tx_list.append(Command::FUNCTION, Function::SURF);
    tx_list.append(Command::DATA_STRUCTURE, DataStructure::MATRIX);
    tx_list.append(Command::DATA_TYPE, typeToDataTypeEnum<double>());
    tx_list.append(Command::NUM_BUFFERS_REQUIRED, static_cast<char>(3));
    tx_list.append(Command::BYTES_PER_ELEMENT, static_cast<char>(sizeof(double)));
    tx_list.append(Command::DIMENSION_2D, Dimension2D(x.rows(), x.cols()));
    tx_list.append(Command::NUM_ELEMENTS, x.numElements());
    tx_list.append(Command::NUM_BYTES, x.numElements() * sizeof(double));
    tx_list.append(Command::HAS_PAYLOAD, true);
    tx_list.extend(settings...);

    sendTxList(tx_list);

    if (std::is_same<T, double>::value)
    {
        sendData(x);
        sendData(y);
        sendData(z);
    }
    else
    {
        const Matrix<double> xd = x;
        const Matrix<double> yd = y;
        const Matrix<double> zd = z;

        sendData(xd);
        sendData(yd);
        sendData(zd);
    }
}

template <typename T, typename... Us>
void drawPolygonFrom4Points(const Point3D<T>& p0,
                            const Point3D<T>& p1,
                            const Point3D<T>& p2,
                            const Point3D<T>& p3,
                            const Us&... settings)
{
    TxList tx_list;
    tx_list.append(Command::FUNCTION, Function::POLYGON_FROM_4_POINTS);
    tx_list.append(Command::DATA_TYPE, typeToDataTypeEnum<T>());
    tx_list.append(Command::NUM_BUFFERS_REQUIRED, static_cast<char>(1));
    tx_list.append(Command::BYTES_PER_ELEMENT, static_cast<char>(sizeof(double)));
    tx_list.append(Command::NUM_BYTES, 4 * sizeof(Point3D<double>));
    tx_list.append(Command::HAS_PAYLOAD, true);
    tx_list.extend(settings...);

    sendTxList(tx_list);

    const size_t num_bytes = 4 * sizeof(Point3D<double>);

    char buffer[num_bytes];

    if (std::is_same<T, double>::value)
    {
        fillBufferWithObjects(buffer, p0, p1, p2, p3);
    }
    else
    {
        const Point3D<double> p0d = p0;
        const Point3D<double> p1d = p1;
        const Point3D<double> p2d = p2;
        const Point3D<double> p3d = p3;

        fillBufferWithObjects(buffer, p0d, p1d, p2d, p3d);
    }

    sendData(buffer, num_bytes);
}

template <typename T, typename... Us>
void plot(const Vector<T>& x, const Vector<T>& y, const Us&... settings)
{
    assert(x.isAllocated() && "x is not allocated!");
    assert(y.isAllocated() && "y is not allocated!");
    assert((x.size() > 0) && (x.size() == y.size()));

    TxList tx_list;
    tx_list.append(Command::FUNCTION, Function::PLOT2);
    tx_list.append(Command::DATA_STRUCTURE, DataStructure::VECTOR);
    tx_list.append(Command::DATA_TYPE, typeToDataTypeEnum<double>());
    tx_list.append(Command::NUM_BUFFERS_REQUIRED, static_cast<char>(2));
    tx_list.append(Command::BYTES_PER_ELEMENT, static_cast<char>(sizeof(double)));
    tx_list.append(Command::NUM_ELEMENTS, x.numElements());
    tx_list.append(Command::NUM_BYTES, x.numElements() * sizeof(double));
    tx_list.append(Command::HAS_PAYLOAD, true);
    tx_list.extend(settings...);

    sendTxList(tx_list);

    if (std::is_same<T, double>::value)
    {
        sendData(x);
        sendData(y);
    }
    else
    {
        const Vector<double> xd(x);
        const Vector<double> yd(y);
        sendData(xd);
        sendData(yd);
    }
}

template <typename T, typename... Us>
void plot3(const Vector<T>& x, const Vector<T>& y, const Vector<T>& z, const Us&... settings)
{
    assert(x.isAllocated() && "x is not allocated!");
    assert(y.isAllocated() && "y is not allocated!");
    assert(z.isAllocated() && "z is not allocated!");
    assert((x.size() > 0) && (x.size() == y.size()) && (x.size() == z.size()));

    TxList tx_list;
    tx_list.append(Command::FUNCTION, Function::PLOT3);
    tx_list.append(Command::DATA_STRUCTURE, DataStructure::VECTOR);
    tx_list.append(Command::DATA_TYPE, typeToDataTypeEnum<double>());
    tx_list.append(Command::NUM_BUFFERS_REQUIRED, static_cast<char>(3));
    tx_list.append(Command::BYTES_PER_ELEMENT, static_cast<char>(sizeof(double)));
    tx_list.append(Command::NUM_ELEMENTS, x.numElements());
    tx_list.append(Command::NUM_BYTES, x.numElements() * sizeof(double));
    tx_list.append(Command::HAS_PAYLOAD, true);
    tx_list.extend(settings...);

    sendTxList(tx_list);

    if (std::is_same<T, double>::value)
    {
        sendData(x);
        sendData(y);
        sendData(z);
    }
    else
    {
        const Vector<double> xd(x);
        const Vector<double> yd(y);
        const Vector<double> zd(z);
        sendData(xd);
        sendData(yd);
        sendData(zd);
    }
}

template <typename T, typename... Us>
void scatter(const Vector<T>& x, const Vector<T>& y, const Us&... settings)
{
    assert(x.isAllocated() && "x is not allocated!");
    assert(y.isAllocated() && "y is not allocated!");
    assert((x.size() > 0) && (x.size() == y.size()));

    TxList tx_list;
    tx_list.append(Command::FUNCTION, Function::SCATTER2);
    tx_list.append(Command::DATA_STRUCTURE, DataStructure::VECTOR);
    tx_list.append(Command::DATA_TYPE, typeToDataTypeEnum<double>());
    tx_list.append(Command::NUM_BUFFERS_REQUIRED, static_cast<char>(2));
    tx_list.append(Command::BYTES_PER_ELEMENT, static_cast<char>(sizeof(double)));
    tx_list.append(Command::NUM_ELEMENTS, x.numElements());
    tx_list.append(Command::NUM_BYTES, x.numElements() * sizeof(double));
    tx_list.append(Command::HAS_PAYLOAD, true);
    tx_list.extend(settings...);

    sendTxList(tx_list);

    if (std::is_same<T, double>::value)
    {
        sendData(x);
        sendData(y);
    }
    else
    {
        const Vector<double> xd(x);
        const Vector<double> yd(y);
        sendData(xd);
        sendData(yd);
    }
}

template <typename T, typename... Us>
void scatter3(const Vector<T>& x, const Vector<T>& y, const Vector<T>& z, const Us&... settings)
{
    assert(x.isAllocated() && "x is not allocated!");
    assert(y.isAllocated() && "y is not allocated!");
    assert(z.isAllocated() && "y is not allocated!");
    assert((x.size() > 0) && (x.size() == y.size()) && (x.size() == z.size()));

    TxList tx_list;
    tx_list.append(Command::FUNCTION, Function::SCATTER3);
    tx_list.append(Command::DATA_STRUCTURE, DataStructure::VECTOR);
    tx_list.append(Command::DATA_TYPE, typeToDataTypeEnum<double>());
    tx_list.append(Command::NUM_BUFFERS_REQUIRED, static_cast<char>(3));
    tx_list.append(Command::BYTES_PER_ELEMENT, static_cast<char>(sizeof(double)));
    tx_list.append(Command::NUM_ELEMENTS, x.numElements());
    tx_list.append(Command::NUM_BYTES, x.numElements() * sizeof(double));
    tx_list.append(Command::HAS_PAYLOAD, true);
    tx_list.extend(settings...);

    sendTxList(tx_list);

    if (std::is_same<T, double>::value)
    {
        sendData(x);
        sendData(y);
        sendData(z);
    }
    else
    {
        const Vector<double> xd(x);
        const Vector<double> yd(y);
        const Vector<double> zd(z);
        sendData(xd);
        sendData(yd);
        sendData(zd);
    }
}

template <typename T, typename... Us>
void drawLine(const Line3D<T>& line, const T t0, const T t1, const Us&... settings)
{
    const size_t num_bytes = sizeof(Line3D<double>) + sizeof(double) * 2;

    TxList tx_list;
    tx_list.append(Command::FUNCTION, Function::LINE3D);
    tx_list.append(Command::DATA_TYPE, typeToDataTypeEnum<double>());
    tx_list.append(Command::NUM_BUFFERS_REQUIRED, static_cast<char>(1));
    tx_list.append(Command::BYTES_PER_ELEMENT, static_cast<char>(sizeof(double)));
    tx_list.append(Command::NUM_BYTES, num_bytes);
    tx_list.append(Command::HAS_PAYLOAD, true);
    tx_list.extend(settings...);

    sendTxList(tx_list);

    char buffer[num_bytes];

    if (std::is_same<T, double>::value)
    {
        fillBufferWithObjects(buffer, line, t0, t1);
    }
    else
    {
        const Line3D<double> ld = line;
        const double t0d = t0;
        const double t1d = t1;

        fillBufferWithObjects(buffer, ld, t0d, t1d);
    }

    sendData(buffer, num_bytes);
}

template <typename T, typename... Us>
void drawLineBetweenPoints(const Point3D<T>& p0, const Point3D<T>& p1, const Us&... settings)
{
    const size_t num_bytes = 2 * sizeof(Point3D<double>);

    TxList tx_list;
    tx_list.append(Command::FUNCTION, Function::LINE_BETWEEN_POINTS_3D);
    tx_list.append(Command::DATA_TYPE, typeToDataTypeEnum<double>());
    tx_list.append(Command::NUM_BUFFERS_REQUIRED, static_cast<char>(1));
    tx_list.append(Command::BYTES_PER_ELEMENT, static_cast<char>(sizeof(double)));
    tx_list.append(Command::NUM_BYTES, num_bytes);
    tx_list.append(Command::HAS_PAYLOAD, true);
    tx_list.extend(settings...);

    sendTxList(tx_list);

    char buffer[num_bytes];

    if (std::is_same<T, double>::value)
    {
        fillBufferWithObjects(buffer, p0, p1);
        sendData(buffer, num_bytes);
    }
    else
    {
        const Point3D<double> p0d = p0;
        const Point3D<double> p1d = p1;
        fillBufferWithObjects(buffer, p0d, p1d);
        sendData(buffer, num_bytes);
    }
}

template <typename T, typename... Us>
void drawPlaneXY(const PointXY<T>& p0,
                 const PointXY<T>& p1,
                 const Plane<T>& plane,
                 const Us&... settings)
{
    const size_t num_bytes = sizeof(Plane<double>) + sizeof(PointXY<double>) * 2;

    TxList tx_list;
    tx_list.append(Command::FUNCTION, Function::PLANE_XY);
    tx_list.append(Command::DATA_TYPE, typeToDataTypeEnum<double>());
    tx_list.append(Command::NUM_BUFFERS_REQUIRED, static_cast<char>(1));
    tx_list.append(Command::BYTES_PER_ELEMENT, static_cast<char>(sizeof(double)));
    tx_list.append(Command::NUM_BYTES, num_bytes);
    tx_list.append(Command::HAS_PAYLOAD, true);
    tx_list.extend(settings...);

    sendTxList(tx_list);

    char buffer[num_bytes];

    if (std::is_same<T, double>::value)
    {
        fillBufferWithObjects(buffer, plane, p0, p1);
    }
    else
    {
        const Plane<double> pd = plane;
        const PointXY<double> p0d = p0;
        const PointXY<double> p1d = p1;
        fillBufferWithObjects(buffer, pd, p0d, p1d);
    }

    sendData(buffer, num_bytes);
}

template <typename T, typename... Us>
void drawPlaneXZ(const PointXZ<T>& p0,
                 const PointXZ<T>& p1,
                 const Plane<T>& plane,
                 const Us&... settings)
{
    const size_t num_bytes = sizeof(Plane<double>) + sizeof(PointXZ<double>) * 2;

    TxList tx_list;
    tx_list.append(Command::FUNCTION, Function::PLANE_XZ);
    tx_list.append(Command::DATA_TYPE, typeToDataTypeEnum<double>());
    tx_list.append(Command::NUM_BUFFERS_REQUIRED, static_cast<char>(1));
    tx_list.append(Command::BYTES_PER_ELEMENT, static_cast<char>(sizeof(double)));
    tx_list.append(Command::NUM_BYTES, num_bytes);
    tx_list.append(Command::HAS_PAYLOAD, true);
    tx_list.extend(settings...);

    sendTxList(tx_list);

    char buffer[num_bytes];

    if (std::is_same<T, double>::value)
    {
        fillBufferWithObjects(buffer, plane, p0, p1);
    }
    else
    {
        const Plane<double> pd = plane;
        const PointXZ<double> p0d = p0;
        const PointXZ<double> p1d = p1;
        fillBufferWithObjects(buffer, pd, p0d, p1d);
    }

    sendData(buffer, num_bytes);
}

template <typename T, typename... Us>
void drawPlaneYZ(const PointYZ<T>& p0,
                 const PointYZ<T>& p1,
                 const Plane<T>& plane,
                 const Us&... settings)
{
    const size_t num_bytes = sizeof(Plane<double>) + sizeof(PointYZ<double>) * 2;

    TxList tx_list;
    tx_list.append(Command::FUNCTION, Function::PLANE_YZ);
    tx_list.append(Command::DATA_TYPE, typeToDataTypeEnum<double>());
    tx_list.append(Command::NUM_BUFFERS_REQUIRED, static_cast<char>(1));
    tx_list.append(Command::BYTES_PER_ELEMENT, static_cast<char>(sizeof(double)));
    tx_list.append(Command::NUM_BYTES, num_bytes);
    tx_list.append(Command::HAS_PAYLOAD, true);
    tx_list.extend(settings...);

    sendTxList(tx_list);

    char buffer[num_bytes];

    if (std::is_same<T, double>::value)
    {
        fillBufferWithObjects(buffer, plane, p0, p1);
    }
    else
    {
        const Plane<double> pd = plane;
        const PointYZ<double> p0d = p0;
        const PointYZ<double> p1d = p1;
        fillBufferWithObjects(buffer, pd, p0d, p1d);
    }

    sendData(buffer, num_bytes);
}

template <typename T, typename... Us> void imShow(const ImageC1<T>& img, const Us&... settings)
{
    static_assert(std::is_same<T, double>::value, TYPE_ERROR_MSG);
    assert(false && "Function not implemented yet!");

    TxList tx_list;
    tx_list.append(Command::FUNCTION, Function::IM_SHOW);
    tx_list.append(Command::DATA_STRUCTURE, DataStructure::IMAGE);
    tx_list.append(Command::DATA_TYPE, typeToDataTypeEnum<T>());
    tx_list.append(Command::NUM_BUFFERS_REQUIRED, static_cast<char>(1));
    tx_list.append(Command::BYTES_PER_ELEMENT, static_cast<char>(sizeof(T)));
    tx_list.append(Command::NUM_ELEMENTS, img.numElements());
    tx_list.append(Command::NUM_BYTES, img.numElements() * sizeof(T));
    tx_list.append(Command::HAS_PAYLOAD, true);
    tx_list.extend(settings...);

    sendTxList(tx_list);

    sendData(img);
}

}  // namespace plot_tool

#endif
