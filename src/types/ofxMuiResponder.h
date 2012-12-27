//
//  ofxMuiResponder.h
//  example-basic
//
//  Created by Christopher P. Baker on 12/22/12.
//
//

#pragma once

#include "ofMain.h"

#include "ofxMuiObject.h"

class ofxMuiResponder {
public:
    ofxMuiResponder(ofxMuiObject* handler);
    
    
    ofxMuiObject* handler;
    
    ofTouchEventArgs touches;
    ofMouseEventArgs mouse;
    ofKeyEventArgs   keys;
};