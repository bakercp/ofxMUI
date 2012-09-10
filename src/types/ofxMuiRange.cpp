//
//  ofxMuiRange.h
//  BasicExample
//
//  Created by Christopher Baker on 1/9/12.
//  Copyright (c) 2012 School of the Art Institute of Chicago. All rights reserved.
//

#include "ofxMuiRange.h"

//--------------------------------------------------------------
ofxMuiRange::ofxMuiRange() {
    clear();
}

//--------------------------------------------------------------
ofxMuiRange::ofxMuiRange(float _min, float _max) {
    setMin(_min);
    setMax(_max);
}

//--------------------------------------------------------------
ofxMuiRange::~ofxMuiRange() {
    
}

//--------------------------------------------------------------
void ofxMuiRange::setMin(float _min) {
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
void ofxMuiRange::setMax(float _max) {
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
void ofxMuiRange::expandToFit(float _val) {
    if(_val > getMax()) setMax(_val);
    if(_val < getMin()) setMin(_val);
}


//--------------------------------------------------------------
bool ofxMuiRange::intersects(ofxMuiRange _range) const {
    return contains(_range.getMin()) || contains(_range.getMax());
}

//--------------------------------------------------------------
ofxMuiRange ofxMuiRange::intersect(ofxMuiRange _range) const {
    ofxMuiRange newRange;
    newRange.setMin(constrain(_range.getMin()));
    newRange.setMax(constrain(_range.getMax()));
    return newRange;
}

ofxMuiRange ofxMuiRange::constrain(ofxMuiRange _range) const {
    ofxMuiRange range = _range;
    //cout << "\t\tCONSTRAIN 0 <<" << range.toString() << endl;
    range.setMin(constrain(range.getMin()));
    //cout << "\t\tCONSTRAIN 1 <<" << range.toString() << endl;
    range.setMax(constrain(range.getMax()));
    //cout << "\t\tCONSTRAIN 2 <<" << range.toString() << endl;
    return range;
}

//--------------------------------------------------------------
float ofxMuiRange::constrain(float _value) const {
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
bool ofxMuiRange::contains(float _value) const {
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
float ofxMuiRange::mean() const {
    return lerp(0.5);
}

//--------------------------------------------------------------
float ofxMuiRange::lerp(float amt) const {
    if(!isBounded()) ofLog(OF_LOG_WARNING,"ofxMuiRange:: Attempting to lerp with an unbounded range.");
    return ofLerp(getMin(), getMax(), amt);
}


//--------------------------------------------------------------
float ofxMuiRange::normalize(float _nValue) const {
    if(!isBounded()) ofLog(OF_LOG_WARNING,"ofxMuiRange:: Attempting to denormalize with an unbounded range.");
    return ofNormalize(_nValue, getMin(),getMax());
}


//--------------------------------------------------------------
float ofxMuiRange::denormalize(float _nValue) const {
    if(!isBounded()) ofLog(OF_LOG_WARNING,"ofxMuiRange:: Attempting to denormalize with an unbounded range.");
    if(_nValue > 1 || _nValue < 0) ofLog(OF_LOG_WARNING,"ofxMuiRange:: Attempting to denormalize a value outside of the 0-1 range, clamping.");
    return ofLerp(getMin(),getMax(), ofClamp(_nValue, 0, 1));
}

//--------------------------------------------------------------
float ofxMuiRange::getMin() const {return min;}
//--------------------------------------------------------------
float ofxMuiRange::getMax() const {return max;}
//--------------------------------------------------------------
void ofxMuiRange::clearMin() { min = -numeric_limits<float>::max(); }
//--------------------------------------------------------------
void ofxMuiRange::clearMax() { max = numeric_limits<float>::max(); }
//--------------------------------------------------------------
void ofxMuiRange::clear() { clearMin(); clearMax(); }
//--------------------------------------------------------------
void ofxMuiRange::invertExtrema() {
    swap(min,max);
}
//--------------------------------------------------------------
float ofxMuiRange::delta() const {
    if(!isBounded()) ofLog(OF_LOG_WARNING,"ofxMuiRange:: Attempting to delta with an unbounded range.");
    return getMax() - getMin();
}
//--------------------------------------------------------------
bool ofxMuiRange::isMinSet() const { return min != -numeric_limits<float>::max(); }
//--------------------------------------------------------------
bool ofxMuiRange::isMaxSet() const { return max != numeric_limits<float>::max(); }

//--------------------------------------------------------------
bool ofxMuiRange::isBounded() const {
    return isMinSet() && isMaxSet();
}

/*
//--------------------------------------------------------------
float ofxMuiRange::quantize(float _value) {
    if(isQuantizing() && isBounded()) {
        int bucketNum = floor(ofClamp((normalize(_value) * quantizationSteps), 0, quantizationSteps-1));
        return ofMap(bucketNum, 0, quantizationSteps-1, getMin(), getMax());
    } else {
        return _value;
    }
}

//--------------------------------------------------------------
void ofxMuiRange::setQuantizationSteps(int _steps) {
    quantizationSteps = _steps;
}

//--------------------------------------------------------------
int ofxMuiRange::getQuantizationSteps() {
    return quantizationSteps;
}

//--------------------------------------------------------------
bool ofxMuiRange::isQuantizing() {
    return quantizationSteps > 0;
}

//--------------------------------------------------------------
void ofxMuiRange::disableQuantization() {
    setQuantizationSteps(-1);
}
 */


//--------------------------------------------------------------
ofxMuiRange ofxMuiRange::fromArray(float* array, int cnt) {
    ofxMuiRange r;
    r.invertExtrema();
    for(int i = 0; i < cnt; i++) r.expandToFit(array[i]);
    return r;
}

//--------------------------------------------------------------
ofxMuiRange ofxMuiRange::fromArray(vector<float> array) {
    ofxMuiRange r;
    r.invertExtrema();
    for(int i = 0; i < array.size(); i++) r.expandToFit(array[i]);
    return r;
}

//--------------------------------------------------------------
ofxMuiRange ofxMuiRange::roundOutward(ofxMuiRange& range) {
    ofxMuiRange nRange(floor(range.getMin()), ceil(range.getMax()));
    return nRange;
}

//--------------------------------------------------------------
ofxMuiRange ofxMuiRange::roundInward(ofxMuiRange& range) {
    float u = range.getMin();
    float v = range.getMax();
    if(u != -numeric_limits<float>::max()) {
        u = ceil(u);
    } // else u stays the same

    if(v != numeric_limits<float>::max()) {
        v = floor(v);
    }
    ofxMuiRange g(u,v);
    return g;
}



string ofxMuiRange::toString() const {
    return ofToString(isMinSet()) + "/" + 
            ofToString(isMaxSet()) + 
            " MIN: " + ofToString(getMin()) + 
            " MAX: " + ofToString(getMax());

}

// Check similarity/equality.
//
//
bool ofxMuiRange::operator==( const ofxMuiRange& _range ) const {
    return (min == _range.min) && (max == _range.max);
}

bool ofxMuiRange::operator!=( const ofxMuiRange& _range ) const {
    return (min != _range.min) || (max != _range.max);
}


