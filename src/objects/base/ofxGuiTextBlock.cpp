//
//  ofxGuiLabel.cpp
//  emptyExample
//
//  Created by Christopher Baker on 7/11/11.
//  Copyright 2011 Kitchen Budapest. All rights reserved.
//

#include "ofxGuiTextBlock.h"

//--------------------------------------------------------------
ofxGuiTextBlock::ofxGuiTextBlock(ofxGuiTrueTypeFont* _font) {
    font = _font;
    text = "";
    blockWidth  = numeric_limits<float>::max();
    blockHeight = numeric_limits<float>::max();
    init();
}
//--------------------------------------------------------------
ofxGuiTextBlock::ofxGuiTextBlock(ofxGuiTrueTypeFont* _font, string _text) {
    font = _font;
    text = _text;
    blockWidth  = numeric_limits<float>::max();
    blockHeight = numeric_limits<float>::max();
    init();
}
//--------------------------------------------------------------
ofxGuiTextBlock::ofxGuiTextBlock(ofxGuiTrueTypeFont* _font, string _text, float _width) {
    font = _font;
    text = _text;
    blockWidth  = _width;
    blockHeight = numeric_limits<float>::max();
    init();
}
//--------------------------------------------------------------
ofxGuiTextBlock::ofxGuiTextBlock(ofxGuiTrueTypeFont* _font, string _text, float _width, float _height) {
    font = _font;
    text = _text;
    blockWidth  = _width;
    blockHeight = _height;
    init();
}

//--------------------------------------------------------------
ofxGuiTextBlock::~ofxGuiTextBlock() {
    
}

//--------------------------------------------------------------
void ofxGuiTextBlock::init() {

    debug = true;
    
    displayLines.push_back(text);
    
    orientation = OF_ORIENTATION_DEFAULT;
    
    capsStyle = LABEL_CAPS_NONE;
    
    cursorPosition = 0.0f;
    widthAtCursor = 0.0f;

    lineBreakMode = LINE_BREAK_MODE_NONE;
    truncationMode = LINE_TRUNCATION_MODE_CLIP;
    
    truncationString = "...";
    
    needsUpdate = true;
    
    maximumLines = numeric_limits<int>::max();
    
    cTextColor = ofColor(255,255,255); // just white
}

//--------------------------------------------------------------
void ofxGuiTextBlock::setTextColor(ofColor _cText) {
    cTextColor = _cText;
}

//--------------------------------------------------------------
ofColor ofxGuiTextBlock::getTextColor() {
    return cTextColor;
}

//--------------------------------------------------------------
void ofxGuiTextBlock::update() {
    
    if(needsUpdate) {
    
        displayText = text;

        applyCaps(displayText,capsStyle);
        
        ofRectangle goalBox(0,0,getTextWidth(),getTextHeight());
        float wrappedWidth = 0;
        float wrappedHeight = 0;
        vector<string> lines;
        vector<int> breakPos;
        vector<ofVec2f> charPos;
        vector<float> lineWidths;
        ofRectangle boundingBox;
        string delimiters = " ";
        
      
        
        breakLines(font,
                   displayText,
                   breakPos,
                   charPos,
                   lineWidths,
                   lines,
                   boundingBox,
                   goalBox,
                   lineBreakMode,
                   delimiters,
                   truncationMode,
                   truncationString);
        
        
        string::iterator begin = displayText.begin();
        vector<int>::iterator bpBegin = breakPos.begin();
        vector<int>::iterator bpIt = breakPos.begin();
        vector<int>::iterator bpEnd = breakPos.end();
        
        while(bpIt != bpEnd) {
            //int i = *bpIt;
            displayText.insert(*bpIt,"\n");
            ++bpIt;
        }
        
        //cout << "lines=" << lines.size() << endl;
        
        
        /*
        applyLineTruncationMode(font, 
                              displayText, 
                              sWidth, 
                              getTextWidth(), 
                              lineBreakMode, 
                              truncationString);
         */
        
       
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
            
            //string testString = displayText;
        }
         */
        
       // displayStringBoundingBox =  font->getStringBoundingBox(displayText,0,0);
        
            
        
        //cout << "display text rect for (displayText)=>" << displayText << "<| " << ofxGuiRectUtils::toString(&displayTextRect) << endl;
        
        /*
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
         */
        
        
        //cout << "display text rect: " << ofxGuiRectUtils::toString(&displayTextRect) << endl;
        
       // setContentBoxWidth(displayStringBoundingBox.width); // should always be 0,0
        //setContentBoxHeight(displayStringBoundingBox.height); // should always be 0,0
       // setHitBox(getContentBox()); // the whole thing
        
        //TODO PARENT NEEDS LAYOUT UPDATE WHEN LABEL PROPOERTIES ARE SET DURING SETUP
        //setParentNeedsLayoutUpdate(true);
        
    }

    needsUpdate = false; // just did it!
}

//--------------------------------------------------------------
void ofxGuiTextBlock::draw(float x, float y) {
    
    ofPushStyle();
    ofPushMatrix();
    ofTranslate(x,y);
    {        
        
        if(debug) {
            ofSetColor(255,255,0);
            ofLine(0,0,0,ofGetHeight());
            ofLine(0,0,ofGetWidth(),0);
            
            ofPushStyle();
            if(isTextWidthLimited()) {
                ofSetColor(255,0,0);
                ofLine(getBlockWidth(),0,getBlockWidth(),ofGetHeight());
            } 
            if(isTextHeightLimited()) {
                ofSetColor(255,0,0);
                ofLine(0,getBlockHeight(),ofGetWidth(),getBlockHeight());
            }
            ofPopStyle();
        }
        
        ofTranslate(0,font->getSize());

        ofSetColor(cTextColor);
        font->drawString(displayText,0,0);
    
        
        /*
         
         if(!displayText.empty()) {
         ofSetColor(cTextColor);
         
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
         ofTranslate(font->getSize(), 
         getTextBoxHeight());
         ofRotateZ(-90);
         break;
         }
         
         //font->drawString(displayText,drawOffsets.x,drawOffsets.y);
         ofPopMatrix();
         }
         */
        
    }
    ofPopMatrix();
    ofPopStyle();
}

//--------------------------------------------------------------
void ofxGuiTextBlock::draw() {
    draw(0,0);
}

//--------------------------------------------------------------
void ofxGuiTextBlock::setText(string _text) {
    if(text.compare(_text) != 0) {
        text = _text;
        displayText = _text;
        needsUpdate = true;
    }
}

//--------------------------------------------------------------
string ofxGuiTextBlock::getText() {
    return text;
}

//--------------------------------------------------------------
void ofxGuiTextBlock::insert(string s, int position) {
    // TODO, update from position
    if(position > text.length()) {
        ofLogError("ofxGuiTextBlock::insert: out of range.");
        return;
    }
    text.insert(position, s);
    needsUpdate = true;
}
//--------------------------------------------------------------
void ofxGuiTextBlock::append(string s) {
    // TODO, update from position
    text += s;
    needsUpdate = true;
}
//--------------------------------------------------------------
void ofxGuiTextBlock::prepend(string s) {
    // TODO, update from position
    text = s + text;
    needsUpdate = true;
}

//--------------------------------------------------------------
string ofxGuiTextBlock::getDisplayText() {
    return displayText;
}

//--------------------------------------------------------------
string ofxGuiTextBlock::getDisplayTextLine(int lineNumber) {
    if(lineNumber > getNumLines() - 1) {
        ofLogError("ofxGuiTextBlock::getDisplayText() requested a display text line that doesn't exist.");
    }
    
    return displayLines[lineNumber];
}

//--------------------------------------------------------------
vector<string> ofxGuiTextBlock::getDisplayTextLines() {
    return displayLines;
}

//--------------------------------------------------------------
void ofxGuiTextBlock::setFont(ofxGuiTrueTypeFont* _font) {
    font = _font;
    needsUpdate = true;
}

//--------------------------------------------------------------
void ofxGuiTextBlock::setCapsStyle(ofxGuiCapsMode _capsStyle) {
    if(capsStyle != _capsStyle) {
        capsStyle = _capsStyle;
        needsUpdate = true;
    }
}

//--------------------------------------------------------------
ofxGuiCapsMode ofxGuiTextBlock::getCapsStyle() { 
    return capsStyle;
}

//--------------------------------------------------------------
void ofxGuiTextBlock::setLineBreakMode(ofxGuiLineBreakMode _lineBreakMode) {
    if(lineBreakMode != _lineBreakMode) {
        lineBreakMode = _lineBreakMode;
        needsUpdate = true;
    }
}

//--------------------------------------------------------------
ofxGuiLineBreakMode ofxGuiTextBlock::getLineBreakMode() {
    return lineBreakMode;
}

//--------------------------------------------------------------
void ofxGuiTextBlock::setTruncationString(string _truncationString) {
    if(truncationString.compare(_truncationString) != 0) {
        truncationString = _truncationString;
        needsUpdate = true;
    }
}

//--------------------------------------------------------------
string ofxGuiTextBlock::getTruncationString() {
    return truncationString;
}

//--------------------------------------------------------------
void ofxGuiTextBlock::setLineTruncationMode(ofxGuiLineTruncationMode _lineTruncationMode) {
    if(truncationMode != _lineTruncationMode) {
        truncationMode = _lineTruncationMode;
        needsUpdate = true;
    }
}

//--------------------------------------------------------------
ofxGuiLineTruncationMode ofxGuiTextBlock::getLineTruncationMode() {
    return truncationMode;
}

//--------------------------------------------------------------
void ofxGuiTextBlock::setHorizontalAlignment(ofxGuiAlign _hAlign) {
    if(_hAlign != hAlign) {
        hAlign = _hAlign;
        needsUpdate = true;
    }
}

//--------------------------------------------------------------
void ofxGuiTextBlock::setVerticalAlignment(ofxGuiAlign _vAlign) {
    if(_vAlign != vAlign) {
        vAlign = _vAlign;
        needsUpdate = true;
    }
}

//--------------------------------------------------------------
ofxGuiAlign ofxGuiTextBlock::getVerticalAlign() {
    return vAlign;
}
//--------------------------------------------------------------
ofxGuiAlign ofxGuiTextBlock::getHorizontalAlignment() {
    return hAlign;
}

//--------------------------------------------------------------
void ofxGuiTextBlock::setOrientation(ofOrientation _orientation) {
    if(_orientation != orientation) {
        orientation = _orientation;
        needsUpdate = true;
    }
}
//--------------------------------------------------------------
ofOrientation ofxGuiTextBlock::getOrientation() {
    return orientation;
}

//--------------------------------------------------------------
bool ofxGuiTextBlock::allowMultipleLines() {
    
    if(maximumLines > 0) {
        switch (lineBreakMode) {
            case LINE_BREAK_MODE_NONE:
                return false;
            case LINE_BREAK_MODE_WORD:
            case LINE_BREAK_MODE_CHARACTER:
                return true;
        }
    } else {
        return false;
    }
}

//--------------------------------------------------------------
void ofxGuiTextBlock::setBlockWidth(float _width) {
    if(_width != blockWidth) {
        blockWidth = _width;
        needsUpdate = true;
    }
}
//--------------------------------------------------------------
void ofxGuiTextBlock::setBlockHeight(float _height) {
    if(_height != blockHeight) {
        blockHeight = _height;
        needsUpdate = true;
    }
}

//--------------------------------------------------------------
void ofxGuiTextBlock::clearBlockWidth() {
    if(blockWidth != numeric_limits<float>::max()) {
        blockWidth = numeric_limits<float>::max();
        needsUpdate = true;
    }
}
//--------------------------------------------------------------
void ofxGuiTextBlock::clearBlockHeight() {
    if(blockHeight != numeric_limits<float>::max()) {
        blockHeight = numeric_limits<float>::max();
        needsUpdate = true;
    }
}

//--------------------------------------------------------------
float ofxGuiTextBlock::getBlockWidth() {
    return blockWidth;
}
//--------------------------------------------------------------
float ofxGuiTextBlock::getBlockHeight() {
    return blockHeight;
}


//--------------------------------------------------------------
float ofxGuiTextBlock::getTextWidth() {
    if(isTextHorizontal()) {
        return getBlockWidth();
    } else {
        return getBlockHeight();
    }
}

//--------------------------------------------------------------
float ofxGuiTextBlock::getTextHeight() {
    if(isTextHorizontal()) {
        return getBlockHeight();
    } else {
        return getBlockWidth();
    }
}

//--------------------------------------------------------------
int ofxGuiTextBlock::getNumLines() {
    return (int)displayLines.size();
}

//--------------------------------------------------------------
void ofxGuiTextBlock::setMaximumLines(int _numLines) {
    if(maximumLines != _numLines) {
        maximumLines = _numLines;
        needsUpdate = true;
    }
}

//--------------------------------------------------------------
int ofxGuiTextBlock::getMaximumLines() {
    return maximumLines;
}

//--------------------------------------------------------------
void ofxGuiTextBlock::clearMaximumLines() {
    if(maximumLines != numeric_limits<int>::max()) {
        maximumLines = numeric_limits<int>::max();
        needsUpdate = true;
    }
}
       
       
//--------------------------------------------------------------
bool ofxGuiTextBlock::empty() {
    return text.empty();
}

//--------------------------------------------------------------
bool ofxGuiTextBlock::isTextHorizontal() {
    switch(orientation) {
        case OF_ORIENTATION_UNKNOWN:
        case OF_ORIENTATION_DEFAULT:
        case OF_ORIENTATION_180:
            return true;
        case OF_ORIENTATION_90_RIGHT:
        case OF_ORIENTATION_90_LEFT:
            return false;
    }
}

//--------------------------------------------------------------
bool ofxGuiTextBlock::isTextVertical() {
    return !isTextHorizontal();
}

//--------------------------------------------------------------
bool ofxGuiTextBlock::isTextWidthLimited() {
    return blockWidth != numeric_limits<float>::max();
}
//--------------------------------------------------------------
bool ofxGuiTextBlock::isTextHeightLimited() {
    return blockHeight != numeric_limits<float>::max();
}





