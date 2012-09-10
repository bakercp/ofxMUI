

#include "ofxGuiSlider.h"

//--------------------------------------------------------------
ofxGuiSlider::ofxGuiSlider(const string& _name, int _x, int _y, int _width, int _height, bool _enabled) : 
    ofxGuiLabelledObject(_name, _x, _y, _width, _height, _enabled),
    ofxGuiNumberData() {
    init();
}

//--------------------------------------------------------------
ofxGuiSlider::ofxGuiSlider(const string& _name, int _x, int _y,bool _enabled) : 
    ofxGuiLabelledObject(_name, _x, _y, _enabled),
    ofxGuiNumberData() {
    init();
}

//--------------------------------------------------------------
ofxGuiSlider::ofxGuiSlider(const string& _name,bool _enabled) :
    ofxGuiLabelledObject(_name, _enabled),
    ofxGuiNumberData() {
    init();
}

//--------------------------------------------------------------
ofxGuiSlider::ofxGuiSlider(bool _enabled) : 
    ofxGuiLabelledObject(_enabled),
    ofxGuiNumberData() {
    init();
}

//--------------------------------------------------------------
ofxGuiSlider::~ofxGuiSlider() {
}

//--------------------------------------------------------------
void ofxGuiSlider::init() {

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
    
    label->setText(name);
    label->enable();
    
    valueLabel->setText("NULL");
    valueLabel->enable();
    valueLabel->show();

    requestBoxLayout();
    
}

//--------------------------------------------------------------
void ofxGuiSlider::dataChanged() {
    float v = getValue(); // gotta get a copy, b/c the value is private
    ofNotifyEvent(ofxGuiSliderEvent, v, this);
}

//--------------------------------------------------------------
void ofxGuiSlider::update() {
    
    tooltip = toString();
    valueLabel->setText(tooltip);
    valueLabel->setTooltip(tooltip);
    //cout << "setting alhpa scale of label
    valueLabel->setAlphaScale(getActiveTimer()); // take care of fading

    switch(orientation) {
        case OF_ORIENTATION_UNKNOWN:
        case OF_ORIENTATION_DEFAULT:	
        case OF_ORIENTATION_180:
            valueLabel->alignTo(getHitBox(),
                                OF_ALIGN_HORZ_LEFT,
                                OF_ALIGN_VERT_CENTER);
            break;
        case OF_ORIENTATION_90_RIGHT:
        case OF_ORIENTATION_90_LEFT:
            valueLabel->alignTo(getHitBox(),
                                OF_ALIGN_HORZ_CENTER,
                                OF_ALIGN_VERT_BOTTOM);
            break;
    }
}

//--------------------------------------------------------------
void ofxGuiSlider::draw() {
    
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
        ofSetColor(cActiveAreaBackground.get(isMouseOver(),isMouseDown(),isEnabled(),alphaScale));
        ofxRect(_x, 0, _w, getHitBoxHeight());
                    
        // the value
        ofSetColor(cActiveAreaForeground.get(isMouseOver(),isMouseDown(),isEnabled(),alphaScale));
        ofxRect(_x, 0, vWidth, getHitBoxHeight());
        
        // the 
        ofNoFill();
        ofSetColor(cActiveAreaFrame.get(isMouseOver(),isMouseDown(),isEnabled(),alphaScale));
        
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
        ofSetColor(cActiveAreaBackground.get(isMouseOver(),isMouseDown(),isEnabled(),alphaScale));
        ofxRect(0, yMax, getHitBoxWidth(), yRange);
        
        // the value
        ofSetColor(cActiveAreaForeground.get(isMouseOver(),isMouseDown(),isEnabled(),alphaScale));
        ofxRect(0, yPos, getHitBoxWidth(), yHeight);
        
        // the 
        ofNoFill();
        ofSetColor(cActiveAreaFrame.get(isMouseOver(),isMouseDown(),isEnabled(),alphaScale));
        
        // range handles
        ofLine(0, yPos, getHitBoxWidth(), yPos);
        ofLine(0, yMin, getHitBoxWidth(), yMin);
        ofLine(0, yMax, getHitBoxWidth(), yMax);
        
    }
    
    ofNoFill();
    ofSetColor(cActiveAreaFrame.get(isMouseOver(),isMouseDown(),isEnabled(),alphaScale));
    ofRect(0, 0, getHitBoxWidth(), getHitBoxHeight() );
    
    ofPopMatrix();
    ofPopStyle();
    
}

//--------------------------------------------------------------
void ofxGuiSlider::keyBind_increaseValue(int key) {
    //setKeyMap(key,bind(&ofxGuiSlider::increment, ref(*this))); 
}

//--------------------------------------------------------------
void ofxGuiSlider::keyBind_decreaseValue(int key) {
    //setKeyMap(key,bind(&ofxGuiSlider::decrement, ref(*this))); 
}

//--------------------------------------------------------------
void ofxGuiSlider::buildFromXml() {}

//--------------------------------------------------------------
void ofxGuiSlider::saveToXml() {}

//--------------------------------------------------------------
void ofxGuiSlider::setOrientation(const ofOrientation& _orientation) {
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
void ofxGuiSlider::setSliderWidth(int _width) {
    setHitBoxWidth(_width);
    requestBoxLayout();
}

//--------------------------------------------------------------
ofOrientation ofxGuiSlider::getOrientation() const {
    return orientation;
}

//--------------------------------------------------------------
int ofxGuiSlider::getSliderWidth() const {
    return getHitBoxWidth();
}

//--------------------------------------------------------------
int ofxGuiSlider::getSliderHeight() const {
    return getHitBoxHeight();
}

//--------------------------------------------------------------
void ofxGuiSlider::setSliderHeight(int _height) {
    setHitBoxHeight(_height);
    requestBoxLayout();
}

//--------------------------------------------------------------
void ofxGuiSlider::onRollOver() {
    //valueLabel->show();
}
//--------------------------------------------------------------
void ofxGuiSlider::onRollOut() {
    //valueLabel->hide();
}

void ofxGuiSlider::onMouseMove() {
//    cout << "mouse moved!!" << endl;
}


//--------------------------------------------------------------
void ofxGuiSlider::onPress() {

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
void ofxGuiSlider::onDoublePress() {
    if(isCtrlPressed()) {
        setNormalizedRangeMin(0.0f);
        setNormalizedRangeMax(1.0f);
    }
}


//--------------------------------------------------------------
void ofxGuiSlider::onDrag() {
    
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
float ofxGuiSlider::toNormalizedValue(ofVec2f v) {
    if(isOrientationHorizontal()) {
        return ofNormalize(v.x, 0.0f, getHitBoxWidth());
    } else {
        // invert to make bottom low, and top higher
        return 1.0f - ofNormalize(v.y, 0.0f, getHitBoxHeight());
    }
}

//--------------------------------------------------------------
void ofxGuiSlider::doContentBoxLayout() {
    
    vector<ofRectangle*> rects;
    ofRectangle bb;

    // TODO get rid of redundant push_backs and use the reverse order params of stack
    
//    if(isOrientationHorizontal()) {
//        if(labelPosition == ALIGN_RIGHT) {
//            rects.push_back(getHitBoxRef());
//            rects.push_back(label);
//            ofxGuiRectUtils::stack(rects,ALIGN_CENTER_Y,ALIGN_LEFT,ALIGN_BOTTOM,0,ofPoint(0,0),false);
//        } else if(labelPosition == ALIGN_TOP) {
//            rects.push_back(label);
//            rects.push_back(getHitBoxRef());
//            ofxGuiRectUtils::stack(rects,ALIGN_CENTER_X,ALIGN_LEFT,ALIGN_BOTTOM,0,ofPoint(0,0),false);
//        }
//    } else {
//        if(labelPosition == ALIGN_RIGHT) {
//            rects.push_back(getHitBoxRef());
//            rects.push_back(label);
//            ofxGuiRectUtils::stack(rects,ALIGN_CENTER_Y,ALIGN_LEFT,ALIGN_BOTTOM,0,ofPoint(0,0),false);
//        } else if (labelPosition == ALIGN_TOP) {
//            rects.push_back(label);
//            rects.push_back(getHitBoxRef());
//            ofxGuiRectUtils::stack(rects,ALIGN_CENTER_X,ALIGN_LEFT,ALIGN_BOTTOM,0,ofPoint(0,0),false);
//        }
//    }
    
    bb = ofGetBoundingBox(rects);
    
    setContentBoxWidth(bb.width);
    setContentBoxHeight(bb.height);
   
}
