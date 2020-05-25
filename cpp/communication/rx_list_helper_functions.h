#ifndef RX_LIST_HELPER_FUNCTIONS_H_
#define RX_LIST_HELPER_FUNCTIONS_H_

#include "communication/rx_classes.h"

namespace plot_tool
{
inline RxReceiveBase* getPointerFromCommandType(const Command cmd, RxReceiveBase* const base_ptr)
{
    RxReceiveBase* ptr;

    if (Command::NUM_BUFFERS_REQUIRED == cmd)
    {
        NumBuffersRequiredRx* other_ptr = dynamic_cast<NumBuffersRequiredRx*>(base_ptr);
        ptr = new NumBuffersRequiredRx(other_ptr->getData());
    }
    else if (Command::NUM_BYTES == cmd)
    {
        NumBytesRx* other_ptr = dynamic_cast<NumBytesRx*>(base_ptr);
        ptr = new NumBytesRx(other_ptr->getData());
    }
    else if (Command::DATA_STRUCTURE == cmd)
    {
        DataStructureRx* other_ptr = dynamic_cast<DataStructureRx*>(base_ptr);
        ptr = new DataStructureRx(other_ptr->getData());
    }
    else if (Command::BYTES_PER_ELEMENT == cmd)
    {
        BytesPerElementRx* other_ptr = dynamic_cast<BytesPerElementRx*>(base_ptr);
        ptr = new BytesPerElementRx(other_ptr->getData());
    }
    else if (Command::DATA_TYPE == cmd)
    {
        DataTypeRx* other_ptr = dynamic_cast<DataTypeRx*>(base_ptr);
        ptr = new DataTypeRx(other_ptr->getData());
    }
    else if (Command::NUM_ELEMENTS == cmd)
    {
        NumElementsRx* other_ptr = dynamic_cast<NumElementsRx*>(base_ptr);
        ptr = new NumElementsRx(other_ptr->getData());
    }
    else if (Command::DIMENSION_2D == cmd)
    {
        Dimension2dRx* other_ptr = dynamic_cast<Dimension2dRx*>(base_ptr);
        ptr = new Dimension2dRx(other_ptr->getData());
    }
    else if (Command::HAS_PAYLOAD == cmd)
    {
        HasPayloadRx* other_ptr = dynamic_cast<HasPayloadRx*>(base_ptr);
        ptr = new HasPayloadRx(other_ptr->getData());
    }
    else if (Command::AZIMUTH == cmd)
    {
        AzimuthRx* other_ptr = dynamic_cast<AzimuthRx*>(base_ptr);
        ptr = new AzimuthRx(other_ptr->getData());
    }
    else if (Command::ELEVATION == cmd)
    {
        ElevationRx* other_ptr = dynamic_cast<ElevationRx*>(base_ptr);
        ptr = new ElevationRx(other_ptr->getData());
    }
    else if (Command::AXES_DIMENSIONS == cmd)
    {
        AxesDimensionsRx* other_ptr = dynamic_cast<AxesDimensionsRx*>(base_ptr);
        ptr = new AxesDimensionsRx(other_ptr->getData());
    }
    else if (Command::AXIS_MIN_MAX_VEC == cmd)
    {
        AxesMinMaxVecRx* other_ptr = dynamic_cast<AxesMinMaxVecRx*>(base_ptr);
        ptr = new AxesMinMaxVecRx(other_ptr->getData());
    }
    else if (Command::LINEWIDTH == cmd)
    {
        LinewidthRx* other_ptr = dynamic_cast<LinewidthRx*>(base_ptr);
        ptr = new LinewidthRx(other_ptr->getData());
    }
    else if (Command::FACE_COLOR == cmd)
    {
        FaceColorRx* other_ptr = dynamic_cast<FaceColorRx*>(base_ptr);
        ptr = new FaceColorRx(other_ptr->getData());
    }
    else if (Command::EDGE_COLOR == cmd)
    {
        EdgeColorRx* other_ptr = dynamic_cast<EdgeColorRx*>(base_ptr);
        ptr = new EdgeColorRx(other_ptr->getData());
    }
    else if (Command::COLOR == cmd)
    {
        ColorRx* other_ptr = dynamic_cast<ColorRx*>(base_ptr);
        ptr = new ColorRx(other_ptr->getData());
    }
    else if (Command::FIGURE_NUM == cmd)
    {
        FigureNumRx* other_ptr = dynamic_cast<FigureNumRx*>(base_ptr);
        ptr = new FigureNumRx(other_ptr->getData());
    }
    else if (Command::ALPHA == cmd)
    {
        AlphaRx* other_ptr = dynamic_cast<AlphaRx*>(base_ptr);
        ptr = new AlphaRx(other_ptr->getData());
    }
    else if (Command::LINE_STYLE == cmd)
    {
        LineStyleRx* other_ptr = dynamic_cast<LineStyleRx*>(base_ptr);
        ptr = new LineStyleRx(other_ptr->getData());
    }
    else if (Command::NAME == cmd)
    {
        NameRx* other_ptr = dynamic_cast<NameRx*>(base_ptr);
        ptr = new NameRx(other_ptr->getData());
    }
    else if (Command::COLOR_MAP == cmd)
    {
        ColorMapRx* other_ptr = dynamic_cast<ColorMapRx*>(base_ptr);
        ptr = new ColorMapRx(other_ptr->getData());
    }
    else if (Command::FUNCTION == cmd)
    {
        FunctionRx* other_ptr = dynamic_cast<FunctionRx*>(base_ptr);
        ptr = new FunctionRx(other_ptr->getData());
    }
    else if (Command::PERSISTENT == cmd)
    {
        PersistentRx* other_ptr = dynamic_cast<PersistentRx*>(base_ptr);
        ptr = new PersistentRx(other_ptr->getData());
    }
    else if (Command::POINT_SIZE == cmd)
    {
        PointSizeRx* other_ptr = dynamic_cast<PointSizeRx*>(base_ptr);
        ptr = new PointSizeRx(other_ptr->getData());
    }
    else if (Command::POS2D == cmd)
    {
        PositionRx* other_ptr = dynamic_cast<PositionRx*>(base_ptr);
        ptr = new PositionRx(other_ptr->getData());
    }
    else
    {
        EXIT() << "Pointer type not found!";
    }

    return dynamic_cast<RxReceiveBase*>(ptr);
}

inline std::pair<RxReceiveBase*, size_t> getPointerFromCommandType(const Command cmd,
                                                                   const char* const buffer)
{
    RxReceiveBase* ptr;

    if (Command::NUM_BUFFERS_REQUIRED == cmd)
    {
        ptr = new NumBuffersRequiredRx(buffer);
    }
    else if (Command::NUM_BYTES == cmd)
    {
        ptr = new NumBytesRx(buffer);
    }
    else if (Command::DATA_STRUCTURE == cmd)
    {
        ptr = new DataStructureRx(buffer);
    }
    else if (Command::BYTES_PER_ELEMENT == cmd)
    {
        ptr = new BytesPerElementRx(buffer);
    }
    else if (Command::DATA_TYPE == cmd)
    {
        ptr = new DataTypeRx(buffer);
    }
    else if (Command::NUM_ELEMENTS == cmd)
    {
        ptr = new NumElementsRx(buffer);
    }
    else if (Command::DIMENSION_2D == cmd)
    {
        ptr = new Dimension2dRx(buffer);
    }
    else if (Command::HAS_PAYLOAD == cmd)
    {
        ptr = new HasPayloadRx(buffer);
    }
    else if (Command::AZIMUTH == cmd)
    {
        ptr = new AzimuthRx(buffer);
    }
    else if (Command::ELEVATION == cmd)
    {
        ptr = new ElevationRx(buffer);
    }
    else if (Command::AXES_DIMENSIONS == cmd)
    {
        ptr = new AxesDimensionsRx(buffer);
    }
    else if (Command::AXIS_MIN_MAX_VEC == cmd)
    {
        ptr = new AxesMinMaxVecRx(buffer);
    }
    else if (Command::LINEWIDTH == cmd)
    {
        ptr = new LinewidthRx(buffer);
    }
    else if (Command::FACE_COLOR == cmd)
    {
        ptr = new FaceColorRx(buffer);
    }
    else if (Command::EDGE_COLOR == cmd)
    {
        ptr = new EdgeColorRx(buffer);
    }
    else if (Command::COLOR == cmd)
    {
        ptr = new ColorRx(buffer);
    }
    else if (Command::FIGURE_NUM == cmd)
    {
        ptr = new FigureNumRx(buffer);
    }
    else if (Command::ALPHA == cmd)
    {
        ptr = new AlphaRx(buffer);
    }
    else if (Command::LINE_STYLE == cmd)
    {
        ptr = new LineStyleRx(buffer);
    }
    else if (Command::NAME == cmd)
    {
        ptr = new NameRx(buffer);
    }
    else if (Command::COLOR_MAP == cmd)
    {
        ptr = new ColorMapRx(buffer);
    }
    else if (Command::FUNCTION == cmd)
    {
        ptr = new FunctionRx(buffer);
    }
    else if (Command::PERSISTENT == cmd)
    {
        ptr = new PersistentRx(buffer);
    }
    else if (Command::POINT_SIZE == cmd)
    {
        ptr = new PointSizeRx(buffer);
    }
    else if (Command::POS2D == cmd)
    {
        ptr = new PositionRx(buffer);
    }
    else
    {
        EXIT() << "Pointer type not found!";
    }

    return std::pair<RxReceiveBase*, size_t>(ptr, ptr->sizeOfData());
}

template <typename T> Command getCommandTypeFromClass()
{
    Command cmd;
    if (std::is_same<T, NumBuffersRequiredRx>::value)
    {
        cmd = Command::NUM_BUFFERS_REQUIRED;
    }
    else if (std::is_same<T, NumBytesRx>::value)
    {
        cmd = Command::NUM_BYTES;
    }
    else if (std::is_same<T, DataStructureRx>::value)
    {
        cmd = Command::DATA_STRUCTURE;
    }
    else if (std::is_same<T, BytesPerElementRx>::value)
    {
        cmd = Command::BYTES_PER_ELEMENT;
    }
    else if (std::is_same<T, DataTypeRx>::value)
    {
        cmd = Command::DATA_TYPE;
    }
    else if (std::is_same<T, NumElementsRx>::value)
    {
        cmd = Command::NUM_ELEMENTS;
    }
    else if (std::is_same<T, Dimension2dRx>::value)
    {
        cmd = Command::DIMENSION_2D;
    }
    else if (std::is_same<T, HasPayloadRx>::value)
    {
        cmd = Command::HAS_PAYLOAD;
    }
    else if (std::is_same<T, AzimuthRx>::value)
    {
        cmd = Command::AZIMUTH;
    }
    else if (std::is_same<T, ElevationRx>::value)
    {
        cmd = Command::ELEVATION;
    }
    else if (std::is_same<T, AxesDimensionsRx>::value)
    {
        cmd = Command::AXES_DIMENSIONS;
    }
    else if (std::is_same<T, AxesMinMaxVecRx>::value)
    {
        cmd = Command::AXIS_MIN_MAX_VEC;
    }
    else if (std::is_same<T, LinewidthRx>::value)
    {
        cmd = Command::LINEWIDTH;
    }
    else if (std::is_same<T, FaceColorRx>::value)
    {
        cmd = Command::FACE_COLOR;
    }
    else if (std::is_same<T, EdgeColorRx>::value)
    {
        cmd = Command::EDGE_COLOR;
    }
    else if (std::is_same<T, ColorRx>::value)
    {
        cmd = Command::COLOR;
    }
    else if (std::is_same<T, FigureNumRx>::value)
    {
        cmd = Command::FIGURE_NUM;
    }
    else if (std::is_same<T, AlphaRx>::value)
    {
        cmd = Command::ALPHA;
    }
    else if (std::is_same<T, LineStyleRx>::value)
    {
        cmd = Command::LINE_STYLE;
    }
    else if (std::is_same<T, NameRx>::value)
    {
        cmd = Command::NAME;
    }
    else if (std::is_same<T, ColorMapRx>::value)
    {
        cmd = Command::COLOR_MAP;
    }
    else if (std::is_same<T, FunctionRx>::value)
    {
        cmd = Command::FUNCTION;
    }
    else if (std::is_same<T, PersistentRx>::value)
    {
        cmd = Command::PERSISTENT;
    }
    else if (std::is_same<T, PointSizeRx>::value)
    {
        cmd = Command::POINT_SIZE;
    }
    else if (std::is_same<T, PositionRx>::value)
    {
        cmd = Command::POS2D;
    }
    else
    {
        EXIT() << "Command type not found!";
    }

    return cmd;
}

}  // namespace plot_tool

#endif
