#ifndef DRAW_LINE_3D_H_
#define DRAW_LINE_3D_H_

#include <arl/math/math.h>

#include <string>
#include <vector>

#include "communication/rx_list.h"
#include "main_application/plot_objects/plot_object_base.h"
#include "opengl_low_level/data_structures.h"
#include "opengl_low_level/opengl_low_level.h"
#include "plot_functions/plot_functions.h"

using namespace plot_tool;

class DrawLine3D : public PlotObjectBase
{
private:
    void findMinMax();
    void setupInternalData();
    float line_width_;

    arl::Point3Dd p0;
    arl::Point3Dd p1;

public:
    DrawLine3D();
    DrawLine3D(const plot_tool::RxList& rx_list, const std::vector<char*> data_vec);

    void visualize() const override;
};

DrawLine3D::DrawLine3D(const plot_tool::RxList& rx_list, const std::vector<char*> data_vec)
    : PlotObjectBase(rx_list, data_vec)
{
    // num_elements is actual number of elements, not number of bytes
    ASSERT(rx_list.getObjectData<FunctionRx>() == Function::LINE3D);
    ASSERT(rx_list.getObjectData<NumBuffersRequiredRx>() == 1);

    line_width_ =
        rx_list.hasKey(Command::LINEWIDTH) ? rx_list.getObjectData<LinewidthRx>().data : 1.0f;

    setupInternalData();

    findMinMax();
}

void DrawLine3D::setupInternalData()
{
    arl::Line3Dd line;
    double t0;
    double t1;

    const char* const data_ptr = data_[0];

    fillObjectsFromBuffer(data_ptr, line, t0, t1);

    p0 = line.eval(t0);
    p1 = line.eval(t1);
}

void DrawLine3D::findMinMax()
{
    min_vec.x = std::min(p0.x, p1.x);
    min_vec.y = std::min(p0.y, p1.y);
    min_vec.z = std::min(p0.z, p1.z);

    max_vec.x = std::max(p0.x, p1.x);
    max_vec.y = std::max(p0.y, p1.y);
    max_vec.z = std::max(p0.z, p1.z);
}

void DrawLine3D::visualize() const
{
    setColor(color_);
    setLinewidth(line_width_);
    drawLine3D(p0, p1);
}

// DrawLine3D::~DrawLine3D() {}

#endif
