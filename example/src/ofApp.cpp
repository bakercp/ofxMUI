//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofApp.h"


void ofApp::setup()
{
    ofSetFrameRate(60);


    std::cout << ofIsFloatEqual(1.1f, 1.f) << std::endl;

    ofx::RegisterPointerEvents(this);
    
    ofSetLogLevel(OF_LOG_VERBOSE);

    auto panelA = mui.addChild<ofx::MUI::Panel>("A", 50, 50, 400, 400);
    auto panelB = panelA->addChild<ofx::MUI::Panel>("B", 50, 50, 300, 300);
    auto panelC0 = panelB->addChild<ofx::MUI::Panel>("C0", 50, 50, 200, 100);
    auto panelC1 = panelB->addChild<ofx::MUI::Panel>("C1", 50, 150, 200, 100);

    panelC0->setFocusable(true);
    panelC1->setFocusable(true);

    auto buttonGroup = mui.addChild<ofxMUI::ButtonGroup>("Radio Group");
    buttonGroup->addRadioButton();
    buttonGroup->addRadioButton();
    buttonGroup->addRadioButton();

}


void ofApp::draw()
{
    ofBackground(0);
}


void ofApp::onPointerUp(ofx::PointerEventArgs& evt)
{
    ofLogVerbose("ofApp::onPointerUp") << evt.toString();
}


void ofApp::onPointerDown(ofx::PointerEventArgs& evt)
{
    ofLogVerbose("ofApp::onPointerDown") << evt.toString();
}


void ofApp::onPointerMove(ofx::PointerEventArgs& evt)
{
//    ofLogVerbose("ofApp::onPointerMove") << evt.toString();
}


void ofApp::onPointerCancel(ofx::PointerEventArgs& evt)
{
//    ofLogVerbose("ofApp::onPointerCancel") << evt.toString();
}
