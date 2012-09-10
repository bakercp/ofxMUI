#include "ofxGuiEnabler.h"

//--------------------------------------------------------------
ofxGuiEnabler::ofxGuiEnabler() :
_enabled(true),
_locked(false), 
_hidden(false),
_setupEvents(true),
_propagateSetupEvents(true),
_updateEvents(true),
_propagateUpdateEvents(true),
_drawEvents(true),
_propagateDrawEvents(true),
_mouseEvents(true),
_propagateMouseEvents(true),
_keyboardEvents(true),
_propagateKeyboardEvents(true),
_messageEvents(true),
_propagateMessageEvents(true),
_fileDragEvents(true),
_propagateFileDragEvents(true),
_windowResizedEvents(true),
_propagateWindowResizedEvents(true)
{
}

ofxGuiEnabler::ofxGuiEnabler(bool _enabled) :
_enabled(_enabled),
_locked(false), 
_hidden(false),
_setupEvents(true),
_propagateSetupEvents(true),
_updateEvents(true),
_propagateUpdateEvents(true),
_drawEvents(true),
_propagateDrawEvents(true),
_mouseEvents(true),
_propagateMouseEvents(true),
_keyboardEvents(true),
_propagateKeyboardEvents(true),
_messageEvents(true),
_propagateMessageEvents(true),
_fileDragEvents(true),
_propagateFileDragEvents(true),
_windowResizedEvents(true),
_propagateWindowResizedEvents(true)
{
}


//--------------------------------------------------------------
ofxGuiEnabler::~ofxGuiEnabler() {
        // nothing to do
}

//--------------------------------------------------------------
bool ofxGuiEnabler::isEnabled() const {
		return _enabled;
}

//--------------------------------------------------------------
void ofxGuiEnabler::enable() {
    setEnabled(true);
}

//--------------------------------------------------------------
void ofxGuiEnabler::disable() {
    setEnabled(false);
}

//--------------------------------------------------------------
void ofxGuiEnabler::toggleEnabled() {
    if(isEnabled()) {
        disable();
    } else {
        enable();
    }
}

//--------------------------------------------------------------
void ofxGuiEnabler::setEnabled(bool __enabled) { 
    if(_enabled != __enabled) {
        _enabled = __enabled;
        doSetEnabled(_enabled);
        if(_enabled) {
            onEnabled();
        } else {
            onDisabled();
        }
    }
}

//--------------------------------------------------------------
bool ofxGuiEnabler::isLocked() const {
    return _locked;
}

//--------------------------------------------------------------
void ofxGuiEnabler::setLocked(bool _val) {
    
    if(isEnabled() && _val != _locked) {
        _locked = _val;
        doSetLocked(_val);
        if(_locked) {
            onLocked();
        } else {
            onUnlocked();
        }  
    }    
}

//--------------------------------------------------------------
bool ofxGuiEnabler::isHidden() const {
    return _hidden;
}

//--------------------------------------------------------------
void ofxGuiEnabler::setHidden(bool _val) {
    //if(_val) //cout << "HIDING" << endl;
    //    else //cout << "SHOWING" << endl;
    _hidden = _val;
}

//--------------------------------------------------------------
void ofxGuiEnabler::hide() {
    setHidden(true);
}

//--------------------------------------------------------------
void ofxGuiEnabler::show() {
    //cout << ">>>>>>> SHOW -- ";
    setHidden(false);
}

//--------------------------------------------------------------
bool ofxGuiEnabler::isSetupHandler() const {
    return _setupEvents;
}

//--------------------------------------------------------------
void ofxGuiEnabler::setIsSetupHandler(bool _val) {
    _setupEvents = _val;
}

//--------------------------------------------------------------
bool ofxGuiEnabler::propagateSetupEvents() {
    return _propagateSetupEvents;
}

//--------------------------------------------------------------
void ofxGuiEnabler::setPropagateSetupEvents(bool _val) {
    _propagateSetupEvents = _val;
}



//--------------------------------------------------------------
bool ofxGuiEnabler::isDrawHandler() const {
    return _drawEvents;
}

//--------------------------------------------------------------
void ofxGuiEnabler::setIsDrawHandler(bool _isDrawing) {
    _drawEvents = _isDrawing;
}

//--------------------------------------------------------------
bool ofxGuiEnabler::propagateDrawEvents() {
    return _propagateDrawEvents;
}

//--------------------------------------------------------------
void ofxGuiEnabler::setPropagateDrawEvents(bool _val) {
    _propagateDrawEvents = _val;
}


//--------------------------------------------------------------
bool ofxGuiEnabler::isUpdateHandler() const {
    return _updateEvents;
}

//--------------------------------------------------------------
void ofxGuiEnabler::setIsUpdateHandler(bool _val) {
    _updateEvents = _val;
}

//--------------------------------------------------------------
bool ofxGuiEnabler::propagateUpdateEvents() {
    return _propagateUpdateEvents;
}

//--------------------------------------------------------------
void ofxGuiEnabler::setPropagateUpdateEvents(bool _val) {
    _propagateUpdateEvents = _val;
}


//--------------------------------------------------------------
bool ofxGuiEnabler::isMouseHandler() const {
    return _mouseEvents;
}

//--------------------------------------------------------------
void ofxGuiEnabler::setIsMouseHandler(bool _val) {
    _mouseEvents = _val;
}

//--------------------------------------------------------------
bool ofxGuiEnabler::propagateMouseEvents() {
    return _propagateMouseEvents;
}

//--------------------------------------------------------------
void ofxGuiEnabler::setPropagateMouseEvents(bool _val) {
    _propagateMouseEvents = _val;
}


//--------------------------------------------------------------
bool ofxGuiEnabler::isKeyboardHandler() {
    return _keyboardEvents;
}

//--------------------------------------------------------------
void ofxGuiEnabler::setIsKeyboardHandler(bool _val) {
    _keyboardEvents = _val;
}

//--------------------------------------------------------------
bool ofxGuiEnabler::propagateKeyboardEvents() {
    return _propagateKeyboardEvents;
}

//--------------------------------------------------------------
void ofxGuiEnabler::setPropagateKeyboardEvents(bool _val) {
    _propagateKeyboardEvents = _val;
}

//--------------------------------------------------------------
void ofxGuiEnabler::setPropagatePeripheralEvents(bool _val) {
    setPropagateKeyboardEvents(_val);
    setPropagateMouseEvents(_val);
}


//--------------------------------------------------------------
bool ofxGuiEnabler::isMessageHandler() const {
    return _messageEvents;
}

//--------------------------------------------------------------
void ofxGuiEnabler::setIsMessageHandler(bool _val) {
    _messageEvents = _val;
}

//--------------------------------------------------------------
bool ofxGuiEnabler::propagateMessageEvents() {
    return _propagateMessageEvents;
}

//--------------------------------------------------------------
void ofxGuiEnabler::setPropagateMessageEvents(bool _val) {
    _propagateMessageEvents = _val;
}


//--------------------------------------------------------------
bool ofxGuiEnabler::isFileDragHandler() const {
    return _fileDragEvents;
}

//--------------------------------------------------------------
void ofxGuiEnabler::setIsFileDragHandler(bool _val) {
    _fileDragEvents = _val;
}

//--------------------------------------------------------------
bool ofxGuiEnabler::propagateFileDragEvents() {
    return _propagateFileDragEvents;
}

//--------------------------------------------------------------
void ofxGuiEnabler::setPropagateFileDragEvents(bool _val) {
    _propagateFileDragEvents = _val;
}


//--------------------------------------------------------------
bool ofxGuiEnabler::isWindowResizedHandler() const {
    return _windowResizedEvents;
}

//--------------------------------------------------------------
void ofxGuiEnabler::setIsWindowResizedHandler(bool _val) {
    _windowResizedEvents = _val;
}

//--------------------------------------------------------------
bool ofxGuiEnabler::propagateWindowResizedEvents() {
    return _propagateWindowResizedEvents;
}

//--------------------------------------------------------------
void ofxGuiEnabler::setPropagateWindowResizedEvents(bool _val) {
    _propagateWindowResizedEvents = _val;
}