#pragma once

#include <string>

class Dialog
{
public:
    virtual ~Dialog() = default;

    virtual void enableActionButton(bool enabled) = 0;
    virtual std::wstring getActionText() const = 0;
    virtual void performAction(const std::wstring &action) = 0;
    virtual void displayClickPosition(const std::wstring &message, const std::wstring &title) = 0;
    virtual void close() = 0;
};
