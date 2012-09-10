//
//  ofxGuiTooltip.cpp
//  emptyExample
//
//  Created by Christopher Baker on 7/10/11.
//  Copyright 2011 Kitchen Budapest. All rights reserved.
//


#include "ofxGuiTooltip.h"

//--------------------------------------------------------------
ofxGuiTooltip::ofxGuiTooltip(const string& _name, bool _enabled) : ofxGuiLabel(_name, _enabled) {
    init();
}

//--------------------------------------------------------------
ofxGuiTooltip::ofxGuiTooltip(bool _enabled) : ofxGuiLabel(_enabled) {
    init();
}

//--------------------------------------------------------------
ofxGuiTooltip::~ofxGuiTooltip() {}

//--------------------------------------------------------------
void ofxGuiTooltip::init() {
        
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
void ofxGuiTooltip::update() {

    
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
void ofxGuiTooltip::setObject(ofxGuiObject* _object, ofMouseEventArgs &e) {
    
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
        setText(currentObject->getTooltip());
    } 
    
}

//--------------------------------------------------------------
void ofxGuiTooltip::cancel() {
    faderTimer = 0;
    waitTimer = waitDelay;
    isTouching = false;
}

//--------------------------------------------------------------
void ofxGuiTooltip::touchOn(const ofVec2f& mousePosition) {

    if(!isTouching) {
        isTouching = true;
    }
    
    if(isTouching && !isLocked) {
        pX = x;
        pY = y;
        x = mousePosition.x + vTooltipOffset.x;
        y = mousePosition.y + vTooltipOffset.y;
    }
    
}

//--------------------------------------------------------------
void ofxGuiTooltip::touchOff() {
    isTouching = false;
}

//--------------------------------------------------------------
bool ofxGuiTooltip::getFadeOut() const {
    return fadeOut;
}

//--------------------------------------------------------------
void ofxGuiTooltip::setFadeOut(bool _fadeOut) {
    fadeOut = _fadeOut;
}

//--------------------------------------------------------------
int  ofxGuiTooltip::getFadeDelay() const {return fadeDelay;}
//--------------------------------------------------------------
void ofxGuiTooltip::setFadeDelay(int millis) {fadeDelay = millis;}
//--------------------------------------------------------------
int  ofxGuiTooltip::getWaitDelay() const {return fadeDelay;}
//--------------------------------------------------------------
void ofxGuiTooltip::setWaitDelay(int millis) {waitDelay = millis;}
