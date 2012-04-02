//
//  ofxGuiBoxProperties.h
//  loosely 
//
//  Created by Christopher Baker on 7/11/11.
//  Copyright 2011 Kitchen Budapest. All rights reserved.
//


#pragma once

#include "ofMain.h"

enum ofxGuiBoxSide {
    SIDE_LEFT = 0,
    SIDE_TOP,
    SIDE_RIGHT,
    SIDE_BOTTOM
};


class ofxGuiBoxPropertyQuad {
public:
    
    float top,right,bottom,left;
    
    ofxGuiBoxPropertyQuad(float _top=0, float _right=0, float _bottom=0, float _left=0) {
        set(_top,_right,_bottom,_top);
    }

    ofxGuiBoxPropertyQuad( const ofxGuiBoxPropertyQuad& quad) {
        set(quad);
    }

    ofxGuiBoxPropertyQuad( float val) {
        set(val);
    }

    void set( float _top, float _right, float _bottom, float _left ) {
        top = _top;
        right = _right;
        bottom = _bottom;
        left = _left;
    }
    
    void set(ofxGuiBoxSide side, float value) {
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
    
    float get(ofxGuiBoxSide side) {
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
    
    void set( const ofxGuiBoxPropertyQuad& quad ) {
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

class ofxGuiBoxProperties {
    
public:
    
    //--------------------------------------------------------------
    ofxGuiBoxProperties();
    ofxGuiBoxProperties(float val);
    ofxGuiBoxProperties(float padding, float margin);
    ofxGuiBoxProperties(float padding, float margin, float border);
    ofxGuiBoxProperties(float padding, float margin, float border, float borderRadius);
    ofxGuiBoxProperties(float pTop, float pRight, float pBottom, float pLeft,
                        float mTop, float mRight, float mBottom, float mLeft);
    ofxGuiBoxProperties(float pTop, float pRight, float pBottom, float pLeft,
                        float mTop, float mRight, float mBottom, float mLeft,
                        float border);
    ofxGuiBoxProperties(float pTop, float pRight, float pBottom, float pLeft,
                        float mTop, float mRight, float mBottom, float mLeft,
                        float bTop, float bRight, float bBottom, float bLeft);

    ofxGuiBoxProperties(const ofxGuiBoxProperties& props);
    
    //--------------------------------------------------------------
    
    // used to be "set()" but cause issues with multiple inher
    // when next to ofSmartRect, etc.
    void setBoxProperties(const ofxGuiBoxProperties& props);
    
    //--------------------------------------------------------------
    

    //--------------------------------------------------------------
    
    // get po
    ofxGuiBoxPropertyQuad* getPadding();
    ofxGuiBoxPropertyQuad* getMargin();
    ofxGuiBoxPropertyQuad* getBorder();
    
    ofxGuiBoxPropertyQuad padding;
    ofxGuiBoxPropertyQuad margin;
    ofxGuiBoxPropertyQuad border;  
    
    
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

