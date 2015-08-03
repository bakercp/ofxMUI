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
	

#include "ofx/MUI/Widget.h"


namespace ofx {
namespace MUI {


/// \brief Slider
///
///
///
/// \tparam Type the data type represented by the Slider.
template<typename Type>
class Slider: public Widget
{
public:
    /// \brief The orientation of the Slider.
    enum class Orientation
    {
        /// \brief Sets the Orientation based on the aspect ratio.
        AUTO,
        /// \brief Locks the Orientation to landscape.
        LANDSCAPE,
        /// \brief Locks the Orientation to portrait.
        PORTRAIT
    };

    /// \brief The drag mode of the Slider.
    ///
    /// The drag mode determins how the Pointer interacts with the slider.
    /// When in Mode::ABSOLUTE, the slider will immediately jump to the location
    /// of the pointer down.  In Mode::RELATIVE, the pointer will be offset
    /// relative to the movemovement of the pointer's original pointer down
    /// location.
    enum class Mode
    {
        /// \brief Sets the position by the absolute position of the dragged pointer.
        ABSOLUTE,
        /// \brief Sets the position by the relative offset of the dragged pointer.
        RELATIVE
    };

    Slider(float x,
           float y,
           float width,
           float height);

    Slider(const std::string& id,
           float x,
           float y,
           float width,
           float height);

    Slider(const std::string& id,
           float x,
           float y,
           float width,
           float height,
           Orientation orientation,
           Mode mode);

    /// \brief Destroy the Slider.
    virtual ~Slider();

    virtual void onDraw() override;

    Mode getMode() const;
    void setMode(Mode mode);

    Orientation getOrientation() const;
    void setOrientation(Orientation orientation);

    /// \brief Determine if the slider direction inverted.
    ///
    /// By default the Slider direction is mapped from 0 (left) to 1 (right)
    /// in Orientation::LANDSCAPE mode and from 0 (bottom) to 1 (top) in
    /// Orientation::PORTRAIT mode.  Inverted Sliders map in the opposite way.
    ///
    /// \returns true if the Slider is inverted.
    bool isInverted() const;

    /// \brief Invert the Slider direction.
    ///
    /// By default the Slider direction is mapped from 0 (left) to 1 (right)
    /// in Orientation::LANDSCAPE mode and from 0 (bottom) to 1 (top) in
    /// Orientation::PORTRAIT mode.  Inverted Sliders map in the opposite way.
    ///
    /// \param inverted true if the Slider direction should be inverted.
    void setInverted(bool inverted);

    void onPointerEvent(DOM::PointerEvent& e);
    void onPointerCaptureEvent(DOM::PointerCaptureEvent& e);

    virtual void onValueChanged(const Type& value);

    ofParameter<Type> value;

protected:
    /// \brief Get the effective orientation.
    /// \returns only Orientation::LANDSCAPE or Orientation::HORIZONTAL.
    Orientation getEffectiveOrientation() const;

    /// \brief Get the active axis index.
    /// \returns 0 for X or 1 for Y.
    std::size_t getActiveAxisIndex() const;

    /// \brief The Slider orientation.
    Orientation _orientation = Orientation::HORIZONTAL;

    /// \brief The drag mode.
    Mode _mode = Mode::RELATIVE;

    /// \brief The "primary" pointer id.
    ///
    /// This is the first pointer that was captured when dragging.
    std::size_t _primaryPointerId = 0;

//    /// \brief The start position for the primary pointer.
//    Point _primaryPointerStart;
//
    /// \brief The start value of the value itself.
    ///
    /// Used when computing offsets in Mode::RELATIVE.
    Type _valueOffset = 0;

    /// \brief Is the Slider direction inverted.
    bool _isInverted = false;

    /// \brief A callback for the Slider's value.
    /// \param value The the updated value.
    void _onValueChanged(Type& value);

    /// \brief A callback for any resize events.
    /// \param value The DOM::ResizeEvent arguments.
    void _onResize(DOM::ResizeEvent& value);

private:
    /// \brief False when the _effectiveOrientation needs to be recalculated.
    mutable bool _effectiveOrientationInvalid = true;

    /// \brief The effective orientation used when the orientation mode is AUTO.
    mutable Orientation _effectiveOrientation;

};


template<typename Type>
Slider<Type>::Slider(float x,
                     float y,
                     float width,
                     float height):
    Slider<Type>::Slider("",
                         x,
                         y,
                         width,
                         height)
{
}


template<typename Type>
Slider<Type>::Slider(const std::string& id,
                     float x,
                     float y,
                     float width,
                     float height):
    Slider<Type>::Slider(id,
                         x,
                         y,
                         width,
                         height,
                         Orientation::AUTO,
                         Mode::ABSOLUTE)
{
}


template<typename Type>
Slider<Type>::Slider(const std::string& id,
                     float x,
                     float y,
                     float width,
                     float height,
                     Orientation orientation,
                     Mode mode):
    Widget(id, x, y, width, height),
    value(id, 0, 0, 1),
    _orientation(orientation),
    _mode(mode)
{
    value.addListener(this, &Slider<Type>::_onValueChanged, std::numeric_limits<int>::min());
    addEventListener(pointerDown, &Slider<Type>::onPointerEvent);
    addEventListener(pointerMove, &Slider<Type>::onPointerEvent);
    addEventListener(gotPointerCapture, &Slider<Type>::onPointerCaptureEvent);
    addEventListener(lostPointerCapture, &Slider<Type>::onPointerCaptureEvent);

    ofAddListener(resize, this, &Slider<Type>::_onResize, std::numeric_limits<int>::min());
}


template<typename Type>
Slider<Type>::~Slider()
{
    value.removeListener(this, &Slider<Type>::_onValueChanged, std::numeric_limits<int>::min());
    removeEventListener(pointerDown, &Slider<Type>::onPointerEvent);
    removeEventListener(pointerMove, &Slider<Type>::onPointerEvent);
    removeEventListener(gotPointerCapture, &Slider<Type>::onPointerCaptureEvent);
    removeEventListener(lostPointerCapture, &Slider<Type>::onPointerCaptureEvent);

    ofRemoveListener(resize, this, &Slider<Type>::_onResize, std::numeric_limits<int>::min());

}


template<typename Type>
void Slider<Type>::onPointerEvent(DOM::PointerEvent& e)
{
    if (e.pointer().id() == _primaryPointerId)
    {
        if (PointerEventArgs::POINTER_DOWN == e.type() ||
            PointerEventArgs::POINTER_MOVE == e.type())
        {
            // Convert to integer to avoid warnings w/ Point.
            std::size_t axisIndex = getActiveAxisIndex();

            // Local position.
            float position = screenToLocal(e.pointer().point())[static_cast<int>(axisIndex)];

            Type valueMin = value.getMin();
            Type valueMax = value.getMax();

            if (_isInverted)
            {
                std::swap(valueMin, valueMax);
            }

            float sliderMin = 0;
            float sliderMax = getSize()[static_cast<int>(axisIndex)];

            if (Orientation::PORTRAIT == getEffectiveOrientation())
            {
                std::swap(sliderMin, sliderMax);
            }

            Type _value = ofMap(position,
                                sliderMin,
                                sliderMax,
                                valueMin,
                                valueMax);

            if (Mode::RELATIVE == _mode)
            {
                if (PointerEventArgs::POINTER_DOWN == e.type())
                {
                    // Find the difference between the current value
                    // and the value underneath the pointer.  This is
                    // the value offset.
                    _valueOffset = (value - _value);
                    return;
                }
                else
                {
                    // Add the value offset to the calculated value based
                    // on the poiter position.
                    _value += _valueOffset;
                }
            }

            value = ofClamp(_value, valueMin, valueMax);
        }
    }
}


template<typename Type>
void Slider<Type>::onPointerCaptureEvent(DOM::PointerCaptureEvent& e)
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



template<typename Type>
void Slider<Type>::onDraw()
{
//    ofNoFill();
//    ofSetColor(255, 127);
//    ofDrawRectRounded(getGeometry(), 5);

    ofFill();

    if (isPointerDown())
    {
        ofSetColor(getColor(ROLE_BACKGROUND, STATE_DOWN));
    }
    else if (isPointerOver())
    {
        ofSetColor(getColor(ROLE_BACKGROUND, STATE_OVER));
    }
    else
    {
        ofSetColor(getColor(ROLE_BACKGROUND, STATE_NORMAL));
    }

    ofDrawRectRounded(0, 0, getWidth(), getHeight(), 3);

    ofNoFill();

    ofSetColor(getColor(ROLE_BORDER, STATE_NORMAL));
    ofDrawRectRounded(0, 0, getWidth(), getHeight(), 3);

    Orientation orientation = _orientation;

    if (Orientation::AUTO == orientation)
    {
        orientation = (getWidth() > getHeight()) ? Orientation::LANDSCAPE : Orientation::PORTRAIT;
    }

    ofFill();

    if (isPointerDown())
    {
        ofSetColor(getColor(ROLE_FOREGROUND, STATE_DOWN));
    }
    else if (isPointerOver())
    {
        ofSetColor(getColor(ROLE_FOREGROUND, STATE_OVER));
    }
    else
    {
        ofSetColor(getColor(ROLE_FOREGROUND, STATE_NORMAL));
    }

    Type min = value.getMin();
    Type max = value.getMax();

    if (_isInverted)
    {
        std::swap(min, max);
    }

    if (Orientation::LANDSCAPE == orientation)
    {
        float x = ofMap(value, min, max, 0, getWidth());
        ofDrawRectRounded(0, 0, x, getHeight(), 3);
    }
    else
    {
        float y = ofMap(value, min, max, getHeight(), 0);
        ofDrawRectRounded(0, y, getWidth(), getHeight() - y, 3);
    }
}


template<typename Type>
typename Slider<Type>::Mode Slider<Type>::getMode() const
{
    return _mode;
}


template<typename Type>
void Slider<Type>::setMode(Mode mode)
{
    _mode = mode;
}


template<typename Type>
typename Slider<Type>::Orientation Slider<Type>::getOrientation() const
{
    return _orientation;
}


template<typename Type>
void Slider<Type>::setOrientation(Orientation orientation)
{
    if (orientation == Orientation::AUTO &&
       _orientation != Orientation::AUTO)
    {
        _effectiveOrientationInvalid = true;
    }

    _orientation = orientation;
}


template<typename Type>
bool Slider<Type>::isInverted() const
{
    return _isInverted;
}


template<typename Type>
void Slider<Type>::setInverted(bool inverted)
{
    _isInverted = inverted;
}


template<typename Type>
typename Slider<Type>::Orientation Slider<Type>::getEffectiveOrientation() const
{
    if (Orientation::AUTO == _orientation)
    {
        if (_effectiveOrientationInvalid)
        {
            _effectiveOrientation = getWidth() > getHeight() ? Orientation::LANDSCAPE : Orientation::PORTRAIT;
            _effectiveOrientationInvalid = false;
        }

        return _effectiveOrientation;
    }
    else
    {
        return _orientation;
    }
}


template<typename Type>
std::size_t Slider<Type>::getActiveAxisIndex() const
{
    return (getEffectiveOrientation() == Orientation::LANDSCAPE) ? 0 : 1;
}

template<typename Type>
void Slider<Type>::onValueChanged(const Type& value)
{
}


template<typename Type>
void Slider<Type>::_onValueChanged(Type& value)
{
    onValueChanged(value);
}


template<typename Type>
void Slider<Type>::_onResize(DOM::ResizeEvent& value)
{
    _effectiveOrientationInvalid = true;
}


typedef Slider<float> FloatSlider;


} } // ofx::MUI
