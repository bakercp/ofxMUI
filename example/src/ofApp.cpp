// =============================================================================
//
// Copyright (c) 2009-2014 Christopher Baker <http://christopherbaker.net>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// =============================================================================


#include "ofApp.h"


void ofApp::setup()
{
    ofSetFrameRate(60);

    ofx::RegisterPointerEvents(this);
    
    ofSetLogLevel(OF_LOG_VERBOSE);

    mui = std::make_unique<ofx::DOM::Document>();

    panelA = mui->addChild(std::make_unique<ofx::MUI::Panel>("A", 50, 50, 400, 400));

    ofAddListener(panelA->move, this, &ofApp::onMove);
    ofAddListener(panelA->resize, this, &ofApp::onResize);


    panelC = panelA->addChild(std::make_unique<ofx::MUI::Panel>("C", 250, 50, 150, 150));

    panelC1 = panelC->addChild(std::make_unique<ofx::MUI::Panel>("C1", 10, 10, 25, 25));
    panelC2 = panelC1->addChild(std::make_unique<ofx::MUI::Panel>("C2", 1, 1, 10, 10));


    panelB = panelA->addChild(std::make_unique<ofx::MUI::Panel>("B", 50, 50, 150, 150));

        auto bang = panelB->addChild(std::make_unique<ofx::MUI::Bang>("Bang", 50, 50, 200, 200));

//    ofAddListener(bang->bang, this, &ofApp::bang);
}


void ofApp::draw()
{
    ofBackground(0);

    ofNoFill();
    ofSetColor(255, 255, 0, 50);


//    ofx::DOM::Geometry bc = panelB->getGeometry();
//    bc.growToInclude(panelC->getGeometry());
//    bc = bc + panelA->getPosition();
//
//
//    ofSetColor(ofColor::yellow);
//    ofDrawRectangle(bc);
//
//    ofx::DOM::Geometry bc0 = panelA->getChildGeometry();
//
//    bc0 = bc0 + panelA->getPosition();
//
//
//    ofSetColor(ofColor::green);
//    ofDrawRectangle(bc0);
//    ofDrawRectangle(t);


//    cout << panelA->getGeometry() << endl;
}


void ofApp::onMove(ofx::DOM::MoveEvent& evt)
{
    cout << "MOVE: " << evt.position() << endl;
}


void ofApp::onResize(ofx::DOM::ResizeEvent& evt)
{
    cout << "RESIZE: " << evt.geometry() << endl;
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


void ofApp::bang()
{
    std::cout << "Got bang. " << std::endl;
}