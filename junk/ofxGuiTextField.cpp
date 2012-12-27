//
//  ofxGuiLabel.cpp
//  emptyExample
//
//  Created by Christopher Baker on 7/11/11.
//  Copyright 2011 Kitchen Budapest. All rights reserved.
//

#include "ofxGuiLabel.h"


//--------------------------------------------------------------
ofxGuiLabel::ofxGuiLabel(string _name, 
                         int _x, 
                         int _y, 
                         int _width, 
                         int _height, 
                         bool _enabled) : 
    ofxGuiObject(_name, 
                 _x, 
                 _y, 
                 _width, 
                 _height, 
                 _enabled) {
    init();
}
//--------------------------------------------------------------
ofxGuiLabel::ofxGuiLabel(string _name, 
                         int _x, 
                         int _y, 
                         bool _enabled) : 
    ofxGuiObject(_name, 
                 _x, 
                 _y, 
                 _enabled) {
    init();
}

ofxGuiLabel::ofxGuiLabel(string _name, 
                         bool _enabled) : 
    ofxGuiObject(_name, 
                 _enabled) {
    init();
}

ofxGuiLabel::ofxGuiLabel(bool _enabled) : 
    ofxGuiObject(_enabled) {
    init();
}

//--------------------------------------------------------------
ofxGuiLabel::~ofxGuiLabel() {
    
}

//--------------------------------------------------------------
void ofxGuiLabel::init() {
    
    setObjectType("LABEL");

    displayText = name;
    pDisplayText = name;

    text = name;
    pText = name;

    setBoxProperties(defaults->labelBoxProperties);    

    setFontSize(SIZE_SMALL); // chooses the font

    capsStyle = LABEL_CAPS_NONE;
    
    if(text.empty()) {
        hide();
    }
        
    cursorPosition = 0.0f;
    widthAtCursor = 0.0f;

    setOrientation(OF_ORIENTATION_DEFAULT);
    
    //cout << "\t\tLABEL CALLING SET NEEDS FROM LABEL INIT " << getName() << endl;

    lineBreakMode = LINE_BREAK_MODE_TAIL_TRUNCATION;
    truncationString = "...";
    
    isMultiline = false;
    
    requestBoxLayout();
}


//--------------------------------------------------------------
void ofxGuiLabel::draw() {
        
    ofPushStyle();
    ofPushMatrix();
    {        
        if(!displayText.empty()) {
            ofSetColor(cText.get(isMouseOver(),isMouseDown(),isEnabled(),alphaScale));
            
            ofPushMatrix();
            // TODO: add support for various text alignments
            ofRectangle drawOffsets = displayStringBoundingBox;

            switch(orientation) {
                case OF_ORIENTATION_UNKNOWN: // if unknown, use default
                case OF_ORIENTATION_DEFAULT:	
                    ofTranslate(0, labelFont->getSize());
                    break;
                case OF_ORIENTATION_180:
                    ofTranslate(displayStringBoundingBox.width, getContentBoxHeight() - labelFont->getSize());
                    ofRotateZ(180);
                    break;
                case OF_ORIENTATION_90_RIGHT:
                    ofTranslate(0,0);
                    ofRotateZ(90);
                    break;
                case OF_ORIENTATION_90_LEFT:
                    // TODO: this is off in the Y direction ... not sure why.
                    ofTranslate(labelFont->getSize(), 
                                getContentBoxHeight());
                    ofRotateZ(-90);
                    break;
            }
            
            
                
            labelFont->drawString(displayText,drawOffsets.x,drawOffsets.y);
            ofPopMatrix();
        }
         
    }
    ofPopMatrix();
    ofPopStyle();

}

//--------------------------------------------------------------
void ofxGuiLabel::setText(string _text) {
    text = _text;
    requestBoxLayout();
}

//--------------------------------------------------------------
string ofxGuiLabel::getText() {
    return text;
}

//--------------------------------------------------------------
string ofxGuiLabel::getDisplayText() {
    return displayText;
}

//--------------------------------------------------------------
void ofxGuiLabel::setFontSize(ofxGuiSize _labelSize) {
    labelSize = _labelSize;
    labelFont = defaults->getFont(_labelSize);
    requestBoxLayout();
}

//--------------------------------------------------------------
ofxGuiSize ofxGuiLabel::getFontSize() {
    return labelSize;
}


//--------------------------------------------------------------
void ofxGuiLabel::setCapsStyle(const ofxGuiLabelCaps& _capsStyle) {
    capsStyle = _capsStyle;
    requestBoxLayout();
}

//--------------------------------------------------------------
ofxGuiLabelCaps ofxGuiLabel::getCapsStyle() const {
    return capsStyle;
}

//--------------------------------------------------------------
void ofxGuiLabel::setLineBreakMode(const ofxGuiLabelLineBreakMode& _lineBreakMode) {
    lineBreakMode = _lineBreakMode;
    requestBoxLayout();
}

//--------------------------------------------------------------
ofxGuiLabelLineBreakMode ofxGuiLabel::getLineBreakMode() const {
    return lineBreakMode;
}

//--------------------------------------------------------------
void ofxGuiLabel::setTruncationString(string _truncationString) {
    truncationString = _truncationString;
    requestBoxLayout();
}

//--------------------------------------------------------------
string ofxGuiLabel::getTruncationString() {
    return truncationString;
}

//--------------------------------------------------------------
bool ofxGuiLabel::empty() {
    return text.empty();
}

//--------------------------------------------------------------
void ofxGuiLabel::doContentBoxLayout() {
    
    displayText = text;
    
    // get the bounding box of an unmodified string
    fullStringBoundingBox   =  labelFont->getStringBoundingBox(text, 0,0);

    switch (capsStyle) {
        case LABEL_CAPS_NONE:
            break;
        case LABEL_CAPS_UPPER:
            toUpperInPlace(displayText);
            break;
        case LABEL_CAPS_LOWER:
            toLowerInPlace(displayText);
            break;
        default:
            // do nothing
            break;
    }
    
    if(lineBreakMode != LINE_BREAK_MODE_WORD_NONE && isFixedWidth()) {
        
        // TODO
        // TODO, this CAN depend on alignent as well
        switch (lineBreakMode) {
            case LINE_BREAK_MODE_WORD_NONE:
            case LINE_BREAK_MODE_WORD_WRAP:
            case LINE_BREAK_MODE_CHARACTER_WRAP:
            case LINE_BREAK_MODE_CLIP:
            case LINE_BREAK_MODE_HEAD_TRUNCATION:
            case LINE_BREAK_MODE_TAIL_TRUNCATION:
            case LINE_BREAK_MODE_MIDDLE_TRUNCATION:
                break;
        }
        
        string testString = displayText;
    }
    
    displayStringBoundingBox =  labelFont->getStringBoundingBox(displayText,0,0);

    
    
    //cout << "display text rect for (displayText)=>" << displayText << "<| " << ofxGuiRectUtils::toString(&displayTextRect) << endl;

    
    switch(orientation) {
        case OF_ORIENTATION_UNKNOWN: // if unknown, use default
        case OF_ORIENTATION_DEFAULT:	
        case OF_ORIENTATION_180:
            //cout << labelFont ->getSize() << endl;
            // place anchor on upper left corner
            displayStringBoundingBox.x = 0;//
            displayStringBoundingBox.y = 0;//y += displayTextRect.height;
            break;
        case OF_ORIENTATION_90_RIGHT:
        case OF_ORIENTATION_90_LEFT:
            float tmp = displayStringBoundingBox.width;
            displayStringBoundingBox.width = displayStringBoundingBox.height; 
            displayStringBoundingBox.height = tmp;
            displayStringBoundingBox.y = 0;
            break;
    }
    

    //cout << "display text rect: " << ofxGuiRectUtils::toString(&displayTextRect) << endl;
    
    setContentBoxWidth(displayStringBoundingBox.width); // should always be 0,0
    setContentBoxHeight(displayStringBoundingBox.height); // should always be 0,0
    setHitBox(getContentBox()); // the whole thing

    //TODO PARENT NEEDS LAYOUT UPDATE WHEN LABEL PROPOERTIES ARE SET DURING SETUP
    //setParentNeedsLayoutUpdate(true);
}

//--------------------------------------------------------------
void breakLines(const ofxGuiLabelLineBreakMode lineBreakMode, 
                const ofxGuiAlign hAlign,
                const ofxGuiAlign vAlign,
                string& s, 
                const string truncationString,
                float targetWidth,
                float targetHeight, 
                int maxLines) {
    // does nothing yet.
    // ideally it should be a part of the truetype font class
    // just returns the oritginal string.
    // but will do amazing things one day.
}

//--------------------------------------------------------------
void ofxGuiLabel::breakSingleLine(const ofxGuiLabelLineBreakMode lineBreakMode, 
                            string& s, 
                            const string truncationString,
                            float targetWidth, 
                            int& truncationIndex) {
// does nothing yet.
// just returns the oritginal string.
// but will do amazing things one day.

// there is probably a smart way to find the breaks quickly 
// (rather than cycling through the entire string)
// http://www.fredosaurus.com/notes-cpp/algorithms/searching/binarysearch.html
}

//--------------------------------------------------------------
void ofxGuiLabel::buildFromXml()
{
	//props->mListener->handleGui(mParamId, kofxGui_Set_Bool, &value, sizeof(bool));
}

//--------------------------------------------------------------
void ofxGuiLabel::saveToXml()
{
	//int		id		= saveObjectData();
	//bool	value	= (buttonType == TYPE_TRIGGER) ? false : (value == true);
    
	//props->mXml.setValue("OBJECT:VALUE", value, id);
}






