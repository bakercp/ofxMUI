

#include "ofxGuiLabelledObject.h"

//--------------------------------------------------------------
ofxGuiLabelledObject::ofxGuiLabelledObject(string _name, int _x, int _y, int _width, int _height, bool _enabled) : 
ofxGuiObject(_name, _x, _y, _width, _height, _enabled) {
    init();
}

//--------------------------------------------------------------
ofxGuiLabelledObject::ofxGuiLabelledObject(string _name, int _x, int _y,bool _enabled) : 
ofxGuiObject(_name, _x, _y, _enabled) {
    init();
}

//--------------------------------------------------------------
ofxGuiLabelledObject::ofxGuiLabelledObject(string _name,bool _enabled) :
ofxGuiObject(_name, _enabled) {
    init();
}

//--------------------------------------------------------------
ofxGuiLabelledObject::ofxGuiLabelledObject(bool _enabled) : 
ofxGuiObject(_enabled) {
    init();
}

//--------------------------------------------------------------
ofxGuiLabelledObject::~ofxGuiLabelledObject() {
    // TODO: shared poitners!!!!!
    removeChild(label);
    removeChild(valueLabel);
    delete label;
    delete valueLabel;
}

//--------------------------------------------------------------
void ofxGuiLabelledObject::init() {
    
    // add the labels
    label = new ofxGuiLabel(name);
    label->setBoxProperties(defaults->sharedLabelBoxProperties);
    label->setName("LABEL");
    label->setText("NULL");
    label->disable();
    
    valueLabel = new ofxGuiLabel();
    valueLabel->setBoxProperties(defaults->valueLabelBoxProperties);
    valueLabel->setName("VALUE LABEL");
    valueLabel->setText("NULL");
    valueLabel->disable();
    
    label->setIsMouseHandler(false);
    label->setIsKeyboardHandler(false);
    
    valueLabel->setIsMouseHandler(false);
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
ofxGuiLabel* ofxGuiLabelledObject::getValueLabel() {
    return valueLabel;
}

//--------------------------------------------------------------
ofxGuiLabel* ofxGuiLabelledObject::getLabel() {
    return label;
}

//--------------------------------------------------------------
void ofxGuiLabelledObject::disableLabels() {
    valueLabel->disable();
    label->disable();
    requestBoxLayout();
}

//--------------------------------------------------------------
void ofxGuiLabelledObject::enableLabels() {
    valueLabel->enable();
    label->enable();
    requestBoxLayout();
}

//--------------------------------------------------------------
void ofxGuiLabelledObject::enableValueLabel() {
    valueLabel->enable();
    requestBoxLayout();
}

//--------------------------------------------------------------
void ofxGuiLabelledObject::enableLabel() {
    label->enable();
    requestBoxLayout();
}

//--------------------------------------------------------------
void ofxGuiLabelledObject::disableValueLabel() {
    valueLabel->disable();
    requestBoxLayout();
}

//--------------------------------------------------------------
void ofxGuiLabelledObject::disableLabel() {
    label->disable();
    requestBoxLayout();
}

//--------------------------------------------------------------
void ofxGuiLabelledObject::setLabelPositionHorz(const ofAlignHorz& hPos) {
    labelPositionHorz = hPos;
    requestBoxLayout();
}

//--------------------------------------------------------------
void ofxGuiLabelledObject::setLabelPositionVert(const ofAlignVert& vPos) {
    labelPositionVert = vPos;
    requestBoxLayout();
}

//--------------------------------------------------------------
void ofxGuiLabelledObject::setValueLabelPositionHorz(const ofAlignHorz& hPos) {
    valueLabelPositionHorz = hPos;
    requestBoxLayout();
}

//--------------------------------------------------------------
void ofxGuiLabelledObject::setValueLabelPositionVert(const ofAlignVert& vPos) {
    valueLabelPositionVert = vPos;
    requestBoxLayout();
}

//--------------------------------------------------------------
ofAlignHorz ofxGuiLabelledObject::getLabelPositionHorz() const {
    return labelPositionHorz;
}

//--------------------------------------------------------------
ofAlignVert ofxGuiLabelledObject::getLabelPositionVert() const {
    return labelPositionVert;
}

//--------------------------------------------------------------
ofAlignHorz ofxGuiLabelledObject::getValueLabelPositionHorz() const {
    return valueLabelPositionHorz;
}

//--------------------------------------------------------------
ofAlignVert ofxGuiLabelledObject::getValueLabelPositionVert() const {
    return valueLabelPositionVert;
}


