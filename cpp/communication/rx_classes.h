#ifndef RX_CLASSES_H_
#define RX_CLASSES_H_

#include <arl/math/math.h>

#include <utility>

#include "communication/shared/plot_attributes.h"
#include "communication/shared/transmission.h"
#include "communication/shared/util_functions.h"

namespace plot_tool
{
class RxReceiveBase
{
private:
    Command command_;

public:
    RxReceiveBase() = default;
    RxReceiveBase(const Command command) : command_(command) {}

    virtual ~RxReceiveBase() {}

    Command getCommandType() const
    {
        return command_;
    }

    virtual size_t sizeOfData() const = 0;
    virtual const char* getDataPointer() const = 0;
};

// Input buffer should start at first data byte

class NumBuffersRequiredRx : public RxReceiveBase
{
private:
    char data_;

public:
    typedef char data_type;
    char getData() const
    {
        return data_;
    }
    NumBuffersRequiredRx() : RxReceiveBase(Command::NUM_BUFFERS_REQUIRED) {}
    NumBuffersRequiredRx(const char data)
        : RxReceiveBase(Command::NUM_BUFFERS_REQUIRED), data_(data)
    {
    }
    NumBuffersRequiredRx(const char* const buffer) : RxReceiveBase(Command::NUM_BUFFERS_REQUIRED)
    {
        plot_tool::fillObjectsFromBuffer(buffer, data_);
    }

    size_t sizeOfData() const override
    {
        return sizeof(char);
    }
    const char* getDataPointer() const override
    {
        return reinterpret_cast<const char* const>(&data_);
    }
};

class NumBytesRx : public RxReceiveBase
{
private:
    size_t data_;

public:
    typedef size_t data_type;
    size_t getData() const
    {
        return data_;
    }
    NumBytesRx() : RxReceiveBase(Command::NUM_BYTES) {}
    NumBytesRx(const size_t data) : RxReceiveBase(Command::NUM_BYTES), data_(data) {}
    NumBytesRx(const char* const buffer) : RxReceiveBase(Command::NUM_BYTES)
    {
        plot_tool::fillObjectsFromBuffer(buffer, data_);
    }

    size_t sizeOfData() const override
    {
        return sizeof(size_t);
    }
    const char* getDataPointer() const override
    {
        return reinterpret_cast<const char* const>(&data_);
    }
};

class DataStructureRx : public RxReceiveBase
{
private:
    DataStructure data_;

public:
    typedef DataStructure data_type;
    DataStructure getData() const
    {
        return data_;
    }
    DataStructureRx() : RxReceiveBase(Command::DATA_STRUCTURE) {}
    DataStructureRx(const DataStructure data) : RxReceiveBase(Command::DATA_STRUCTURE), data_(data)
    {
    }
    DataStructureRx(const char* const buffer) : RxReceiveBase(Command::DATA_STRUCTURE)
    {
        plot_tool::fillObjectsFromBuffer(buffer, data_);
    }

    size_t sizeOfData() const override
    {
        return sizeof(DataStructure);
    }
    const char* getDataPointer() const override
    {
        return reinterpret_cast<const char* const>(&data_);
    }
};

class BytesPerElementRx : public RxReceiveBase
{
private:
    char data_;

public:
    typedef char data_type;
    char getData() const
    {
        return data_;
    }
    BytesPerElementRx() : RxReceiveBase(Command::BYTES_PER_ELEMENT) {}
    BytesPerElementRx(const char data) : RxReceiveBase(Command::BYTES_PER_ELEMENT), data_(data) {}
    BytesPerElementRx(const char* const buffer) : RxReceiveBase(Command::BYTES_PER_ELEMENT)
    {
        plot_tool::fillObjectsFromBuffer(buffer, data_);
    }

    size_t sizeOfData() const override
    {
        return sizeof(char);
    }
    const char* getDataPointer() const override
    {
        return reinterpret_cast<const char* const>(&data_);
    }
};

class DataTypeRx : public RxReceiveBase
{
private:
    DataType data_;

public:
    typedef DataType data_type;
    DataType getData() const
    {
        return data_;
    }
    DataTypeRx() : RxReceiveBase(Command::DATA_TYPE) {}
    DataTypeRx(const DataType data) : RxReceiveBase(Command::DATA_TYPE), data_(data) {}
    DataTypeRx(const char* const buffer) : RxReceiveBase(Command::DATA_TYPE)
    {
        plot_tool::fillObjectsFromBuffer(buffer, data_);
    }

    size_t sizeOfData() const override
    {
        return sizeof(DataType);
    }
    const char* getDataPointer() const override
    {
        return reinterpret_cast<const char* const>(&data_);
    }
};

class NumElementsRx : public RxReceiveBase
{
private:
    size_t data_;

public:
    typedef size_t data_type;
    size_t getData() const
    {
        return data_;
    }
    NumElementsRx() : RxReceiveBase(Command::NUM_ELEMENTS) {}
    NumElementsRx(const size_t data) : RxReceiveBase(Command::NUM_ELEMENTS), data_(data) {}
    NumElementsRx(const char* const buffer) : RxReceiveBase(Command::NUM_ELEMENTS)
    {
        plot_tool::fillObjectsFromBuffer(buffer, data_);
    }

    size_t sizeOfData() const override
    {
        return sizeof(size_t);
    }
    const char* getDataPointer() const override
    {
        return reinterpret_cast<const char* const>(&data_);
    }
};

class Dimension2dRx : public RxReceiveBase
{
private:
    Dimension2D data_;

public:
    typedef Dimension2D data_type;
    Dimension2D getData() const
    {
        return data_;
    }
    Dimension2dRx() : RxReceiveBase(Command::DIMENSION_2D) {}
    Dimension2dRx(const Dimension2D data) : RxReceiveBase(Command::DIMENSION_2D), data_(data) {}
    Dimension2dRx(const char* const buffer) : RxReceiveBase(Command::DIMENSION_2D)
    {
        plot_tool::fillObjectsFromBuffer(buffer, data_);
    }

    size_t sizeOfData() const override
    {
        return sizeof(Dimension2D);
    }
    const char* getDataPointer() const override
    {
        return reinterpret_cast<const char* const>(&data_);
    }
};

class HasPayloadRx : public RxReceiveBase
{
private:
    bool data_;

public:
    typedef bool data_type;
    bool getData() const
    {
        return data_;
    }
    HasPayloadRx() : RxReceiveBase(Command::HAS_PAYLOAD) {}
    HasPayloadRx(const bool data) : RxReceiveBase(Command::HAS_PAYLOAD), data_(data) {}
    HasPayloadRx(const char* const buffer) : RxReceiveBase(Command::HAS_PAYLOAD)
    {
        plot_tool::fillObjectsFromBuffer(buffer, data_);
    }

    size_t sizeOfData() const override
    {
        return sizeof(bool);
    }
    const char* getDataPointer() const override
    {
        return reinterpret_cast<const char* const>(&data_);
    }
};

class AzimuthRx : public RxReceiveBase
{
private:
    float data_;

public:
    typedef float data_type;
    float getData() const
    {
        return data_;
    }
    AzimuthRx() : RxReceiveBase(Command::AZIMUTH) {}
    AzimuthRx(const float data) : RxReceiveBase(Command::AZIMUTH), data_(data) {}
    AzimuthRx(const char* const buffer) : RxReceiveBase(Command::AZIMUTH)
    {
        plot_tool::fillObjectsFromBuffer(buffer, data_);
    }

    size_t sizeOfData() const override
    {
        return sizeof(float);
    }
    const char* getDataPointer() const override
    {
        return reinterpret_cast<const char* const>(&data_);
    }
};

class ElevationRx : public RxReceiveBase
{
private:
    float data_;

public:
    typedef float data_type;
    float getData() const
    {
        return data_;
    }
    ElevationRx() : RxReceiveBase(Command::ELEVATION) {}
    ElevationRx(const float data) : RxReceiveBase(Command::ELEVATION), data_(data) {}
    ElevationRx(const char* const buffer) : RxReceiveBase(Command::ELEVATION)
    {
        plot_tool::fillObjectsFromBuffer(buffer, data_);
    }

    size_t sizeOfData() const override
    {
        return sizeof(float);
    }
    const char* getDataPointer() const override
    {
        return reinterpret_cast<const char* const>(&data_);
    }
};

class AxesDimensionsRx : public RxReceiveBase
{
private:
    char data_;

public:
    typedef char data_type;
    char getData() const
    {
        return data_;
    }
    AxesDimensionsRx() : RxReceiveBase(Command::AXES_DIMENSIONS) {}
    AxesDimensionsRx(const char data) : RxReceiveBase(Command::AXES_DIMENSIONS), data_(data) {}
    AxesDimensionsRx(const char* const buffer) : RxReceiveBase(Command::AXES_DIMENSIONS)
    {
        plot_tool::fillObjectsFromBuffer(buffer, data_);
    }

    size_t sizeOfData() const override
    {
        return sizeof(char);
    }
    const char* getDataPointer() const override
    {
        return reinterpret_cast<const char* const>(&data_);
    }
};

class AxesMinMaxVecRx : public RxReceiveBase
{
private:
    std::pair<arl::Vec3D<double>, arl::Vec3D<double>> data_;

public:
    typedef std::pair<arl::Vec3D<double>, arl::Vec3D<double>> data_type;
    std::pair<arl::Vec3D<double>, arl::Vec3D<double>> getData() const
    {
        return data_;
    }
    AxesMinMaxVecRx() : RxReceiveBase(Command::AXIS_MIN_MAX_VEC) {}
    AxesMinMaxVecRx(const std::pair<arl::Vec3D<double>, arl::Vec3D<double>> data)
        : RxReceiveBase(Command::AXIS_MIN_MAX_VEC), data_(data)
    {
    }
    AxesMinMaxVecRx(const char* const buffer) : RxReceiveBase(Command::AXIS_MIN_MAX_VEC)
    {
        plot_tool::fillObjectsFromBuffer(buffer, data_);
    }

    size_t sizeOfData() const override
    {
        return sizeof(std::pair<arl::Vec3D<double>, arl::Vec3D<double>>);
    }
    const char* getDataPointer() const override
    {
        return reinterpret_cast<const char* const>(&data_);
    }
};

class LinewidthRx : public RxReceiveBase
{
private:
    Linewidth data_;

public:
    typedef Linewidth data_type;
    Linewidth getData() const
    {
        return data_;
    }
    LinewidthRx() : RxReceiveBase(Command::LINEWIDTH) {}
    LinewidthRx(const Linewidth data) : RxReceiveBase(Command::LINEWIDTH), data_(data) {}
    LinewidthRx(const char* const buffer) : RxReceiveBase(Command::LINEWIDTH)
    {
        plot_tool::fillObjectsFromBuffer(buffer, data_);
    }

    size_t sizeOfData() const override
    {
        return sizeof(Linewidth);
    }
    const char* getDataPointer() const override
    {
        return reinterpret_cast<const char* const>(&data_);
    }
};

class FaceColorRx : public RxReceiveBase
{
private:
    FaceColor data_;

public:
    typedef FaceColor data_type;
    FaceColor getData() const
    {
        return data_;
    }
    FaceColorRx() : RxReceiveBase(Command::FACE_COLOR) {}
    FaceColorRx(const FaceColor data) : RxReceiveBase(Command::FACE_COLOR), data_(data) {}
    FaceColorRx(const char* const buffer) : RxReceiveBase(Command::FACE_COLOR)
    {
        plot_tool::fillObjectsFromBuffer(buffer, data_);
    }

    size_t sizeOfData() const override
    {
        return sizeof(FaceColor);
    }
    const char* getDataPointer() const override
    {
        return reinterpret_cast<const char* const>(&data_);
    }
};

class EdgeColorRx : public RxReceiveBase
{
private:
    EdgeColor data_;

public:
    typedef EdgeColor data_type;
    EdgeColor getData() const
    {
        return data_;
    }
    EdgeColorRx() : RxReceiveBase(Command::EDGE_COLOR) {}
    EdgeColorRx(const EdgeColor data) : RxReceiveBase(Command::EDGE_COLOR), data_(data) {}
    EdgeColorRx(const char* const buffer) : RxReceiveBase(Command::EDGE_COLOR)
    {
        plot_tool::fillObjectsFromBuffer(buffer, data_);
    }

    size_t sizeOfData() const override
    {
        return sizeof(EdgeColor);
    }
    const char* getDataPointer() const override
    {
        return reinterpret_cast<const char* const>(&data_);
    }
};

class ColorRx : public RxReceiveBase
{
private:
    Color data_;

public:
    typedef Color data_type;
    Color getData() const
    {
        return data_;
    }
    ColorRx() : RxReceiveBase(Command::COLOR) {}
    ColorRx(const Color data) : RxReceiveBase(Command::COLOR), data_(data) {}
    ColorRx(const char* const buffer) : RxReceiveBase(Command::COLOR)
    {
        plot_tool::fillObjectsFromBuffer(buffer, data_);
    }

    size_t sizeOfData() const override
    {
        return sizeof(Color);
    }
    const char* getDataPointer() const override
    {
        return reinterpret_cast<const char* const>(&data_);
    }
};

class FigureNumRx : public RxReceiveBase
{
private:
    char data_;

public:
    typedef char data_type;
    char getData() const
    {
        return data_;
    }
    FigureNumRx() : RxReceiveBase(Command::FIGURE_NUM) {}
    FigureNumRx(const char data) : RxReceiveBase(Command::FIGURE_NUM), data_(data) {}
    FigureNumRx(const char* const buffer) : RxReceiveBase(Command::FIGURE_NUM)
    {
        plot_tool::fillObjectsFromBuffer(buffer, data_);
    }

    size_t sizeOfData() const override
    {
        return sizeof(char);
    }
    const char* getDataPointer() const override
    {
        return reinterpret_cast<const char* const>(&data_);
    }
};

class AlphaRx : public RxReceiveBase
{
private:
    Alpha data_;

public:
    typedef Alpha data_type;
    Alpha getData() const
    {
        return data_;
    }
    AlphaRx() : RxReceiveBase(Command::ALPHA) {}
    AlphaRx(const Alpha data) : RxReceiveBase(Command::ALPHA), data_(data) {}
    AlphaRx(const char* const buffer) : RxReceiveBase(Command::ALPHA)
    {
        plot_tool::fillObjectsFromBuffer(buffer, data_);
    }

    size_t sizeOfData() const override
    {
        return sizeof(Alpha);
    }
    const char* getDataPointer() const override
    {
        return reinterpret_cast<const char* const>(&data_);
    }
};

class LineStyleRx : public RxReceiveBase
{
private:
    LineStyle data_;

public:
    typedef LineStyle data_type;
    LineStyle getData() const
    {
        return data_;
    }
    LineStyleRx() : RxReceiveBase(Command::LINE_STYLE) {}
    LineStyleRx(const LineStyle data) : RxReceiveBase(Command::LINE_STYLE), data_(data) {}
    LineStyleRx(const char* const buffer) : RxReceiveBase(Command::LINE_STYLE)
    {
        plot_tool::fillObjectsFromBuffer(buffer, data_);
    }

    size_t sizeOfData() const override
    {
        return sizeof(LineStyle);
    }
    const char* getDataPointer() const override
    {
        return reinterpret_cast<const char* const>(&data_);
    }
};

class NameRx : public RxReceiveBase
{
private:
    Name data_;

public:
    typedef Name data_type;
    Name getData() const
    {
        return data_;
    }
    NameRx() : RxReceiveBase(Command::NAME) {}
    NameRx(const Name data) : RxReceiveBase(Command::NAME), data_(data) {}
    NameRx(const char* const buffer) : RxReceiveBase(Command::NAME)
    {
        plot_tool::fillObjectsFromBuffer(buffer, data_);
    }

    size_t sizeOfData() const override
    {
        return sizeof(Name);
    }
    const char* getDataPointer() const override
    {
        return reinterpret_cast<const char* const>(&data_);
    }
};

class ColorMapRx : public RxReceiveBase
{
private:
    ColorMap data_;

public:
    typedef ColorMap data_type;
    ColorMap getData() const
    {
        return data_;
    }
    ColorMapRx() : RxReceiveBase(Command::COLOR_MAP) {}
    ColorMapRx(const ColorMap data) : RxReceiveBase(Command::COLOR_MAP), data_(data) {}
    ColorMapRx(const char* const buffer) : RxReceiveBase(Command::COLOR_MAP)
    {
        plot_tool::fillObjectsFromBuffer(buffer, data_);
    }

    size_t sizeOfData() const override
    {
        return sizeof(ColorMap);
    }
    const char* getDataPointer() const override
    {
        return reinterpret_cast<const char* const>(&data_);
    }
};

class FunctionRx : public RxReceiveBase
{
private:
    Function data_;

public:
    typedef Function data_type;
    Function getData() const
    {
        return data_;
    }
    FunctionRx() : RxReceiveBase(Command::FUNCTION) {}
    FunctionRx(const Function data) : RxReceiveBase(Command::FUNCTION), data_(data) {}
    FunctionRx(const char* const buffer) : RxReceiveBase(Command::FUNCTION)
    {
        plot_tool::fillObjectsFromBuffer(buffer, data_);
    }

    size_t sizeOfData() const override
    {
        return sizeof(Function);
    }
    const char* getDataPointer() const override
    {
        return reinterpret_cast<const char* const>(&data_);
    }
};

class PersistentRx : public RxReceiveBase
{
private:
    Persistent data_;  // Dummy just to have something

public:
    typedef Persistent data_type;
    Persistent getData() const
    {
        return data_;
    }
    PersistentRx() : RxReceiveBase(Command::FUNCTION) {}
    PersistentRx(const Persistent data) : RxReceiveBase(Command::FUNCTION), data_(data) {}
    PersistentRx(const char* const buffer) : RxReceiveBase(Command::FUNCTION)
    {
        plot_tool::fillObjectsFromBuffer(buffer, data_);
    }

    size_t sizeOfData() const override
    {
        return 0;
    }

    const char* getDataPointer() const override
    {
        return reinterpret_cast<const char* const>(&data_);
    }
};

class PointSizeRx : public RxReceiveBase
{
private:
    PointSize data_;

public:
    typedef PointSize data_type;
    PointSize getData() const
    {
        return data_;
    }
    PointSizeRx() : RxReceiveBase(Command::POINT_SIZE) {}
    PointSizeRx(const PointSize data) : RxReceiveBase(Command::POINT_SIZE), data_(data) {}
    PointSizeRx(const char* const buffer) : RxReceiveBase(Command::POINT_SIZE)
    {
        plot_tool::fillObjectsFromBuffer(buffer, data_);
    }

    size_t sizeOfData() const override
    {
        return sizeof(PointSize);
    }
    const char* getDataPointer() const override
    {
        return reinterpret_cast<const char* const>(&data_);
    }
};

class PositionRx : public RxReceiveBase
{
private:
    Pos2D data_;

public:
    typedef Pos2D data_type;
    Pos2D getData() const
    {
        return data_;
    }
    PositionRx() : RxReceiveBase(Command::POS2D) {}
    PositionRx(const Pos2D data) : RxReceiveBase(Command::POS2D), data_(data) {}
    PositionRx(const char* const buffer) : RxReceiveBase(Command::POS2D)
    {
        plot_tool::fillObjectsFromBuffer(buffer, data_);
    }

    size_t sizeOfData() const override
    {
        return sizeof(Pos2D);
    }
    const char* getDataPointer() const override
    {
        return reinterpret_cast<const char* const>(&data_);
    }
};

}  // namespace plot_tool

#endif
