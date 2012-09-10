//
//  ofxMuiUtils.h
//  emptyExample
//
//  Created by Christopher Baker on 7/12/11.
//  Copyright 2011 Kitchen Budapest. All rights reserved.
//

#pragma once

#include "ofMain.h"
#include "ofxMuiObject.h"




class ofxMuiObject;


// UTILITY METHODS

static inline void rect(float x1, float y1, float x2, float y2,
                   float tl, float tr, float br, float bl) {
    
    ofBeginShape();
    //    vertex(x1+tl, y1);
    if (tr != 0) {
        ofVertex(x2-tr, y1);
    
//        quadraticVertex(x2, y1, x2, y1+tr);
    } else {
        ofVertex(x2, y1);
    }
    if (br != 0) {
        ofVertex(x2, y2-br);
//        quadraticVertex(x2, y2, x2-br, y2);
    } else {
        ofVertex(x2, y2);
    }
    if (bl != 0) {
        ofVertex(x1+bl, y2);
//        quadraticVertex(x1, y2, x1, y2-bl);
    } else {
        ofVertex(x1, y2);
    }
    if (tl != 0) {
        ofVertex(x1, y1+tl);
 //       quadraticVertex(x1, y1, x1+tl, y1);
    } else {
        ofVertex(x1, y1);
    }
    //    endShape();
   // endShape(CLOSE);
    ofEndShape();
}


//--------------------------------------------------------------
static inline int roundInt(float value)
{
    // a la java
	return (int)floor((value + 0.5f));
};
 

//--------------------------------------------------------------
static inline string ofColorToHexString(const ofColor color) 
{
    char hex[9];
    int  red	= CLAMP(roundInt(color.r),0,255);
    int  green	= CLAMP(roundInt(color.g),0,255);
    int  blue	= CLAMP(roundInt(color.b),0,255);
    int  alpha	= CLAMP(roundInt(color.a),0,255);
    sprintf(hex, "%.2X%.2X%.2X%.2X", alpha, red, green, blue );
    return hex;
};
//--------------------------------------------------------------


#define MAX_GUI_OBJECT_STACK 1024

static int ofxMuiDebug = true;
static int ofxMuiObjectStackDepth = 0;
static ofxMuiObject* ofxMuiObjectStack[MAX_GUI_OBJECT_STACK];

static void ofxMuiPushObject(ofxMuiObject* obj) {
    if(ofxMuiObjectStackDepth < MAX_GUI_OBJECT_STACK) {
        ofxMuiObjectStack[ofxMuiObjectStackDepth] = obj;
        ofxMuiObjectStackDepth++;
    } else {
        ofLog(OF_LOG_ERROR, "ofxMui: Too many calls to ofxMuiPushObject without enough calls to ofxMuiPopObject.");
    }
}

static ofxMuiObject* ofxMuiPopObject() {
    if(ofxMuiObjectStackDepth > 0) {
        ofxMuiObject* obj = ofxMuiObjectStack[ofxMuiObjectStackDepth];
        ofxMuiObjectStackDepth--;
        return obj;
    } else {
        ofLog(OF_LOG_ERROR, "ofxMui: Too many calls to ofxMuiPopObject without enough calls to ofxMuiPushObject.");
        return NULL;
    }
}

/*
static int ofxMuiObjectDeferredDrawStackDepth = 0;
static ofxMuiObject* ofxMuiObjectDeferredDrawStack[MAX_GUI_OBJECT_STACK];

static void ofxMuiRegisterDeferredDrawObject(ofxMuiObject* obj) {
    if(ofxMuiObjectDeferredDrawStackDepth < MAX_GUI_OBJECT_STACK) {
        ofxMuiObjectDeferredDrawStack[ofxMuiObjectDeferredDrawStackDepth] = obj;
        ofxMuiObjectDeferredDrawStackDepth++;
    } else {
        ofLog(OF_LOG_ERROR, "ofxMui: ofxMuiRegisterDeferredDrawObject full!");
    }
}

 */
// no way to delete them ... ?



static void ofxMuiDebugString(ofxMuiObject* object, string s) {
    string ss = "";
    for(int i = 0; i < ofxMuiObjectStackDepth; i++) 
        ss += "\t";
    //ss += "[" + object->getName() + "] : ";
    ss += s;
    cout << ss << endl;
};

static inline string debugRectToString(ofRectangle rect) {
    string s = ofToString(rect.x) + "/" + 
    ofToString(rect.y) + "/" + 
    ofToString(rect.width) + "/" + 
    ofToString(rect.height);
    return s;
};
