#include <arl/utilities/logging.h>

#include "main_application/main_window.h"

using namespace plot_tool;

void MainWindow::eventReceiveFunction(wxCommandEvent& event)
{
    (void)event;
    handleSentCommands();
    mtx_.unlock();
}

void MainWindow::handleSentCommands()
{
    const Function function_type = rx_list_.getObjectData<FunctionRx>();

    if (function_type == Function::FIGURE)
    {
        if (rx_list_.hasKey(Command::FIGURE_NUM))
        {
            const char figure_number = rx_list_.getObjectData<FigureNumRx>();
            if (figureWindowExists(figure_number))
            {
                setCurrentPlotWindowFromFigNum(figure_number);
            }
            else
            {
                createNewPlotWindow(figure_number);
            }
        }
        else
        {
            createNewPlotWindow();
        }
    }
    else
    {
        if (plot_windows_.size() == 0)
        {
            createNewPlotWindow();
        }
        current_plot_window_.first->addData(rx_list_, receiver_buffer_pointers_);
    }
}

void MainWindow::setCurrentPlotWindowFromFigNum(const size_t figure_number)
{
    bool is_set = false;
    for (auto plot_window : plot_windows_)
    {
        if (figure_number == plot_window.first->getFigureNum())
        {
            current_plot_window_ = plot_window;
            is_set = true;
        }
    }
    ASSERT(is_set) << "Couldn't find plot window from figure number!";
}

bool MainWindow::figureWindowExists(const size_t fig_num) const
{
    bool window_exists = false;
    for (auto plot_window : plot_windows_)
    {
        if (fig_num == plot_window.first->getFigureNum())
        {
            window_exists = true;
        }
    }
    return window_exists;
}
