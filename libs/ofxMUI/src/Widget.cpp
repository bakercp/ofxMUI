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
#include "ofGraphics.h"


namespace ofx {
namespace MUI {


Widget::~Widget()
{
}


void Widget::onDraw()
{
    ofSetColor(255, 127);
    ofDrawBitmapString(getId(), 2, 12);

    ofFill();
    ofSetColor(255, 15);
    ofDrawRectangle(0, 0, getSize().x, getSize().y);

    ofNoFill();
    ofSetColor(255, 60);
    ofDrawRectangle(0, 0, getSize().x, getSize().y);
}


void Widget::setEnableDragging(bool draggingEnabled)
{
    if (draggingEnabled != _isDraggingEnabled)
    {
        if (draggingEnabled)
        {
            addEventListener(pointerMove, &Widget::_onPointerEvent, false, std::numeric_limits<int>::min());
            addEventListener(pointerDown, &Widget::_onPointerEvent, false, std::numeric_limits<int>::min());
            addEventListener(pointerUp, &Widget::_onPointerEvent, false, std::numeric_limits<int>::min());
            addEventListener(gotPointerCapture, &Widget::_onPointerCaptureEvent, false, std::numeric_limits<int>::min());
            addEventListener(lostPointerCapture, &Widget::_onPointerCaptureEvent, false, std::numeric_limits<int>::min());
            _isDraggingEnabled = true;
        }
        else
        {
            removeEventListener(pointerMove, &Widget::_onPointerEvent, false, std::numeric_limits<int>::min());
            removeEventListener(pointerDown, &Widget::_onPointerEvent, false, std::numeric_limits<int>::min());
            removeEventListener(pointerUp, &Widget::_onPointerEvent, false, std::numeric_limits<int>::min());
            removeEventListener(gotPointerCapture, &Widget::_onPointerCaptureEvent, false, std::numeric_limits<int>::min());
            removeEventListener(lostPointerCapture, &Widget::_onPointerCaptureEvent, false, std::numeric_limits<int>::min());
            if (isDragging())
            {
                releasePointerCapture(_dragId);
            }
            _isDraggingEnabled = false;
        }
    }
}


bool Widget::isDraggingEnabled() const
{
    return _isDraggingEnabled;
}


bool Widget::isDragging() const
{
    return _isDragging;
}


void Widget::_onPointerEvent(DOM::PointerEvent& e)
{
    if (e.type() == PointerEventArgs::POINTER_DOWN)
    {
        setPointerCapture(e.pointer().id());

        if (isDragging() && _dragId == e.pointer().id())
        {
            _dragOffset = screenToLocal(e.pointer().point());
            _dragStart  = e.pointer().point();
        }
    }
    else if (e.type() == PointerEventArgs::POINTER_MOVE)
    {
        if (isDragging() && _dragId == e.pointer().id())
        {
            DOM::Position p = parent()->screenToLocal(e.pointer().point()) - _dragOffset;

            // Constrain position if child node.
            if (!isRoot() && !_parent->isRoot())
            {
                DOM::Geometry g = parent()->getGeometry();
                DOM::Geometry r = getGeometry();
                p.x = ofClamp(p.x, 0, g.width - r.width);
                p.y = ofClamp(p.y, 0, g.height - r.height);
            }
            setPosition(p);
        }
    }
    else if (e.type() == PointerEventArgs::POINTER_UP)
    {
        if (isDragging() && _dragId == e.pointer().id())
        {
            // Release the current pointer.
            releasePointerCapture(e.pointer().id());

            // TODO: transfer drag to existing captured pointer?
        }
    }
}


void Widget::_onPointerCaptureEvent(DOM::PointerCaptureEvent& e)
{
    if (e.type() == PointerEventArgs::GOT_POINTER_CAPTURE)
    {
        _capturedPointers.insert(e.id());

        if (isDraggingEnabled() && !isDragging())
        {
            _dragId = e.id();
            _isDragging = true;
        }
    }
    else if (e.type() == PointerEventArgs::LOST_POINTER_CAPTURE)
    {
        _capturedPointers.erase(e.id());

        if (isDraggingEnabled() && isDragging())
        {
            _dragId = 0;
            _isDragging = false;
        }
    }
}


} } // namespace ofx::MUI



