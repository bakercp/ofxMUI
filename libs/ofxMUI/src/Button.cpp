// =============================================================================
//
// Copyright (c) 2009-2016 Christopher Baker <http://christopherbaker.net>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// =============================================================================


#include "ofx/MUI/Button.h"
#include "ofx/MUI/Styles.h"


namespace ofx {
namespace MUI {


const std::string ButtonEventArgs::BUTTON_DOWN = "buttondown";
const std::string ButtonEventArgs::BUTTON_UP = "buttonup";
const std::string ButtonEventArgs::BUTTON_PRESSED = "buttonpressed";


ButtonEventArgs::~ButtonEventArgs()
{
}


Button::Button(const std::string& id,
               float x,
               float y,
               float width,
               float height):
    Widget(id, x, y, width, height),
    _value(id, 0, 0, _stateCount)
{
    registerEventType(ButtonEventArgs::BUTTON_DOWN, &onButtonDown);
    registerEventType(ButtonEventArgs::BUTTON_UP, &onButtonUp);
    registerEventType(ButtonEventArgs::BUTTON_PRESSED, &onButtonPressed);

    _value.addListener(this,
                       &Button::_onValueChanged,
                       std::numeric_limits<int>::lowest());

    addEventListener(pointerDown, &Button::onPointerEvent, false, std::numeric_limits<int>::min());
    addEventListener(pointerUp, &Button::onPointerEvent, false, std::numeric_limits<int>::min());

    addEventListener(gotPointerCapture, &Button::onPointerCaptureEvent);
    addEventListener(lostPointerCapture, &Button::onPointerCaptureEvent);

    setImplicitPointerCapture(true);
}


Button::~Button()
{
    // Remove the listener from the local or bound parameters.
    _value.removeListener(this,
                          &Button::_onValueChanged,
                          std::numeric_limits<int>::lowest());

    removeEventListener(pointerDown, &Button::onPointerEvent, false, std::numeric_limits<int>::min());
    removeEventListener(pointerUp, &Button::onPointerEvent, false, std::numeric_limits<int>::min());

    removeEventListener(gotPointerCapture, &Button::onPointerCaptureEvent);
    removeEventListener(lostPointerCapture, &Button::onPointerCaptureEvent);
}


void Button::setTriggerOnRelease(bool value)
{
    _triggerOnRelease = value;
}


bool Button::getTriggerOnRelease() const
{
    return _triggerOnRelease;
}


void Button::setPointerOverOnRelease(bool value)
{
    _pointerOverOnRelease = value;
}


bool Button::getPointerOverOnRelease() const
{
    return _pointerOverOnRelease;
}


void Button::onDraw() const
{
    if (isPointerDown())
    {
		ofSetColor(getStyles()->getColor(Styles::ROLE_BACKGROUND, Styles::STATE_DOWN));
    }
    else if (isPointerOver())
    {
        ofSetColor(getStyles()->getColor(Styles::ROLE_BACKGROUND, Styles::STATE_OVER));
    }
    else
    {
        ofSetColor(getStyles()->getColor(Styles::ROLE_BACKGROUND, Styles::STATE_NORMAL));
    }

	ofDrawRectangle(0, 0, getWidth(), getHeight());

	if (isPointerDown())
	{
		ofSetColor(getStyles()->getColor(Styles::ROLE_FOREGROUND, Styles::STATE_DOWN));
	}
	else if (isPointerOver())
	{
		ofSetColor(getStyles()->getColor(Styles::ROLE_FOREGROUND, Styles::STATE_OVER));
	}
	else
	{
		ofSetColor(getStyles()->getColor(Styles::ROLE_FOREGROUND, Styles::STATE_NORMAL));
	}

	ofDrawRectangle(5, 5, getWidth() - 10, getHeight() - 10);

    ofNoFill();
    ofSetColor(getStyles()->getColor(Styles::ROLE_BORDER, Styles::STATE_NORMAL));
    ofDrawRectangle(0, 0, getWidth(), getHeight());

}


void Button::onPointerEvent(DOM::PointerUIEventArgs& e)
{
    if (e.type() == PointerEventArgs::POINTER_DOWN)
    {
        // ofNotifyEvent(onButtonDown, this);
        ButtonEventArgs buttonDown(ButtonEventArgs::BUTTON_DOWN,
                                   this,
                                   this,
                                   nullptr,
                                   true,
                                   true,
                                   e.timestamp());

        this->dispatchEvent(buttonDown);

        if (!_triggerOnRelease)
        {
            _incrementState();
        }
    }
    else if (e.type() == PointerEventArgs::POINTER_UP)
    {

        if (_triggerOnRelease &&
            (!_pointerOverOnRelease ||
             (_pointerOverOnRelease && isPointerOver())))
        {
            _incrementState();
        }

        ButtonEventArgs buttonUp(ButtonEventArgs::BUTTON_UP,
                                 this,
                                 this,
                                 nullptr,
                                 true,
                                 true,
                                 e.timestamp());
        this->dispatchEvent(buttonUp);

//        ofNotifyEvent(onButtonUp, this);

        ButtonEventArgs buttonPressed(ButtonEventArgs::BUTTON_PRESSED,
                                      this,
                                      this,
                                      nullptr,
                                      true,
                                      true,
                                      e.timestamp());
        this->dispatchEvent(buttonPressed);

//        ofNotifyEvent(onButtonPressed, this);
    }
}


void Button::onPointerCaptureEvent(DOM::PointerCaptureUIEventArgs& e)
{
    if (PointerEventArgs::GOT_POINTER_CAPTURE == e.type() && _primaryPointerId == 0)
    {
        _primaryPointerId = e.id();
    }
    else if (PointerEventArgs::LOST_POINTER_CAPTURE == e.type() && _primaryPointerId == e.id())
    {
        _primaryPointerId = 0;
    }
}


void Button::_onValueChanged(const void* sender, int& value)
{
    // We forward the event changes as sent by the slider.
    ofNotifyEvent(onValueChanged, value, this);
}


int Button::operator = (int v)
{
    _value = v;
    return v;
}


Button::operator const int& ()
{
    return _value;
}


void Button::_incrementState()
{
    _value = (_value + 1) % _stateCount;
}


ToggleButton::ToggleButton(const std::string& id,
                           float x,
                           float y,
                           float width,
                           float height):
    Button(id, x, y, width, height)
{
    _stateCount = 2;
    _value.setMax(_stateCount);
}


ToggleButton::~ToggleButton()
{
}


void ToggleButton::onDraw() const
{
    Button::onDraw();

    if (_value)
    {
        ofFill();
        ofSetColor(getStyles()->getColor(Styles::ROLE_ACCENT, Styles::STATE_DOWN));
        ofDrawRectangle(10, 10, getWidth() - 20, getHeight() - 20);
    }
}



RadioButton::~RadioButton()
{
}


void RadioButton::onDraw() const
{
    if (_value)
    {
        ofFill();
    }
    else
    {
        ofNoFill();
    }

    ofSetColor(getStyles()->getColor(Styles::ROLE_ACCENT, Styles::STATE_DOWN));
    ofDrawEllipse(getWidth() / 2, getHeight() / 2, getWidth() - 10, getHeight() - 10);
}


} } // namespace ofx::MUI



