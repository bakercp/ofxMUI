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

#include "ofMain.h"
#include "ofxXmlSettings.h"

#include "ofxMuiDefaults.h"
#include "ofxMuiUtils.h"
#include "ofxMuiEnabler.h"
#include "ofxMuiBox.h"
#include "ofxMuiKeyMapper.h"


class ofxMuiObject : public ofxMuiBox, public ofxMuiEnabler, public ofxMuiKeyMapper  {
public:
    
    //--------------------------------------------------------------
    // CONSTRUCTORS+DESTRUCTORS ////////////////////////////////////
    //--------------------------------------------------------------

    ofxMuiObject(const string& _name, int _x, int _y, int _width, int _height, bool _enabled = true);
    ofxMuiObject(const string& _name, int _x, int _y, bool _enabled = true);
    ofxMuiObject(const string& _name, bool _enabled = true);
    ofxMuiObject(bool _enabled = true);
    
    virtual ~ofxMuiObject();
    
    //--------------------------------------------------------------
    // STANDARD OF MESSAGES ////////////////////////////////////////
    //--------------------------------------------------------------
	
    void            _setup(ofEventArgs &e);
	void            _update(ofEventArgs &e);
    void            _draw(ofEventArgs &e);
	void            _exit(ofEventArgs &e);
    void            _windowResized(ofResizeEventArgs &e);
    ofxMuiObject*   _fileDragEvent(ofDragInfo &e, ofxMuiObject* handled);
    void            _gotMessage(ofMessage &e);
    
    //--------------------------------------------------------------
    // MOUSE HANDLING //////////////////////////////////////////////
    //--------------------------------------------------------------
	
    ofxMuiObject*	_mouseMoved(ofMouseEventArgs &e,	ofxMuiObject* handled); 
	ofxMuiObject*	_mousePressed(ofMouseEventArgs &e,	ofxMuiObject* handled, int numClicks);
	ofxMuiObject*	_mouseDragged(ofMouseEventArgs &e,	ofxMuiObject* handled);//, ofxMuiObject* dragObject);
	ofxMuiObject*	_mouseReleased(ofMouseEventArgs &e,	ofxMuiObject* handled);//, ofxMuiObject* dragObject);
    
    //--------------------------------------------------------------
    // KEYBOARD HANDLING ///////////////////////////////////////////
    //--------------------------------------------------------------

	ofxMuiObject*	_keyPressed(ofKeyEventArgs &e,	ofxMuiObject* handled);
	ofxMuiObject*	_keyReleased(ofKeyEventArgs &e,	ofxMuiObject* handled);
    
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
	virtual	void	loadFromXml(ofxXmlSettings& xml) {}
	virtual	void	saveToXml(ofxXmlSettings& xml) {}

    //--------------------------------------------------------------
    // ofxMuiEnabler CALLBACK //////////////////////////////////////
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
    bool    isDragMoveable() const;
    
    bool    isDragging() const;
    
    bool    isHitDragable() const;
    bool    isHitDragOrigin() const;

    void    setIsFileDropReceiver(bool _val);
    bool    isFileDropReceiver() const;
    
    void    setIsDropSender(bool _val);
    bool    isDropSender() const;
    
    void    setIsDropReceiver(bool _val);
    bool    isDropReceiver() const;
    
    //--------------------------------------------------------------
    // INTERACTIVE INPUT ///////////////////////////////////////////
    //--------------------------------------------------------------

    bool    isMouseDown() const;
    bool    isMouseOver() const;
    
    //--------------------------------------------------------------
    // TOOLTIP /////////////////////////////////////////////////////
    //--------------------------------------------------------------

    string  getTooltip() const;
    void    setTooltip(const string& _tooltip);
    
    bool    isTooltipEnabled() const;
    void    setTooltipEnabled(bool _enable);
    
    //--------------------------------------------------------------
    // OBJECT TREE AND FAMILY //////////////////////////////////////
    //--------------------------------------------------------------
    
    ofxMuiObject* getParent();
    void setParent(ofxMuiObject* parent);
    
    // implemets virtual method from box
	bool hasParent() const;

    bool isChild(ofxMuiObject* child);
    void addChild(ofxMuiObject* child);
    bool removeChild(ofxMuiObject* child);
    bool hasChildren();
  
    //--------------------------------------------------------------
    // COLORS/SHADOWS //////////////////////////////////////////////
    //--------------------------------------------------------------

    float getAlphaScale() const;
    void  setAlphaScale(float _alphaScale);
    
    bool  getDoShadow() const;
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

    ofxMuiDefaults* defaults;

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
	virtual void onObjectDragOver(ofxMuiObject* dropableObject) {}
	
    // onObjectDragOutside: called when a valid drop object is dragged 
    // outside of a valid receiver
	virtual void onObjectDragOutside(ofxMuiObject* dropableObject) {}
	
    // onObjectDropSent: called when an object is dropped 
	virtual void onObjectDropSent(ofxMuiObject* sentObject) {}
    
    // onObjectDropReceived: called by the receiver ON the 
    //      sender when received
	virtual void onObjectDropReceived(ofxMuiObject* receiverObject) {} 
	
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
    ofxMuiColor cBox;      // usually clear
    ofxMuiColor cMargin;   // the margin frame color
    ofxMuiColor cBorder;   // the border frame color
    
    ofxMuiColor cContent;  // the content box is usually just clear to let
    ofxMuiColor cPadding;  // usually the padding box sets color for content
                           // the padding box color shine through
    ofxMuiColor cHit;   // the hit
    
    // TEXT
    ofxMuiColor cText;     // the standard color of the text
    
    // the active areas are any area that is "hot"
    // i.e. a button, a slider, a switch zone, etc.
    
    ofxMuiColor cActiveAreaForeground; // color of the active area's bg
    ofxMuiColor cActiveAreaBackground; // color of the active area's bg
    ofxMuiColor cActiveAreaFrame;      // color of the active area's frame
    
    // SHADOWS
    ofxMuiColor cShadow;        // the color of the shadow
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
	
	virtual bool	isDropReceiverForObject(ofxMuiObject* dragObject);
    
    //--------------------------------------------------------------
    // FAMILY OBJECTS //////////////////////////////////////////////
    //--------------------------------------------------------------

    // 
    
    // moves through the focus tree
    //ofxMuiObject* inFocus;
    // void nextFocus();
    // void lastFocus();
        
    bool canHandleIt(ofxMuiObject* handled);
    
    
    ofxMuiObject*                   parent;
	vector<ofxMuiObject*>			childObjects;
	vector<ofxMuiObject*>::iterator	childObjectsIter;

    //--------------------------------------------------------------
    // ORIENTATION /////////////////////////////////////////////////
    //--------------------------------------------------------------    
    
    ofOrientation orientation;
    
};

