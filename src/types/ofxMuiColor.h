//
//  ofxMuiColor.h
//  A class to encpasulate multiple color states for a given gui element
//
//  Created by Christopher P. Baker on 7/10/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once

#include "ofMain.h"

class ofxMuiColor {
        
public:
    
    ofxMuiColor();    
    ofxMuiColor(ofColor _all);    
    ofxMuiColor(ofColor _normal, ofColor _hover, ofColor _active);
    ofxMuiColor(ofColor _normal, ofColor _hover, ofColor _active, ofColor _disabled);
    
    ofColor normal;   // the single dominant color
    ofColor hover;    // the color when something is ready for interaction
    ofColor active;   // the color of the "on" or 
    ofColor disabled; // the single color representing a disabled (non-interactive)

    ofColor get(bool isOver, 
                bool isActive,
                bool isEnabled,
                float alphaScale);
    
};
