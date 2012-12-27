/*==============================================================================
 
 Copyright (c) 2009-2012 Christopher Baker <http://christopherbaker.net>
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 
 ==============================================================================*/

#pragma once

//#include "ofxMuiLabelledObject.h"
#include "ofxMuiButton.h"
//#include "ofxMuiColorPicker.h"
//#include "ofxMuiSlider.h"
//#include "ofxMuiKnob.h"
//#include "ofxMuiNumberBox.h"

//--------------------------------------------------------------
class ofxMuiPanel : public ofxMuiObject
{

public:

    ofxMuiPanel(const string& _name, int _x, int _y, int _width, int _height, bool _enabled = true);
    ofxMuiPanel(const string& _name, int _x, int _y,bool _enabled = true);
    ofxMuiPanel(const string& _name, bool _enabled = true);
    ofxMuiPanel(bool _enabled = true);
    virtual ~ofxMuiPanel();
    
    void draw();	// called every frame to draw object
    
    
    ofxMuiButton*	addButton(string name = "");
//    ofxMuiButton*	addToggle(string name = "");
//    ofxMuiButton*	addBang(string name = "");
    
  //  ofxMuiColorPicker*  addColorPicker(string name = "");
//    ofxMuiSlider*   addSlider(string name = "");
    
//    ofxMuiKnob*      addKnob(string name = "");
//    ofxMuiNumberBox* addNumberBox(string name = "");
    
    /*
    ofxMuiLabelledButton*	addButtonTrigger(string name);
    ofxMuiLabelledButton*	addButtonSwitch(string name);
*/
 
/*
    ofxMuiSlider*	addSlider(string name, 
                              int width, int height, 
                              float min, float max, 
                              float value, int display, 
                              int steps=ofxMui_STEPS);
*/
    /*
    ofxMuiXYPad*	addXYPad(	string name, int width, int height, ofVec2f min, ofVec2f max, ofVec2f value, int display, int steps=ofxMui_STEPS);
    ofxMuiPoints*	addPoints(	string name, int width, int height, ofVec2f min, ofVec2f max, ofVec2f value, int display, int steps=ofxMui_STEPS);




    ofxMuiFiles*	addFiles(	string name, int width, int height, string value, string subPath, string suffix);
    ofxMuiColor*	addColor(	string name, int width, int height, ofRGBA value, int mode);
    ofxMuiMatrix*	addMatrix(	string name, int width, int height, int xGrid, int yGrid, int value, int mode, int spacing);
    ofxMuiScope*	addScope(	string name, int width, int height, int length, ofVec2f value, int mode);
    ofxMuiKnob*		addKnob(	string name, int width, int height, float min, float max, float value, int display, int steps=ofxMui_STEPS);
    ofxMuiRadar*	addRadar(	string name, int width, int height, float min, float max, float value, int display, int steps=ofxMui_STEPS);
    ofxMuiSwitch*	addSwitch(	string name, int width, int height, int min, int max, int value, const string* paramStrings);	
    */
    void			loadFromXml(ofxXmlSettings& xml);
    void			saveToXml(ofxXmlSettings& xml);

    // bakercp
    
protected:
    void init();

    //--------------------------------------------------------------
    // INHERITED FROM SUPERCLASS ///////////////////////////////////
    //--------------------------------------------------------------
    
    void doContentBoxLayout();
        
    
    		
};