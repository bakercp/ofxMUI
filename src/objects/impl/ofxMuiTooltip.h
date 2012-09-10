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

#include "ofMain.h"
#include "ofxMuiLabel.h"

// TODO: labels go offscreen if their object is too close to an edge


class ofxMuiTooltip : public ofxMuiLabel {
public:
    ofxMuiTooltip(const string& _name, bool _enabled = true);
    ofxMuiTooltip(bool _enabled = true);
    ~ofxMuiTooltip();
    
    void update();
    
    void setObject(ofxMuiObject* _object, ofMouseEventArgs &e);
    
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
    ofxMuiObject* currentObject;
    
};


