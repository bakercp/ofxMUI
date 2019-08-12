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

    panelA->setDraggable(true);

    auto panelB = panelA->addChild<Panel>("B", 50, 50, 300, 300);
    auto panelC0 = panelB->addChild<Panel>("C0", 50, 50, 200, 100);
    auto panelC1 = panelB->addChild<Panel>("C1", 50, 150, 200, 100);

    panelC1->setDraggable(true);

    panelC0->setFocusable(true);
    panelC1->setFocusable(true);

    auto buttonGroup = mui.addChild<ButtonGroup>("Radio Group");
    buttonGroup->addRadioButton();
    buttonGroup->addRadioButton();
    buttonGroup->addRadioButton();

    auto buttonGroup2 = mui.addChild<ButtonGroup>("Radio Group 2",
                                                  100,
                                                  0,
                                                  Button::DEFAULT_WIDTH,
                                                  Button::DEFAULT_HEIGHT,
                                                  Orientation::HORIZONTAL);
    buttonGroup2->addRadioButton();
    buttonGroup2->addRadioButton();
    buttonGroup2->addRadioButton();

//    const std::string& id,
//    float x = 0,
//    float y = 0,
//    float width = Button::DEFAULT_WIDTH,
//    float height = Button::DEFAULT_HEIGHT,
//    DOM::Orientation orientation = DOM::Orientation::VERTICAL
    //ofSystemAlertDialog("Error!");

    ofBackground(0);
}


void ofApp::draw()
{
}
