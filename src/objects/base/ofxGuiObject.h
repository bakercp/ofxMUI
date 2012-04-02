/*
 *  ofxGuiObject.h
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

#include "ofMain.h"

#include "ofxGuiDefaults.h"
#include "ofxGuiUtils.h"
#include "ofxGuiEnabler.h"
#include "ofxGuiBox.h"
#include "ofxGuiKeyMapper.h"


class ofxGuiObject : public ofxGuiBox, public ofxGuiEnabler, public ofxGuiKeyMapper  {
public:
    
    //--------------------------------------------------------------
    // CONSTRUCTORS+DESTRUCTORS ////////////////////////////////////
    //--------------------------------------------------------------

    ofxGuiObject(string _name, int _x, int _y, int _width, int _height, bool _enabled = true);
    ofxGuiObject(string _name, int _x, int _y, bool _enabled = true);
    ofxGuiObject(string _name, bool _enabled = true);
    ofxGuiObject(bool _enabled = true);
    
    virtual ~ofxGuiObject();
    
    //--------------------------------------------------------------
    // STANDARD OF MESSAGES ////////////////////////////////////////
    //--------------------------------------------------------------
	
    void            _setup(ofEventArgs &e);
	void            _update(ofEventArgs &e);
    void            _draw(ofEventArgs &e);
	void            _exit(ofEventArgs &e);
    void            _windowResized(ofResizeEventArgs &e);
    ofxGuiObject*   _fileDragEvent(ofDragInfo &e, ofxGuiObject* handled);
    void            _gotMessage(ofMessage &e);
    
    //--------------------------------------------------------------
    // MOUSE HANDLING //////////////////////////////////////////////
    //--------------------------------------------------------------
	
    ofxGuiObject*	_mouseMoved(ofMouseEventArgs &e,	ofxGuiObject* handled); 
	ofxGuiObject*	_mousePressed(ofMouseEventArgs &e,	ofxGuiObject* handled, int numClicks);
	ofxGuiObject*	_mouseDragged(ofMouseEventArgs &e,	ofxGuiObject* handled);//, ofxGuiObject* dragObject);
	ofxGuiObject*	_mouseReleased(ofMouseEventArgs &e,	ofxGuiObject* handled);//, ofxGuiObject* dragObject);
    
    //--------------------------------------------------------------
    // KEYBOARD HANDLING ///////////////////////////////////////////
    //--------------------------------------------------------------

	ofxGuiObject*	_keyPressed(ofKeyEventArgs &e,	ofxGuiObject* handled);
	ofxGuiObject*	_keyReleased(ofKeyEventArgs &e,	ofxGuiObject* handled);
    
    //--------------------------------------------------------------
    // STANDARD OF MESSAGE CALLBACKS ///////////////////////////////
    //--------------------------------------------------------------
    
    virtual void	setup()  {}
	virtual void	update() {}
    
    // can be overriden in subclass
    virtual void    drawBox();          // draw the full box
    virtual void    drawBorder();  //
    virtual void    drawPaddingBox();   // draw the padding box
    
    virtual void    drawShadowBox();    // this is a shadow of the border box
    
    virtual void    drawContentBox();   // draw Content Box
    
    virtual void	draw() = 0;         // draw the contents of content box
    
	virtual void	exit() {}

    virtual void	windowResized(ofResizeEventArgs &e) {}
	virtual void	fileDragEvent(ofDragInfo &dragInfo) {}
	virtual void	gotMessage(ofMessage &msg) {}

    //--------------------------------------------------------------
    // XML /////////////////////////////////////////////////////////
    //--------------------------------------------------------------

	int				saveObjectData();
	virtual	void	buildFromXml() {}
	virtual	void	saveToXml() {}

    //--------------------------------------------------------------
    // ofxGuiEnabler CALLBACK //////////////////////////////////////
    //--------------------------------------------------------------

    void doSetEnabled(bool _enabled);

    //--------------------------------------------------------------
    // LABELS //////////////////////////////////////////////////////
    //--------------------------------------------------------------

    void    setName(string _label);
    string  getName();

    //--------------------------------------------------------------
    // DRAGGING+DROPPING ///////////////////////////////////////////
    //--------------------------------------------------------------
	void    cancelDrag();   // immediate cancel the dragging
	
    void    setIsDragMoveable(bool _val); // can we drag this thing around
    bool    isDragMoveable();
    
    bool    isDragging();
    
    bool    isHitDragable();
    bool    isHitDragOrigin();

    void    setIsFileDropReceiver(bool _val);
    bool    isFileDropReceiver();
    
    void    setIsDropSender(bool _val);
    bool    isDropSender();
    
    void    setIsDropReceiver(bool _val);
    bool    isDropReceiver();
    
    //--------------------------------------------------------------
    // INTERACTIVE INPUT ///////////////////////////////////////////
    //--------------------------------------------------------------

    bool    isMouseDown();
    bool    isMouseOver();
    
    //--------------------------------------------------------------
    // TOOLTIP /////////////////////////////////////////////////////
    //--------------------------------------------------------------

    string  getTooltip();
    void    setTooltip(string _tooltip);
    
    bool    isTooltipEnabled();
    void    setTooltipEnabled(bool _enable);
    
    //--------------------------------------------------------------
    // OBJECT TREE AND FAMILY //////////////////////////////////////
    //--------------------------------------------------------------
    
    ofxGuiObject* getParent();
    void setParent(ofxGuiObject* parent);
    
    // implemets virtual method from box
	bool hasParent();

    bool isChild(ofxGuiObject* child);
    void addChild(ofxGuiObject* child);
    bool removeChild(ofxGuiObject* child);
    bool hasChildren();
  
    //--------------------------------------------------------------
    // COLORS/SHADOWS //////////////////////////////////////////////
    //--------------------------------------------------------------

    float getAlphaScale();
    void  setAlphaScale(float _alphaScale);
    
    bool  getDoShadow();
    void  setDoShadow(bool _doShadow);
    
    //--------------------------------------------------------------
    // SUPERCLASSES ////////////////////////////////////////////////
    //--------------------------------------------------------------

    virtual ofVec2f getBoxScreenPosition();

    ofVec2f getContentBoxScreenPosition();
    
    //--------------------------------------------------------------
    // DEBUG ///////////////////////////////////////////////////////
    //--------------------------------------------------------------
    
    string getDebugString();
    
    
    // TODO: const?
    string getObjectType();
    
    //--------------------------------------------------------------
    // ORIENTATION /////////////////////////////////////////////////
    //--------------------------------------------------------------

    void setOrientation(ofOrientation _orientation); 
    ofOrientation getOrientation(); 
    
    bool isOrientationHorizontal();
    
protected:
    
    //--------------------------------------------------------------
    // SETTINGS ////////////////////////////////////////////////////
    //--------------------------------------------------------------

    ofxGuiDefaults* defaults;

    //--------------------------------------------------------------
    // CALLED BY CONSTRUCTOR ///////////////////////////////////////
    //--------------------------------------------------------------
    
    // not virtual, because it is only used in the constructor 
    // and subclasses should be able to define and call their own locally
    void init();
    
    //--------------------------------------------------------------
    // TOOLTIP /////////////////////////////////////////////////////
    //--------------------------------------------------------------

    
    bool    tooltipEnabled;
    string  tooltip;
    
    
    
    // TODO: add in more complex getters and setters for other info
    // like key shortcuts and osc addresses?
    
    //--------------------------------------------------------------
    // INPUT EVENT HANDLING ////////////////////////////////////////
    //--------------------------------------------------------------
    // keyboard
    void setKeyboardOnPress(bool _keyboardOnPress);
    bool getKeyboardOnPress();
    
    
    // TODO this is kind of a HACK until of gets it's special
    // keypresses figured out
    
    bool isShiftPressed();
    bool isCtrlPressed();
    bool isAltPressed();
    
    float getActiveTimer();
    
    //--------------------------------------------------------------
    // MOUSE MOVEMENT CALLBACKS ////////////////////////////////////
    //--------------------------------------------------------------
    
    // onRollOver: called when mouse enters object x, y, width, height
	virtual void onRollOver() {}
    // onRollOut: called when mouse leaves object x, y, width, height
	virtual void onRollOut() {}
    // onMouseMove: called when mouse moves while over object x, y, width, height
    virtual void onMouseMove() {}			

    //--------------------------------------------------------------
    // MOUSE PRESS CALLBACKS ///////////////////////////////////////
    //--------------------------------------------------------------
    
    // onPress: called when mouse presses while over object
    virtual void onPress() {}		
    
    // onDoublePress: called when mouse is double-clicked while over object
    virtual void onDoublePress() {}
    
    // onPressOutside: called when mouse presses while outside object
	virtual void onPressOutside() {}		
    
    // onRelease: called when mouse releases while over object
	virtual void onRelease() {}
	
    // onReleaseOutside: called when mouse releases outside 
    //      of object after being pressed on object
    virtual void onReleaseOutside()	{}		

    //--------------------------------------------------------------
    // MOUSE DRAG CALLBACKS ////////////////////////////////////////
    //--------------------------------------------------------------
    
    // onDrag: called on the handling object ANYTIME the mouse is 
    //             being dragged. this is called alongside onDragOver/onDragOutside
    //             probably best not to implement both.
    virtual void onDrag() {}
        
    // onDragStart: called when a drag is started for an object
    virtual void onDragStart() {};
    
    // onDragEnd: called when a drag is ended for an object
    virtual void onDragEnd() {};

    // onDragCancelled: this gets called when a drag gets cancelled
	virtual void onDragCancelled() {};
    
    // onDragMoving: this is called when the object is being moved via dragging
    virtual void onDragMoving() {};
    
    // onDragOver: called when mouse moves while over object 
    //             and button is down (but not dragging object)
	virtual void onDragOver() {}			
    // onDragOutside: called when mouse moves while outside 
    //             the object after being clicked on it
    virtual void onDragOutside() {}
    
    
    
    /*
    // onDragReleased: these values should already be set
    virtual void onDragReleased(int newLocalPositionX, 
                                int newLocalPositionY) {}	
    */
    
    //--------------------------------------------------------------
    // OBJECT DRAGGING CALLBACKS ///////////////////////////////////
    //--------------------------------------------------------------
    
    /*
    // onObjectDragStart: called when the object is beig dragged
	virtual void onObjectDragStart( ofMouseEventArgs &e ) {}
    
    // onObjectDragEnd: called when the dragging object is dropped
	virtual void onObjectDragEnd( ofMouseEventArgs &e ) {}
    
    // onObjectDragging: called when the mouse is dragging this object
	virtual void onObjectDragging( ofMouseEventArgs &e ) {}		
    */
     
    
    // onObjectDragOver: called when a valid drop object is dragged over 
    // a valid receiver
	virtual void onObjectDragOver(ofxGuiObject* dropableObject) {}
	
    // onObjectDragOutside: called when a valid drop object is dragged 
    // outside of a valid receiver
	virtual void onObjectDragOutside(ofxGuiObject* dropableObject) {}
	
    // onObjectDropSent: called when an object is dropped 
	virtual void onObjectDropSent(ofxGuiObject* sentObject) {}
    
    // onObjectDropReceived: called by the receiver ON the 
    //      sender when received
	virtual void onObjectDropReceived(ofxGuiObject* receiverObject) {} 
	
    //--------------------------------------------------------------
    // KEY PRESS CALLBACKS /////////////////////////////////////////
    //--------------------------------------------------------------

    // onKeyPressed: called when a key is pressed with the object in focus
	virtual void onKeyPressed() {}		
    // onKeyReleased: called when a key is released with the obejct in focus
    virtual void onKeyReleased() {}		
    
    //--------------------------------------------------------------
    // COLORS/SHADOWS //////////////////////////////////////////////
    //--------------------------------------------------------------
    //
    // basic box colors
    // none of these boxes have frames
    // the border is the only frame
    //
    
    // BOXES
    ofxGuiColor cBox;      // usually clear
    ofxGuiColor cMargin;   // the margin frame color
    ofxGuiColor cBorder;   // the border frame color
    
    ofxGuiColor cContent;  // the content box is usually just clear to let
    ofxGuiColor cPadding;  // usually the padding box sets color for content
                           // the padding box color shine through
    ofxGuiColor cHit;   // the hit
    
    // TEXT
    ofxGuiColor cText;     // the standard color of the text
    
    // the active areas are any area that is "hot"
    // i.e. a button, a slider, a switch zone, etc.
    
    ofxGuiColor cActiveAreaForeground; // color of the active area's bg
    ofxGuiColor cActiveAreaBackground; // color of the active area's bg
    ofxGuiColor cActiveAreaFrame;      // color of the active area's frame
    
    // SHADOWS
    ofxGuiColor cShadow;        // the color of the shadow
                                // the shadow box is the 

    bool        doShadow;       // will the shadow be drawn?
    ofVec2f     shadowOffset;
    
    // OVERALL ALPHA SCALE
    float alphaScale;  // all colors respect the alpha scale
                       // when called

    
    //--------------------------------------------------------------
    // LABELS/TEXT /////////////////////////////////////////////////
    //--------------------------------------------------------------
    
	string name; // the name of this paramater
                 // serves as the default for tooltips and 
                 // (in some cases) display text

    string objectType;
    
    void setObjectType(string objectType);
    
    //--------------------------------------------------------------
    // INTERACTIVE INPUT ///////////////////////////////////////////
    //--------------------------------------------------------------

    // keyboard states
	int     key;
    int     pKey;
	bool    keyboardOnPress;
    
    // mouse states
	bool    _isMouseDown;
    bool    _isMouseOver;
	
    // mouse positions
    ofVec2f mousePosition;
    ofVec2f pMousePosition;
    
    ofVec2f deltaMousePosition; // diff between mousePosition and pMousePosition
    
    // mouse buttons
    int     mouseButton;
    int     pMouseButton;

    // used to set all of the previous states
    void    saveMouseEvent(ofMouseEventArgs &e); 
    void    saveKeyboardEvent(ofKeyEventArgs &e); 

    // allow for easy fading in and out and other 
    float isActiveTimer;
    float isActiveTimerRate;
        
    //--------------------------------------------------------------
    // DRAGGING+DROPPING ///////////////////////////////////////////
    //--------------------------------------------------------------

	bool			_isDragMoveable; // can we drag this thing around
	bool			_isDragging;		// is dragging
	
    // for times when we start a drag inside of a hit
    bool            _isHitDragable;
    bool            _isHitDragOrigin;
    
	ofVec2f         dragStartPosition; // where we were before the dragging started
    ofVec2f         totalDragDelta; // the total delta diff between dragstart 
                                    // position and current mousePositio 
    
    bool            _isFileDropReceiver;
    
	// object dragging and dropping
	bool			_isDropSender; // can we drop this thing on something
	bool			_isDropReceiver; // can we receive a dropped object
	
	virtual bool	isDropReceiverForObject(ofxGuiObject* dragObject);
    
    //--------------------------------------------------------------
    // FAMILY OBJECTS //////////////////////////////////////////////
    //--------------------------------------------------------------

    // 
    
    // moves through the focus tree
    //ofxGuiObject* inFocus;
    // void nextFocus();
    // void lastFocus();
        
    bool canHandleIt(ofxGuiObject* handled);
    
    
    ofxGuiObject*                   parent;
	vector<ofxGuiObject*>			childObjects;
	vector<ofxGuiObject*>::iterator	childObjectsIter;

    //--------------------------------------------------------------
    // ORIENTATION /////////////////////////////////////////////////
    //--------------------------------------------------------------    
    
    ofOrientation orientation;
    
};

