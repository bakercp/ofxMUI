//
//  ofxMuiColorPicker.cpp
//  BasicExample
//
//  Created by Christopher Baker on 7/24/11.
//  Copyright 2011 School of the Art Institute of Chicago. All rights reserved.
//

// THANKS JULAPY!
// http://www.julapy.com/processing/ColorPicker.pde

#pragma once

#include "ofxMuiLabelledObject.h"
#include "ofxMuiNumberData.h"

class ofxMuiColorPicker : public ofxMuiLabelledObject, public ofxMuiNumberData {
public:
    
    ofxMuiColorPicker(string _name, int _x, int _y, int _width, int _height, bool _enabled = true);
    ofxMuiColorPicker(string _name, int _x, int _y,bool _enabled = true);
    ofxMuiColorPicker(string _name, bool _enabled = true);
    ofxMuiColorPicker(bool _enabled = true);
    virtual ~ofxMuiColorPicker();
    
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
    
    //void keyBind_toggleValue(int key);
    
    //--------------------------------------------------------------
    // GETTERS AND SETTERS /////////////////////////////////////////
    //--------------------------------------------------------------
    
    // 
    
    //--------------------------------------------------------------
    // LABELS //////////////////////////////////////////////////////
    //--------------------------------------------------------------
        
protected:
    
    void init(); // local init for convenience
    void dataChanged();
    

    //--------------------------------------------------------------
    // INHERITED FROM SUPERCLASS ///////////////////////////////////
    //--------------------------------------------------------------
    
    // mouse action
	void onPress();
	void onDragOver();	
    void onDragOutside();
	void onReleaseOutside();
    
    void doContentBoxLayout();
    
	//--------------------------------------------------------------
    // VARIABLES ///////////////////////////////////////////////////
    //--------------------------------------------------------------
    
    ofVec2f cursor;
    
    ofImage picker;
    
    bool showEyeDroperPreview;
    ofTexture eyeDropperPreview; // the little grab from the screen
    int eyeDropperPreviewPixelWidth;
    int eyeDropperPreviewPixelHeight;

    
    
    ofRectangle colorPickerPreview;
    
    void generatePicker (int w, int h);
    void setGradient(int x, int y, float w, float h, ofColor c1, ofColor c2 );
    void drawRect( int rx, int ry, int rw, int rh, ofColor rc );

    
    //--------------------------------------------------------------
    // EVENTS //////////////////////////////////////////////////////
    //--------------------------------------------------------------
    
    ofEvent<ofColor> ofxMuiColorPickerEvent;
    
    
};

//--------------------------------------------------------------
