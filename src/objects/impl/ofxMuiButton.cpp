/*
 *  ofxMuiButton.cpp
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


//--------------------------------------------------------------
#include "ofxMuiButton.h"


ofxMuiButton::ofxMuiButton(const string& _name, int _x, int _y, int _width, int _height, bool _enabled) : 
ofxMuiLabelledObject(_name, _x, _y, _width, _height, _enabled),
ofxMuiNumberData(ofxMui_BOOL) {
    init();
}

//--------------------------------------------------------------
ofxMuiButton::ofxMuiButton(const string& _name, int _x, int _y,bool _enabled) : 
ofxMuiLabelledObject(_name, _x, _y, _enabled),
ofxMuiNumberData(ofxMui_BOOL) {
    init();
}

//--------------------------------------------------------------
ofxMuiButton::ofxMuiButton(const string& _name,bool _enabled) :
ofxMuiLabelledObject(_name, _enabled),
ofxMuiNumberData(ofxMui_BOOL) {
    init();
}

//--------------------------------------------------------------
ofxMuiButton::ofxMuiButton(bool _enabled) : 
ofxMuiLabelledObject(_enabled),
ofxMuiNumberData(ofxMui_BOOL) {
    init();
}

//--------------------------------------------------------------
ofxMuiButton::~ofxMuiButton() {
}

//--------------------------------------------------------------
void ofxMuiButton::init() {
    // super class init should have already been called in the constructor def list
    setObjectType("BUTTON");
    roundFrame = defaults->buttonRoundFrame;
    
    // override the superclass
    setBoxProperties(defaults->buttonBoxProperties);    
    buttonType = TYPE_SWITCH;
    
    
    setButtonIcon(ICON_DEFAULT);
    
    setValue(false);

    // set default key binding
    keyBind_toggleValue(defaults->keyboardToggle);

    // custom, just for the button itself (i.e. no clicking on the label)
	setHitBox(0, 0, defaults->buttonWidth, defaults->buttonHeight);

    label->setText(name);
    label->enable();
    
    requestBoxLayout();
    
}

//--------------------------------------------------------------
void ofxMuiButton::keyBind_toggleValue(int key) {
    //setKeyMap(key,bind(&ofxMuiButton::toggle, ref(*this))); 
}

//--------------------------------------------------------------
void ofxMuiButton::dataChanged(int index) {
    bool value = getValueBool();
    ofNotifyEvent(ofxMuiButtonEvent, value, this);
}

//--------------------------------------------------------------
void ofxMuiButton::draw()
{

    ofPushStyle();
	ofPushMatrix(); // initial push
    
    ofTranslate(getHitBoxPosition());

    //--------- DRAW THE BUTTON BACKGROUND
    // default
    ofFill();
    ofSetColor(cActiveAreaBackground.get(isMouseOver(),isMouseDown(),isEnabled(),alphaScale));
    if(roundFrame) {
        // assuming that the icon is square ...
        ofCircle(getHitBoxWidth()/2, getHitBoxHeight()/2, getHitBoxWidth()/2);
    } else {
        ofxRect(0, 0, getHitBoxWidth(), getHitBoxHeight());
    }
    
    ofNoFill();
    ofSetColor(cActiveAreaForeground.get(isMouseOver(),isMouseDown(),isEnabled(),alphaScale));

    if(useIcon) {
        int iconWidth = icon->getIcon(getValue())->getWidth();
        int iconHeight = icon->getIcon(getValue())->getHeight();;
        int hitWidth = getHitBoxWidth();
        int hitHeight = getHitBoxHeight();
        int xlateX = 0;
        int xlateY = 0;
        
        // center the icon
        ofPushMatrix();
        
        if(iconWidth < hitWidth) {
            int diffX = hitWidth - iconWidth;
            xlateX = diffX/2;
        } else {
            int diffX = iconWidth - hitWidth;
            xlateX = -diffX/2;
        }
        
        if(iconHeight < hitHeight) {
            int diffY = hitHeight - iconHeight;
            xlateY = diffY/2;
        } else {
            int diffY = iconHeight - hitHeight;
            xlateY = -diffY/2;
        }
        
        ofTranslate(xlateX, xlateY);
        icon->getIcon(getValue())->draw(0,0);   

        ofPopMatrix();
        
        
    } else {
        ofFill();
        ofxRect(0, 0, getHitBoxWidth(), getHitBoxHeight());
    }
    
    ofNoFill();
    ofSetColor(cActiveAreaFrame.get(isMouseOver(),isMouseDown(),isEnabled(),alphaScale));
    if(roundFrame) {
        // assuming that the icon is square ...
        ofCircle(getHitBoxWidth()/2, getHitBoxHeight()/2, getHitBoxWidth()/2);
    } else {
        ofxRect(0, 0, getHitBoxWidth(), getHitBoxHeight());
    }

    ofPopMatrix(); // HIT RECT PUSH
    ofPopStyle();

    
}

//--------------------------------------------------------------
void ofxMuiButton::onPress()
{
	if(mouseButton == 0) {
		// left click
		if (buttonType == TYPE_SWITCH) {
			toggle();
		} else if(buttonType == TYPE_TRIGGER) {
            setValue(true); // turn on
		}
	}
}

//--------------------------------------------------------------
void ofxMuiButton::onRelease()
{
	if(mouseButton == 0) {
		// left click
		if(buttonType == TYPE_TRIGGER) {
            setValue(false); // turn of
		}
	}
}

//--------------------------------------------------------------
void ofxMuiButton::onReleaseOutside()
{
	if(mouseDown && mouseButton == 0) {
		// left click
		if(buttonType == TYPE_TRIGGER) {
			setValue(false); // turn on
		}
	}
}

//--------------------------------------------------------------
void ofxMuiButton::buildFromXml()
{
	//props->mListener->handleGui(mParamId, kofxMui_Set_Bool, &value, sizeof(bool));
}

//--------------------------------------------------------------
void ofxMuiButton::saveToXml()
{
	int		id		= saveObjectData();
	bool	value	= (buttonType == TYPE_TRIGGER) ? false : (value == true);

	//props->mXml.setValue("OBJECT:VALUE", value, id);
}

//--------------------------------------------------------------
void ofxMuiButton::setButtonSize(int _width, int _height) {
    setButtonWidth(_width);
    setButtonHeight(_height);
}

//--------------------------------------------------------------
void ofxMuiButton::setButtonWidth(int _width) {
    setHitBoxWidth(_width);
    requestBoxLayout();
}

//--------------------------------------------------------------
void ofxMuiButton::setButtonHeight(int _height) {
    setHitBoxHeight(_height);
    requestBoxLayout();
}

//--------------------------------------------------------------
int  ofxMuiButton::getButtonWidth() {
    return getHitBoxWidth();
}
//--------------------------------------------------------------
int  ofxMuiButton::getButtonHeight() {
    return getHitBoxHeight();
}

//--------------------------------------------------------------
void ofxMuiButton::setButtonType(const ofxMuiButtonType& _buttonType) {
    buttonType = _buttonType;
    requestBoxLayout();
}
//--------------------------------------------------------------
ofxMuiButtonType ofxMuiButton::getButtonType() const {
    return buttonType;
}
//--------------------------------------------------------------
void ofxMuiButton::setButtonIcon(const ofxMuiIconName& _buttonIcon) {
    buttonIconName = _buttonIcon;
    if(buttonIconName == ICON_NONE) {
        icon = NULL;
        useIcon = false;
        // assume that it has or will be set
        //hitBox.width = defaults->buttonWidth;
        //hitBox.height = icon->getHeight();
    } else {
        icon = defaults->getIcon(buttonIconName);
        
        setHitBoxWidth(icon->getWidth());
        setHitBoxHeight(icon->getHeight());

        useIcon = true;
    }
    
    requestBoxLayout();
}

ofxMuiIconName ofxMuiButton::getButtonIcon() const {
    return buttonIconName;
}

////--------------------------------------------------------------
//void ofxMuiButton::setAlignVert(const ofAlignVert& _vAlign) {
//    verticalAlign = _vAlign;
//}
//
////--------------------------------------------------------------
//ofAlignVert ofxMuiButton::getAlignVert() const {
//    return verticalAlign;
//}

//--------------------------------------------------------------
void ofxMuiButton::setRoundFrame(bool _roundFrame) {
    roundFrame = _roundFrame;
    requestBoxLayout();
}

//--------------------------------------------------------------
bool ofxMuiButton::getRoundFrame() {
    return roundFrame;
}

//--------------------------------------------------------------
void ofxMuiButton::doContentBoxLayout() {
    
    // TODO: handle the case where the label is EMPTY
    
    // vertical ofxMuiLabelCaps
    if(label->getHeight() > getHitBoxHeight()) {
        setContentBoxHeight(label->getHeight());
        setHitBoxY((label->getHeight() - getHitBoxHeight()) / 2.0f);
        label->setY(0);
    } else {
        setContentBoxHeight(getHitBoxHeight());
        label->setY((getHitBoxHeight() - label->getHeight()) / 2.0f);
        setHitBoxY(0);
    }
    
    // label to the right
    label->setX(getHitBoxWidth()); // label to the right
    setHitBoxX(0);
    
    // TODO: this doesn't account for auto widths ...
    setContentBoxWidth(getHitBoxWidth() + label->getWidth());
    
}



