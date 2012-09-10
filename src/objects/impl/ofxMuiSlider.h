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

#include "ofxMuiLabelledObject.h"
#include "ofxMuiNumberData.h"

//--------------------------------------------------------------
class ofxMuiSlider : public ofxMuiLabelledObject, public ofxMuiNumberData {
public:

    ofxMuiSlider(const string& _name, int _x, int _y, int _width, int _height, bool _enabled = true);
    ofxMuiSlider(const string& _name, int _x, int _y,bool _enabled = true);
    ofxMuiSlider(const string& _name, bool _enabled = true);
    ofxMuiSlider(bool _enabled = true);
    virtual ~ofxMuiSlider();

    //--------------------------------------------------------------
    // INHERITED FROM SUPERCLASS ///////////////////////////////////
    //--------------------------------------------------------------

    void update();
    void draw();

    //--------------------------------------------------------------
    // PERSISTENCE /////////////////////////////////////////////////
    //--------------------------------------------------------------

    void loadFromXml(ofxXmlSettings& xml);
    void saveToXml(ofxXmlSettings& xml);
    
    //--------------------------------------------------------------
    // KEYBINDING //////////////////////////////////////////////////
    //--------------------------------------------------------------

    void keyBind_increaseValue(int key);
    void keyBind_decreaseValue(int key);

    //--------------------------------------------------------------
    // GETTERS AND SETTERS /////////////////////////////////////////
    //--------------------------------------------------------------
    
    int  getSliderWidth() const;
    void setSliderWidth(int _width);
    
    int  getSliderHeight() const;
    void setSliderHeight(int _height);
    
    ofOrientation getOrientation() const;
    void setOrientation(const ofOrientation& _orientation);
        
protected:

    void init();
    void dataChanged();
    
    float toNormalizedValue(ofVec2f pos);
        
    //--------------------------------------------------------------
    // INHERITED FROM SUPERCLASS ///////////////////////////////////
    //--------------------------------------------------------------
    
    void onRollOver();
    void onRollOut();
    
    void onMouseMove();
    
    void onPress();
    void onDoublePress();
    void onDrag();
    
    void doContentBoxLayout();

    //--------------------------------------------------------------
    // LOCAL HELPER FUNCTIONS //////////////////////////////////////
    //--------------------------------------------------------------
    
    //--------------------------------------------------------------
    // VARIABLES ///////////////////////////////////////////////////
    //--------------------------------------------------------------
        
    //--------------------------------------------------------------
    // EVENTS //////////////////////////////////////////////////////
    //--------------------------------------------------------------

    float normCtrlDragStartMin;
    float normCtrlDragStartMax;
    
    ofEvent<float> ofxMuiSliderEvent;

    
};

//--------------------------------------------------------------

