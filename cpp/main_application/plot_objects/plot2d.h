#ifndef PLOT2D_H_
#define PLOT2D_H_

#include <arl/math/math.h>

#include <string>
#include <vector>

#include "communication/rx_list.h"
#include "main_application/plot_objects/plot_object_base.h"
#include "opengl_low_level/data_structures.h"
#include "opengl_low_level/opengl_low_level.h"
#include "plot_functions/plot_functions.h"

using namespace plot_tool;

class Plot2D : public PlotObjectBase
{
private:
    size_t num_elements_;
    float line_width_;

    arl::Vectord x_vec, y_vec;

    void findMinMax();

public:
    Plot2D();
    Plot2D(const plot_tool::RxList& rx_list, const std::vector<char*> data_vec);
    ~Plot2D();

    void visualize() const override;
};

Plot2D::Plot2D(const plot_tool::RxList& rx_list, const std::vector<char*> data_vec)
    : PlotObjectBase(rx_list, data_vec)
{
    // num_elements is actual number of elements, not number of bytes
    ASSERT(rx_list.getObjectData<FunctionRx>() == Function::PLOT2);
    ASSERT(rx_list.getObjectData<NumBuffersRequiredRx>() == 2);
    ASSERT(rx_list.getObjectData<DataStructureRx>() == DataStructure::VECTOR);

    num_elements_ = rx_list.getObjectData<NumElementsRx>();

    x_vec.setInternalData(reinterpret_cast<double*>(data_[0]), num_elements_);
    y_vec.setInternalData(reinterpret_cast<double*>(data_[1]), num_elements_);

    line_width_ =
        rx_list.hasKey(Command::LINEWIDTH) ? rx_list.getObjectData<LinewidthRx>().data : 1.0f;

    findMinMax();
}

void Plot2D::findMinMax()
{
    ASSERT(x_vec.isAllocated()) << "Vector not allocated when checking min/max!";
    ASSERT(y_vec.isAllocated()) << "Vector not allocated when checking min/max!";

    min_vec.x = arl::min(x_vec);
    min_vec.y = arl::min(y_vec);

    max_vec.x = arl::max(x_vec);
    max_vec.y = arl::max(y_vec);
}

void Plot2D::visualize() const
{
    setColor(color_);
    setLinewidth(line_width_);
    plot(x_vec, y_vec);
}

Plot2D::~Plot2D()
{
    x_vec.setInternalData(nullptr, 0);  // Hack
    y_vec.setInternalData(nullptr, 0);
}

#endif
