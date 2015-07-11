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


#pragma once
	

#include "ofx/DOM/Element.h"
#include "ofx/DOM/Events.h"


namespace ofx {
namespace MUI {


class Widget: public DOM::Element
{
public:
    using DOM::Element::Element;

    virtual ~Widget();

    virtual void onDraw();


    /// \brief Enable dragging for this Widget.
    /// \param drag True if drag should be enabled.
    void setEnableDragging(bool draggingEnabled);

    /// \brief Determine if dragging is enabled for this Widget.
    /// \returns true iff the dragging is enabled.
    bool isDraggingEnabled() const;

    /// \brief Determine if this Widget is being dragged.
    /// \returns true if this Widget is being dragged.
    bool isDragging() const;

    /// \brief Default callback for built-in events, including dragging.
    void _onPointerEvent(DOM::PointerEvent& e);

    /// \brief Default callback for built-in events, including dragging.
    void _onPointerCaptureEvent(DOM::PointerCaptureEvent& e);

protected:
    /// \brief True iff the Widget is configured to be dragged.
    bool _isDraggingEnabled = false;

    /// \brief True iff the widget is currently being dragged.
    bool _isDragging = false;

    /// \brief The id of the pointer that is currently dragging.
    std::size_t _dragId = 0;

    /// \brief The drag starting point (parent's local coordinates).
    Point _dragStart;

    /// \brief The local starting point (local coordinates).
    Point _dragOffset;

    /// \brief The velocity of the drag in points / millisecond.
    Point _dragVelocity;

    /// \brief The last drag update time in milliseconds.
    uint64_t _lastDragUpdate;

    
};


} } // ofx::MUI
