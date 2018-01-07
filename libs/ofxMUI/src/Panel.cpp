//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofx/MUI/Panel.h"
#include "ofGraphics.h"


namespace ofx {
namespace MUI {


Panel::Panel(float x, float y, float width, float height):
    Panel("", x, y, width, height)
{
}


Panel::Panel(const std::string& id, float x, float y, float width, float height):
    Widget(id, x, y, width, height)
{
    addEventListener(keyDown,
                     &Panel::onKeyboardDownEvent,
                     false,
                     std::numeric_limits<int>::lowest());
}


Panel::~Panel()
{
}


void Panel::onDraw() const
{
    Widget::onDraw();
    ofDrawBitmapString(getId(), 20, 20);
}


void Panel::onKeyboardDownEvent(DOM::KeyboardUIEventArgs& evt)
{
    if (this == evt.target())
    {
        ofLogNotice("Panel::onKeyboardDownEvent") << getId() << " : " << evt.key().codepoint;
    }
}


} } // namespace ofx::MUI
