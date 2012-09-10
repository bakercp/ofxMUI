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

#include "ofxMuiNumberData.h"

//--------------------------------------------------------------
// CONSTRUCTORS+DESTRUCTORS ////////////////////////////////////
//--------------------------------------------------------------
ofxMuiNumberData::ofxMuiNumberData() {
    dataType = ofxMui_FLOAT;
    init(1);
}
//--------------------------------------------------------------
ofxMuiNumberData::ofxMuiNumberData(const ofxMuiNumberDataType& _dataType) {
    dataType = _dataType;
    init(1);
}
//--------------------------------------------------------------
ofxMuiNumberData::ofxMuiNumberData(const ofxMuiNumberDataType& _dataType, int _initialSize) {
    dataType = _dataType;
    init(_initialSize);
}
//--------------------------------------------------------------
ofxMuiNumberData::~ofxMuiNumberData() {
    // nothing to do
}
//--------------------------------------------------------------
// DATA TYPE ///////////////////////////////////////////////////
//--------------------------------------------------------------
void ofxMuiNumberData::setDataType(const ofxMuiNumberDataType& _dataType) {
    dataType = _dataType;
    // TODO -- DO CHECKING HERE??
}
//--------------------------------------------------------------
ofxMuiNumberDataType ofxMuiNumberData::getDataType() const {
    return dataType;
}

//--------------------------------------------------------------
void ofxMuiNumberData::pushNewValue(float value, bool constrain, int index) {
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
bool  ofxMuiNumberData::setValue(float val, int index) {
    if(isValidIndex(index)) {
        pushNewValue(val,true,index);
        return true;
    } else {
        return false;
    }
}
//--------------------------------------------------------------
void  ofxMuiNumberData::setAllValues(float val) {
    if(canUseSetAll()) {
        for(int i = 0; i < getNumValues(); i++) pushNewValue(val,true, i);
    }
}
//--------------------------------------------------------------
bool  ofxMuiNumberData::setNormalizedValue(float val, int index) {
    if(isValidIndex(index) && bounds[index].isBounded()) {
        pushNewValue(bounds[index].denormalize(val),true,index);
        return true;
    } else {
        return false;
    }
}
//--------------------------------------------------------------
void  ofxMuiNumberData::setAllNormalizedValues(float val) {
    if(canUseSetAll()) {
        for(int i = 0; i < getNumValues(); i++) setNormalizedValue(val,i);
    }
}

//--------------------------------------------------------------
float ofxMuiNumberData::getValue(int index) const {
    if(isValidIndex(index)) {
        // conditionally quantize based on the BOUNDS, not the range
        return values[index].back();//bounds[index];.quantize(values[index]);
    } else {
        ofLog(OF_LOG_ERROR, "ofxMuiNumberData:: Attempted to get an invalid value.");
        return 0;
    }
}
//--------------------------------------------------------------
float ofxMuiNumberData::getValueFloat(int index) const {
    return getValue(index);
}
//--------------------------------------------------------------
int   ofxMuiNumberData::getValueInt(int index) const {
    return (int)getValue(index);
}
//--------------------------------------------------------------
bool  ofxMuiNumberData::getValueBool(int index) const {
    return (bool)getValue(index);
}

//--------------------------------------------------------------
float ofxMuiNumberData::getNormalizedValue(int index) const {
    if(isValidIndex(index) && bounds[index].isBounded()) {
        return bounds[index].normalize(getValue());
    } else {
        ofLog(OF_LOG_WARNING,"ofxMuiNumberData:: Attempting to get a normalized value from an unbounded range.");
        return false;
    }
}

//--------------------------------------------------------------
float ofxMuiNumberData::getLastValue(int index) const {
    if(isValidIndex(index)) {
        // conditionally quantize based on the BOUNDS, not the range
        return values[index][values[index].size()-2];//bounds[index];.quantize(values[index]);
    } else {
        ofLog(OF_LOG_ERROR, "ofxMuiNumberData:: Attempted to get an invalid value.");
        return 0;
    }
}
//--------------------------------------------------------------
float ofxMuiNumberData::getLastValueFloat(int index) const {
    return getLastValue(index);
}
//--------------------------------------------------------------
int   ofxMuiNumberData::getLastValueInt(int index) const {
    return (int)getLastValue(index);
}
//--------------------------------------------------------------
bool  ofxMuiNumberData::getLastValueBool(int index) const {
    return (bool)getLastValue(index);
}

//--------------------------------------------------------------
float ofxMuiNumberData::getLastNormalizedValue(int index) const {
    if(isValidIndex(index) && bounds[index].isBounded()) {
        return bounds[index].normalize(getLastValue());
        // TODO ... this is trick ... it's possible that the bounds
        // could have changed ... resulting in an incorrect last value?
        // unlikely, yes.
    } else {
        ofLog(OF_LOG_WARNING,"ofxMuiNumberData:: Attempting to get a normalized value from an unbounded range.");
        return false;
    }
}

//--------------------------------------------------------------
float ofxMuiNumberData::getDeltaValue(int index) const {
    if(isValidIndex(index)) {
        // conditionally quantize based on the BOUNDS, not the range
        return (values[index][values[index].size()-2] - values[index].back());//bounds[index];.quantize(values[index]);
    } else {
        ofLog(OF_LOG_ERROR, "ofxMuiNumberData:: Attempted to get an invalid value.");
        return 0;
    }
}
//--------------------------------------------------------------
float ofxMuiNumberData::getDeltaValueFloat(int index) const {
    return getDeltaValue(index);
}
//--------------------------------------------------------------
int   ofxMuiNumberData::getDeltaValueInt(int index) const {
    return (int)(getDeltaValue(index));
}
//--------------------------------------------------------------
bool  ofxMuiNumberData::getDeltaValueBool(int index) const {
    return (bool)(getDeltaValue(index));
}

//--------------------------------------------------------------
int   ofxMuiNumberData::getNumValues() const {
    return values.size();;
}

//--------------------------------------------------------------
// HISTORY ////////////////////////////////////////////////////
//--------------------------------------------------------------
bool ofxMuiNumberData::setHistoryLength(int length, int index) {
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
            ofLog(OF_LOG_ERROR, "ofxMuiNumberData:: Invalid history length value.  HistoryLength value must be >= 2.");
            return false;
        }
    } else {
        ofLog(OF_LOG_ERROR, "ofxMuiNumberData:: Attempted to get an invalid value.");
        return 0;
    }
}

//--------------------------------------------------------------
int ofxMuiNumberData::getHistoryLength(int index) const {
    if(isValidIndex(index)) {
        return historyLength[index];
    } else {
        return -1;
    }
}


//--------------------------------------------------------------
// ADDING/INSERTING/REMOVING ///////////////////////////////////
//--------------------------------------------------------------
bool  ofxMuiNumberData::addValue(float val) {
    addValue(val, ofxMuiRange());
}
//--------------------------------------------------------------
bool  ofxMuiNumberData::addValue(float val, ofxMuiRange _bounds) {
    addValue(val, _bounds, ofxMuiRange());
}
//--------------------------------------------------------------
bool  ofxMuiNumberData::addValue(float val, ofxMuiRange _bounds, ofxMuiRange _range) {

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
bool  ofxMuiNumberData::insertValue(int index, float val) {
    insertValue(index, val, ofxMuiRange());
}
//--------------------------------------------------------------
bool  ofxMuiNumberData::insertValue(int index, float val, ofxMuiRange _bounds) {
    insertValue(index, val, _bounds, ofxMuiRange());
}
//--------------------------------------------------------------
bool  ofxMuiNumberData::insertValue(int index, float val, ofxMuiRange _bounds, ofxMuiRange _range) {
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
bool  ofxMuiNumberData::removeValue(int index) {
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
bool ofxMuiNumberData::setBounds(float _min, float _max, int index) {
    setBounds(ofxMuiRange(_min, _max),index);
}

//--------------------------------------------------------------
bool ofxMuiNumberData::setBounds(ofxMuiRange _range, int index) {
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

bool ofxMuiNumberData::setBoundsMin(float _min, int index) {
    return setBounds(_min,bounds[index].getMax(),index);
}

//--------------------------------------------------------------
bool ofxMuiNumberData::setBoundsMax(float _max, int index) {
    return setBounds(bounds[index].getMin(),_max,index);
}

//--------------------------------------------------------------
float ofxMuiNumberData::getBoundsMin(int index) const {
    if(isValidIndex(index)) {
        return bounds[index].getMin();
    } else {
        return 0;
    }
}
//--------------------------------------------------------------
float ofxMuiNumberData::getBoundsMax(int index) const {
    if(isValidIndex(index)) {
        return bounds[index].getMax();
    } else {
        return 0;
    }
}


//--------------------------------------------------------------
ofxMuiRange ofxMuiNumberData::getBounds(int index) const {
    if(isValidIndex(index)) {
        return bounds[index];
    } else {
        return ofxMuiRange();
    }
}


//--------------------------------------------------------------
bool ofxMuiNumberData::setRangeMin(float _min, int index) {
    return setRange(_min,ranges[index].getMax(),index);
}

//--------------------------------------------------------------
bool ofxMuiNumberData::setRangeMax(float _max, int index) {
    return setRange(ranges[index].getMin(),_max,index);
}

//--------------------------------------------------------------
float ofxMuiNumberData::getRangeMin(int index) const {
    if(isValidIndex(index)) {
        return ranges[index].getMin();
    } else {
        return 0;
    }
}
//--------------------------------------------------------------
float ofxMuiNumberData::getRangeMax(int index) const{
    if(isValidIndex(index)) {
        return ranges[index].getMax();
    } else {
        return 0;
    }
}

//--------------------------------------------------------------
bool ofxMuiNumberData::setNormalizedRangeMin(float _min, int index) {
    return setRangeMin(bounds[index].denormalize(_min),index);
}

//--------------------------------------------------------------
bool ofxMuiNumberData::setNormalizedRangeMax(float _max, int index) {
    return setRangeMax(bounds[index].denormalize(_max),index);
}

//--------------------------------------------------------------
float ofxMuiNumberData::getNormalizedRangeMin(int index) const {
    if(isValidIndex(index)) {
        return bounds[index].normalize(ranges[index].getMin());
    } else {
        return 0;
    }
}
//--------------------------------------------------------------
float ofxMuiNumberData::getNormalizedRangeMax(int index) const {
    if(isValidIndex(index)) {
        return bounds[index].normalize(ranges[index].getMax());
    } else {
        return 0;
    }
}

//--------------------------------------------------------------
bool ofxMuiNumberData::setRange(float _min, float _max, int index) {
    setRange(ofxMuiRange(_min,_max), index);
}

//--------------------------------------------------------------
bool ofxMuiNumberData::setRange(ofxMuiRange _range, int index) {
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
ofxMuiRange ofxMuiNumberData::getRange(int index) const {
    if(isValidIndex(index)) {
        return ranges[index];
    } else {
        return ofxMuiRange(-1,-1);
    }
}

//--------------------------------------------------------------
bool ofxMuiNumberData::clearRange(int index) {
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
bool ofxMuiNumberData::clearBounds(int index) {
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
bool ofxMuiNumberData::isRangeEnabled() const {
    return hasRange;
}

//--------------------------------------------------------------
// DISPLAY PRECISION ///////////////////////////////////////////
//--------------------------------------------------------------

//--------------------------------------------------------------
bool ofxMuiNumberData::setDisplayPrecision(float _precision, int index) {
    if(isValidIndex(index)) {
        displayPrecision[index] = _precision;
        return true;
    } else {
        return false;
    }
}

//--------------------------------------------------------------
float ofxMuiNumberData::getDisplayPrecision(int index) const {
    if(isValidIndex(index)) {
        return displayPrecision[index];
    } else {
        return 0;
    }
}

//--------------------------------------------------------------
// INCREMENTING ////////////////////////////////////////////////
//--------------------------------------------------------------
bool ofxMuiNumberData::setIncrementValue(float _incrementValue, int index) {
    if(isValidIndex(index)) {
        incrementValues[index] = _incrementValue;
        return true;
    } else {
        return false;
    }
}

//--------------------------------------------------------------
float ofxMuiNumberData::getIncrementValue(int index) const {
    if(isValidIndex(index)) {
        return incrementValues[index];
    } else {
        return 0;
    }
}

//--------------------------------------------------------------
bool ofxMuiNumberData::increment(int index) {
    if(isValidIndex(index)) {
        add(incrementValues[index],index);
        return true;
    } else {
        return false;
    }
}
//--------------------------------------------------------------
bool ofxMuiNumberData::decrement(int index) {
    if(isValidIndex(index)) {
        subtract(incrementValues[index],index);
        return true;
    } else {
        return false;
    }
}

//--------------------------------------------------------------
bool ofxMuiNumberData::add(float value, int index) {
    if(isValidIndex(index)) {
        pushNewValue(values[index].back() + value, true, index);
        return true;
    } else {
        return false;
    }
}

//--------------------------------------------------------------
void ofxMuiNumberData::addAll(float value) {
    for(int i = 0; i < getNumValues(); i++) {
        add(value, i);
    }
}

//--------------------------------------------------------------
bool ofxMuiNumberData::subtract(float value, int index) {
    if(isValidIndex(index)) {
        pushNewValue(values[index].back() - value, true, index);
        return true;
    } else {
        return false;
    }
}

//--------------------------------------------------------------
void ofxMuiNumberData::subtractAll(float value) {
    for(int i = 0; i < getNumValues(); i++) {
        subtract(value, i);
    }
}

//--------------------------------------------------------------
bool ofxMuiNumberData::multiply(float value, int index) {
    if(isValidIndex(index)) {
        pushNewValue(values[index].back() * value, true, index);
        return true;
    } else {
        return false;
    }
}
//--------------------------------------------------------------
void ofxMuiNumberData::multiplyAll(float value) {
    for(int i = 0; i < getNumValues(); i++) {
        multiply(value, i);
    }
}

//--------------------------------------------------------------
bool ofxMuiNumberData::divide(float value, int index) {
    if(isValidIndex(index)) {
        pushNewValue(values[index].back() / value, true, index);
        return true;
    } else {
        return false;
    }
}

//--------------------------------------------------------------
void ofxMuiNumberData::divideAll(float value) {
    for(int i = 0; i < getNumValues(); i++) {
        divide(value, i);
    }
}

//--------------------------------------------------------------
bool ofxMuiNumberData::toggle(int index) {
    if(isValidIndex(index)) {
        if(!isBoolType()) ofLog(OF_LOG_WARNING, "ofxMuiNumberData: Toggling non boolean type.");

        pushNewValue(values[index].back() > 0.5 ? 0 : 1, true, index);
        
        return true;
    } else {
        return false;
    }
}

//--------------------------------------------------------------
void ofxMuiNumberData::toggleAll() {
    for(int i = 0; i < getNumValues(); i++) {
        toggle(i);
    }
}


//--------------------------------------------------------------
bool ofxMuiNumberData::invert(int index) {
    if(isValidIndex(index)) {
        pushNewValue(bounds[index].getMax() - values[index].back(), true, index);
        return true;
    } else {
        return false;
    }
}
//--------------------------------------------------------------
void ofxMuiNumberData::invertAll() {
    for(int i = 0; i < getNumValues(); i++) {
        invert(i);
    }
}

//--------------------------------------------------------------
float ofxMuiNumberData::normalize(float _value, int index) {
    if(isValidIndex(index)) {
        return bounds[index].normalize(_value);
    } else {
        return 0;
    }
}

//--------------------------------------------------------------
float ofxMuiNumberData::denormalize(float _value, int index) {
    if(isValidIndex(index)) {
        return bounds[index].denormalize(_value);
    } else {
        return 0;
    }
}

//--------------------------------------------------------------
float ofxMuiNumberData::rangeNormalize(float _value, int index) {
    if(isValidIndex(index)) {
        return ranges[index].normalize(_value);
    } else {
        return 0;
    }
}

//--------------------------------------------------------------
float ofxMuiNumberData::rangeDenormalize(float _value, int index) {
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
bool ofxMuiNumberData::setQuantizationSteps(int _numSteps, int index) {
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
int ofxMuiNumberData::getQuantizationSteps(int index) {
    if(isValidIndex(index)) {
        return bounds[index].getQuantizationSteps();
    } else {
        return -1;
    }
}

//--------------------------------------------------------------
bool ofxMuiNumberData::disableQuantization(int index) {
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
string ofxMuiNumberData::toString(int index) {
    if(isValidIndex(index)) {
        return ofToString(values[index].back(),displayPrecision[index]);
    } else {
        return "INVALID INDEX";
    }
}

string ofxMuiNumberData::historyToString(int index) {
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
string ofxMuiNumberData::boundsToString(int index) {
    if(isValidIndex(index)) {
        ostringstream out;
        out << "Bounds (" << index << ") ";
        out << "(" << getBounds().getMin() << "," << getBounds().getMax() << ")" << endl;
        return out.str();
    } else {
        return "INVALID INDEX";
    }
}

string ofxMuiNumberData::rangeToString(int index) {
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
bool ofxMuiNumberData::isValidIndex(int index) const {
    if(index == 0 || (index > 0 && index < getNumValues() && isArrayType())) {
        return true;
    } else {
        ofLog(OF_LOG_ERROR, "ofxMuiNumberData: invalid index " + index);
        return false; // a negative index is never good
    } 
}

//--------------------------------------------------------------
bool ofxMuiNumberData::isValidInsertionIndex(int index) const {
    if(isArrayType() && index > -1 && index <= getNumValues()) {
        return true;
    } else {
        ofLog(OF_LOG_ERROR, "ofxMuiNumberData: invalid insertion index " + ofToString(index) + " where size = " +ofToString(getNumValues()));
        return false;
    }
}


//--------------------------------------------------------------
bool ofxMuiNumberData::canUseSetAll() const {
    if(getNumValues() > 0 && isArrayType()) {
        return true;
    } else {
        ofLog(OF_LOG_WARNING, "ofxMuiNumberData: unable to set all - invalid numValues < 1 or not array type");
        return false; // a negative index is never good
    }
                                
}

//--------------------------------------------------------------
void ofxMuiNumberData::constrainValue(bool& _valueChanged, int index) {
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
void ofxMuiNumberData::checkRange(bool& _boundsChanged, bool& _rangeChanged, int index) {
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
bool ofxMuiNumberData::isBoolType() const {
    return dataType == ofxMui_BOOL || dataType == ofxMui_BOOL_ARRAY;
}
//--------------------------------------------------------------
bool ofxMuiNumberData::isFloatType() const {
   return dataType == ofxMui_FLOAT || dataType == ofxMui_FLOAT_ARRAY;
}
//--------------------------------------------------------------
bool ofxMuiNumberData::isIntType() const {
   return dataType == ofxMui_INT || dataType == ofxMui_INT_ARRAY;
}

//--------------------------------------------------------------
bool ofxMuiNumberData::isArrayType() const {
    return  dataType == ofxMui_BOOL_ARRAY ||
            dataType == ofxMui_INT_ARRAY  ||
            dataType == ofxMui_FLOAT_ARRAY;
}

//--------------------------------------------------------------
void ofxMuiNumberData::init(int initialSize) {
    
    if(!isArrayType() && initialSize > 1) {
        ofLog(OF_LOG_ERROR, "ofxMuiNumberData: trying to init an array, but data type is incorrect");
    }
    
    _defaults = &ofxMuiDefaults::getInstance(); // get a link to the singleton

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
void ofxMuiNumberData::setClosestRangeLimit(float norm) {
    float dMin = fabs(norm - getNormalizedRangeMin());
    float dMax = fabs(norm - getNormalizedRangeMax());
    if(dMin > dMax) {
        setNormalizedRangeMax(norm);
    } else {
        setNormalizedRangeMin(norm);
    }
}

//--------------------------------------------------------------
void ofxMuiNumberData::setRightOrLeftRangeLimit(float norm) {
    if(norm > getNormalizedValue()) {
        setNormalizedRangeMax(norm);
    } else {
        setNormalizedRangeMin(norm);
    }
}





