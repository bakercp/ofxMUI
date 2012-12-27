//
//  ofxGuiLabel.h
//  emptyExample
//
//  Created by Christopher Baker on 7/11/11.
//  Copyright 2011 Kitchen Budapest. All rights reserved.
//

#pragma once

#include "ofxGuiObject.h"
#include <Poco/String.h>

using Poco::toUpper;
using Poco::toLower;
using Poco::toUpperInPlace;
using Poco::toLowerInPlace;


//enum ofxGuiLabelCaps {
//    LABEL_CAPS_NONE  = 0,
//    LABEL_CAPS_UPPER = 1,
//    LABEL_CAPS_LOWER = 2
//    // small small caps? :)
//};
//
//// mirrors ios
//enum ofxGuiLabelLineBreakMode {
//    LINE_BREAK_MODE_WORD_NONE = 0,
//    LINE_BREAK_MODE_WORD_WRAP,
//    LINE_BREAK_MODE_CHARACTER_WRAP,
//    LINE_BREAK_MODE_CLIP,
//    LINE_BREAK_MODE_HEAD_TRUNCATION,
//    LINE_BREAK_MODE_TAIL_TRUNCATION,
//    LINE_BREAK_MODE_MIDDLE_TRUNCATION
//};


class ofxGuiLabel : public ofxGuiObject {
public:

    ofxGuiLabel(const string& _name, int _x, int _y, int _width, int _height, bool _enabled = true);
    ofxGuiLabel(const string& _name, int _x, int _y, bool _enabled = true);
    ofxGuiLabel(const string& _name, bool _enabled = true);
    ofxGuiLabel(bool _enabled = true);
    virtual ~ofxGuiLabel();
    
    //--------------------------------------------------------------
    // INHERITED FROM SUPERCLASS ///////////////////////////////////
    //--------------------------------------------------------------
    void draw();

    //--------------------------------------------------------------
    // PERSISTENCE /////////////////////////////////////////////////
    //--------------------------------------------------------------
    
    void    buildFromXml();
    void    saveToXml();
    
    //--------------------------------------------------------------
    // GETTERS AND SETTERS /////////////////////////////////////////
    //--------------------------------------------------------------
    
    void setText(const string& text);
    string getText() const;
    
    string getDisplayText() const;
    
    void setFontSize(const ofxGuiSize& _fontSize);
    ofxGuiSize getFontSize() const;
    
    void setCapsStyle(int _capsStyle);
    int getCapsStyle() const;

    void setLineBreakMode(int _lineBreakMode);
    int getLineBreakMode() const;
    
    void setTruncationString(const string& _truncationString) const;
    string getTruncationString() const;

    
    bool empty() const;

    /*
    float getWidth();
    float getHeight();
     */
//    int getCursorPosition() const {
//        
//        ofVec2f p;
//        if(isCustomHitBox()) {
//            
//            p = screenToHitBox(mousePosition);
//            cout << "NAME=>" << name << endl;
//            if(hasParent()) {
//                cout << "PARENT NAME =" << getParent()->getName() << endl;
//            } else {
//                cout << "NO PARENT" << endl;
//            }
//            cout << "customHitBox" << getHitBoxOffset().x << "/" << getHitBoxOffset().y << ":" << getHitBoxWidth() << "/" << getHitBoxHeight() << endl;
//        } else {
//            p = screenToContentBox(mousePosition);
//            cout << "NONcustomHitBox" << getHitBoxOffset().x << "/" << getHitBoxOffset().y << ":" << getHitBoxWidth() << "/" << getHitBoxHeight() << endl;
//        }
//
//        cout << p.x << "X=" << x << ">><<" << width << endl;
//        
//        float width = 0.0f;
//        for(int i = displayText.size(); i >= 0; i--) {
//            width = labelFont->stringWidth(displayText.substr(0,i));
//            if( p.x >= width ) {
//                cursorPosition = i;
//                widthAtCursor = width;
//                break;
//            }
//        }
//        return cursorPosition;
//    }
    
    
protected:
    
    void init();

    //--------------------------------------------------------------
    // INHERITED FROM SUPERCLASS ///////////////////////////////////
    //--------------------------------------------------------------
    
    void doContentBoxLayout();
    
    //--------------------------------------------------------------
    // VARIABLES ///////////////////////////////////////////////////
    //--------------------------------------------------------------

    int cursorPosition;
    float widthAtCursor;
    
    ofxGuiLabelCaps capsStyle;
    
    string text;  // the label text
    string pText; // the previous label text
    string displayText; // the actual adjusted string for display
    string pDisplayText; // previous displayString (for undos?)

    ofRectangle fullStringBoundingBox;
    ofRectangle displayStringBoundingBox;
    
    ofTrueTypeFont* labelFont;
    ofxGuiSize labelSize;

//    ofxGuiLabelLineBreakMode lineBreakMode;
    int lineBreakMode;
    
    string truncationString;
    
    bool isMultiline;
    
    void breakLines(const ofxGuiLabelLineBreakMode& lineBreakMode,
                    const ofxGuiAlign& hAlign,
                    const ofxGuiAlign& vAlign,
                    string& s, 
                    const string& truncationString,
                    float targetWidth,
                    float targetHeight, 
                    int maxLines = numeric_limits<int>::max());

    void breakSingleLine(const ofxGuiLabelLineBreakMode lineBreakMode, 
                   string& s, 
                   const string& truncationString,
                   float targetWidth, 
                   int& truncationIndex);
    
};