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


#include "ofx/MUI/Bang.h"
#include "ofx/MUI/Styles.h"


namespace ofx {
namespace MUI {


Bang::Bang(float x, float y, float width, float height):
    Bang("", x, y, width, height)
{
}


Bang::Bang(const std::string& id, float x, float y, float width, float height):
    Widget(id, x, y, width, height)
{
    addEventListener(pointerDown, &Bang::_onPointerEvent, false, std::numeric_limits<int>::min());
    addEventListener(pointerUp, &Bang::_onPointerEvent, false, std::numeric_limits<int>::min());
}


Bang::~Bang()
{
    removeEventListener(pointerDown, &Bang::_onPointerEvent, false, std::numeric_limits<int>::min());
    removeEventListener(pointerUp, &Bang::_onPointerEvent, false, std::numeric_limits<int>::min());
}


void Bang::onDraw()
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

    ofDrawRectRounded(0, 0, getWidth(), getHeight(), 3);

    ofNoFill();
    ofSetColor(getStyles()->getColor(Styles::ROLE_BORDER, Styles::STATE_NORMAL));
    ofDrawRectRounded(0, 0, getWidth(), getHeight(), 3);

}


void Bang::_onPointerEvent(DOM::PointerEvent& e)
{
    if (e.type() == PointerEventArgs::POINTER_DOWN)
    {
        if (!_setValueOnRelease)
        {
            bool t = true;
            ofNotifyEvent(bang, t, this);
        }
    }
    else if (e.type() == PointerEventArgs::POINTER_UP)
    {
        if (_setValueOnRelease && _requireReleaseOver && hitTest(screenToLocal(e.pointer().point())))
        {
            bool t = false;
            ofNotifyEvent(bang, t, this);
        }
    }
}


} } // namespace ofx::MUI



