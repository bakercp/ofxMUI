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

#include "ofxMuiWindow.h"

//--------------------------------------------------------------
ofxMuiWindow::ofxMuiWindow(const string& _name, int _x, int _y, int _width, int _height, bool _enabled) : 
ofxMuiPanel(_name, _x, _y, _width, _height, _enabled) {
    init();
}

//--------------------------------------------------------------
ofxMuiWindow::ofxMuiWindow(const string& _name, int _x, int _y,bool _enabled) : 
ofxMuiPanel(_name, _x, _y, _enabled) {
    init();
}

//--------------------------------------------------------------
ofxMuiWindow::ofxMuiWindow(const string& _name,bool _enabled) :
ofxMuiPanel(_name, _enabled) {
    init();
}

//--------------------------------------------------------------
ofxMuiWindow::ofxMuiWindow(bool _enabled) : 
ofxMuiPanel(_enabled) {
    init();
}

//--------------------------------------------------------------
ofxMuiWindow::~ofxMuiWindow() {
    // deletion is of all child objects are done in the super class
    // delete enableDisableButton;
    // delete minMaxButton;
 	
}

//--------------------------------------------------------------
void ofxMuiWindow::init() {
    
    setObjectType("WINDOW");
    
	isMinimized		= false;
    _isDragMoveable	= true;
    
//    setTooltip("");
    
    setBoxProperties(defaults->windowBoxProperties);

	// draw the min max/ active inactive buttons
	enableDisableButton = new ofxMuiButton();

    enableDisableButton->setButtonIcon(defaults->windowBoxEnableDisableIcon);
    enableDisableButton->keyBind_toggleValue(defaults->keyboardEnableDisable);
//    enableDisableButton->setTooltip("Enable/Disable (" + ofToString(defaults->keyboardEnableDisable) + ")");
//    enableDisableButton->setTooltipEnabled(true);
	
    addChild(enableDisableButton);
	
	minMaxButton = new ofxMuiButton();
    minMaxButton->setButtonIcon(defaults->windowBoxMinMaxIcon);
    minMaxButton->keyBind_toggleValue(defaults->keyboardMinMax);
//    minMaxButton->setTooltip("Minimize/Maximize (" + ofToString(defaults->keyboardMinMax) + ")");
//    minMaxButton->setTooltipEnabled(true);
    addChild(minMaxButton);

    requestBoxLayout();

}

//--------------------------------------------------------------
void ofxMuiWindow::update() {
    // not using events locally anymore. 
    if(minMaxButton->getValue()) {
        minimize();
    } else {
        maximize(); 
    }

    if(enableDisableButton->getValue()) {
        disable(); 
    } else {
        enable();   
    }
}

//--------------------------------------------------------------
void ofxMuiWindow::draw() {
    
    ofPushStyle();
	ofPushMatrix(); // initial push
    
    ofTranslate(getHitBoxPosition());
    
    ofSetColor(255,0,255);
	
    if(isMinimized) {
        //ofxRect(0.0f, 0.0f, width, windowButtonHeight + 1);
        ofxRect(0.0f, 0.0f, minimizedRect.width,minimizedRect.height);
    } else {
        ofxRect(0.0f, 0.0f, getHitBoxWidth(), getHitBoxHeight());
    }
    ofNoFill();
    
    /*
     if(name != "") {
     if(isMinimized) {
     
     ofPushMatrix();
     ofTranslate(mGlobals->mPadLeft,mGlobals->mPadTop);
     drawParamString(windowButtonWidth*2, 0, name, false);	
     ofPopMatrix();
     
     } else {
     drawHeadString(mBorder, mBorder + windowButtonHeight, name, false);
     }
     }
     
     if(mBorder > 0)
     {
     //	border
     //glColor4f(mGlobals->mBorderColor.r, mGlobals->mBorderColor.g, mGlobals->mBorderColor.b, mGlobals->mBorderColor.a);
     ofSetColor(mGlobals->mBorderColor);
     
     if(isMinimized) {
     ofxRect(0.0f, 0.0f, minimizedRect.width,minimizedRect.height);
     //ofxRect(0.0f, 0.0f, width, windowButtonHeight );
     } else {
     ofxRect(0.0f, 0.0f, width, height);
     }
     }
     
     if(isEnabled && !isMinimized) {
     ofxMuiObject* tmpObj;
     for(int i = 0; i < childObjects.size(); i++)
     {
     tmpObj = (ofxMuiObject*)childObjects.at(i);
     tmpObj->draw();
     }
     } else {
     //			minMaxButton->draw();
     //			enableDisableButton->draw();
     }
     
     
    
     */
	
	
	ofPopMatrix();
    ofPopStyle();
    
}

//--------------------------------------------------------------
void ofxMuiWindow::toggleMaxMin()
{
	if(isMinimized) {
		maximize();		
	} else {
		minimize();
	}
	
}

//--------------------------------------------------------------

void ofxMuiWindow::maximize() {
    if(!isMinimized) return;
	isMinimized = false;
    
    for(int i = 0; i < childObjects.size(); i++) {
        if(childObjects[i] != enableDisableButton &&
           childObjects[i] != minMaxButton /*&&
           childObjects[i] != label &&
           childObjects[i] != valueLabel*/) {
            childObjects[i]->show();
        }
	}
    
    requestBoxLayout();
}

//--------------------------------------------------------------
void ofxMuiWindow::minimize() {
    if(isMinimized) return;
	isMinimized = true;
    
    // disallow mouse / keyboard input when hidden
    for(int i = 0; i < childObjects.size(); i++) {
        if(childObjects[i] != enableDisableButton &&
           childObjects[i] != minMaxButton/*&&
                                           childObjects[i] != label &&
                                           childObjects[i] != valueLabel*/) {
            childObjects[i]->hide();
        }
	}
    
    requestBoxLayout();
}


//--------------------------------------------------------------
void ofxMuiWindow::loadFromXml(ofxXmlSettings& xml) {	
}

//--------------------------------------------------------------
void ofxMuiWindow::saveToXml(ofxXmlSettings& xml)
{   /*
     ofxMuiObject* tmpObj;
     
     int id = name();
     
     mGlobals->mXml.setValue("OBJECT:BORDER", mBorder, id);
     mGlobals->mXml.setValue("OBJECT:SPACING", mSpacing, id);
     mGlobals->mXml.pushTag("OBJECT", id);
     
     for(int i = 0; i < childObjects.size(); i++)
     {
     tmpObj = (ofxMuiObject*)childObjects.at(i);
     tmpObj->saveToXml(ofxXmlSettings& xml);
     }
     
     mGlobals->mXml.popTag();
     */
}


//--------------------------------------------------------------
void ofxMuiWindow::doContentBoxLayout() {
    cout << "doing content box layout " << endl;
    int currentX = 0;
    int currentY = 0;
    
    int maxX = 0;
    int maxY = 0;
    
    // position the minmax/enable/disable buttons
    enableDisableButton->setPosition(0,0);
    currentX+=enableDisableButton->getWidth();
    minMaxButton->setPosition(currentX,0);
    currentX+=minMaxButton->getWidth();
    
    // position the label
    
    // TODO: center this
//    int labelY = (minMaxButton->getY() + minMaxButton->getHeight()) / 2.0 -label->getHeight() / 2.0 ;
//    label->setPosition(currentX, labelY);
//    
//    
//    maxX = MAX(maxX, label->getPosition().x + label->getWidth());
//    
//    currentY+=MAX(MAX(enableDisableButton->getHeight(),
//                      minMaxButton->getHeight()),
//                    label->getHeight());
//    
//    
//    currentX = 0;
    
    minimizedRect.x = 0;
	minimizedRect.y = 0;
    minimizedRect.width = maxX;
    minimizedRect.height = currentY;
    
    
    if(isMinimized) {
        
        
        
    } else {
        for(int i = 0; i < childObjects.size(); i++) {
            if(childObjects[i] != enableDisableButton &&
               childObjects[i] != minMaxButton/*&&
                                               childObjects[i] != label &&
                                               childObjects[i] != valueLabel*/) {
                currentX = 0;
                childObjects[i]->setPosition(currentX,currentY);
                currentY += childObjects[i]->getHeight();
                maxX = MAX(maxX,childObjects[i]->getWidth());
            }
        }
    }
    
    setHitBox(0,0,maxX,currentY);
    setContentBoxWidth(getHitBoxWidth());
    setContentBoxHeight(getHitBoxHeight());
}