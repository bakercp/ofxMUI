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

#include "ofxMuiLabelledObject.h"

//--------------------------------------------------------------
ofxMuiLabelledObject::ofxMuiLabelledObject(string _name, int _x, int _y, int _width, int _height, bool _enabled) : 
ofxMuiObject(/*_name,*/_x, _y, _width, _height, _enabled) {
    init();
}

//--------------------------------------------------------------
ofxMuiLabelledObject::ofxMuiLabelledObject(string _name, int _x, int _y,bool _enabled) : 
ofxMuiObject(/*_name,*/ _x, _y, _enabled) {
    init();
}

//--------------------------------------------------------------
ofxMuiLabelledObject::ofxMuiLabelledObject(string _name,bool _enabled) :
ofxMuiObject(/*_name,*/ _enabled) {
    init();
}

//--------------------------------------------------------------
ofxMuiLabelledObject::ofxMuiLabelledObject(bool _enabled) : 
ofxMuiObject(_enabled) {
    init();
}

//--------------------------------------------------------------
ofxMuiLabelledObject::~ofxMuiLabelledObject() {
    // TODO: shared poitners!!!!!
    removeChild(label);
    removeChild(valueLabel);
    delete label;
    delete valueLabel;
}

//--------------------------------------------------------------
void ofxMuiLabelledObject::init() {
    
    // add the labels
    label = new ofxMuiLabel();//ofxMuiLabel(name);
    label->setBoxProperties(defaults->sharedLabelBoxProperties);
    //label->setName("LABEL");
    label->setText("NULL");
    label->disable();
    
    valueLabel = new ofxMuiLabel();
    valueLabel->setBoxProperties(defaults->valueLabelBoxProperties);
    //valueLabel->setName("VALUE LABEL");
    valueLabel->setText("NULL");
    valueLabel->disable();
    
    label->setIsTouchHandler(false);
    label->setIsKeyboardHandler(false);
    
    valueLabel->setIsTouchHandler(false);
    valueLabel->setIsKeyboardHandler(false);

    labelPositionHorz = OF_ALIGN_HORZ_RIGHT;
    labelPositionVert = OF_ALIGN_VERT_CENTER;

    valueLabelPositionHorz = OF_ALIGN_HORZ_RIGHT;
    valueLabelPositionVert = OF_ALIGN_VERT_CENTER;

    /*
    valueLabel->setFixedWidth(false);
    valueLabel->setFixedHeight(false);
    */
     
    addChild(label);
    addChild(valueLabel);
    
    requestBoxLayout();
}

//--------------------------------------------------------------
ofxMuiLabel* ofxMuiLabelledObject::getValueLabel() {
    return valueLabel;
}

//--------------------------------------------------------------
ofxMuiLabel* ofxMuiLabelledObject::getLabel() {
    return label;
}

//--------------------------------------------------------------
void ofxMuiLabelledObject::disableLabels() {
    valueLabel->disable();
    label->disable();
    requestBoxLayout();
}

//--------------------------------------------------------------
void ofxMuiLabelledObject::enableLabels() {
    valueLabel->enable();
    label->enable();
    requestBoxLayout();
}

//--------------------------------------------------------------
void ofxMuiLabelledObject::enableValueLabel() {
    valueLabel->enable();
    requestBoxLayout();
}

//--------------------------------------------------------------
void ofxMuiLabelledObject::enableLabel() {
    label->enable();
    requestBoxLayout();
}

//--------------------------------------------------------------
void ofxMuiLabelledObject::disableValueLabel() {
    valueLabel->disable();
    requestBoxLayout();
}

//--------------------------------------------------------------
void ofxMuiLabelledObject::disableLabel() {
    label->disable();
    requestBoxLayout();
}

//--------------------------------------------------------------
void ofxMuiLabelledObject::setLabelPositionHorz(const ofAlignHorz& hPos) {
    labelPositionHorz = hPos;
    requestBoxLayout();
}

//--------------------------------------------------------------
void ofxMuiLabelledObject::setLabelPositionVert(const ofAlignVert& vPos) {
    labelPositionVert = vPos;
    requestBoxLayout();
}

//--------------------------------------------------------------
void ofxMuiLabelledObject::setValueLabelPositionHorz(const ofAlignHorz& hPos) {
    valueLabelPositionHorz = hPos;
    requestBoxLayout();
}

//--------------------------------------------------------------
void ofxMuiLabelledObject::setValueLabelPositionVert(const ofAlignVert& vPos) {
    valueLabelPositionVert = vPos;
    requestBoxLayout();
}

//--------------------------------------------------------------
ofAlignHorz ofxMuiLabelledObject::getLabelPositionHorz() const {
    return labelPositionHorz;
}

//--------------------------------------------------------------
ofAlignVert ofxMuiLabelledObject::getLabelPositionVert() const {
    return labelPositionVert;
}

//--------------------------------------------------------------
ofAlignHorz ofxMuiLabelledObject::getValueLabelPositionHorz() const {
    return valueLabelPositionHorz;
}

//--------------------------------------------------------------
ofAlignVert ofxMuiLabelledObject::getValueLabelPositionVert() const {
    return valueLabelPositionVert;
}


