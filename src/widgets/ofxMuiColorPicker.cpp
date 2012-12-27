//
//  ofxMuiColorPicker.cpp
//  BasicExample
//
//  Created by Christopher Baker on 7/24/11.
//  Copyright 2011 School of the Art Institute of Chicago. All rights reserved.
//

#include "ofxMuiColorPicker.h"

ofxMuiColorPicker::ofxMuiColorPicker(string _name, int _x, int _y, int _width, int _height, bool _enabled) : 
ofxMuiLabelledObject(_name, _x, _y, _width, _height, _enabled),
ofxMuiNumberData(ofxMui_FLOAT_ARRAY, 4) {
    init();
}

//--------------------------------------------------------------
ofxMuiColorPicker::ofxMuiColorPicker(string _name, int _x, int _y,bool _enabled) : 
ofxMuiLabelledObject(_name, _x, _y, _enabled),
ofxMuiNumberData(ofxMui_FLOAT_ARRAY, 4) {
    init();
}

//--------------------------------------------------------------
ofxMuiColorPicker::ofxMuiColorPicker(string _name,bool _enabled) :
ofxMuiLabelledObject(_name, _enabled),
ofxMuiNumberData(ofxMui_FLOAT_ARRAY, 4) {
    init();
}

//--------------------------------------------------------------
ofxMuiColorPicker::ofxMuiColorPicker(bool _enabled) : 
ofxMuiLabelledObject(_enabled),
ofxMuiNumberData(ofxMui_FLOAT_ARRAY, 4) {
    init();
}

//--------------------------------------------------------------
ofxMuiColorPicker::~ofxMuiColorPicker() {
}

//--------------------------------------------------------------
void ofxMuiColorPicker::update() {
    ofColor c = getValue();
    //tooltip = "HEX:  "+ofColorToHexString(getValue());
    //tooltip+= "\n";
//    tooltip.clear();
//    tooltip+= "A: " + ofToString((int)c.a) + "\n"; 
//    tooltip+= "R: " + ofToString((int)c.r) + "\n"; 
//    tooltip+= "G: " + ofToString((int)c.g) + "\n"; 
//    tooltip+= "B: " + ofToString((int)c.b); 
}

//--------------------------------------------------------------
void ofxMuiColorPicker::init() {
    // super class init should have already been called in the constructor def list
    
    setObjectType("COLOR_PICKER");

    // override the superclass
    setBoxProperties(defaults->colorPickerBoxProperties);    
	
    setValue(1,0); // r
    setValue(1,1); // g
    setValue(1,2); // b
    setValue(1,3); // a

	// set default key binding
    //keyBind_toggleValue(' ');
    
	// custom, just for the button itself (i.e. no clicking on the label)
	setHitBox(0, 0, defaults->colorPickerWidth, defaults->colorPickerHeight);
    
    colorPickerPreview.height = defaults->colorPickerPreviewHeight;

    // get the little preview-r
    
    eyeDropperPreviewPixelWidth = defaults->colorPickerEyeDropperWidth / defaults->colorPickerEyeDropperZoom;
    eyeDropperPreviewPixelHeight = defaults->colorPickerEyeDropperWidth / defaults->colorPickerEyeDropperZoom;
    eyeDropperPreview.allocate(eyeDropperPreviewPixelWidth,eyeDropperPreviewPixelHeight,GL_RGB);
    
    showEyeDroperPreview = false;
    
    setNeedsLayoutUpdate(true);

}

//--------------------------------------------------------------
void ofxMuiColorPicker::dataChanged() {
    //ofNotifyEvent(ofxMuiColorPickerEvent, value, this);
}


//--------------------------------------------------------------
//void ofxMuiColorPicker::keyBind_toggleValue(int key) {
//    setKeyMap(key,bind(&ofxGuiButton::toggleValue, ref(*this))); 
//}

//--------------------------------------------------------------
void ofxMuiColorPicker::draw() {
    
    //if(name == "MCP") {
    //    cout << "in here" << endl;
    //}
    
    ofPushStyle();
	ofPushMatrix(); // initial push
    
    ofTranslate(getHitBoxX(),getHitBoxY());
    

    
    ofSetColor(255);
    picker.draw(0,0);

    ofFill();
    ofSetColor(getValue());
    ofxRect(colorPickerPreview);

    ofFill();
    ofSetColor(30);
    ofLine(colorPickerPreview.x,colorPickerPreview.y,getHitBoxWidth(),colorPickerPreview.y);
    
    ofNoFill();
    
    
    if(showEyeDroperPreview) {
        
        eyeDropperPreview.loadScreenData(mousePosition.x-eyeDropperPreviewPixelWidth/2.0f,
                                         mousePosition.y-eyeDropperPreviewPixelHeight/2.0f
                                         ,eyeDropperPreviewPixelWidth,eyeDropperPreviewPixelHeight);

        
        ofPushMatrix();
        ofTranslate(screenToHitBox(mousePosition));

        
        ofSetColor(255);
       // ofxRect(0,0,
       // ofPushMatrix(

        ofPushMatrix();
        ofScale(defaults->colorPickerEyeDropperZoom,defaults->colorPickerEyeDropperZoom);
        ofTranslate(-eyeDropperPreviewPixelWidth/2.0, -eyeDropperPreviewPixelHeight/2.0f);
        eyeDropperPreview.draw(0,0);
        ofPopMatrix();
        
        ofCircle(0,0,4,4);

        
        ofPopMatrix();
     
    } else {
        //ofSetColor(getValue().getInverted().getBrightness());
        ofCircle(cursor.x-2, cursor.y-2, 4);
    }
    
    /*
    if(isDragging) {
        ofFill();
        ofSetColor(255);
        ofxRect(0,0,40,40);
    }
    */
        
        
    ofPopMatrix(); // HIT RECT PUSH
    ofPopStyle();
    
    
}

//--------------------------------------------------------------
void ofxMuiColorPicker::onPress() {
    showEyeDroperPreview = false;
    cursor = screenToHitBox(mousePosition);
    //setValue(picker.getColor(cursor.x,cursor.y));
}

//--------------------------------------------------------------
void ofxMuiColorPicker::onDragOver() {
    showEyeDroperPreview = false;
    cursor = screenToHitBox(mousePosition);
    //setValue(picker.getColor(cursor.x,cursor.y));
}

//--------------------------------------------------------------
void ofxMuiColorPicker::onDragOutside() {
    showEyeDroperPreview = true;
    
}

//--------------------------------------------------------------
void ofxMuiColorPicker::onReleaseOutside() {
    // grab the ceter color and set it
    
    
    showEyeDroperPreview = false;
}

//--------------------------------------------------------------
void ofxMuiColorPicker::buildFromXml()
{
	//props->mListener->handleGui(mParamId, kofxGui_Set_Bool, &value, sizeof(bool));
}

//--------------------------------------------------------------
void ofxMuiColorPicker::saveToXml()
{
}

//--------------------------------------------------------------
void ofxMuiColorPicker::doContentBoxLayout() {
//
//    
//    // regenerate the picker image
//    picker.allocate(hitBox.width, hitBox.height, OF_IMAGE_COLOR);
//    generatePicker(hitBox.width, hitBox.height);
//    picker.update();
//    
//    // label to the right
//    label->setX(0); // label to the right
//    label->setY(0);
//
//    hitBox.x = 0;
//    hitBox.y = label->getHeight();
//    
//    // TODO: this doesn't account for auto widths ...
//
//    colorPickerPreview.x = hitBox.x;
//    colorPickerPreview.y = hitBox.height;
//    // height set during init
//    colorPickerPreview.width = hitBox.width;
//
//    contentBox.width = hitBox.width;
//    contentBox.height = hitBox.height + label->getHeight() + colorPickerPreview.height;
//
    
    
}



void ofxMuiColorPicker::generatePicker (int w, int h)
{
    // draw color.
    int cw = w - 0.2f*w; // the color width
    for( int i=0; i<cw; i++ ) 
    {
        float nColorPercent = i / (float)cw;
        float rad = (-360.0f * nColorPercent) * (PI / 180.0f);
        int nR = (int)(cos(rad) * 127.0f + 128);// << 16;
        int nG = (int)(cos(rad + 2.0f * PI / 3.0f) * 127.0f + 128.0f);// << 8;
        int nB = (int)(cos(rad + 4.0f * PI / 3.0f) * 127.0f + 128.0f);
        //int nColor = nR | nG | nB;
        
        ofColor nColor = ofColor(nR,nG,nB);
        
        setGradient( i, 0, 1, h/2, 0xFFFFFF, nColor );
        setGradient( i, (h/2), 1, h/2, nColor, 0x000000 );
    }
    
    // 
    int gsWidth = (w - cw) / 2;
    int bwWidth = gsWidth;
    
    // draw black/white.
    drawRect( cw, 0,   gsWidth, h/2, 0xFFFFFF );
    drawRect( cw, h/2, gsWidth, h/2, 0        );
    
    // draw grey scale.
    for( int j=0; j<h; j++ ) {
        int g = 255 - (int)(j/(float)(h-1) * 255 );

        drawRect( cw+gsWidth, j, gsWidth, 1, ofColor( g, g, g ) );
    }

}

void ofxMuiColorPicker::setGradient(int x, int y, float w, float h, ofColor c1, ofColor c2 )
{
    float deltaR = c2.r - c1.r;
    float deltaG = c2.g - c1.g;
    float deltaB = c2.b - c1.b;
    
    for (int j = y; j<(y+h); j++)
    {
        ofColor c = ofColor(c1.r+(j-y)*(deltaR/h), 
                            c1.g+(j-y)*(deltaG/h), 
                            c1.b+(j-y)*(deltaB/h) );
        
        picker.setColor( x, j, c );
    }
}

void ofxMuiColorPicker::drawRect( int rx, int ry, int rw, int rh, ofColor rc ) {
    for(int i=rx; i<rx+rw; i++) {
        for(int j=ry; j<ry+rh; j++) {
            picker.setColor(i, j, rc);
        }
    }
}


