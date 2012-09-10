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

#include "ofxMuiBoxProperties.h"

//--------------------------------------------------------------
ofxMuiBoxProperties::ofxMuiBoxProperties() {
    padding.set(0);
    margin.set(0);
    border.set(0);
    borderRadius = 0;
}
    
ofxMuiBoxProperties::ofxMuiBoxProperties(float val) {
    padding.set(val);
    margin.set(val);
    border.set(val);
    borderRadius = 0;
}

ofxMuiBoxProperties::ofxMuiBoxProperties(float _padding, float _margin) {
    padding.set(_padding);
    margin.set(_margin);
    border.set(0);
    borderRadius = 0;
}

ofxMuiBoxProperties::ofxMuiBoxProperties(float _padding, float _margin, float _border) {
    padding.set(_padding);
    margin.set(_margin);
    border.set(_border);
    borderRadius = 0;
}

ofxMuiBoxProperties::ofxMuiBoxProperties(float _padding, float _margin, float _border, float _borderRadius) {
    padding.set(_padding);
    margin.set(_margin);
    border.set(_border);
    borderRadius = _borderRadius;
}

ofxMuiBoxProperties::ofxMuiBoxProperties(float pTop, float pRight, float pBottom, float pLeft,
                                             float mTop, float mRight, float mBottom, float mLeft) {
    padding.set(pTop, pRight, pBottom, pLeft);
    margin.set(mTop, mRight, mBottom, mLeft);
    border.set(0);
    borderRadius = 0;
}

ofxMuiBoxProperties::ofxMuiBoxProperties(float pTop, float pRight, float pBottom, float pLeft,
                                             float mTop, float mRight, float mBottom, float mLeft,
                                             float _border) {
    padding.set(pTop, pRight, pBottom, pLeft);
    margin.set(mTop, mRight, mBottom, mLeft);
    border.set(_border);
    borderRadius = 0;
}

ofxMuiBoxProperties::ofxMuiBoxProperties(float pTop, float pRight, float pBottom, float pLeft,
                                         float mTop, float mRight, float mBottom, float mLeft,
                                         float bTop, float bRight, float bBottom, float bLeft) {
    padding.set(pTop, pRight, pBottom, pLeft);
    margin.set(mTop, mRight, mBottom, mLeft);
    border.set(bTop, bRight, bBottom, bLeft);
    borderRadius = 0;
}

ofxMuiBoxProperties::ofxMuiBoxProperties(const ofxMuiBoxProperties& props) : 
        padding(props.padding), 
        margin(props.margin),
        border(props.border),
        borderRadius(props.borderRadius) {
}

//--------------------------------------------------------------

void ofxMuiBoxProperties::setBoxProperties(const ofxMuiBoxProperties& props) {
    padding = props.padding;
    margin = props.margin;
    border = props.border;
    borderRadius = props.borderRadius;
}


//--------------------------------------------------------------
ofxMuiBoxPropertyQuad* ofxMuiBoxProperties::getPadding() {
    return &padding;
}

//--------------------------------------------------------------
ofxMuiBoxPropertyQuad* ofxMuiBoxProperties::getMargin() {
    return &margin;
}

//--------------------------------------------------------------
ofxMuiBoxPropertyQuad* ofxMuiBoxProperties::getBorder() {
    return &border;
}



//--------------------------------------------------------------
