/*
 *  ofxMuiSlider.h
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
#include "ofxMuiNumberData.h"

//--------------------------------------------------------------
class ofxMuiSlider : public ofxMuiLabelledObject, public ofxMuiNumberData {
public:

    ofxMuiSlider(const string& _name, int _x, int _y, int _width, int _height, bool _enabled = true);
    ofxMuiSlider(const string& _name, int _x, int _y,bool _enabled = true);
    ofxMuiSlider(const string& _name, bool _enabled = true);
    ofxMuiSlider(bool _enabled = true);
    virtual ~ofxMuiSlider();

    //--------------------------------------------------------------
    // INHERITED FROM SUPERCLASS ///////////////////////////////////
    //--------------------------------------------------------------

    void update();
    void draw();

    //--------------------------------------------------------------
    // PERSISTENCE /////////////////////////////////////////////////
    //--------------------------------------------------------------

    void buildFromXml();
    void saveToXml();
    
    //--------------------------------------------------------------
    // KEYBINDING //////////////////////////////////////////////////
    //--------------------------------------------------------------

    void keyBind_increaseValue(int key);
    void keyBind_decreaseValue(int key);

    //--------------------------------------------------------------
    // GETTERS AND SETTERS /////////////////////////////////////////
    //--------------------------------------------------------------
    
    int  getSliderWidth() const;
    void setSliderWidth(int _width);
    
    int  getSliderHeight() const;
    void setSliderHeight(int _height);
    
    ofOrientation getOrientation() const;
    void setOrientation(const ofOrientation& _orientation);
        
protected:

    void init();
    void dataChanged();
    
    float toNormalizedValue(ofVec2f pos);
        
    //--------------------------------------------------------------
    // INHERITED FROM SUPERCLASS ///////////////////////////////////
    //--------------------------------------------------------------
    
    void onRollOver();
    void onRollOut();
    
    void onMouseMove();
    
    void onPress();
    void onDoublePress();
    void onDrag();
    
    void doContentBoxLayout();

    //--------------------------------------------------------------
    // LOCAL HELPER FUNCTIONS //////////////////////////////////////
    //--------------------------------------------------------------
    
    //--------------------------------------------------------------
    // VARIABLES ///////////////////////////////////////////////////
    //--------------------------------------------------------------
        
    //--------------------------------------------------------------
    // EVENTS //////////////////////////////////////////////////////
    //--------------------------------------------------------------

    float normCtrlDragStartMin;
    float normCtrlDragStartMax;
    
    ofEvent<float> ofxMuiSliderEvent;

    
};

//--------------------------------------------------------------

