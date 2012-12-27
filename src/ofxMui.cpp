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

#include "ofxMui.h"


//--------------------------------------------------------------
ofxMui::ofxMui() : ofxMuiEnabler() {
    width = ofGetWidth();
    height = ofGetHeight();
    autoResize = true;
    init();
}

//--------------------------------------------------------------
ofxMui::ofxMui(int _w, int _h) : ofxMuiEnabler() {
    width = _w;
    height = _h;
    autoResize = false;
    init();
}

//--------------------------------------------------------------

ofxMui::~ofxMui() {
	ofRemoveListener(ofEvents().setup, this, &ofxMui::setup); // sets up any guis
	ofRemoveListener(ofEvents().update, this, &ofxMui::update);
	ofRemoveListener(ofEvents().draw, this, &ofxMui::draw);
    ofRemoveListener(ofEvents().exit, this, &ofxMui::exit);
    ofRemoveListener(ofEvents().windowResized, this, &ofxMui::windowResized);
    ofRemoveListener(ofEvents().fileDragEvent, this, &ofxMui::fileDragEvent);
    ofRemoveListener(ofEvents().messageEvent, this, &ofxMui::gotMessage);

	ofRemoveListener(ofEvents().keyPressed, this, &ofxMui::keyPressed);
	ofRemoveListener(ofEvents().keyReleased, this, &ofxMui::keyReleased);
	
    ofRemoveListener(ofEvents().mouseMoved, this, &ofxMui::mouseMoved);
	ofRemoveListener(ofEvents().mouseDragged, this, &ofxMui::mouseDragged);
	ofRemoveListener(ofEvents().mouseReleased, this, &ofxMui::mouseReleased);
	ofRemoveListener(ofEvents().mousePressed, this, &ofxMui::mousePressed);

    
//#ifdef defined(TARGET_OF_IPHONE) || defined(TARGET_ANDROID)
    ofRemoveListener(ofEvents().touchDown, this, &ofxMui::touchDown);
    ofRemoveListener(ofEvents().touchMoved, this, &ofxMui::touchMoved);
    ofRemoveListener(ofEvents().touchUp, this, &ofxMui::touchUp);
    ofRemoveListener(ofEvents().touchDoubleTap, this, &ofxMui::touchDoubleTap);
    ofRemoveListener(ofEvents().touchCancelled, this, &ofxMui::touchCancelled);
//#ifdef
    for(int i = 0; i < mObjects.size(); i++) {
        delete mObjects[i];   
    }
    mObjects.clear();
    
    //delete fbo;
}

//--------------------------------------------------------------
void ofxMui::init() {
    ofAddListener(ofEvents().setup, this, &ofxMui::setup); // sets up any guis
	ofAddListener(ofEvents().update, this, &ofxMui::update);
	ofAddListener(ofEvents().draw, this, &ofxMui::draw);
	ofAddListener(ofEvents().exit, this, &ofxMui::exit);
    ofAddListener(ofEvents().windowResized, this, &ofxMui::windowResized);
    ofAddListener(ofEvents().fileDragEvent, this, &ofxMui::fileDragEvent);
    ofAddListener(ofEvents().messageEvent, this, &ofxMui::gotMessage);
    
	ofAddListener(ofEvents().keyPressed, this, &ofxMui::keyPressed);
	ofAddListener(ofEvents().keyReleased, this, &ofxMui::keyReleased);
    
	ofAddListener(ofEvents().mouseMoved, this, &ofxMui::mouseMoved);
	ofAddListener(ofEvents().mouseDragged, this, &ofxMui::mouseDragged);
	ofAddListener(ofEvents().mouseReleased, this, &ofxMui::mouseReleased);
	ofAddListener(ofEvents().mousePressed, this, &ofxMui::mousePressed);
    
    ofAddListener(ofEvents().touchDown, this, &ofxMui::touchDown);
    ofAddListener(ofEvents().touchMoved, this, &ofxMui::touchMoved);
    ofAddListener(ofEvents().touchUp, this, &ofxMui::touchUp);
    ofAddListener(ofEvents().touchDoubleTap, this, &ofxMui::touchDoubleTap);
    ofAddListener(ofEvents().touchCancelled, this, &ofxMui::touchCancelled);
    
	mXmlDone			= true;
	
	// dragging
	//dragPreviousPosition = ofVec2f(-FLT_MAX, -FLT_MAX); // the last poistion in the drag world
    
    //tooltip.setText("tooltip!");
    
    handled = NULL;
    
    isMousePressed = false;
    isMouseDragging = false;
    
    mouseClickThreshold = 300; // num ms for a double-click
    lastMouseClick = INT_MIN;
    numMouseClicks = 0;
    
    // prepare the fbo for
    fbo.allocate(width, height);

    autoResize = true;
}

//--------------------------------------------------------------
void ofxMui::setup(ofEventArgs &e) {
	if(isEnabled()) {
		for(int i = 0; i < mObjects.size(); i++) {
            ofxMuiPushObject(mObjects[i]);
            mObjects[i]->_setup(e);
            ofxMuiPopObject();
		}
	}
}

//--------------------------------------------------------------
void ofxMui::update(ofEventArgs &e) {
	if(isEnabled()) {
		for(int i = 0; i < mObjects.size(); i++) {
            ofxMuiPushObject(mObjects[i]);
			mObjects[i]->_update(e);
            ofxMuiPopObject();
		}
	}

    //tooltip._update(e);
}

//--------------------------------------------------------------
void ofxMui::draw(ofEventArgs &e) {  
    fbo.begin();
    {
        ofPushStyle();
        ofBackground(0,0);
        if(isEnabled()) {
            ofEnableAlphaBlending();
            // draw from the back forward
            for(int i = 0; i < mObjects.size(); i++) {
                ofxMuiPushObject(mObjects[i]);
                mObjects[i]->_draw(e);
                ofxMuiPopObject();
            }
            //tooltip._draw(e);
            ofDisableAlphaBlending();
        }
        ofPopStyle();
    }
    fbo.end();
    
    ofEnableAlphaBlending();
    fbo.draw(0,0);
    ofDisableAlphaBlending();
    
}

//--------------------------------------------------------------
void ofxMui::exit(ofEventArgs &e) {
	if(isEnabled()) {
		for(int i = 0; i < mObjects.size(); i++) {
            ofxMuiPushObject(mObjects[i]);
			mObjects[i]->_exit(e);
            ofxMuiPopObject();
		}
	}
}

//--------------------------------------------------------------
void ofxMui::windowResized(ofResizeEventArgs &e) {
    
    if(autoResize) {
        width = e.width;
        height = e.height;
        
        if(e.width != fbo.getWidth() || e.height != fbo.getHeight()) {
            fbo.allocate(e.width, e.height);
        }
    }
    
 	if(isEnabled()) {
		for(int i = 0; i < mObjects.size(); i++) {
            ofxMuiPushObject(mObjects[i]);
			mObjects[i]->_windowResized(e);
            ofxMuiPopObject();
		}
	}
}

//--------------------------------------------------------------
void ofxMui::fileDragEvent(ofDragInfo &e) {

 	if(isEnabled()) {
        ofxMuiObject* localHandle = NULL;
		for(int i = 0; i < mObjects.size(); i++) {
            ofxMuiPushObject(mObjects[i]);
			localHandle = mObjects[i]->_fileDragEvent(e,localHandle);
            ofxMuiPopObject();
		}
	}
}

//--------------------------------------------------------------
void ofxMui::gotMessage(ofMessage &e) {
 	if(isEnabled()) {
		for(int i = 0; i < mObjects.size(); i++) {
            ofxMuiPushObject(mObjects[i]);
			mObjects[i]->_gotMessage(e);
            ofxMuiPopObject();
		}
	}
}


//--------------------------------------------------------------
void ofxMui::keyPressed(ofKeyEventArgs &e) {
    // TODO: based on focus!!

	if(isEnabled()) {
        ofxMuiObject* localHandle = NULL;
		for(int i = (mObjects.size()-1); i >= 0; i--) {
            ofxMuiPushObject(mObjects[i]);
			localHandle = mObjects[i]->_keyPressed(e, localHandle);
            ofxMuiPopObject();
		}
	}
}

//--------------------------------------------------------------
void ofxMui::keyReleased(ofKeyEventArgs &e) {	
    // TODO: ased on focus!!
	if(isEnabled()) {
        ofxMuiObject* localHandle = NULL;
		for(int i = (mObjects.size()-1); i >= 0; i--) {
            ofxMuiPushObject(mObjects[i]);
			localHandle = mObjects[i]->_keyReleased(e, localHandle);
            ofxMuiPopObject();
		}
	}
}

//--------------------------------------------------------------
void ofxMui::mouseMoved(ofMouseEventArgs &e) {

    
    if(isEnabled()) {
        ofxMuiObject* localHandle = NULL;
		for(int i = (mObjects.size()-1); i >= 0; i--) {
            ofxMuiPushObject(mObjects[i]);
			localHandle = mObjects[i]->_mouseMoved(e, localHandle);
            ofxMuiPopObject();
		}
		
        //tooltip.setObject(handled, e);
    
    }
	
    //tooltip.setObject(NULL, args.x, args.y);

}

//--------------------------------------------------------------
void ofxMui::mouseDragged(ofMouseEventArgs &e) {
    
    isMouseDragging = true;
    
    //tooltip.setObject(NULL, e);
    //tooltip.cancel();

    
	if(isEnabled()) {
		ofxMuiObject* newHandler = NULL;
		
		for(int i = (mObjects.size()-1); i >= 0; i--) {
            ofxMuiPushObject(mObjects[i]);
			newHandler = mObjects[i]->_mouseDragged(e, handled);
            ofxMuiPopObject();
			if(!handled && newHandler) {
				handled = newHandler;
			}
		}
	}
}

//--------------------------------------------------------------
void ofxMui::mousePressed(ofMouseEventArgs &e) {
    
    int now = ofGetElapsedTimeMillis();
    
    if( (now - lastMouseClick) < mouseClickThreshold ) {
        numMouseClicks++;
    } else {
        numMouseClicks = 1;
    }
    
    lastMouseClick = now;
    
    isMousePressed = true;
    handled = NULL; // must be unhadled

    //tooltip.setObject(NULL, e);
    //tooltip.cancel();

    if(isEnabled()) {
		ofxMuiObject* newHandler = NULL;
		for(int i = (mObjects.size()-1); i >= 0; i--) {
            ofxMuiPushObject(mObjects[i]);
			newHandler = mObjects[i]->_mousePressed(e, handled, numMouseClicks);
            ofxMuiPopObject();
			if(!handled && newHandler) {
				handled = newHandler;
				bringToFront(i);
			}
            
		}
	}
}

//--------------------------------------------------------------
void ofxMui::mouseReleased(ofMouseEventArgs &e) {

    isMousePressed = false;
    isMouseDragging = false;
    
    if(isEnabled()) {
		ofxMuiObject* newHandler = NULL;
		
		for(int i = (mObjects.size()-1); i >= 0; i--) {
            ofxMuiPushObject(mObjects[i]);
			newHandler = mObjects[i]->_mouseReleased(e, handled);
            ofxMuiPopObject();
			if(!handled && newHandler) {
				handled = newHandler;
			}
		}
        
        
        //tooltip.setObject(handled, e);

	}

    handled = NULL;
	
}

//--------------------------------------------------------------
void ofxMui::touchDown(ofTouchEventArgs & touch) {
    cout << "down" << endl;
}

//--------------------------------------------------------------
void ofxMui::touchMoved(ofTouchEventArgs& touch) {
    cout << "move" << endl;
}
//--------------------------------------------------------------

void ofxMui::touchUp(ofTouchEventArgs& touch) {
    cout << "up" << endl;
}

//--------------------------------------------------------------
void ofxMui::touchDoubleTap(ofTouchEventArgs& touch) {
    cout << "double tap" << endl;
}

//--------------------------------------------------------------
void ofxMui::touchCancelled(ofTouchEventArgs& touch) {
    cout << "cancel" << endl;
}


//--------------------------------------------------------------
void ofxMui::bringToFront(int index)  {
	if(index >= 0 && index < mObjects.size()) {
		if(index < (mObjects.size() - 1)) {
			// keep going until you are at the front
			for(int i = index; i < mObjects.size(); ++i) {
				bringForward(i);
            }
		} else {
			ofLog(OF_LOG_VERBOSE, "Already at the front.");
		}
	} else {
		ofLog(OF_LOG_ERROR, "Index out of range.");
	}
}

//--------------------------------------------------------------
void ofxMui::bringForward(int index) {
	if(index >= 0 && index < mObjects.size()) {
		if(index < (mObjects.size() - 1)) {
			swap(mObjects[index], mObjects[index+1]);
		} else {
			ofLogVerbose("ofxMui") << "Already at the front.";
		}
	} else {
		ofLog(OF_LOG_ERROR, "Index out of range.");
	}	
}

//--------------------------------------------------------------
void ofxMui::sendToBack(int index) {
	if(index >= 0 && index < mObjects.size()) {
		if(index != 0) {
			for(int i = index; i >= 0; --i) {
				sendBackward(i);
            }
		} else {
			ofLog(OF_LOG_VERBOSE, "ofxMui: Object already at the back.");
		}
	} else {
		ofLog(OF_LOG_ERROR, "ofxMui: Index out of range.");
	}
}

//--------------------------------------------------------------
void ofxMui::sendBackward(int index) {
	if(index >= 0 && index < mObjects.size()) {
		if(index != 0) {
			swap(mObjects[index], mObjects[index-1]);
		} else {
			ofLog(OF_LOG_VERBOSE, "ofxMui: Object already at the back.");
		}
	} else {
		ofLog(OF_LOG_ERROR, "ofxMui: Index out of range.");
	}
}


//--------------------------------------------------------------
ofxMuiObject* ofxMui::addGuiObject(ofxMuiObject* obj) {
    // no parent set
    // TODO: will set up here if it becomes a gui object ... 
	mObjects.push_back(obj);
	return obj;
}

//--------------------------------------------------------------
bool ofxMui::removeGuiObject(ofxMuiObject* obj) {
	// iterator to vector element:
	mObjectsIter = find (mObjects.begin(), mObjects.end(), obj);

	if(mObjectsIter != mObjects.end()) {
		mObjects.erase(mObjectsIter);
		return true;
	} else {
		return false;
	}	
}


//--------------------------------------------------------------
ofxMuiWindow* ofxMui::addWindow(string name, int x, int y)
{
	ofxMuiWindow* newPanel = new ofxMuiWindow(name, x, y);
	addGuiObject(newPanel);
	return newPanel;
}

//--------------------------------------------------------------
bool ofxMui::removePanel(ofxMuiPanel* panel)
{
	return removeGuiObject(panel);
}


//--------------------------------------------------------------
bool ofxMui::buildFromXml(string file) {
    
    /*
	if(!mXmlDone)
		return false;
	
	if(!props->mXml.loadFile(file))
		return false;
	
	int numberOfTags = props->mXml.getNumTags("UI");
	
	if(numberOfTags != 1)
		return false;
	
	mObjects.clear();
	
	mXmlDone			= false;
	props->mXmlfile	= file;
	
	props->mXml.pushTag("UI", 0);

	isEnabled()	= props->mXml.getValue("ISACTIVE", 0);

	props->loadFromXml(ofxXmlSettings& xml);
	
	numberOfTags = props->mXml.getNumTags("OBJECT");
	
	if(numberOfTags > 0)
	{
		for(int i = 0; i < numberOfTags; i++)
		{
			props->mXml.pushTag("OBJECT", i);
			
			int		id		= props->mXml.getValue("ID", 0);
			string	type	= props->mXml.getValue("TYPE", "");
			string	name	= props->mXml.getValue("NAME", "");
			int		x		= props->mXml.getValue("LEFT", 0);
			int		y		= props->mXml.getValue("TOP", 0);
			int		border	= props->mXml.getValue("BORDER", 0);
			int		spacing	= props->mXml.getValue("SPACING", 0);
			
			if(type == "PANEL")
			{
				ofxMuiPanel* panel = addPanel(name, x, y, border, spacing);
				panel->loadFromXml(ofxXmlSettings& xml);
			}
			
			props->mXml.popTag();
		}
	}
	
	props->mXml.popTag();
	
	mXmlDone = true;
	*/
	return true;
}

//--------------------------------------------------------------
void ofxMui::saveToXml(string file) {
    /*
	if(!mXmlDone)
		return;

	mXmlDone = false;

	props->mXml.clear();
		
	int id = props->mXml.addTag("UI");
	
	props->mXml.setValue("UI:VERSION", ofxMui_VERSION, id);

	props->mXml.setValue("UI:ISACTIVE", isEnabled(), id);
		
	props->mXml.pushTag("UI", id);

	props->saveToXml(ofxXmlSettings& xml);

	ofxMuiObject* tmpObj;

	for(int i = 0; i < mObjects.size(); i++)
	{
		tmpObj = (ofxMuiObject*)mObjects.at(i);
		tmpObj->saveToXml(ofxXmlSettings& xml);
	}
	
	props->mXml.popTag();
	props->mXml.saveFile(file);

	mXmlDone = true;
    */
}

//--------------------------------------------------------------

