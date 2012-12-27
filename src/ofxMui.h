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

#include <set>

//--------------------------------------------------------------
#include "ofxMuiUtils.h"
#include "ofxMuiObject.h"
#include "ofxMuiTouch.h"
//#include "ofxMuiTooltip.h"
#include "ofxMuiWindow.h"


#define ofxMui_VERSION			"1.0" //

class ofxMuiObject;


//--------------------------------------------------------------
class ofxMui : public ofxMuiEnabler, public ofxMuiKeyMapper {
	
public:
    
	
	ofxMui();      
    ofxMui(int w, int h); // auto resize
	virtual ~ofxMui();
	
    // core oF event suite
	void    setup(ofEventArgs &e);
	void    update(ofEventArgs &e);
	void    draw(ofEventArgs &e);
	void    exit(ofEventArgs &e);
    void    windowResized(ofResizeEventArgs &e);
    void    fileDragEvent(ofDragInfo &e);
    void    gotMessage(ofMessage &e);
	
    // input events
	void	keyPressed(ofKeyEventArgs &e);
	void	keyReleased(ofKeyEventArgs &e);

	void	mouseMoved(ofMouseEventArgs &e);
	void	mouseDragged(ofMouseEventArgs &e);
	void	mousePressed(ofMouseEventArgs &e);
	void	mouseReleased(ofMouseEventArgs &e);
    
    void    touchDown(ofTouchEventArgs & touch);
    void    touchMoved(ofTouchEventArgs& touch);
	void    touchUp(ofTouchEventArgs& touch);
	void    touchDoubleTap(ofTouchEventArgs& touch);
	void    touchCancelled(ofTouchEventArgs& touch);

    
    
    
    
    
    
    
    /// TODO: ALL OF THE BABOVE MOUSE FUNCTIONS SHOULD BE FUNNELED INTO THE TOUCH HANDLERS

	ofxMuiWindow*	addWindow(string name, int x, int y);
	bool			removePanel(ofxMuiPanel* panel);
    
	bool			buildFromXml(string file);
	void			saveToXml(string file);
    bool            mXmlDone;	

	vector			<ofxMuiObject*>				mObjects;
	vector			<ofxMuiObject*>::iterator	mObjectsIter;
	
    
    vector          <ofxMuiObject*>             selectedMObjects;

    
    ofxMuiObject*   handled;   // is the current active object (mouse over)
    
    //set<ofxMuiObject*> handled; // for multi-touch
    
	//ofVec2f         dragPreviousPosition;
	
    // Panel layer operations
	void			bringToFront(int index);
	void			bringForward(int index);	
	void			sendToBack(int index);
	void			sendBackward(int index);
	
	//ofxMuiTooltip   tooltip;
    
    ofxMuiObject*	addGuiObject(ofxMuiObject* obj);
	bool			removeGuiObject(ofxMuiObject* obj);

    //ofFbo& getFboRef();
    
    
    map<int,ofxMuiTouch> activeTouches;
    
private:
	
    ofFbo fbo;

    void init();
    
    int mouseClickThreshold;
    int lastMouseClick;
    int numMouseClicks;
    
    bool isMousePressed;
    bool isMouseDragging;
    
    bool autoResize;
    int width;
    int height;
    
};

//--------------------------------------------------------------

typedef ofPtr<ofxMui> ofxSharedMui;
