//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier: MIT
//


#pragma once
	

#include "ofx/MUI/Widget.h"


namespace ofx {
namespace MUI {


class XYSlider: public Widget
{
public:
    XYSlider(const std::string& id = "",
          float x = 0,
          float y = 0,
          float width = 0,
          float height = 0);

    /// \brief Destroy the XYSlider.
    virtual ~XYSlider();

    // void onDraw() const override;
    /// \brief The parameter to watch.
    ofParameter<glm::vec2> _value;

    /// \brief A callback for the parameter change.
    ofEvent<glm::vec2> valueChanged;

    /// \brief Pointer event callback.
    /// \param evt The event data.
    void onPointerEvent(DOM::PointerUIEventArgs& e);

    /// \brief Pointer event callback.
    /// \param evt The event data.
    void onPointerCaptureEvent(DOM::PointerCaptureUIEventArgs& e);
    
    void onDraw() const override;
    
protected:
    /// \brief A callback for any resize events.
    /// \param value The DOM::ResizeEvent arguments.
    void _onResize(DOM::ResizeEventArgs&);

    /// \brief A callback for the ParameterWidget's value.
    /// \param value The the updated value.
    void _onValueChanged(const void* sender, glm::vec2& value);

    /// \brief The "primary" pointer id.
    ///
    /// This is the first pointer that was captured when dragging.
    std::size_t _primaryPointerId = 0;

    /// \brief True if the Panel can be resized.
    bool _resizeable = false;

};


} } // ofx::MUI
