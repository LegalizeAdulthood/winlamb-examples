#include <dialog.h>
#include <mediator.h>
#include "resource.h"

#include <winlamb/button.h>
#include <winlamb/dialog_main.h>
#include <winlamb/sysdlg.h>
#include <winlamb/textbox.h>

#include <sstream>

class DialogControlsMediator : public wl::dialog_main, public Dialog
{
public:
    DialogControlsMediator();

    void enableActionButton(bool enabled) override;
    std::wstring getActionText() const override;
    void performAction(const std::wstring &action) override;
    void displayClickPosition(const std::wstring &message, const std::wstring &title) override;
    void close() override;

private:
    wl::button m_button;
    wl::textbox m_text;
    Mediator m_mediator{this};
};

DialogControlsMediator::DialogControlsMediator()
{
    setup.dialogId = IDD_MAIN;
    
    on_message(WM_INITDIALOG, [this](wl::params p)
    {
        m_button.assign(this, IDC_ACTION_BUTTON)
            .set_text(L"Action")
            .set_focus();
        m_text.assign(this, IDC_ACTION_TEXT)
            .set_text(L"Initial action text");
        return TRUE;
    });
    on_message(WM_LBUTTONDOWN, [this](wl::wm::lbuttondown p) { return m_mediator.leftButtonDown(p); });
    on_command(IDC_ACTION_TEXT, [this](wl::wm::command p) { return m_mediator.actionTextCommand(p); });
    on_command(IDC_ACTION_BUTTON, [this](wl::wm::command p) { return m_mediator.actionButtonCommand(p); });
    on_command(IDCANCEL, [this](wl::params p) { return m_mediator.okButtonCommand(p); });
    on_command(IDOK, [this](wl::params p) { return m_mediator.cancelButtonCommand(p); });
}

void DialogControlsMediator::enableActionButton(bool enabled)
{
    m_button.set_enabled(enabled);
}

std::wstring DialogControlsMediator::getActionText() const
{
    return m_text.get_text();
}

void DialogControlsMediator::performAction(const std::wstring &action)
{
    wl::sysdlg::msgbox(hwnd(), L"Action", action, MB_OK);
}

void DialogControlsMediator::displayClickPosition(const std::wstring &message, const std::wstring &title)
{
    wl::sysdlg::msgbox(hwnd(), title, message, MB_OK);
}

void DialogControlsMediator::close()
{
    SendMessage(hwnd(), WM_CLOSE, 0, 0);
}

RUN(DialogControlsMediator);
