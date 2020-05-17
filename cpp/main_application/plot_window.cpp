#include "plot_window.h"

#include "main_application/plot_window_gl_pane.h"

PlotWindow::PlotWindow(wxWindow* parent, const int figure_number)
    : wxFrame(parent,
              wxID_ANY,
              "Figure " + std::to_string(figure_number),
              wxPoint(30, 30),
              wxSize(600, 628)),
      figure_number_(figure_number),
      window_title_("Figure " + std::to_string(figure_number_))
{
    window_id_ = GetId();

    int args[] = {WX_GL_RGBA,
                  WX_GL_DOUBLEBUFFER,
                  WX_GL_DEPTH_SIZE,
                  16,
                  WX_GL_SAMPLES,
                  4,
                  WX_GL_SAMPLE_BUFFERS,
                  1,
                  0};

    gl_pane_ = new PlotWindowGLPane(this, args, wxPoint(0, 0));

    sizer_ = new wxBoxSizer(wxVERTICAL);
    sizer_->Add(gl_pane_, 1, wxEXPAND, 0);

    SetSizer(sizer_);
    SetAutoLayout(true);

    gl_pane_->SetFocus();

    Show();

    Refresh();
}

PlotWindow::~PlotWindow()
{
    delete gl_pane_;
}

void PlotWindow::OnSize(wxSizeEvent& event)
{
    (void)event;
    // gl_pane_->SetSize(GetSize().x, GetSize().y);
}

size_t PlotWindow::getFigureNum() const
{
    return figure_number_;
}

void PlotWindow::onButtonPressed(wxCommandEvent& event)
{
    (void)event;
}

void PlotWindow::OnClose(wxCloseEvent& event)
{
    (void)event;
    // Destroy();
}

std::string PlotWindow::getWindowName()
{
    return window_title_.ToStdString();
}

void PlotWindow::addData(const plot_tool::RxList& rx_list, const std::vector<char*> data_vec)
{
    gl_pane_->addData(rx_list, data_vec);
}
