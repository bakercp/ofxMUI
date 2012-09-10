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