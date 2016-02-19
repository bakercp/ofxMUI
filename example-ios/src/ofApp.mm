#include "ofApp.h"


void ofApp::setup()
{
    fontLarge.load("Roboto_Condensed/RobotoCondensed-Light.ttf", 20);
    fontMedium.load("Roboto_Condensed/RobotoCondensed-Light.ttf", 15);
    fontSmall.load("Roboto_Condensed/RobotoCondensed-Light.ttf", 10);

    ofSetFrameRate(60);

    ofx::RegisterPointerEvents(this);

    ofSetLogLevel(OF_LOG_VERBOSE);

    mui = std::make_unique<ofx::DOM::Document>();

    fader = mui->addChild(std::make_unique<MUI::FloatSlider>("fader", 10, 10, 50, 400));
    volume = mui->addChild(std::make_unique<MUI::FloatSlider>("volume", 70, 10, 30, 300));
    ritard = mui->addChild(std::make_unique<MUI::FloatSlider>("ritard", 120, 10, 50, 400));
    tempo = mui->addChild(std::make_unique<MUI::FloatSlider>("tempo", 180, 10, 70, 400));

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
    ofLogVerbose("ofApp::onPointerMove") << evt.toString();
}


void ofApp::onPointerCancel(ofx::PointerEventArgs& evt)
{
    ofLogVerbose("ofApp::onPointerCancel") << evt.toString();
}
