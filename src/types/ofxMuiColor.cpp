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

#include "ofxMuiColor.h"

static ofColor COLOR_NORMAL_DEFAULT = ofColor(255,127);
static ofColor COLOR_HOVER_DEFAULT = ofColor(255,255,0,200);
static ofColor COLOR_ACTIVE_DEFAULT = ofColor(0,127,255,200);
static ofColor COLOR_DISABLED_DEFAULT = ofColor(255,127);

//--------------------------------------------------------------
ofxMuiColor::ofxMuiColor() : 
    normal(COLOR_NORMAL_DEFAULT),
    hover(COLOR_HOVER_DEFAULT),
    active(COLOR_ACTIVE_DEFAULT),
    disabled(COLOR_DISABLED_DEFAULT)
{}
    
//--------------------------------------------------------------
ofxMuiColor::ofxMuiColor(ofColor _normal) :
    normal(_normal),
    hover(_normal),
    active(_normal),
    disabled(_normal)
{}

//--------------------------------------------------------------
ofxMuiColor::ofxMuiColor(ofColor _normal, ofColor _hover, ofColor _active) :
    normal(_normal),
    hover(_hover),
    active(_active),
    disabled(COLOR_DISABLED_DEFAULT)
{}

//--------------------------------------------------------------
ofxMuiColor::ofxMuiColor(ofColor _normal, ofColor _hover, ofColor _active, ofColor _disabled) :
    normal(_normal),
    hover(_hover),
    active(_active),
    disabled(_disabled)
{}

//--------------------------------------------------------------
ofColor ofxMuiColor::get(bool isOver, bool isActive, bool isEnabled, float alphaScale) {
    ofColor cOut = normal;
    
    if (isEnabled) {
        if(isOver) {
            cOut = hover;
        } else if(isActive) {
            cOut = active;
		} else {
            cOut = normal;
        }
	} else {
        cOut = disabled;
	}

    if(alphaScale < 1.0) {
        cOut.a *= alphaScale;
    }
    
    return cOut;
}
