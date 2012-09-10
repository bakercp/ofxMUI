//
//  ofxGuiRange.h
//  BasicExample
//
//  Created by Christopher Baker on 1/9/12.
//  Copyright (c) 2012 School of the Art Institute of Chicago. All rights reserved.
//

#include "ofxGuiRange.h"

//--------------------------------------------------------------
ofxGuiRange::ofxGuiRange() {
    clear();
}

//--------------------------------------------------------------
ofxGuiRange::ofxGuiRange(float _min, float _max) {
    setMin(_min);
    setMax(_max);
}

//--------------------------------------------------------------
ofxGuiRange::~ofxGuiRange() {
    
}

//--------------------------------------------------------------
void ofxGuiRange::setMin(float _min) {
    //if(_min <= max) {
        min = _min;
    //} else {
    // cout << "XXXxxXXXxxXXXxxXXXxx SET MIN FAILED W/ " << _min << " > " << max << endl;
    //}
    
    /*
    if(isMaxSet() && max < min) {
        swap(max, min); // force it
    }
     */
} 

//--------------------------------------------------------------
void ofxGuiRange::setMax(float _max) {
    //if(_max >= min) {
        max = _max;
    //} else {
    //    cout << "XXXxxXXXxxXXXxxXXXxx SET MAX FAILED W/ " << _max << " < " << min << endl;
    //}
/*
    max = _max;
    if(isMinSet() && min > max) {
        swap(max,min); // force it
    }
 */
}

//--------------------------------------------------------------
void ofxGuiRange::expandToFit(float _val) {
    if(_val > getMax()) setMax(_val);
    if(_val < getMin()) setMin(_val);
}


//--------------------------------------------------------------
bool ofxGuiRange::intersects(ofxGuiRange _range) const {
    return contains(_range.getMin()) || contains(_range.getMax());
}

//--------------------------------------------------------------
ofxGuiRange ofxGuiRange::intersect(ofxGuiRange _range) const {
    ofxGuiRange newRange;
    newRange.setMin(constrain(_range.getMin()));
    newRange.setMax(constrain(_range.getMax()));
    return newRange;
}

ofxGuiRange ofxGuiRange::constrain(ofxGuiRange _range) const {
    ofxGuiRange range = _range;
    //cout << "\t\tCONSTRAIN 0 <<" << range.toString() << endl;
    range.setMin(constrain(range.getMin()));
    //cout << "\t\tCONSTRAIN 1 <<" << range.toString() << endl;
    range.setMax(constrain(range.getMax()));
    //cout << "\t\tCONSTRAIN 2 <<" << range.toString() << endl;
    return range;
}

//--------------------------------------------------------------
float ofxGuiRange::constrain(float _value) const {
    float value = _value;
    if(isMinSet()) {
        //cout << "CONSTRAINED " << value << " BY BOUNDED MIN OF " << getMin();
        value = MAX(min, value);  
        //cout << " RESULTING IN " << value << endl;
        
        
    } else {
        //cout << "NOT CONSTRAINED BY UNBOUNDED MIN " << endl;
        
    }
    
    //cout << value << endl;
    
    if(isMaxSet()) {
        //cout << "CONSTRAINED " << value << " BY BOUNDED MAX OF " << getMax() << endl;
     value = MIN(max, value);   
    } else {
        //cout << "NOT CONSTRAINED BY UNBOUNDED MAX " << endl;

    }
    
    //cout << value << endl;
    
    return value;
}

//--------------------------------------------------------------
bool ofxGuiRange::contains(float _value) const {
    if(isMinSet() && isMaxSet()) {
        return _value <= max && _value >= min;
    } else if(isMinSet()) {
        return _value >= min;
    } else if(isMaxSet()) {
        return _value <= max;
    } else {
        // no constraints
        return true;  
    }
}

//--------------------------------------------------------------
float ofxGuiRange::mean() const {
    return lerp(0.5);
}

//--------------------------------------------------------------
float ofxGuiRange::lerp(float amt) const {
    if(!isBounded()) ofLog(OF_LOG_WARNING,"ofxGuiRange:: Attempting to lerp with an unbounded range.");
    return ofLerp(getMin(), getMax(), amt);
}


//--------------------------------------------------------------
float ofxGuiRange::normalize(float _nValue) const {
    if(!isBounded()) ofLog(OF_LOG_WARNING,"ofxGuiRange:: Attempting to denormalize with an unbounded range.");
    return ofNormalize(_nValue, getMin(),getMax());
}


//--------------------------------------------------------------
float ofxGuiRange::denormalize(float _nValue) const {
    if(!isBounded()) ofLog(OF_LOG_WARNING,"ofxGuiRange:: Attempting to denormalize with an unbounded range.");
    if(_nValue > 1 || _nValue < 0) ofLog(OF_LOG_WARNING,"ofxGuiRange:: Attempting to denormalize a value outside of the 0-1 range, clamping.");
    return ofLerp(getMin(),getMax(), ofClamp(_nValue, 0, 1));
}

//--------------------------------------------------------------
float ofxGuiRange::getMin() const {return min;}
//--------------------------------------------------------------
float ofxGuiRange::getMax() const {return max;}
//--------------------------------------------------------------
void ofxGuiRange::clearMin() { min = -numeric_limits<float>::max(); }
//--------------------------------------------------------------
void ofxGuiRange::clearMax() { max = numeric_limits<float>::max(); }
//--------------------------------------------------------------
void ofxGuiRange::clear() { clearMin(); clearMax(); }
//--------------------------------------------------------------
void ofxGuiRange::invertExtrema() {
    swap(min,max);
}
//--------------------------------------------------------------
float ofxGuiRange::delta() const {
    if(!isBounded()) ofLog(OF_LOG_WARNING,"ofxGuiRange:: Attempting to delta with an unbounded range.");
    return getMax() - getMin();
}
//--------------------------------------------------------------
bool ofxGuiRange::isMinSet() const { return min != -numeric_limits<float>::max(); }
//--------------------------------------------------------------
bool ofxGuiRange::isMaxSet() const { return max != numeric_limits<float>::max(); }

//--------------------------------------------------------------
bool ofxGuiRange::isBounded() const {
    return isMinSet() && isMaxSet();
}

/*
//--------------------------------------------------------------
float ofxGuiRange::quantize(float _value) {
    if(isQuantizing() && isBounded()) {
        int bucketNum = floor(ofClamp((normalize(_value) * quantizationSteps), 0, quantizationSteps-1));
        return ofMap(bucketNum, 0, quantizationSteps-1, getMin(), getMax());
    } else {
        return _value;
    }
}

//--------------------------------------------------------------
void ofxGuiRange::setQuantizationSteps(int _steps) {
    quantizationSteps = _steps;
}

//--------------------------------------------------------------
int ofxGuiRange::getQuantizationSteps() {
    return quantizationSteps;
}

//--------------------------------------------------------------
bool ofxGuiRange::isQuantizing() {
    return quantizationSteps > 0;
}

//--------------------------------------------------------------
void ofxGuiRange::disableQuantization() {
    setQuantizationSteps(-1);
}
 */


//--------------------------------------------------------------
ofxGuiRange ofxGuiRange::fromArray(float* array, int cnt) {
    ofxGuiRange r;
    r.invertExtrema();
    for(int i = 0; i < cnt; i++) r.expandToFit(array[i]);
    return r;
}

//--------------------------------------------------------------
ofxGuiRange ofxGuiRange::fromArray(vector<float> array) {
    ofxGuiRange r;
    r.invertExtrema();
    for(int i = 0; i < array.size(); i++) r.expandToFit(array[i]);
    return r;
}

//--------------------------------------------------------------
ofxGuiRange ofxGuiRange::roundOutward(ofxGuiRange& range) {
    ofxGuiRange nRange(floor(range.getMin()), ceil(range.getMax()));
    return nRange;
}

//--------------------------------------------------------------
ofxGuiRange ofxGuiRange::roundInward(ofxGuiRange& range) {
    float u = range.getMin();
    float v = range.getMax();
    if(u != -numeric_limits<float>::max()) {
        u = ceil(u);
    } // else u stays the same

    if(v != numeric_limits<float>::max()) {
        v = floor(v);
    }
    ofxGuiRange g(u,v);
    return g;
}



string ofxGuiRange::toString() const {
    return ofToString(isMinSet()) + "/" + 
            ofToString(isMaxSet()) + 
            " MIN: " + ofToString(getMin()) + 
            " MAX: " + ofToString(getMax());

}

// Check similarity/equality.
//
//
bool ofxGuiRange::operator==( const ofxGuiRange& _range ) const {
    return (min == _range.min) && (max == _range.max);
}

bool ofxGuiRange::operator!=( const ofxGuiRange& _range ) const {
    return (min != _range.min) || (max != _range.max);
}


