/*  ofxMui.h
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
#pragma once

//--------------------------------------------------------------
#include "ofxMuiUtils.h"
#include "ofxMuiObject.h"
#include "ofxMuiTooltip.h"
#include "ofxMuiWindow.h"

#define ofxMui_VERSION			"1.0" //

class ofxMuiObject;


//--------------------------------------------------------------
class ofxMui : public ofxMuiEnabler, public ofxMuiKeyMapper {
	
public:
	
	ofxMui();      
    ofxMui(int w, int h);
	virtual ~ofxMui();
	
    // core oF event suite
	void    setup(ofEventArgs &e);
	void    update(ofEventArgs &e);
	void    draw(ofEventArgs &e);
	void    exit(ofEventArgs &e);
    void    windowResized(ofResizeEventArgs &e);
    void    fileDragEvent(ofDragInfo &e);
    void    gotMessage(ofMessage &e);
	
	void	keyPressed(ofKeyEventArgs &e);
	void	keyReleased(ofKeyEventArgs &e);
	void	mouseMoved(ofMouseEventArgs &e);
	void	mouseDragged(ofMouseEventArgs &e);
	void	mousePressed(ofMouseEventArgs &e);
	void	mouseReleased(ofMouseEventArgs &e);

	ofxMuiWindow*	addWindow(string name, int x, int y);
	bool			removePanel(ofxMuiPanel* panel);
    
	bool			buildFromXml(string file);
	void			saveToXml(string file);
    bool            mXmlDone;	

	vector			<ofxMuiObject*>				mObjects;
	vector			<ofxMuiObject*>::iterator	mObjectsIter;
	
    ofxMuiObject*   handled;   // is the current active object (mouse over)
	ofVec2f         dragPreviousPosition;
	
    // Panel layer operations
	void			bringToFront(int index);
	void			bringForward(int index);	
	void			sendToBack(int index);
	void			sendBackward(int index);
	
	ofxMuiTooltip   tooltip;
    
    ofxMuiObject*	addGuiObject(ofxMuiObject* obj);
	bool			removeGuiObject(ofxMuiObject* obj);

    ofFbo* getFboRef();
    
private:
	
    ofFbo fbo;

    void init();
    
    int mouseClickThreshold;
    int lastMouseClick;
    int numMouseClicks;
    
    bool isMousePressed;
    bool isMouseDragging;
    
    int width;
    int height;
    
};

//--------------------------------------------------------------

