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

    std::unique_ptr<Layout::Document> mui;

};


