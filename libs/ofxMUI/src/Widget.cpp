// =============================================================================
//
// Copyright (c) 2009-2015 Christopher Baker <http://christopherbaker.net>
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


#include "ofx/MUI/Widget.h"
#include "ofx/DOM/Exceptions.h"


namespace ofx {
namespace MUI {


const std::string Widget::ROLE_FOREGROUND = "ROLE_FOREGROUND";
const std::string Widget::ROLE_BACKGROUND = "ROLE_BACKGROUND";
const std::string Widget::ROLE_BORDER = "ROLE_BORDER";
const std::string Widget::ROLE_TEXT = "ROLE_TEXT";
const std::string Widget::STATE_NORMAL = "STATE_NORMAL";
const std::string Widget::STATE_OVER = "STATE_OVER";
const std::string Widget::STATE_DOWN = "STATE_DOWN";
const std::string Widget::STATE_DISABLED = "STATE_DISABLED";
const std::string Widget::STATE_LOCKED = "STATE_LOCKED";


Widget::Widget(float x, float y, float width, float height):
    Widget("", x, y, width, height)
{
}


Widget::Widget(const std::string& id, float x, float y, float width, float height):
    DOM::Element(id, x, y, width, height)
{
    addEventListener(pointerMove, &Widget::_onPointerEvent, false, std::numeric_limits<int>::min());
    addEventListener(pointerDown, &Widget::_onPointerEvent, false, std::numeric_limits<int>::min());
    addEventListener(pointerUp, &Widget::_onPointerEvent, false, std::numeric_limits<int>::min());

    addEventListener(pointerOver, &Widget::_onPointerEvent, false, std::numeric_limits<int>::min());
    addEventListener(pointerEnter, &Widget::_onPointerEvent, false, std::numeric_limits<int>::min());
    addEventListener(pointerOut, &Widget::_onPointerEvent, false, std::numeric_limits<int>::min());
    addEventListener(pointerLeave, &Widget::_onPointerEvent, false, std::numeric_limits<int>::min());

    addEventListener(gotPointerCapture, &Widget::_onPointerCaptureEvent, false, std::numeric_limits<int>::min());
    addEventListener(lostPointerCapture, &Widget::_onPointerCaptureEvent, false, std::numeric_limits<int>::min());
}


Widget::~Widget()
{
    removeEventListener(pointerMove, &Widget::_onPointerEvent, false, std::numeric_limits<int>::min());
    removeEventListener(pointerDown, &Widget::_onPointerEvent, false, std::numeric_limits<int>::min());
    removeEventListener(pointerUp, &Widget::_onPointerEvent, false, std::numeric_limits<int>::min());

    removeEventListener(pointerOver, &Widget::_onPointerEvent, false, std::numeric_limits<int>::min());
    removeEventListener(pointerEnter, &Widget::_onPointerEvent, false, std::numeric_limits<int>::min());
    removeEventListener(pointerOut, &Widget::_onPointerEvent, false, std::numeric_limits<int>::min());
    removeEventListener(pointerLeave, &Widget::_onPointerEvent, false, std::numeric_limits<int>::min());

    removeEventListener(gotPointerCapture, &Widget::_onPointerCaptureEvent, false, std::numeric_limits<int>::min());
    removeEventListener(lostPointerCapture, &Widget::_onPointerCaptureEvent, false, std::numeric_limits<int>::min());
}


void Widget::onDraw()
{
    ofSetColor(getColor(ROLE_TEXT, STATE_NORMAL));
    ofDrawBitmapString(getId(), 2, 12);

    ofFill();
    ofSetColor(getColor(ROLE_BACKGROUND, STATE_NORMAL));
    ofDrawRectangle(0, 0, getWidth(), getHeight());

    ofNoFill();
    ofSetColor(getColor(ROLE_BORDER, STATE_NORMAL));
    ofDrawRectangle(0, 0, getWidth(), getHeight());
}


bool Widget::isPointerOver() const
{
    return _isPointerOver;
}


bool Widget::isPointerDown() const
{
    return !_capturedPointers.empty();
}


void Widget::setAutoCapturePointer(bool autoCapturePointer)
{
    _autoCapturePointer = autoCapturePointer;
}


bool Widget::getAutoCapturePointer() const
{
    return _autoCapturePointer;
}


//void Widget::setDropTarget(bool dropTarget)
//{
//    _isDropTarget = dropTarget;
//}
//
//
//bool Widget::isDropTarget() const
//{
//    return _isDropTarget;
//}
//
//
//void Widget::setDraggable(bool draggable)
//{
//    if (draggable != _isDraggable)
//    {
//        if (draggable)
//        {
//            _isDraggable = true;
//        }
//        else
//        {
//            if (isDragging())
//            {
//                releasePointerCapture(_dragId);
//            }
//
//            _isDraggable = false;
//        }
//    }
//}
//
//
//bool Widget::isDraggable() const
//{
//    return _isDraggable;
//}
//
//
//bool Widget::isDragging() const
//{
//    return _isDragging;
//}


void Widget::_onPointerEvent(DOM::PointerEvent& e)
{
    if (e.type() == PointerEventArgs::POINTER_DOWN)
    {
        // If we are auto capturing pointers, then try.
        if (_autoCapturePointer)
        {
            setPointerCapture(e.pointer().id());

            auto i = _capturedPointers.find(e.pointer().id());

            if (i != _capturedPointers.end())
            {
                i->second.update(this, e);
            }
            else
            {
                // Capture failed.
            }
        }
    }
    else if (e.type() == PointerEventArgs::POINTER_MOVE)
    {
        if (_autoCapturePointer && e.pointer().buttons() > 0)
        {
            auto i = _capturedPointers.find(e.pointer().id());

            if (i != _capturedPointers.end())
            {
                i->second.update(this, e);
            }
        }
    }
    else if (e.type() == PointerEventArgs::POINTER_UP)
    {
        if (_autoCapturePointer)
        {
            auto i = _capturedPointers.find(e.pointer().id());

            if (i != _capturedPointers.end())
            {
                releasePointerCapture(e.pointer().id());
            }
        }

        // TODO: transfer drag to existing captured pointer?
    }
    else if (e.type() == PointerEventArgs::POINTER_OVER)
    {
        _isPointerOver = true;
    }
    else if (e.type() == PointerEventArgs::POINTER_ENTER)
    {
        cout << getId() << " POINTER_ENTER" << endl;
    }
    else if (e.type() == PointerEventArgs::POINTER_OUT)
    {
        _isPointerOver = false;
    }
    else if (e.type() == PointerEventArgs::POINTER_LEAVE)
    {
        cout << getId() << " POINTER_LEAVE" << endl;
    }
}


void Widget::_onPointerCaptureEvent(DOM::PointerCaptureEvent& e)
{
    if (e.type() == PointerEventArgs::GOT_POINTER_CAPTURE)
    {
        if (_capturedPointers.find(e.id()) == _capturedPointers.end())
        {
            _capturedPointers.emplace(std::make_pair(e.id(), DOM::CapturedPointer(e.id())));
        }
        else
        {
            throw DOM::DOMException(DOM::DOMException::INVALID_STATE_ERROR);
        }
    }
    else if (e.type() == PointerEventArgs::LOST_POINTER_CAPTURE)
    {
        auto i = _capturedPointers.find(e.id());

        if (i != _capturedPointers.end())
        {
            _capturedPointers.erase(i);
        }
        else
        {
            throw DOM::DOMException(DOM::DOMException::INVALID_STATE_ERROR);
        }
    }
}


ofColor Widget::getColor(const std::string& role, const std::string& state) const
{
    try
    {
        return getAttribute<ofColor>(role + state, true);
    }
    catch (DOM::DOMException& exc)
    {
        if (STATE_NORMAL == state)
        {
            if (ROLE_FOREGROUND == role)
            {
                return ofColor(255, 255, 0, 80);
            }
            else if(ROLE_BACKGROUND == role)
            {
                return ofColor(255, 60);
            }
            else if (ROLE_BORDER == role)
            {
                return ofColor(255, 100);
            }
            else if (ROLE_TEXT == role)
            {
                return ofColor(255);
            }
        }
        else if (STATE_OVER == state)
        {
            if (ROLE_FOREGROUND == role)
            {
                return ofColor(255, 255, 0, 120);
            }
            else if(ROLE_BACKGROUND == role)
            {
                return ofColor(255, 60);
            }
            else if (ROLE_BORDER == role)
            {
                return ofColor(255, 100);
            }
            else if (ROLE_TEXT == role)
            {
                return ofColor(255);
            }
        }
        else if (STATE_DOWN == state)
        {
            if (ROLE_FOREGROUND == role)
            {
                return ofColor(255, 255, 0, 200);
            }
            else if(ROLE_BACKGROUND == role)
            {
                return ofColor(255, 60);
            }
            else if (ROLE_BORDER == role)
            {
                return ofColor(255, 100);
            }
            else if (ROLE_TEXT == role)
            {
                return ofColor(255);
            }
        }
        else if (STATE_DISABLED == state || STATE_LOCKED == state)
        {
            if (ROLE_FOREGROUND == role)
            {
                return ofColor(127, 40);
            }
            else if(ROLE_BACKGROUND == role)
            {
                return ofColor(127, 20);
            }
            else if (ROLE_BORDER == role)
            {
                return ofColor(127, 50);
            }
            else if (ROLE_TEXT == role)
            {
                return ofColor(127);
            }
        }
        else
        {
            cout << "----" << endl;
        }

        ofLogWarning("Widget::getColor") << "Role: " << role << " State: " << state << " color unknown.";
        return ofColor();
    }
}


void Widget::setColor(const std::string& role, const std::string& state, const ofColor& color)
{
    setAttribute(role + state, color);
}



void Widget::clearColor(const std::string& role, const std::string& state)
{
    clearAttribute(role + state);
}


} } // namespace ofx::MUI
