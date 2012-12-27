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

//--------------------------------------------------------------
#include "ofxMuiLabelledObject.h"

class ofxMuiQuad : public ofxMuiObject {
    
public:
    
    ofxMuiQuad(const string& _name, int _x, int _y, int _width, int _height, bool _enabled = true);
    ofxMuiQuad(const string& _name, int _x, int _y,bool _enabled = true);
    ofxMuiQuad(const string& _name, bool _enabled = true);
    ofxMuiQuad(bool _enabled = true);
    virtual ~ofxMuiQuad();
    
    //--------------------------------------------------------------
    // INHERITED FROM SUPERCLASS ///////////////////////////////////
    //--------------------------------------------------------------
    
    void draw();
    
    //--------------------------------------------------------------
    // PERSISTENCE /////////////////////////////////////////////////
    //--------------------------------------------------------------
    
	void loadFromXml(ofxXmlSettings& xml);
	void saveToXml(ofxXmlSettings& xml);
    
    //--------------------------------------------------------------
    // KEYBINDING //////////////////////////////////////////////////
    //--------------------------------------------------------------
    
//    void keyBind_toggleValue(int key);
    
    //--------------------------------------------------------------
    // GETTERS AND SETTERS /////////////////////////////////////////
    //--------------------------------------------------------------
    
    //--------------------------------------------------------------
    // EVENTS //////////////////////////////////////////////////////
    //--------------------------------------------------------------
        
protected:
    
    void init(); // local init for convenience
    void dataChanged(int index);
    
    //--------------------------------------------------------------
    // INHERITED FROM SUPERCLASS ///////////////////////////////////
    //--------------------------------------------------------------
    
    // mouse action
	void onPress();
	void onRelease();
	void onReleaseOutside();
    
    void doContentBoxLayout();
    
	//--------------------------------------------------------------
    // VARIABLES ///////////////////////////////////////////////////
    //--------------------------------------------------------------
    
    ofAlignHorz             labelPositionHorz;
    ofAlignVert             labelPositionVert;
    ofAlignVert             vAlign;
    
    bool                    roundFrame;
    
};

//--------------------------------------------------------------

