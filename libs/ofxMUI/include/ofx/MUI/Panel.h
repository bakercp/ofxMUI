//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once
	

#include "ofx/MUI/Widget.h"


namespace ofx {
namespace MUI {


class Panel: public Widget
{
public:
    Panel(float x, float y, float width, float height):
        Panel("", x, y, width, height)
    {
    }

    Panel(const std::string& id, float x, float y, float width, float height):
        Widget(id, x, y, width, height),
		_resizeable(false)
    {
        setDraggable(true);
    }

    virtual ~Panel()
    {
    }

protected:
	bool _resizeable;

};


} } // ofx::MUI
