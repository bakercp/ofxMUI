//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


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

    /// \brief Set the elevation of the widget.
    /// \param elevation The elevation in pixels.
    void setElevation(float elevation);

    /// \returns the elevation in pixels.
    float getElevation() const;
    
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
	void _onPointerEvent(DOM::PointerUIEventArgs& e);

	/// \brief Default callback for built-in events, including dragging.
	void _onPointerCaptureEvent(DOM::PointerCaptureUIEventArgs& e);

    /// \brief True iff the Widget is a target for dragged Widgets.
    bool _isDropTarget = false;

    /// \brief True iff the Widget is configured to be dragged.
    bool _isDraggable = false;

    /// \brief True iff the widget is currently being dragged.
    bool _isDragging = false;

    /// \brief True iff the pointer is over the widget.
    bool _isPointerOver = false;

    /// \brief True if the element should move to the fron upon pointer capture.
    bool _moveToFrontOnCapture = true;

    /// \brief The elevation of the widget in pixels.
    float _elevation = 0;
    
    /// \brief A map of callbacks key-down events.
    std::map<uint64_t, std::function<void(DOM::KeyboardUIEventArgs& event)>> _keyboardListeners;

private:
	/// \brief The shared Styles.
    mutable std::shared_ptr<Styles> _styles = nullptr;

};


} } // ofx::MUI
