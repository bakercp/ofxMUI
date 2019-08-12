//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier: MIT
//


#include "ofApp.h"


void ofApp::setup()
{
    using namespace ofxMUI;
    using namespace ofxDOM;

    ofSetFrameRate(60);
    ofSetLogLevel(OF_LOG_VERBOSE);

    Panel* panelA = mui.addChild<Panel>("A", 50, 50, 400, 400);

    ofBackground(0);
}


void ofApp::draw()
{
}
