#ifndef END_INDEX_H_
#define END_INDEX_H_

#include <cassert>

namespace plot_tool
{
struct EndIndex
{
    const int offset;

    EndIndex() : offset(0) {}
    EndIndex(const int offset_) : offset(offset_)
    {
        assert(offset_ <= 0 && "Offset must be either 0 or negative!");
    }
};

}  // namespace plot_tool

#endif
