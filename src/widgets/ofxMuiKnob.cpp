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

#include "ofxMuiKnob.h"

//--------------------------------------------------------------
ofxMuiKnob::ofxMuiKnob(const string& _name, int _x, int _y, int _width, int _height, bool _enabled) : 
    ofxMuiLabelledObject(_name, _x, _y, _width, _height, _enabled),
    ofxMuiNumberData() {
    init();
}

//--------------------------------------------------------------
ofxMuiKnob::ofxMuiKnob(const string& _name, int _x, int _y,bool _enabled) : 
    ofxMuiLabelledObject(_name, _x, _y, _enabled),
    ofxMuiNumberData() {
    init();
}

//--------------------------------------------------------------
ofxMuiKnob::ofxMuiKnob(const string& _name,bool _enabled) :
    ofxMuiLabelledObject(_name, _enabled),
    ofxMuiNumberData() {
    init();
}

//--------------------------------------------------------------
ofxMuiKnob::ofxMuiKnob(bool _enabled) : 
    ofxMuiLabelledObject(_enabled),
    ofxMuiNumberData() {
    init();
}

//--------------------------------------------------------------
ofxMuiKnob::~ofxMuiKnob() {
}

//--------------------------------------------------------------
void ofxMuiKnob::init() {

    setObjectType("KNOB");

    setHitBoxWidth(defaults->knobWidth);
    setHitBoxHeight(defaults->knobHeight);
    
	// set default key binding
    keyBind_increaseValue('=');
    keyBind_decreaseValue('-');

    setBoxProperties(defaults->knobBoxProperties);
    
    // set values
    setValue(0);
    //setBoundsMin(0.0f);
    //setBoundsMax(1.0f);
    
    //valueLabel->d();
    label->enable();
    
    lastKnobAngle = 0.0f;
    knobAngle = 0.0f;
    dKnobAngle = 0.0f;
    
    zeroAngle = HALF_PI; // up
    
    boundaryWedgeAngle = PI/4.0f;
    
    innerRadiusPct = 0.60f;
    outerRadiusPct = 1.00f;
    
    innerRadiusW = getHitBoxHalfWidth() * innerRadiusPct;
    outerRadiusW = getHitBoxHalfWidth() * outerRadiusPct;
    innerRadiusH = getHitBoxHalfHeight() * innerRadiusPct;
    outerRadiusH = getHitBoxHalfHeight() * outerRadiusPct;
    
    float b = innerRadiusW;
    float v = b / 6.0f;
    dialArrow.moveTo(0,-v);
    dialArrow.lineTo(b,0);
    dialArrow.lineTo(0,+v);
    dialArrow.close();
    dialArrow.setFilled(false);
    
    dialShape.setArcResolution(360);
    dialRangeShape.setArcResolution(360);
    dialValueShape.setArcResolution(360);

    needsRedraw = true;
    
    
    normCtrlDragStartMin = 0.0f;
    normCtrlDragStartMax = 0.0f;
    totalDragDelta = ofPoint(0.0f,0.0f);
    
    dKnobScaler = 0.01f;
    
    smartRotate = false;
    smoothedCenter = getHitBoxCenter();
    smoothedCenterAlpha = 0.95;
    
    requestBoxLayout();
}

//--------------------------------------------------------------
void ofxMuiKnob::dataChanged(int index) {
    needsRedraw = true; // if data changed, then get a redraw (this doesn't account for range/bounds changes ...)
    float v = getValue(); // gotta get a copy, 'cause it's private!
    ofNotifyEvent(ofxMuiKnobEvent, v, this);
}

//--------------------------------------------------------------
void ofxMuiKnob::rangeChanged(int index) {
    needsRedraw = true; // if data changed, then get a redraw (this doesn't account for range/bounds changes ...)
   // cout << "range changed index=" << index << endl;
}

//--------------------------------------------------------------
void ofxMuiKnob::boundsChanged(int index) {
    needsRedraw = true; // if data changed, then get a redraw (this doesn't account for range/bounds changes ...)
   // cout << "bounds changed index=" << index << endl;
}


//--------------------------------------------------------------
void ofxMuiKnob::update() {
//    tooltip = toString();
//    valueLabel->setText(tooltip);
//    valueLabel->setTooltip(tooltip);
//        
    if(needsRedraw) { // dial shape needs update due to data change
        
        cout << "here" << endl;
        
        if(getBounds().isBounded()) {
            
            innerRadiusW = getHitBoxHalfWidth() * innerRadiusPct;
            outerRadiusW = getHitBoxHalfWidth() * outerRadiusPct;
            innerRadiusH = getHitBoxHalfHeight() * innerRadiusPct;
            outerRadiusH = getHitBoxHalfHeight() * outerRadiusPct;
            
            angleBounds0 = ofRadToDeg(normalizedValueToAngle(0.0f));
            angleBounds1 = ofRadToDeg(normalizedValueToAngle(1.0f));
            
            angleValue0 = angleBounds0;
            angleValue1 = ofRadToDeg(normalizedValueToAngle(getNormalizedValue()));

            dialShape.clear();
            dialShape.arc(0,0,outerRadiusW,outerRadiusH,angleBounds0,angleBounds1);
            dialShape.arcNegative(0,0,innerRadiusW,innerRadiusH,angleBounds1,angleBounds0);
            dialShape.close();
            
            
            if(getRange().isBounded()) {
                
                angleRange0 = ofRadToDeg(normalizedValueToAngle(getNormalizedRangeMin()));
                angleRange1 = ofRadToDeg(normalizedValueToAngle(getNormalizedRangeMax()));

                angleValue0 = angleRange0; // reset it if this is active
                
                dialRangeShape.clear();
                dialRangeShape.arc(0,0,outerRadiusW,outerRadiusH,angleRange0,angleRange1);
                dialRangeShape.arcNegative(0,0,innerRadiusW,innerRadiusH,angleRange1,angleRange0);
                dialRangeShape.close();
            }
            
            //
            dialValueShape.clear();
            dialValueShape.arc(0,0,outerRadiusW,outerRadiusH,angleValue0,angleValue1);
            dialValueShape.arcNegative(0,0,innerRadiusW,innerRadiusH,angleValue1,angleValue0);
            dialValueShape.close();
            
            
        } else {
            // nothing to draw
        }
        needsRedraw = false;
    }
     
    
    
}

//--------------------------------------------------------------
void ofxMuiKnob::draw() {
    
    // pre calculate colors for reuse
    ofColor activeAreaBackground = cActiveAreaBackground.get(isTouchOver(),isTouchDown(),isEnabled(),alphaScale);
    ofColor activeAreaFrame = cActiveAreaFrame.get(isTouchOver(),isTouchDown(),isEnabled(),alphaScale);
    ofColor activeForeground = cActiveAreaForeground.get(isTouchOver(),isTouchDown(),isEnabled(),alphaScale);
    ofEnableAlphaBlending();
    
    ofPushStyle();
    ofPushMatrix();
    
    ofTranslate(getHitBoxPosition());

    ofPushMatrix();
    ofTranslate(getHitBoxCenter());
    ofRotateZ(ofRadToDeg(zeroAngle));

    ofFill();
    ofSetColor(activeAreaBackground);
    ofEllipse(0,0,innerRadiusW*2.0f,innerRadiusH*2.0f);
    
    // draw a little arrow
    ofNoFill();
    ofPushMatrix();
    ofRotateZ(ofRadToDeg(knobAngle));
    dialArrow.setStrokeColor(activeAreaFrame);
    dialArrow.draw(0,0);
    ofPopMatrix();
    
    
    dialRangeShape.setFillColor(activeAreaBackground);
    dialRangeShape.setFilled(true);
    dialRangeShape.draw(0,0);

    
    dialValueShape.setFillColor(activeForeground);
    dialValueShape.setFilled(true);
    dialValueShape.draw(0,0);

    dialShape.setStrokeColor(activeAreaFrame);
    dialShape.setFilled(false);
    dialShape.draw(0,0);
    
    ofSetColor(activeAreaFrame);
    ofNoFill();
    
    ofPushMatrix();
    ofRotateZ(angleValue0);
    ofLine(innerRadiusW,0,outerRadiusH,0);
    ofPopMatrix();
    
    ofPushMatrix();
    ofRotateZ(angleValue1);
    ofLine(innerRadiusW,0,outerRadiusH,0);
    ofPopMatrix();

    ofPushMatrix();
    ofRotateZ(angleRange1);
    ofLine(innerRadiusW,0,outerRadiusH,0);
    ofPopMatrix();
    
    if(getBounds().isBounded()) {
    } else {
    }
    
    
    ofDisableAlphaBlending();

    
    ofPopMatrix();
    
       
    ofPopMatrix();
    ofPopStyle();
    
}

//--------------------------------------------------------------
float ofxMuiKnob::getKnobAngle() {
    return knobAngle;
}
//--------------------------------------------------------------
float ofxMuiKnob::getLastKnobAngle() {
    return lastKnobAngle;
}

//--------------------------------------------------------------
float ofxMuiKnob::getNormalizedKnobPosition() {
    return ofNormalize(getKnobAngle(),boundaryWedgeAngle*0.5f,2*PI-boundaryWedgeAngle*0.5f);
}

//--------------------------------------------------------------
float ofxMuiKnob::getLastNormalizedKnobPosition() {
    return ofNormalize(getLastKnobAngle(),boundaryWedgeAngle*0.5f,2*PI-boundaryWedgeAngle*0.5f);
}

//--------------------------------------------------------------
float ofxMuiKnob::smallestAngleDelta(float angle0, float angle1) {
    float d = angle0 - angle1;
    return atan2(sin(d),cos(d)); // positive is in the clockwise direction
}

//--------------------------------------------------------------
float ofxMuiKnob::largestAngleDelta(float angle0, float angle1) {
    return 2*PI - smallestAngleDelta(angle0,angle1); // positive is in the clockwise direction
}

//--------------------------------------------------------------
float ofxMuiKnob::normalizedValueToAngle(float value) {
    return ofLerp(boundaryWedgeAngle*0.5f,2*PI-boundaryWedgeAngle*0.5f,value);
}

//--------------------------------------------------------------
void ofxMuiKnob::keyBind_increaseValue(int key) {
    //setKeyMap(key,bind(&ofxMuiKnob::increment, ref(*this))); 
}

//--------------------------------------------------------------
void ofxMuiKnob::keyBind_decreaseValue(int key) {
    //setKeyMap(key,bind(&ofxMuiKnob::decrement, ref(*this))); 
}

//--------------------------------------------------------------
bool ofxMuiKnob::getSmartRotate() const {
    return smartRotate;
}

//--------------------------------------------------------------
void ofxMuiKnob::setSmartRotate(bool v) {
    smartRotate = v;
}

//--------------------------------------------------------------
void ofxMuiKnob::loadFromXml(ofxXmlSettings& xml) {}

//--------------------------------------------------------------
void ofxMuiKnob::saveToXml(ofxXmlSettings& xml) {}

//--------------------------------------------------------------
void ofxMuiKnob::onPress() {
    registerMousePosition(mousePosition);

    float nv = getNormalizedKnobPosition();
    
    if(getBounds().isBounded()) {
        
        if(isRangeEnabled() && isShiftPressed()) {
            if(isCtrlPressed()) {
                setRightOrLeftRangeLimit(nv);
            } else {
                setClosestRangeLimit(nv);
            }
        } else if(isRangeEnabled() && isCtrlPressed()) {
            normCtrlDragStartMin = getNormalizedRangeMin();
            normCtrlDragStartMax = getNormalizedRangeMax();
        } else {
            setNormalizedValue(nv);
        }
    } else {
        //setNormalizedValue(nv);
        ofVec2f v = screenToHitBox(mousePosition);
        float d = v.distance(getHitBoxCenter());
        float ds = ofNormalize(d,0,getHitBoxWidth()*2.0f) * 10.0f;
        
        add(ds*dKnobScaler*dKnobAngle);
    }

}

//--------------------------------------------------------------
void ofxMuiKnob::onRelease() {
    smoothedCenter = getHitBoxCenter();
}

//--------------------------------------------------------------
void ofxMuiKnob::onDrag() {
    registerMousePosition(mousePosition);
    
    float nv = getNormalizedKnobPosition();
    
    cout << "nv=" << nv << endl;
    
    if(getBounds().isBounded()) {
        if(isRangeEnabled() && isShiftPressed()) {
            if(isCtrlPressed()) {
                setRightOrLeftRangeLimit(nv);
            } else {
                setClosestRangeLimit(nv);
            }
        } else if(isRangeEnabled() && isCtrlPressed()) {
            normCtrlDragStartMin = getNormalizedRangeMin();
            normCtrlDragStartMax = getNormalizedRangeMax();
        } else {
            setNormalizedValue(nv);
        }

        /*
        if(isRangeEnabled() && isShiftPressed()) {
            setClosestRangeLimit(nv);
        } else if(isRangeEnabled() && isCtrlPressed()) {
            // TODO -- fix this
            // TODO -- quick angle change problem
            
            float normDx = 
            fabs(smallestAngleDelta(normCtrlDragStartMin, normCtrlDragStartMax) )/ (2 * PI - boundaryWedgeAngle);
            setNormalizedRangeMin(ofClamp(normCtrlDragStartMin + normDx,0,1));
            setNormalizedRangeMax(ofClamp(normCtrlDragStartMax + normDx,0,1));
        } else {
            //setNormalizedValue(nv);
            ofVec2f v = screenToHitBox(mousePosition);
            float d = v.distance(getHitBoxCenter());
            float ds = ofNormalize(d,0,getHitBoxWidth()*2.0f) * 10.0f;
        
            add(ds*dKnobScaler*getBounds().delta()*dKnobAngle);
        }
         */
    } else {
        //setNormalizedValue(nv);
        //ofVec2f v = screenToHitBox(mousePosition);
        //float d = v.distance(ofVec2f(getHitBoxWidth()*0.5f,getHitBoxHeight()*0.5f));
        float ds =  1;//ofNormalize(d,0,getHitBoxWidth()*2.0f) * 10.0f;
        
        add(ds*dKnobScaler*dKnobAngle);
        
        
        cout << getValue() << endl;
    }
}


//--------------------------------------------------------------
void ofxMuiKnob::registerMousePosition(ofVec2f mousePoint) {
    lastKnobAngle = knobAngle;
    knobAngle = calculateKnobPosition(screenToHitBox(mousePoint));
    dKnobAngle = smallestAngleDelta(knobAngle, lastKnobAngle);
}


//--------------------------------------------------------------
float ofxMuiKnob::calculateKnobPosition(ofVec2f v) {
    // center the coords to rotate around the center
    ofPoint knobCenter;
    
    if(smartRotate && localHitTest(v.x,v.y)) {
        // smooth center
        smoothedCenter.x = smoothedCenterAlpha * smoothedCenter.x + (1-smoothedCenterAlpha) * v.x;
        smoothedCenter.y = smoothedCenterAlpha * smoothedCenter.y + (1-smoothedCenterAlpha) * v.y;
        // smooth center
        knobCenter.x = v.x - smoothedCenter.x;
        knobCenter.y = v.y - smoothedCenter.y;
    } else {
        knobCenter = v - getHitBoxCenter();
    }
    
    float t = atan2(knobCenter.y, knobCenter.x) - zeroAngle;
    t = t > 0 ? t : M_TWO_PI + t;
    
    return t;
}

//--------------------------------------------------------------
bool ofxMuiKnob::hitTest(float screenX, float screenY) { 
    // this function could be overriden w/ via the virtual declaration
    // hitRect is always described in with respect to the content frame 
    ofVec2f hitBoxMousePos = screenToHitBox(ofVec2f(screenX, screenY));
    return localHitTest(hitBoxMousePos.x, hitBoxMousePos.y);
}

//--------------------------------------------------------------
bool ofxMuiKnob::localHitTest(float localX, float localY) {
    // Normalize the coordinates compared to the ellipse
    // having a center at 0,0 and a radius of 0.5.
    // via Java Ellipse2D
    float ellw = getHitBoxWidth();
    if (ellw <= 0.0) return false;
    float normx = (localX - getHitBoxX()) / ellw - 0.5f;
    float ellh = getHitBoxHeight();
    if (ellh <= 0.0) return false;
    float normy = (localY - getHitBoxY()) / ellh - 0.5f;
    return (normx * normx + normy * normy) < 0.25f;
}


//--------------------------------------------------------------
void ofxMuiKnob::doContentBoxLayout() {
    
    // TODO: handle the case where the label is EMPTY
    
    
    // vertical ofxMuiLabelCaps
    if(label->getHeight() > getHitBoxHeight()) {
        setContentBoxHeight(label->getHeight());
        setHitBoxY((label->getHeight() - getHitBoxHeight())/2.0);
        label->setY(0);
    } else {
        setContentBoxHeight(getHitBoxHeight());
        label->setY((getHitBoxHeight() - label->getHeight())/2.0);
        setHitBoxY(0);
    }
    
    
    // label to the right
    label->setX(getHitBoxWidth()); // label to the right
    setHitBoxX(0);

    // value label placement
    valueLabel->setX(getHitBoxX());
    
    valueLabel->setY(getHitBoxY() + (getHitBoxHeight() - valueLabel->getHeight())/2.0);
    
    // TODO: this doesn't account for auto widths ...
    setContentBoxWidth(getHitBoxWidth() + label->getWidth());

}


//--------------------------------------------------------------
void ofxMuiKnob::onDoublePress() {
    if(isCtrlPressed()) {
        setNormalizedRangeMin(0);
        setNormalizedRangeMax(1);
    }
}

