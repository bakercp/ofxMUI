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

#include "ofxMuiObject.h"
#include "ofxMuiTextBlock.h"
#include <Poco/String.h>

using Poco::toUpper;
using Poco::toLower;
using Poco::toUpperInPlace;
using Poco::toLowerInPlace;


class ofxMuiLabel : public ofxMuiObject {
public:

    ofxMuiLabel(const string& _name, int _x, int _y, int _width, int _height, bool _enabled = true);
    ofxMuiLabel(const string& _name, int _x, int _y, bool _enabled = true);
    ofxMuiLabel(const string& _name, bool _enabled = true);
    ofxMuiLabel(bool _enabled = true);
    virtual ~ofxMuiLabel();
    
    //--------------------------------------------------------------
    // INHERITED FROM SUPERCLASS ///////////////////////////////////
    //--------------------------------------------------------------
    void draw();

    //--------------------------------------------------------------
    // PERSISTENCE /////////////////////////////////////////////////
    //--------------------------------------------------------------
    
    void    loadFromXml(ofxXmlSettings& xml);
    void    saveToXml(ofxXmlSettings& xml);
    
    //--------------------------------------------------------------
    // GETTERS AND SETTERS /////////////////////////////////////////
    //--------------------------------------------------------------
    
    void setText(const string& text);
    string getText() const;
    
    string getDisplayText() const;
    
    void setFontSize(const ofxMuiSize& _fontSize);
    ofxMuiSize getFontSize() const;
    
    void setCapsStyle(const ofxMuiCapsMode& _capsStyle);
    ofxMuiCapsMode getCapsStyle() const;

    void setLineBreakMode(const ofxMuiLineBreakMode& _lineBreakMode);
    ofxMuiLineBreakMode getLineBreakMode() const;
    
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
    
    ofxMuiCapsMode capsStyle;
    
    string text;  // the label text
    string pText; // the previous label text
    string displayText; // the actual adjusted string for display
    string pDisplayText; // previous displayString (for undos?)

    ofRectangle fullStringBoundingBox;
    ofRectangle displayStringBoundingBox;
    
    ofxMuiFont* labelFont;
    ofxMuiSize labelSize;

    ofxMuiLineBreakMode lineBreakMode;
    
    string truncationString;
    
    bool isMultiline;
        
};