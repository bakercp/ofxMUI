//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


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


void Widget::onDraw() const
{
    ofFill();

    auto styles = getStyles();

    if (isPointerDown())
    {
        ofSetColor(styles->getColor(Styles::ROLE_BACKGROUND, Styles::STATE_DOWN));
    }
    else if (isPointerOver())
    {
        ofSetColor(styles->getColor(Styles::ROLE_BACKGROUND, Styles::STATE_OVER));
    }
    else
    {
        ofSetColor(styles->getColor(Styles::ROLE_BACKGROUND, Styles::STATE_NORMAL));
    }

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


void Widget::_onPointerEvent(DOM::PointerUIEventArgs& e)
{
	if (e.type() == PointerEventArgs::POINTER_DOWN)
	{
	}
	else if (e.type() == PointerEventArgs::POINTER_MOVE)
	{
		if (_isDragging)
		{
			if (!capturedPointers().empty())
			{
				const DOM::CapturedPointer& pointer = *capturedPointers().begin();
				setPosition(screenToParent(pointer.position() - pointer.offset()));
			}
			else
			{
				ofLogError("Widget::_onPointerEvent") << "No captured pointers to drag with.";
			}

		}
	}
	else if (e.type() == PointerEventArgs::POINTER_OVER)
	{
		_isPointerOver = true;
	}
	else if (e.type() == PointerEventArgs::POINTER_OUT)
	{
		_isPointerOver = false;
	}
    else
    {
        // unhandled.
    }
}


void Widget::_onPointerCaptureEvent(DOM::PointerCaptureUIEventArgs& e)
{
	if (e.type() == PointerEventArgs::GOT_POINTER_CAPTURE)
	{
		if (_moveToFrontOnCapture)
		{
			moveToFront();
		}

		_isDragging = _isDraggable;

	}
	else if (e.type() == PointerEventArgs::LOST_POINTER_CAPTURE)
	{
		_isDragging = false;
	}
}


} } // namespace ofx::MUI
