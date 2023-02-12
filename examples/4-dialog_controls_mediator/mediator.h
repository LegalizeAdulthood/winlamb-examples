#pragma once

#include "dialog.h"

#include <winlamb/internals/params_wm.h>

class Mediator
{
public:
    Mediator(Dialog *dialog) : m_dialog(dialog) {}

    INT_PTR leftButtonDown(wl::wm::lbuttondown p);
    INT_PTR actionTextCommand(wl::wm::command p);
    INT_PTR actionButtonCommand(wl::wm::command p);
    INT_PTR okButtonCommand(wl::wm::command p);
    INT_PTR cancelButtonCommand(wl::wm::command p);

private:
    Dialog *m_dialog;
};
