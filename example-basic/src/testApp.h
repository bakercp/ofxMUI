#pragma once



#include "ofMain.h"
#include "ofxMui.h"

#include "ofxMuiWindow.h"
#include "ofxMuiTextBlock.h"
#include "ofxMuiTrueTypeFont.h"
//#include "MyCustomControllerObject.h"
//#include "TestObject.h"

class testApp : public ofBaseApp {

public:

    void setup();
    void update();
    void draw();

    void setupGui();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

    float bkg;

    //ofxMuiSlider* mySlider;
    //ofxMuiLabelledButton* myButton;
    //ofxMuiLabelledButton* myOtherButton;

    void printModifiers();
    
    ofImage img;

    void newButtonEvent(const void * sender, int & i);

    ofxMui* gui;
    ofxMuiButton* button;
    ofxMuiButton* button0;
    ofxMuiButton* button1;
    ofxMuiButton* button2;
    ofxMuiButton* button3;
    ofxMuiButton* button4;
    
    //, obj;
    //ofxMuiColorPicker* picker;
    //ofxMuiWindow* panel;
    //ofxMuiWindow* panel1;
    //    ofxMuiPanel* obj;
    //ofxMuiLabelledButton* obj;
    ofxMuiSlider* sliderH;
    ofxMuiSlider* sliderV;
    ofxMuiSlider* slider0;
    ofxMuiSlider* slider1;
    ofxMuiSlider* slider2;
    ofxMuiSlider* slider3;

    
    ofxMuiLabel* lab0;
    ofxMuiLabel* lab1;
    ofxMuiLabel* lab2;
    ofxMuiLabel* lab3;
    ofxMuiLabel* lab4;
    ofxMuiLabel* lab5;
    ofxMuiLabel* lab6;
    ofxMuiLabel* lab7;

    ofxMuiLabel* lab0i;
    ofxMuiLabel* lab1i;
    ofxMuiLabel* lab2i;
    ofxMuiLabel* lab3i;

    ofxMuiNumberBox* nb0;
    ofxMuiNumberBox* nb1;
    ofxMuiNumberBox* nb2;
    ofxMuiNumberBox* nb3;
    
    
    ofxMuiKnob* knob0;
    //ofxMuiNumberBox* nb;

    //ofxTestObj* obj;
    //MyCustomControllerObject* guiObj;

    vector<ofRectangle> rects;
    vector<ofRectangle> solvedRects;
    ofRectangle bb;
    
    
    ofxMuiTextBlock* tb;;
    ofxMuiTrueTypeFont ttf;
    //ofxMuiTrueTypeFont ttf2;
    
    vector<ofCharacter> offsets;
    
    int s0, s1;
    
    string txt;
    /*
                TestObject* a1;
                TestObject a2;
                TestObject* a3;
     */
};
