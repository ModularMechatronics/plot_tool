#ifndef INDEX_SPAN_H_
#define INDEX_SPAN_H_

#include <stdio.h>

namespace plot_tool
{
struct IndexSpan
{
    const size_t from;
    const size_t to;

    IndexSpan() = delete;
    IndexSpan(const size_t from_, const size_t to_) : from(from_), to(to_) {}
};
}  // namespace plot_tool

#endif
