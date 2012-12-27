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

#include "ofxMuiEnabler.h"

//--------------------------------------------------------------
ofxMuiEnabler::ofxMuiEnabler() :
_enabled(true),
_locked(false), 
_hidden(false),
_setupEvents(true),
_propagateSetupEvents(true),
_updateEvents(true),
_propagateUpdateEvents(true),
_drawEvents(true),
_propagateDrawEvents(true),
//_mouseEvents(true),
//_propagateMouseEvents(true),
_keyboardEvents(true),
_propagateKeyboardEvents(true),
_touchEvents(true),
_propagateTouchEvents(true),
_messageEvents(true),
_propagateMessageEvents(true),
_fileDragEvents(true),
_propagateFileDragEvents(true),
_windowResizedEvents(true),
_propagateWindowResizedEvents(true)
{
}

ofxMuiEnabler::ofxMuiEnabler(bool _enabled) :
_enabled(_enabled),
_locked(false), 
_hidden(false),
_setupEvents(true),
_propagateSetupEvents(true),
_updateEvents(true),
_propagateUpdateEvents(true),
_drawEvents(true),
_propagateDrawEvents(true),
//_mouseEvents(true),
//_propagateMouseEvents(true),
_keyboardEvents(true),
_propagateKeyboardEvents(true),
_touchEvents(true),
_propagateTouchEvents(true),
_messageEvents(true),
_propagateMessageEvents(true),
_fileDragEvents(true),
_propagateFileDragEvents(true),
_windowResizedEvents(true),
_propagateWindowResizedEvents(true)
{
}

//--------------------------------------------------------------
ofxMuiEnabler::~ofxMuiEnabler() {}

//--------------------------------------------------------------
bool ofxMuiEnabler::isEnabled() const {
    return _enabled;
}

//--------------------------------------------------------------
void ofxMuiEnabler::enable() {
    setEnabled(true);
}

//--------------------------------------------------------------
void ofxMuiEnabler::disable() {
    setEnabled(false);
}

//--------------------------------------------------------------
void ofxMuiEnabler::toggleEnabled() {
    if(isEnabled()) {
        disable();
    } else {
        enable();
    }
}

//--------------------------------------------------------------
void ofxMuiEnabler::setEnabled(bool __enabled) { 
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
bool ofxMuiEnabler::isLocked() const {
    return _locked;
}

//--------------------------------------------------------------
void ofxMuiEnabler::setLocked(bool _val) {
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
bool ofxMuiEnabler::isHidden() const {
    return _hidden;
}

//--------------------------------------------------------------
void ofxMuiEnabler::setHidden(bool _val) {
    _hidden = _val;
}

//--------------------------------------------------------------
void ofxMuiEnabler::hide() {
    setHidden(true);
}

//--------------------------------------------------------------
void ofxMuiEnabler::show() {
    setHidden(false);
}

//--------------------------------------------------------------
bool ofxMuiEnabler::isSetupHandler() const {
    return _setupEvents;
}

//--------------------------------------------------------------
void ofxMuiEnabler::setIsSetupHandler(bool _val) {
    _setupEvents = _val;
}

//--------------------------------------------------------------
bool ofxMuiEnabler::propagateSetupEvents() {
    return _propagateSetupEvents;
}

//--------------------------------------------------------------
void ofxMuiEnabler::setPropagateSetupEvents(bool _val) {
    _propagateSetupEvents = _val;
}



//--------------------------------------------------------------
bool ofxMuiEnabler::isDrawHandler() const {
    return _drawEvents;
}

//--------------------------------------------------------------
void ofxMuiEnabler::setIsDrawHandler(bool _isDrawing) {
    _drawEvents = _isDrawing;
}

//--------------------------------------------------------------
bool ofxMuiEnabler::propagateDrawEvents() {
    return _propagateDrawEvents;
}

//--------------------------------------------------------------
void ofxMuiEnabler::setPropagateDrawEvents(bool _val) {
    _propagateDrawEvents = _val;
}


//--------------------------------------------------------------
bool ofxMuiEnabler::isUpdateHandler() const {
    return _updateEvents;
}

//--------------------------------------------------------------
void ofxMuiEnabler::setIsUpdateHandler(bool _val) {
    _updateEvents = _val;
}

//--------------------------------------------------------------
bool ofxMuiEnabler::propagateUpdateEvents() {
    return _propagateUpdateEvents;
}

//--------------------------------------------------------------
void ofxMuiEnabler::setPropagateUpdateEvents(bool _val) {
    _propagateUpdateEvents = _val;
}


////--------------------------------------------------------------
//bool ofxMuiEnabler::isMouseHandler() const {
//    return _mouseEvents;
//}
//
////--------------------------------------------------------------
//void ofxMuiEnabler::setIsMouseHandler(bool _val) {
//    _mouseEvents = _val;
//}
//
////--------------------------------------------------------------
//bool ofxMuiEnabler::propagateMouseEvents() {
//    return _propagateMouseEvents;
//}
//
////--------------------------------------------------------------
//void ofxMuiEnabler::setPropagateMouseEvents(bool _val) {
//    _propagateMouseEvents = _val;
//}


//--------------------------------------------------------------
bool ofxMuiEnabler::isKeyboardHandler() {
    return _keyboardEvents;
}

//--------------------------------------------------------------
void ofxMuiEnabler::setIsKeyboardHandler(bool _val) {
    _keyboardEvents = _val;
}

//--------------------------------------------------------------
bool ofxMuiEnabler::propagateKeyboardEvents() {
    return _propagateKeyboardEvents;
}

//--------------------------------------------------------------
void ofxMuiEnabler::setPropagateKeyboardEvents(bool _val) {
    _propagateKeyboardEvents = _val;
}

//--------------------------------------------------------------
bool ofxMuiEnabler::isTouchHandler() const {
    return _touchEvents;
}

//--------------------------------------------------------------
void ofxMuiEnabler::setIsTouchHandler(bool _val) {
    _touchEvents = _val;
}

//--------------------------------------------------------------
bool ofxMuiEnabler::propagateTouchEvents() {
    return _propagateTouchEvents;
}

//--------------------------------------------------------------
void ofxMuiEnabler::setPropagateTouchEvents(bool _val) {
    _propagateTouchEvents = _val;
}

//--------------------------------------------------------------
void ofxMuiEnabler::setPropagateInputEvents(bool _val) {
    setPropagateKeyboardEvents(_val);
    setPropagateTouchEvents(_val);
//    setPropagateMouseEvents(_val);
}


//--------------------------------------------------------------
bool ofxMuiEnabler::isMessageHandler() const {
    return _messageEvents;
}

//--------------------------------------------------------------
void ofxMuiEnabler::setIsMessageHandler(bool _val) {
    _messageEvents = _val;
}

//--------------------------------------------------------------
bool ofxMuiEnabler::propagateMessageEvents() {
    return _propagateMessageEvents;
}

//--------------------------------------------------------------
void ofxMuiEnabler::setPropagateMessageEvents(bool _val) {
    _propagateMessageEvents = _val;
}


//--------------------------------------------------------------
bool ofxMuiEnabler::isFileDragHandler() const {
    return _fileDragEvents;
}

//--------------------------------------------------------------
void ofxMuiEnabler::setIsFileDragHandler(bool _val) {
    _fileDragEvents = _val;
}

//--------------------------------------------------------------
bool ofxMuiEnabler::propagateFileDragEvents() {
    return _propagateFileDragEvents;
}

//--------------------------------------------------------------
void ofxMuiEnabler::setPropagateFileDragEvents(bool _val) {
    _propagateFileDragEvents = _val;
}


//--------------------------------------------------------------
bool ofxMuiEnabler::isWindowResizedHandler() const {
    return _windowResizedEvents;
}

//--------------------------------------------------------------
void ofxMuiEnabler::setIsWindowResizedHandler(bool _val) {
    _windowResizedEvents = _val;
}

//--------------------------------------------------------------
bool ofxMuiEnabler::propagateWindowResizedEvents() {
    return _propagateWindowResizedEvents;
}

//--------------------------------------------------------------
void ofxMuiEnabler::setPropagateWindowResizedEvents(bool _val) {
    _propagateWindowResizedEvents = _val;
}