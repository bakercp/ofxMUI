//
//  ofxGuiRectangle.h
//  BasicExample
//
//  Created by Christopher Baker on 1/16/12.
//  Copyright (c) 2012 School of the Art Institute of Chicago. All rights reserved.
//

#pragma once

#include "ofMain.h"

class ofxGuiRectangle : ofRectangle {

public:
    ofxGuiRectangle ();
    ofxGuiRectangle (ofxGuiRectangle const & r);
    virtual ~ofxGuiRectangle ();
    void set (ofxGuiRectangle const & rect);

    float getX();
    float getY();
    float getWidth();
    float getHeight();
    
    void setX(float _x);
    void setY(float _y);
    
    ofPoint getCorner(int i = 0); // clock-wise from Northwest
    
};