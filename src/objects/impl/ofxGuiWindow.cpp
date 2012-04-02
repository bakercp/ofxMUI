//--------------------------------------------------------------
#include "ofxGuiWindow.h"

//--------------------------------------------------------------
ofxGuiWindow::ofxGuiWindow(string _name, int _x, int _y, int _width, int _height, bool _enabled) : 
ofxGuiPanel(_name, _x, _y, _width, _height, _enabled) {
    init();
}

//--------------------------------------------------------------
ofxGuiWindow::ofxGuiWindow(string _name, int _x, int _y,bool _enabled) : 
ofxGuiPanel(_name, _x, _y, _enabled) {
    init();
}

//--------------------------------------------------------------
ofxGuiWindow::ofxGuiWindow(string _name,bool _enabled) :
ofxGuiPanel(_name, _enabled) {
    init();
}

//--------------------------------------------------------------
ofxGuiWindow::ofxGuiWindow(bool _enabled) : 
ofxGuiPanel(_enabled) {
    init();
}

//--------------------------------------------------------------
ofxGuiWindow::~ofxGuiWindow() {
    // deletion is of all child objects are done in the super class
    // delete enableDisableButton;
    // delete minMaxButton;
 	
}

//--------------------------------------------------------------
void ofxGuiWindow::init() {
    
    setObjectType("WINDOW");
    
	isMinimized		= false;
    _isDragMoveable	= true;
    
    setTooltip("");
    
    setBoxProperties(defaults->windowBoxProperties);
    
	// draw the min max/ active inactive buttons
	enableDisableButton = new ofxGuiButton();
    enableDisableButton->setButtonIcon(defaults->windowBoxEnableDisableIcon);
    enableDisableButton->keyBind_toggleValue(defaults->keyboardEnableDisable);
    enableDisableButton->setTooltip("Enable/Disable (" + ofToString(defaults->keyboardEnableDisable) + ")");
    enableDisableButton->setTooltipEnabled(true);
	addChild(enableDisableButton);
	
	minMaxButton = new ofxGuiButton();
    minMaxButton->setButtonIcon(defaults->windowBoxMinMaxIcon);
    minMaxButton->keyBind_toggleValue(defaults->keyboardMinMax);
    minMaxButton->setTooltip("Minimize/Maximize (" + ofToString(defaults->keyboardMinMax) + ")");
    minMaxButton->setTooltipEnabled(true);
    addChild(minMaxButton);
	
    requestBoxLayout();
    
}

//--------------------------------------------------------------
void ofxGuiWindow::update() {
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
void ofxGuiWindow::draw() {
    
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
     ofxGuiObject* tmpObj;
     for(int i = 0; i < childObjects.size(); i++)
     {
     tmpObj = (ofxGuiObject*)childObjects.at(i);
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
void ofxGuiWindow::toggleMaxMin()
{
	if(isMinimized) {
		maximize();		
	} else {
		minimize();
	}
	
}

//--------------------------------------------------------------

void ofxGuiWindow::maximize() {
    if(!isMinimized) return;
	isMinimized = false;
    
    for(int i = 0; i < childObjects.size(); i++) {
        if(childObjects[i] != enableDisableButton &&
           childObjects[i] != minMaxButton &&
           childObjects[i] != label &&
           childObjects[i] != valueLabel) {
            childObjects[i]->show();
        }
	}
    
    requestBoxLayout();
}

//--------------------------------------------------------------
void ofxGuiWindow::minimize() {
    if(isMinimized) return;
	isMinimized = true;
    
    // disallow mouse / keyboard input when hidden
    for(int i = 0; i < childObjects.size(); i++) {
        if(childObjects[i] != enableDisableButton &&
           childObjects[i] != minMaxButton &&
           childObjects[i] != label &&
           childObjects[i] != valueLabel) {
            childObjects[i]->hide();
        }
	}
    
    requestBoxLayout();
}


//--------------------------------------------------------------
void ofxGuiWindow::buildFromXml() {	
}

//--------------------------------------------------------------
void ofxGuiWindow::saveToXml()
{   /*
     ofxGuiObject* tmpObj;
     
     int id = name();
     
     mGlobals->mXml.setValue("OBJECT:BORDER", mBorder, id);
     mGlobals->mXml.setValue("OBJECT:SPACING", mSpacing, id);
     mGlobals->mXml.pushTag("OBJECT", id);
     
     for(int i = 0; i < childObjects.size(); i++)
     {
     tmpObj = (ofxGuiObject*)childObjects.at(i);
     tmpObj->saveToXml();
     }
     
     mGlobals->mXml.popTag();
     */
}


//--------------------------------------------------------------
void ofxGuiWindow::doContentBoxLayout() {
    
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
    int labelY = (minMaxButton->getY() + minMaxButton->getHeight()) / 2.0 -label->getHeight() / 2.0 ;
    label->setPosition(currentX, labelY);
    
    
    maxX = MAX(maxX, label->getPosition().x + label->getWidth());
    
    currentY+=MAX(MAX(enableDisableButton->getHeight(),
                      minMaxButton->getHeight()),
                    label->getHeight());
    
    
    currentX = 0;
    
    minimizedRect.x = 0;
	minimizedRect.y = 0;
    minimizedRect.width = maxX;
    minimizedRect.height = currentY;
    
    
    if(isMinimized) {
        
        
        
    } else {
        for(int i = 0; i < childObjects.size(); i++) {
            if(childObjects[i] != enableDisableButton &&
               childObjects[i] != minMaxButton &&
               childObjects[i] != label &&
               childObjects[i] != valueLabel) {
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