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

#include "ofxMuiLabelledObject.h"
#include "ofxMuiNumberData.h"

//--------------------------------------------------------------
class ofxMuiNumberBox : public ofxMuiLabelledObject, public ofxMuiNumberData {
public:
    
    ofxMuiNumberBox(const string& _name, int _x, int _y, int _width, int _height, bool _enabled = true);
    ofxMuiNumberBox(const string& _name, int _x, int _y,bool _enabled = true);
    ofxMuiNumberBox(const string& _name, bool _enabled = true);
    ofxMuiNumberBox(bool _enabled = true);
    virtual ~ofxMuiNumberBox();
    
    //--------------------------------------------------------------
    // INHERITED FROM SUPERCLASS ///////////////////////////////////
    //--------------------------------------------------------------
    
    void update();
    void draw();
    
    //--------------------------------------------------------------
    // PERSISTENCE /////////////////////////////////////////////////
    //--------------------------------------------------------------
    
    void loadFromXml(ofxXmlSettings& xml);
    void saveToXml(ofxXmlSettings& xml);
    
    //--------------------------------------------------------------
    // KEYBINDING //////////////////////////////////////////////////
    //--------------------------------------------------------------
    
    void keyBind_increaseValue(int key);
    void keyBind_decreaseValue(int key);
    
    //--------------------------------------------------------------
    // GETTERS AND SETTERS /////////////////////////////////////////
    //--------------------------------------------------------------
    
protected:
    
    void init();
        
    //--------------------------------------------------------------
    // INHERITED FROM SUPERCLASS ///////////////////////////////////
    //--------------------------------------------------------------
    
    void onPress();
    void onDrag();
    
    float getDragDigit();
    
    void doContentBoxLayout();
    
    //--------------------------------------------------------------
    // VARIABLES ///////////////////////////////////////////////////
    //--------------------------------------------------------------
    
    int numPosition;
    
    //--------------------------------------------------------------
    // EVENTS //////////////////////////////////////////////////////
    //--------------------------------------------------------------
    
    ofEvent<float> ofxMuiNumberBoxEvent;
    
    
};

//--------------------------------------------------------------

