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

#include "ofxMuiTooltip.h"

//--------------------------------------------------------------
ofxMuiTooltip::ofxMuiTooltip(const string& _name, bool _enabled) : ofxMuiLabel(_name, _enabled) {
    init();
}

//--------------------------------------------------------------
ofxMuiTooltip::ofxMuiTooltip(bool _enabled) : ofxMuiLabel(_enabled) {
    init();
}

//--------------------------------------------------------------
ofxMuiTooltip::~ofxMuiTooltip() {}

//--------------------------------------------------------------
void ofxMuiTooltip::init() {
        
    setObjectType("TOOLTIP");

    currentObject = NULL;
    
    vTooltipOffset = defaults->tooltipOffset;

    pX = -INT_MAX;
    pY = -INT_MAX;
    
    fadeDelay = defaults->tooltipWaitDelay;
    waitDelay = defaults->tooltipFadeDelay;
    
    faderTimer = 0; // init to zero
    waitTimer  = 0;
    
    
    isTouching = false;
    isLocked = false;
    
    fadeOut = true;

    lastTime = ofGetElapsedTimeMillis();

    alphaScale = 0.0;
    
    setBoxProperties(defaults->tooltipBoxProperties);
    requestBoxLayout();
}

//--------------------------------------------------------------
void ofxMuiTooltip::update() {

    
    // resize the local frames, this must be done here
    // because the tooltip oject is not a child of another gui object
    // TODO: unless we hve on massive invisible container ... 
    if(needsLayout) {
        doLayout();
    }

    // we keep track here in case this gets disabled or something
    // perhaps ... not needed if this is always getting called ...
    int now     = ofGetElapsedTimeMillis(); 
    int dt      = now - lastTime;
    lastTime    = now;
    
    if(isTouching) {
        faderTimer = fadeDelay;
        waitTimer += dt;
        
        if(waitTimer >= waitDelay) {
            alphaScale = 1.0;
            isLocked = true;
        } else {
            alphaScale = 0.0;
            isLocked = false;
        }
        
    } else {
        
        faderTimer -= dt;
        waitTimer  -= dt;
        if(fadeOut) {
            alphaScale = ofMap(faderTimer, 0, fadeDelay, 0.0f, 1.0f, true);
        } else {
            alphaScale = (faderTimer > 0.0) ? 1.0 : 0.0; 
        }
    }

    faderTimer = ofClamp(faderTimer, 0, fadeDelay);
    waitTimer = ofClamp(waitTimer, 0, waitDelay);
        
}
  
//--------------------------------------------------------------
void ofxMuiTooltip::setObject(ofxMuiObject* _object, ofMouseEventArgs &e) {
    
    if(_object == NULL) {
        if(currentObject != NULL) {
            currentObject = NULL;
            touchOff();
        } else {
            // do nothing ...
            
        }
    } else if(_object == currentObject) {
        touchOn(ofVec2f(e.x,e.y));
        // already set
    } else {
        // IT IS A NEW OBJECT
        touchOff();
        touchOn(ofVec2f(e.x,e.y));
        currentObject = _object;
       // setText(currentObject->getTooltip());
    } 
    
}

//--------------------------------------------------------------
void ofxMuiTooltip::cancel() {
    faderTimer = 0;
    waitTimer = waitDelay;
    isTouching = false;
}

//--------------------------------------------------------------
void ofxMuiTooltip::touchOn(const ofVec2f& mousePosition) {

    if(!isTouching) {
        isTouching = true;
    }
    
    if(isTouching && !isLocked) {
        pX = getX();
        pY = getY();
        setPosition(mousePosition + vTooltipOffset);
    }
    
}

//--------------------------------------------------------------
void ofxMuiTooltip::touchOff() {
    isTouching = false;
}

//--------------------------------------------------------------
bool ofxMuiTooltip::getFadeOut() const {
    return fadeOut;
}

//--------------------------------------------------------------
void ofxMuiTooltip::setFadeOut(bool _fadeOut) {
    fadeOut = _fadeOut;
}

//--------------------------------------------------------------
int  ofxMuiTooltip::getFadeDelay() const {return fadeDelay;}
//--------------------------------------------------------------
void ofxMuiTooltip::setFadeDelay(int millis) {fadeDelay = millis;}
//--------------------------------------------------------------
int  ofxMuiTooltip::getWaitDelay() const {return fadeDelay;}
//--------------------------------------------------------------
void ofxMuiTooltip::setWaitDelay(int millis) {waitDelay = millis;}
