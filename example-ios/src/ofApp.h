#pragma once


#include "ofMain.h"
#include "ofxiOS.h"
#include "ofxiOSExtras.h"

#include "ofxMUI.h"


using namespace ofx;


class ofApp: public ofxiOSApp
{
public:
    void setup();
    void draw();

    void onPointerUp(PointerEventArgs& evt);
    void onPointerDown(PointerEventArgs& evt);
    void onPointerMove(PointerEventArgs& evt);
    void onPointerCancel(PointerEventArgs& evt);

    std::unique_ptr<DOM::Document> mui;

    MUI::FloatSlider* fader;
    MUI::FloatSlider* volume;
    MUI::FloatSlider* ritard;
    MUI::FloatSlider* tempo;

    ofTrueTypeFont fontLarge;
    ofTrueTypeFont fontMedium;
    ofTrueTypeFont fontSmall;

};


