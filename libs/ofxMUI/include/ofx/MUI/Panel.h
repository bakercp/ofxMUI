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
        addEventListener(pointerMove, &Panel::onPointerMove);
        addEventListener(pointerDown, &Panel::onPointerDown);
        addEventListener(pointerUp, &Panel::onPointerUp);

        addEventListener(gotPointerCapture, &Panel::onGotPointerCapture);
        addEventListener(lostPointerCapture, &Panel::onLostPointerCapture);
    }

        void onPointerOver(DOM::PointerEvent& e)
        {
            if (dragging == e.pointer().id())
            {
                DOM::Position p = parent()->screenToLocal(e.pointer().point()) - dragOffset;
                DOM::Geometry g = parent()->getGeometry();
                DOM::Geometry r = getGeometry();
                p.x = ofClamp(p.x, 0, g.width - r.width);
                p.y = ofClamp(p.y, 0, g.height - r.height);
    
                setPosition(p);
            }
        }


    void onGotPointerCapture(DOM::PointerCaptureEvent& e)
    {
        if (e.target() == this)
        {
            if (dragging == 0)
            {
                dragging = e.id();
            }
        }
    }

    void onLostPointerCapture(DOM::PointerCaptureEvent& e)
    {
        if (e.target() == this)
        {
            if (e.id() == dragging)
            {
                dragging = 0;
            }
        }
    }

    void onPointerMove(DOM::PointerEvent& e)
    {
        if (dragging == e.pointer().id())
        {
            DOM::Position p = parent()->screenToLocal(e.pointer().point()) - dragOffset;
            DOM::Geometry g = parent()->getGeometry();
            DOM::Geometry r = getGeometry();
            p.x = ofClamp(p.x, 0, g.width - r.width);
            p.y = ofClamp(p.y, 0, g.height - r.height);

            setPosition(p);
        }
    }

    void onPointerDown(DOM::PointerEvent& e)
    {
        setPointerCapture(e.pointer().id());

        if (dragging == e.pointer().id())
        {
            dragOffset = screenToLocal(e.pointer().point());
            dragStart = e.pointer().point();
        }

    }

    void onPointerUp(DOM::PointerEvent& e) 
    {
//        toString(e);

//        e.stopPropagation();
//        e.preventDefault();
    }

    void toString(DOM::PointerEvent& e)
    {
        std::cout << toString(e.getPhase()) << " " << getId() << " got " << e.type() << " @ " << e.pointer().point() << " id = " << e.pointer().id() << " " << e.pointer().deviceType() << std::endl;
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


    std::size_t dragging = 0;
    Point dragStart;
    Point dragOffset;


};


} } // ofx::MUI
