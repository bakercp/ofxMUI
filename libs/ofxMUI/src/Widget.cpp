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
#include "ofx/MUI/MUI.h"
#include "ofx/MUI/Styles.h"


namespace ofx {
namespace MUI {


Widget::Widget(float x, float y, float width, float height):
    Widget("", x, y, width, height)
{
}


Widget::Widget(const std::string& id, float x, float y, float width, float height):
    DOM::Element(id, x, y, width, height),
	_isDropTarget(false),
	_isDraggable(false),
	_isDragging(false),
	_isPointerOver(false)
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

	setImplicitPointerCapture(true);
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
	std::stringstream ss;

	ss << getId() << std::endl;

	if (!capturedPointers().empty())
	{
		ss << "CP: " << ofToString(capturedPointers()) << std::endl;
	}

	ofSetColor(getStyles()->getColor(Styles::ROLE_TEXT, Styles::STATE_NORMAL));
    ofDrawBitmapString(ss.str(), 2, 12);

    ofFill();
    ofSetColor(getStyles()->getColor(Styles::ROLE_BACKGROUND, Styles::STATE_NORMAL));
    ofDrawRectangle(0, 0, getWidth(), getHeight());

    ofNoFill();
    ofSetColor(getStyles()->getColor(Styles::ROLE_BORDER, Styles::STATE_NORMAL));
    ofDrawRectangle(0, 0, getWidth(), getHeight());

}


bool Widget::isPointerOver() const
{
    return _isPointerOver;
}


bool Widget::isPointerDown() const
{
	return !capturedPointers().empty();
}


void Widget::setDropTarget(bool dropTarget)
{
    _isDropTarget = dropTarget;
}


bool Widget::isDropTarget() const
{
    return _isDropTarget;
}


void Widget::setDraggable(bool draggable)
{
	_isDraggable = draggable;
}


bool Widget::isDraggable() const
{
    return _isDraggable;
}


bool Widget::isDragging() const
{
    return _isDragging;
}


void Widget::_onPointerEvent(DOM::PointerEvent& e)
{
    if (e.type() == PointerEventArgs::POINTER_DOWN)
    {
    }
    else if (e.type() == PointerEventArgs::POINTER_MOVE)
    {
    }
    else if (e.type() == PointerEventArgs::POINTER_OVER)
    {
        _isPointerOver = true;
    }
    else if (e.type() == PointerEventArgs::POINTER_OUT)
    {
        _isPointerOver = false;
    }
}


void Widget::_onPointerCaptureEvent(DOM::PointerCaptureEvent& e)
{
	_isDragging = e.type() == PointerEventArgs::GOT_POINTER_CAPTURE && _isDraggable;
}


std::shared_ptr<Styles> Widget::getStyles() const
{
	if (_styles == nullptr)
	{
		const MUI* mui = dynamic_cast<const MUI*>(document());

		if (mui != nullptr)
		{
			_styles = mui->getDocumentStyles();
		}
		else
		{
			ofLogWarning("Widget::getStyles") << "No root document, using default styles.";
			_styles = std::make_shared<Styles>();
		}
	}

	return _styles;
}


void Widget::setStyles(std::shared_ptr<Styles> styles)
{
	_styles = styles;
}



} } // namespace ofx::MUI
