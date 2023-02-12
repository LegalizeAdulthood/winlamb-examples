#include <winlamb/window_main.h>

#include <sstream>

class SimpleMainWindow : public wl::window_main
{
public:
    SimpleMainWindow();
};

SimpleMainWindow::SimpleMainWindow()
{
    setup.wndClassEx.lpszClassName = L"Main Window";
    setup.title = L"Main Window";
    setup.style |= WS_MINIMIZEBOX;
    
    on_message(WM_CREATE, [this](wl::wm::create p) -> LRESULT
    {
        set_text(L"A new title for this window");
        return 0;
    });
    on_message(WM_LBUTTONDOWN, [this](wl::wm::lbuttondown p) -> LRESULT
    {
        const bool isCtrlDown = p.has_ctrl();
        if (isCtrlDown)
        {
            const long xPos = p.pos().x;
            std::wostringstream str;
            str << L"Ctrl click at position " << xPos;
            MessageBoxW(hwnd(), str.str().c_str(), L"Mouse Click", MB_OK);
        }
        return 0;
    });
}

RUN(SimpleMainWindow);
