// =============================================================================
//
// Copyright (c) 2009-2015 Christopher Baker <http://christopherbaker.net>
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

    ofSetLogLevel(OF_LOG_VERBOSE);

	data0.setName("data0");
	data1.setName("data1");

	scope = mui.addChild<MUI::Scope<float>>("data scope", 10, 10, 1000, 200, 128);

	scope->axes[0].setMinimum(0);
	scope->axes[0].setMaximum(scope->getMaxSize());

	scope->axes[1].setMinimum(-1);
	scope->axes[1].setMaximum(1);

	scope->setColor(data0.getName(), ofColor::yellow);
	scope->setColor(data1.getName(), ofColor::green);

	ofBackground(0);
}


void ofApp::draw()
{
	data0 += ofRandom(-0.01, 0.01);
	data1 += ofRandom(-0.01, 0.01);

	scope->add(data0.getName(), data0);
	scope->add(data1.getName(), data1);

    ofNoFill();
    ofSetColor(255, 255, 0, 50);
}

