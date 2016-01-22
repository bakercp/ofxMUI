// =============================================================================
//
// Copyright (c) 2009-2016 Christopher Baker <http://christopherbaker.net>
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
	

#include "ofx/MUI/Types.h"
#include "ofx/MUI/Widget.h"
#include "ofx/MUI/Button.h"


namespace ofx {
namespace MUI {


class ButtonGroup;


class ButtonGroupEventArgs
{
public:


private:
    std::size_t _index;
    Button* _button;
    ButtonGroup* _buttonGroup;

};


class ButtonGroup: public Widget
{
public:
    ButtonGroup(const std::string& id,
                float x = 0,
                float y = 0,
                float width = Button::DEFAULT_WIDTH,
                float height = Button::DEFAULT_HEIGHT,
                bool exclusive = true,
                Orientation orientation = Orientation::HORIZONTAL);

    virtual ~ButtonGroup();

    virtual void onDraw() const override;

//    Button* addButton(const std::string& id);
//
////
//    Button* removeButton(const std::string& id);
//    Button* removeButton(std::size_t index);
//
//    Button* getButton(const std::string& id);
//    Button* getButton(std::size_t index);
//
    template <typename WidgetType, typename... Args>
    WidgetType* addButton(Args&&... args)
    {
        static_assert(std::is_base_of<Button, WidgetType>::value, "WidgetType not derived from Button");
        return addChild(std::make_unique<WidgetType>(std::forward<Args>(args)...));
    }

//    ofEvent<int> onValueChanged;

protected:
    DOM::DOMEvent<ButtonEventArgs> onButtonEvent;
    void _onButtonEvent(ButtonEventArgs& e);

    /// \brief If true, only one Button can be checked at a time.
    bool _exclusive = true;

    /// \brief The ButtonGroup orientation.
    Orientation _orientation = Orientation::HORIZONTAL;

};


} } // ofx::MUI
