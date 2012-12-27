//
//  ofxGuiDataTypes.h
//  BasicExample
//
//  Created by Christopher Baker on 7/21/11.
//  Copyright 2011 School of the Art Institute of Chicago. All rights reserved.
//

#pragma once

//#include <limits>
#include "ofMain.h"

// TODO: createa  way to bind to variables?




/*

class ofxGuiBoolData {
public:
    ofxGuiBoolData() : value(true) {}
    ofxGuiBoolData(bool _value) : value(_value) {}
    ~ofxGuiBoolData() {};
    void toggleValue() {setValue(!value);}
    bool getValue() { return value; }
    void setValue(bool _val) { value = _val; dataChanged();}
    
    string toString() {
        return value ? "TRUE" : "FALSE";
    }
    
protected:
    virtual void dataChanged() {};

    bool value;
};







template<typename DataType>
class ofxGuiData_ {
public:
    
    //--------------------------------------------------------------
    ofxGuiData_<DataType> () {
        init();
    }
    
    //--------------------------------------------------------------
    ofxGuiData_<DataType> (DataType d) {
        init(d); 
    }
    
    //--------------------------------------------------------------
    ~ofxGuiData_<DataType> () {};
    
    //--------------------------------------------------------------
    DataType getValue() {
        return quantize(value); // return the conditionally quantized value
    }
    
    //--------------------------------------------------------------
    void setValue(DataType _val) {
        if(value == _val) return; // short circuit if no change
        DataType prevVal = value;
        value = _val;
        constrainValue();
        // only send data changed value IF ultimately there was a change
        if(prevVal != value) {
            dataChanged();
        }
    }
    
    //--------------------------------------------------------------
    void setIncrementValue(DataType _incrementValue) { incrementValue = _incrementValue; }

    //--------------------------------------------------------------
    DataType getIncrementValue() { return incrementValue; } 
    
    
    //--------------------------------------------------------------
    void setMinValue(DataType _minValue) {
        localRange.setMin(_minValue);

        
        
        // if the constrain process changes data, send a message
        if(constrainValue()) dataChanged();
    }
    
    
    //--------------------------------------------------------------
    void setMaxValue(DataType _maxValue) {
        /*
        maxValueSet=true;
        
        if(globalMaxValueSet) {
            minValue = MAX(globalMinValue, _minValue);
        } else {
            setGlobalMinValue(_minValue);
            minValue = _minValue;
        }
        // if the constrain process changes data, send a message
        if(constrainValue()) dataChanged();
        if(globalMaxValueSet) {
            //maxValue = quantize(_maxValue);
            maxValue = MIN(globalMaxValue, maxValue);
        } else {
            maxValue = _maxValue;
            setGlobalMaxValue(_maxValue);
        }
        
        if(globalMinValueSet) {
            
        } else {
            
        }
        
        
        maxValueSet=true;
        
        DataType oldValue = value;
        value = ofClamp(value, minValue, maxValue);
        if(value != oldValue) dataChanged();
         */
    }
    

    
    // local minima/maxima
    //--------------------------------------------------------------
    DataType getMinValue() {return minValue;}
    //--------------------------------------------------------------
    DataType getMaxValue() {return maxValue;}
    //--------------------------------------------------------------
    bool isMinValueSet() {return minValueSet;}
    //--------------------------------------------------------------
    void clearMinValue() {minValueSet = false;}
    //--------------------------------------------------------------
    bool isMaxValueSet() {return maxValueSet;}
    //--------------------------------------------------------------
    void clearMaxValue() {maxValueSet = false;}
    
    // global minima/maxima
    //--------------------------------------------------------------
    DataType getGlobalMinValue() {return globalMinValue;}
    //--------------------------------------------------------------
    DataType getGlobalMaxValue() {return globalMaxValue;}
    //--------------------------------------------------------------
    bool isGlobalMinValueSet() {return globalMinValueSet;}
    //--------------------------------------------------------------
    void clearGlobalMinValue() {globalMinValueSet = false;}
    //--------------------------------------------------------------
    bool isGlobalMaxValueSet() {return globalMaxValueSet;}
    //--------------------------------------------------------------
    void clearGlobalMaxValue() {globalMaxValueSet = false;}

    // setting global minima/maxima
    //--------------------------------------------------------------
    void setGlobalMinValue(DataType _globalMinValue) {
        globalMinValue = _globalMinValue;
        globalMinValueSet = true;
        
        // check to see if it is greater than the current global max
        if(isGlobalMaxValueSet()) {
            globalMinValue = MIN(globalMinValue, globalMaxValue);
        }
        
        // this will get set even if it is not enabled
        if(minValue < globalMinValue) {
            setMinValue(globalMinValue);
        }
        
        // this will get set even if it is not enabled
        if(maxValue < globalMinValue) {
            setMaxValue(globalMinValue);
        }
        
       // checkValue();
    }
   
    
    //--------------------------------------------------------------
    void setGlobalMaxValue(DataType _globalMaxValue) {
        globalMaxValue = _globalMaxValue;
        globalMaxValueSet = true;
        
        if(isGlobalMinValueSet() && globalMaxValue < globalMinValue) {
            globalMaxValue = globalMinValue;
        }
        
        if(isMaxValueSet() && maxValue > globalMaxValue) {
            setMaxValue(globalMaxValue);
        }
        
        if(isMinValueSet() && minValue > globalMaxValue) {
            setMinValue(globalMinValue);
        }
        
      //  checkValue();
    }
    

    
    
     
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    //--------------------------------------------------------------
    void setNormMinMax(float _minValue, float _maxValue) {
        setNormMinValue(_minValue);
        setNormMaxValue(_maxValue);
    }
    
    //--------------------------------------------------------------
    void setNormMinValue(float n) {
        setMinValue(normToGlobal(n));
    }
    
    //--------------------------------------------------------------
    void setNormMaxValue(float n) {
        setMaxValue(normToGlobal(n));
    }
    
    //--------------------------------------------------------------
    DataType normToGlobal(float n) {
        return (DataType)ofLerp(globalMinValue, globalMaxValue, n);
    }
    
    
       //--------------------------------------------------------------
    void setGlobalMinMax(DataType _globalMinValue, DataType _globalMaxValue) {
        setGlobalMinValue(_globalMinValue);
        setGlobalMaxValue(_globalMaxValue);
    }
    
    //--------------------------------------------------------------
    void setMinMax(DataType _minValue, DataType _maxValue) {
        setMinValue(_minValue);
        setMaxValue(_maxValue);
    }

    //--------------------------------------------------------------
    int getQuantizationSteps() {
        return quantizeSteps;
    };
    
    //--------------------------------------------------------------
    void setQuantizatioSteps(int _quantizeSteps) {
        if(_quantizeSteps < 0) {
            setQuantize(false);
        } else {
            quantizeSteps = _quantizeSteps;
            setQuantize(true);
        }
    }
    
    //--------------------------------------------------------------
    void setQuantize(bool _doQuantize) {
        doQuantize = _doQuantize;
    }
    
    //--------------------------------------------------------------
    void increaseValue() {add(incrementValue);}
    //--------------------------------------------------------------
    void decreaseValue() {add(-incrementValue);}
    
    //--------------------------------------------------------------
    DataType getNormalizedMinValue() {
        return ofNormalize(minValue, globalMinValue, globalMaxValue);
    }
    
    //--------------------------------------------------------------
    DataType getNormalizedMaxValue() {
        return ofNormalize(maxValue, globalMinValue, globalMaxValue);
    }
    
    //--------------------------------------------------------------
    DataType getNormalizedValue() {
        
        if(globalMinValueSet && globalMaxValueSet) {
            // will quantize in setValue
            return ofNormalize(value, globalMinValue, globalMaxValue);
        } else {
            ofLog(OF_LOG_WARNING,"ofxGuiFloatData: getNormalizedValue() called, w/o global max or min values defined. Doing nothing. VALUE=%d (%d, %d)",value, globalMinValueSet, globalMaxValueSet);
            return value;
        }
    }
    
    //--------------------------------------------------------------
    void setDisplayPrecision(int _displayPrecision) {displayPrecision = _displayPrecision;}
    //--------------------------------------------------------------
    int getDisplayPrecision() {return displayPrecision;}
    
    //--------------------------------------------------------------
    string toString() {
        return ofToString(getValue(),displayPrecision);
    }
    
    //--------------------------------------------------------------
    void add(DataType f) { setValue(value + f); }
    
protected:

    // returns true if data is changed
    bool constrainValue() {
        DataType prevValue = value;
        // check against global max/min
        if(globalMinValueSet) value = MAX(globalMinValue, value);
        if(globalMaxValueSet) value = MIN(globalMaxValue, value);
        // check against local max/min
        if(minValueSet) value = MAX(minValue, value);
        if(maxValueSet) value = MIN(maxValue, value);
        // callback on change 
        return (prevValue != value);
    }
    
    
    
    //--------------------------------------------------------------
    void init() {
        init(0);
    }
    
    //--------------------------------------------------------------
    void init(DataType d) {
        value = d;

        minValue = 0;
        maxValue = 0; 
        minValueSet = false;
        maxValueSet = false; 
        
        globalMinValue = 0;
        globalMaxValue = 0;
        globalMinValueSet = false;
        globalMaxValueSet = false;
        
        quantizeSteps = 1024;
        doQuantize = false;
        
        if(sizeof(DataType) == sizeof(float) || sizeof(DataType) == sizeof(double)) {
            incrementValue = 0.01;
            displayPrecision = 2;
        } else {
            incrementValue = 1;
            displayPrecision = 0;
        }
    }
    
    //--------------------------------------------------------------
    virtual void dataChanged() {};
    
    //--------------------------------------------------------------
    DataType quantize(DataType value) {
        if(doQuantize && globalMinValueSet && globalMaxValueSet) {
            int bucketNum = floor(ofClamp((getNormalizedValue() * quantizeSteps), 0, quantizeSteps-1));
            return ofMap(bucketNum, 0, quantizeSteps-1, globalMinValue, globalMaxValue);
        } else {
            return value;
        }
    }
    
    //--------------------------------------------------------------
    // for setting the value
    void setValueFromNormalized(DataType normalizedPosition) {
        if(globalMinValueSet && globalMaxValueSet) {
            setValue(ofLerp(globalMinValue,globalMaxValue,normalizedPosition));
        } else {
            ofLog(OF_LOG_WARNING,"ofxGuiFloatData: getNormalizedValue() called, w/o global max or min values defined. Doing nothing.");
        }
    }
    
    //--------------------------------------------------------------
    
private:

    // the value
    DataType value;

    // the increment step
    DataType incrementValue;
    
    
    
    // local minima and maxima for ranges
    DataType minValue, maxValue;
    bool minValueSet, maxValueSet;
    
    // global minima and maxima for ranges
    DataType globalMinValue, globalMaxValue;
    bool globalMinValueSet, globalMaxValueSet;
    
    
    // quantization
    int quantizeSteps;
    bool doQuantize;
    
    // display precision
    int displayPrecision;
    
};

typedef ofxGuiData_<float>  ofxGuiDataf;
typedef ofxGuiData_<int>    ofxGuiDatai;

