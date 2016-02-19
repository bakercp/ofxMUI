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
	ofEnableAlphaBlending();

	ofSetFrameRate(60);

    ofSetLogLevel(OF_LOG_VERBOSE);

    // Set up a random number for testing a slider with an external ofParameter.
    noiseOffset = 0;
    randomFloatParemter = 0;
    randomFloatParemter.setMin(0);
    randomFloatParemter.setMax(1);

    // Create three float sliders.
    floatSlider0 = mui.addChild<MUI::FloatSlider>("float_slider_0", // name
                                                  10,  // x-position
                                                  10,  // y-position
                                                  50,  // width
                                                  400, // height
                                                  MUI::Orientation::AUTO, // Choose orientation automatically based on width / height ratio.
                                                  MUI::DragMode::RELATIVE // Set drag mode to relative.
                                                  );

    floatSlider0->makeReferenceTo(randomFloatParemter);

    // Register the slider to a dedicated callback.
    floatSlider0->addListener(this, &ofApp::onFloatSlider);

    // Create a slider.
    floatSlider1 = mui.addChild<MUI::FloatSlider>("float_slider_1", 70, 10, 30, 300);

    // Register the slider to a shared callback.
    floatSlider1->addListener(this, &ofApp::onFloatSlider);

    // Create a slider.
    floatSlider2 = mui.addChild<MUI::FloatSlider>("float_slider_2", 250, 10, 50, 400);

    // Attach the random float value.
    floatSlider2->makeReferenceTo(randomFloatParemter);

    // Add a listener AFTER making a reference.
    floatSlider2->addListener(this, &ofApp::onFloatSlider);

    // Make this slider slide relative to the last position.
    floatSlider2->setDragMode(MUI::DragMode::RELATIVE);


    


	ofSetBackgroundColor(0);
}

void ofApp::update()
{
    noiseOffset += 0.01;
    randomFloatParemter = ofNoise(noiseOffset); 

    *floatSlider1 = ofSignedNoise(noiseOffset);

//    cout << "--- << " << endl;
//
//    cout << (float)floatSlider2 << endl;
//    cout << randomFloatParemter << endl;
}


void ofApp::draw()
{
}


void ofApp::onFloatSlider(const void* sender, float& f)
{


//    MUI::FloatSlider* s = (MUI::FloatSlider*)sender;
//
//    MUI::Parameter<float>* s = (MUI::Parameter<float>*)sender;

//    cout << s-> << endl;

    if (sender == floatSlider0)
	{
		std::cout << "floatSlider0: " << f << std::endl;
	}
	else if (sender == floatSlider1)
	{
		std::cout << "floatSlider1: " << f << std::endl;
	}
	else if (sender == floatSlider2)
	{
		std::cout << "floatSlider2: " << f << std::endl;
	}
    else if (sender == &randomFloatParemter)
    {
        std::cout << "randomFloatParemter: " << f << std::endl;
    }
	else
	{
		std::cout << "Unknown sender. " << f << std::endl;
	}

//    if (sender == (MUI::Parameter<float>*)floatSlider0)
//    {
//        std::cout << "floatSlider0: " << f << std::endl;
//    }
//    else if (sender == (MUI::Parameter<float>*)floatSlider1)
//    {
//        std::cout << "floatSlider1: " << f << std::endl;
//    }
//    else if (sender == (MUI::Parameter<float>*)floatSlider2)
//    {
//        std::cout << "floatSlider2: " << f << std::endl;
//    }
//    else if (sender == &randomFloatParemter)
//    {
//        std::cout << "randomFloatParemter: " << f << std::endl;
//    }
//    else
//    {
//        std::cout << "Unknown sender. " << f << std::endl;
//    }

}



