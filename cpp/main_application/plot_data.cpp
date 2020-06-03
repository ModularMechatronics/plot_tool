#include "main_application/plot_data.h"

#include <arl/math/math.h>
#include <arl/utilities/logging.h>

#include "communication/rx_list.h"
#include "communication/shared/util_functions.h"
#include "main_application/plot_objects/plot_objects.h"
#include "opengl_low_level/data_structures.h"
#include "opengl_low_level/opengl_low_level.h"
#include "plot_functions/plot_functions.h"

using namespace plot_tool;
using namespace arl;

PlotDataHandler::PlotDataHandler() {}

void PlotDataHandler::clear()
{
    for (size_t k = 0; k < plot_datas_.size(); k++)
    {
        delete plot_datas_[k];
    }
    plot_datas_.clear();
}

void PlotDataHandler::addData(const plot_tool::RxList& rx_list, const std::vector<char*> data_vec)
{
    const plot_tool::Function fcn_type = rx_list.getObjectData<FunctionRx>();
    switch (fcn_type)
    {
        case plot_tool::Function::PLOT2:
            plot_datas_.push_back(dynamic_cast<PlotObjectBase*>(new Plot2D(rx_list, data_vec)));

            break;
        case plot_tool::Function::PLOT3:
            plot_datas_.push_back(dynamic_cast<PlotObjectBase*>(new Plot3D(rx_list, data_vec)));

            break;
        case plot_tool::Function::SURF:
            plot_datas_.push_back(dynamic_cast<PlotObjectBase*>(new Surf(rx_list, data_vec)));

            break;
        case plot_tool::Function::LINE3D:
            plot_datas_.push_back(dynamic_cast<PlotObjectBase*>(new DrawLine3D(rx_list, data_vec)));

            break;
        case plot_tool::Function::LINE_BETWEEN_POINTS_3D:
            plot_datas_.push_back(
                dynamic_cast<PlotObjectBase*>(new DrawLineBetweenPoints3D(rx_list, data_vec)));

            break;
        case plot_tool::Function::PLANE_XY:
            plot_datas_.push_back(
                dynamic_cast<PlotObjectBase*>(new DrawPlaneXY(rx_list, data_vec)));

            break;
        case plot_tool::Function::PLANE_XZ:
            plot_datas_.push_back(
                dynamic_cast<PlotObjectBase*>(new DrawPlaneXZ(rx_list, data_vec)));

            break;
        case plot_tool::Function::PLANE_YZ:
            plot_datas_.push_back(
                dynamic_cast<PlotObjectBase*>(new DrawPlaneYZ(rx_list, data_vec)));

            break;
        case plot_tool::Function::POLYGON_FROM_4_POINTS:
            plot_datas_.push_back(
                dynamic_cast<PlotObjectBase*>(new DrawPolygon4Points(rx_list, data_vec)));

            break;
        case plot_tool::Function::SCATTER3:
            plot_datas_.push_back(dynamic_cast<PlotObjectBase*>(new Scatter3D(rx_list, data_vec)));

            break;
        case plot_tool::Function::SCATTER2:
            plot_datas_.push_back(dynamic_cast<PlotObjectBase*>(new Scatter2D(rx_list, data_vec)));

            break;
        default:
            EXIT() << "Unsupported function!";
            break;
    }
}

void PlotDataHandler::visualize() const
{
    for (size_t k = 0; k < plot_datas_.size(); k++)
    {
        plot_datas_[k]->visualize();
    }
}

std::pair<Vec3Dd, Vec3Dd> PlotDataHandler::getMinMaxVectors() const
{
    if (plot_datas_.size() == 0)
    {
        return std::pair<Vec3Dd, Vec3Dd>(Vec3Dd(-1, -1, -1), Vec3Dd(1, 1, 1));
    }
    else
    {
        const std::pair<Vec3Dd, Vec3Dd> min_max = plot_datas_[0]->getMinMaxVectors();
        size_t num_dimensions = plot_datas_[0]->getNumDimensions();
        Vec3Dd min_vec = min_max.first;
        Vec3Dd max_vec = min_max.second;

        bool z_is_set = num_dimensions == 3 ? true : false;

        for (size_t k = 1; k < plot_datas_.size(); k++)
        {
            const std::pair<Vec3Dd, Vec3Dd> current_min_max = plot_datas_[0]->getMinMaxVectors();

            size_t current_num_dimensions = plot_datas_[k]->getNumDimensions();
            num_dimensions = std::max(num_dimensions, current_num_dimensions);

            if (current_num_dimensions == 3)
            {
                if (!z_is_set)
                {
                    min_vec.z = current_min_max.first.z;
                    max_vec.z = current_min_max.second.z;
                    z_is_set = true;
                }
                else
                {
                    min_vec.z = std::min(min_vec.z, current_min_max.first.z);
                }
            }

            min_vec.x = std::min(min_vec.x, current_min_max.first.x);
            min_vec.y = std::min(min_vec.y, current_min_max.first.y);
        }

        if (num_dimensions == 2)
        {
            min_vec.z = -1.0;
            max_vec.z = 1.0;
        }

        const arl::Vec3Dd diff_vec = max_vec - min_vec;

        const arl::Vectord v = {diff_vec.x, diff_vec.y, diff_vec.z};

        const double largest_diff = arl::max(v);

        // If some of the axes turns out to have a very small difference
        // between min and max, we have to modify this
        if (diff_vec.x < largest_diff * 0.01)
        {
            min_vec.x = -largest_diff * 0.01;
            max_vec.x = largest_diff * 0.01;
        }
        if (diff_vec.y < largest_diff * 0.01)
        {
            min_vec.y = -largest_diff * 0.01;
            max_vec.y = largest_diff * 0.01;
        }
        if (diff_vec.z < largest_diff * 0.01)
        {
            min_vec.z = -largest_diff * 0.01;
            max_vec.z = largest_diff * 0.01;
        }

        return std::pair<Vec3Dd, Vec3Dd>(min_vec, max_vec);
    }
}

void PlotDataHandler::softClear()
{
    std::vector<PlotObjectBase*> new_plot_datas;
    for (size_t k = 0; k < plot_datas_.size(); k++)
    {
        if (plot_datas_[k]->isPersistent())
        {
            new_plot_datas.push_back(plot_datas_[k]);
        }
        else
        {
            delete plot_datas_[k];
        }
    }
    plot_datas_ = new_plot_datas;
}
