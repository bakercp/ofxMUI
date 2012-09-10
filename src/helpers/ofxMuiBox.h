//
//  ofxMuiBox.h
//  emptyExample
//
//  Created by Christopher P. Baker on 7/11/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once

#include "ofMain.h"
#include "ofxMuiConstants.h"
#include "ofxMuiRange.h"
#include "ofxMuiBoxProperties.h"
#include "ofxRectangleUtils.h"


enum ofxMuiBoxCoordinates {
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
class ofxMuiBox : public ofRectangle, public ofxMuiBoxProperties {
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
    
    ofxMuiBox(ofRectangle _rect);
    ofxMuiBox(float _x, float _y, float _w, float _h);
    ofxMuiBox(float _x, float _y);
    ofxMuiBox();

    virtual ~ofxMuiBox();
    
    //--------------------------------------------------------------
    // CUSTOM DRAWING //////////////////////////////////////////////
    //--------------------------------------------------------------
    void ofxRect(const ofRectangle & r, bool inner = true);  
    void ofxRect(float x, float y, float width, float height, bool inner = true);
    void ofxFrame(float x, float y, float width, float height, ofxMuiBoxPropertyQuad frameProperties);

    //--------------------------------------------------------------
    // GUI BOX /////////////////////////////////////////////////////
    //--------------------------------------------------------------
    
    ofRectangle getBox();
    
    bool insideBox(const ofPoint& _point) const;
    
    // this is relative to the enclosing content box or screen
    
//    void setPosition(float _x, float _y, bool _updateParent = false);
//    void setX(float _x, bool _updateParent = false);
//    void setY(float _y, bool _updateParent = false);

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
    virtual float getWidth() const;
    virtual float getHeight() const;

    void setFixedWidth(bool _fixedWidth);
    void setFixedHeight(bool _fixedHeight);
    
    bool isFixedWidth() const;
    bool isFixedHeight() const;
    
    //--------------------------------------------------------------
    // BORDER BOX //////////////////////////////////////////////////
    //--------------------------------------------------------------
    
    // all are relative to the box position
    // i.e. getBorderBox().x == getBorderOffset().x
    ofRectangle getBorderBox() const;
    ofVec2f     getBorderBoxOffset() const;
    float       getBorderBoxSideOffset(const ofxMuiBoxSide& side) const;
    float       getBorderBoxWidth() const;
    float       getBorderBoxHeight() const;
    
    float       getBorderBoxHalfWidth() const;
    float       getBorderBoxHalfHeight() const;
    ofVec2f     getBorderBoxCenter() const;
    float       getBorderBoxCenterX() const;
    float       getBorderBoxCenterY() const;
    
    bool        insideBorderBox(const ofPoint& _point) const;
    
    //--------------------------------------------------------------
    // PADDING BOX /////////////////////////////////////////////////
    //--------------------------------------------------------------
    
    ofRectangle getPaddingBox() const;
    ofVec2f     getPaddingBoxOffset() const;
    float       getPaddingBoxSideOffset(const ofxMuiBoxSide& side) const;
    float       getPaddingBoxWidth() const;
    float       getPaddingBoxHeight() const;

    float       getPaddingBoxHalfWidth() const;
    float       getPaddingBoxHalfHeight() const;
    ofVec2f     getPaddingBoxCenter() const;
    float       getPaddingBoxCenterX() const;
    float       getPaddingBoxCenterY() const;

    
    bool        insidePaddingBox(const ofPoint& _point) const;
    
    //--------------------------------------------------------------
    // CONTENT BOX /////////////////////////////////////////////////
    //--------------------------------------------------------------

    ofRectangle  getContentBox() const;
    ofRectangle& getContentBoxRef();
    ofVec2f      getContentBoxOffset() const;
    
    float       getContentBoxSideOffset(const ofxMuiBoxSide& side) const;

    float       getContentBoxWidth() const;
    float       getContentBoxHeight() const;

    float       getContentBoxHalfWidth() const;
    float       getContentBoxHalfHeight() const;
    ofVec2f     getContentBoxCenter() const;
    float       getContentBoxCenterX() const;
    float       getContentBoxCenterY() const;

    void        setContentBoxWidth(float _width);
    void        setContentBoxHeight(float _height);
    
    //bool        insideContentBox(ofPoint _point);

    // for setting the content box when the width and/or height are fixed
    float getMaxAllowableContentBoxWidth() const;
    float getMaxAllowableContentBoxHeight() const;
    
    //--------------------------------------------------------------
    // HIT BOX //////////////////////////////////////////////////
    //--------------------------------------------------------------

    ofRectangle  getHitBox() const;
    ofRectangle& getHitBoxRef();
    ofVec2f      getHitBoxOffset() const;
    
    ofVec2f     getHitBoxPosition() const;
    float       getHitBoxX() const;
    float       getHitBoxY() const;
    float       getHitBoxWidth() const;
    float       getHitBoxHeight() const;
    
    float       getHitBoxHalfWidth() const;
    float       getHitBoxHalfHeight() const;
    ofVec2f     getHitBoxCenter() const;
    float       getHitBoxCenterX() const;
    float       getHitBoxCenterY() const;
    
    // TODO we don't constrain this hit area (width/height) to the content box
    // when the box width/height are fixed ...  this affects
    // the hit test and any subclassed hit tests.  thus, a hit
    // is no GUARANTEED to be inside the content box ... but we can hope 
    void        setHitBox(const ofRectangle& _rect);
    void        setHitBox(float _x, float _y, float _width, float _height);
    void        setHitBoxX(float _x);
    void        setHitBoxY(float _y);
    void        setHitBoxWidth(float _width);
    void        setHitBoxHeight(float _height);
    
    //bool        insideHitBox(ofPoint _point);
    
    bool        isCustomHitBox() const;
    
    //--------------------------------------------------------------
    // SCREEN MAPPING //////////////////////////////////////////////
    //--------------------------------------------------------------
    
    ofVec2f screenToBox(const ofVec2f& p) const;
    ofVec2f screenToBorderBox(const ofVec2f& p) const;
    ofVec2f screenToPaddingBox(const ofVec2f& p) const;
    ofVec2f screenToContentBox(const ofVec2f& p) const;
    ofVec2f screenToHitBox(const ofVec2f& p) const;
    
    // virtual to respect parent
    virtual ofVec2f getBoxScreenPosition() const;
    ofVec2f getBorderScreenPosition() const;
    ofVec2f getPaddingScreenPosition() const;
    ofVec2f getContentScreenPosition() const;
    ofVec2f getHitBoxScreenPosition() const;
    
    //--------------------------------------------------------------
    // THE HIT TEST ////////////////////////////////////////////////
    //--------------------------------------------------------------

    // returns > 0 if given (x, y) coordinates (in content box space) 
    // are over any the hit box.

    // this can be overriden in subclasses to use something other
    // than the hitbox for more complex mouse handling.
    
    // this will not be called if the click is not in the content box 
    
    bool hitTest(const ofPoint& contentBoxX) const;
    virtual bool hitTest(float contentBoxX, float contentBoxY) const;
    
    //--------------------------------------------------------------
    // LAYOUT //////////////////////////////////////////////////////
    //--------------------------------------------------------------

    // during auto layout flow times, this will manage new-line 
    // enforcement
    void setNeedsNewLine(bool _needsNewLine);
    bool getNeedsNewLine() const;
    
    void setParentNeedsLayoutUpdate(bool _parentNeedsLayout = true);
    bool getParentNeedsLayoutUpdate() const;
    
    void setNeedsLayoutUpdate(bool _needsLayout = true);
    bool getNeedsLayoutUpdate() const;
    
    void requestBoxLayout();
    
    // virtual bool hasParent() { return false; }
    
    void doLayout();
    

    // content alignment for fixt box situations
    void setContentAlignHorz(const ofAlignHorz& _hAlign);
    void setContentAlignVert(const ofAlignVert& _vAlign);
    
    ofAlignHorz getContentAlignHorz() const;
    ofAlignVert getContentAlignVert() const;

    
protected:
    // static members
   // static ofxMuiBoxProperties default_boxProps;
    
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

    
    ofxMuiRange xRange;
    ofxMuiRange yRange;
    
    ofAlignHorz hContentAlign;
    ofAlignVert vContentAlign;
    
};


