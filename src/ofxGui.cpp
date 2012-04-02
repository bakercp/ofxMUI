/*  ofxGui.cpp
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

#include "ofxGui.h"


//--------------------------------------------------------------
ofxGui::ofxGui() : ofxGuiEnabler() {
    width = ofGetWidth();
    height = ofGetHeight();
    init();


}

//--------------------------------------------------------------
ofxGui::ofxGui(int _w, int _h) : ofxGuiEnabler() {
    width = _w;
    height = _h;
    init();
}

//--------------------------------------------------------------

ofxGui::~ofxGui() {
	ofRemoveListener(ofEvents().setup, this, &ofxGui::setup); // sets up any guis
	ofRemoveListener(ofEvents().update, this, &ofxGui::update);
	ofRemoveListener(ofEvents().draw, this, &ofxGui::draw);
    ofRemoveListener(ofEvents().exit, this, &ofxGui::exit);
    ofRemoveListener(ofEvents().windowResized, this, &ofxGui::windowResized);
    ofRemoveListener(ofEvents().fileDragEvent, this, &ofxGui::fileDragEvent);
    ofRemoveListener(ofEvents().messageEvent, this, &ofxGui::gotMessage);

	ofRemoveListener(ofEvents().keyPressed, this, &ofxGui::keyPressed);
	ofRemoveListener(ofEvents().keyReleased, this, &ofxGui::keyReleased);
	
    ofRemoveListener(ofEvents().mouseMoved, this, &ofxGui::mouseMoved);
	ofRemoveListener(ofEvents().mouseDragged, this, &ofxGui::mouseDragged);
	ofRemoveListener(ofEvents().mouseReleased, this, &ofxGui::mouseReleased);
	ofRemoveListener(ofEvents().mousePressed, this, &ofxGui::mousePressed);
	
    for(int i = 0; i < mObjects.size(); i++) {
        delete mObjects[i];   
    }
    mObjects.clear();
    
    //delete fbo;
}

//--------------------------------------------------------------
void ofxGui::init() {
    ofAddListener(ofEvents().setup, this, &ofxGui::setup); // sets up any guis
	ofAddListener(ofEvents().update, this, &ofxGui::update);
	ofAddListener(ofEvents().draw, this, &ofxGui::draw);
	ofAddListener(ofEvents().exit, this, &ofxGui::exit);
    ofAddListener(ofEvents().windowResized, this, &ofxGui::windowResized);
    ofAddListener(ofEvents().fileDragEvent, this, &ofxGui::fileDragEvent);
    ofAddListener(ofEvents().messageEvent, this, &ofxGui::gotMessage);
    
	ofAddListener(ofEvents().keyPressed, this, &ofxGui::keyPressed);
	ofAddListener(ofEvents().keyReleased, this, &ofxGui::keyReleased);
    
	ofAddListener(ofEvents().mouseMoved, this, &ofxGui::mouseMoved);
	ofAddListener(ofEvents().mouseDragged, this, &ofxGui::mouseDragged);
	ofAddListener(ofEvents().mouseReleased, this, &ofxGui::mouseReleased);
	ofAddListener(ofEvents().mousePressed, this, &ofxGui::mousePressed);
    
	mXmlDone			= true;
	
	// dragging
	dragPreviousPosition = ofVec2f(-FLT_MAX, -FLT_MAX); // the last poistion in the drag world
    
    tooltip.setText("tooltip!");
    
    handled = NULL;
    
    isMousePressed = false;
    isMouseDragging = false;
    
    mouseClickThreshold = 300; // num ms for a double-click
    lastMouseClick = INT_MIN;
    numMouseClicks = 0;
    
    // prepare the fbo for
    fbo.allocate(width, height);
}

//--------------------------------------------------------------
void ofxGui::setup(ofEventArgs &e) {
	if(isEnabled()) {
		for(int i = 0; i < mObjects.size(); i++) {
            ofxGuiPushObject(mObjects[i]);
            mObjects[i]->_setup(e);
            ofxGuiPopObject();
		}
	}
}

//--------------------------------------------------------------
void ofxGui::update(ofEventArgs &e) {
	if(isEnabled()) {
		for(int i = 0; i < mObjects.size(); i++) {
            ofxGuiPushObject(mObjects[i]);
			mObjects[i]->_update(e);
            ofxGuiPopObject();
		}
	}

    tooltip._update(e);
}

//--------------------------------------------------------------
void ofxGui::draw(ofEventArgs &e)
{  
    fbo.begin();
    {
        ofPushStyle();
        ofBackground(0,0);
        if(isEnabled()) {
            ofEnableAlphaBlending();
            // draw from the back forward
            for(int i = 0; i < mObjects.size(); i++) {
                ofxGuiPushObject(mObjects[i]);
                mObjects[i]->_draw(e);
                ofxGuiPopObject();
            }
            tooltip._draw(e);
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
void ofxGui::exit(ofEventArgs &e)
{
	if(isEnabled()) {
		for(int i = 0; i < mObjects.size(); i++) {
            ofxGuiPushObject(mObjects[i]);
			mObjects[i]->_exit(e);
            ofxGuiPopObject();
		}
	}
}

//--------------------------------------------------------------
void ofxGui::windowResized(ofResizeEventArgs &e)
{
 	if(isEnabled()) {
		for(int i = 0; i < mObjects.size(); i++) {
            ofxGuiPushObject(mObjects[i]);
			mObjects[i]->_windowResized(e);
            ofxGuiPopObject();
		}
	}
}


//--------------------------------------------------------------
void ofxGui::fileDragEvent(ofDragInfo &e) {

 	if(isEnabled()) {
        ofxGuiObject* localHandle = NULL;
		for(int i = 0; i < mObjects.size(); i++) {
            ofxGuiPushObject(mObjects[i]);
			localHandle = mObjects[i]->_fileDragEvent(e,localHandle);
            ofxGuiPopObject();
		}
	}
}

//--------------------------------------------------------------
void ofxGui::gotMessage(ofMessage &e) {
 	if(isEnabled()) {
		for(int i = 0; i < mObjects.size(); i++) {
            ofxGuiPushObject(mObjects[i]);
			mObjects[i]->_gotMessage(e);
            ofxGuiPopObject();
		}
	}
}


//--------------------------------------------------------------
void ofxGui::keyPressed(ofKeyEventArgs &e) {
    // TODO: based on focus!!

	if(isEnabled()) {
        ofxGuiObject* localHandle = NULL;
		for(int i = (mObjects.size()-1); i >= 0; i--) {
            ofxGuiPushObject(mObjects[i]);
			localHandle = mObjects[i]->_keyPressed(e, localHandle);
            ofxGuiPopObject();
		}
	}
}

//--------------------------------------------------------------
void ofxGui::keyReleased(ofKeyEventArgs &e) {	
    // TODO: ased on focus!!
	if(isEnabled()) {
        ofxGuiObject* localHandle = NULL;
		for(int i = (mObjects.size()-1); i >= 0; i--) {
            ofxGuiPushObject(mObjects[i]);
			localHandle = mObjects[i]->_keyReleased(e, localHandle);
            ofxGuiPopObject();
		}
	}
}
//--------------------------------------------------------------
void ofxGui::mouseMoved(ofMouseEventArgs &e) {

    
    if(isEnabled()) {
        ofxGuiObject* localHandle = NULL;
		for(int i = (mObjects.size()-1); i >= 0; i--) {
            ofxGuiPushObject(mObjects[i]);
			localHandle = mObjects[i]->_mouseMoved(e, localHandle);
            ofxGuiPopObject();
		}
		
        tooltip.setObject(handled, e);
    
    }
	
    //tooltip.setObject(NULL, args.x, args.y);

}

//--------------------------------------------------------------
void ofxGui::mouseDragged(ofMouseEventArgs &e) {
    
    isMouseDragging = true;
    
    tooltip.setObject(NULL, e);
    tooltip.cancel();

    
	if(isEnabled()) {
		ofxGuiObject* newHandler = NULL;
		
		for(int i = (mObjects.size()-1); i >= 0; i--) {
            ofxGuiPushObject(mObjects[i]);
			newHandler = mObjects[i]->_mouseDragged(e, handled);
            ofxGuiPopObject();
			if(!handled && newHandler) {
				handled = newHandler;
			}
		}
	}
}

//--------------------------------------------------------------
void ofxGui::mousePressed(ofMouseEventArgs &e) {
    
    int now = ofGetElapsedTimeMillis();
    
    if( (now - lastMouseClick) < mouseClickThreshold ) {
        numMouseClicks++;
    } else {
        numMouseClicks = 1;
    }
    
    lastMouseClick = now;
    
    isMousePressed = true;
    handled = NULL; // must be unhadled

    tooltip.setObject(NULL, e);
    tooltip.cancel();

    if(isEnabled()) {
		ofxGuiObject* newHandler = NULL;
		for(int i = (mObjects.size()-1); i >= 0; i--) {
            ofxGuiPushObject(mObjects[i]);
			newHandler = mObjects[i]->_mousePressed(e, handled, numMouseClicks);
            ofxGuiPopObject();
			if(!handled && newHandler) {
				handled = newHandler;
				bringToFront(i);
			}
            
		}
	}
}

//--------------------------------------------------------------
void ofxGui::mouseReleased(ofMouseEventArgs &e) {

    isMousePressed = false;
    isMouseDragging = false;
    
    if(isEnabled()) {
		ofxGuiObject* newHandler = NULL;
		
		for(int i = (mObjects.size()-1); i >= 0; i--) {
            ofxGuiPushObject(mObjects[i]);
			newHandler = mObjects[i]->_mouseReleased(e, handled);
            ofxGuiPopObject();
			if(!handled && newHandler) {
				handled = newHandler;
			}
		}
        
        
        tooltip.setObject(handled, e);

	}

    handled = NULL;
	
}

//--------------------------------------------------------------
void ofxGui::bringToFront(int index)  {
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
void ofxGui::bringForward(int index) {
	if(index >= 0 && index < mObjects.size()) {
		if(index < (mObjects.size() - 1)) {
			swap(mObjects[index], mObjects[index+1]);
		} else {
			ofLog(OF_LOG_VERBOSE, "Already at the front.");
		}
	} else {
		ofLog(OF_LOG_ERROR, "Index out of range.");
	}	
}

//--------------------------------------------------------------
void ofxGui::sendToBack(int index) {
	if(index >= 0 && index < mObjects.size()) {
		if(index != 0) {
			for(int i = index; i >= 0; --i) {
				sendBackward(i);
            }
		} else {
			ofLog(OF_LOG_VERBOSE, "ofxGui: Object already at the back.");
		}
	} else {
		ofLog(OF_LOG_ERROR, "ofxGui: Index out of range.");
	}
}

//--------------------------------------------------------------
void ofxGui::sendBackward(int index) {
	if(index >= 0 && index < mObjects.size()) {
		if(index != 0) {
			swap(mObjects[index], mObjects[index-1]);
		} else {
			ofLog(OF_LOG_VERBOSE, "ofxGui: Object already at the back.");
		}
	} else {
		ofLog(OF_LOG_ERROR, "ofxGui: Index out of range.");
	}
}


//--------------------------------------------------------------
ofxGuiObject* ofxGui::addGuiObject(ofxGuiObject* obj) {
    // no parent set
    // TODO: will set up here if it becomes a gui object ... 
	mObjects.push_back(obj);
	return obj;
}

//--------------------------------------------------------------
bool ofxGui::removeGuiObject(ofxGuiObject* obj) {
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
ofxGuiWindow* ofxGui::addWindow(string name, int x, int y)
{
	ofxGuiWindow* newPanel = new ofxGuiWindow(name, x, y);
	addGuiObject(newPanel);
	return newPanel;
}

//--------------------------------------------------------------
bool ofxGui::removePanel(ofxGuiPanel* panel)
{
	return removeGuiObject(panel);
}


//--------------------------------------------------------------
bool ofxGui::buildFromXml(string file) {
    
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

	props->buildFromXml();
	
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
				ofxGuiPanel* panel = addPanel(name, x, y, border, spacing);
				panel->buildFromXml();
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
void ofxGui::saveToXml(string file) {
    /*
	if(!mXmlDone)
		return;

	mXmlDone = false;

	props->mXml.clear();
		
	int id = props->mXml.addTag("UI");
	
	props->mXml.setValue("UI:VERSION", OFXGUI_VERSION, id);

	props->mXml.setValue("UI:ISACTIVE", isEnabled(), id);
		
	props->mXml.pushTag("UI", id);

	props->saveToXml();

	ofxGuiObject* tmpObj;

	for(int i = 0; i < mObjects.size(); i++)
	{
		tmpObj = (ofxGuiObject*)mObjects.at(i);
		tmpObj->saveToXml();
	}
	
	props->mXml.popTag();
	props->mXml.saveFile(file);

	mXmlDone = true;
    */
}

//--------------------------------------------------------------

