//
//  ofxMuiKeyMapper.h
//  emptyExample
//
//  Created by Christopher Baker on 7/15/11.
//  Copyright 2011 Kitchen Budapest. All rights reserved.
//

#pragma once

#include "ofMain.h"


// tr1 stuff, for function callbacks and key mapping
#if (_MSC_VER)
#include <functional>
#include <unordered_map>
    using std::unordered_map;
    using std::function;
    using std::bind;
    using std::ref;
#else
#include <tr1/functional>
#include <tr1/unordered_map>
    using std::tr1::unordered_map;
    using std::tr1::function;
    using std::tr1::bind;
    using std::tr1::ref;
#endif


// function pointer for keymaps
// all key mapped functions will have to point to 
// methods that do not take any variables
typedef function<void ()> KeyMappedFunc;

class ofxMuiKeyMapper {
    
public:
    ofxMuiKeyMapper();
    virtual ~ofxMuiKeyMapper();
    
    bool removeKeyMap(int key);    
    void setKeyMap(int key, KeyMappedFunc func);
    bool isKeyMapped(int key);
    int  getNumKeysMapped();
    bool executeKeyMappedFunc(int key);
    void clearKeyMaps();
    
protected:

private:
    
    // key mappings 
	unordered_map<int,KeyMappedFunc>            keyMap;
    unordered_map<int,KeyMappedFunc>::iterator  keyMapIter;
};