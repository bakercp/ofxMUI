#pragma once



#include "ofMain.h"
#include "ofxGui.h"

#include "ofxGuiWindow.h"
#include "ofxGuiTextBlock.h"
#include "ofxGuiTrueTypeFont.h"
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

    //ofxGuiSlider* mySlider;
    //ofxGuiLabelledButton* myButton;
    //ofxGuiLabelledButton* myOtherButton;

    void printModifiers();
    
    ofImage img;

    void newButtonEvent(const void * sender, int & i);

    ofxGui* gui;
    ofxGuiButton* button;
    ofxGuiButton* button0;
    ofxGuiButton* button1;
    ofxGuiButton* button2;
    ofxGuiButton* button3;
    ofxGuiButton* button4;
    
    //, obj;
    //ofxGuiColorPicker* picker;
    //ofxGuiWindow* panel;
    //ofxGuiWindow* panel1;
    //    ofxGuiPanel* obj;
    //ofxGuiLabelledButton* obj;
    ofxGuiSlider* sliderH;
    ofxGuiSlider* sliderV;
    ofxGuiSlider* slider0;
    ofxGuiSlider* slider1;
    ofxGuiSlider* slider2;
    ofxGuiSlider* slider3;

    
    ofxGuiLabel* lab0;
    ofxGuiLabel* lab1;
    ofxGuiLabel* lab2;
    ofxGuiLabel* lab3;
    ofxGuiLabel* lab4;
    ofxGuiLabel* lab5;
    ofxGuiLabel* lab6;
    ofxGuiLabel* lab7;

    ofxGuiLabel* lab0i;
    ofxGuiLabel* lab1i;
    ofxGuiLabel* lab2i;
    ofxGuiLabel* lab3i;

    ofxGuiNumberBox* nb0;
    ofxGuiNumberBox* nb1;
    ofxGuiNumberBox* nb2;
    ofxGuiNumberBox* nb3;
    
    
    ofxGuiKnob* knob0;
    //ofxGuiNumberBox* nb;

    //ofxTestObj* obj;
    //MyCustomControllerObject* guiObj;

    vector<ofRectangle> rects;
    vector<ofRectangle> solvedRects;
    ofRectangle bb;
    
    
    ofxGuiTextBlock* tb;;
    ofxGuiTrueTypeFont ttf;
    //ofxGuiTrueTypeFont ttf2;
    
    vector<ofCharacter> offsets;
    
    int s0, s1;
    
    string txt;
    /*
                TestObject* a1;
                TestObject a2;
                TestObject* a3;
     */
};
