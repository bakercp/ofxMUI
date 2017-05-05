//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofApp.h"


void ofApp::setup()
{
    ofSetFrameRate(60);

    ofx::RegisterPointerEvents(this);
    
    ofSetLogLevel(OF_LOG_VERBOSE);

    mui = std::make_unique<ofx::DOM::Document>();

    auto panelA = mui->attachChild(std::make_unique<ofx::MUI::Panel>("A", 50, 50, 400, 400));
    auto panelB = panelA->attachChild(std::make_unique<ofx::MUI::Panel>("B", 50, 50, 300, 300));
    panelB->attachChild(std::make_unique<ofx::MUI::Panel>("C", 50, 50, 200, 200));
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
