#pragma once


#include "ofMain.h"


#if defined(TARGET_OF_IOS)
#include "ofxiOS.h"
#include "ofxiOSExtras.h"
#define BaseApp ofxiOSApp
#else
#define BaseApp ofBaseApp
#endif

#include "ofxMUI.h"


using namespace ofx;


class ofApp: public BaseApp
{
public:
    void setup();
    void update();
    void draw();
    void exit();


#if defined(TARGET_OF_IOS)
    void lostFocus();
    void gotFocus();
    void gotMemoryWarning();
    void deviceOrientationChanged(int newOrientation);
#endif
    
    void onBang(const void* sender, bool& value);

    MUI::MUI mui;

    enum
    {
        MATRIX_WIDTH = 10,
        MATRIX_HEIGHT = 7
    };

    std::vector<MUI::Button*> buttons;

};
