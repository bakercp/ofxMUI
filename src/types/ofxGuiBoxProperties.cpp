#include "ofxGuiBoxProperties.h"

//--------------------------------------------------------------
ofxGuiBoxProperties::ofxGuiBoxProperties() {
    padding.set(0);
    margin.set(0);
    border.set(0);
    borderRadius = 0;
}
    
ofxGuiBoxProperties::ofxGuiBoxProperties(float val) {
    padding.set(val);
    margin.set(val);
    border.set(val);
    borderRadius = 0;
}

ofxGuiBoxProperties::ofxGuiBoxProperties(float _padding, float _margin) {
    padding.set(_padding);
    margin.set(_margin);
    border.set(0);
    borderRadius = 0;
}

ofxGuiBoxProperties::ofxGuiBoxProperties(float _padding, float _margin, float _border) {
    padding.set(_padding);
    margin.set(_margin);
    border.set(_border);
    borderRadius = 0;
}

ofxGuiBoxProperties::ofxGuiBoxProperties(float _padding, float _margin, float _border, float _borderRadius) {
    padding.set(_padding);
    margin.set(_margin);
    border.set(_border);
    borderRadius = _borderRadius;
}

ofxGuiBoxProperties::ofxGuiBoxProperties(float pTop, float pRight, float pBottom, float pLeft,
                                             float mTop, float mRight, float mBottom, float mLeft) {
    padding.set(pTop, pRight, pBottom, pLeft);
    margin.set(mTop, mRight, mBottom, mLeft);
    border.set(0);
    borderRadius = 0;
}

ofxGuiBoxProperties::ofxGuiBoxProperties(float pTop, float pRight, float pBottom, float pLeft,
                                             float mTop, float mRight, float mBottom, float mLeft,
                                             float _border) {
    padding.set(pTop, pRight, pBottom, pLeft);
    margin.set(mTop, mRight, mBottom, mLeft);
    border.set(_border);
    borderRadius = 0;
}

ofxGuiBoxProperties::ofxGuiBoxProperties(float pTop, float pRight, float pBottom, float pLeft,
                                         float mTop, float mRight, float mBottom, float mLeft,
                                         float bTop, float bRight, float bBottom, float bLeft) {
    padding.set(pTop, pRight, pBottom, pLeft);
    margin.set(mTop, mRight, mBottom, mLeft);
    border.set(bTop, bRight, bBottom, bLeft);
    borderRadius = 0;
}

ofxGuiBoxProperties::ofxGuiBoxProperties(const ofxGuiBoxProperties& props) : 
        padding(props.padding), 
        margin(props.margin),
        border(props.border),
        borderRadius(props.borderRadius) {
}

//--------------------------------------------------------------

void ofxGuiBoxProperties::setBoxProperties(const ofxGuiBoxProperties& props) {
    padding = props.padding;
    margin = props.margin;
    border = props.border;
    borderRadius = props.borderRadius;
}


//--------------------------------------------------------------
ofxGuiBoxPropertyQuad* ofxGuiBoxProperties::getPadding() {
    return &padding;
}

//--------------------------------------------------------------
ofxGuiBoxPropertyQuad* ofxGuiBoxProperties::getMargin() {
    return &margin;
}

//--------------------------------------------------------------
ofxGuiBoxPropertyQuad* ofxGuiBoxProperties::getBorder() {
    return &border;
}



//--------------------------------------------------------------
