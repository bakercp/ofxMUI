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

#include "ofxMuiBox.h"

//--------------------------------------------------------------
// we explicitly set the frame size, and disallow auto adjusting
ofxMuiBox::ofxMuiBox(ofRectangle _rect) : 
    ofxMuiBoxProperties(),
    needsNewLine(true),
    needsLayout(false),
    parentNeedsLayout(false),
    isLayoutSetupComplete(false),
    hContentAlign(OF_ALIGN_HORZ_LEFT),
    vContentAlign(OF_ALIGN_VERT_TOP)
{
    set(_rect);
    hitBox = ofRectangle();
    contentBox = ofRectangle();
}

//--------------------------------------------------------------
ofxMuiBox::ofxMuiBox(float _x, float _y, float _w, float _h) : 
    ofxMuiBoxProperties(),
    needsNewLine(true),
    needsLayout(false),
    parentNeedsLayout(false),
    isLayoutSetupComplete(false),
    hContentAlign(OF_ALIGN_HORZ_LEFT),
    vContentAlign(OF_ALIGN_VERT_TOP)
{
    set(_x,_y,_w,_h);
    hitBox = ofRectangle();
    contentBox = ofRectangle();
}

//--------------------------------------------------------------
// we only set the frame position, and allow auto adjusting
ofxMuiBox::ofxMuiBox(float _x, float _y) : 
    ofxMuiBoxProperties(),
    needsNewLine(true),
	needsLayout(false),
    parentNeedsLayout(false),
    isLayoutSetupComplete(false),
    hContentAlign(OF_ALIGN_HORZ_LEFT),
    vContentAlign(OF_ALIGN_VERT_TOP)
{
    set(_x,_y,0,0);
    hitBox = ofRectangle();
    contentBox = ofRectangle();
}

//--------------------------------------------------------------
// we set nothing and allow auto adjusting
ofxMuiBox::ofxMuiBox() : 
    ofxMuiBoxProperties(),
    fixedWidth(false),
    fixedHeight(false),
    needsNewLine(true),
    needsLayout(false),
    parentNeedsLayout(false),
    isLayoutSetupComplete(false),
    hContentAlign(OF_ALIGN_HORZ_LEFT),
    vContentAlign(OF_ALIGN_VERT_TOP)
{
    set(ofRectangle(0,0,0,0));
    hitBox = ofRectangle();
    contentBox = ofRectangle();
}

//--------------------------------------------------------------
ofxMuiBox::~ofxMuiBox() {}

//----------------------------------------------------------
void ofxMuiBox::ofxRect(const ofRectangle & r, bool inner){
	ofxRect(r.x, r.y, r.width, r.height, inner);
}

//--------------------------------------------------------------
// TODO
// from : https://github.com/openframeworks/openFrameworks/issues/798
void ofxMuiBox::ofxRect(float _x, float _y, float _width, float _height, bool inner) {
    //ofRect(_x,_y,_width,_height);
    
    if(ofGetFill()) {
        ofRect(_x, _y, _width, _height);
    } else {
        if(inner) {
            ofRect(_x + .5, _y + .5, _width - 1, _height - 1);
        } else {
            ofRect(_x - .5, _y - .5, _width + 1, _height + 1);
        }
    }
    
}


//--------------------------------------------------------------
void ofxMuiBox::ofxFrame(float _x, float _y, float _width, float _height, ofxMuiBoxPropertyQuad quadProp) {
    
    ofPushMatrix();
    ofTranslate(_x,_y);
    
    float quadW = _width  - (quadProp.left + quadProp.right);
    float quadH = _height - (quadProp.top  + quadProp.bottom);
    
    // TODO: would like to integrate border radius ... but not easy to draw
    // arcs at the moment.   come back to this later ... with ofPolyline perhaps?
    
    // draw the object frame FRAME IF shown
    if(border.top > 0) {
        ofxRect(quadProp.left,
                0,
                quadW,
                quadProp.top
                );
        
        if(quadProp.left > 0) {
            // upper left corner piece
            ofxRect(0,0,quadProp.left,quadProp.top);
            //ofCircle(0,0,10);
        }
    }
    
    // draw the object frame FRAME IF shown
    if(quadProp.right > 0) {
        ofxRect(_width-quadProp.right,
                quadProp.top,
                quadProp.right,
                quadH
                );
        
        if(quadProp.top > 0) {
            // upper right corner piece
            ofxRect(_width-quadProp.right,0,quadProp.right,quadProp.top);
        }
    }
    
    // draw the object frame FRAME IF shown
    if(quadProp.bottom > 0) {
        ofxRect(quadProp.left,
                quadH+quadProp.top,
                quadW,
                quadProp.bottom
                );
        
        if(border.right > 0) {
            // upper right corner piece
            ofxRect(_width-quadProp.right,
                    quadH+quadProp.top,
                    quadProp.right,
                    quadProp.bottom);
        }
    }
    
    // draw the object frame FRAME IF shown
    if(quadProp.left > 0) {
        ofxRect(0,
                quadProp.top,
                quadProp.left,
                quadH
                );
        
        if(quadProp.bottom > 0) {
            ofxRect(0,
                    _height-quadProp.bottom,
                    quadProp.left,
                    quadProp.bottom);
        }
    }
    
    ofPopMatrix();
}






//--------------------------------------------------------------
ofRectangle ofxMuiBox::getBox() {
    return ofRectangle(*this);
}

////--------------------------------------------------------------
//void ofxMuiBox::setX(float _x, bool _updateParent) {
//    x = _x;
//    checkBoundsX();
//    setParentNeedsLayoutUpdate(_updateParent);
//}
//
////--------------------------------------------------------------
//void ofxMuiBox::setY(float _y, bool _updateParent) {
//    y = _y;
//    checkBoundsY();
//    setParentNeedsLayoutUpdate(_updateParent);
//}
//--------------------------------------------------------------
void ofxMuiBox::setMinBounds(ofVec2f _minBounds) {
    xRange.setMin(_minBounds.x);
    yRange.setMin(_minBounds.y);
    checkBounds();
}

//--------------------------------------------------------------
void ofxMuiBox::setMaxBounds(ofVec2f _maxBounds) {
    xRange.setMax(_maxBounds.x);
    yRange.setMax(_maxBounds.y);
    checkBounds();
}

//--------------------------------------------------------------
void ofxMuiBox::setMaxX(float _maxX) {
    xRange.setMax(_maxX);
    checkBoundsX();
}

//--------------------------------------------------------------
void ofxMuiBox::setMaxY(float _maxY) {
    yRange.setMax(_maxY);
    checkBoundsY();
}

//--------------------------------------------------------------
void ofxMuiBox::setMinX(float _minX) {
    xRange.setMin(_minX);
    checkBoundsX();
}

//--------------------------------------------------------------
void ofxMuiBox::setMinY(float _minY) {
    yRange.setMin(_minY);
    checkBoundsY();
}

//--------------------------------------------------------------
void ofxMuiBox::setBoundsX(float minX, float maxX) {
    xRange.setMin(minX);
    xRange.setMax(maxX);
    checkBoundsX();
}

//--------------------------------------------------------------
void ofxMuiBox::setBoundsY(float minY, float maxY) {
    yRange.setMin(minY);
    yRange.setMax(maxY);
    checkBoundsY();
}

//--------------------------------------------------------------
void ofxMuiBox::clearBounds() {
    clearMaxBounds();
    clearMinBounds();
}

//--------------------------------------------------------------
void ofxMuiBox::clearMaxBounds() {
    clearMaxX();
    clearMaxY();
}

//--------------------------------------------------------------
void ofxMuiBox::clearMinBounds() {
    clearMinX();
    clearMinY();
}

//--------------------------------------------------------------
void ofxMuiBox::clearMaxX() {
    xRange.clearMax();
    checkBoundsX();
}

//--------------------------------------------------------------
void ofxMuiBox::clearMaxY() {
    yRange.clearMax();
    checkBoundsY();
}

//--------------------------------------------------------------
void ofxMuiBox::clearMinX() {
    xRange.clearMin();
    checkBoundsX();
}

//--------------------------------------------------------------
void ofxMuiBox::clearMinY() {
    yRange.clearMin();
    checkBoundsY();
}

//--------------------------------------------------------------
void ofxMuiBox::setWidth(float _width) {
    if(_width >= 0) width = _width;
    fixedWidth = (width > 0);
    requestBoxLayout();
}

//--------------------------------------------------------------
void ofxMuiBox::setHeight(float _height) {
    if(_height >= 0) height = _height;
    fixedHeight = (height > 0);
    requestBoxLayout();
}

//--------------------------------------------------------------
float ofxMuiBox::getWidth() const {
    return width;
}

//--------------------------------------------------------------
float ofxMuiBox::getHeight() const {
    return height;
}

//--------------------------------------------------------------
void ofxMuiBox::setFixedWidth(bool _fixedWidth) {
    if(_fixedWidth == fixedWidth) return;
    fixedWidth = _fixedWidth;
    requestBoxLayout();
    //if(!fixedWidth) setParentNeedsLayoutUpdate(true);
}

//--------------------------------------------------------------
void ofxMuiBox::setFixedHeight(bool _fixedHeight) {
    if(_fixedHeight == fixedHeight) return;
    fixedHeight = _fixedHeight;
    requestBoxLayout();
    //if(!fixedHeight) setParentNeedsLayoutUpdate(true);
}

//--------------------------------------------------------------
bool ofxMuiBox::isFixedHeight() const {
    return fixedHeight;
}
//--------------------------------------------------------------
bool ofxMuiBox::isFixedWidth() const {
    return fixedWidth;
}

//--------------------------------------------------------------
ofRectangle ofxMuiBox::getBorderBox() const {
    return ofRectangle(getBorderBoxOffset(), 
                       getBorderBoxWidth(), 
                       getBorderBoxHeight());
}

//--------------------------------------------------------------
ofVec2f ofxMuiBox::getBorderBoxOffset() const {
    return ofVec2f(getBorderBoxSideOffset(SIDE_LEFT), 
                   getBorderBoxSideOffset(SIDE_TOP));
}

//--------------------------------------------------------------
float ofxMuiBox::getBorderBoxSideOffset(const ofxMuiBoxSide& side) const {
    return margin.get(side);
}

//--------------------------------------------------------------
float ofxMuiBox::getBorderBoxWidth() const {
    return width - (margin.right + margin.left);
}

//--------------------------------------------------------------
float ofxMuiBox::getBorderBoxHeight() const {
    return height - (margin.top + margin.bottom);
}

//--------------------------------------------------------------
float ofxMuiBox::getBorderBoxHalfWidth() const {
    return getBorderBoxWidth() * 0.5f;
}
//--------------------------------------------------------------
float ofxMuiBox::getBorderBoxHalfHeight() const {
    return getBorderBoxHeight() * 0.5f;
}
//--------------------------------------------------------------
ofVec2f ofxMuiBox::getBorderBoxCenter() const {
    return ofPoint(getBorderBoxCenterX(),getBorderBoxCenterY());
}
//--------------------------------------------------------------
float ofxMuiBox::getBorderBoxCenterX() const {
    return getBorderBoxHalfWidth();
}
//--------------------------------------------------------------
float ofxMuiBox::getBorderBoxCenterY() const {
    return getBorderBoxHalfHeight();
}

//--------------------------------------------------------------
ofRectangle ofxMuiBox::getPaddingBox() const {
    return ofRectangle(getPaddingBoxOffset(), 
                       getPaddingBoxWidth(), 
                       getPaddingBoxHeight());
}

//--------------------------------------------------------------
ofVec2f ofxMuiBox::getPaddingBoxOffset() const {
    return ofVec2f(getPaddingBoxSideOffset(SIDE_LEFT), 
                   getPaddingBoxSideOffset(SIDE_TOP));
}

//--------------------------------------------------------------
float ofxMuiBox::getPaddingBoxSideOffset(const ofxMuiBoxSide& side) const {
    return margin.get(side) + border.get(side);
}


//--------------------------------------------------------------
float ofxMuiBox::getPaddingBoxWidth() const {
    return width - (border.right + border.left) - (margin.right + margin.left);
}

//--------------------------------------------------------------
float ofxMuiBox::getPaddingBoxHeight() const {
    return height - (border.top + border.bottom) - (margin.top + margin.bottom);
}

//--------------------------------------------------------------
float ofxMuiBox::getPaddingBoxHalfWidth() const {
    return getPaddingBoxWidth() * 0.5f;
}

//--------------------------------------------------------------
float ofxMuiBox::getPaddingBoxHalfHeight() const {
    return getPaddingBoxHeight() * 0.5f;
}

//--------------------------------------------------------------
ofVec2f ofxMuiBox::getPaddingBoxCenter() const {
    return ofVec2f(getPaddingBoxCenterX(),getPaddingBoxCenterY());
}

//--------------------------------------------------------------
float ofxMuiBox::getPaddingBoxCenterX() const {
    return getPaddingBoxHalfHeight();
}

//--------------------------------------------------------------
float ofxMuiBox::getPaddingBoxCenterY() const {
    return getPaddingBoxHalfHeight();
}

//--------------------------------------------------------------
bool ofxMuiBox::insidePaddingBox(const ofPoint& _point) const {
    // this function assumes that the point has already been offset to the padding box
    // thus it sees if the point is between x 0/width and y 0/height
    return _point.x > 0 && _point.y > 0 && _point.x < getPaddingBoxWidth() && _point.y < getPaddingBoxHeight();
}

//--------------------------------------------------------------
ofRectangle ofxMuiBox::getContentBox() const {
    return contentBox;
}

//--------------------------------------------------------------
ofRectangle& ofxMuiBox::getContentBoxRef() {
    return contentBox;
}

//--------------------------------------------------------------
ofVec2f ofxMuiBox::getContentBoxOffset() const {
    return ofVec2f(getContentBoxSideOffset(SIDE_LEFT),
                   getContentBoxSideOffset(SIDE_TOP));
}

//--------------------------------------------------------------
float ofxMuiBox::getContentBoxSideOffset(const ofxMuiBoxSide& side) const {
    return margin.get(side) + border.get(side) + padding.get(side);
}

//--------------------------------------------------------------
float ofxMuiBox::getContentBoxWidth() const{
    return getContentBox().width;
}

//--------------------------------------------------------------
float ofxMuiBox::getContentBoxHeight() const {
    return getContentBox().height;
}
//--------------------------------------------------------------
float ofxMuiBox::getContentBoxHalfWidth() const {
    return getContentBoxWidth() * 0.5f;
}
//--------------------------------------------------------------
float ofxMuiBox::getContentBoxHalfHeight() const {
    return getContentBoxHeight() * 0.5f;
}
//--------------------------------------------------------------
ofVec2f ofxMuiBox::getContentBoxCenter() const {
    return ofVec2f(getContentBoxCenterX(), getContentBoxCenterY());
}
//--------------------------------------------------------------
float ofxMuiBox::getContentBoxCenterX() const {
    return getContentBoxHalfWidth();
}
//--------------------------------------------------------------
float ofxMuiBox::getContentBoxCenterY() const {
    return getContentBoxHalfHeight();
}

//--------------------------------------------------------------
void ofxMuiBox::setContentBoxWidth(float _width) {
    if(_width < 0) {
        ofLog(OF_LOG_ERROR,"ofxMuiBox: Set a negative content box width.  Not possible.");
        return;
    }
    
    if(isFixedWidth()) {
        contentBox.width = getWidth() - getContentBoxSideOffset(SIDE_LEFT) - getContentBoxSideOffset(SIDE_RIGHT);
    } else {
        contentBox.width = _width;
    }
    
}
//--------------------------------------------------------------
void ofxMuiBox::setContentBoxHeight(float _height) {
    if(_height < 0) {
        ofLog(OF_LOG_ERROR,"ofxMuiBox: Set a negative content box height.  Not possible.");
        return;
    }
    
    if(isFixedHeight()) {
        contentBox.height = getHeight() - getContentBoxSideOffset(SIDE_TOP) - getContentBoxSideOffset(SIDE_BOTTOM);
    } else {
        contentBox.height = _height;
    }
}

//--------------------------------------------------------------
// for setting the content box when the width and/or height are fixed
float ofxMuiBox::getMaxAllowableContentBoxWidth() const {
    if(isFixedWidth()) {
        return getWidth() - getContentBoxSideOffset(SIDE_LEFT) - getContentBoxSideOffset(SIDE_RIGHT);
    } else {
        return numeric_limits<float>::max();
    }
}
//--------------------------------------------------------------
float ofxMuiBox::getMaxAllowableContentBoxHeight() const {
    if(isFixedHeight()) {
        return getHeight() - getContentBoxSideOffset(SIDE_TOP) - getContentBoxSideOffset(SIDE_BOTTOM);
    } else {
        return numeric_limits<float>::max();
    }
}

/*
//--------------------------------------------------------------
bool ofxMuiBox::insideContentBox(ofPoint _point) {
    // this function assumes that the point has already been offset to the padding box
    // thus it sees if the point is between x 0/width and y 0/height
    return _point.x > 0 && _point.y > 0 && _point.x < getContentBoxWidth() && _point.y < getContentBoxHeight();
}
 */

//--------------------------------------------------------------
ofRectangle ofxMuiBox::getHitBox() const {
	if(isCustomHitBox()) {
		return hitBox;
	} else {
        // if no hit box, then just pass the content box
        return getContentBox();
	}
}

//--------------------------------------------------------------
ofRectangle& ofxMuiBox::getHitBoxRef() {
	if(isCustomHitBox()) {
		return hitBox;
	} else {
        // if no hit box, then just pass the content box
        return getContentBoxRef();
	}
}


//--------------------------------------------------------------
ofVec2f ofxMuiBox::getHitBoxOffset() const {
    return getContentBoxOffset() + ofVec2f(getHitBoxX(), getHitBoxY());
}


//--------------------------------------------------------------
void ofxMuiBox::setHitBox(const ofRectangle& _hitBox) {
	
    //cout << "SETHITBOX     ="<< _hitBox.x << "|" << _hitBox.y << "|" << _hitBox.width << "|" << _hitBox.height << endl;
    
    setHitBox(_hitBox.x,
                 _hitBox.y,
                 _hitBox.width,
                 _hitBox.height);
}

//--------------------------------------------------------------
void ofxMuiBox::setHitBox(float _x, float _y, float _width, float _height) {
    
    //cout << "SETHITBOX <><>="<< _x << "|" << _y << "|" << _width << "|" << _height << endl;

    
    if(_x < 0) {
        ofLog(OF_LOG_ERROR,"ofxMuiBox: Set a negative hitbox x position.  Not possible.");
        return;
    }
    
    if(_y < 0) {
        ofLog(OF_LOG_ERROR,"ofxMuiBox: Set a negative hitbox y position.  Not possible.");
        return;
    }

    if(_width < 0) {
        ofLog(OF_LOG_ERROR,"ofxMuiBox: Set a negative hitbox height.  Not possible.");
        return;
    }
    
    if(_height < 0) {
        ofLog(OF_LOG_ERROR,"ofxMuiBox: Set a negative hitbox height.  Not possible.");
        return;
    }
    
//    hitBox = ofRectangle(_x,_y,_width,_height);
}

//--------------------------------------------------------------
void ofxMuiBox::setHitBoxX(float _x) {
    if(_x < 0) {
        ofLog(OF_LOG_ERROR,"ofxMuiBox: Set a negative hitbox x position.  Not possible.");
        return;
    }
    
	hasCustomHitBox = true;
    hitBox.x = _x;
}
//--------------------------------------------------------------
void ofxMuiBox::setHitBoxY(float _y) {
    if(_y < 0) {
        ofLog(OF_LOG_ERROR,"ofxMuiBox: Set a negative hitbox y position.  Not possible.");
        return;
    }
	hasCustomHitBox = true;
    hitBox.y = _y;
}
//--------------------------------------------------------------
void ofxMuiBox::setHitBoxWidth(float _width) {
    if(_width < 0) {
        ofLog(OF_LOG_ERROR,"ofxMuiBox: Set a negative hitbox height.  Not possible.");
        return;
    }

    //cout << "Setting the width to " << _width;
    
	hasCustomHitBox = true;
    hitBox.width = _width;
    
    //cout << " hitBox.width =" << hitBox.width << endl;;
    
    
}
//--------------------------------------------------------------
void ofxMuiBox::setHitBoxHeight(float _height) {
    if(_height < 0) {
        ofLog(OF_LOG_ERROR,"ofxMuiBox: Set a negative hitbox height.  Not possible.");
        return;
    }

    //cout << "Setting the height to " << _height;;

    
	hasCustomHitBox = true;
    hitBox.height = _height;
    
    //cout << " hitBox.height =" << hitBox.height << endl;;

}


/*

//--------------------------------------------------------------
bool ofxMuiBox::insideHitBox(ofPoint _point) {
    // this function assumes that the point has already been offset to the hitbox
    // thus it sees if the point is between x 0/width and y 0/height
    //cout << _point << " IN " << endl;
    //cout << hasCustomHitBox << " | " << getHitBoxWidth() << " / " << getHitBoxHeight() << endl;
    //cout << "---" << endl;
    //cout << (_point.x > 0) << endl;
    //cout << (_point.y > 0) << endl;
    //cout << (_point.x < getHitBoxWidth()) << endl;
    //cout << (_point.y < getHitBoxHeight()) << endl;
    //cout << "---" << endl;
    
    return _point.x > 0 && _point.y > 0 && _point.x < getHitBoxWidth() && _point.y < getHitBoxHeight();
}
*/
//--------------------------------------------------------------
bool ofxMuiBox::isCustomHitBox() const {
    return hasCustomHitBox;
}

//--------------------------------------------------------------
float ofxMuiBox::getHitBoxWidth() const {
	return getHitBox().width;
}

//--------------------------------------------------------------
float ofxMuiBox::getHitBoxHeight() const {
	return getHitBox().height;
}

//--------------------------------------------------------------
float ofxMuiBox::getHitBoxHalfWidth() const {
    return getHitBoxWidth() * 0.5f;
}

//--------------------------------------------------------------
float ofxMuiBox::getHitBoxHalfHeight() const {
    return getHitBoxHeight() * 0.5f;
}

//--------------------------------------------------------------
ofVec2f ofxMuiBox::getHitBoxCenter() const {
    return ofVec2f(getHitBoxCenterX(),getHitBoxCenterY());
}
//--------------------------------------------------------------
float ofxMuiBox::getHitBoxCenterX() const {
    return getHitBoxHalfWidth();
}
//--------------------------------------------------------------
float ofxMuiBox::getHitBoxCenterY() const {
    return getHitBoxHalfHeight();
}

//--------------------------------------------------------------
ofVec2f ofxMuiBox::getHitBoxPosition() const {
    return ofVec2f(getHitBoxX(), getHitBoxY());
}

//--------------------------------------------------------------
float ofxMuiBox::getHitBoxX() const {
    return getHitBox().x;
}
//--------------------------------------------------------------
float ofxMuiBox::getHitBoxY() const {
    return getHitBox().y;
}

//--------------------------------------------------------------
bool ofxMuiBox::insideBorderBox(const ofPoint& _point) const {
    // this function assumes that the point has already been offset to the border box
    // thus it sees if the point is between x 0/width and y 0/height
    return _point.x > 0 && _point.y > 0 && _point.x < getBorderBoxWidth() && _point.y < getBorderBoxHeight();
}

//--------------------------------------------------------------
ofVec2f ofxMuiBox::screenToBox(const ofVec2f& p) const {
    return p - getBoxScreenPosition();
}

//--------------------------------------------------------------
ofVec2f ofxMuiBox::screenToBorderBox(const ofVec2f& p) const {
    return p - (getBoxScreenPosition() +  getBorderBoxOffset());
}

//--------------------------------------------------------------
ofVec2f ofxMuiBox::screenToPaddingBox(const ofVec2f& p) const {
    return p - (getBoxScreenPosition() +  getPaddingBoxOffset());
}

//--------------------------------------------------------------
ofVec2f ofxMuiBox::screenToContentBox(const ofVec2f& p) const {
    return p - (getBoxScreenPosition() +  getContentBoxOffset());
}

//--------------------------------------------------------------
ofVec2f ofxMuiBox::screenToHitBox(const ofVec2f& p) const {
    return p - (getBoxScreenPosition() +  getHitBoxOffset());
}

//--------------------------------------------------------------
ofVec2f ofxMuiBox::getBoxScreenPosition() const {
    return getPosition();
}

//--------------------------------------------------------------
bool ofxMuiBox::insideBox(const ofPoint& _point) const {
    // this function assumes that the point has already been offset to the border box
    // thus it sees if the point is between x 0/width and y 0/height
    return _point.x > 0 && _point.y > 0 && _point.x < getWidth() && _point.y < getHeight();
}

//--------------------------------------------------------------
ofVec2f ofxMuiBox::getBorderScreenPosition() const {
    return getBoxScreenPosition() + getBorderBoxOffset();
}

//--------------------------------------------------------------
ofVec2f ofxMuiBox::getPaddingScreenPosition() const {
    return getBoxScreenPosition() + getPaddingBoxOffset();
}

//--------------------------------------------------------------
ofVec2f ofxMuiBox::getContentScreenPosition() const {
    return getBoxScreenPosition() + getContentBoxOffset();
}

//--------------------------------------------------------------
ofVec2f ofxMuiBox::getHitBoxScreenPosition() const {
    return getBoxScreenPosition() + getHitBoxOffset();
}

//--------------------------------------------------------------
bool ofxMuiBox::hitTest(const ofPoint& screenMousePos) const {
    return hitTest(screenMousePos.x,screenMousePos.y);
}

//--------------------------------------------------------------
bool ofxMuiBox::hitTest(float screenX, float screenY) const {
    // this function could be overriden w/ via the virtual declaration
    // hitRect is always described in with respect to the content frame 
    ofVec2f contentMousePos = screenToContentBox(ofVec2f(screenX, screenY));
    
    ofRectangle wr = getHitBox();
        
    // +1 issue attempted to be fixed
    return contentMousePos.x > wr.x && 
            contentMousePos.y > wr.y && 
            contentMousePos.x <= (wr.x + wr.width + 1) && 
            contentMousePos.y <= (wr.y + wr.height + 1);
    
}
 

//--------------------------------------------------------------
void ofxMuiBox::setNeedsNewLine(bool _needsNewLine) {
    needsNewLine = _needsNewLine;
    setParentNeedsLayoutUpdate(true);
}

//--------------------------------------------------------------
bool ofxMuiBox::getNeedsNewLine() const {
    return needsNewLine;
}

//--------------------------------------------------------------
void ofxMuiBox::setNeedsLayoutUpdate(bool _needsLayout) {
    needsLayout = _needsLayout;
}

//--------------------------------------------------------------
bool ofxMuiBox::getNeedsLayoutUpdate() const {
    return needsLayout;
}

//--------------------------------------------------------------
void ofxMuiBox::setParentNeedsLayoutUpdate(bool _parentNeedsLayout) {
    parentNeedsLayout = _parentNeedsLayout;
}

//--------------------------------------------------------------
bool ofxMuiBox::getParentNeedsLayoutUpdate() const {
    return parentNeedsLayout;
}

//--------------------------------------------------------------
void ofxMuiBox::requestBoxLayout() {
    // if the object hasn't had a chance to get an initial layout, then we
    // allow it to do so until the update loop comes around.
    // this allows one to configure objects in the setup without
    // entering everything in through the object's constructor
    if (isLayoutSetupComplete) {
        setNeedsLayoutUpdate(true);
    } else {
        doLayout();
    }
}


//--------------------------------------------------------------
void ofxMuiBox::checkBounds() {
    checkBoundsX();
    checkBoundsY();
}

//--------------------------------------------------------------
void ofxMuiBox::checkBoundsX() {
    x = xRange.constrain(x);
}
//--------------------------------------------------------------
void ofxMuiBox::checkBoundsY() {
    y = yRange.constrain(y);
}

//--------------------------------------------------------------
void ofxMuiBox::doLayout() {
    doContentBoxLayout();
    
    if(!fixedWidth) {
        width = contentBox.width;
        width += (margin.right  + margin.left);
        width += (border.right  + border.left);
        width += (padding.right + padding.left);
    }
    
    if(!fixedHeight) {
        height = contentBox.height;
        height += (margin.top  + margin.bottom);
        height += (border.top  + border.bottom);
        height += (padding.top + padding.bottom);
    }
    
    needsLayout = false;
}


// content alignment for fixt box situations
//--------------------------------------------------------------
void ofxMuiBox::setContentAlignHorz(const ofAlignHorz& _hAlign) {
    hContentAlign = _hAlign;
    requestBoxLayout();
}
//--------------------------------------------------------------
void ofxMuiBox::setContentAlignVert(const ofAlignVert& _vAlign) {
    vContentAlign = _vAlign;
    requestBoxLayout();
}

//--------------------------------------------------------------
ofAlignHorz ofxMuiBox::getContentAlignHorz() const {
    return hContentAlign;
}
//--------------------------------------------------------------
ofAlignVert ofxMuiBox::getContentAlignVert() const {
    return vContentAlign;
}



