//
//  ofxGuiNumberData.h
//  BasicExample
//
//  Created by Christopher Baker on 1/9/12.
//  Copyright (c) 2012 School of the Art Institute of Chicago. All rights reserved.
//

#pragma once

#include "ofMain.h"
#include "ofxGuiDefaults.h"
#include "ofxGuiRange.h"

enum ofxGuiNumberDataType {
    OFXGUI_BOOL,
    OFXGUI_INT,
    OFXGUI_FLOAT,
    OFXGUI_BOOL_ARRAY,
    OFXGUI_INT_ARRAY,
    OFXGUI_FLOAT_ARRAY,
};

class ofxGuiNumberData {
public:
    
    //--------------------------------------------------------------
    // CONSTRUCTORS+DESTRUCTORS ////////////////////////////////////
    //--------------------------------------------------------------
    ofxGuiNumberData();
    ofxGuiNumberData(ofxGuiNumberDataType dataType);
    ofxGuiNumberData(ofxGuiNumberDataType dataType, int initialSize);
    
    virtual ~ofxGuiNumberData();

    //--------------------------------------------------------------
    // DATA TYPE ///////////////////////////////////////////////////
    //--------------------------------------------------------------
    void setDataType(ofxGuiNumberDataType dataType);
    ofxGuiNumberDataType getDataType();
    
    //--------------------------------------------------------------
    // GETTING AND SETTING /////////////////////////////////////////
    //--------------------------------------------------------------
    bool  setValue(float val, int index = 0);
    void  setAllValues(float val);
    bool  setNormalizedValue(float val, int index = 0);
    void  setAllNormalizedValues(float val);
    
    float getValue(int index = 0);
    float getValueFloat(int index = 0);
    int   getValueInt(int index = 0);
    bool  getValueBool(int index = 0);
    
    float getNormalizedValue(int index = 0); // can fail
    
    // simple history
    float getLastValue(int index = 0);
    float getLastValueFloat(int index = 0);
    int   getLastValueInt(int index = 0);
    bool  getLastValueBool(int index = 0);

    float getLastNormalizedValue(int index = 0); // can fail
    
    // uses the value with the last value
    float getDeltaValue(int index = 0);
    float getDeltaValueFloat(int index = 0);
    int   getDeltaValueInt(int index = 0);
    bool  getDeltaValueBool(int index = 0);
    

    int   getNumValues();
    
    //--------------------------------------------------------------
    // HISTORY ////////////////////////////////////////////////////
    //--------------------------------------------------------------

    // TODO: implement a variable history with the queue
    
    bool setHistoryLength(int length, int index = 0);
    int getHistoryLength(int index = 0);
    
    //--------------------------------------------------------------
    // ADDING/INSERTING/REMOVING ///////////////////////////////////
    //--------------------------------------------------------------
    bool  addValue(float val);
    bool  addValue(float val, ofxGuiRange _bounds);
    bool  addValue(float val, ofxGuiRange _bounds, ofxGuiRange _range);
    
    bool  addNormalizedValue(float val);

    bool  insertValue(int index, float val);
    bool  insertValue(int index, float val, ofxGuiRange _bounds);
    bool  insertValue(int index, float val, ofxGuiRange _bounds, ofxGuiRange _range);

    bool  insertNormalizedValue(int index, float val);

    bool  removeValue(int index); // will fail in some cases
    
    //--------------------------------------------------------------
    // BOUNDS AND RANGE ////////////////////////////////////////////
    //--------------------------------------------------------------
    
    // bounds
    
    bool setBounds(float _min, float _max, int index = 0);
    bool setBounds(ofxGuiRange _range, int index = 0);

    bool setBoundsMin(float _min, int index = 0);
    bool setBoundsMax(float _max, int index = 0);
    
    float getBoundsMin(int index = 0);
    float getBoundsMax(int index = 0);
    
    bool clearBounds(int index = 0); // will also clear range


    ofxGuiRange getBounds(int index = 0);

    // range
    
    bool setRange(float _min, float _max, int index = 0);
    bool setRange(ofxGuiRange _range, int index = 0);
    
    bool setRangeMin(float _min, int index = 0);
    bool setRangeMax(float _max, int index = 0);
    
    float getRangeMin(int index = 0);
    float getRangeMax(int index = 0);
    
    bool setNormalizedRangeMin(float _min, int index = 0);
    bool setNormalizedRangeMax(float _max, int index = 0);
    
    float getNormalizedRangeMin(int index = 0);
    float getNormalizedRangeMax(int index = 0);
        
    ofxGuiRange getRange(int index = 0);

    bool isRangeEnabled();
    bool clearRange(int index = 0);
    
    //--------------------------------------------------------------
    // DISPLAY PRECISION ///////////////////////////////////////////
    //--------------------------------------------------------------

    bool  setDisplayPrecision(float _precision, int index = 0);
    float getDisplayPrecision(int index = 0);
    
    //--------------------------------------------------------------
    // INCREMENTING ////////////////////////////////////////////////
    //--------------------------------------------------------------
    
    bool setIncrementValue(float _incrementValue, int index = 0);
    bool setAllIncrementValues(float _incrementValue);
    float getIncrementValue(int index = 0);

    bool increment(int index = 0);
    void incrementAll();
    
    bool decrement(int index = 0);
    void decrementAll();
    
    bool add(float value, int index = 0);
    void addAll(float value);
    
    bool subtract(float value, int index = 0);
    void subtractAll(float value);
    
    bool multiply(float value, int index = 0);
    void multiplyAll(float value);
    
    bool divide(float value, int index = 0);
    void divideAll(float value);
    
    bool toggle(int index = 0);
    void toggleAll();
    
    bool invert(int index = 0);
    void invertAll();
    
    float normalize(float _value, int index = 0);
    float denormalize(float _value, int index = 0);

    float rangeNormalize(float _value, int index = 0);
    float rangeDenormalize(float _value, int index = 0);

    //--------------------------------------------------------------
    // QUANTIZATION ////////////////////////////////////////////////
    //--------------------------------------------------------------
    
    bool setQuantizationSteps(int _numSteps, int index = 0);
    int  getQuantizationSteps(int index = 0);
    bool setAllQuantizationSteps(float _numSteps);
    bool disableQuantization(int index = 0);

    //--------------------------------------------------------------
    // TO STRING ///////////////////////////////////////////////////
    //--------------------------------------------------------------

    string toString(int index = 0);
    string historyToString(int index = 0);
    string boundsToString(int index = 0);
    string rangeToString(int index = 0);
    
    
    //--------------------------------------------------------------
    // CALLBACK ////////////////////////////////////////////////////
    //--------------------------------------------------------------

    virtual void dataChanged(int index) {};
    virtual void boundsChanged(int index) {};
    virtual void rangeChanged(int index) {};
    
    void setClosestRangeLimit(float norm);
    void setRightOrLeftRangeLimit(float norm);
    
protected:
    bool isValidIndex(int index);
    bool isValidInsertionIndex(int index);
    
    bool canUseSetAll();
    
    void checkRange(bool& boundsChanged, bool& rangeChanged, int index = 0);
        
    bool isArrayType();
    bool isBoolType();
    bool isFloatType();
    bool isIntType();

    
    float getDefaultIncrement();
    float getDefaultDisplayPrecision();
    ofxGuiRange getDefaultBound();
    ofxGuiRange getDefaultRange();
    
private:
    
    void pushNewValue(float value, bool constrain = true, int index = 0);
    
    // attempt to always enforce this rule:
    // - bounds.min <= range.min <= value <= range.max <= bounds.max
    // - range cannot be set without bounds being set
    // if range is not enabled, then the equation simply changes to 
    // 
    // - bounds.min <= value <= bounds.max
    // if range is enabled, then it will be automatically constrained
    
    ofxGuiDefaults* _defaults;

    void init(int _numValues);
    
    ofxGuiNumberDataType dataType; 
    // everything stored as floats
    // cast and uncast as requested
    vector< deque<float> >  values;
    vector< deque<float> >::iterator  valuesIter;
    deque<float>::iterator queueIter;
    
    vector< int > historyLength;
    vector< int >::iterator historyLengthIter;
    
    vector<ofxGuiRange> bounds;      // the total range
    vector<ofxGuiRange>::iterator boundsIter;

    bool hasRange;
    vector<ofxGuiRange> ranges;       // the local limits
    vector<ofxGuiRange>::iterator rangesIter;
    
    // display precision
    vector<int> displayPrecision;     // precision -1 is unset
    vector<int>::iterator displayPrecisionIter;
    
    // increments
    vector<float>  incrementValues;
    vector<float>::iterator incrementValuesIter;
    
    void constrainValue(bool& _valueChanged, int index = 0);
    
};