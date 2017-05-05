//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once
	

#include "ofx/MUI/Widget.h"


namespace ofx {
namespace MUI {


//    addEventListener(gotPointerCapture, &Widget::_onPointerCaptureEvent, false, std::numeric_limits<int>::min());
//    addEventListener(lostPointerCapture, &Widget::_onPointerCaptureEvent, false, std::numeric_limits<int>::min());
//
//    setImplicitPointerCapture(true);
//}
//
//
//    Widget::~Widget()
//    {
//        removeEventListener(pointerMove, &Widget::_onPointerEvent, false, std::numeric_limits<int>::min());
//        removeEventListener(pointerDown, &Widget::_onPointerEvent, false, std::numeric_limits<int>::min());


class Panel: public Widget
{
public:
    Panel(float x, float y, float width, float height):
        Panel("", x, y, width, height)
    {
    }

    Panel(const std::string& id, float x, float y, float width, float height):
        Widget(id, x, y, width, height),
		_resizeable(false)
    {
        addEventListener(keyDown, &Panel::onKeyboardDownEvent, false, std::numeric_limits<int>::min());

        setDraggable(true);
    }

    virtual ~Panel()
    {
    }

    void onDraw() const override
    {
        Widget::onDraw();
        ofDrawBitmapString(getId(), 20, 20);
    }

    void onKeyboardDownEvent(DOM::KeyboardUIEventArgs& evt)
    {
        if (this == evt.target())
        {
            std::cout << getId() << " : " << evt.key().codepoint << std::endl;
        }
    }

protected:
	bool _resizeable;

};


} } // ofx::MUI
