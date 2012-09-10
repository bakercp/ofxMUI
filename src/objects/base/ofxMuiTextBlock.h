/*==============================================================================
 
 Copyright (c) 2009-2012 Christopher Baker <http://christopherbaker.net>
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 
 ==============================================================================*/

#pragma once

#include "ofMain.h"
#include "ofxMuiConstants.h"
#include "ofxMuiTextUtils.h"
#include "ofxMuiTrueTypeFont.h"
#include <Poco/RegularExpression.h>
#include <Poco/StringTokenizer.h>
#include <Poco/String.h>
#include <Poco/Ascii.h>

using Poco::toUpper;
using Poco::toLower;
using Poco::toUpperInPlace;
using Poco::toLowerInPlace;
using Poco::StringTokenizer;
using Poco::cat;
using Poco::RegularExpression;

class ofxMuiTextBlock {
public:
    
    ofxMuiTextBlock(ofxMuiTrueTypeFont* font);
    ofxMuiTextBlock(ofxMuiTrueTypeFont* font, const string& _text);
    ofxMuiTextBlock(ofxMuiTrueTypeFont* font, const string& _text, float _width);
    ofxMuiTextBlock(ofxMuiTrueTypeFont* font, const string& _text, float _width, float _height);
    
    virtual ~ofxMuiTextBlock();

    // drawing and updating
    void update();
    virtual void draw(float x, float y);
    virtual void draw();
    
    // content
    void setText(const string& text);
    string getText() const;
    
    void insert(const string& s, int position);
    void append(const string& s);
    void prepend(const string& s);
    
    string getDisplayText() const;
    string getDisplayTextLine(int lineNumber) const;
    vector<string> getDisplayTextLines() const;
    
    // style
    
    void setTextColor(const ofColor& _cText);
    ofColor getTextColor() const;

    ofxMuiTrueTypeFont* getFont();
    void setFont(ofxMuiTrueTypeFont* _font);
    
    void setCapsStyle(const ofxMuiCapsMode& _capsStyle);
    ofxMuiCapsMode getCapsStyle() const;

    void setLineBreakMode(const ofxMuiLineBreakMode& _lineBreakMode);
    ofxMuiLineBreakMode getLineBreakMode() const;
    
    void setLineTruncationMode(const ofxMuiLineTruncationMode& _lineTruncationMode);
    ofxMuiLineTruncationMode getLineTruncationMode() const;
    
    void setTruncationString(const string& _truncationString);
    string getTruncationString() const;

    void setAlignHorz(const ofAlignHorz& _hAlign);
    void setAlignVert(const ofAlignVert& _vAlign);
    
    ofAlignHorz getAlignHorz() const;
    ofAlignVert getAlignVert() const;

    void setOrientation(const ofOrientation& _orientation);
    ofOrientation getOrientation() const;
    
    
    bool allowMultipleLines() const;
    int  getNumLines() const;

    void setMaximumLines(int _numLines);
    int getMaximumLines() const;
    void clearMaximumLines();

    void setBlockWidth(float _width);
    void setBlockHeight(float _height);
    
    void clearBlockWidth();
    void clearBlockHeight();
    
    float getBlockWidth() const;
    float getBlockHeight() const;
    
    bool empty() const;
    
    bool isTextHorizontal() const;
    bool isTextVertical() const;
    bool isTextWidthLimited() const;
    bool isTextHeightLimited() const;
    
    // can override w/ a library like libhyphenate
    virtual string hyphenate(string word) {return word;}
    
protected:
    
    float getTextWidth() const;  // accounts for rotation
    float getTextHeight() const; // accounts for rotation
    
    
    bool debug;
    
    void init();
    
    //--------------------------------------------------------------
    // VARIABLES ///////////////////////////////////////////////////
    //--------------------------------------------------------------

    // isCharacterWidthLimited -- limit to X columns for monofont or Y rows
    
    bool needsUpdate;
    int updateFromPosition; // TODO: the position from where we need to update
                                 // for efficiency, we may not need to udpate anything above an insert point, etc
                                // or below if the current line is the only one affected.

    // content
    string text;  // the full label text
    string displayText;
    vector<string> displayLines; // the actual adjusted strings for display
    
    int maximumLines;
    
    // pre/post/truncation -- is subject to truncation and alignment rules
    string textPre; // added to the beginning of all display text
    string textPost; // added to the end of all display text
    string truncationString;
    ofxMuiLineTruncationMode truncationMode;
    
    // size, location, position, etc.
    
    ofAlignHorz hAlign;
    ofAlignVert vAlign;
    ofOrientation orientation;
    
    int cursorPosition;
    float widthAtCursor;
    
    // not subject to rotation
    float blockWidth;
    float blockHeight;
    
    ofRectangle fullStringBoundingBox;
    ofRectangle displayStringBoundingBox;

    // style
    ofxMuiTrueTypeFont*     font;
    ofColor             cTextColor;
    ofxMuiCapsMode      capsStyle;
    ofxMuiLineBreakMode lineBreakMode;
    
};