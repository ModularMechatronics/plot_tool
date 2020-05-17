#ifndef PLOT_TOOL_TRANSMISSION_H_
#define PLOT_TOOL_TRANSMISSION_H_

#include <climits>
#include <cstdint>
#include <cstdlib>
#include <utility>
#include <vector>

#include "shared/base_types.h"
#include "shared/plot_attributes.h"
#include "shared/util_functions.h"

namespace plot_tool
{
template <typename T> DataType typeToDataTypeEnum()
{
    if (std::is_same<T, float>::value)
    {
        return DataType::FLOAT;
    }
    else if (std::is_same<T, double>::value)
    {
        return DataType::DOUBLE;
    }
    else if (std::is_same<T, int>::value)
    {
        return DataType::INT;
    }
    else if (std::is_same<T, unsigned int>::value)
    {
        return DataType::UINT;
    }
    else if (std::is_same<T, char>::value)
    {
        return DataType::CHAR;
    }
    else if (std::is_same<T, unsigned char>::value)
    {
        return DataType::UCHAR;
    }
    else
    {
        return DataType::UNKNOWN;
    }
}

template <typename U> bool checkTypeValid(const Command& command)
{
    if (command == Command::NUM_BUFFERS_REQUIRED)
    {
        return std::is_same<U, char>::value;
    }
    else if (command == Command::NUM_BYTES)
    {
        return std::is_same<U, size_t>::value;
    }
    else if (command == Command::DATA_STRUCTURE)
    {
        return std::is_same<U, DataStructure>::value;
    }
    else if (command == Command::BYTES_PER_ELEMENT)
    {
        return std::is_same<U, char>::value;
    }
    else if (command == Command::DATA_TYPE)
    {
        return std::is_same<U, DataType>::value;
    }
    else if (command == Command::NUM_ELEMENTS)
    {
        return std::is_same<U, size_t>::value;
    }
    else if (command == Command::DIMENSION_2D)
    {
        return std::is_same<U, Dimension2D>::value;
    }
    else if (command == Command::HAS_PAYLOAD)
    {
        return std::is_same<U, bool>::value;
    }
    else if (command == Command::AZIMUTH)
    {
        return std::is_same<U, float>::value;
    }
    else if (command == Command::ELEVATION)
    {
        return std::is_same<U, float>::value;
    }
    else if (command == Command::AXES_DIMENSIONS)
    {
        return std::is_same<U, char>::value;
    }
    else if (command == Command::AXIS_MIN_MAX_VEC)
    {
        return std::is_same<U, std::pair<Bound3D, Bound3D>>::value;
    }
    else if (command == Command::LINEWIDTH)
    {
        return std::is_same<U, Linewidth>::value;
    }
    else if (command == Command::FACE_COLOR)
    {
        return std::is_same<U, FaceColor>::value;
    }
    else if (command == Command::EDGE_COLOR)
    {
        return std::is_same<U, EdgeColor>::value;
    }
    else if (command == Command::COLOR)
    {
        return std::is_same<U, Color>::value;
    }
    else if (command == Command::FIGURE_NUM)
    {
        return std::is_same<U, char>::value;
    }
    else if (command == Command::ALPHA)
    {
        return std::is_same<U, Alpha>::value;
    }
    else if (command == Command::LINE_STYLE)
    {
        return std::is_same<U, LineStyle>::value;
    }
    else if (command == Command::NAME)
    {
        return std::is_same<U, Name>::value;
    }
    else if (command == Command::COLOR_MAP)
    {
        return std::is_same<U, ColorMap>::value;
    }
    else if (command == Command::FUNCTION)
    {
        return std::is_same<U, Function>::value;
    }
    else if (command == Command::PERSISTENT)
    {
        return std::is_same<U, Persistent>::value;
    }
    else if (command == Command::POINT_SIZE)
    {
        return std::is_same<U, PointSize>::value;
    }
    else
    {
        return false;
    }
}

template <typename U> constexpr bool isCorrectType()
{
    return std::is_same<U, Linewidth>::value || std::is_same<U, Alpha>::value ||
           std::is_same<U, Name>::value || std::is_same<U, LineStyle>::value ||
           std::is_same<U, Color>::value || std::is_same<U, EdgeColor>::value ||
           std::is_same<U, FaceColor>::value || std::is_same<U, ColorMap>::value ||
           std::is_same<U, Persistent>::value || std::is_same<U, PointSize>::value;
}

class TxList
{
private:
    std::vector<TxPair> vec;

    void extendInternal(__attribute__((unused)) std::vector<TxPair>& vec)
    {
        //  To catch when there are no arguments to extend
    }

    template <typename U> void extendInternal(std::vector<TxPair>& vec, const U& obj)
    {
        static_assert(isCorrectType<U>(), "\n\nError: Input must have correct type!\n");

        vec.push_back(TxPair());
        TxPair* const ptr = &(vec[vec.size() - 1]);

        ptr->command = obj.getCommandType();
        ptr->num_bytes = sizeof(U);

        assert((ptr->num_bytes <= max_num_bytes) && "Too many data bytes!");

        plot_tool::fillBufferWithObjects(ptr->data, obj);
    }

    template <typename U, typename... Us>
    void extendInternal(std::vector<TxPair>& vec, const U& obj, const Us&... other_objs)
    {
        static_assert(isCorrectType<U>(), "\n\nError: Input must have correct type!\n");

        vec.push_back(TxPair());
        TxPair* const ptr = &(vec[vec.size() - 1]);

        ptr->command = obj.getCommandType();
        ptr->num_bytes = sizeof(U);

        assert((ptr->num_bytes <= max_num_bytes) && "Too many data bytes!");

        plot_tool::fillBufferWithObjects(ptr->data, obj);

        extendInternal(vec, other_objs...);
    }

public:
    TxList()
    {
        vec.reserve(16);
    }

    std::vector<TxPair> getVector() const
    {
        return vec;
    }

    template <typename U> void append(const Command& command, const U& data)
    {
        assert(checkTypeValid<U>(command) && "Invalid data type for command data!");

        vec.push_back(TxPair());
        TxPair* const ptr = &(vec[vec.size() - 1]);

        ptr->command = command;
        ptr->num_bytes = sizeof(U);

        assert((ptr->num_bytes <= max_num_bytes) && "Too many data bytes!");

        plot_tool::fillBufferWithObjects(ptr->data, data);
    }

    template <typename... Us> void extend(const Us&... objects)
    {
        extendInternal(vec, objects...);
    }

    size_t totalNumBytesFromBuffer() const
    {
        // 1 for first byte, that indicates how many attributes in buffer, which is
        // same as vec.size()
        size_t s = 1;

        for (size_t k = 0; k < vec.size(); k++)
        {
            s = s + sizeof(Command) + vec[k].num_bytes;
        }

        return s;
    }

    void fillBufferWithData(char* const buffer) const
    {
        assert(vec.size() < max_num_bytes);
        buffer[0] = static_cast<char>(vec.size());
        size_t idx = 1;

        for (size_t k = 0; k < vec.size(); k++)
        {
            const char* const command_type_ptr =
                reinterpret_cast<const char* const>(&(vec[k].command));

            buffer[idx] = command_type_ptr[0];
            buffer[idx + 1] = command_type_ptr[1];
            idx = idx + 2;
            for (size_t i = 0; i < static_cast<size_t>(vec[k].num_bytes); i++)
            {
                buffer[idx] = vec[k].data[i];
                idx++;
            }
        }
    }
};

}  // namespace plot_tool

#endif
