//
//  ofxGuiLabel.h
//  emptyExample
//
//  Created by Christopher Baker on 7/11/11.
//  Copyright 2011 Kitchen Budapest. All rights reserved.
//

#pragma once

#include "ofMain.h"
#include "ofxGuiConstants.h"
#include "ofxGuiTextUtils.h"
#include "ofxGuiTrueTypeFont.h"
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

class ofxGuiTextBlock {
public:
    
    ofxGuiTextBlock(ofxGuiTrueTypeFont* font);
    ofxGuiTextBlock(ofxGuiTrueTypeFont* font, const string& _text);
    ofxGuiTextBlock(ofxGuiTrueTypeFont* font, const string& _text, float _width);
    ofxGuiTextBlock(ofxGuiTrueTypeFont* font, const string& _text, float _width, float _height);
    
    virtual ~ofxGuiTextBlock();

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

    ofxGuiTrueTypeFont* getFont();
    void setFont(ofxGuiTrueTypeFont* _font);
    
    void setCapsStyle(const ofxGuiCapsMode& _capsStyle);
    ofxGuiCapsMode getCapsStyle() const;

    void setLineBreakMode(const ofxGuiLineBreakMode& _lineBreakMode);
    ofxGuiLineBreakMode getLineBreakMode() const;
    
    void setLineTruncationMode(const ofxGuiLineTruncationMode& _lineTruncationMode);
    ofxGuiLineTruncationMode getLineTruncationMode() const;
    
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
    ofxGuiLineTruncationMode truncationMode;
    
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
    ofxGuiTrueTypeFont*     font;
    ofColor             cTextColor;
    ofxGuiCapsMode      capsStyle;
    ofxGuiLineBreakMode lineBreakMode;
    
};