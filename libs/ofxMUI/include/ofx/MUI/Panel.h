// =============================================================================
//
// Copyright (c) 2009-2013 Christopher Baker <http://christopherbaker.net>
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


class Panel: public Widget
{
public:
    typedef std::unique_ptr<Panel> Ptr;

    Panel(float x, float y, float width, float height): Panel("", x, y, width, height)
    {
    }

    Panel(const std::string& id, float x, float y, float width, float height):
        Widget(id, x, y, width, height)
    {
        addEventListener("pointermove");
        addEventListener("pointerdown");
        addEventListener("pointerup");
    }

    void onPointerMove(DOM::PointerEvent& e) override
    {
        toString(e);

        if (e.pointer().getButtons())
        {
            cout << "\tbuttons pressed! " << ofToBinary(e.pointer().getButtons()) << endl;;
        }

        e.stopPropagation();
        e.preventDefault();
    }

    void onPointerDown(DOM::PointerEvent& e) override
    {
        setPointerCapture(e.pointer().getPointerID());

        toString(e);

        e.stopPropagation();
        e.preventDefault();
    }

    void onPointerUp(DOM::PointerEvent& e) override
    {
        releasePointerCapture(e.pointer().getPointerID());

        toString(e);

        e.stopPropagation();
        e.preventDefault();
    }

    void toString(DOM::PointerEvent& e)
    {
        cout << toString(e.getPhase()) << " " << getId() << " got " << e.type() << " @ " << e.pointer().getPoint() << " id = " << e.pointer().getPointerID() << endl;
    }

    std::string toString(DOM::Event::Phase phase)
    {
        switch(phase)
        {
            case DOM::Event::Phase::NONE: return "NONE";
            case DOM::Event::Phase::CAPTURING_PHASE: return "CAPTURING_PHASE";
            case DOM::Event::Phase::AT_TARGET: return "AT_TARGET";
            case DOM::Event::Phase::BUBBLING_PHASE: return "BUBBLING_PHASE";
        }
        return "UNKNOWN"; 
    }

};


} } // ofx::MUI
