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


#include "ofx/MUI/ButtonGroup.h"


namespace ofx {
namespace MUI {

ButtonGroup::ButtonGroup(const std::string& id,
                         DOM::Orientation orientation):
    ButtonGroup(id, 0, 0, 0, 0, orientation)
{
}


ButtonGroup::ButtonGroup(const std::string& id,
                         float x,
                         float y,
                         float width,
                         float height,
                         DOM::Orientation orientation):
    Widget(id, x, y, width, height),
    _orientation(orientation)
{
    createLayout<DOM::BoxLayout>(this, orientation);

    registerEventType(ButtonEventArgs::BUTTON_PRESSED, &onButtonEvent);
    registerEventType(ButtonEventArgs::BUTTON_DOWN, &onButtonEvent);
    registerEventType(ButtonEventArgs::BUTTON_UP, &onButtonEvent);

    addEventListener(onButtonEvent,
                     &ButtonGroup::_onButtonEvent,
                     true,
                     std::numeric_limits<int>::min());


}


ButtonGroup::~ButtonGroup()
{
    removeEventListener(onButtonEvent,
                        &ButtonGroup::_onButtonEvent,
                        true,
                        std::numeric_limits<int>::min());

}


void ButtonGroup::onDraw() const
{
    ofSetColor(255, 127);
    ofFill();
    ofDrawRectangle(0, 0, getWidth(), getHeight());
}


void ButtonGroup::_onButtonEvent(ButtonEventArgs& e)
{
//    if (e.type() == ButtonEventArgs::BUTTON_DOWN)
//    {
//        if (_exclusive)
//        {
//            for (auto& child : _children)
//            {
//                Button* button = dynamic_cast<Button*>(child.get());
//
//                if (button && button != e.source())
//                {
//                    button->_value.setWithoutEventNotifications(0);
//                }
//                else
//                {
////                    button->_value.setWithoutEventNotifications(1);
//                }
//            }
//        }
//    }
}


    
//Button* ButtonGroup::addButton(const std::string& name)
//{
//    return nullptr;
//}


} } // namespace ofx::MUI



