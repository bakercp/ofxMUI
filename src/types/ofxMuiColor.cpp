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
