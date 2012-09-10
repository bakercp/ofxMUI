/*
 *  ofxMuiButton.h
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
#include "ofxMuiLabelledObject.h"
#include "ofxMuiIcon.h"
#include "ofxMuiNumberData.h"


enum ofxMuiButtonType
{
	TYPE_SWITCH,
	TYPE_TRIGGER /* like a bang */
};

class ofxMuiButton : public ofxMuiLabelledObject, public ofxMuiNumberData {
    
public:

    ofxMuiButton(const string& _name, int _x, int _y, int _width, int _height, bool _enabled = true);
    ofxMuiButton(const string& _name, int _x, int _y,bool _enabled = true);
    ofxMuiButton(const string& _name, bool _enabled = true);
    ofxMuiButton(bool _enabled = true);
    virtual ~ofxMuiButton();

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

    void setButtonType(const ofxMuiButtonType& _buttonType);
    ofxMuiButtonType getButtonType() const;
    
    void setButtonIcon(const ofxMuiIconName& _buttonIcon);
    ofxMuiIconName getButtonIcon() const;
    
    void setAlignVert(const ofAlignVert& _vAlign);
    ofAlignVert getAlignVert() const;
    
    void setRoundFrame(bool _roundFrame);
    bool getRoundFrame();
    

    
    
    //--------------------------------------------------------------
    // EVENTS //////////////////////////////////////////////////////
    //--------------------------------------------------------------
    
    ofEvent<bool> ofxMuiButtonEvent;

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

    ofxMuiIcon*             icon;
    bool                    useIcon;

	ofxMuiButtonType        buttonType;
    ofxMuiIconName          buttonIconName;

    ofAlignHorz             labelPositionHorz;
    ofAlignVert             labelPositionVert;
    ofAlignVert             vAlign;
    
    bool                    roundFrame;
    
};

//--------------------------------------------------------------

