//
//  ofxGuiLabel.h
//  emptyExample
//
//  Created by Christopher Baker on 7/11/11.
//  Copyright 2011 Kitchen Budapest. All rights reserved.
//

#pragma once

#include "ofxGuiObject.h"
#include "ofxGuiTextBlock.h"
#include <Poco/String.h>

using Poco::toUpper;
using Poco::toLower;
using Poco::toUpperInPlace;
using Poco::toLowerInPlace;


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
    
    void setCapsStyle(const ofxGuiCapsMode& _capsStyle);
    ofxGuiCapsMode getCapsStyle() const;

    void setLineBreakMode(const ofxGuiLineBreakMode& _lineBreakMode);
    ofxGuiLineBreakMode getLineBreakMode() const;
    
    void setTruncationString(const string& _truncationString);
    string getTruncationString() const;

    
    bool empty() const;

    /*
    float getWidth();
    float getHeight();
     */
    int getCursorPosition() {
        
        ofVec2f p;
        if(isCustomHitBox()) {
            
            p = screenToHitBox(mousePosition);
            cout << "NAME=>" << name << endl;
            if(hasParent()) {
                cout << "PARENT NAME =" << getParent()->getName() << endl;
            } else {
                cout << "NO PARENT" << endl;
            }
            cout << "customHitBox" << getHitBoxOffset().x << "/" << getHitBoxOffset().y << ":" << getHitBoxWidth() << "/" << getHitBoxHeight() << endl;
        } else {
            p = screenToContentBox(mousePosition);
            cout << "NONcustomHitBox" << getHitBoxOffset().x << "/" << getHitBoxOffset().y << ":" << getHitBoxWidth() << "/" << getHitBoxHeight() << endl;
        }

        cout << p.x << "X=" << x << ">><<" << width << endl;
        
        float width = 0.0f;
        for(int i = displayText.size(); i >= 0; i--) {
            width = labelFont->stringWidth(displayText.substr(0,i));
            if( p.x >= width ) {
                cursorPosition = i;
                widthAtCursor = width;
                break;
            }
        }
        return cursorPosition;
    }
    
    
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
    
    ofxGuiCapsMode capsStyle;
    
    string text;  // the label text
    string pText; // the previous label text
    string displayText; // the actual adjusted string for display
    string pDisplayText; // previous displayString (for undos?)

    ofRectangle fullStringBoundingBox;
    ofRectangle displayStringBoundingBox;
    
    ofxGuiFont* labelFont;
    ofxGuiSize labelSize;

    ofxGuiLineBreakMode lineBreakMode;
    
    string truncationString;
    
    bool isMultiline;
        
};