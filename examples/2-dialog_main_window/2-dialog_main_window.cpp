#include "resource.h"

#include <winlamb/dialog_main.h>

#include <sstream>

class DialogMainWindow : public wl::dialog_main
{
public:
    DialogMainWindow();
};

DialogMainWindow::DialogMainWindow()
{
    setup.dialogId = IDD_MAIN;
    
    on_message(WM_INITDIALOG, [this](wl::params p) -> INT_PTR
    {
        set_text(L"A new title for the dialog");
        return TRUE;
    });
    on_message(WM_LBUTTONDOWN, [this](wl::wm::lbuttondown p) -> INT_PTR
    {
        const bool isCtrlDown = p.has_ctrl();
        if (isCtrlDown)
        {
            const long xPos = p.pos().x;
            std::wostringstream str;
            str << L"Ctrl click at position " << xPos;
            MessageBoxW(hwnd(), str.str().c_str(), L"Mouse Click", MB_OK);
        }
        return TRUE;
    });
    on_command(IDCANCEL, [this](wl::params) -> INT_PTR
    {
        SendMessage(hwnd(), WM_CLOSE, 0, 0);
        return TRUE;
    });
    on_command(IDOK, [this](wl::params) -> INT_PTR
    {
        SendMessage(hwnd(), WM_CLOSE, 0, 0);
        return TRUE;
    });
}

RUN(DialogMainWindow);
