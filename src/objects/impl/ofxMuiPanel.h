/*
 *  ofxMuiPanel.h
 *  openFrameworks
 *
 *  Copyright 2008 alphakanal/Stefan Kirch.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#pragma once

#include "ofxMuiLabelledObject.h"
#include "ofxMuiButton.h"
//#include "ofxMuiColorPicker.h"
#include "ofxMuiSlider.h"
#include "ofxMuiKnob.h"
#include "ofxMuiNumberBox.h"

//--------------------------------------------------------------
class ofxMuiPanel : public ofxMuiLabelledObject
{

public:

    ofxMuiPanel(const string& _name, int _x, int _y, int _width, int _height, bool _enabled = true);
    ofxMuiPanel(const string& _name, int _x, int _y,bool _enabled = true);
    ofxMuiPanel(const string& _name, bool _enabled = true);
    ofxMuiPanel(bool _enabled = true);
    virtual ~ofxMuiPanel();
    
    void draw();	// called every frame to draw object
    
    
    ofxMuiButton*	addButton(string name = "");
    ofxMuiButton*	addSwitch(string name = "");
    ofxMuiButton*	addTrigger(string name = "");
    
  //  ofxMuiColorPicker*  addColorPicker(string name = "");
    ofxMuiSlider*       addSlider(string name = "");
    
    ofxMuiKnob*      addKnob(string name = "");
    ofxMuiNumberBox* addNumberBox(string name = "");
    
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
    void			buildFromXml();
    void			saveToXml();

    // bakercp
    
protected:
    void init();

    //--------------------------------------------------------------
    // INHERITED FROM SUPERCLASS ///////////////////////////////////
    //--------------------------------------------------------------
    
    void doContentBoxLayout();
        
    
    		
};

//--------------------------------------------------------------

