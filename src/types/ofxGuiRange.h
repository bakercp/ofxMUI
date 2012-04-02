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
    
    bool intersects(ofxGuiRange _range);
    
    
    // the same thing
    ofxGuiRange intersect(ofxGuiRange _range);
    ofxGuiRange constrain(ofxGuiRange _range);

    float constrain(float _value);

    bool contains(float _value);
    
    float mean();
    float lerp(float _value);
    float normalize(float _value);
    float denormalize(float _nValue);
    
    float getMin();
    float getMax();
    
    void clearMin();
    void clearMax();
    
    void clear();
    
    bool isMinSet();
    bool isMaxSet();
    
    bool isBounded();
    
    void invertExtrema();
    
    float delta();
    
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
    
    string toString();
    
private:
    float min, max;
    //int quantizationSteps; // < 1 is disabled
};