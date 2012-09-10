#include "ofxGuiBox.h"

//--------------------------------------------------------------
// we explicitly set the frame size, and disallow auto adjusting
ofxGuiBox::ofxGuiBox(ofRectangle _rect) : 
    ofxGuiBoxProperties(),
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
ofxGuiBox::ofxGuiBox(float _x, float _y, float _w, float _h) : 
    ofxGuiBoxProperties(),
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
ofxGuiBox::ofxGuiBox(float _x, float _y) : 
    ofxGuiBoxProperties(),
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
ofxGuiBox::ofxGuiBox() : 
    ofxGuiBoxProperties(),
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
ofxGuiBox::~ofxGuiBox() {}

//----------------------------------------------------------
void ofxGuiBox::ofxRect(const ofRectangle & r, bool inner){
	ofxRect(r.x, r.y, r.width, r.height, inner);
}

//--------------------------------------------------------------
// TODO
// from : https://github.com/openframeworks/openFrameworks/issues/798
void ofxGuiBox::ofxRect(float _x, float _y, float _width, float _height, bool inner) {
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
void ofxGuiBox::ofxFrame(float _x, float _y, float _width, float _height, ofxGuiBoxPropertyQuad quadProp) {
    
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
ofRectangle ofxGuiBox::getBox() {
    return ofRectangle(*this);
}

////--------------------------------------------------------------
//void ofxGuiBox::setX(float _x, bool _updateParent) {
//    x = _x;
//    checkBoundsX();
//    setParentNeedsLayoutUpdate(_updateParent);
//}
//
////--------------------------------------------------------------
//void ofxGuiBox::setY(float _y, bool _updateParent) {
//    y = _y;
//    checkBoundsY();
//    setParentNeedsLayoutUpdate(_updateParent);
//}
//--------------------------------------------------------------
void ofxGuiBox::setMinBounds(ofVec2f _minBounds) {
    xRange.setMin(_minBounds.x);
    yRange.setMin(_minBounds.y);
    checkBounds();
}

//--------------------------------------------------------------
void ofxGuiBox::setMaxBounds(ofVec2f _maxBounds) {
    xRange.setMax(_maxBounds.x);
    yRange.setMax(_maxBounds.y);
    checkBounds();
}

//--------------------------------------------------------------
void ofxGuiBox::setMaxX(float _maxX) {
    xRange.setMax(_maxX);
    checkBoundsX();
}

//--------------------------------------------------------------
void ofxGuiBox::setMaxY(float _maxY) {
    yRange.setMax(_maxY);
    checkBoundsY();
}

//--------------------------------------------------------------
void ofxGuiBox::setMinX(float _minX) {
    xRange.setMin(_minX);
    checkBoundsX();
}

//--------------------------------------------------------------
void ofxGuiBox::setMinY(float _minY) {
    yRange.setMin(_minY);
    checkBoundsY();
}

//--------------------------------------------------------------
void ofxGuiBox::setBoundsX(float minX, float maxX) {
    xRange.setMin(minX);
    xRange.setMax(maxX);
    checkBoundsX();
}

//--------------------------------------------------------------
void ofxGuiBox::setBoundsY(float minY, float maxY) {
    yRange.setMin(minY);
    yRange.setMax(maxY);
    checkBoundsY();
}

//--------------------------------------------------------------
void ofxGuiBox::clearBounds() {
    clearMaxBounds();
    clearMinBounds();
}

//--------------------------------------------------------------
void ofxGuiBox::clearMaxBounds() {
    clearMaxX();
    clearMaxY();
}

//--------------------------------------------------------------
void ofxGuiBox::clearMinBounds() {
    clearMinX();
    clearMinY();
}

//--------------------------------------------------------------
void ofxGuiBox::clearMaxX() {
    xRange.clearMax();
    checkBoundsX();
}

//--------------------------------------------------------------
void ofxGuiBox::clearMaxY() {
    yRange.clearMax();
    checkBoundsY();
}

//--------------------------------------------------------------
void ofxGuiBox::clearMinX() {
    xRange.clearMin();
    checkBoundsX();
}

//--------------------------------------------------------------
void ofxGuiBox::clearMinY() {
    yRange.clearMin();
    checkBoundsY();
}

//--------------------------------------------------------------
void ofxGuiBox::setWidth(float _width) {
    if(_width >= 0) width = _width;
    fixedWidth = (width > 0);
    requestBoxLayout();
}

//--------------------------------------------------------------
void ofxGuiBox::setHeight(float _height) {
    if(_height >= 0) height = _height;
    fixedHeight = (height > 0);
    requestBoxLayout();
}

//--------------------------------------------------------------
float ofxGuiBox::getWidth() const {
    return width;
}

//--------------------------------------------------------------
float ofxGuiBox::getHeight() const {
    return height;
}

//--------------------------------------------------------------
void ofxGuiBox::setFixedWidth(bool _fixedWidth) {
    if(_fixedWidth == fixedWidth) return;
    fixedWidth = _fixedWidth;
    requestBoxLayout();
    //if(!fixedWidth) setParentNeedsLayoutUpdate(true);
}

//--------------------------------------------------------------
void ofxGuiBox::setFixedHeight(bool _fixedHeight) {
    if(_fixedHeight == fixedHeight) return;
    fixedHeight = _fixedHeight;
    requestBoxLayout();
    //if(!fixedHeight) setParentNeedsLayoutUpdate(true);
}

//--------------------------------------------------------------
bool ofxGuiBox::isFixedHeight() const {
    return fixedHeight;
}
//--------------------------------------------------------------
bool ofxGuiBox::isFixedWidth() const {
    return fixedWidth;
}

//--------------------------------------------------------------
ofRectangle ofxGuiBox::getBorderBox() const {
    return ofRectangle(getBorderBoxOffset(), 
                       getBorderBoxWidth(), 
                       getBorderBoxHeight());
}

//--------------------------------------------------------------
ofVec2f ofxGuiBox::getBorderBoxOffset() const {
    return ofVec2f(getBorderBoxSideOffset(SIDE_LEFT), 
                   getBorderBoxSideOffset(SIDE_TOP));
}

//--------------------------------------------------------------
float ofxGuiBox::getBorderBoxSideOffset(const ofxGuiBoxSide& side) const {
    return margin.get(side);
}

//--------------------------------------------------------------
float ofxGuiBox::getBorderBoxWidth() const {
    return width - (margin.right + margin.left);
}

//--------------------------------------------------------------
float ofxGuiBox::getBorderBoxHeight() const {
    return height - (margin.top + margin.bottom);
}

//--------------------------------------------------------------
float ofxGuiBox::getBorderBoxHalfWidth() const {
    return getBorderBoxWidth() * 0.5f;
}
//--------------------------------------------------------------
float ofxGuiBox::getBorderBoxHalfHeight() const {
    return getBorderBoxHeight() * 0.5f;
}
//--------------------------------------------------------------
ofVec2f ofxGuiBox::getBorderBoxCenter() const {
    return ofPoint(getBorderBoxCenterX(),getBorderBoxCenterY());
}
//--------------------------------------------------------------
float ofxGuiBox::getBorderBoxCenterX() const {
    return getBorderBoxHalfWidth();
}
//--------------------------------------------------------------
float ofxGuiBox::getBorderBoxCenterY() const {
    return getBorderBoxHalfHeight();
}

//--------------------------------------------------------------
ofRectangle ofxGuiBox::getPaddingBox() const {
    return ofRectangle(getPaddingBoxOffset(), 
                       getPaddingBoxWidth(), 
                       getPaddingBoxHeight());
}

//--------------------------------------------------------------
ofVec2f ofxGuiBox::getPaddingBoxOffset() const {
    return ofVec2f(getPaddingBoxSideOffset(SIDE_LEFT), 
                   getPaddingBoxSideOffset(SIDE_TOP));
}

//--------------------------------------------------------------
float ofxGuiBox::getPaddingBoxSideOffset(const ofxGuiBoxSide& side) const {
    return margin.get(side) + border.get(side);
}


//--------------------------------------------------------------
float ofxGuiBox::getPaddingBoxWidth() const {
    return width - (border.right + border.left) - (margin.right + margin.left);
}

//--------------------------------------------------------------
float ofxGuiBox::getPaddingBoxHeight() const {
    return height - (border.top + border.bottom) - (margin.top + margin.bottom);
}

//--------------------------------------------------------------
float ofxGuiBox::getPaddingBoxHalfWidth() const {
    return getPaddingBoxWidth() * 0.5f;
}

//--------------------------------------------------------------
float ofxGuiBox::getPaddingBoxHalfHeight() const {
    return getPaddingBoxHeight() * 0.5f;
}

//--------------------------------------------------------------
ofVec2f ofxGuiBox::getPaddingBoxCenter() const {
    return ofVec2f(getPaddingBoxCenterX(),getPaddingBoxCenterY());
}

//--------------------------------------------------------------
float ofxGuiBox::getPaddingBoxCenterX() const {
    return getPaddingBoxHalfHeight();
}

//--------------------------------------------------------------
float ofxGuiBox::getPaddingBoxCenterY() const {
    return getPaddingBoxHalfHeight();
}

//--------------------------------------------------------------
bool ofxGuiBox::insidePaddingBox(const ofPoint& _point) const {
    // this function assumes that the point has already been offset to the padding box
    // thus it sees if the point is between x 0/width and y 0/height
    return _point.x > 0 && _point.y > 0 && _point.x < getPaddingBoxWidth() && _point.y < getPaddingBoxHeight();
}

//--------------------------------------------------------------
ofRectangle ofxGuiBox::getContentBox() const {
    return contentBox;
}

//--------------------------------------------------------------
ofRectangle& ofxGuiBox::getContentBoxRef() {
    return contentBox;
}

//--------------------------------------------------------------
ofVec2f ofxGuiBox::getContentBoxOffset() const {
    return ofVec2f(getContentBoxSideOffset(SIDE_LEFT),
                   getContentBoxSideOffset(SIDE_TOP));
}

//--------------------------------------------------------------
float ofxGuiBox::getContentBoxSideOffset(const ofxGuiBoxSide& side) const {
    return margin.get(side) + border.get(side) + padding.get(side);
}

//--------------------------------------------------------------
float ofxGuiBox::getContentBoxWidth() const{
    return getContentBox().width;
}

//--------------------------------------------------------------
float ofxGuiBox::getContentBoxHeight() const {
    return getContentBox().height;
}
//--------------------------------------------------------------
float ofxGuiBox::getContentBoxHalfWidth() const {
    return getContentBoxWidth() * 0.5f;
}
//--------------------------------------------------------------
float ofxGuiBox::getContentBoxHalfHeight() const {
    return getContentBoxHeight() * 0.5f;
}
//--------------------------------------------------------------
ofVec2f ofxGuiBox::getContentBoxCenter() const {
    return ofVec2f(getContentBoxCenterX(), getContentBoxCenterY());
}
//--------------------------------------------------------------
float ofxGuiBox::getContentBoxCenterX() const {
    return getContentBoxHalfWidth();
}
//--------------------------------------------------------------
float ofxGuiBox::getContentBoxCenterY() const {
    return getContentBoxHalfHeight();
}

//--------------------------------------------------------------
void ofxGuiBox::setContentBoxWidth(float _width) {
    if(_width < 0) {
        ofLog(OF_LOG_ERROR,"ofxGuiBox: Set a negative content box width.  Not possible.");
        return;
    }
    
    if(isFixedWidth()) {
        contentBox.width = getWidth() - getContentBoxSideOffset(SIDE_LEFT) - getContentBoxSideOffset(SIDE_RIGHT);
    } else {
        contentBox.width = _width;
    }
    
}
//--------------------------------------------------------------
void ofxGuiBox::setContentBoxHeight(float _height) {
    if(_height < 0) {
        ofLog(OF_LOG_ERROR,"ofxGuiBox: Set a negative content box height.  Not possible.");
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
float ofxGuiBox::getMaxAllowableContentBoxWidth() const {
    if(isFixedWidth()) {
        return getWidth() - getContentBoxSideOffset(SIDE_LEFT) - getContentBoxSideOffset(SIDE_RIGHT);
    } else {
        return numeric_limits<float>::max();
    }
}
//--------------------------------------------------------------
float ofxGuiBox::getMaxAllowableContentBoxHeight() const {
    if(isFixedHeight()) {
        return getHeight() - getContentBoxSideOffset(SIDE_TOP) - getContentBoxSideOffset(SIDE_BOTTOM);
    } else {
        return numeric_limits<float>::max();
    }
}

/*
//--------------------------------------------------------------
bool ofxGuiBox::insideContentBox(ofPoint _point) {
    // this function assumes that the point has already been offset to the padding box
    // thus it sees if the point is between x 0/width and y 0/height
    return _point.x > 0 && _point.y > 0 && _point.x < getContentBoxWidth() && _point.y < getContentBoxHeight();
}
 */

//--------------------------------------------------------------
ofRectangle ofxGuiBox::getHitBox() const {
	if(isCustomHitBox()) {
		return hitBox;
	} else {
        // if no hit box, then just pass the content box
        return getContentBox();
	}
}

//--------------------------------------------------------------
ofRectangle& ofxGuiBox::getHitBoxRef() {
	if(isCustomHitBox()) {
		return hitBox;
	} else {
        // if no hit box, then just pass the content box
        return getContentBoxRef();
	}
}


//--------------------------------------------------------------
ofVec2f ofxGuiBox::getHitBoxOffset() const {
    return getContentBoxOffset() + ofVec2f(getHitBoxX(), getHitBoxY());
}


//--------------------------------------------------------------
void ofxGuiBox::setHitBox(const ofRectangle& _hitBox) {
	
    //cout << "SETHITBOX     ="<< _hitBox.x << "|" << _hitBox.y << "|" << _hitBox.width << "|" << _hitBox.height << endl;
    
    setHitBox(_hitBox.x,
                 _hitBox.y,
                 _hitBox.width,
                 _hitBox.height);
}

//--------------------------------------------------------------
void ofxGuiBox::setHitBox(float _x, float _y, float _width, float _height) {
    
    //cout << "SETHITBOX <><>="<< _x << "|" << _y << "|" << _width << "|" << _height << endl;

    
    if(_x < 0) {
        ofLog(OF_LOG_ERROR,"ofxGuiBox: Set a negative hitbox x position.  Not possible.");
        return;
    }
    
    if(_y < 0) {
        ofLog(OF_LOG_ERROR,"ofxGuiBox: Set a negative hitbox y position.  Not possible.");
        return;
    }

    if(_width < 0) {
        ofLog(OF_LOG_ERROR,"ofxGuiBox: Set a negative hitbox height.  Not possible.");
        return;
    }
    
    if(_height < 0) {
        ofLog(OF_LOG_ERROR,"ofxGuiBox: Set a negative hitbox height.  Not possible.");
        return;
    }
    
//    hitBox = ofRectangle(_x,_y,_width,_height);
}

//--------------------------------------------------------------
void ofxGuiBox::setHitBoxX(float _x) {
    if(_x < 0) {
        ofLog(OF_LOG_ERROR,"ofxGuiBox: Set a negative hitbox x position.  Not possible.");
        return;
    }
    
	hasCustomHitBox = true;
    hitBox.x = _x;
}
//--------------------------------------------------------------
void ofxGuiBox::setHitBoxY(float _y) {
    if(_y < 0) {
        ofLog(OF_LOG_ERROR,"ofxGuiBox: Set a negative hitbox y position.  Not possible.");
        return;
    }
	hasCustomHitBox = true;
    hitBox.y = _y;
}
//--------------------------------------------------------------
void ofxGuiBox::setHitBoxWidth(float _width) {
    if(_width < 0) {
        ofLog(OF_LOG_ERROR,"ofxGuiBox: Set a negative hitbox height.  Not possible.");
        return;
    }

    //cout << "Setting the width to " << _width;
    
	hasCustomHitBox = true;
    hitBox.width = _width;
    
    //cout << " hitBox.width =" << hitBox.width << endl;;
    
    
}
//--------------------------------------------------------------
void ofxGuiBox::setHitBoxHeight(float _height) {
    if(_height < 0) {
        ofLog(OF_LOG_ERROR,"ofxGuiBox: Set a negative hitbox height.  Not possible.");
        return;
    }

    //cout << "Setting the height to " << _height;;

    
	hasCustomHitBox = true;
    hitBox.height = _height;
    
    //cout << " hitBox.height =" << hitBox.height << endl;;

}


/*

//--------------------------------------------------------------
bool ofxGuiBox::insideHitBox(ofPoint _point) {
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
bool ofxGuiBox::isCustomHitBox() const {
    return hasCustomHitBox;
}

//--------------------------------------------------------------
float ofxGuiBox::getHitBoxWidth() const {
	return getHitBox().width;
}

//--------------------------------------------------------------
float ofxGuiBox::getHitBoxHeight() const {
	return getHitBox().height;
}

//--------------------------------------------------------------
float ofxGuiBox::getHitBoxHalfWidth() const {
    return getHitBoxWidth() * 0.5f;
}

//--------------------------------------------------------------
float ofxGuiBox::getHitBoxHalfHeight() const {
    return getHitBoxHeight() * 0.5f;
}

//--------------------------------------------------------------
ofVec2f ofxGuiBox::getHitBoxCenter() const {
    return ofVec2f(getHitBoxCenterX(),getHitBoxCenterY());
}
//--------------------------------------------------------------
float ofxGuiBox::getHitBoxCenterX() const {
    return getHitBoxHalfWidth();
}
//--------------------------------------------------------------
float ofxGuiBox::getHitBoxCenterY() const {
    return getHitBoxHalfHeight();
}

//--------------------------------------------------------------
ofVec2f ofxGuiBox::getHitBoxPosition() const {
    return ofVec2f(getHitBoxX(), getHitBoxY());
}

//--------------------------------------------------------------
float ofxGuiBox::getHitBoxX() const {
    return getHitBox().x;
}
//--------------------------------------------------------------
float ofxGuiBox::getHitBoxY() const {
    return getHitBox().y;
}

//--------------------------------------------------------------
bool ofxGuiBox::insideBorderBox(const ofPoint& _point) const {
    // this function assumes that the point has already been offset to the border box
    // thus it sees if the point is between x 0/width and y 0/height
    return _point.x > 0 && _point.y > 0 && _point.x < getBorderBoxWidth() && _point.y < getBorderBoxHeight();
}

//--------------------------------------------------------------
ofVec2f ofxGuiBox::screenToBox(const ofVec2f& p) const {
    return p - getBoxScreenPosition();
}

//--------------------------------------------------------------
ofVec2f ofxGuiBox::screenToBorderBox(const ofVec2f& p) const {
    return p - (getBoxScreenPosition() +  getBorderBoxOffset());
}

//--------------------------------------------------------------
ofVec2f ofxGuiBox::screenToPaddingBox(const ofVec2f& p) const {
    return p - (getBoxScreenPosition() +  getPaddingBoxOffset());
}

//--------------------------------------------------------------
ofVec2f ofxGuiBox::screenToContentBox(const ofVec2f& p) const {
    return p - (getBoxScreenPosition() +  getContentBoxOffset());
}

//--------------------------------------------------------------
ofVec2f ofxGuiBox::screenToHitBox(const ofVec2f& p) const {
    return p - (getBoxScreenPosition() +  getHitBoxOffset());
}

//--------------------------------------------------------------
ofVec2f ofxGuiBox::getBoxScreenPosition() const {
    return getPosition();
}

//--------------------------------------------------------------
bool ofxGuiBox::insideBox(const ofPoint& _point) const {
    // this function assumes that the point has already been offset to the border box
    // thus it sees if the point is between x 0/width and y 0/height
    return _point.x > 0 && _point.y > 0 && _point.x < getWidth() && _point.y < getHeight();
}

//--------------------------------------------------------------
ofVec2f ofxGuiBox::getBorderScreenPosition() const {
    return getBoxScreenPosition() + getBorderBoxOffset();
}

//--------------------------------------------------------------
ofVec2f ofxGuiBox::getPaddingScreenPosition() const {
    return getBoxScreenPosition() + getPaddingBoxOffset();
}

//--------------------------------------------------------------
ofVec2f ofxGuiBox::getContentScreenPosition() const {
    return getBoxScreenPosition() + getContentBoxOffset();
}

//--------------------------------------------------------------
ofVec2f ofxGuiBox::getHitBoxScreenPosition() const {
    return getBoxScreenPosition() + getHitBoxOffset();
}

//--------------------------------------------------------------
bool ofxGuiBox::hitTest(const ofPoint& screenMousePos) const {
    return hitTest(screenMousePos.x,screenMousePos.y);
}

//--------------------------------------------------------------
bool ofxGuiBox::hitTest(float screenX, float screenY) const {
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
void ofxGuiBox::setNeedsNewLine(bool _needsNewLine) {
    needsNewLine = _needsNewLine;
    setParentNeedsLayoutUpdate(true);
}

//--------------------------------------------------------------
bool ofxGuiBox::getNeedsNewLine() const {
    return needsNewLine;
}

//--------------------------------------------------------------
void ofxGuiBox::setNeedsLayoutUpdate(bool _needsLayout) {
    needsLayout = _needsLayout;
}

//--------------------------------------------------------------
bool ofxGuiBox::getNeedsLayoutUpdate() const {
    return needsLayout;
}

//--------------------------------------------------------------
void ofxGuiBox::setParentNeedsLayoutUpdate(bool _parentNeedsLayout) {
    parentNeedsLayout = _parentNeedsLayout;
}

//--------------------------------------------------------------
bool ofxGuiBox::getParentNeedsLayoutUpdate() const {
    return parentNeedsLayout;
}

//--------------------------------------------------------------
void ofxGuiBox::requestBoxLayout() {
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
void ofxGuiBox::checkBounds() {
    checkBoundsX();
    checkBoundsY();
}

//--------------------------------------------------------------
void ofxGuiBox::checkBoundsX() {
    x = xRange.constrain(x);
}
//--------------------------------------------------------------
void ofxGuiBox::checkBoundsY() {
    y = yRange.constrain(y);
}

//--------------------------------------------------------------
void ofxGuiBox::doLayout() {
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
void ofxGuiBox::setContentAlignHorz(const ofAlignHorz& _hAlign) {
    hContentAlign = _hAlign;
    requestBoxLayout();
}
//--------------------------------------------------------------
void ofxGuiBox::setContentAlignVert(const ofAlignVert& _vAlign) {
    vContentAlign = _vAlign;
    requestBoxLayout();
}

//--------------------------------------------------------------
ofAlignHorz ofxGuiBox::getContentAlignHorz() const {
    return hContentAlign;
}
//--------------------------------------------------------------
ofAlignVert ofxGuiBox::getContentAlignVert() const {
    return vContentAlign;
}



