//
//  ofxGuiData.h
//  BasicExample
//
//  Created by Christopher Baker on 1/9/12.
//  Copyright (c) 2012 School of the Art Institute of Chicago. All rights reserved.
//


#pragma once

#include "ofMain.h"

class ofxGuiData {
public:
    ofxGuiData() {}
    virtual ~ofxGuiData();

    virtual int getNumValues() {};
    virtual void toString(int index) {};

protected:
    virtual void dataChanged(int index) {};
        
};