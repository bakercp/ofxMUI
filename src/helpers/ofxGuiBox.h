//
//  ofxGuiBox.h
//  emptyExample
//
//  Created by Christopher P. Baker on 7/11/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once

#include "ofMain.h"
#include "ofxGuiConstants.h"
#include "ofxGuiRange.h"
#include "ofxGuiBoxProperties.h"
#include "ofxGuiRectUtils.h"


enum ofxGuiBoxCoordinates {
    COORD_SCREEN = 0,
    COORD_BOX,
    COORD_BORDER_BOX,
    COORD_PADDING_BOX,
    COORD_CONTENT_BOX,
    COORD_HIT_BOX
};

// the base rectangle is protected, because we need to know when changes size
// the base box properties is not protected and any changes must be manually
// followed by a call to setNeedsLayoutUpdate().  perhaps
// there is a good way around this -- a callback in the box properties?
class ofxGuiBox : protected ofRectangle, public ofxGuiBoxProperties {
public:

    // THE GUI BOX!
    //   __________________________________________________________
    //  |BOX - RENDERED AS A FILLED QUAD                           |
    //  |   CORNER CAN BE ANYWHERE INSIDE OF PARENT                |
    //  |   (SCREEN OR PANEL OR OBJECT                             |
    //  |    ____________________________________________________  |
    //  | M |BORDER BOX - RENDERED AS A FRAME                    | |
    //  | A |   CORNER ALWAYS @ 0,0                              | |
    //  | A |                                                    | |
    //  | R | B                                                  | |
    //  | G | O     __________________________________________   | |
    //  | I | R    |PADDING BOX - RENDERED AS A FILLED QUAD   |  | |
    //  | N | D    |  CORNER ALWAYS @ 0,0                     |  | |
    //  | N | D    |                                          |  | |
    //  |   | E    | P   ___________________________________  |  | |
    //  |   | R    | A  |CONTENT BOX - RENDERD BY OBJECT   |  |  | |
    //  |   |      | D  |                                  |  |  | |
    //  |   |      | D  |  CORNER ALWAYS @ 0,0             |  |  | |
    //  |   |      | I  |                                  |  |  | |
    //  |   |      | N  |     ___________________________  |  |  | |
    //  |   |      | G  |    |                           | |  |  | |
    //  |   |      |    |    |  CORNER CAN BE ANYWHERE   | |  |  | |
    //  |   |      |    |    |  INSIDE THE CONTENT BOX   | |  |  | |
    //  |   |      |    |    |                           | |  |  | |
    //  |   |      |    |    |  HIT BOX -                | |  |  | |
    //  |   |      |    |    |  RENDERED BY OBJECT       | |  |  | |
    //  |   |      |    |    |  This is the "hot" zone"  | |  |  | |
    //  |   |      |    |    |  It can live anywhere in  | |  |  | |
    //  |   |      |    |    |  the content box.         | |  |  | |
    //  |   |      |    |    |                           | |  |  | |
    //  |   |      |    |    |  The hitbox is            | |  |  | |
    //  |   |      |    |    |  optional.  If it is      | |  |  | |
    //  |   |      |    |    |  NULL reference, then     | |  |  | |
    //  |   |      |    |    |  it is undefined and the  | |  |  | |
    //  |   |      |    |    |  entire content box is    | |  |  | |
    //  |   |      |    |    |  treated as the hit area. | |  |  | |
    //  |   |      |    |    |                           | |  |  | |
    //  |   |      |    |    |  The content box will     | |  |  | |
    //  |   |      |    |    |  also contain any child   | |  |  | |
    //  |   |      |    |    |  elements and their       | |  |  | |
    //  |   |      |    |    |  inside gui boxes.        | |  |  | |
    //  |   |      |    |    |___________________________| |  |  | |
    //  |   |      |    |                                  |  |  | |
    //  |   |      |    |__________________________________|  |  | |
    //  |   |      |                                          |  | |
    //  |   |      |                                          |  | |
    //  |   |      |__________________________________________|  | |
    //  |   |                                                    | |
    //  |   |____________________________________________________| |
    //  |__________________________________________________________|
    //

    //--------------------------------------------------------------
    // CONSTRUCT/DESTRUCT //////////////////////////////////////////
    //--------------------------------------------------------------
    
    ofxGuiBox(ofRectangle _rect);
    ofxGuiBox(float _x, float _y, float _w, float _h);
    ofxGuiBox(float _x, float _y);
    ofxGuiBox();

    virtual ~ofxGuiBox();
    
    //--------------------------------------------------------------
    // CUSTOM DRAWING //////////////////////////////////////////////
    //--------------------------------------------------------------
    void ofxRect(const ofRectangle & r, bool inner = true);  
    void ofxRect(float x, float y, float width, float height, bool inner = true);
    void ofxFrame(float x, float y, float width, float height, ofxGuiBoxPropertyQuad frameProperties);

    //--------------------------------------------------------------
    // GUI BOX /////////////////////////////////////////////////////
    //--------------------------------------------------------------
    
    ofRectangle getBox();
    ofVec2f     getPosition();
    
    bool        insideBox(ofPoint _point);
    
    // this is relative to the enclosing content box or screen
    
    void set(ofRectangle const & rect);
    void set (float px, float py, float w, float h);
    void set (ofPoint pos, float w, float h);
    void setFromCenter (float px, float py, float w, float h);
    void setFromCenter (ofPoint pos, float w, float h);

    void setPosition(float _x, float _y, bool _updateParent = false);
    void setX(float _x, bool _updateParent = false);
    void setY(float _y, bool _updateParent = false);
    
    void addX(float _dx);
    void addY(float _dy);
    
    float  getX();
    float  getY();
    
    float  getX1();
    float  getY1();

    float  getLeft();
    float  getTop();
    float  getRight();
    float  getBottom();
        
    float  getCenterX();
    float  getCenterY();
    
    float  getHalfWidth();
    float  getHalfHeight();
    
    ofPoint getCenter();
    
    ofVec2f getMaxBounds();
    ofVec2f getMinBounds();
    float   getMaxX();
    float   getMaxY();
    float   getMinX();
    float   getMinY();
    void setMinBounds(ofVec2f _minBounds);
    void setMaxBounds(ofVec2f _maxBounds);
    void setMaxX(float _maxX);
    void setMaxY(float _maxY);
    void setMinX(float _minX);
    void setMinY(float _minY);
    
    void setBoundsX(float minX, float maxX);
    void setBoundsY(float minY, float maxY);
    
    void clearBounds();
    void clearMaxBounds();
    void clearMinBounds();
    void clearMaxX();
    void clearMaxY();
    void clearMinX();
    void clearMinY();
    
    // by explicitly setting width or height, it is implied that
    // you want a fixed width and / or fixed height.
    
    
    
    void setWidth(float _width);
    void setHeight(float _height);
    
    // sometimes objects need to be able to report a zero w/h
    // if there is nothing in them (i.e. label);
    virtual float getWidth();
    virtual float getHeight();

    void setFixedWidth(bool _fixedWidth);
    void setFixedHeight(bool _fixedHeight);
    
    bool isFixedWidth();
    bool isFixedHeight();
    
    //--------------------------------------------------------------
    // BORDER BOX //////////////////////////////////////////////////
    //--------------------------------------------------------------
    
    // all are relative to the box position
    // i.e. getBorderBox().x == getBorderOffset().x
    ofRectangle getBorderBox();
    ofVec2f     getBorderBoxOffset();
    float       getBorderBoxSideOffset(ofxGuiBoxSide side);
    float       getBorderBoxWidth();
    float       getBorderBoxHeight();
    
    float       getBorderBoxHalfWidth();
    float       getBorderBoxHalfHeight();
    ofVec2f     getBorderBoxCenter();
    float       getBorderBoxCenterX();
    float       getBorderBoxCenterY();
    
    bool        insideBorderBox(ofPoint _point);
    
    //--------------------------------------------------------------
    // PADDING BOX /////////////////////////////////////////////////
    //--------------------------------------------------------------
    
    ofRectangle getPaddingBox();
    ofVec2f     getPaddingBoxOffset();
    float       getPaddingBoxSideOffset(ofxGuiBoxSide side);
    float       getPaddingBoxWidth();
    float       getPaddingBoxHeight();

    float       getPaddingBoxHalfWidth();
    float       getPaddingBoxHalfHeight();
    ofVec2f     getPaddingBoxCenter();
    float       getPaddingBoxCenterX();
    float       getPaddingBoxCenterY();

    
    bool        insidePaddingBox(ofPoint _point);
    
    //--------------------------------------------------------------
    // CONTENT BOX /////////////////////////////////////////////////
    //--------------------------------------------------------------

    ofRectangle getContentBox();
    ofRectangle* getContentBoxRef();
    ofVec2f     getContentBoxOffset();
    
    float       getContentBoxSideOffset(ofxGuiBoxSide side);

    float       getContentBoxWidth();
    float       getContentBoxHeight();

    float       getContentBoxHalfWidth();
    float       getContentBoxHalfHeight();
    ofVec2f     getContentBoxCenter();
    float       getContentBoxCenterX();
    float       getContentBoxCenterY();

    void        setContentBoxWidth(float _width);
    void        setContentBoxHeight(float _height);
    
    //bool        insideContentBox(ofPoint _point);

    // for setting the content box when the width and/or height are fixed
    float getMaxAllowableContentBoxWidth();
    float getMaxAllowableContentBoxHeight();
    
    //--------------------------------------------------------------
    // HIT BOX //////////////////////////////////////////////////
    //--------------------------------------------------------------

    ofRectangle  getHitBox();
    ofRectangle* getHitBoxRef();
    ofVec2f     getHitBoxOffset();
    
    ofVec2f     getHitBoxPosition();
    float       getHitBoxX();
    float       getHitBoxY();
    float       getHitBoxWidth();
    float       getHitBoxHeight();
    
    float       getHitBoxHalfWidth();
    float       getHitBoxHalfHeight();
    ofVec2f     getHitBoxCenter();
    float       getHitBoxCenterX();
    float       getHitBoxCenterY();
    
    // TODO we don't constrain this hit area (width/height) to the content box
    // when the box width/height are fixed ...  this affects
    // the hit test and any subclassed hit tests.  thus, a hit
    // is no GUARANTEED to be inside the content box ... but we can hope 
    void        setHitBox(ofRectangle _rect);
    void        setHitBox(float _x, float _y, float _width, float _height);
    void        setHitBoxX(float _x);
    void        setHitBoxY(float _y);
    void        setHitBoxWidth(float _width);
    void        setHitBoxHeight(float _height);
    
    //bool        insideHitBox(ofPoint _point);
    
    bool        isCustomHitBox();
    
    //--------------------------------------------------------------
    // SCREEN MAPPING //////////////////////////////////////////////
    //--------------------------------------------------------------
    
    ofVec2f screenToBox(ofVec2f p);
    ofVec2f screenToBorderBox(ofVec2f p);
    ofVec2f screenToPaddingBox(ofVec2f p);
    ofVec2f screenToContentBox(ofVec2f p);
    ofVec2f screenToHitBox(ofVec2f p);
    
    // virtual to respect parent
    virtual ofVec2f getBoxScreenPosition();
    ofVec2f getBorderScreenPosition();    
    ofVec2f getPaddingScreenPosition();
    ofVec2f getContentScreenPosition();
    ofVec2f getHitBoxScreenPosition();
    
    //--------------------------------------------------------------
    // THE HIT TEST ////////////////////////////////////////////////
    //--------------------------------------------------------------

    // returns > 0 if given (x, y) coordinates (in content box space) 
    // are over any the hit box.

    // this can be overriden in subclasses to use something other
    // than the hitbox for more complex mouse handling.
    
    // this will not be called if the click is not in the content box 
    
    bool hitTest(ofPoint contentBoxX);
    virtual bool hitTest(float contentBoxX, float contentBoxY);
    
    //--------------------------------------------------------------
    // LAYOUT //////////////////////////////////////////////////////
    //--------------------------------------------------------------

    // during auto layout flow times, this will manage new-line 
    // enforcement
    void setNeedsNewLine(bool _needsNewLine);
    bool getNeedsNewLine();
    
    void setParentNeedsLayoutUpdate(bool _parentNeedsLayout = true);
    bool getParentNeedsLayoutUpdate();
    
    void setNeedsLayoutUpdate(bool _needsLayout = true);
    bool getNeedsLayoutUpdate();
    
    void requestBoxLayout();
    
    // virtual bool hasParent() { return false; }
    
    void doLayout();
    

    // content alignment for fixt box situations
    void setHorizontalAlign(ofxGuiAlign _hAlign);
    void setVerticalAlign(ofxGuiAlign _vAlign);
    
    ofxGuiAlign getHorizontalAlign();
    ofxGuiAlign getVerticalAlign();

    
protected:
    // static members
   // static ofxGuiBoxProperties default_boxProps;
    
    void checkBounds();
    void checkBoundsX();
    void checkBoundsY();
    
    // auto layout
    bool fixedWidth;
    bool fixedHeight;
    
    //      The hitbox is always defined in terms of its 
    //      offset from the content box.

    bool needsNewLine;
    
    bool needsLayout;
    bool parentNeedsLayout;
    
    // each object must do its own content box layout
    virtual void doContentBoxLayout() {};
    
    bool isLayoutSetupComplete;
    
private:
    
    ofRectangle contentBox;

    bool hasCustomHitBox;
    ofRectangle hitBox;

    
    ofxGuiRange xRange;
    ofxGuiRange yRange;
    
    ofxGuiAlign hContentAlign;
    ofxGuiAlign vContentAlign;
    
};


