#ifndef SCATTER_3D_H_
#define SCATTER_3D_H_

#include <arl/math/math.h>

#include <string>
#include <vector>

#include "communication/rx_list.h"
#include "main_application/plot_objects/plot_object_base.h"
#include "opengl_low_level/data_structures.h"
#include "opengl_low_level/opengl_low_level.h"
#include "plot_functions/plot_functions.h"

using namespace plot_tool;

class Scatter3D : public PlotObjectBase
{
private:
    size_t num_elements_;
    float point_size_;

    arl::Vectord x_vec, y_vec, z_vec;

    void findMinMax();

public:
    Scatter3D();
    Scatter3D(const plot_tool::RxList& rx_list, const std::vector<char*> data_vec);
    ~Scatter3D();

    void visualize() const override;
};

Scatter3D::Scatter3D(const plot_tool::RxList& rx_list, const std::vector<char*> data_vec)
    : PlotObjectBase(rx_list, data_vec)
{
    // num_elements is actual number of elements, not number of bytes
    ASSERT(rx_list.getObjectData<FunctionRx>() == Function::SCATTER3);
    ASSERT(rx_list.getObjectData<NumBuffersRequiredRx>() == 3);
    ASSERT(rx_list.getObjectData<DataStructureRx>() == DataStructure::VECTOR);

    num_elements_ = rx_list.getObjectData<NumElementsRx>();
    point_size_ =
        rx_list.hasKey(Command::POINT_SIZE) ? rx_list.getObjectData<PointSizeRx>().data : 1.0f;

    x_vec.setInternalData(reinterpret_cast<double*>(data_[0]), num_elements_);
    y_vec.setInternalData(reinterpret_cast<double*>(data_[1]), num_elements_);
    z_vec.setInternalData(reinterpret_cast<double*>(data_[2]), num_elements_);

    findMinMax();
}

void Scatter3D::findMinMax()
{
    ASSERT(x_vec.isAllocated()) << "Vector x not allocated when checking min/max!";
    ASSERT(y_vec.isAllocated()) << "Vector y not allocated when checking min/max!";
    ASSERT(z_vec.isAllocated()) << "Vector z not allocated when checking min/max!";

    min_vec.x = arl::min(x_vec);
    min_vec.y = arl::min(y_vec);
    min_vec.z = arl::min(z_vec);

    max_vec.x = arl::max(x_vec);
    max_vec.y = arl::max(y_vec);
    max_vec.z = arl::max(z_vec);
}

void Scatter3D::visualize() const
{
    setColor(color_);
    setPointSize(point_size_);
    scatter3(x_vec, y_vec, z_vec);
}

Scatter3D::~Scatter3D()
{
    x_vec.setInternalData(nullptr, 0);  // Hack
    y_vec.setInternalData(nullptr, 0);
    z_vec.setInternalData(nullptr, 0);
}

#endif
