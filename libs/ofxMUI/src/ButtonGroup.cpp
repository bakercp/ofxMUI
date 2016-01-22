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
                         float x,
                         float y,
                         float width,
                         float height,
                         bool exclusive,
                         Orientation orientation):
    Widget(id, x, y, width, height),
    _exclusive(exclusive),
    _orientation(orientation)
{
    createLayout<BoxLayout>(this, orientation);
//    registerEventType(ButtonEventArgs::BUTTON_PRESSED, &onButtonPressed);
//
//    this->addEventListener(onButtonPressed, &ButtonGroup::_onButtonPressed, false, std::numeric_limits<int>::min());
}


ButtonGroup::~ButtonGroup()
{
}


void ButtonGroup::onDraw() const
{
    ofSetColor(255, 127);
    ofFill();
    ofDrawRectangle(0, 0, getWidth(), getHeight());
}


    //
//Button* ButtonGroup::addButton(const std::string& name)
//{
//    return nullptr;
//}
//

} } // namespace ofx::MUI



