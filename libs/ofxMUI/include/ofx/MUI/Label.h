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
	

#include "ofx/MUI/Widget.h"
#include "ofx/MUI/Styles.h"


namespace ofx {
namespace MUI {


/// \brief A widget label
class Label: public Widget
{
public:
    enum
    {
        NSLineBreakByWordWrapping = 0,
        NSLineBreakByCharWrapping,
        NSLineBreakByClipping,
        NSLineBreakByTruncatingHead,
        NSLineBreakByTruncatingTail,
        NSLineBreakByTruncatingMiddle
    };
//    typedef NSUInteger NSLineBreakMode


//    enum ofAlignVert {
//        OF_ALIGN_VERT_IGNORE   = 0x0000,
//        OF_ALIGN_VERT_TOP      = 0x0010,
//        OF_ALIGN_VERT_BOTTOM   = 0x0020,
//        OF_ALIGN_VERT_CENTER   = 0x0040,
//    };
//
//    enum ofAlignHorz {
//        OF_ALIGN_HORZ_IGNORE   = 0x0000,
//        OF_ALIGN_HORZ_LEFT     = 0x0001,
//        OF_ALIGN_HORZ_RIGHT    = 0x0002,
//        OF_ALIGN_HORZ_CENTER   = 0x0004,
//    };

    virtual void onDraw() const override;

    /// \returns the Label text.
    std::string getText() const;

    /// \brief Set the Label text.
    /// \param text The text to set.
    void setText(const std::string& text);

    /// \returns the displayed text.
    std::string displayText() const;

    /// \returns the vertical alignment of the Label text.
    ofAlignVert getVerticalAlignment() const;

    /// \brief Set the vertical alignment of the Label text.
    /// \param alignment The alignment to set.
    void setVerticalAlignment(ofAlignVert alignment);

    /// \returns the horizontal alignment of the Label text.
    ofAlignHorz getHorizontalAlignment() const;

    /// \brief Set the horizontal alignment of the Label text.
    /// \param alignment The alignment to set.
    void setHorizontalAlignment(ofAlignHorz alignment);

private:
    /// \brief The contents of the label.
    ///
    /// If empty, will default to the DOM::Element's id.
    std::string _text;

    /// \brief The text to be displayed.
    ///
    /// The display text is what will actually be displayed. It may be subject
    /// to content replacement, truncation, etc.
    mutable std::string _displayText;

    /// \brief The label's vertical edge to align to.
    ///
    /// If OF_ALIGN_VERT_IGNORE, OF_ALIGN_VERT_CENTER will be used.
    ofAlignVert _alignmentVertical = OF_ALIGN_VERT_CENTER;

    /// \brief The label's horizontal edge to align to.
    ///
    /// If OF_ALIGN_HORZ_IGNORE, OF_ALIGN_HORZ_LEFT will be used.
    ofAlignHorz _alignmentHorzontal = OF_ALIGN_HORZ_LEFT;

};


} } // ofx::MUI
