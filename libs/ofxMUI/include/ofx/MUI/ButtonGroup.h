//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier: MIT
//


#pragma once
	

#include "ofx/MUI/Types.h"
#include "ofx/MUI/Widget.h"
#include "ofx/MUI/Button.h"


namespace ofx {
namespace MUI {


/// \brief A set of event arguments for Button events.
class ButtonGroupEventArgs: public DOM::EventArgs
{
public:
    using DOM::EventArgs::EventArgs;

    /// \brief Destroy the ButtonGroupEventArgs.
    virtual ~ButtonGroupEventArgs();

    Button* button = nullptr;

//    
//    std::string value;
//    
//    /// \brief The state of the button.
//    int state = 0;

    /// \brief The button up event type.
    static const std::string BUTTON_GROUP_UP;

    /// \brief The button down event type.
    static const std::string BUTTON_GROUP_DOWN;

//    /// \brief The button pressed event type.
//    static const std::string BUTTON_GROUP_PRESSED;

    /// \brief The event when the button state changes.
    static const std::string BUTTON_GROUP_STATE_CHANGED;

};


class ButtonGroup: public Widget
{
public:
    ButtonGroup(const std::string& id,
                DOM::Orientation orientation);

    ButtonGroup(const std::string& id,
                float x = 0,
                float y = 0,
                float width = 40,
                float height = 40,
                DOM::Orientation orientation = DOM::Orientation::VERTICAL);

    virtual ~ButtonGroup();

    virtual void onDraw() const override;

    template <typename... Args>
    RadioButton* addRadioButton(Args&&... args)
    {
        RadioButton* button = addChild(std::make_unique<RadioButton>(std::forward<Args>(args)...));

        if (button->siblings<RadioButton>().empty())
        {
            button->setState(1);
        }

        return button;
    }

    template <typename... Args>
    ToggleButton* addToggleButton(Args&&... args)
    {
        ToggleButton* button = addChild(std::make_unique<ToggleButton>(std::forward<Args>(args)...));

        return button;
    }

//    /// \brief Event called when button is pressed and released.
//    ///
//    /// This event follows the require release over policy.
//    DOM::DOMEvent<ButtonEventArgs> buttonPressed;

    /// \brief The event called when the button goes from an up to down state.
    DOM::DOMEvent<ButtonGroupEventArgs> buttonGroupDown;

    /// \brief The event called when the button goes from down to up state.
    DOM::DOMEvent<ButtonGroupEventArgs> buttonGroupUp;

    /// \brief The event called when the button value changes.
    ///
    /// This event follows various policies of the button configuration.
    DOM::DOMEvent<ButtonGroupEventArgs> buttonGroupStateChanged;
    
protected:
    /// \brief A protected event for child buttons.
    DOM::DOMEvent<ButtonEventArgs> _childButton;

    void _onChildButton(ButtonEventArgs& e);

    /// \brief The ButtonGroup orientation.
    DOM::Orientation _orientation = DOM::Orientation::HORIZONTAL;

};


} } // ofx::MUI
