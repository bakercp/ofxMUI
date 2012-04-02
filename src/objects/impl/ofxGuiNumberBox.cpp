
#include "ofxGuiNumberBox.h"


//--------------------------------------------------------------
ofxGuiNumberBox::ofxGuiNumberBox(string _name, int _x, int _y, int _width, int _height, bool _enabled) : 
ofxGuiLabelledObject(_name, _x, _y, _width, _height, _enabled),
ofxGuiNumberData() {
    init();
}

//--------------------------------------------------------------
ofxGuiNumberBox::ofxGuiNumberBox(string _name, int _x, int _y,bool _enabled) : 
ofxGuiLabelledObject(_name, _x, _y, _enabled),
ofxGuiNumberData() {
    init();
}

//--------------------------------------------------------------
ofxGuiNumberBox::ofxGuiNumberBox(string _name,bool _enabled) :
ofxGuiLabelledObject(_name, _enabled),
ofxGuiNumberData() {
    init();
}

//--------------------------------------------------------------
ofxGuiNumberBox::ofxGuiNumberBox(bool _enabled) : 
ofxGuiLabelledObject(_enabled),
ofxGuiNumberData() {
    init();
}

//--------------------------------------------------------------
ofxGuiNumberBox::~ofxGuiNumberBox() {
}

//--------------------------------------------------------------
void ofxGuiNumberBox::init() {

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
void ofxGuiNumberBox::update() {
    tooltip = toString();
    valueLabel->setText(tooltip);
    valueLabel->setTooltip(tooltip);
}

//--------------------------------------------------------------
void ofxGuiNumberBox::draw() {
    
    ofPushStyle();
    ofPushMatrix();
    
    ofTranslate(getHitBoxPosition());
    
    //--------- DRAW THE BUTTON BACKGROUND
    // default
    ofFill();

    ofSetColor(cActiveAreaForeground.get(isMouseOver(),isMouseDown(),isEnabled(),alphaScale));
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
void ofxGuiNumberBox::keyBind_increaseValue(int key) {
    //setKeyMap(key,bind(&ofxGuiNumberBox::increment, ref(*this))); 
}

//--------------------------------------------------------------
void ofxGuiNumberBox::keyBind_decreaseValue(int key) {
    //setKeyMap(key,bind(&ofxGuiNumberBox::decrement, ref(*this))); 
}

//--------------------------------------------------------------
void ofxGuiNumberBox::buildFromXml() {}

//--------------------------------------------------------------
void ofxGuiNumberBox::saveToXml() {}

//--------------------------------------------------------------
void ofxGuiNumberBox::onPress() {
    numPosition = valueLabel->getCursorPosition();
}

//--------------------------------------------------------------
void ofxGuiNumberBox::onDrag() {
    add(getDragDigit() * (pMousePosition.y - mousePosition.y));
}

//--------------------------------------------------------------
float ofxGuiNumberBox::getDragDigit() {

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
void ofxGuiNumberBox::doContentBoxLayout() {
    // TODO: handle the case where the label is EMPTY
    
    // vertical ofxGuiLabelCaps
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



