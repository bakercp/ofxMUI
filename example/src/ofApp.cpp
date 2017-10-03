//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofApp.h"


void ofApp::setup()
{
    ofSetFrameRate(60);
    ofSetLogLevel(OF_LOG_VERBOSE);

    auto panelA = mui.addChild<ofxMUI::Panel>("A", 50, 50, 400, 400);
    auto panelB = panelA->addChild<ofxMUI::Panel>("B", 50, 50, 300, 300);
    auto panelC0 = panelB->addChild<ofxMUI::Panel>("C0", 50, 50, 200, 100);
    auto panelC1 = panelB->addChild<ofxMUI::Panel>("C1", 50, 150, 200, 100);

    panelC0->setFocusable(true);
    panelC1->setFocusable(true);

    auto buttonGroup = mui.addChild<ofxMUI::ButtonGroup>("Radio Group");
    buttonGroup->addRadioButton();
    buttonGroup->addRadioButton();
    buttonGroup->addRadioButton();

    //ofSystemAlertDialog("Error!");

    ofBackground(0);
}


void ofApp::draw()
{
}
