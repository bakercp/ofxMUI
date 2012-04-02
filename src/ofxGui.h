/*  ofxGui.h
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
#include "ofxGuiUtils.h"
#include "ofxGuiObject.h"
#include "ofxGuiTooltip.h"
#include "ofxGuiWindow.h"

#define OFXGUI_VERSION			"1.0" //

class ofxGuiObject;


//--------------------------------------------------------------
class ofxGui : public ofxGuiEnabler, public ofxGuiKeyMapper {
	
public:
	
	ofxGui();      
    ofxGui(int w, int h);
	virtual ~ofxGui();
	
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

	ofxGuiWindow*	addWindow(string name, int x, int y);
	bool			removePanel(ofxGuiPanel* panel);
    
	bool			buildFromXml(string file);
	void			saveToXml(string file);
    bool            mXmlDone;	

	vector			<ofxGuiObject*>				mObjects;
	vector			<ofxGuiObject*>::iterator	mObjectsIter;
	
    ofxGuiObject*   handled;   // is the current active object (mouse over)
	ofVec2f         dragPreviousPosition;
	
    // Panel layer operations
	void			bringToFront(int index);
	void			bringForward(int index);	
	void			sendToBack(int index);
	void			sendBackward(int index);
	
	ofxGuiTooltip   tooltip;
    
    ofxGuiObject*	addGuiObject(ofxGuiObject* obj);
	bool			removeGuiObject(ofxGuiObject* obj);

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

