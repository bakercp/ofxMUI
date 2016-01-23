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


#include <vector>
#include "ofx/MUI/Types.h"


namespace ofx {
namespace MUI {


class Widget;


/// \brief A base class for laying out Widgets.
class Layout
{
public:
    Layout(Widget* parent);

    /// \brief Destroy the layout.
    virtual ~Layout();

    Widget* parent();

    bool isDoingLayout() const;

    std::vector<Widget*> getWidgets();

    /// \brief Do
    virtual void doLayout() = 0;


protected:
    /// \brief The owning Widget class.
    Widget* _parent = nullptr;

    bool _isDoingLayout = false;

    friend class Widget;
};


class BoxLayout: public Layout
{
public:
    /// If the Orientation::DEFAULT is chosen, the default will be set to
    /// Orientation::HORIZONTAL.
    BoxLayout(Widget* parent, Orientation orientation = Orientation::VERTICAL);

    virtual ~BoxLayout();

    virtual void doLayout() override;

    Orientation orientation() const;

protected:
    Orientation _orientation = Orientation::HORIZONTAL;

};


} } // ofx::MUI
