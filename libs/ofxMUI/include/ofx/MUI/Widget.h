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
	

#include "ofParameter.h"
#include "ofGraphics.h"
#include "ofx/DOM/Element.h"
#include "ofx/DOM/Events.h"


namespace ofx {
namespace MUI {


class Styles;


/// \brief A Widget is the base class for all MUI interactive elements.
class Widget: public DOM::Element
{
public:
    Widget(float x, float y, float width, float height);

    Widget(const std::string& id, float x, float y, float width, float height);

    /// \brief Destroy this Widget.
    virtual ~Widget();

    virtual void onDraw() const override;

	/// \returns true if the pointer is over this Widget.
    bool isPointerOver() const;

	/// \returns true if the pointer is down on this Widget.
    bool isPointerDown() const;

    /// \brief Enable or disable the Widget as a drop target.
    /// \param dropTarget True iff this Widget is a drop target.
    void setDropTarget(bool dropTarget);

    /// \brief Determine if this Widget is a drop target.
    /// \returns true iff this Widget is a drop target.
    bool isDropTarget() const;

    /// \brief Set draggability for this Widget.
    /// \param draggable True iff draggability is enabled.
    void setDraggable(bool draggable);

    /// \brief Determine if draggability is enabled for this Widget.
    /// \returns true iff the draggability is enabled.
    bool isDraggable() const;

    /// \brief Determine if this Widget is being dragged.
    /// \returns true if this Widget is being dragged.
    bool isDragging() const;

	/// \brief Get the Styles for this Widget.
	/// \returns the Widget's styles.
	std::shared_ptr<Styles> getStyles() const;

	/// \brief Set the Styles for this Widget.
	///
	/// If the style is set to nullptr, it will automatically adopt the root
	/// document style.
	///
	/// \param style The style to set.
	void setStyles(std::shared_ptr<Styles> styles);

protected:
	/// \brief Default callback for built-in events, including dragging.
	void _onPointerEvent(DOM::PointerEvent& e);

	/// \brief Default callback for built-in events, including dragging.
	void _onPointerCaptureEvent(DOM::PointerCaptureEvent& e);

    /// \brief True iff the Widget is a target for dragged Widgets.
    bool _isDropTarget;

    /// \brief True iff the Widget is configured to be dragged.
    bool _isDraggable;

    /// \brief True iff the widget is currently being dragged.
    bool _isDragging;

    /// \brief True iff the pointer is over the widget.
    bool _isPointerOver;

    /// \brief True if the element should move to the fron upon pointer capture.
	bool _moveToFrontOnCapture;

private:
	/// \brief The shared Styles.
	mutable std::shared_ptr<Styles> _styles;

};


} } // ofx::MUI
