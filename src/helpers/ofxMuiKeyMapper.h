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