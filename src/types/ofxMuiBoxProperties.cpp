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
