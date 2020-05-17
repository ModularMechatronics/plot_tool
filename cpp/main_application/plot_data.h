#ifndef PLOT_DATA_H_
#define PLOT_DATA_H_

#include <arl/math/math.h>

#include <string>
#include <vector>

#include "communication/rx_list.h"
#include "opengl_low_level/data_structures.h"

class PlotObjectBase;

class PlotDataHandler
{
private:
public:
    std::pair<arl::Vec3Dd, arl::Vec3Dd> getMinMaxVectors() const;
    std::vector<PlotObjectBase*> plot_datas_;
    PlotDataHandler();
    void clear();
    void softClear();
    void addData(const plot_tool::RxList& rx_list, const std::vector<char*> data_vec);
    void visualize() const;
};

#endif
