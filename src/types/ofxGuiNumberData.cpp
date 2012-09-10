//
//  ofxGuiData.cpp
//  BasicExample
//
//  Created by Christopher Baker on 1/9/12.
//  Copyright (c) 2012 School of the Art Institute of Chicago. All rights reserved.
//

#include "ofxGuiNumberData.h"

//--------------------------------------------------------------
// CONSTRUCTORS+DESTRUCTORS ////////////////////////////////////
//--------------------------------------------------------------
ofxGuiNumberData::ofxGuiNumberData() {
    dataType = OFXGUI_FLOAT;
    init(1);
}
//--------------------------------------------------------------
ofxGuiNumberData::ofxGuiNumberData(const ofxGuiNumberDataType& _dataType) {
    dataType = _dataType;
    init(1);
}
//--------------------------------------------------------------
ofxGuiNumberData::ofxGuiNumberData(const ofxGuiNumberDataType& _dataType, int _initialSize) {
    dataType = _dataType;
    init(_initialSize);
}
//--------------------------------------------------------------
ofxGuiNumberData::~ofxGuiNumberData() {
    // nothing to do
}
//--------------------------------------------------------------
// DATA TYPE ///////////////////////////////////////////////////
//--------------------------------------------------------------
void ofxGuiNumberData::setDataType(const ofxGuiNumberDataType& _dataType) {
    dataType = _dataType;
    // TODO -- DO CHECKING HERE??
}
//--------------------------------------------------------------
ofxGuiNumberDataType ofxGuiNumberData::getDataType() const {
    return dataType;
}

//--------------------------------------------------------------
void ofxGuiNumberData::pushNewValue(float value, bool constrain, int index) {
    bool valueChanged = false;
    float curValue = values[index].back();
    
    // push the new value into the history
    values[index].push_back(value);
    // constrain it if needed
    if(constrain) constrainValue(valueChanged, index);
    // pop off old history values
    while(values[index].size() > historyLength[index]) {
        values[index].pop_front();
    }
    
    if(curValue != values[index].back() || valueChanged) {
        dataChanged(index);
    }
}


//--------------------------------------------------------------
// GETTING AND SETTING /////////////////////////////////////////
//--------------------------------------------------------------
bool  ofxGuiNumberData::setValue(float val, int index) {
    if(isValidIndex(index)) {
        pushNewValue(val,true,index);
        return true;
    } else {
        return false;
    }
}
//--------------------------------------------------------------
void  ofxGuiNumberData::setAllValues(float val) {
    if(canUseSetAll()) {
        for(int i = 0; i < getNumValues(); i++) pushNewValue(val,true, i);
    }
}
//--------------------------------------------------------------
bool  ofxGuiNumberData::setNormalizedValue(float val, int index) {
    if(isValidIndex(index) && bounds[index].isBounded()) {
        pushNewValue(bounds[index].denormalize(val),true,index);
        return true;
    } else {
        return false;
    }
}
//--------------------------------------------------------------
void  ofxGuiNumberData::setAllNormalizedValues(float val) {
    if(canUseSetAll()) {
        for(int i = 0; i < getNumValues(); i++) setNormalizedValue(val,i);
    }
}

//--------------------------------------------------------------
float ofxGuiNumberData::getValue(int index) const {
    if(isValidIndex(index)) {
        // conditionally quantize based on the BOUNDS, not the range
        return values[index].back();//bounds[index];.quantize(values[index]);
    } else {
        ofLog(OF_LOG_ERROR, "ofxGuiNumberData:: Attempted to get an invalid value.");
        return 0;
    }
}
//--------------------------------------------------------------
float ofxGuiNumberData::getValueFloat(int index) const {
    return getValue(index);
}
//--------------------------------------------------------------
int   ofxGuiNumberData::getValueInt(int index) const {
    return (int)getValue(index);
}
//--------------------------------------------------------------
bool  ofxGuiNumberData::getValueBool(int index) const {
    return (bool)getValue(index);
}

//--------------------------------------------------------------
float ofxGuiNumberData::getNormalizedValue(int index) const {
    if(isValidIndex(index) && bounds[index].isBounded()) {
        return bounds[index].normalize(getValue());
    } else {
        ofLog(OF_LOG_WARNING,"ofxGuiNumberData:: Attempting to get a normalized value from an unbounded range.");
        return false;
    }
}

//--------------------------------------------------------------
float ofxGuiNumberData::getLastValue(int index) const {
    if(isValidIndex(index)) {
        // conditionally quantize based on the BOUNDS, not the range
        return values[index][values[index].size()-2];//bounds[index];.quantize(values[index]);
    } else {
        ofLog(OF_LOG_ERROR, "ofxGuiNumberData:: Attempted to get an invalid value.");
        return 0;
    }
}
//--------------------------------------------------------------
float ofxGuiNumberData::getLastValueFloat(int index) const {
    return getLastValue(index);
}
//--------------------------------------------------------------
int   ofxGuiNumberData::getLastValueInt(int index) const {
    return (int)getLastValue(index);
}
//--------------------------------------------------------------
bool  ofxGuiNumberData::getLastValueBool(int index) const {
    return (bool)getLastValue(index);
}

//--------------------------------------------------------------
float ofxGuiNumberData::getLastNormalizedValue(int index) const {
    if(isValidIndex(index) && bounds[index].isBounded()) {
        return bounds[index].normalize(getLastValue());
        // TODO ... this is trick ... it's possible that the bounds
        // could have changed ... resulting in an incorrect last value?
        // unlikely, yes.
    } else {
        ofLog(OF_LOG_WARNING,"ofxGuiNumberData:: Attempting to get a normalized value from an unbounded range.");
        return false;
    }
}

//--------------------------------------------------------------
float ofxGuiNumberData::getDeltaValue(int index) const {
    if(isValidIndex(index)) {
        // conditionally quantize based on the BOUNDS, not the range
        return (values[index][values[index].size()-2] - values[index].back());//bounds[index];.quantize(values[index]);
    } else {
        ofLog(OF_LOG_ERROR, "ofxGuiNumberData:: Attempted to get an invalid value.");
        return 0;
    }
}
//--------------------------------------------------------------
float ofxGuiNumberData::getDeltaValueFloat(int index) const {
    return getDeltaValue(index);
}
//--------------------------------------------------------------
int   ofxGuiNumberData::getDeltaValueInt(int index) const {
    return (int)(getDeltaValue(index));
}
//--------------------------------------------------------------
bool  ofxGuiNumberData::getDeltaValueBool(int index) const {
    return (bool)(getDeltaValue(index));
}

//--------------------------------------------------------------
int   ofxGuiNumberData::getNumValues() const {
    return values.size();;
}

//--------------------------------------------------------------
// HISTORY ////////////////////////////////////////////////////
//--------------------------------------------------------------
bool ofxGuiNumberData::setHistoryLength(int length, int index) {
    if(isValidIndex(index)) {
        if(length >= 2) {
            historyLength[index] = length;
            if(values[index].size() > length) {
                // if there are too many, prune
                while(values[index].size() > historyLength[index]) {
                    values[index].pop_front();
                }
            } else {
                // if there aren't enough, copy
                float v = values[index].back();
                while(values[index].size() < historyLength[index]) {
                    values[index].push_back(v);
                }
            }
            return true;
        } else {
            ofLog(OF_LOG_ERROR, "ofxGuiNumberData:: Invalid history length value.  HistoryLength value must be >= 2.");
            return false;
        }
    } else {
        ofLog(OF_LOG_ERROR, "ofxGuiNumberData:: Attempted to get an invalid value.");
        return 0;
    }
}

//--------------------------------------------------------------
int ofxGuiNumberData::getHistoryLength(int index) const {
    if(isValidIndex(index)) {
        return historyLength[index];
    } else {
        return -1;
    }
}


//--------------------------------------------------------------
// ADDING/INSERTING/REMOVING ///////////////////////////////////
//--------------------------------------------------------------
bool  ofxGuiNumberData::addValue(float val) {
    addValue(val, ofxGuiRange());
}
//--------------------------------------------------------------
bool  ofxGuiNumberData::addValue(float val, ofxGuiRange _bounds) {
    addValue(val, _bounds, ofxGuiRange());
}
//--------------------------------------------------------------
bool  ofxGuiNumberData::addValue(float val, ofxGuiRange _bounds, ofxGuiRange _range) {

    // prepare iterators
    // start inserting
    historyLength.push_back(_defaults->dataHistoryLength);
    deque<float> initQ(_defaults->dataHistoryLength, val); // create a history
    values.push_back(initQ); // add the queue
    
    bounds.push_back(_bounds);
    ranges.push_back(_range);

    displayPrecision.push_back(_defaults->displayPrecision);


    if(isBoolType() || isIntType()) {
        incrementValues.push_back(_defaults->incrementInt);
    } else if(isFloatType()) {
        incrementValues.push_back(_defaults->incrementFloat);
    }

    bool boundsChanged = false;
    bool rangeChanged = false;
    bool valueChanged = false;
    checkRange(boundsChanged, rangeChanged, getNumValues()-1);
    constrainValue(valueChanged, getNumValues()-1);

}

//--------------------------------------------------------------
bool  ofxGuiNumberData::insertValue(int index, float val) {
    insertValue(index, val, ofxGuiRange());
}
//--------------------------------------------------------------
bool  ofxGuiNumberData::insertValue(int index, float val, ofxGuiRange _bounds) {
    insertValue(index, val, _bounds, ofxGuiRange());
}
//--------------------------------------------------------------
bool  ofxGuiNumberData::insertValue(int index, float val, ofxGuiRange _bounds, ofxGuiRange _range) {
    if(isValidInsertionIndex(index)) {
        // prepare iterators
        valuesIter = values.begin() + index;
        historyLengthIter = historyLength.begin() + index;
        boundsIter = bounds.begin() + index;
        rangesIter = ranges.begin() + index;
        displayPrecisionIter = displayPrecision.begin() + index; 
        incrementValuesIter = incrementValues.begin() + index;
        
        // start inserting
        
        historyLength.insert(historyLengthIter, _defaults->dataHistoryLength);
        deque<float> initQ(_defaults->dataHistoryLength, val); // create a history
        values.push_back(initQ); // add the queue
        values.insert(valuesIter, initQ);

        bounds.insert(boundsIter, _bounds);
        ranges.insert(rangesIter, _range);
        
        // if it's global, take it from the other
        displayPrecision.insert(displayPrecisionIter, _defaults->displayPrecision);
        
        
        if(isBoolType() || isIntType()) {
            incrementValues.insert(incrementValuesIter, _defaults->incrementInt);
        } else if(isFloatType()) {
            incrementValues.insert(incrementValuesIter, _defaults->incrementFloat);
        }
        
        bool boundsChanged = false;
        bool rangeChanged = false;
        bool valueChanged = false;        
        checkRange(boundsChanged, rangeChanged, index);
        constrainValue(valueChanged,index);
        
    } else {
        return false;
    }
}

//--------------------------------------------------------------
bool  ofxGuiNumberData::removeValue(int index) {
    if(isValidIndex(index)) { 
        // WE CAN REMOVE THE LAST ONE ... just be careful
        valuesIter = values.begin() + index;
        boundsIter = bounds.begin() + index;
        rangesIter = ranges.begin() + index;
        displayPrecisionIter = displayPrecision.begin() + index; 
        incrementValuesIter = incrementValues.begin() + index;
        
        // start inserting
        values.erase(valuesIter);
        bounds.erase(boundsIter);
        ranges.erase(rangesIter);
        displayPrecision.erase(displayPrecisionIter);
        incrementValues.erase(incrementValuesIter);
        return true;
    } else {
        return false;
    }
}

//--------------------------------------------------------------
// BOUNDS AND RANGE ////////////////////////////////////////////
//--------------------------------------------------------------

//--------------------------------------------------------------
bool ofxGuiNumberData::setBounds(float _min, float _max, int index) {
    setBounds(ofxGuiRange(_min, _max),index);
}

//--------------------------------------------------------------
bool ofxGuiNumberData::setBounds(ofxGuiRange _range, int index) {
    if(isValidIndex(index)) {
        if(_range == bounds[index]) return true;
        bounds[index] = _range;
        bool _boundsChanged = false;
        bool _rangeChanged = false;
        bool _valueChanged = false;
        
        checkRange(_boundsChanged, _rangeChanged, index);
        constrainValue(_valueChanged,index);

        boundsChanged(index); // we know that they did
        if(_rangeChanged) rangeChanged(index);
        if(_valueChanged) dataChanged(index);  // does not push another value onto the stack in this case
        
        
        //cout << "boundsMin/max=" << bounds[index].getMin() << "/" << bounds[index].getMax() << endl;
        
        return true;
    } else {
        return false;
    }
}

bool ofxGuiNumberData::setBoundsMin(float _min, int index) {
    return setBounds(_min,bounds[index].getMax(),index);
}

//--------------------------------------------------------------
bool ofxGuiNumberData::setBoundsMax(float _max, int index) {
    return setBounds(bounds[index].getMin(),_max,index);
}

//--------------------------------------------------------------
float ofxGuiNumberData::getBoundsMin(int index) const {
    if(isValidIndex(index)) {
        return bounds[index].getMin();
    } else {
        return 0;
    }
}
//--------------------------------------------------------------
float ofxGuiNumberData::getBoundsMax(int index) const {
    if(isValidIndex(index)) {
        return bounds[index].getMax();
    } else {
        return 0;
    }
}


//--------------------------------------------------------------
ofxGuiRange ofxGuiNumberData::getBounds(int index) const {
    if(isValidIndex(index)) {
        return bounds[index];
    } else {
        return ofxGuiRange();
    }
}


//--------------------------------------------------------------
bool ofxGuiNumberData::setRangeMin(float _min, int index) {
    return setRange(_min,ranges[index].getMax(),index);
}

//--------------------------------------------------------------
bool ofxGuiNumberData::setRangeMax(float _max, int index) {
    return setRange(ranges[index].getMin(),_max,index);
}

//--------------------------------------------------------------
float ofxGuiNumberData::getRangeMin(int index) const {
    if(isValidIndex(index)) {
        return ranges[index].getMin();
    } else {
        return 0;
    }
}
//--------------------------------------------------------------
float ofxGuiNumberData::getRangeMax(int index) const{
    if(isValidIndex(index)) {
        return ranges[index].getMax();
    } else {
        return 0;
    }
}

//--------------------------------------------------------------
bool ofxGuiNumberData::setNormalizedRangeMin(float _min, int index) {
    return setRangeMin(bounds[index].denormalize(_min),index);
}

//--------------------------------------------------------------
bool ofxGuiNumberData::setNormalizedRangeMax(float _max, int index) {
    return setRangeMax(bounds[index].denormalize(_max),index);
}

//--------------------------------------------------------------
float ofxGuiNumberData::getNormalizedRangeMin(int index) const {
    if(isValidIndex(index)) {
        return bounds[index].normalize(ranges[index].getMin());
    } else {
        return 0;
    }
}
//--------------------------------------------------------------
float ofxGuiNumberData::getNormalizedRangeMax(int index) const {
    if(isValidIndex(index)) {
        return bounds[index].normalize(ranges[index].getMax());
    } else {
        return 0;
    }
}

//--------------------------------------------------------------
bool ofxGuiNumberData::setRange(float _min, float _max, int index) {
    setRange(ofxGuiRange(_min,_max), index);
}

//--------------------------------------------------------------
bool ofxGuiNumberData::setRange(ofxGuiRange _range, int index) {
    if(isValidIndex(index)) {
        if(hasRange && _range == ranges[index]) return;

        
        //cout << "in range " << _range.getMin() << "/" << _range.getMax() << endl;
        
        hasRange = true;
        ranges[index] = _range;

        bool _boundsChanged = false;
        bool _rangeChanged = false;
        bool _valueChanged = false;

        checkRange(_boundsChanged, _rangeChanged, index);
        constrainValue(_valueChanged, index);

        // callbacks
        if(_valueChanged) dataChanged(index);
        rangeChanged(index);
        if(_boundsChanged) boundsChanged(index);
    

       // cout << "out range " << _range.getMin() << "/" << _range.getMax() << endl;

        
        return true;
    } else {
        return false;
    }
}

//--------------------------------------------------------------
ofxGuiRange ofxGuiNumberData::getRange(int index) const {
    if(isValidIndex(index)) {
        return ranges[index];
    } else {
        return ofxGuiRange(-1,-1);
    }
}

//--------------------------------------------------------------
bool ofxGuiNumberData::clearRange(int index) {
    if(isValidIndex(index)) {
        if(hasRange) {
            hasRange = false;
            ranges[index].clear();
            rangeChanged(index);
        }
        return true;
    } else {
        return false;
    }
}

//--------------------------------------------------------------
bool ofxGuiNumberData::clearBounds(int index) {
    if(isValidIndex(index)) {
        if(bounds[index].isBounded()) {
            clearRange(index);
            bounds[index].clear();
            boundsChanged(index);
        }
        return true;
    } else {
        return false;
    }
}


//--------------------------------------------------------------
bool ofxGuiNumberData::isRangeEnabled() const {
    return hasRange;
}

//--------------------------------------------------------------
// DISPLAY PRECISION ///////////////////////////////////////////
//--------------------------------------------------------------

//--------------------------------------------------------------
bool ofxGuiNumberData::setDisplayPrecision(float _precision, int index) {
    if(isValidIndex(index)) {
        displayPrecision[index] = _precision;
        return true;
    } else {
        return false;
    }
}

//--------------------------------------------------------------
float ofxGuiNumberData::getDisplayPrecision(int index) const {
    if(isValidIndex(index)) {
        return displayPrecision[index];
    } else {
        return 0;
    }
}

//--------------------------------------------------------------
// INCREMENTING ////////////////////////////////////////////////
//--------------------------------------------------------------
bool ofxGuiNumberData::setIncrementValue(float _incrementValue, int index) {
    if(isValidIndex(index)) {
        incrementValues[index] = _incrementValue;
        return true;
    } else {
        return false;
    }
}

//--------------------------------------------------------------
float ofxGuiNumberData::getIncrementValue(int index) const {
    if(isValidIndex(index)) {
        return incrementValues[index];
    } else {
        return 0;
    }
}

//--------------------------------------------------------------
bool ofxGuiNumberData::increment(int index) {
    if(isValidIndex(index)) {
        add(incrementValues[index],index);
        return true;
    } else {
        return false;
    }
}
//--------------------------------------------------------------
bool ofxGuiNumberData::decrement(int index) {
    if(isValidIndex(index)) {
        subtract(incrementValues[index],index);
        return true;
    } else {
        return false;
    }
}

//--------------------------------------------------------------
bool ofxGuiNumberData::add(float value, int index) {
    if(isValidIndex(index)) {
        pushNewValue(values[index].back() + value, true, index);
        return true;
    } else {
        return false;
    }
}

//--------------------------------------------------------------
void ofxGuiNumberData::addAll(float value) {
    for(int i = 0; i < getNumValues(); i++) {
        add(value, i);
    }
}

//--------------------------------------------------------------
bool ofxGuiNumberData::subtract(float value, int index) {
    if(isValidIndex(index)) {
        pushNewValue(values[index].back() - value, true, index);
        return true;
    } else {
        return false;
    }
}

//--------------------------------------------------------------
void ofxGuiNumberData::subtractAll(float value) {
    for(int i = 0; i < getNumValues(); i++) {
        subtract(value, i);
    }
}

//--------------------------------------------------------------
bool ofxGuiNumberData::multiply(float value, int index) {
    if(isValidIndex(index)) {
        pushNewValue(values[index].back() * value, true, index);
        return true;
    } else {
        return false;
    }
}
//--------------------------------------------------------------
void ofxGuiNumberData::multiplyAll(float value) {
    for(int i = 0; i < getNumValues(); i++) {
        multiply(value, i);
    }
}

//--------------------------------------------------------------
bool ofxGuiNumberData::divide(float value, int index) {
    if(isValidIndex(index)) {
        pushNewValue(values[index].back() / value, true, index);
        return true;
    } else {
        return false;
    }
}

//--------------------------------------------------------------
void ofxGuiNumberData::divideAll(float value) {
    for(int i = 0; i < getNumValues(); i++) {
        divide(value, i);
    }
}

//--------------------------------------------------------------
bool ofxGuiNumberData::toggle(int index) {
    if(isValidIndex(index)) {
        if(!isBoolType()) ofLog(OF_LOG_WARNING, "ofxGuiNumberData: Toggling non boolean type.");

        pushNewValue(values[index].back() > 0.5 ? 0 : 1, true, index);
        
        return true;
    } else {
        return false;
    }
}

//--------------------------------------------------------------
void ofxGuiNumberData::toggleAll() {
    for(int i = 0; i < getNumValues(); i++) {
        toggle(i);
    }
}


//--------------------------------------------------------------
bool ofxGuiNumberData::invert(int index) {
    if(isValidIndex(index)) {
        pushNewValue(bounds[index].getMax() - values[index].back(), true, index);
        return true;
    } else {
        return false;
    }
}
//--------------------------------------------------------------
void ofxGuiNumberData::invertAll() {
    for(int i = 0; i < getNumValues(); i++) {
        invert(i);
    }
}

//--------------------------------------------------------------
float ofxGuiNumberData::normalize(float _value, int index) {
    if(isValidIndex(index)) {
        return bounds[index].normalize(_value);
    } else {
        return 0;
    }
}

//--------------------------------------------------------------
float ofxGuiNumberData::denormalize(float _value, int index) {
    if(isValidIndex(index)) {
        return bounds[index].denormalize(_value);
    } else {
        return 0;
    }
}

//--------------------------------------------------------------
float ofxGuiNumberData::rangeNormalize(float _value, int index) {
    if(isValidIndex(index)) {
        return ranges[index].normalize(_value);
    } else {
        return 0;
    }
}

//--------------------------------------------------------------
float ofxGuiNumberData::rangeDenormalize(float _value, int index) {
    if(isValidIndex(index)) {
        return ranges[index].denormalize(_value);
    } else {
        return 0;
    }
}



/*
//--------------------------------------------------------------
// QUANTIZATION ////////////////////////////////////////////////
//--------------------------------------------------------------
bool ofxGuiNumberData::setQuantizationSteps(int _numSteps, int index) {
    if(isValidIndex(index)) {
        if(isGlobalBounds()) {
            boundsIter = bounds.begin();
            for(boundsIter = bounds.begin(); 
                boundsIter != bounds.end(); 
                ++boundsIter) {
                (*boundsIter).setQuantizationSteps(_numSteps);
            }
            
        } else {
            bounds[index].setQuantizationSteps(_numSteps);
        }
        return true;
    } else {
        return false;
    }
}

//--------------------------------------------------------------
int ofxGuiNumberData::getQuantizationSteps(int index) {
    if(isValidIndex(index)) {
        return bounds[index].getQuantizationSteps();
    } else {
        return -1;
    }
}

//--------------------------------------------------------------
bool ofxGuiNumberData::disableQuantization(int index) {
    if(isValidIndex(index)) {
        if(isGlobalBounds()) {
            boundsIter = bounds.begin();
            for(boundsIter = bounds.begin(); 
                boundsIter != bounds.end(); 
                ++boundsIter) {
                (*boundsIter).disableQuantization();
            }
            
        } else {
            bounds[index].disableQuantization();
        }
        return true;
    } else {
        return false;
    }
}
*/

//--------------------------------------------------------------
// TO STRING ///////////////////////////////////////////////////
//--------------------------------------------------------------
string ofxGuiNumberData::toString(int index) {
    if(isValidIndex(index)) {
        return ofToString(values[index].back(),displayPrecision[index]);
    } else {
        return "INVALID INDEX";
    }
}

string ofxGuiNumberData::historyToString(int index) {
    if(isValidIndex(index)) {
        ostringstream out;
        out << "History (" << index << ") ";
        for(queueIter = values[index].begin(); queueIter != values[index].end(); ++queueIter) {
            out << *queueIter << ",";
        }
        return out.str();
    } else {
        return "INVALID INDEX";
    }
}
string ofxGuiNumberData::boundsToString(int index) {
    if(isValidIndex(index)) {
        ostringstream out;
        out << "Bounds (" << index << ") ";
        out << "(" << getBounds().getMin() << "," << getBounds().getMax() << ")" << endl;
        return out.str();
    } else {
        return "INVALID INDEX";
    }
}

string ofxGuiNumberData::rangeToString(int index) {
    if(isValidIndex(index)) {
        ostringstream out;
        out << "Range (" << index << ") ";
        out << "(" << getBounds().getMin() << "," << getBounds().getMax() << ")" << endl;
        return out.str();
    } else {
        return "INVALID INDEX";
    }
}


//--------------------------------------------------------------
bool ofxGuiNumberData::isValidIndex(int index) const {
    if(index == 0 || (index > 0 && index < getNumValues() && isArrayType())) {
        return true;
    } else {
        ofLog(OF_LOG_ERROR, "ofxGuiNumberData: invalid index " + index);
        return false; // a negative index is never good
    } 
}

//--------------------------------------------------------------
bool ofxGuiNumberData::isValidInsertionIndex(int index) const {
    if(isArrayType() && index > -1 && index <= getNumValues()) {
        return true;
    } else {
        ofLog(OF_LOG_ERROR, "ofxGuiNumberData: invalid insertion index " + ofToString(index) + " where size = " +ofToString(getNumValues()));
        return false;
    }
}


//--------------------------------------------------------------
bool ofxGuiNumberData::canUseSetAll() const {
    if(getNumValues() > 0 && isArrayType()) {
        return true;
    } else {
        ofLog(OF_LOG_WARNING, "ofxGuiNumberData: unable to set all - invalid numValues < 1 or not array type");
        return false; // a negative index is never good
    }
                                
}

//--------------------------------------------------------------
void ofxGuiNumberData::constrainValue(bool& _valueChanged, int index) {
// todo, report changed value
    int lastValueIndex = values[index].size()-1; 
    float tmpVal = values[index].back();
    
    values[index][lastValueIndex] = bounds[index].constrain(values[index][lastValueIndex]);         
                  
    if(hasRange) {
        values[index][lastValueIndex] = ranges[index].constrain(values[index][lastValueIndex]);
    }
    
    // set the changed bit
    _valueChanged = values[index].back() != tmpVal;
}

//--------------------------------------------------------------
void ofxGuiNumberData::checkRange(bool& _boundsChanged, bool& _rangeChanged, int index) {
    if(!isRangeEnabled()) return;
    
    float constrainedRangeMin = 0;
    float constrainedRangeMax = 0;
    
    bool rangeMinChanged = false;
    bool rangeMaxChanged = false;

    
    bool boundsMinChanged = false;
    bool boundsMaxChanged = false;
    // make sure bounds are set.  cannot have a range without bounds
    if(!bounds[index].isMinSet()) {
        bounds[index].setMin(ranges[index].getMin());
        boundsMinChanged = true;
    }

    if(!bounds[index].isMaxSet()) {
        bounds[index].setMax(ranges[index].getMax());
        boundsMaxChanged = true;
    }
    
    // callback
    _boundsChanged = boundsMinChanged || boundsMaxChanged;

    
    // NOW WE KNOW THAT BOUNDS ARE SET FOR SURE
    
    constrainedRangeMin = bounds[index].constrain(ranges[index].getMin());
    if(constrainedRangeMin != ranges[index].getMin()) {
        ranges[index].setMin(constrainedRangeMin);
        rangeMinChanged = true;
    }
    
    constrainedRangeMax = bounds[index].constrain(ranges[index].getMax());
    if(constrainedRangeMax != ranges[index].getMax()) {
        ranges[index].setMax(constrainedRangeMax);
        rangeMaxChanged = true;
    }

    _rangeChanged = rangeMinChanged || rangeMaxChanged;
}
      
//--------------------------------------------------------------
bool ofxGuiNumberData::isBoolType() const {
    return dataType == OFXGUI_BOOL || dataType == OFXGUI_BOOL_ARRAY;
}
//--------------------------------------------------------------
bool ofxGuiNumberData::isFloatType() const {
   return dataType == OFXGUI_FLOAT || dataType == OFXGUI_FLOAT_ARRAY;
}
//--------------------------------------------------------------
bool ofxGuiNumberData::isIntType() const {
   return dataType == OFXGUI_INT || dataType == OFXGUI_INT_ARRAY;
}

//--------------------------------------------------------------
bool ofxGuiNumberData::isArrayType() const {
    return  dataType == OFXGUI_BOOL_ARRAY ||
            dataType == OFXGUI_INT_ARRAY  ||
            dataType == OFXGUI_FLOAT_ARRAY;
}

//--------------------------------------------------------------
void ofxGuiNumberData::init(int initialSize) {
    
    if(!isArrayType() && initialSize > 1) {
        ofLog(OF_LOG_ERROR, "ofxGuiNumberData: trying to init an array, but data type is incorrect");
    }
    
    _defaults = &ofxGuiDefaults::getInstance(); // get a link to the singleton

    // no range to start
    hasRange = false;
    // do not use global to start.  if you do, this will fail

    for(int i = 0; i < initialSize; i++) {
        addValue(0);
    }
    
    //cout << "after setup, initial size is " << getNumValues() << endl;

    //cout << ">>INIT BOUNDS >> " << getBounds().toString() << endl;
    //cout << ">>INIT RANGE >> " << getRange().toString() << endl;
    //cout << ">>>>>>>>>>" << endl;
    
}

//--------------------------------------------------------------
void ofxGuiNumberData::setClosestRangeLimit(float norm) {
    float dMin = fabs(norm - getNormalizedRangeMin());
    float dMax = fabs(norm - getNormalizedRangeMax());
    if(dMin > dMax) {
        setNormalizedRangeMax(norm);
    } else {
        setNormalizedRangeMin(norm);
    }
}

//--------------------------------------------------------------
void ofxGuiNumberData::setRightOrLeftRangeLimit(float norm) {
    if(norm > getNormalizedValue()) {
        setNormalizedRangeMax(norm);
    } else {
        setNormalizedRangeMin(norm);
    }
}





