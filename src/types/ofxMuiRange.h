//
//  ofxMuiBoundedRange.h
//  BasicExample
//
//  Created by Christopher Baker on 1/9/12.
//  Copyright (c) 2012 School of the Art Institute of Chicago. All rights reserved.
//

#pragma once

#include "ofMain.h"

class ofxMuiRange {
public:
    
    // essentially, this class just enforces the model of
    // min <= max
    
    ofxMuiRange();
    ofxMuiRange(float min, float max);
    
    virtual ~ofxMuiRange();
    
    void setMin(float _min);
    void setMax(float _max);
    
    void expandToFit(float _val);
    
    bool intersects(ofxMuiRange _range) const;
    
    
    // the same thing
    ofxMuiRange intersect(ofxMuiRange _range) const;
    ofxMuiRange constrain(ofxMuiRange _range) const;

    float constrain(float _value) const;

    bool contains(float _value) const;
    
    float mean() const;
    float lerp(float _value) const;
    float normalize(float _value) const;
    float denormalize(float _nValue) const;
    
    float getMin() const;
    float getMax() const;
    
    void clearMin();
    void clearMax();
    
    void clear();
    
    bool isMinSet() const;
    bool isMaxSet() const;
    
    bool isBounded() const;
    
    void invertExtrema();
    
    float delta() const;
    
    static ofxMuiRange fromArray(float* array, int cnt);
    static ofxMuiRange fromArray(vector<float> array);
    static ofxMuiRange roundOutward(ofxMuiRange& range);
    static ofxMuiRange roundInward(ofxMuiRange& range);
    

    bool operator==( const ofxMuiRange& vec ) const;
    bool operator!=( const ofxMuiRange& vec ) const;

    


    
    //float quantize(float _value);
    
    //void setQuantizationSteps(int _steps);
    //int  getQuantizationSteps();
    //bool isQuantizing();
    //void disableQuantization();
    
    string toString() const;
    
private:
    float min, max;
    //int quantizationSteps; // < 1 is disabled
};