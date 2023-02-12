#include "mediator.h"

#include <sstream>

INT_PTR Mediator::leftButtonDown(wl::wm::lbuttondown p)
{
    const bool isCtrlDown = p.has_ctrl();
    if (isCtrlDown)
    {
        const POINT pos = p.pos();
        const long xPos = pos.x;
        std::wostringstream str;
        str << L"Ctrl click at position " << xPos;
        m_dialog->displayClickPosition(str.str(), L"Mouse Click");
    }
    return TRUE;
}

INT_PTR Mediator::actionTextCommand(wl::wm::command p)
{
    if (p.control_notif_code() == EN_CHANGE)
    {
        m_dialog->enableActionButton(!m_dialog->getActionText().empty());
    }
    return TRUE;
}

INT_PTR Mediator::actionButtonCommand(wl::wm::command p)
{
    if (p.control_notif_code() == BN_CLICKED)
    {
        m_dialog->performAction(m_dialog->getActionText());
    }
    return TRUE;
}

INT_PTR Mediator::okButtonCommand(wl::wm::command p)
{
    m_dialog->close();
    return TRUE;
}

INT_PTR Mediator::cancelButtonCommand(wl::wm::command p)
{
    m_dialog->close();
    return TRUE;
}
