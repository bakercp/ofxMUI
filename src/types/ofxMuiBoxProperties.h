//
//  ofxMuiBoxProperties.h
//  loosely 
//
//  Created by Christopher Baker on 7/11/11.
//  Copyright 2011 Kitchen Budapest. All rights reserved.
//


#pragma once

#include "ofMain.h"

enum ofxMuiBoxSide {
    SIDE_LEFT = 0,
    SIDE_TOP,
    SIDE_RIGHT,
    SIDE_BOTTOM
};


class ofxMuiBoxPropertyQuad {
public:
    
    float top,right,bottom,left;
    
    ofxMuiBoxPropertyQuad(float _top=0, float _right=0, float _bottom=0, float _left=0) {
        set(_top,_right,_bottom,_top);
    }

    ofxMuiBoxPropertyQuad( const ofxMuiBoxPropertyQuad& quad) {
        set(quad);
    }

    ofxMuiBoxPropertyQuad( float val) {
        set(val);
    }

    void set( float _top, float _right, float _bottom, float _left ) {
        top = _top;
        right = _right;
        bottom = _bottom;
        left = _left;
    }
    
    void set(const ofxMuiBoxSide& side, float value) {
        switch (side) {
            case SIDE_LEFT:
                left = value;
                break;
            case SIDE_TOP:
                top = value;
                break;
            case SIDE_RIGHT:
                right = value;
                break;
            case SIDE_BOTTOM:
                bottom = value;
                break;
        }
    }
    
    float get(const ofxMuiBoxSide& side) const {
        switch (side) {
            case SIDE_LEFT:
                return left;
            case SIDE_TOP:
                return top;
            case SIDE_RIGHT:
                return right;
            case SIDE_BOTTOM:
                return bottom;
        }
    }
    
    void set( const ofxMuiBoxPropertyQuad& quad ) {
        set(quad.top, quad.right, quad.bottom, quad.left);
    }
        
    void set( float val) {
        top = right = bottom = left = val;
    }
    
    float * getPtr() {
        return (float*)&top;
    }
    const float * getPtr() const {
        return (const float *)&top;
    }
    
    float& operator[]( int n ){
        return getPtr()[n];
    }
    
    float operator[]( int n ) const {
        return getPtr()[n];
    }
    
    
    
};

class ofxMuiBoxProperties {
    
public:
    
    //--------------------------------------------------------------
    ofxMuiBoxProperties();
    ofxMuiBoxProperties(float val);
    ofxMuiBoxProperties(float padding, float margin);
    ofxMuiBoxProperties(float padding, float margin, float border);
    ofxMuiBoxProperties(float padding, float margin, float border, float borderRadius);
    ofxMuiBoxProperties(float pTop, float pRight, float pBottom, float pLeft,
                        float mTop, float mRight, float mBottom, float mLeft);
    ofxMuiBoxProperties(float pTop, float pRight, float pBottom, float pLeft,
                        float mTop, float mRight, float mBottom, float mLeft,
                        float border);
    ofxMuiBoxProperties(float pTop, float pRight, float pBottom, float pLeft,
                        float mTop, float mRight, float mBottom, float mLeft,
                        float bTop, float bRight, float bBottom, float bLeft);

    ofxMuiBoxProperties(const ofxMuiBoxProperties& props);
    
    //--------------------------------------------------------------
    
    // used to be "set()" but cause issues with multiple inher
    // when next to ofSmartRect, etc.
    void setBoxProperties(const ofxMuiBoxProperties& props);
    
    //--------------------------------------------------------------
    

    //--------------------------------------------------------------
    
    // get po
    ofxMuiBoxPropertyQuad* getPadding();
    ofxMuiBoxPropertyQuad* getMargin();
    ofxMuiBoxPropertyQuad* getBorder();
    
    ofxMuiBoxPropertyQuad padding;
    ofxMuiBoxPropertyQuad margin;
    ofxMuiBoxPropertyQuad border;  
    
    
    // this could be per corner ... but ... annoying.
    /* 
     -moz-border-radius: 1000px;
     -moz-border-radius-bottomright: 2300px;
     border-radius: 1000px;
     border-bottom-right-radius: 2300px;
     etc.
     */ 
    int borderRadius;
};

