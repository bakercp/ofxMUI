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

#include "ofxMuiKeyMapper.h"



// static shared state information
// of now has built-in keyPressed array, but no way to check on modifiers by default

//--------------------------------------------------------------
ofxMuiKeyMapper::ofxMuiKeyMapper() {    
}

//--------------------------------------------------------------
ofxMuiKeyMapper::~ofxMuiKeyMapper() {    
}

//--------------------------------------------------------------
bool ofxMuiKeyMapper::removeKeyMap(int key) {
    keyMapIter = keyMap.find(key);
    if(keyMapIter == keyMap.end()) {
        // it wasn't found
        return false;
    } else {
        keyMap.erase(keyMapIter);
        return true;
    }
}
 
//--------------------------------------------------------------
void ofxMuiKeyMapper::setKeyMap(int key, KeyMappedFunc func) {
    removeKeyMap(key); // remove an old key
    keyMap[key] = func; // add a new one
}

//--------------------------------------------------------------
bool ofxMuiKeyMapper::isKeyMapped(int key) {
    keyMapIter = keyMap.find(key);
    return keyMapIter != keyMap.end(); // if it is @ the end, it was not found
}

//--------------------------------------------------------------
int ofxMuiKeyMapper::getNumKeysMapped() {
    return keyMap.size();
}

//--------------------------------------------------------------
bool ofxMuiKeyMapper::executeKeyMappedFunc(int key) {
    keyMapIter = keyMap.find(key);
    if(keyMapIter == keyMap.end()) {
        return false;
    } else {
        keyMapIter->second(); // call the mapped function
        return true;
    }
}

//--------------------------------------------------------------
void ofxMuiKeyMapper::clearKeyMaps() {
    keyMap.clear();
}