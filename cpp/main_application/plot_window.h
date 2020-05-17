#ifndef PLOT_WINDOW_H_
#define PLOT_WINDOW_H_

#include <wx/button.h>
#include <wx/frame.h>
#include <wx/textctrl.h>

// Include order matters for gl and wxgl headers

#include <wx/glcanvas.h>
#include <wx/notebook.h>
#include <wx/wx.h>

#include <string>

#include "communication/rx_list.h"
#include "main_application/plot_window_gl_pane.h"

// https://forums.wxwidgets.org/viewtopic.php?t=43767
// https://stackoverflow.com/questions/14138/enabling-opengl-in-wxwidgets

class PlotWindow : public wxFrame
{
private:
    wxButton* test_button_;

    wxGLContext* gl_context_;

    PlotWindowGLPane* gl_pane_;

    void onButtonPressed(wxCommandEvent& event);
    void createOpenGLStuff();

    const size_t figure_number_;
    const wxString window_title_;
    int window_id_;
    wxBoxSizer* sizer_;

    void OnSize(wxSizeEvent& event);

public:
    ~PlotWindow();
    PlotWindow();
    PlotWindow(wxWindow* parent, const int window_id);
    virtual void OnClose(wxCloseEvent& event);

    std::string getWindowName();
    size_t getFigureNum() const;

    std::string* str_ptr;

    void addData(const plot_tool::RxList& rx_list, const std::vector<char*> data_vec);
};

#endif
