//
//  ofxGuiTooltip.h
//  emptyExample
//
//  Created by Christopher Baker on 7/10/11.
//  Copyright 2011 Kitchen Budapest. All rights reserved.
//

#pragma once

#include "ofMain.h"
#include "ofxGuiLabel.h"

// TODO: labels go offscreen if their object is too close to an edge


class ofxGuiTooltip : public ofxGuiLabel {
public:
    ofxGuiTooltip(const string& _name, bool _enabled = true);
    ofxGuiTooltip(bool _enabled = true);
    ~ofxGuiTooltip();
    
    void update();
    
    void setObject(ofxGuiObject* _object, ofMouseEventArgs &e);
    
    void touchOn(const ofVec2f& _mousePosition);
    void touchOff();

    void cancel();
    
    int  getFadeDelay() const;
    void setFadeDelay(int millis);
    
    int  getWaitDelay() const;
    void setWaitDelay(int millis);
    
    bool getFadeOut() const;
    void setFadeOut(bool _fadeOut);
    
protected:
    void init();
        
    // fading and waiting
    long faderTimer;
    long waitTimer;

    // delays
    long fadeDelay;
    long waitDelay;
    
    bool fadeOut;
    
    // is the mouse touching
    bool isTouching;
    bool isLocked;
    
    // the last time it was touched
    int lastTime;
    
    // positioning
    int pX, pY;

    ofVec2f vTooltipOffset;
    ofxGuiObject* currentObject;
    
};


