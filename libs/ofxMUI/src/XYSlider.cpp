//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier: MIT
//


#include "ofx/MUI/XYSlider.h"
#include "ofGraphics.h"
#include "ofMath.h"
#include "ofx/MUI/Styles.h"


namespace ofx {
namespace MUI {

//Panel::Panel(float x, float y, float width, float height):
//    Panel("", x, y, width, height)
//{
//}


XYSlider::XYSlider(const std::string& id, float x, float y, float width, float height):
    Widget(id, x, y, width, height)
{
    _value.addListener(this,
                       &XYSlider::_onValueChanged,
                       std::numeric_limits<int>::lowest());

    addEventListener(pointerDown, &XYSlider::onPointerEvent);
    addEventListener(pointerMove, &XYSlider::onPointerEvent);
    addEventListener(gotPointerCapture, &XYSlider::onPointerCaptureEvent);
    addEventListener(lostPointerCapture, &XYSlider::onPointerCaptureEvent);

    ofAddListener(Widget::resize, this, &XYSlider::_onResize, std::numeric_limits<int>::lowest());

    setImplicitPointerCapture(true);
}


XYSlider::~XYSlider()
{
    // Remove the listener from the local or bound parameters.
    _value.removeListener(this,
                          &XYSlider::_onValueChanged,
                          std::numeric_limits<int>::lowest());

    removeEventListener(pointerDown, &XYSlider::onPointerEvent);
    removeEventListener(pointerMove, &XYSlider::onPointerEvent);
    removeEventListener(gotPointerCapture, &XYSlider::onPointerCaptureEvent);
    removeEventListener(lostPointerCapture, &XYSlider::onPointerCaptureEvent);
}


void XYSlider::onDraw() const
{
    Widget::onDraw();
 
    ofSetColor(getStyles()->getColor(Styles::ROLE_TEXT, Styles::STATE_NORMAL));
    
    float x = ofMap(_value->x, _value.getMin().x, _value.getMax().x, 0, getWidth(), true);
    float y = ofMap(_value->y, _value.getMin().y, _value.getMax().y, 0, getHeight(), true);;
 
    ofDrawLine(x, 0, x, getHeight());
    ofDrawLine(0, y, getWidth(), y);

    ofDrawCircle(x, y, 5);
}


void XYSlider::onPointerEvent(DOM::PointerUIEventArgs& e)
{
    if (e.pointer().pointerId() == _primaryPointerId)
    {
        if (PointerEventArgs::POINTER_DOWN == e.type() ||
            PointerEventArgs::POINTER_MOVE == e.type())
        {
            // Local position.
            glm::vec2 position = screenToLocal(e.pointer().position());

            float x = ofMap(position.x, 0, getWidth(), _value.getMin().x, _value.getMax().x, true);
            float y = ofMap(position.y, 0, getHeight(), _value.getMin().y, _value.getMax().y, true);

            _value = glm::vec2(x, y);

//            std::cout << _value << std::endl;
        }
    }
}


void XYSlider::onPointerCaptureEvent(DOM::PointerCaptureUIEventArgs& e)
{
    if (PointerEventArgs::GOT_POINTER_CAPTURE == e.type() &&
        _primaryPointerId == 0)
    {
        _primaryPointerId = e.id();
    }
    else if (PointerEventArgs::LOST_POINTER_CAPTURE == e.type() &&
             _primaryPointerId == e.id())
    {
        _primaryPointerId = 0;
    }
}


void XYSlider::_onResize(DOM::ResizeEventArgs&)
{
}


void XYSlider::_onValueChanged(const void* sender, glm::vec2& value)
{
    // We forward the event changes as sent by the slider.
    ofNotifyEvent(valueChanged, value, this);
}


} } // namespace ofx::MUI
