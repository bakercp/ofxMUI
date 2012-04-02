//
//  ofxGuiLabelledObject.h
//  BasicExample
//
//  Created by Christopher Baker on 7/25/11.
//  Copyright 2011 School of the Art Institute of Chicago. All rights reserved.
//

#pragma once 

#include "ofxGuiObject.h"
#include "ofxGuiLabel.h"

//--------------------------------------------------------------
class ofxGuiLabelledObject : public ofxGuiObject {
public:
    
    ofxGuiLabelledObject(string _name, int _x, int _y, int _width, int _height, bool _enabled = true);
    ofxGuiLabelledObject(string _name, int _x, int _y,bool _enabled = true);
    ofxGuiLabelledObject(string _name, bool _enabled = true);
    ofxGuiLabelledObject(bool _enabled = true);
    virtual ~ofxGuiLabelledObject();
    
    ofxGuiLabel* getValueLabel(); // the internal value label
    ofxGuiLabel* getLabel();      // the label describing the value
    
    void disableLabels();
    void enableLabels();
    
    void enableValueLabel();
    void enableLabel();

    void disableValueLabel();
    void disableLabel();
    
    void setLabelPosition(ofxGuiAlign pos);
    void setValueLabelPosition(ofxGuiAlign pos);

    ofxGuiAlign getLabelPosition();
    ofxGuiAlign getValueLabelPosition();
    
protected:
    void init();
    ofxGuiLabel* label;      // the label describing the value
    ofxGuiLabel* valueLabel; // the internal value label
    
    ofxGuiAlign labelPosition;
    ofxGuiAlign valueLabelPosition;
    
};

