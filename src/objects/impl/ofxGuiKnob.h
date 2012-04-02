
#pragma once 

#include "ofxGuiLabelledObject.h"
#include "ofxGuiNumberData.h"

//--------------------------------------------------------------
class ofxGuiKnob : public ofxGuiLabelledObject, public ofxGuiNumberData {
public:

    ofxGuiKnob(string _name, int _x, int _y, int _width, int _height, bool _enabled = true);
    ofxGuiKnob(string _name, int _x, int _y,bool _enabled = true);
    ofxGuiKnob(string _name, bool _enabled = true);
    ofxGuiKnob(bool _enabled = true);
    virtual ~ofxGuiKnob();

    //--------------------------------------------------------------
    // INHERITED FROM SUPERCLASS ///////////////////////////////////
    //--------------------------------------------------------------

    void update();
    void draw();

    //--------------------------------------------------------------
    // PERSISTENCE /////////////////////////////////////////////////
    //--------------------------------------------------------------

    void buildFromXml();
    void saveToXml();
    
    //--------------------------------------------------------------
    // KEYBINDING //////////////////////////////////////////////////
    //--------------------------------------------------------------

    void keyBind_increaseValue(int key);
    void keyBind_decreaseValue(int key);

    //--------------------------------------------------------------
    // GETTERS AND SETTERS /////////////////////////////////////////
    //--------------------------------------------------------------
    
    bool getSmartRotate();
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
    
    ofEvent<float> ofxGuiKnobEvent;

    
};

//--------------------------------------------------------------

