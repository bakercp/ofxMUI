//
//  ofxMuiEnabler.h
//  emptyExample
//
//  Created by Christopher Baker on 7/10/11.
//  Copyright 2011 Kitchen Budapest. All rights reserved.
//

#pragma once

#include "ofMain.h"

class ofxMuiEnabler {
	
public:

	ofxMuiEnabler();
    ofxMuiEnabler(bool _enabled);
    virtual ~ofxMuiEnabler();
	
    //--------------------------------------------------------------
    // ENABLING ////////////////////////////////////////////////////
    //--------------------------------------------------------------
    // this is a general use state.  this is the base state.  if the
    // subclass is not enabled, then very little will be propagated.
    
    bool isEnabled() const;
    void enable();
    void disable();
    void toggleEnabled();
	void setEnabled(bool _enabled);

    //--------------------------------------------------------------
    // LOCKING /////////////////////////////////////////////////////
    //--------------------------------------------------------------
    // locking is a special case.  some variables (like setting 
    // values) respect a locked state.  e.g. when a button is locked
    // it cannot be modified
    
    bool isLocked() const;
    void setLocked(bool _locked);
    
    //--------------------------------------------------------------
    // HIDDEN //////////////////////////////////////////////////////
    //--------------------------------------------------------------
    // this is primarily set and unset by parent objects that 
    // minimize (i.e. panels);
    
    bool isHidden() const;
    void setHidden(bool _hidden);
    void show();
    void hide();
    
    //--------------------------------------------------------------
    // SETUP ///////////////////////////////////////////////////////
    //--------------------------------------------------------------
    // this allows a special case when the object should not be 
    // setup for some reason.
    
    bool isSetupHandler() const;
    void setIsSetupHandler(bool _isSetup);
    
    bool propagateSetupEvents();
    void setPropagateSetupEvents(bool _propagateSetupEvents);
    
    //--------------------------------------------------------------
    // RENDERING ///////////////////////////////////////////////////
    //--------------------------------------------------------------
    // this allows a special case when the object should not be 
    // rendered for some reason.
    
    bool isDrawHandler() const;
    void setIsDrawHandler(bool _isDrawing);
    
    bool propagateDrawEvents();
    void setPropagateDrawEvents(bool _propagateDrawEvents);
    
    //--------------------------------------------------------------
    // UPDATING ////////////////////////////////////////////////////
    //--------------------------------------------------------------
    // this allows a special case when the object should not be 
    // rendered for some reason.
    
    bool isUpdateHandler() const;
    void setIsUpdateHandler(bool _isUpdating);
    
    bool propagateUpdateEvents();
    void setPropagateUpdateEvents(bool _propagateUpdates);
    
    
    //--------------------------------------------------------------
    // INPUT EVENT HANDLING ////////////////////////////////////////
    //--------------------------------------------------------------
    
    bool isMouseHandler() const;
    void setIsMouseHandler(bool _isMouseHandler);
    
    bool isKeyboardHandler();
    void setIsKeyboardHandler(bool _isKeyboardHandler);
    
    
    // propagation
    
    bool propagateMouseEvents();
    void setPropagateMouseEvents(bool _propagateMouse);

    bool propagateKeyboardEvents();
    void setPropagateKeyboardEvents(bool _propagateKeyboard);

    // utility 
    void setPropagatePeripheralEvents(bool _propagatePeripheralInput);
    
    //--------------------------------------------------------------
    // OTHER EVENT HANDLING ////////////////////////////////////////
    //--------------------------------------------------------------
    
    bool isMessageHandler() const;
    void setIsMessageHandler(bool _val);

    bool isFileDragHandler() const;
    void setIsFileDragHandler(bool _val);
    
    bool isWindowResizedHandler() const;
    void setIsWindowResizedHandler(bool _val);

    
    // propagation
    bool propagateMessageEvents();
    void setPropagateMessageEvents(bool _val);

    bool propagateFileDragEvents();
    void setPropagateFileDragEvents(bool _val);

    bool propagateWindowResizedEvents();
    void setPropagateWindowResizedEvents(bool _val);
    

protected:
        
    // this is for convenience
    virtual void doSetEnabled(bool _enabled) {};
    virtual void doSetLocked(bool _unlocked) {};

    
	// subclasses can get these messages
    // if something special needs to happen on lock or unlock
	virtual void onEnabled() {};
	virtual void onDisabled() {};
    
    virtual void onLocked() {};
	virtual void onUnlocked() {};
    
private:

    
    // this object
    bool _enabled;
    bool _locked; // called unlocked ... so it can normally be true
    bool _hidden;
    
    // oF events handling -- 
    // precice control over event acquisition and 
    // propagation
    // in ofxMui, of events have a signle entry point
    // at the root node and pass down through the 
    // tree, rather than setting up each object as an 
    // ofEvent listener.
        
    bool _setupEvents;
    bool _propagateSetupEvents;
    
    bool _updateEvents;
    bool _propagateUpdateEvents;

    bool _drawEvents;
    bool _propagateDrawEvents;
    
    bool _mouseEvents;
    bool _propagateMouseEvents;

    bool _keyboardEvents;
    bool _propagateKeyboardEvents;

    bool _messageEvents;
    bool _propagateMessageEvents;
    
    bool _fileDragEvents;
    bool _propagateFileDragEvents;
    
    bool _windowResizedEvents;
    bool _propagateWindowResizedEvents;
    	
};


