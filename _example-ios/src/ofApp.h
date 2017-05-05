//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include "ofMain.h"
#include "ofxiOS.h"
#include "ofxiOSExtras.h"
#include "ofxMUI.h"


using namespace ofx;
using namespace ofx::MUI;


class ofApp: public ofxiOSApp
{
public:
    void setup();
    void draw();

    void onPointerUp(ofx::PointerEventArgs& evt);
    void onPointerDown(ofx::PointerEventArgs& evt);
    void onPointerMove(ofx::PointerEventArgs& evt);
    void onPointerCancel(ofx::PointerEventArgs& evt);

    std::unique_ptr<DOM::Document> mui;

};


