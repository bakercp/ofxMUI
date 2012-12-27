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

#include "ofxMuiNumberBox.h"

//--------------------------------------------------------------
ofxMuiNumberBox::ofxMuiNumberBox(const string& _name, int _x, int _y, int _width, int _height, bool _enabled) : 
ofxMuiLabelledObject(_name, _x, _y, _width, _height, _enabled),
ofxMuiNumberData() {
    init();
}

//--------------------------------------------------------------
ofxMuiNumberBox::ofxMuiNumberBox(const string& _name, int _x, int _y,bool _enabled) :
ofxMuiLabelledObject(_name, _x, _y, _enabled),
ofxMuiNumberData() {
    init();
}

//--------------------------------------------------------------
ofxMuiNumberBox::ofxMuiNumberBox(const string& _name,bool _enabled) :
ofxMuiLabelledObject(_name, _enabled),
ofxMuiNumberData() {
    init();
}

//--------------------------------------------------------------
ofxMuiNumberBox::ofxMuiNumberBox(bool _enabled) : 
ofxMuiLabelledObject(_enabled),
ofxMuiNumberData() {
    init();
}

//--------------------------------------------------------------
ofxMuiNumberBox::~ofxMuiNumberBox() {
}

//--------------------------------------------------------------
void ofxMuiNumberBox::init() {

    setObjectType("NUMBER_BOX");
    
    setHitBoxWidth(defaults->numberBoxWidth);
    setHitBoxHeight(defaults->numberBoxHeight);
        
	// set default key binding
    keyBind_increaseValue(defaults->keyboardIncrease);
    keyBind_decreaseValue(defaults->keyboardDecrease);
    
    setBoxProperties(defaults->numberBoxBoxProperties);
    
    // set values
    setValue(0.5f);
    //setMaxValue(1.0f);
    //setMinValue(0.0f);
    
    
    label->enable();
    valueLabel->enable();
    
    requestBoxLayout();
}

//--------------------------------------------------------------
void ofxMuiNumberBox::update() {
//    tooltip = toString();
//    valueLabel->setText(tooltip);
//    valueLabel->setTooltip(tooltip);
}

//--------------------------------------------------------------
void ofxMuiNumberBox::draw() {
    
    ofPushStyle();
    ofPushMatrix();
    
    ofTranslate(getHitBoxPosition());
    
    //--------- DRAW THE BUTTON BACKGROUND
    // default
    ofFill();

    ofSetColor(cActiveAreaForeground.get(isTouchOver(),isTouchDown(),isEnabled(),alphaScale));
    ofxRect(0, 0, getHitBoxWidth(),getHitBoxHeight());
    
    /*
    ofNoFill();
    ofSetColor(cActiveAreaFrame.get(mouseOver,mouseDown,isEnabled(),alphaScale));
    ofxRect(0, 0, hitBox.width, hitBox.height);
    */
    
    ofPopMatrix();
    ofPopStyle();
    
}

//--------------------------------------------------------------
void ofxMuiNumberBox::keyBind_increaseValue(int key) {
    //setKeyMap(key,bind(&ofxMuiNumberBox::increment, ref(*this))); 
}

//--------------------------------------------------------------
void ofxMuiNumberBox::keyBind_decreaseValue(int key) {
    //setKeyMap(key,bind(&ofxMuiNumberBox::decrement, ref(*this))); 
}

//--------------------------------------------------------------
void ofxMuiNumberBox::loadFromXml(ofxXmlSettings& xml) {}

//--------------------------------------------------------------
void ofxMuiNumberBox::saveToXml(ofxXmlSettings& xml) {}

//--------------------------------------------------------------
void ofxMuiNumberBox::onPress() {
    numPosition = valueLabel->getCursorPosition();
}

//--------------------------------------------------------------
void ofxMuiNumberBox::onDrag() {
    add(getDragDigit() * (pMousePosition.y - mousePosition.y));
}

//--------------------------------------------------------------
float ofxMuiNumberBox::getDragDigit() {

    //cout << numPosition << "<<UMPO" << endl;
    
    int found=(int)valueLabel->getDisplayText().find('.');
    if (found!=string::npos) {
        int offset = numPosition - found;
        if(offset < 0) {
            return 1.0f;
        } else {
            return 1.0f / pow(10.0f, offset);
        }
    } else {
        return 1.0f;
    }

}

//--------------------------------------------------------------
void ofxMuiNumberBox::doContentBoxLayout() {
    // TODO: handle the case where the label is EMPTY
    
    // vertical ofxMuiLabelCaps
    if(label->getHeight() > getHitBoxHeight()) {
        setContentBoxHeight(label->getHeight());
        setHitBoxY((label->getHeight() - getHitBoxHeight())/2.0);
        label->setY(0);
    } else {
        setContentBoxHeight(getHitBoxHeight());
        label->setY(roundInt((getHitBoxHeight() - label->getHeight())/2.0));
        setHitBoxY(0);
    }
    
    // label to the right
    label->setX(getHitBoxWidth()); // label to the right
    setHitBoxX(0);
    
    // value label placement
    valueLabel->setX(getHitBoxX());
    valueLabel->setY(getHitBoxY() + getHitBoxHeight()/2.0f - valueLabel->getHeight() / 2.0f);
    
    // TODO: this doesn't account for auto widths ...
    setContentBoxWidth(getHitBoxWidth() + label->getWidth());
}



