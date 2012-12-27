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

