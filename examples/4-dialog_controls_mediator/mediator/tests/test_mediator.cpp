#include <dialog.h>
#include <mediator.h>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

class MockDialog : public Dialog
{
public:
    ~MockDialog() override = default;

    MOCK_METHOD(void, enableActionButton, (bool enabled));
    MOCK_METHOD(std::wstring, getActionText, (), (const));
    MOCK_METHOD(void, performAction, (const std::wstring &action));
    MOCK_METHOD(void, displayClickPosition, (const std::wstring &message, const std::wstring &title));
    MOCK_METHOD(void, close, ());
};

class MediatorTest : public testing::Test
{
public:
protected:
    testing::StrictMock<MockDialog> dialog;
    Mediator mediator{&dialog};
};

TEST_F(MediatorTest, construct)
{
    // setup and tear down does it all.
}

TEST_F(MediatorTest, left_button_click_no_modifiers_does_nothing)
{
    wl::wm::lbuttondown params{wl::params{WM_LBUTTONDOWN, MK_LBUTTON}};

    const INT_PTR result = mediator.leftButtonDown(params);

    EXPECT_EQ( TRUE, result );
}

TEST_F(MediatorTest, ctrl_left_button_click_displays_position)
{
    using namespace testing;
    wl::wm::lbuttondown params{wl::params{WM_LBUTTONDOWN, MK_LBUTTON | MK_CONTROL}};
    EXPECT_CALL(dialog, displayClickPosition(_, _));

    const INT_PTR result = mediator.leftButtonDown(params);

    EXPECT_EQ( TRUE, result );
}

TEST_F(MediatorTest, ctrl_left_button_click_displays_position_message)
{
    using namespace testing;
    wl::wm::lbuttondown params{wl::params{WM_LBUTTONDOWN, MK_LBUTTON | MK_CONTROL, MAKELONG(10, 15)}};
    EXPECT_CALL(dialog, displayClickPosition(StrEq(L"Ctrl click at position 10"), StrEq(L"Mouse Click")));

    const INT_PTR result = mediator.leftButtonDown(params);

    EXPECT_EQ( TRUE, result );
}

TEST_F(MediatorTest, action_text_non_change_notification)
{
    using namespace testing;
    wl::wm::command params{wl::params{WM_COMMAND, MAKELONG(0, EN_SETFOCUS)}};

    const INT_PTR result = mediator.actionTextCommand(params);

    EXPECT_EQ( TRUE, result );
}

TEST_F(MediatorTest, action_text_change_notification_non_empty_enables_button)
{
    using namespace testing;
    wl::wm::command params{wl::params{WM_COMMAND, MAKELONG(0, EN_CHANGE)}};
    EXPECT_CALL(dialog, getActionText()).WillRepeatedly(Return(L"Non-empty"));
    EXPECT_CALL(dialog, enableActionButton(true));

    const INT_PTR result = mediator.actionTextCommand(params);

    EXPECT_EQ( TRUE, result );
}

TEST_F(MediatorTest, action_text_change_notification_empty_disables_button)
{
    using namespace testing;
    wl::wm::command params{wl::params{WM_COMMAND, MAKELONG(0, EN_CHANGE)}};
    EXPECT_CALL(dialog, getActionText()).WillRepeatedly(Return(L""));
    EXPECT_CALL(dialog, enableActionButton(false));

    const INT_PTR result = mediator.actionTextCommand(params);

    EXPECT_EQ( TRUE, result );
}

TEST_F(MediatorTest, action_button_non_click_notification)
{
    using namespace testing;
    wl::wm::command params{wl::params{WM_COMMAND, MAKELONG(0, BN_SETFOCUS)}};

    const INT_PTR result = mediator.actionButtonCommand(params);

    EXPECT_EQ( TRUE, result );
}

TEST_F(MediatorTest, action_button_click_performs_action)
{
    using namespace testing;
    wl::wm::command params{wl::params{WM_COMMAND, MAKELONG(0, BN_CLICKED)}};
    const wchar_t *action{L"Action"};
    EXPECT_CALL(dialog, getActionText()).WillRepeatedly(Return(action));
    EXPECT_CALL(dialog, performAction(StrEq(action)));

    const INT_PTR result = mediator.actionButtonCommand(params);

    EXPECT_EQ( TRUE, result );
}

TEST_F(MediatorTest, ok_button_clicked_closes_dialog)
{
    using namespace testing;
    wl::wm::command params{wl::params{WM_COMMAND}};
    EXPECT_CALL(dialog, close());

    const INT_PTR result = mediator.okButtonCommand(params);

    EXPECT_EQ( TRUE, result );
}

TEST_F(MediatorTest, cancel_button_clicked_closes_dialog)
{
    using namespace testing;
    wl::wm::command params{wl::params{WM_COMMAND}};
    EXPECT_CALL(dialog, close());

    const INT_PTR result = mediator.cancelButtonCommand(params);

    EXPECT_EQ( TRUE, result );
}
