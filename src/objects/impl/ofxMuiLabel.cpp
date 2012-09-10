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

#include "ofxMuiLabel.h"


//--------------------------------------------------------------
ofxMuiLabel::ofxMuiLabel(const string& _name, 
                         int _x, 
                         int _y, 
                         int _width, 
                         int _height, 
                         bool _enabled) : 
    ofxMuiObject(_name, 
                 _x, 
                 _y, 
                 _width, 
                 _height, 
                 _enabled) {
    init();
}
//--------------------------------------------------------------
ofxMuiLabel::ofxMuiLabel(const string& _name, 
                         int _x, 
                         int _y, 
                         bool _enabled) : 
    ofxMuiObject(_name, 
                 _x, 
                 _y, 
                 _enabled) {
    init();
}

ofxMuiLabel::ofxMuiLabel(const string& _name, 
                         bool _enabled) : 
    ofxMuiObject(_name, 
                 _enabled) {
    init();
}

ofxMuiLabel::ofxMuiLabel(bool _enabled) : 
    ofxMuiObject(_enabled) {
    init();
}

//--------------------------------------------------------------
ofxMuiLabel::~ofxMuiLabel() {
    
}

//--------------------------------------------------------------
void ofxMuiLabel::init() {
    
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

    truncationString = "...";
    
    isMultiline = false;
    
    requestBoxLayout();
}


//--------------------------------------------------------------
void ofxMuiLabel::draw() {
        
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
void ofxMuiLabel::setText(const string& _text) {
    text = _text;
    requestBoxLayout();
}

//--------------------------------------------------------------
string ofxMuiLabel::getText() const {
    return text;
}

//--------------------------------------------------------------
string ofxMuiLabel::getDisplayText() const {
    return displayText;
}

//--------------------------------------------------------------
void ofxMuiLabel::setFontSize(const ofxMuiSize& _labelSize) {
    labelSize = _labelSize;
    labelFont = defaults->getFont(_labelSize);
    requestBoxLayout();
}

//--------------------------------------------------------------
ofxMuiSize ofxMuiLabel::getFontSize() const {
    return labelSize;
}


//--------------------------------------------------------------
void ofxMuiLabel::setCapsStyle(const ofxMuiCapsMode& _capsStyle) {
    capsStyle = _capsStyle;
    requestBoxLayout();
}

//--------------------------------------------------------------
ofxMuiCapsMode ofxMuiLabel::getCapsStyle() const {
    return capsStyle;
}

//--------------------------------------------------------------
void ofxMuiLabel::setLineBreakMode(const ofxMuiLineBreakMode& _lineBreakMode) {
    lineBreakMode = _lineBreakMode;
    requestBoxLayout();
}

//--------------------------------------------------------------
ofxMuiLineBreakMode ofxMuiLabel::getLineBreakMode() const {
    return lineBreakMode;
}

//--------------------------------------------------------------
void ofxMuiLabel::setTruncationString(const string& _truncationString) {
    truncationString = _truncationString;
    requestBoxLayout();
}

//--------------------------------------------------------------
string ofxMuiLabel::getTruncationString() const {
    return truncationString;
}

//--------------------------------------------------------------
bool ofxMuiLabel::empty() const {
    return text.empty();
}

//--------------------------------------------------------------
void ofxMuiLabel::doContentBoxLayout() {
    
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
    
    /*
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
     */
    
    displayStringBoundingBox =  labelFont->getStringBoundingBox(displayText,0,0);

    
    
    //cout << "display text rect for (displayText)=>" << displayText << "<| " << ofxMuiRectUtils::toString(&displayTextRect) << endl;

    
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
    

    //cout << "display text rect: " << ofxMuiRectUtils::toString(&displayTextRect) << endl;
    
    setContentBoxWidth(displayStringBoundingBox.width); // should always be 0,0
    setContentBoxHeight(displayStringBoundingBox.height); // should always be 0,0
    setHitBox(getContentBox()); // the whole thing

    //TODO PARENT NEEDS LAYOUT UPDATE WHEN LABEL PROPOERTIES ARE SET DURING SETUP
    //setParentNeedsLayoutUpdate(true);
}

//--------------------------------------------------------------
void ofxMuiLabel::loadFromXml(ofxXmlSettings& xml)
{
	//props->mListener->handleGui(mParamId, kofxMui_Set_Bool, &value, sizeof(bool));
}

//--------------------------------------------------------------
void ofxMuiLabel::saveToXml(ofxXmlSettings& xml)
{
	//int		id		= saveObjectData();
	//bool	value	= (buttonType == TYPE_TRIGGER) ? false : (value == true);
    
	//props->mXml.setValue("OBJECT:VALUE", value, id);
}






