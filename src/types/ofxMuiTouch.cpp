//
//  ofxMuiTouch.cpp
//  example-basic
//
//  Created by Christopher P. Baker on 12/22/12.
//
//

#include "ofxMuiTouch.h"

//--------------------------------------------------------------
ofxMuiTouch::ofxMuiTouch() {}
//--------------------------------------------------------------
ofxMuiTouch::~ofxMuiTouch() {}

//--------------------------------------------------------------
void ofxMuiTouch::update(const ofTouchEventArgs& evt) {
    
}

//--------------------------------------------------------------
void ofxMuiTouch::update(const ofMouseEventArgs& evt) {
    
}


//--------------------------------------------------------------
ofVec2f ofxMuiTouch::getPosition() const {
    return position;
}

//--------------------------------------------------------------
ofVec2f ofxMuiTouch::getLastPosition() const {
    return lastPosition;
}

//--------------------------------------------------------------
ofVec2f ofxMuiTouch::getVelocity() const {
    return position - lastPosition;
}

//--------------------------------------------------------------
unsigned long long ofxMuiTouch::getLastUpdated() const {
    return lastUpdated;
}

//--------------------------------------------------------------
unsigned int ofxMuiTouch::getId() const {
    return id;
}

//--------------------------------------------------------------
unsigned int ofxMuiTouch::getModifiers() const {
    return modifiers;
}

