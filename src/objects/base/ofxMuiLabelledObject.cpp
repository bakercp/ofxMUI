

#include "ofxMuiLabelledObject.h"

//--------------------------------------------------------------
ofxMuiLabelledObject::ofxMuiLabelledObject(string _name, int _x, int _y, int _width, int _height, bool _enabled) : 
ofxMuiObject(_name, _x, _y, _width, _height, _enabled) {
    init();
}

//--------------------------------------------------------------
ofxMuiLabelledObject::ofxMuiLabelledObject(string _name, int _x, int _y,bool _enabled) : 
ofxMuiObject(_name, _x, _y, _enabled) {
    init();
}

//--------------------------------------------------------------
ofxMuiLabelledObject::ofxMuiLabelledObject(string _name,bool _enabled) :
ofxMuiObject(_name, _enabled) {
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
    label = new ofxMuiLabel(name);
    label->setBoxProperties(defaults->sharedLabelBoxProperties);
    label->setName("LABEL");
    label->setText("NULL");
    label->disable();
    
    valueLabel = new ofxMuiLabel();
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


