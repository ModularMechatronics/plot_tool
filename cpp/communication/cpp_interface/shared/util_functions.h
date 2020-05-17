#ifndef UTIL_FUNCTIONS_H_
#define UTIL_FUNCTIONS_H_

#include <cstdlib>

namespace plot_tool
{
template <typename U> constexpr size_t totalSizeOfObjects(__attribute__((unused)) const U& obj)
{
    return sizeof(U);
}

template <typename U, typename... Us>
constexpr size_t totalSizeOfObjects(__attribute__((unused)) const U& obj, const Us&... objects)
{
    return sizeof(U) + totalSizeOfObjects(objects...);
}

template <typename U>
void fillBufferWithObjectsInternal(size_t idx, char* const buffer, const U& obj)
{
    const char* const obj_ptr = reinterpret_cast<const char* const>(&obj);

    for (size_t k = 0; k < sizeof(U); k++)
    {
        buffer[idx] = obj_ptr[k];
        idx++;
    }
}

template <typename U, typename... Us>
void fillBufferWithObjectsInternal(size_t idx,
                                   char* const buffer,
                                   const U& obj,
                                   const Us&... objects)
{
    const char* const obj_ptr = reinterpret_cast<const char* const>(&obj);

    for (size_t k = 0; k < sizeof(U); k++)
    {
        buffer[idx] = obj_ptr[k];
        idx++;
    }
    fillBufferWithObjectsInternal(idx, buffer, objects...);
}

template <typename... Us> void fillBufferWithObjects(char* const buffer, const Us&... objects)
{
    size_t idx = 0;
    fillBufferWithObjectsInternal(idx, buffer, objects...);
}

template <typename U>
void fillObjectsFromBufferInternal(size_t idx, const char* const buffer, U& obj)
{
    char* const obj_ptr = reinterpret_cast<char* const>(&obj);

    for (size_t k = 0; k < sizeof(U); k++)
    {
        obj_ptr[k] = buffer[idx];
        idx++;
    }
}

template <typename U, typename... Us>
void fillObjectsFromBufferInternal(size_t idx, const char* const buffer, U& obj, Us&... objects)
{
    char* const obj_ptr = reinterpret_cast<char* const>(&obj);

    for (size_t k = 0; k < sizeof(U); k++)
    {
        obj_ptr[k] = buffer[idx];
        idx++;
    }
    fillObjectsFromBufferInternal(idx, buffer, objects...);
}

template <typename... Us> void fillObjectsFromBuffer(const char* const buffer, Us&... objects)
{
    size_t idx = 0;
    fillObjectsFromBufferInternal(idx, buffer, objects...);
}

}  // namespace plot_tool

#endif
