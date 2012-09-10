/*
 *  ofxGuiPanel.h
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

#include "ofxGuiLabelledObject.h"
#include "ofxGuiButton.h"
#include "ofxGuiColorPicker.h"
#include "ofxGuiSlider.h"
#include "ofxGuiKnob.h"
#include "ofxGuiNumberBox.h"

//--------------------------------------------------------------
class ofxGuiPanel : public ofxGuiLabelledObject
{

public:

    ofxGuiPanel(const string& _name, int _x, int _y, int _width, int _height, bool _enabled = true);
    ofxGuiPanel(const string& _name, int _x, int _y,bool _enabled = true);
    ofxGuiPanel(const string& _name, bool _enabled = true);
    ofxGuiPanel(bool _enabled = true);
    virtual ~ofxGuiPanel();
    
    void draw();	// called every frame to draw object
    
    
    ofxGuiButton*	addButton(string name = "");
    ofxGuiButton*	addSwitch(string name = "");
    ofxGuiButton*	addTrigger(string name = "");
    
    ofxGuiColorPicker*  addColorPicker(string name = "");
    ofxGuiSlider*       addSlider(string name = "");
    
    ofxGuiKnob*      addKnob(string name = "");
    ofxGuiNumberBox* addNumberBox(string name = "");
    
    /*
    ofxGuiLabelledButton*	addButtonTrigger(string name);
    ofxGuiLabelledButton*	addButtonSwitch(string name);
*/
 
/*
    ofxGuiSlider*	addSlider(string name, 
                              int width, int height, 
                              float min, float max, 
                              float value, int display, 
                              int steps=OFXGUI_STEPS);
*/
    /*
    ofxGuiXYPad*	addXYPad(	string name, int width, int height, ofVec2f min, ofVec2f max, ofVec2f value, int display, int steps=OFXGUI_STEPS);
    ofxGuiPoints*	addPoints(	string name, int width, int height, ofVec2f min, ofVec2f max, ofVec2f value, int display, int steps=OFXGUI_STEPS);




    ofxGuiFiles*	addFiles(	string name, int width, int height, string value, string subPath, string suffix);
    ofxGuiColor*	addColor(	string name, int width, int height, ofRGBA value, int mode);
    ofxGuiMatrix*	addMatrix(	string name, int width, int height, int xGrid, int yGrid, int value, int mode, int spacing);
    ofxGuiScope*	addScope(	string name, int width, int height, int length, ofVec2f value, int mode);
    ofxGuiKnob*		addKnob(	string name, int width, int height, float min, float max, float value, int display, int steps=OFXGUI_STEPS);
    ofxGuiRadar*	addRadar(	string name, int width, int height, float min, float max, float value, int display, int steps=OFXGUI_STEPS);
    ofxGuiSwitch*	addSwitch(	string name, int width, int height, int min, int max, int value, const string* paramStrings);	
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

