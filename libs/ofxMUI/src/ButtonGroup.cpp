//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier: MIT
//


#include "ofx/MUI/ButtonGroup.h"


namespace ofx {
namespace MUI {


const std::string ButtonGroupEventArgs::BUTTON_GROUP_UP = "buttongroupup";
const std::string ButtonGroupEventArgs::BUTTON_GROUP_DOWN = "buttongroupdown";
//const std::string ButtonEventArgs::BUTTON_GROUP_PRESSED = "buttongrouppressed";
const std::string ButtonGroupEventArgs::BUTTON_GROUP_STATE_CHANGED = "buttongroupstatechanged";


ButtonGroupEventArgs::~ButtonGroupEventArgs()
{
}



ButtonGroup::ButtonGroup(const std::string& id,
                         DOM::Orientation orientation):
    ButtonGroup(id, 0, 0, 0, 0, orientation)
{
}


ButtonGroup::ButtonGroup(const std::string& id,
                         float x,
                         float y,
                         float width,
                         float height,
                         DOM::Orientation orientation):
    Widget(id, x, y, width, height),
    _orientation(orientation)
{
//    createLayout<DOM::BoxLayout>(this, orientation);

    // Register for any events that this will provide.
    registerEventType(ButtonGroupEventArgs::BUTTON_GROUP_DOWN, &buttonGroupDown);
    registerEventType(ButtonGroupEventArgs::BUTTON_GROUP_UP, &buttonGroupUp);
    registerEventType(ButtonGroupEventArgs::BUTTON_GROUP_STATE_CHANGED, &buttonGroupStateChanged);

    // Register for any events that this will listen for.
    registerEventType(ButtonEventArgs::BUTTON_DOWN, &_childButton);
    registerEventType(ButtonEventArgs::BUTTON_UP, &_childButton);
    registerEventType(ButtonEventArgs::BUTTON_STATE_CHANGED, &_childButton);

    // We listen for ALL ButtonEventArgs::BUTTON_* from one method for convenience.
    //
    // We listen on the CAPTURE phase so that none of the CHILD elements of
    // OUR children will receive the BUBBLED messages.
    addEventListener(_childButton,
                     &ButtonGroup::_onChildButton,
                     true,
                     std::numeric_limits<int>::lowest());
}


ButtonGroup::~ButtonGroup()
{
    removeEventListener(_childButton,
                        &ButtonGroup::_onChildButton,
                        true,
                        std::numeric_limits<int>::lowest());
}


void ButtonGroup::onDraw() const
{
    ofSetColor(255, 127);
    ofFill();
    ofDrawRectangle(0, 0, getWidth(), getHeight());
}


void ButtonGroup::_onChildButton(ButtonEventArgs& e)
{
    Button* source = dynamic_cast<Button*>(e.source());
    
    if (e.type() == ButtonEventArgs::BUTTON_UP)
    {
        ButtonGroupEventArgs evt(ButtonGroupEventArgs::BUTTON_GROUP_UP,
                                 this,
                                 this,
                                 nullptr,
                                 true,
                                 true,
                                 e.timestamp());
        evt.button = source;
        this->dispatchEvent(evt);
    }
    else if (e.type() == ButtonEventArgs::BUTTON_DOWN)
    {
        ButtonGroupEventArgs evt(ButtonGroupEventArgs::BUTTON_GROUP_DOWN,
                                 this,
                                 this,
                                 nullptr,
                                 true,
                                 true,
                                 e.timestamp());
        evt.button = source;
        this->dispatchEvent(evt);
    }
    else if (e.type() == ButtonEventArgs::BUTTON_STATE_CHANGED)
    {
        ButtonGroupEventArgs evt(ButtonGroupEventArgs::BUTTON_GROUP_STATE_CHANGED,
                                 this,
                                 this,
                                 nullptr,
                                 true,
                                 true,
                                 e.timestamp());
        evt.button = source;
        this->dispatchEvent(evt);
    }
    
    // Consume the event.
    e.stopPropagation();
}



} } // namespace ofx::MUI



