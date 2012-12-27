//
//  ofxMuiTouch.h
//  example-basic
//
//  Created by Christopher P. Baker on 12/22/12.
//
//

#pragma once

#include "ofMain.h"

#include "ofxMuiObject.h"

class ofxMuiTouch {
public:
    ofxMuiTouch();
    virtual ~ofxMuiTouch();
    
    void update(const ofTouchEventArgs& evt);
    void update(const ofMouseEventArgs& evt);
    
    
    ofVec2f getPosition()     const;
    ofVec2f getLastPosition() const;
    ofVec2f getVelocity()     const;
    
    unsigned long long getLastUpdated() const;
    
    unsigned int getId() const;
    unsigned int getModifiers() const;
    
    
protected:
    
    unsigned int id;
    unsigned int modifiers;
    
    ofVec2f position;
    ofVec2f lastPosition;
    
    unsigned long long lastUpdated;
    
};