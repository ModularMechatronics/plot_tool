#include "main_application/plot_window_gl_pane.h"

#include <arl/math/math.h>
#include <arl/utilities/logging.h>
#include <wx/event.h>

#include "axes/axes.h"
#include "io_devices/io_devices.h"
#include "main_application/plot_data.h"
#include "opengl_low_level/opengl_low_level.h"
#include "plot_functions/plot_functions.h"

using namespace arl;

BEGIN_EVENT_TABLE(PlotWindowGLPane, wxGLCanvas)
EVT_LEFT_DOWN(PlotWindowGLPane::mouseLeftPressed)
EVT_LEFT_UP(PlotWindowGLPane::mouseLeftReleased)
EVT_SIZE(PlotWindowGLPane::resized)
EVT_KEY_DOWN(PlotWindowGLPane::keyPressed)
EVT_KEY_UP(PlotWindowGLPane::keyReleased)
EVT_PAINT(PlotWindowGLPane::render)
END_EVENT_TABLE()

using namespace plot_tool;

PlotWindowGLPane::PlotWindowGLPane(wxFrame* parent, int* args, const wxPoint& position)
    : wxGLCanvas(parent, wxID_ANY, args, position, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE)
{
    m_context = new wxGLContext(this);

    SetBackgroundStyle(wxBG_STYLE_CUSTOM);

    const float min_x = -1.0;
    const float max_x = 1.0;
    const float min_y = -1.0;
    const float max_y = 1.0;
    const float min_z = -1.0;
    const float max_z = 1.0;

    const AxesSettings axes_settings({min_x, min_y, min_z}, {max_x, max_y, max_z});

    Bind(wxEVT_MOTION, &PlotWindowGLPane::mouseMoved, this);

    axes_interactor_ = new AxesInteractor(axes_settings);
    axes_painter_ = new AxesPainter(axes_settings);

    hold_on_ = false;
    axes_set_ = false;

    glEnable(GL_MULTISAMPLE);

    glHint(GL_MULTISAMPLE_FILTER_HINT_NV, GL_NICEST);
}

PlotWindowGLPane::~PlotWindowGLPane()
{
    delete m_context;
}

void PlotWindowGLPane::addData(const plot_tool::RxList& rx_list, const std::vector<char*> data_vec)
{
    const Function function_type = rx_list.getObjectData<FunctionRx>();

    if (function_type == Function::HOLD_ON)
    {
        hold_on_ = true;
    }
    else if (function_type == Function::AXES)
    {
        axes_set_ = true;
        const int num_dimensions = rx_list.getObjectData<AxesDimensionsRx>();

        ASSERT((num_dimensions == 2) || (num_dimensions == 3))
            << "Error in dimension: " << num_dimensions;
        const auto new_ax_lim = rx_list.getObjectData<AxesMinMaxVecRx>();

        if (num_dimensions == 2)
        {
            axes_interactor_->setAxesLimits(arl::Vec2Dd(new_ax_lim.first.x, new_ax_lim.first.y),
                                            arl::Vec2Dd(new_ax_lim.second.x, new_ax_lim.second.y));
        }
        else
        {
            axes_interactor_->setAxesLimits(new_ax_lim.first, new_ax_lim.second);
        }
    }
    else if (function_type == Function::VIEW)
    {
        const float azimuth = rx_list.getObjectData<AzimuthRx>();
        const float elevation = rx_list.getObjectData<ElevationRx>();

        axes_interactor_->setViewAngles(azimuth, elevation);
    }
    else if (function_type == Function::CLEAR)
    {
        axes_set_ = false;
        hold_on_ = false;
        plot_data_handler_.clear();
    }
    else if (function_type == Function::SOFT_CLEAR)
    {
        plot_data_handler_.softClear();
    }
    else
    {
        if (!hold_on_)
        {
            plot_data_handler_.clear();
        }
        plot_data_handler_.addData(rx_list, data_vec);

        if (!axes_set_)
        {
            const std::pair<arl::Vec3Dd, arl::Vec3Dd> min_max =
                plot_data_handler_.getMinMaxVectors();
            axes_interactor_->setAxesLimits(min_max.first, min_max.second);
        }
    }

    // TODO: Add "holdClear" that only clears when new data comes in, to avoid flashing

    Refresh();
}

void PlotWindowGLPane::mouseLeftPressed(wxMouseEvent& event)
{
    const wxPoint current_point = event.GetPosition();

    left_mouse_button_.setIsPressed(current_point.x, current_point.y);
    Refresh();
}

void PlotWindowGLPane::mouseLeftReleased(wxMouseEvent& event)
{
    (void)event;

    left_mouse_button_.setIsReleased();
    Refresh();
}

void PlotWindowGLPane::mouseMoved(wxMouseEvent& event)
{
    if (left_mouse_button_.isPressed())
    {
        const wxPoint current_point = event.GetPosition();
        left_mouse_button_.updateOnMotion(current_point.x, current_point.y);
        axes_interactor_->registerMouseDragInput(left_mouse_button_.getDeltaPos().x,
                                                 left_mouse_button_.getDeltaPos().y);

        Refresh();
    }
}

void PlotWindowGLPane::keyPressed(wxKeyEvent& event)
{
    const int key_code = event.GetKeyCode();

    // Only add alpha numeric keys due to errors when clicking outside of window
    if (std::isalnum(key_code))
    {
        keyboard_state_.keyGotPressed(key_code);
    }
    Refresh();
}

void PlotWindowGLPane::keyReleased(wxKeyEvent& event)
{
    const int key_code = event.GetKeyCode();

    // Only add alpha numeric keys due to errors when clicking outside of window
    if (std::isalnum(key_code))
    {
        keyboard_state_.keyGotReleased(key_code);
    }
    Refresh();
}

void PlotWindowGLPane::resized(wxSizeEvent& evt)
{
    // (void)evt;
    this->SetSize(evt.GetSize());

    Refresh();
}

// Returns window width in pixels
int PlotWindowGLPane::getWidth()
{
    return GetSize().x;
}

// Returns window height in pixels
int PlotWindowGLPane::getHeight()
{
    return GetSize().y;
}

InteractionType keyboardStateToInteractionType(const KeyboardState& keyboard_state)
{
    if (keyboard_state.keyIsPressed('C'))
    {
        return InteractionType::RESET;
    }
    else if (keyboard_state.keyIsPressed('P'))
    {
        return InteractionType::PAN;
    }
    else if (keyboard_state.keyIsPressed('R'))
    {
        return InteractionType::ROTATE;
    }
    else if (keyboard_state.keyIsPressed('Z'))
    {
        return InteractionType::ZOOM;
    }
    else
    {
        return InteractionType::UNCHANGED;
    }
}

void PlotWindowGLPane::render(wxPaintEvent& evt)
{
    (void)evt;
    if (!IsShown())
        return;

    // clang-format off
    /*const double m[] = {1, 0, 0, 0, 
                        0, 0, 1, 0, 
                        0, 1, 0, 0, 
                        0, 0, 0, 1};
    // clang-format on
    glLoadMatrixd(m);*/

    wxGLCanvas::SetCurrent(*m_context);
    wxPaintDC(
        this);

    glEnable(GL_MULTISAMPLE);

    const float bg_color = 190.0f;

    glClearColor(bg_color / 255.0f, bg_color / 255.0f, bg_color / 255.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    axes_interactor_->update(
        keyboardStateToInteractionType(keyboard_state_), getWidth(), getHeight());

    axes_painter_->paint(axes_interactor_->getAxesLimits(),
                         axes_interactor_->getViewAngles(),
                         axes_interactor_->generateGridVectors(),
                         axes_interactor_->getCoordConverter());

    glEnable(GL_DEPTH_TEST);  // TODO: Put in "plotBegin" and "plotEnd"?
    axes_painter_->plotBegin();

    plot_data_handler_.visualize();

    axes_painter_->plotEnd();
    glDisable(GL_DEPTH_TEST);

    // glFlush();
    SwapBuffers();
}
