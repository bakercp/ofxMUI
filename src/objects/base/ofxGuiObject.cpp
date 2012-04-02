/*
 *  ofxGuiObject.cpp
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
#include "ofxGuiObject.h"

//--------------------------------------------------------------
ofxGuiObject::ofxGuiObject(string _name, int _x, int _y, int _width, int _height, bool _enabled) : 
    ofxGuiBox(_x,_y,_width,_height), 
    ofxGuiEnabler(_enabled), 
    ofxGuiKeyMapper(),
    name(_name) {
        init();
}
//--------------------------------------------------------------
ofxGuiObject::ofxGuiObject(string _name, int _x, int _y, bool _enabled) : 
    ofxGuiBox(_x,_y), 
    ofxGuiEnabler(_enabled), 
    ofxGuiKeyMapper(),
    name(_name) {
        init();
}
//--------------------------------------------------------------
ofxGuiObject::ofxGuiObject(string _name, bool _enabled) : 
    ofxGuiBox(), 
    ofxGuiEnabler(_enabled), 
    ofxGuiKeyMapper(),
    name(_name) {
        init();
}

//--------------------------------------------------------------
ofxGuiObject::ofxGuiObject(bool _enabled) : 
    ofxGuiBox(), 
    ofxGuiEnabler(_enabled), 
    ofxGuiKeyMapper(),
    name("NULL") {
        init();
}

//--------------------------------------------------------------
ofxGuiObject::~ofxGuiObject() {
    // clear and delete any child objects
    for(int i = 0; i < childObjects.size(); i++) delete childObjects[i];
    childObjects.clear();
}

//--------------------------------------------------------------
void ofxGuiObject::init() {
    defaults = &ofxGuiDefaults::getInstance(); // get a link to the singleton
    
    tooltip             = name;
    tooltipEnabled      = false;
    
	parent              = NULL;

	_isMouseDown        = false;
	_isMouseOver        = false;
	
	// drag'n'drop
	_isDragMoveable		= false;
	_isDragging			= false;
    
    _isHitDragable   = true;
    _isHitDragOrigin = false;

	_isDropSender		= false; // can we drop this thing on something
	_isDropReceiver		= false; // can we receive a dropped object
	
    _isFileDropReceiver  = false;
    
    // set vars from static members
    cBox                = defaults->cBox;
    cBorder             = defaults->cBorder;
    cPadding            = defaults->cPadding;
    cContent            = defaults->cContent;
    cHit                = defaults->cHit;
    
    cText               = defaults->cText;

    cActiveAreaForeground = defaults->cActiveAreaForeground;
    cActiveAreaBackground = defaults->cActiveAreaBackground;
    cActiveAreaFrame      = defaults->cActiveAreaFrame;
    
    cShadow             = defaults->cShadow;

    doShadow            = defaults->doShadow;
    shadowOffset        = defaults->shadowOffset;
    
    alphaScale          = defaults->alphaScale;
    
    keyboardOnPress     = defaults->keyboardOnPress;
    
    objectType          = "BASE_OBJECT";
    
    orientation         = OF_ORIENTATION_DEFAULT;
    
    isActiveTimer       = 0.0f;
    isActiveTimerRate   = 0.05f;
            
}


//--------------------------------------------------------------

void ofxGuiObject::_setup(ofEventArgs &e) {
	if(!isEnabled()) return;
    
    // propagate setup
    if(propagateSetupEvents()) {
        for(int i = 0; i < childObjects.size(); i++) {
            ofxGuiPushObject(childObjects[i]);
            childObjects[i]->_setup(e);
            ofxGuiPopObject();
        }
    }
    
    // do local setup
	if(isSetupHandler()) {
        setup();
    }
}


//--------------------------------------------------------------

void ofxGuiObject::_update(ofEventArgs &e) {
    if(!isEnabled()) return;
	
    
    for(int i = 0; i < childObjects.size(); i++) {
        // update child (this will resize its frame if needed)
        ofxGuiPushObject(childObjects[i]);
        
        childObjects[i]->_update(e);
        if(childObjects[i]->getParentNeedsLayoutUpdate()) {
            needsLayout = true;
        }
        
        ofxGuiPopObject();
    }
	
    // TODO: do layout changes always happen? 
    // resize the local frames, propagate layout requests
    if(needsLayout) {
        isLayoutSetupComplete = true;
        doLayout(); // will set to false
    }
    
    if(isUpdateHandler()) {
        // do the local update
        if (isMouseOver() || isMouseDown() || isDragging()) {
            isActiveTimer += isActiveTimerRate;
        } else {
            isActiveTimer -= isActiveTimerRate;
        }
        
        isActiveTimer = ofClamp(isActiveTimer,0,1);
        
        update();
    }

}

//--------------------------------------------------------------
void ofxGuiObject::_draw(ofEventArgs &e) {
    
    
    //ofxGuiDebugString(this, "DRAW-> " + this->getName() + " isHidden()=" + ofToString(isHidden()));
    
	if(!isEnabled() || isHidden()) return;

    ofPushStyle();
    ofPushMatrix();
    {
        ofTranslate(getPosition());
        
        if(isDrawHandler()) {

            ////////////////////////////////////////////////////////
            // DRAW THE BOX / MARGIN ///////////////////////////////
            ////////////////////////////////////////////////////////
            
            drawBox();

            ////////////////////////////////////////////////////////
            // DRAW THE BORDER BOX /////////////////////////////////
            ////////////////////////////////////////////////////////
            
            ofPushMatrix();
            {
                ofTranslate(getBorderBoxOffset());
                drawShadowBox();
                drawBorder();
            }
            ofPopMatrix();
            
            ////////////////////////////////////////////////////////
            // DRAW THE PADDING BOX ////////////////////////////////
            ////////////////////////////////////////////////////////

            ofPushMatrix();
            {
                ofTranslate(getPaddingBoxOffset());
                drawPaddingBox();
            }
            ofPopMatrix(); 
        
            ////////////////////////////////////////////////////////
            // DRAW THE CONTENT BOX ////////////////////////////////
            ////////////////////////////////////////////////////////
            
            ofPushMatrix();
            {
                ofTranslate(getContentBoxOffset());
                drawContentBox();
            }
            ofPopMatrix();
        }
        
        if(propagateDrawEvents()) {
            ofPushMatrix();
            {
                ofTranslate(getContentBoxOffset());
                
                ////////////////////////////////////////////////////////
                // SET UP CONTENT BOX CLIPPING IF REQUESTED ////////////
                ////////////////////////////////////////////////////////
                if(defaults->enableContentBoxClipping) {
                    ofVec2f sp = getContentBoxScreenPosition();
                    glEnable(GL_SCISSOR_TEST);
                    glScissor(sp.x-2, sp.y-2, getContentBoxWidth()+3,getContentBoxHeight()+3);
                }
                ////////////////////////////////////////////////////////
                // DRAW THE CONTENT ITSELF /////////////////////////////
                ////////////////////////////////////////////////////////
                draw(); ////////////////////////////////////////////////
                ////////////////////////////////////////////////////////
                // SET UP CONTENT BOX CLIPPING IF REQUESTED ////////////
                ////////////////////////////////////////////////////////
                if(defaults->enableContentBoxClipping) {
                    glDisable(GL_SCISSOR_TEST);
                }
                ////////////////////////////////////////////////////////
                
                for(int i = 0; i < childObjects.size(); i++) {
                    ofxGuiPushObject(childObjects[i]);
                    childObjects[i]->_draw(e);
                    ofxGuiPopObject();
                }
                
            }
        }
        
        ofPopMatrix();
    }
    ofPopMatrix();
    ofPopStyle();

}

//--------------------------------------------------------------
void ofxGuiObject::_exit(ofEventArgs &e) {
    // always propagated.  always executed
    
    for(int i = 0; i < childObjects.size(); i++) {
        ofxGuiPushObject(childObjects[i]);
        childObjects[i]->_exit(e);
        ofxGuiPopObject();
    }

	exit();
}

//--------------------------------------------------------------
void ofxGuiObject::_windowResized(ofResizeEventArgs &e) {
    // always propagated
    if(propagateWindowResizedEvents()) {
        for(int i = 0; i < childObjects.size(); i++) { 
            ofxGuiPushObject(childObjects[i]);
            childObjects[i]->_windowResized(e);
            ofxGuiPopObject();
        }
    }
        
    if(isWindowResizedHandler()) {
        windowResized(e);
    }
}

//--------------------------------------------------------------
ofxGuiObject*  ofxGuiObject::_fileDragEvent(ofDragInfo &e, ofxGuiObject* handled) {
//    vector <string> files;
//    ofPoint position;

	ofxGuiObject* newHandler = NULL;
    
    // always propagated ... (?)
    if(propagateFileDragEvents()) {
        for(int i = 0; i < childObjects.size(); i++) {
            ofxGuiPushObject(childObjects[i]);
            newHandler = childObjects[i]->_fileDragEvent(e, handled);
            ofxGuiPopObject();
            if(!handled && newHandler) {
                handled = newHandler;
            }
        }
    }
    
    if(isFileDragHandler() && canHandleIt(handled) && hitTest(e.position)) {
        fileDragEvent(e);
        handled = this;
    } 
    
    return handled;
}

//--------------------------------------------------------------
void ofxGuiObject::_gotMessage(ofMessage &e) {
    // always propagated (?)
    
    if(propagateMessageEvents()) {
        for(int i = 0; i < childObjects.size(); i++) {
            ofxGuiPushObject(childObjects[i]);
            childObjects[i]->_gotMessage(e);
            ofxGuiPopObject();
        }
    }
    
    gotMessage(e);
}

//--------------------------------------------------------------

ofxGuiObject* ofxGuiObject::_keyPressed(ofKeyEventArgs &e, ofxGuiObject* handled) {
	if(!isEnabled() || !keyboardOnPress || isHidden()) return NULL;
    
	ofxGuiObject* newHandler = NULL;
	
    saveKeyboardEvent(e);

    if(propagateKeyboardEvents()) {
        for(int i = (childObjects.size()-1); i >= 0; i--) {
            ofxGuiPushObject(childObjects[i]);
            newHandler = childObjects[i]->_keyPressed(e, handled);
            ofxGuiPopObject();
            // currently an event can only be handled by one item
            if(!handled && newHandler) {
                handled = newHandler;
            }
        }
    }
    
    if(isKeyboardHandler() && canHandleIt(handled) && executeKeyMappedFunc(key)) {
        onKeyPressed(); // just an alert (should be earlier?)
        handled = this;
    }

	
	return handled;
}

//--------------------------------------------------------------

ofxGuiObject* ofxGuiObject::_keyReleased(ofKeyEventArgs &e, ofxGuiObject* handled) {
	if(!isEnabled() || keyboardOnPress || isHidden()) return NULL;
    
	ofxGuiObject* newHandler = NULL;
	
    saveKeyboardEvent(e);
    
    if(propagateKeyboardEvents()) {
        for(int i = (childObjects.size()-1); i >= 0; i--) {
            ofxGuiPushObject(childObjects[i]);
            newHandler = childObjects[i]->_keyReleased(e, handled);
            ofxGuiPopObject();
            // currently an event can only be handled by one item
            if(!handled && newHandler) {
                handled = newHandler;
            }
        }
    }
	
    if(isKeyboardHandler() && canHandleIt(handled) && executeKeyMappedFunc(key)) {
        onKeyReleased();
        handled = this;
    }
	
	return handled;
}

//--------------------------------------------------------------

ofxGuiObject* ofxGuiObject::_mouseMoved(ofMouseEventArgs &e, ofxGuiObject* handled) {
    
	if(!isEnabled() || isHidden()) return NULL;

    saveMouseEvent(e);
    
    if(propagateMouseEvents()) {
        ofxGuiObject* newHandler = NULL;
        for(int i = (childObjects.size()-1); i >= 0; i--) {
            ofxGuiPushObject(childObjects[i]);
            newHandler = childObjects[i]->_mouseMoved(e, handled);
            ofxGuiPopObject();
            // currently an event can only be handled by one item
            if(!handled && newHandler) {
                handled = newHandler;
            }
        }
    }
	
    bool didHit = hitTest(mousePosition); // if mouse is over the object

	if(isMouseHandler() && canHandleIt(handled) && didHit) { 

		// if the mouse wasn't over it already
		if(!isMouseOver()) {
			onRollOver();	// call onRollOver
			_isMouseOver = true;				// update flag
		} else {
			// we were already on it!
			onMouseMove();	// and trigger onMouseMove
		}

		handled = this; // this is the handler now!
        
	} else if(isMouseOver()) {		// if mouse is not over the object, but the flag is true (From previous frame)
		_isMouseOver = false;		// update flag
		onRollOut();			// call onRollOut
	} else {
		// unaffected
	}
	
	return handled;
}

//--------------------------------------------------------------

ofxGuiObject* ofxGuiObject::_mouseDragged(ofMouseEventArgs &e, ofxGuiObject* handled) {
	

	if(!isEnabled() || isHidden()) return NULL;
	
	saveMouseEvent(e);

    if(propagateMouseEvents()) {
        ofxGuiObject* newHandler = NULL;
        for(int i = (childObjects.size()-1); i >= 0; i--) {
            ofxGuiPushObject(childObjects[i]);
            newHandler = childObjects[i]->_mouseDragged(e, handled);
            ofxGuiPopObject();
            // currently an event can only be handled by one item
            if(!handled && newHandler) {
                handled = newHandler;
            }
        }
    }
		
	bool didHit = hitTest(mousePosition);
	
    if(isMouseHandler() && (isDragging() || (canHandleIt(handled) && didHit && isMouseDown()))) {				

        if(!isDragging()) {
            _isDragging = true;
            dragStartPosition = mousePosition;
            
//            if (isHitDragable() && insideHitBox(screenToHitBox(mousePosition))) {
            if (isHitDragable() && hitTest(mousePosition)) {

                _isHitDragOrigin = true;
            } else {
                _isHitDragOrigin = false;
            }
            
            onDragStart();
        } else {
            totalDragDelta = mousePosition - dragStartPosition;
            onDrag();
        }
        
        if(isDragMoveable() && (!isHitDragable() && isHitDragOrigin())) {
            
            ofVec2f pos = getPosition();
            ofVec2f maxB = getMaxBounds();
            ofVec2f minB = getMinBounds();
            
            ofVec2f inWPos;
            if(hasParent()) {
                inWPos = parent->screenToHitBox(mousePosition);
            } else {
                inWPos = screenToHitBox(mousePosition);
            }
            

            
          //  (inWPos.x > minB.x && deltaMousePosition.x > 0)
          //  ||
          //  (inWPos.x < (maxB.x + hitBox.width) && deltaMousePosition.x < 0)) {
            
            
            
            
            
            if((inWPos.x > minB.x && deltaMousePosition.x > 0) ||
               (inWPos.x < maxB.x && deltaMousePosition.x < 0)) {
                addX(deltaMousePosition.x);
            }
            
            
                addY(deltaMousePosition.y);

            onDragMoving();
        } 
            
        if(didHit) {
            onDragOver();
        } else {
            onDragOutside();
        }
        
		handled = this;
	
	} else {
                
		// ALREADY HANDLED OR NOT DRAGGING OR NOT OVER
		if(didHit) {
			if(isDropReceiverForObject(handled)) {
                onObjectDragOver(handled);
            }
		} else {
			if(isDropReceiverForObject(handled)) {
                onObjectDragOutside(handled);
            }
		}		
	}
		
	return handled;
}

//--------------------------------------------------------------

ofxGuiObject* ofxGuiObject::_mousePressed(ofMouseEventArgs &e, ofxGuiObject* handled, int numClicks) {

	if(!isEnabled() || isHidden()) return NULL;
	
	saveMouseEvent(e);

    if(propagateMouseEvents()) {
        ofxGuiObject* newHandler = NULL;
        for(int i = (childObjects.size()-1); i >= 0; i--) {
            ofxGuiPushObject(childObjects[i]);
            newHandler = childObjects[i]->_mousePressed(e, handled, numClicks);
            ofxGuiPopObject();
            // currently an event can only be handled by one item
            if(!handled && newHandler) {
                handled = newHandler;
            }
        }
    }
	
    
    bool didHit = hitTest(mousePosition);
    
	if(isMouseHandler() && canHandleIt(handled) && didHit) { 				
		if(!isMouseDown()) {				
			_isMouseDown = true;						 
			onPress();
            if(numClicks == 2 && pMousePosition == mousePosition) {
                onDoublePress();
            }
		}
		handled = this;					// set this as handled
	} else {							// if mouse is not over
		_isMouseDown = false;
		onPressOutside(); // someone else was pressed
	}

	return handled;
}

//--------------------------------------------------------------
ofxGuiObject* ofxGuiObject::_mouseReleased(ofMouseEventArgs &e, ofxGuiObject* handled) {

	if(!isEnabled() || isHidden()) return NULL;

	saveMouseEvent(e);
    
    if(propagateMouseEvents()) {
        ofxGuiObject* newHandler = NULL;
        for(int i = (childObjects.size()-1); i >= 0; i--) {
            ofxGuiPushObject(childObjects[i]);
            newHandler = childObjects[i]->_mouseReleased(e, handled);
            ofxGuiPopObject();
            // currently an event can only be handled by one item
            if(!handled && newHandler) {
                handled = newHandler;
            }
        }
    }	
    
	// hit test
	bool didHit = hitTest(mousePosition);
	
	if(isMouseHandler() && (isDragging() || didHit)) {		
		// this is either the object being dragged or an object being dropped upon
		
		if(isDragging()) {
			if(didHit) {
				onRelease();
			} else {
				onReleaseOutside();
			}
			
			handled = this;
            
		} else if(didHit && isDropReceiverForObject(handled)) {
			// are we a drop receiver? and is there valid drag object?
			onObjectDropReceived(handled); // note that we got it
			handled->onObjectDropSent(this); // note to the object that it was sent
		} else {
			// drop failed
			onRelease();
		}

	} else {
		onReleaseOutside();
	}
		
	
	// in any case, the mouse is no longer down
    _isDragging = false;
	_isMouseDown = false;
    _isMouseOver = isMouseHandler() && didHit;
	
	return handled;
}

//--------------------------------------------------------------
void ofxGuiObject::cancelDrag() {
	if(isDragging()) {
		_isDragging = false;
		onDragCancelled();
	}
}

//--------------------------------------------------------------
void ofxGuiObject::setIsDragMoveable(bool _val) {
    _isDragMoveable = _val;
}

//--------------------------------------------------------------
bool ofxGuiObject::isDragMoveable() {
    return _isDragMoveable;
}

//--------------------------------------------------------------
bool ofxGuiObject::isDragging() {
    return _isDragging;
}

//--------------------------------------------------------------
bool ofxGuiObject::isHitDragable() {
    return _isHitDragable;
}

//--------------------------------------------------------------
bool ofxGuiObject::isHitDragOrigin() {
    return _isHitDragOrigin;
}

//--------------------------------------------------------------
void ofxGuiObject::setIsFileDropReceiver(bool _val) {
    _isFileDropReceiver = _val;
}

//--------------------------------------------------------------
bool ofxGuiObject::isFileDropReceiver() {
    return _isFileDropReceiver;
}

//--------------------------------------------------------------
void ofxGuiObject::setIsDropSender(bool _val) {
    _isDropSender = _val;
}

//--------------------------------------------------------------
bool ofxGuiObject::isDropSender() {
    return _isDropSender;
}

//--------------------------------------------------------------
void ofxGuiObject::setIsDropReceiver(bool _val) {
    _isDropReceiver = _val;
}

//--------------------------------------------------------------
bool ofxGuiObject::isDropReceiver() {
    return _isDropReceiver;
}

//--------------------------------------------------------------
bool ofxGuiObject::isMouseDown() {
    return _isMouseDown;
}

//--------------------------------------------------------------
bool ofxGuiObject::isMouseOver() {
    return _isMouseOver;
}



//--------------------------------------------------------------
/*
void ofxGuiObject::releaseDrag() {
	
	if(isMouseDragging()) {
		_isMouseDragging = false;
		onDragReleased(x, y);
		preDragPosition = NULL; // get rid of the reference
	}
}
 */

//--------------------------------------------------------------

void ofxGuiObject::doSetEnabled(bool _enabled) {
	// tell all of the children (if any)
	for(int i = (childObjects.size()-1); i >= 0; i--) {
        ofxGuiPushObject(childObjects[i]);
		childObjects[i]->setEnabled(_enabled);
        ofxGuiPopObject();
	}
}



//--------------------------------------------------------------
int ofxGuiObject::saveObjectData() {
	/*
	int id	= props->mXml.addTag("OBJECT");
	
	props->mXml.setValue("OBJECT:ENABLED", isEnabled, id);
	props->mXml.setValue("OBJECT:TYPE", getTagName(), id);
	props->mXml.setValue("OBJECT:NAME", name, id);

	props->mXml.setValue("OBJECT:LEFT", mObjX, id);
	props->mXml.setValue("OBJECT:TOP", mObjY, id);
	//	props->mXml.setValue("OBJECT:WIDTH", mObjWidth, id);
	//	props->mXml.setValue("OBJECT:HEIGHT", mObjHeight, id);
	
	//	props->mXml.setValue("OBJECT:CTRX", mCtrX, id);
	//	props->mXml.setValue("OBJECT:CTRY", mCtrY, id);
	
	props->mXml.setValue("OBJECT:WIDTH", mCtrWidth, id);
	props->mXml.setValue("OBJECT:HEIGHT", mCtrHeight, id);
	
	props->mXml.setValue("OBJECT:MODE", mMode, id);
	props->mXml.setValue("OBJECT:DISPLAY", mDisplay, id);
	props->mXml.setValue("OBJECT:STEPS", mSteps, id);
	
	return id;
	 */
	return -1;
}


//--------------------------------------------------------------

// this can be overridden to provide more sophisticated drag/drop filtering
bool ofxGuiObject::isDropReceiverForObject(ofxGuiObject* dragObject) {
	return dragObject && isDropReceiver() && dragObject->isDropSender();
}

//--------------------------------------------------------------
void ofxGuiObject::saveMouseEvent(ofMouseEventArgs &e) {
    pMousePosition.x = mousePosition.x;
    pMousePosition.y = mousePosition.y;
	pMouseButton = mouseButton;

    mousePosition.x = e.x;
    mousePosition.y = e.y;
    mouseButton = e.button;
    
    deltaMousePosition = mousePosition - pMousePosition;
}

//--------------------------------------------------------------
void ofxGuiObject::saveKeyboardEvent(ofKeyEventArgs &e) {
    pKey = key;
	key = e.key;
}

//--------------------------------------------------------------
bool ofxGuiObject::hasParent() {
	return parent != NULL;
}


//--------------------------------------------------------------
ofVec2f ofxGuiObject::getBoxScreenPosition() {
	if(hasParent()) {
        // we always measure position from the parent's CONTENT box
		return parent->getBoxScreenPosition() + parent->getContentBoxOffset() +  getPosition();
	} else {
        // get the position w/ respect to the window
		return getPosition();
	}
}

//--------------------------------------------------------------
ofVec2f ofxGuiObject::getContentBoxScreenPosition() {
    return getBoxScreenPosition() + getContentBoxOffset();
}


//--------------------------------------------------------------
string ofxGuiObject::getDebugString() {
    ostringstream out;
	
    out << name << " ";
    out << "mX/mY: " << mousePosition << endl;  
    out << "dX/dY: " << deltaMousePosition << endl;
    out << "mouseOver: " << isMouseOver() << " mouseDown: " << isMouseDown() << " isDragging: " << isDragging() << endl;
    
    if(isDragging()) {
        out << dragStartPosition << endl;
        out << totalDragDelta << endl;
    }

	return out.str();
}


//--------------------------------------------------------------
void ofxGuiObject::setName(string _name) {
    name = _name;
}

//--------------------------------------------------------------
string ofxGuiObject::getName() {
    return name;
}

//--------------------------------------------------------------
string ofxGuiObject::getObjectType() {
    return objectType;
}

//--------------------------------------------------------------
void ofxGuiObject::setObjectType(string _objectType) {
    objectType = _objectType;
}

//--------------------------------------------------------------
void ofxGuiObject::setOrientation(ofOrientation _orientation) {
    orientation = _orientation;
    requestBoxLayout();
}

//--------------------------------------------------------------
ofOrientation ofxGuiObject::getOrientation() {
    return orientation;
}

//--------------------------------------------------------------
bool ofxGuiObject::isOrientationHorizontal() {
    switch(orientation) {
        case OF_ORIENTATION_UNKNOWN: // we'll just assume
        case OF_ORIENTATION_DEFAULT:	
        case OF_ORIENTATION_180:
            return true;
        case OF_ORIENTATION_90_RIGHT:
        case OF_ORIENTATION_90_LEFT:
            return false;
    }
}






//--------------------------------------------------------------
string ofxGuiObject::getTooltip() {
    return tooltip;
}

//--------------------------------------------------------------
void ofxGuiObject::setTooltip(string _tooltip) {
    tooltip = _tooltip;
}

//--------------------------------------------------------------
bool ofxGuiObject::isTooltipEnabled() {
    return tooltipEnabled;
}

//--------------------------------------------------------------
void ofxGuiObject::setTooltipEnabled(bool _enabled) {
    tooltipEnabled = _enabled;
}

//--------------------------------------------------------------
ofxGuiObject* ofxGuiObject::getParent() {
    return parent;
}

//--------------------------------------------------------------
void ofxGuiObject::setParent(ofxGuiObject* _parent) {
    parent = _parent;
}


//--------------------------------------------------------------
void ofxGuiObject::addChild(ofxGuiObject* child) {
    if(child->hasParent()) {
        ofLog(OF_LOG_WARNING, "ofxGuiObject::addChild() : child already has parent ... not advised.");
    }

    child->setParent(this);
    childObjects.push_back(child);
    requestBoxLayout();
}

//--------------------------------------------------------------
bool ofxGuiObject::isChild(ofxGuiObject* child) {
    
    // just double check
    if(this == child) return false;
    
    // TODO: this will short circuit, but perhaps there is a better structure
    // to hold all of these than a giant recursive tree ...
    for(int i = 0; i < childObjects.size(); i++) {
        // is this a child?  or is it a child of the child?
        if(child == childObjects[i] || childObjects[i]->isChild(child)) {
            return true;
        }        
    }
    
    return false;
}


//--------------------------------------------------------------
bool ofxGuiObject::hasChildren() {
    return !childObjects.empty();
}

//--------------------------------------------------------------
bool ofxGuiObject::removeChild(ofxGuiObject* child) {
    
    // iterator to vector element:
    childObjectsIter = find (childObjects.begin(), childObjects.end(), child);

    // TODO: should delete memory?
    // XXXXX DELETE MEMORY?
    if(childObjectsIter != childObjects.end()) {
        childObjects.erase(childObjectsIter);
        return true;
    } else {
        return false;
    }	
}

//--------------------------------------------------------------
void ofxGuiObject::drawBox() {
    ofColor boxColor = cBox.get(isMouseOver(),isMouseDown(),isEnabled(),alphaScale);
    if(boxColor.a > 0) {
        ofFill();
        ofSetColor(boxColor);
        ofxRect(0,0,getWidth(),getHeight());
    }
}

//--------------------------------------------------------------
void ofxGuiObject::drawBorder() {
    ofColor borderColor = cBorder.get(isMouseOver(),isMouseDown(),isEnabled(),alphaScale);
    if(borderColor.a > 0) {
        ofFill();
        ofSetColor(borderColor);
        ofxFrame(0,0,getBorderBoxWidth(),getBorderBoxHeight(),border);
    }
}

//--------------------------------------------------------------
void ofxGuiObject::drawPaddingBox() {
    ofColor paddingColor = cPadding.get(isMouseOver(),isMouseDown(),isEnabled(),alphaScale);
    if(paddingColor.a > 0) {
        ofFill();
        ofSetColor(paddingColor);
        ofxRect(0,0,getPaddingBoxWidth(),getPaddingBoxHeight());
    }
}

//--------------------------------------------------------------
void ofxGuiObject::drawContentBox() {
    ofColor contentColor = cContent.get(isMouseOver(),isMouseDown(),isEnabled(),alphaScale);
    if(contentColor.a > 0) {
        ofFill();
        ofSetColor(contentColor);
        ofxRect(0,0,getContentBoxWidth(),getContentBoxHeight());
    }
}

//--------------------------------------------------------------
void ofxGuiObject::drawShadowBox() {
    // DRAW THE SHADOW if alpha is set above 0
    if(doShadow) {
        ofColor shadowColor = cShadow.get(isMouseOver(),isMouseDown(),isEnabled(),alphaScale);
        if(shadowColor.a > 0) {
            ofPushMatrix();
            ofTranslate(shadowOffset);
            ofFill();
            ofSetColor(shadowColor);
            ofxRect(getBorderBox());
            ofPopMatrix();
        }
    }
}


//--------------------------------------------------------------
float ofxGuiObject::getAlphaScale() {
    return alphaScale;
}
//--------------------------------------------------------------
void ofxGuiObject::setAlphaScale(float _alphaScale) {
    alphaScale = _alphaScale;
}

//--------------------------------------------------------------
bool ofxGuiObject::getDoShadow() {
    return doShadow;
}
//--------------------------------------------------------------
void ofxGuiObject::setDoShadow(bool _doShadow) {
    doShadow = _doShadow;
}

//--------------------------------------------------------------
void ofxGuiObject::setKeyboardOnPress(bool _keyboardOnPress) {
    keyboardOnPress = _keyboardOnPress;
}

//--------------------------------------------------------------
bool ofxGuiObject::getKeyboardOnPress() {
    return keyboardOnPress;
}

//--------------------------------------------------------------
bool ofxGuiObject::isShiftPressed() {
    return ofGetModifierPressed(OF_KEY_SHIFT);
}

//--------------------------------------------------------------
bool ofxGuiObject::isCtrlPressed() {
    return ofGetModifierPressed(OF_KEY_CTRL);
}

//--------------------------------------------------------------
bool ofxGuiObject::isAltPressed() {
    return ofGetModifierPressed(OF_KEY_ALT);
}

//--------------------------------------------------------------
float ofxGuiObject::getActiveTimer() {
    return isActiveTimer;
}

//--------------------------------------------------------------
bool ofxGuiObject::canHandleIt(ofxGuiObject* handled) {
    // are we the handler already?  or has it been handled yet?
    return handled == this || !handled;
}


