#include "ofxGuiColorData.h"

//--------------------------------------------------------------
ofxGuiColorData::ofxGuiColorData() {

}

//--------------------------------------------------------------
ofxGuiColorData::ofxGuiColorData(ofColor _value) {
    
}

//--------------------------------------------------------------
ofxGuiColorData::~ofxGuiColorData() {

};

//--------------------------------------------------------------
ofColor ofxGuiColorData::getValue(int index) { 
    return value; 
}

//--------------------------------------------------------------
void setValue(ofColor _val) { 

    value = _val; dataChanged();

}

//--------------------------------------------------------------
string toString() {
    
    string s;
    s+= "A:" + ofToString((int)value.a) + " "; 
    s+= "R:" + ofToString((int)value.r) + " "; 
    s+= "G:" + ofToString((int)value.g) + " "; 
    s+= "B:" + ofToString((int)value.b); 
    
    return s;
}
