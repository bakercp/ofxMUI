// =============================================================================
//
// Copyright (c) 2009-2016 Christopher Baker <http://christopherbaker.net>
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
	ofEnableAlphaBlending();

	ofSetFrameRate(60);

    ofSetLogLevel(OF_LOG_VERBOSE);

    radioButtons = mui.addChild<MUI::ButtonGroup>("radio", MUI::Orientation::VERTICAL);
    radioButtons2 = mui.addChild<MUI::ButtonGroup>("radio2", MUI::Orientation::HORIZONTAL);

    radioButtons2->setPosition(300, 300);

    radioButtons->addRadioButton("b", 0, 0, 100, 100);
    radioButtons->addRadioButton("c", 0, 0, 100, 100);
    radioButtons->addRadioButton("d", 0, 0, 100, 100);
    radioButtons->addRadioButton("e", 0, 0, 100, 100);
    MUI::Widget* w = radioButtons->addRadioButton("a", 0, 0, 100, 100);

//    w->setEnabled(false);
    w->setHidden(true);
    

    radioButtons2->addToggleButton("aa");
    radioButtons2->addToggleButton("bb");
    radioButtons2->addToggleButton("cc");
    radioButtons2->addRadioButton("dd");
    radioButtons2->addRadioButton("ee");

	ofSetBackgroundColor(0);
}


void ofApp::draw()
{
}


void ofApp::onBang(const void* sender, bool& value)
{
    cout << "got bang = > " << value << endl;
}



