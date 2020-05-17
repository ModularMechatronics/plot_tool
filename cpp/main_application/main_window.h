#ifndef MAIN_WINDOW_H_
#define MAIN_WINDOW_H_

#include <wx/button.h>
#include <wx/frame.h>
#include <wx/textctrl.h>
#include <wx/wx.h>

#include <mutex>
#include <string>
#include <thread>
#include <tuple>
#include <utility>
#include <vector>

#include "communication/rx_list.h"
#include "communication/server.h"
#include "plot_window.h"

/*
Interface requirements for plot windows
 - Sending "figure(1);" from client application shall
    * Open a new figure if figure 1 doesn't exist
    * Set figure 1 to the current active figure if it does exist
 - One shall be able to open a figure with the base gui
 - The gui shall be able to read a configuration file (like json) and
   open plot windows accordingly (number of windows, axes settings for each window)
*/

wxDEFINE_EVENT(EVENT_TYPE_HANDLE_NEW_DATA, wxCommandEvent);

class MainWindow : public wxFrame
{
private:
    wxButton* test_button_;
    wxButton* button_new_window_;
    wxButton* button_clear_command_;

    wxTextCtrl* text_edit_box_;

    wxString window_title_;
    std::thread* receive_thread_;
    std::mutex mtx_;
    std::vector<std::string> plot_command_vector_;
    plot_tool::RxList rx_list_;
    plot_tool::Server* server_;

    std::vector<std::pair<PlotWindow*, int>> plot_windows_;
    std::pair<PlotWindow*, int> current_plot_window_;

    void onButtonPressed(wxCommandEvent& event);
    void onClearCommandButtonPressed(wxCommandEvent& event);
    void onNewWindowButtonPressed(wxCommandEvent& event);

    void eventReceiveFunction(wxCommandEvent& event);
    void receiverThreadFunction();
    void receiverWxThreadFunction();

    std::vector<char*> receiver_buffer_pointers_;

    int figure_counter_;

    void handleSentCommands();
    bool figureWindowExists(const size_t fig_num) const;
    void createNewPlotWindow(const size_t fig_num);
    void createNewPlotWindow();
    void setCurrentPlotWindowFromFigNum(const size_t figure_number);

public:
    MainWindow();
    MainWindow(const wxString& title);
    virtual void OnClose(wxCloseEvent& event);
    void OnChildDestroy(wxCloseEvent& event);

    void printToCmdLine(const std::string& str);
};

#endif
