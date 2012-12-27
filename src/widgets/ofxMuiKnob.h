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
class ofxMuiKnob : public ofxMuiLabelledObject, public ofxMuiNumberData {
public:

    ofxMuiKnob(const string& _name, int _x, int _y, int _width, int _height, bool _enabled = true);
    ofxMuiKnob(const string& _name, int _x, int _y,bool _enabled = true);
    ofxMuiKnob(const string& _name, bool _enabled = true);
    ofxMuiKnob(bool _enabled = true);
    virtual ~ofxMuiKnob();

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
    
    bool getSmartRotate() const;
    void setSmartRotate(bool v);
    
protected:

    void init();
    void dataChanged(int index);
    void boundsChanged(int index);
    void rangeChanged(int index);
    
    float calculateKnobPosition(ofVec2f v);
    
    float getKnobAngle();
    float getLastKnobAngle();
    
    float getNormalizedKnobPosition();
    float getLastNormalizedKnobPosition();
    
    float smallestAngleDelta(float angle0, float angle1);
    float largestAngleDelta(float angle0, float angle1);
    
    float normalizedValueToAngle(float value);
    
    //--------------------------------------------------------------
    // INHERITED FROM SUPERCLASS ///////////////////////////////////
    //--------------------------------------------------------------
    
    void onPress();
    void onRelease();
    void onDrag();		
    void onDoublePress();
    
    void doContentBoxLayout();
    
    // @OVERRIDE for round shapes
    bool hitTest(float screenX, float screenY);
    
    bool localHitTest(float localX, float localY);
    
    //--------------------------------------------------------------
    // VARIABLES ///////////////////////////////////////////////////
    //--------------------------------------------------------------
    
    void registerMousePosition(ofVec2f mousePoint);

    float lastKnobAngle; // 0-2_PI
    float knobAngle;     // 0-2_PI
    float dKnobAngle;
    float dKnobScaler;

    // code to allow for a non-centered dragging rotation
    bool smartRotate;
    ofPoint smoothedCenter;
    float smoothedCenterAlpha;
    
    float boundaryWedgeAngle;
    
    float zeroAngle;
    
    float innerRadiusPct;
    float outerRadiusPct;

    float innerRadiusH;
    float outerRadiusH;
    float innerRadiusW;
    float outerRadiusW;
    
    float angleBounds0,angleBounds1;
    float angleValue0, angleValue1;
    float angleRange0, angleRange1;
    
    
    bool needsRedraw;
    
    float normCtrlDragStartMin;
    float normCtrlDragStartMax;
    
    ofPath dialShape;
    ofPath dialRangeShape;
    ofPath dialValueShape;
    ofPath dialArrow;
    
    
    //--------------------------------------------------------------
    // EVENTS //////////////////////////////////////////////////////
    //--------------------------------------------------------------
    
    ofEvent<float> ofxMuiKnobEvent;

    
};

//--------------------------------------------------------------

