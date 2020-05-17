#ifndef DRAW_POLYGON_4_POINTS_H_
#define DRAW_POLYGON_4_POINTS_H_

#include <arl/math/math.h>

#include <string>
#include <vector>

#include "communication/rx_list.h"
#include "main_application/plot_objects/plot_object_base.h"
#include "opengl_low_level/data_structures.h"
#include "opengl_low_level/opengl_low_level.h"
#include "plot_functions/plot_functions.h"

using namespace plot_tool;

class DrawPolygon4Points : public PlotObjectBase
{
private:
    void findMinMax();
    void setupInternalData();
    RGBTripletf edge_color_;
    RGBTripletf face_color_;
    float line_width_;

    arl::Point3Dd p0;
    arl::Point3Dd p1;
    arl::Point3Dd p2;
    arl::Point3Dd p3;

public:
    DrawPolygon4Points();
    DrawPolygon4Points(const plot_tool::RxList& rx_list, const std::vector<char*> data_vec);

    void visualize() const override;
};

DrawPolygon4Points::DrawPolygon4Points(const plot_tool::RxList& rx_list,
                                       const std::vector<char*> data_vec)
    : PlotObjectBase(rx_list, data_vec)
{
    // num_elements is actual number of elements, not number of bytes
    ASSERT(rx_list.getObjectData<FunctionRx>() == Function::POLYGON_FROM_4_POINTS);
    ASSERT(rx_list.getObjectData<NumBuffersRequiredRx>() == 1);

    line_width_ =
        rx_list.hasKey(Command::LINEWIDTH) ? rx_list.getObjectData<LinewidthRx>().data : 1.0f;

    face_color_ = RGBTripletf(0.1, 0.2, 0.1);
    edge_color_ = RGBTripletf(0.0, 0.0, 0.0);

    if (rx_list.hasKey(Command::FACE_COLOR))
    {
        FaceColor c = rx_list.getObjectData<FaceColorRx>();
        face_color_.red = c.red;
        face_color_.green = c.green;
        face_color_.blue = c.blue;
    }
    if (rx_list.hasKey(Command::EDGE_COLOR))
    {
        EdgeColor c = rx_list.getObjectData<EdgeColorRx>();
        edge_color_.red = c.red;
        edge_color_.green = c.green;
        edge_color_.blue = c.blue;
    }

    setupInternalData();

    findMinMax();
}

void DrawPolygon4Points::setupInternalData()
{
    const char* const data_ptr = data_[0];

    fillObjectsFromBuffer(data_ptr, p0, p1, p2, p3);
}

void DrawPolygon4Points::findMinMax()
{
    const arl::Vectord vx = {p0.x, p1.x, p2.x, p3.x};
    const arl::Vectord vy = {p0.y, p1.y, p2.y, p3.y};
    const arl::Vectord vz = {p0.z, p1.z, p2.z, p3.z};

    min_vec.x = arl::min(vx);
    min_vec.y = arl::min(vy);
    min_vec.z = arl::min(vz);

    max_vec.x = arl::max(vx);
    max_vec.y = arl::max(vy);
    max_vec.z = arl::max(vz);
}

void DrawPolygon4Points::visualize() const
{
    setColor(face_color_);
    drawPolygon3D(p0, p1, p2, p3);

    setLinewidth(line_width_);
    setColor(edge_color_);
    drawLine3D(p0, p1);
    drawLine3D(p1, p2);
    drawLine3D(p2, p3);
    drawLine3D(p3, p0);
}

// DrawPolygon4Points::~DrawPolygon4Points() {}

#endif
