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

enum ofxMuiIconName {
    ICON_NONE,
    ICON_DEFAULT,
    ICON_X,
    ICON_PLUSMINUS,
    ICON_CHECK,
    ICON_TARGET
};


class ofxMuiIcon {
    
public:
    
    ofxMuiIcon() : onLoaded(false), offLoaded(false)  {}
    
    ofxMuiIcon(string _img) : onLoaded(false), offLoaded(false) {
        set(_img, _img);
    }    

    ofxMuiIcon(string _on, string _off) : onLoaded(false), offLoaded(false) {
        set(_on, _off);
    }    

    ofImage* getIcon(bool _isActive = true) {
        return _isActive ? &on : &off; 
    }
    
    void setOn(string _on) {
        onLoaded = on.loadImage(_on);
        if(!onLoaded) {
            ofLog(OF_LOG_ERROR, "ofxMuiIcon::Icons on Image " + _on + " not loaded.");
        }

    }
    
    void setOff(string _off) {
        offLoaded = off.loadImage(_off);
        
        if(!offLoaded) {
            ofLog(OF_LOG_ERROR, "ofxMuiIcon::Icons off Image " + _off + " not loaded.");
        }

    }
    
    ofImage* getOn() {return &on;};
    ofImage* getOff() {return &off;};
    
    void set(string _on, string _off) {
        onLoaded = on.loadImage(_on);
        offLoaded = off.loadImage(_off);
        
        width = on.getWidth();
        height = on.getHeight();
        
        if(on.width != off.width || on.height != off.height) {
            ofLog(OF_LOG_WARNING, "ofxMuiIcon::Icons (" + _on + ") & (" + _off + ") are not equal in size.  Unpredictable results.");
        }
        
        if(!onLoaded) {
            ofLog(OF_LOG_ERROR, "ofxMuiIcon::Icons on Image " + _on + " not loaded.");
        }
        
        if(!offLoaded) {
            ofLog(OF_LOG_ERROR, "ofxMuiIcon::Icons off Image " + _off + " not loaded.");
        }
        
    }
    
    int getWidth() {return width;};
    int getHeight() {return height;};
    
    bool isLoaded() {
        return offLoaded && onLoaded;
    }
    
    bool isOnLoaded() {
        return onLoaded;
    }
    
    bool isOffLoaded() {
        return offLoaded;
    }
    
protected:
    
private: 
    // TODO: add "active"?
    
    ofImage on;   // normal
    ofImage off;
    
    bool onLoaded;
    bool offLoaded;
    
    int width;
    int height;
    
};




























/*
 enum ofxMuiIconType {
 ICON_TYPE_DEFAULT,
 ICON_TYPE_BLANK,
 ICON_TYPE_ADD,
 ICON_TYPE_SUBTRACT,
 ICON_TYPE_X,
 ICON_TYPE_CHECK,
 ICON_TYPE_STOP
 
 ,
 ICON_PAUSE,
 ICON_PLAY,
 
 ICON_ALERT,
 ICON_CAMERA,
 
 ICON_CD,
 
 ICON_ARROW1_E,
 ICON_ARROW1_N,
 ICON_ARROW1_NE,
 ICON_ARROW1_NW,
 ICON_ARROW1_S,
 ICON_ARROW1_SE,
 ICON_ARROW1_SW,
 ICON_ARROW1_W,
 
 ICON_ARROW2_E,
 ICON_ARROW2_N,
 ICON_ARROW2_NE,
 ICON_ARROW2_NW,
 ICON_ARROW2_S,
 ICON_ARROW2_SE,
 ICON_ARROW2_SW,
 ICON_ARROW2_W,
 
 ICON_ARROW3_E,
 ICON_ARROW3_N,
 ICON_ARROW3_NE,
 ICON_ARROW3_NW,
 ICON_ARROW3_S,
 ICON_ARROW3_SE,
 ICON_ARROW3_SW,
 ICON_ARROW3_W,
 
 ICON_LOCK,
 ICON_UNLOCK,
 
 ICON_LOOP,
 
 ICON_SEARCH,
 
 ICON_FIRST,
 ICON_LAST,
 
 
 ICON_ZOOMIN,
 ICON_ZOOMOUT
 };
 
 */
