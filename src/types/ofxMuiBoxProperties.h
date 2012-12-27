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


// TODO: this can now be replaced by combinations of ofAlignVert & ofAlignHorz
enum ofxMuiBoxSide {
    SIDE_LEFT = 0,
    SIDE_TOP,
    SIDE_RIGHT,
    SIDE_BOTTOM
};

enum ofxMuiBoxCorner {
    TOP_LEFT = 0,
    TOP_RIGHT,
    BOTTOM_RIGHT,
    BOTTOM_LEFT
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
    
//    float getTotalVerticalPadding() const;
//    float getTotalHorizontalPadding() const;
//
//    float getTotalVerticalMargin() const;
//    float getTotalHorizontalMargin() const;
//
//    float getTotalVerticalBorder() const;
//    float getTotalHorizontalBorder() const;

    
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

