#pragma once

#include "ofMain.h"
#include "ofxGuiData.h"

class ofxGuiColorData : ofxGuiData {
public:
    ofxGuiColorData() : value(ofColor(0)) {}
    ofxGuiColorData(ofColor _value) : value(_value) {}
    ~ofxGuiColorData() {};
    ofColor getValue() { return value; }
    void setValue(ofColor _val) { value = _val; dataChanged();}
    
    string toString() {
        
        string s;
        s+= "A:" + ofToString((int)value.a) + " "; 
        s+= "R:" + ofToString((int)value.r) + " "; 
        s+= "G:" + ofToString((int)value.g) + " "; 
        s+= "B:" + ofToString((int)value.b); 
        
        return s;
    }
    
protected:
    vector<ofColor> values;
};
