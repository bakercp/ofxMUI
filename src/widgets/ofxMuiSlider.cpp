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

#include "ofxMuiSlider.h"

//--------------------------------------------------------------
ofxMuiSlider::ofxMuiSlider(const string& _name, int _x, int _y, int _width, int _height, bool _enabled) : 
    ofxMuiLabelledObject(_name, _x, _y, _width, _height, _enabled),
    ofxMuiNumberData() {
    init();
}

//--------------------------------------------------------------
ofxMuiSlider::ofxMuiSlider(const string& _name, int _x, int _y,bool _enabled) : 
    ofxMuiLabelledObject(_name, _x, _y, _enabled),
    ofxMuiNumberData() {
    init();
}

//--------------------------------------------------------------
ofxMuiSlider::ofxMuiSlider(const string& _name,bool _enabled) :
    ofxMuiLabelledObject(_name, _enabled),
    ofxMuiNumberData() {
    init();
}

//--------------------------------------------------------------
ofxMuiSlider::ofxMuiSlider(bool _enabled) : 
    ofxMuiLabelledObject(_enabled),
    ofxMuiNumberData() {
    init();
}

//--------------------------------------------------------------
ofxMuiSlider::~ofxMuiSlider() {
}

//--------------------------------------------------------------
void ofxMuiSlider::init() {

    setObjectType("SLIDER");
    setOrientation(defaults->sliderOrientation);
    setSliderWidth(defaults->sliderWidth);
    setSliderHeight(defaults->sliderHeight);

	// set default key binding
    keyBind_increaseValue(defaults->keyboardIncrease);
    keyBind_decreaseValue(defaults->keyboardDecrease);

    setBoxProperties(defaults->sliderBoxProperties);
    
    // set values
    setValue(0.5f);
    
    setBoundsMin(0.0f);
    setBoundsMax(1.0f);

    normCtrlDragStartMin = 0.0f;
    normCtrlDragStartMax = 1.0f;
    
//    label->setText(name);
    label->enable();
    
    valueLabel->setText("NULL");
    valueLabel->enable();
    valueLabel->show();

    requestBoxLayout();
    
}

//--------------------------------------------------------------
void ofxMuiSlider::dataChanged() {
    float v = getValue(); // gotta get a copy, b/c the value is private
    ofNotifyEvent(ofxMuiSliderEvent, v, this);
}

//--------------------------------------------------------------
void ofxMuiSlider::update() {
    
//    tooltip = toString();
//    valueLabel->setText(tooltip);
//    valueLabel->setTooltip(tooltip);
    //cout << "setting alhpa scale of label
    valueLabel->setAlphaScale(getActiveTimer()); // take care of fading

//    switch(orientation) {
//        case OF_ORIENTATION_UNKNOWN:
//        case OF_ORIENTATION_DEFAULT:	
//        case OF_ORIENTATION_180:
//            valueLabel->alignTo(getHitBox(),
//                                OF_ALIGN_HORZ_LEFT,
//                                OF_ALIGN_VERT_CENTER);
//            break;
//        case OF_ORIENTATION_90_RIGHT:
//        case OF_ORIENTATION_90_LEFT:
//            valueLabel->alignTo(getHitBox(),
//                                OF_ALIGN_HORZ_CENTER,
//                                OF_ALIGN_VERT_BOTTOM);
//            break;
//    }
}

//--------------------------------------------------------------
void ofxMuiSlider::draw() {
    
    float v = getNormalizedValue();

    float nMin = 0.0f;
    float nMax = 1.0f;
        
    if(isRangeEnabled()) {
        nMin = getBounds().normalize(getRangeMin());
        nMax = getBounds().normalize(getRangeMax());
    }

    ofPushStyle();
    ofPushMatrix();
  
    ofTranslate(getHitBoxPosition());
    
    if(isOrientationHorizontal()) {

        int pos = v * getHitBoxWidth();
        int  _x = getHitBoxWidth() * nMin;
        int  _w = getHitBoxWidth() * (nMax - nMin);
        int  vWidth = pos - _x;
        
        // background
        ofFill();
        ofSetColor(cActiveAreaBackground.get(isTouchOver(),isTouchDown(),isEnabled(),alphaScale));
        ofxRect(_x, 0, _w, getHitBoxHeight());
                    
        // the value
        ofSetColor(cActiveAreaForeground.get(isTouchOver(),isTouchDown(),isEnabled(),alphaScale));
        ofxRect(_x, 0, vWidth, getHitBoxHeight());
        
        // the 
        ofNoFill();
        ofSetColor(cActiveAreaFrame.get(isTouchOver(),isTouchDown(),isEnabled(),alphaScale));
        
        // range handles
        ofLine(_x, 0, _x, getHitBoxHeight());
        ofLine(_x + _w, 0, _x + _w, getHitBoxHeight());
        
        // the vertical line
        ofLine(pos, 0, pos, getHitBoxHeight());

    } else {
        
        
        int _pos = getHitBoxHeight() * v;
        int _min = getHitBoxHeight() * nMin;
        int _max = getHitBoxHeight() * nMax;
        
        // turn it upside-down
        int yPos = getHitBoxHeight() - _pos;
        int yMin = getHitBoxHeight() - _min;
        int yMax = getHitBoxHeight() - _max;
        
        int yRange = yMin - yMax;
        int yHeight = yMin - yPos;
        
        // background
        ofFill();
        ofSetColor(cActiveAreaBackground.get(isTouchOver(),isTouchDown(),isEnabled(),alphaScale));
        ofxRect(0, yMax, getHitBoxWidth(), yRange);
        
        // the value
        ofSetColor(cActiveAreaForeground.get(isTouchOver(),isTouchDown(),isEnabled(),alphaScale));
        ofxRect(0, yPos, getHitBoxWidth(), yHeight);
        
        // the 
        ofNoFill();
        ofSetColor(cActiveAreaFrame.get(isTouchOver(),isTouchDown(),isEnabled(),alphaScale));
        
        // range handles
        ofLine(0, yPos, getHitBoxWidth(), yPos);
        ofLine(0, yMin, getHitBoxWidth(), yMin);
        ofLine(0, yMax, getHitBoxWidth(), yMax);
        
    }
    
    ofNoFill();
    ofSetColor(cActiveAreaFrame.get(isTouchOver(),isTouchDown(),isEnabled(),alphaScale));
    ofRect(0, 0, getHitBoxWidth(), getHitBoxHeight() );
    
    ofPopMatrix();
    ofPopStyle();
    
}

//--------------------------------------------------------------
void ofxMuiSlider::keyBind_increaseValue(int key) {
    //setKeyMap(key,bind(&ofxMuiSlider::increment, ref(*this))); 
}

//--------------------------------------------------------------
void ofxMuiSlider::keyBind_decreaseValue(int key) {
    //setKeyMap(key,bind(&ofxMuiSlider::decrement, ref(*this))); 
}

//--------------------------------------------------------------
void ofxMuiSlider::loadFromXml(ofxXmlSettings& xml) {}

//--------------------------------------------------------------
void ofxMuiSlider::saveToXml(ofxXmlSettings& xml) {}

//--------------------------------------------------------------
void ofxMuiSlider::setOrientation(const ofOrientation& _orientation) {
    if(_orientation != orientation) {
        //cout << orientation << " ORIENTATION IS NOW " << name << endl; 
        int currentWidth = getHitBoxWidth();
        int currentHeight = getHitBoxHeight();
        // swap them
        setHitBoxWidth(currentHeight);
        setHitBoxHeight(currentWidth);
        orientation = _orientation;
        requestBoxLayout();
        
        label->setOrientation(orientation);
        valueLabel->setOrientation(orientation);
        
        if(isOrientationHorizontal()) {
            //label->setFlip(false);
            //valueLabel->setFlip(false);
            setLabelPositionHorz(OF_ALIGN_HORZ_RIGHT);
            setLabelPositionVert(OF_ALIGN_VERT_CENTER);
        } else {
            //label->setFlip(true);
            //valueLabel->setFlip(true);
            setLabelPositionHorz(OF_ALIGN_HORZ_CENTER);
            setLabelPositionVert(OF_ALIGN_VERT_TOP);
        }
    }
}

//--------------------------------------------------------------
void ofxMuiSlider::setSliderWidth(int _width) {
    setHitBoxWidth(_width);
    requestBoxLayout();
}

//--------------------------------------------------------------
ofOrientation ofxMuiSlider::getOrientation() const {
    return orientation;
}

//--------------------------------------------------------------
int ofxMuiSlider::getSliderWidth() const {
    return getHitBoxWidth();
}

//--------------------------------------------------------------
int ofxMuiSlider::getSliderHeight() const {
    return getHitBoxHeight();
}

//--------------------------------------------------------------
void ofxMuiSlider::setSliderHeight(int _height) {
    setHitBoxHeight(_height);
    requestBoxLayout();
}

//--------------------------------------------------------------
void ofxMuiSlider::onRollOver() {
    //valueLabel->show();
}
//--------------------------------------------------------------
void ofxMuiSlider::onRollOut() {
    //valueLabel->hide();
}

void ofxMuiSlider::onMouseMove() {
//    cout << "mouse moved!!" << endl;
}


//--------------------------------------------------------------
void ofxMuiSlider::onPress() {

    ofVec2f screenToHit= screenToHitBox(mousePosition);
    float nv = toNormalizedValue(screenToHit);

    if(!hitTest(mousePosition)) {
        return;   
    } 
    
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
    
    
    
}

//--------------------------------------------------------------
void ofxMuiSlider::onDoublePress() {
    if(isCtrlPressed()) {
        setNormalizedRangeMin(0.0f);
        setNormalizedRangeMax(1.0f);
    }
}


//--------------------------------------------------------------
void ofxMuiSlider::onDrag() {
    
    ofVec2f screenToHit= screenToHitBox(mousePosition);
    float nv = toNormalizedValue(screenToHit);

    // only drag 
    if(!isHitDragOrigin()) return; // prevents odd dragging situations
    
    if(isRangeEnabled() && isShiftPressed()) {
        setClosestRangeLimit(nv);
    
    } else if(isRangeEnabled() && isCtrlPressed()) {
        if(isOrientationHorizontal()) {
            float normDx = totalDragDelta.x / getHitBoxWidth();
            setNormalizedRangeMin(ofClamp(normCtrlDragStartMin + normDx,0.0f,1.0f));
            setNormalizedRangeMax(ofClamp(normCtrlDragStartMax + normDx,0.0f,1.0f));
        } else {
            float normDy = totalDragDelta.y / getHitBoxHeight();
            setNormalizedRangeMin(ofClamp(normCtrlDragStartMin - normDy,0.0f,1.0f));
            setNormalizedRangeMax(ofClamp(normCtrlDragStartMax - normDy,0.0f,1.0f));
        }
        
    } else {
        setNormalizedValue(nv);
    }
}


//--------------------------------------------------------------
float ofxMuiSlider::toNormalizedValue(ofVec2f v) {
    if(isOrientationHorizontal()) {
        return ofNormalize(v.x, 0.0f, getHitBoxWidth());
    } else {
        // invert to make bottom low, and top higher
        return 1.0f - ofNormalize(v.y, 0.0f, getHitBoxHeight());
    }
}

//--------------------------------------------------------------
void ofxMuiSlider::doContentBoxLayout() {
    
    vector<ofRectangle*> rects;
    ofRectangle bb;

    // TODO get rid of redundant push_backs and use the reverse order params of stack
    
//    if(isOrientationHorizontal()) {
//        if(labelPosition == ALIGN_RIGHT) {
//            rects.push_back(getHitBoxRef());
//            rects.push_back(label);
//            ofxMuiRectUtils::stack(rects,ALIGN_CENTER_Y,ALIGN_LEFT,ALIGN_BOTTOM,0,ofPoint(0,0),false);
//        } else if(labelPosition == ALIGN_TOP) {
//            rects.push_back(label);
//            rects.push_back(getHitBoxRef());
//            ofxMuiRectUtils::stack(rects,ALIGN_CENTER_X,ALIGN_LEFT,ALIGN_BOTTOM,0,ofPoint(0,0),false);
//        }
//    } else {
//        if(labelPosition == ALIGN_RIGHT) {
//            rects.push_back(getHitBoxRef());
//            rects.push_back(label);
//            ofxMuiRectUtils::stack(rects,ALIGN_CENTER_Y,ALIGN_LEFT,ALIGN_BOTTOM,0,ofPoint(0,0),false);
//        } else if (labelPosition == ALIGN_TOP) {
//            rects.push_back(label);
//            rects.push_back(getHitBoxRef());
//            ofxMuiRectUtils::stack(rects,ALIGN_CENTER_X,ALIGN_LEFT,ALIGN_BOTTOM,0,ofPoint(0,0),false);
//        }
//    }
    
    bb = ofGetBoundingBox(rects);
    
    setContentBoxWidth(bb.width);
    setContentBoxHeight(bb.height);
   
}
