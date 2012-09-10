//
//  ofxMuiLabelledObject.h
//  BasicExample
//
//  Created by Christopher Baker on 7/25/11.
//  Copyright 2011 School of the Art Institute of Chicago. All rights reserved.
//

#pragma once 

#include "ofxMuiObject.h"
#include "ofxMuiLabel.h"

//--------------------------------------------------------------
class ofxMuiLabelledObject : public ofxMuiObject {
public:
    
    ofxMuiLabelledObject(string _name, int _x, int _y, int _width, int _height, bool _enabled = true);
    ofxMuiLabelledObject(string _name, int _x, int _y,bool _enabled = true);
    ofxMuiLabelledObject(string _name, bool _enabled = true);
    ofxMuiLabelledObject(bool _enabled = true);
    virtual ~ofxMuiLabelledObject();
    
    ofxMuiLabel* getValueLabel(); // the internal value label
    ofxMuiLabel* getLabel();      // the label describing the value
    
    void disableLabels();
    void enableLabels();
    
    void enableValueLabel();
    void enableLabel();

    void disableValueLabel();
    void disableLabel();
    
    void setLabelPositionHorz(const ofAlignHorz& hPos);
    void setLabelPositionVert(const ofAlignVert& vPos);

    void setValueLabelPositionHorz(const ofAlignHorz& hPos);
    void setValueLabelPositionVert(const ofAlignVert& vPos);

    ofAlignHorz getLabelPositionHorz() const;
    ofAlignVert getLabelPositionVert() const;
    
    ofAlignHorz getValueLabelPositionHorz() const;
    ofAlignVert getValueLabelPositionVert() const;
    
protected:
    void init();
    ofxMuiLabel* label;      // the label describing the value
    ofxMuiLabel* valueLabel; // the internal value label
    
    ofAlignHorz labelPositionHorz;
    ofAlignVert labelPositionVert;
    
    ofAlignHorz valueLabelPositionHorz;
    ofAlignVert valueLabelPositionVert;
        
};

