#include "resource.h"

#include <winlamb/button.h>
#include <winlamb/dialog_main.h>
#include <winlamb/sysdlg.h>
#include <winlamb/textbox.h>

#include <sstream>

class DialogControls : public wl::dialog_main
{
public:
    DialogControls();

private:
    wl::button m_button;
    wl::textbox m_text;
};

DialogControls::DialogControls()
{
    setup.dialogId = IDD_MAIN;
    
    on_message(WM_INITDIALOG, [this](wl::params p) -> INT_PTR
    {
        m_button.assign(this, IDC_ACTION_BUTTON)
            .set_text(L"Action")
            .set_focus();
        m_text.assign(this, IDC_ACTION_TEXT)
            .set_text(L"Initial action text");
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
    on_command(IDC_ACTION_TEXT, [this](wl::wm::command p) -> INT_PTR
    {
        if (p.control_notif_code() == EN_CHANGE)
        {
            m_button.set_enabled(!m_text.get_text().empty());
        }
        return TRUE;
    });
    on_command(IDC_ACTION_BUTTON, [this](wl::wm::command p) -> INT_PTR
    {
        if (p.control_notif_code() == BN_CLICKED)
        {
            wl::sysdlg::msgbox(hwnd(), L"Action", m_text.get_text(), MB_OK);
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

RUN(DialogControls);
