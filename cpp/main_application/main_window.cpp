#include "main_window.h"

#include <arl/utilities/logging.h>
#include <arl/utilities/misc.h>
#include <unistd.h>

#include <csignal>
#include <iostream>

using namespace plot_tool;

MainWindow::MainWindow(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title, wxPoint(30, 30), wxSize(300, 70))
{
    window_title_ = title;

    wxPanel* panel = new wxPanel(this, wxID_ANY);

    button_new_window_ =
        new wxButton(panel, wxID_ANY, _T("New figure"), wxPoint(10, 10), wxSize(100, 50));
    button_new_window_->Bind(
        wxEVT_COMMAND_BUTTON_CLICKED, &MainWindow::onNewWindowButtonPressed, this);

    Bind(wxEVT_CLOSE_WINDOW, &MainWindow::OnClose, this);
    Bind(EVENT_TYPE_HANDLE_NEW_DATA, &MainWindow::eventReceiveFunction, this);

    const size_t max_buffer_size = 1000000;
    server_ = new plot_tool::Server(
        "socket_file", max_buffer_size, &mtx_, &plot_command_vector_, rx_list_);

    for (size_t k = 0; k < server_->getNumBufferPointers(); k++)
    {
        receiver_buffer_pointers_.push_back(
            server_->getBufferPointer(k));  // TODO: Change into function of Server
    }

    current_plot_window_.first = nullptr;
    current_plot_window_.second = 0;

    receive_thread_ = new std::thread(&MainWindow::receiverThreadFunction, this);
    figure_counter_ = 0;

    //

    int argc = 1;
    char* argv[1] = {"hej"};
    glutInit(&argc, argv);
}

void MainWindow::onClearCommandButtonPressed(wxCommandEvent& event)
{
    (void)event;
    text_edit_box_->Clear();
}

void MainWindow::receiverThreadFunction()
{
    server_->start();

    wxCommandEvent data_received_event(EVENT_TYPE_HANDLE_NEW_DATA);
    data_received_event.SetString("New data received");

    while (1)
    {
        mtx_.lock();
        server_->receive();
        mtx_.unlock();
        mtx_.lock();
        wxPostEvent(this, data_received_event);
    }
}

void MainWindow::onButtonPressed(wxCommandEvent& event)
{
    (void)event;
}

void MainWindow::OnChildDestroy(wxCloseEvent& event)
{
    (void)event;
    wxWindow* ww = this->FindWindowById(event.GetId());
    for (size_t k = 0; k < plot_windows_.size(); k++)
    {
        if (plot_windows_[k].second == event.GetId())
        {
            plot_windows_.erase(plot_windows_.begin() + k);
        }
    }
    ww->Destroy();
    if (plot_windows_.size() > 0)
    {
        current_plot_window_ = plot_windows_[0];
    }
    else
    {
        current_plot_window_.first = nullptr;
        current_plot_window_.second = 0;
    }
}

void MainWindow::onNewWindowButtonPressed(wxCommandEvent& event)
{
    (void)event;
    createNewPlotWindow();
}

void MainWindow::createNewPlotWindow(const size_t fig_num)
{
    if (plot_windows_.size() >= 10)
    {
        LOG_WARNING() << "Too many plot windows!";
    }
    else
    {
        PlotWindow* plot_window = new PlotWindow(this, fig_num);

        plot_window->Show();
        const int window_id = plot_window->GetId();

        plot_windows_.push_back(std::pair<PlotWindow*, int>(plot_window, window_id));
        plot_window->Bind(wxEVT_CLOSE_WINDOW, &MainWindow::OnChildDestroy, this);
        current_plot_window_ = plot_windows_[plot_windows_.size() - 1];
        setCurrentPlotWindowFromFigNum(fig_num);
    }
}

void MainWindow::createNewPlotWindow()
{
    if (plot_windows_.size() >= 10)
    {
        LOG_WARNING() << "Too many plot windows!";
    }
    else
    {
        size_t new_figure_number = 0;
        for (auto plot_window : plot_windows_)
        {
            new_figure_number = std::max(new_figure_number, plot_window.first->getFigureNum());
        }
        new_figure_number++;

        PlotWindow* plot_window = new PlotWindow(this, new_figure_number);

        plot_window->Show();
        const int window_id = plot_window->GetId();

        plot_windows_.push_back(std::pair<PlotWindow*, int>(plot_window, window_id));
        plot_window->Bind(wxEVT_CLOSE_WINDOW, &MainWindow::OnChildDestroy, this);
        current_plot_window_ = plot_windows_[plot_windows_.size() - 1];
        setCurrentPlotWindowFromFigNum(new_figure_number);
    }
}

void MainWindow::OnClose(wxCloseEvent& event)
{
    (void)event;
    if (wxMessageBox("Are you sure you want to exit?",
                     "Please confirm",
                     wxICON_QUESTION | wxYES_NO) != wxYES)
    {
        return;
    }

    std::cout << "Window close" << std::endl;
    Destroy();
}
