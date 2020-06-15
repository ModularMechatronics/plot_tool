#ifndef PLOT_TOOL_MATH_MACROS_H_
#define PLOT_TOOL_MATH_MACROS_H_

#include "logging.h"

namespace plot_tool
{
#define DATA_ALLOCATION(data, data_size, data_type, alloc_type)                                   \
    try                                                                                           \
    {                                                                                             \
        data = new data_type[data_size];                                                          \
    }                                                                                             \
    catch (std::bad_alloc & ba)                                                                   \
    {                                                                                             \
        std::cerr << alloc_type << " allocation failed, bad_alloc caught: " << ba.what() << '\n'; \
        exit(-1);                                                                                 \
    }

#define ASSERT_MAT_VALID(mat)                                \
    PT_ASSERT(mat.isAllocated()) << "Matrix not allocated!"; \
    PT_ASSERT(mat.rows() > 0) << "Number of rows is 0!";     \
    PT_ASSERT(mat.cols() > 0) << "Number of cols is 0!"

#define ASSERT_VEC_VALID(vec)                                \
    PT_ASSERT(vec.isAllocated()) << "Matrix not allocated!"; \
    PT_ASSERT(vec.rows() > 0) << "Vector size is 0!";

#define ASSERT_MAT_VALID_INTERNAL()                      \
    PT_ASSERT(is_allocated_) << "Matrix not allocated!"; \
    PT_ASSERT(num_rows_ > 0) << "Number of rows is 0!";  \
    PT_ASSERT(num_cols_ > 0) << "Number of cols is 0!"

#define ASSERT_VEC_VALID_INTERNAL()                      \
    PT_ASSERT(is_allocated_) << "Vector not allocated!"; \
    PT_ASSERT(vector_length_ > 0) << "Number of elements is 0!"

}  // namespace plot_tool

#endif
