//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier: MIT
//


#include "ofx/MUI/Label.h"


namespace ofx {
namespace MUI {




//Label::Label(const std::string& text): Label("", text)
//{
//}


Label::Label(const std::string& id)://, const std::string& text):
    Widget(id, 0, 0, 0, 0)
{
    setImplicitPointerCapture(false);
//    setText(text);
    setAttribute("text-align", "center");
    setAttribute("vertical-align", "middle");
}


Label::~Label()
{
}


void Label::onDraw() const
{
    ofPushStyle();
    ofFill();
    ofSetColor(getStyles()->getColor(Styles::ROLE_TEXT, Styles::STATE_NORMAL));
    const auto& font = getStyles()->getFont();
    font.drawString(_text, 0, font.getSize());
    ofPopStyle();
}


std::string Label::getText() const
{
    return _text;
}


void Label::setText(const std::string& text)
{
    _text = text;
    
    const auto& font = getStyles()->getFont();
    
    setAttribute("min-width", font.stringWidth(text));
    setAttribute("min-height", font.getSize());
}


std::string Label::displayText() const
{
    return _displayText;
}


//ofAlignVert Label::getVerticalAlignment() const
//{
//    return _alignmentVertical;
//}
//
//
//void Label::setVerticalAlignment(ofAlignVert alignment)
//{
//    _alignmentVertical = alignment;
//}
//
//
//ofAlignHorz Label::getHorizontalAlignment() const
//{
//    return _alignmentHorzontal;
//}
//
//
//void Label::setHorizontalAlignment(ofAlignHorz alignment)
//{
//    _alignmentHorzontal = alignment;
//}


} } // namespace ofx::MUI
