//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier: MIT
//


#pragma once
	

#include "ofx/MUI/Widget.h"


namespace ofx {
namespace MUI {


//    addEventListener(gotPointerCapture, &Widget::_onPointerCaptureEvent, false, std::numeric_limits<int>::lowest());
//    addEventListener(lostPointerCapture, &Widget::_onPointerCaptureEvent, false, std::numeric_limits<int>::lowest());
//
//    setImplicitPointerCapture(true);
//}
//
//
//    Widget::~Widget()
//    {
//        removeEventListener(pointerMove, &Widget::_onPointerEvent, false, std::numeric_limits<int>::lowest());
//        removeEventListener(pointerDown, &Widget::_onPointerEvent, false, std::numeric_limits<int>::lowest());


class Panel: public Widget
{
public:
    Panel(const std::string& id = "",
          float x = 0,
          float y = 0,
          float width = 0,
          float height = 0);

    /// \brief Destroy the Panel.
    virtual ~Panel();

    // void onDraw() const override;

    void onKeyboardDownEvent(DOM::KeyboardUIEventArgs& evt);

protected:
    /// \brief True if the Panel can be resized.
    bool _resizeable = false;

};


} } // ofx::MUI
