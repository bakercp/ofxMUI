//
//  ofxGuiBoundedRange.h
//  BasicExample
//
//  Created by Christopher Baker on 1/9/12.
//  Copyright (c) 2012 School of the Art Institute of Chicago. All rights reserved.
//

#pragma once

#include "ofMain.h"

class ofxGuiRange {
public:
    
    // essentially, this class just enforces the model of
    // min <= max
    
    ofxGuiRange();
    ofxGuiRange(float min, float max);
    
    virtual ~ofxGuiRange();
    
    void setMin(float _min);
    void setMax(float _max);
    
    void expandToFit(float _val);
    
    bool intersects(ofxGuiRange _range) const;
    
    
    // the same thing
    ofxGuiRange intersect(ofxGuiRange _range) const;
    ofxGuiRange constrain(ofxGuiRange _range) const;

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
    
    static ofxGuiRange fromArray(float* array, int cnt);
    static ofxGuiRange fromArray(vector<float> array);
    static ofxGuiRange roundOutward(ofxGuiRange& range);
    static ofxGuiRange roundInward(ofxGuiRange& range);
    

    bool operator==( const ofxGuiRange& vec ) const;
    bool operator!=( const ofxGuiRange& vec ) const;

    


    
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