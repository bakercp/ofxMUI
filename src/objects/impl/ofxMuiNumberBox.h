//
//  ofxMuiNumberBox.h
//  BasicExample
//
//  Created by Christopher Baker on 7/25/11.
//  Copyright 2011 School of the Art Institute of Chicago. All rights reserved.
//


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
    
    void buildFromXml();
    void saveToXml();
    
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

