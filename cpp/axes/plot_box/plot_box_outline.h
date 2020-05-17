#ifndef PLOT_BOX_OUTLINE_H_
#define PLOT_BOX_OUTLINE_H_

#include "axes/structures/axes_settings.h"
#include "axes/structures/view_angles.h"

void drawDottedBox(const AxesSettings& axes_settings);
void drawOutline(const AxesSettings& axes_settings, const ViewAngles& view_angles);

#endif
