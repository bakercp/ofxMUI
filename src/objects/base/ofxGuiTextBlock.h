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
    ofxGuiTextBlock(ofxGuiTrueTypeFont* font, string _text);
    ofxGuiTextBlock(ofxGuiTrueTypeFont* font, string _text, float _width);
    ofxGuiTextBlock(ofxGuiTrueTypeFont* font, string _text, float _width, float _height);
    
    virtual ~ofxGuiTextBlock();

    // drawing and updating
    void update();
    virtual void draw(float x, float y);
    virtual void draw();
    
    // content
    void setText(string text);
    string getText();
    
    void insert(string s, int position);
    void append(string s);
    void prepend(string s);
    
    string getDisplayText();
    string getDisplayTextLine(int lineNumber);
    vector<string> getDisplayTextLines();
    
    // style
    
    void setTextColor(ofColor _cText);
    ofColor getTextColor();

    ofxGuiTrueTypeFont* getFont();
    void setFont(ofxGuiTrueTypeFont* _font);
    
    void setCapsStyle(ofxGuiCapsMode _capsStyle);
    ofxGuiCapsMode getCapsStyle();

    void setLineBreakMode(ofxGuiLineBreakMode _lineBreakMode);
    ofxGuiLineBreakMode getLineBreakMode();
    
    void setLineTruncationMode(ofxGuiLineTruncationMode _lineTruncationMode);
    ofxGuiLineTruncationMode getLineTruncationMode();
    
    void setTruncationString(string _truncationString);
    string getTruncationString();

    void setHorizontalAlignment(ofxGuiAlign _hAlign);
    void setVerticalAlignment(ofxGuiAlign _vAlign);
    
    ofxGuiAlign getVerticalAlign();
    ofxGuiAlign getHorizontalAlignment();

    void setOrientation(ofOrientation _orientation);
    ofOrientation getOrientation();
    
    
    bool allowMultipleLines();
    int  getNumLines();

    void setMaximumLines(int _numLines);
    int getMaximumLines();
    void clearMaximumLines();

    void setBlockWidth(float _width);
    void setBlockHeight(float _height);
    
    void clearBlockWidth();
    void clearBlockHeight();
    
    float getBlockWidth();
    float getBlockHeight();
    
    bool empty();    
    
    bool isTextHorizontal();
    bool isTextVertical();
    bool isTextWidthLimited();
    bool isTextHeightLimited();
    
    // can override w/ a library like libhyphenate
    virtual string hyphenate(string word) {return word;}
    
protected:
    
    float getTextWidth();  // accounts for rotation
    float getTextHeight(); // accounts for rotation
    
    
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
    
    ofxGuiAlign hAlign;
    ofxGuiAlign vAlign;
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