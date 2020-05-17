#include <arl/utilities/logging.h>
#include <wx/wx.h>

#include <csignal>
#include <iostream>

#include "main_window.h"

class MainApp : public wxApp
{
private:
public:
    virtual bool OnInit();
    virtual int OnExit();
};

MainWindow* main_window;

IMPLEMENT_APP(MainApp)

bool MainApp::OnInit()
{
    system("rm -rf /tmp/socket_file_ /tmp/socket_file /tmp/socket_fil");

    main_window = new MainWindow("Plot tool v0.1");
    main_window->Show();

    SetTopWindow(main_window);

    return true;
}

int MainApp::OnExit()
{
    PRINT() << "Exit!";
    return true;
}
