/*
 *  ofxGuiButton.h
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

//--------------------------------------------------------------
#include "ofxGuiLabelledObject.h"
#include "ofxGuiIcon.h"
#include "ofxGuiNumberData.h"


enum ofxGuiButtonType
{
	TYPE_SWITCH,
	TYPE_TRIGGER /* like a bang */
};

class ofxGuiButton : public ofxGuiLabelledObject, public ofxGuiNumberData {
    
public:

    ofxGuiButton(const string& _name, int _x, int _y, int _width, int _height, bool _enabled = true);
    ofxGuiButton(const string& _name, int _x, int _y,bool _enabled = true);
    ofxGuiButton(const string& _name, bool _enabled = true);
    ofxGuiButton(bool _enabled = true);
    virtual ~ofxGuiButton();

    //--------------------------------------------------------------
    // INHERITED FROM SUPERCLASS ///////////////////////////////////
    //--------------------------------------------------------------
    
    void draw();
    
    //--------------------------------------------------------------
    // PERSISTENCE /////////////////////////////////////////////////
    //--------------------------------------------------------------
    
	void buildFromXml();
	void saveToXml();
    
    //--------------------------------------------------------------
    // KEYBINDING //////////////////////////////////////////////////
    //--------------------------------------------------------------
    
    void keyBind_toggleValue(int key);
    
    //--------------------------------------------------------------
    // GETTERS AND SETTERS /////////////////////////////////////////
    //--------------------------------------------------------------

    void setButtonSize(int _width, int _height);
    void setButtonWidth(int _width);
    void setButtonHeight(int _height);
    int  getButtonWidth();
    int  getButtonHeight();

    void setButtonType(const ofxGuiButtonType& _buttonType);
    ofxGuiButtonType getButtonType() const;
    
    void setButtonIcon(const ofxGuiIconName& _buttonIcon);
    ofxGuiIconName getButtonIcon() const;
    
    void setAlignVert(const ofAlignVert& _vAlign);
    ofAlignVert getAlignVert() const;
    
    void setRoundFrame(bool _roundFrame);
    bool getRoundFrame();
    

    
    
    //--------------------------------------------------------------
    // EVENTS //////////////////////////////////////////////////////
    //--------------------------------------------------------------
    
    ofEvent<bool> ofxGuiButtonEvent;

protected:

    void init(); // local init for convenience
    void dataChanged(int index);
    
    //--------------------------------------------------------------
    // INHERITED FROM SUPERCLASS ///////////////////////////////////
    //--------------------------------------------------------------
    
    // mouse action
	void onPress();			
	void onRelease();		
	void onReleaseOutside();

    void doContentBoxLayout();

	//--------------------------------------------------------------
    // VARIABLES ///////////////////////////////////////////////////
    //--------------------------------------------------------------

    ofxGuiIcon*             icon;
    bool                    useIcon;

	ofxGuiButtonType        buttonType;
    ofxGuiIconName          buttonIconName;

    ofAlignHorz             labelPositionHorz;
    ofAlignVert             labelPositionVert;
    ofAlignVert             vAlign;
    
    bool                    roundFrame;
    
};

//--------------------------------------------------------------

