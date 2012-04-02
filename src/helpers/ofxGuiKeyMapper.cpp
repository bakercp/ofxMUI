//
//  ofxGuiKeyMapper.cpp
//  emptyExample
//
//  Created by Christopher Baker on 7/15/11.
//  Copyright 2011 Kitchen Budapest. All rights reserved.
//

#include "ofxGuiKeyMapper.h"



// static shared state information
// of now has built-in keyPressed array, but no way to check on modifiers by default

//--------------------------------------------------------------
ofxGuiKeyMapper::ofxGuiKeyMapper() {    
}

//--------------------------------------------------------------
ofxGuiKeyMapper::~ofxGuiKeyMapper() {    
}

//--------------------------------------------------------------
bool ofxGuiKeyMapper::removeKeyMap(int key) {
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
void ofxGuiKeyMapper::setKeyMap(int key, KeyMappedFunc func) {
    removeKeyMap(key); // remove an old key
    keyMap[key] = func; // add a new one
}

//--------------------------------------------------------------
bool ofxGuiKeyMapper::isKeyMapped(int key) {
    keyMapIter = keyMap.find(key);
    return keyMapIter != keyMap.end(); // if it is @ the end, it was not found
}

//--------------------------------------------------------------
int ofxGuiKeyMapper::getNumKeysMapped() {
    return keyMap.size();
}

//--------------------------------------------------------------
bool ofxGuiKeyMapper::executeKeyMappedFunc(int key) {
    keyMapIter = keyMap.find(key);
    if(keyMapIter == keyMap.end()) {
        return false;
    } else {
        keyMapIter->second(); // call the mapped function
        return true;
    }
}

//--------------------------------------------------------------
void ofxGuiKeyMapper::clearKeyMaps() {
    keyMap.clear();
}