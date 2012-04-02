#include "ofxGuiRectUtils.h"


//--------------------------------------------------------------
ofRectangle ofxGuiRectUtils::intersection(const ofRectangle* r0, const ofRectangle* r1) {
    ofRectangle r(0,0,0,0);
    
    if(intersect(r0, r1)) {
        r.x = MAX(r0->x, r1->x);
        r.y = MAX(r0->y, r1->y);
        r.width = MIN(r0->x + r0->width, r1->x + r1->width); 
        r.height = MIN(r0->y + r0->height, r1->y + r1->height); 
    } 
       
    return r;
}

//--------------------------------------------------------------
bool ofxGuiRectUtils::contains(const ofRectangle* r0, const ofRectangle* r1) {
    return r1->x >= r0->x && r1->x + r1->width  <= r0->x + r0->width &&
           r1->y >= r0->y && r1->y + r1->height <= r0->y + r0->height;
    
}

//--------------------------------------------------------------
bool ofxGuiRectUtils::intersect(const ofRectangle* r0, const ofRectangle* r1) {
    return  r0->x               < (r1->x + r1->width)  &&
           (r0->x + r0->width)  >  r1->x               &&
            r0->y               < (r1->y + r1->height) &&
           (r0->y + r0->height) >  r1->y;
}

//--------------------------------------------------------------
void ofxGuiRectUtils::horzAlign(ofRectangle* rect, 
                            ofxGuiAlign   align, 
                            const ofRectangle bb,
                            ofPoint rectAnchor) {
    
    switch(align) {
        case ALIGN_NONE:
        case ALIGN_BASELINE:
        case ALIGN_TOP:
        case ALIGN_BOTTOM:
        case ALIGN_JUSTIFY_Y:
        case ALIGN_CENTER_Y:
        case ALIGN_JUSTIFY_X:
            ofLog(OF_LOG_WARNING,"horzAlign: not horz align enum, ignoring");
            return; // not horizontal
        case ALIGN_LEFT:
            rect->x = bb.x - rectAnchor.x;
            break;
        case ALIGN_RIGHT:
            rect->x = bb.x + bb.width - rectAnchor.x;
            break;
        case ALIGN_CENTER_X:
            rect->x = bb.x + bb.width / 2.0f - rectAnchor.x;
            break;
    }            
}

//--------------------------------------------------------------
void ofxGuiRectUtils::vertAlign(ofRectangle* rect, 
                            ofxGuiAlign   align, 
                            const ofRectangle bb,
                            ofPoint rectAnchor) {
    
    switch(align) {
        case ALIGN_NONE:
        case ALIGN_BASELINE:
        case ALIGN_JUSTIFY_Y:
        case ALIGN_JUSTIFY_X:
        case ALIGN_LEFT:
        case ALIGN_RIGHT:
        case ALIGN_CENTER_X:
            ofLog(OF_LOG_WARNING,"vertAlign: not vert align enum, ignoring");
            return; // not horizontal
        case ALIGN_TOP:
            rect->y = bb.y - rectAnchor.y;
            break;
        case ALIGN_BOTTOM:
            rect->y = bb.y + bb.height - rectAnchor.y;
            break;
        case ALIGN_CENTER_Y:
            rect->y = bb.y + bb.height / 2.0f - rectAnchor.y;
            break;
    }            
}

//--------------------------------------------------------------
void ofxGuiRectUtils::align(ofRectangle* rect, 
                       ofxGuiAlign   _hAlign, 
                       ofxGuiAlign   _vAlign,
                       const ofRectangle bb,
                       ofPoint rectAnchor) {
    horzAlign(rect, _hAlign, bb, rectAnchor);
    vertAlign(rect, _vAlign, bb, rectAnchor);
}

//--------------------------------------------------------------
void ofxGuiRectUtils::align(vector<ofRectangle*>& rects, 
                            ofxGuiAlign   _objectAlign,
                            ofxGuiAlign   _anchorAlign, 
                            ofxGuiAlignTo    _alignTo, 
                            const ofRectangle bb) {

    ofxGuiRange _x, _y, _width, _height;
    getExtrema(rects,_x,_y,_width,_height);

    float alignX = 0.0f;
    float alignY = 0.0f;
    
    ofRectangle boundingBox = bb;
            
    switch(_alignTo) {
        case ALIGN_TO_NONE:
            ofLog(OF_LOG_WARNING,"ofGuiRectUtils::align : Attempting to align to nothing, but you gotta align to something, so assuming the anchor.");
        case ALIGN_TO_ANCHOR:
            alignX = bb.x;
            alignY = bb.y;
        case ALIGN_TO_SELECTION:
            getBoundingBox(rects, boundingBox);
            // now pass through to the next case b/c we have determined the bounding box
        case ALIGN_TO_BOUNDING_BOX:
            alignX = boundingBox.x;
            alignY = boundingBox.y;
            switch(_anchorAlign) {
                case ALIGN_NONE:
                    ofLog(OF_LOG_WARNING,"ofGuiRectUtils::align : Attempting to align to nothing, but you gotta align to something, so assuming left.");
                case ALIGN_LEFT:
                case ALIGN_TOP:
                    // already took care of these two above
                case ALIGN_JUSTIFY_X:
                case ALIGN_JUSTIFY_Y:
                case ALIGN_BASELINE:
                    break;
                case ALIGN_CENTER_X:
                    alignX = boundingBox.x + (boundingBox.width  / 2.0);
                    break;
                case ALIGN_CENTER_Y:
                    alignY = boundingBox.y + (boundingBox.height / 2.0);
                    break;
                case ALIGN_RIGHT:
                    alignX = boundingBox.x + boundingBox.width;
                    break;
                case ALIGN_BOTTOM:
                    alignY = boundingBox.y + boundingBox.height;
                    break;
            }            
            break;
    }
    
    for(vector<ofRectangle*>::iterator rr = rects.begin(); rr != rects.end(); ++rr) {
        ofRectangle* r = *rr; // get the pointer

        switch(_objectAlign) {
            // X ALIGN (HORZ)
            case ALIGN_NONE:
                ofLog(OF_LOG_WARNING,"ofGuiRectUtils::align : Attempting to align to nothing, but you gotta align to something, so assuming left.");
            case ALIGN_LEFT:
            case ALIGN_JUSTIFY_X:
                r->x = alignX;
                break;
            case ALIGN_RIGHT:
                r->x = alignX - r->width;
                break;
            case ALIGN_CENTER_X:
                r->x = alignX - r->width / 2.0f;
                break;
            // Y ALIGN (VERT)
            case ALIGN_TOP:
            case ALIGN_JUSTIFY_Y:
            case ALIGN_BASELINE:
                r->y = alignY;
                break;
            case ALIGN_BOTTOM:
                r->y = alignY - r->height;
                break;
            case ALIGN_CENTER_Y:
                r->y = alignY - r->height / 2.0f;
                break;
            
        }            
    }
    
    
}
//--------------------------------------------------------------
void ofxGuiRectUtils::distribute(vector<ofRectangle*>& rects, 
                       ofxGuiAlign   _objectAlign,
                       ofxGuiAlignTo _alignTo, 
                       const ofRectangle bb) {

    if(rects.size() < 2) {
        ofLog(OF_LOG_WARNING,"ofGuiRectUtils::distribute : Need more than one item to distribute");
        return;
    }
    
    bool aligningHorizontally = isHorizontalAlignment(_objectAlign);
    
    // make sure the bounding box is useful
    if(_alignTo == ALIGN_TO_BOUNDING_BOX && 
       ((aligningHorizontally && bb.width <= 0 ) || 
        (!aligningHorizontally && bb.height <= 0))) {
        ofLog(OF_LOG_WARNING,"ofGuiRectUtils::distribute : Bounding box is of 0 width and/or height. Aligning to selection.");
        _alignTo = ALIGN_TO_SELECTION;
    }

    float totalRectSpan  = 0;
    ofRectangle boundingBox = bb;
    vector<ofRectangle*> sortedRectangles;
    for(vector<ofRectangle*>::iterator it = rects.begin(); it != rects.end(); ++it) {
        sortedRectangles.push_back((*it));
        totalRectSpan += aligningHorizontally ? (*it)->width : (*it)->height;
    }
    
    // sort rectangle pointers so we can sort them 
    // spatially while preserving the incoming vector 
    // order for layering, etc. 
    sortRectanglesByPosition(sortedRectangles, _objectAlign);
    
    switch(_alignTo) {
        case ALIGN_TO_NONE:
        case ALIGN_TO_ANCHOR:
            /*
            string mess = "ofGuiRectUtils::distribute : ";
            mess += "??";//"ofxGuiGetAlignString(_alignTo); //TODO
            mess += " ignored, aligning to slection.";
            ofLog(OF_LOG_WARNING,mess);
             */
        case ALIGN_TO_SELECTION:
            // if we are aligning to the selection, then we have to make our own bounding box
            // and then we pass through and use it. 
            getBoundingBox(rects, boundingBox);
        case ALIGN_TO_BOUNDING_BOX:
            
            int numElements = sortedRectangles.size() - 1;
            float currentPos  = 0;
            float totalSpan = 0;
            float increment = 0;
            
            ofRectangle* firstRect = sortedRectangles.front();
            ofRectangle* lastRect  = sortedRectangles.back();
            
            // set the position of the first and last elements.
            // when we cycle through the rest of the rects,
            // we will calculate our spacing during the first rect
            // and then we will ignore the very last rect, as we
            // already set the position of first and last below.
            if(aligningHorizontally) {
                firstRect->x = boundingBox.x;
                lastRect->x  = boundingBox.x + boundingBox.width - lastRect->width;
            } else {
                firstRect->y = boundingBox.y;
                lastRect->y  = boundingBox.y + boundingBox.height - lastRect->height;
            }


            //int i = 0;
            
            // go through all squares, except the last
            for(vector<ofRectangle*>::iterator it = sortedRectangles.begin(); it != sortedRectangles.end(); ++it) {
                ofRectangle* r = (*it); // get the pointer
                
                bool isFirst = (r == firstRect); // make a note to see if we are on the first element
                
                switch(_objectAlign) {
                    case ALIGN_NONE: // ALIGN_NONE will result in a left align
                    case ALIGN_LEFT:
                        
                        if(isFirst) {
                            totalSpan = lastRect->x - firstRect->x;
                            increment = totalSpan / numElements;
                            currentPos = r->x;
                        } else {
                            r->x = currentPos;
                        }
                        currentPos += increment;
                        break;
                    case ALIGN_RIGHT:
                        if(isFirst) {
                            totalSpan      = (lastRect->x + lastRect->width) - (firstRect->x + firstRect->width);
                            increment      = totalSpan / numElements;
                            currentPos     = (firstRect->x + firstRect->width);
                        } else {
                            r->x = (currentPos - r->width);
                        }
                        currentPos += increment;
                        break;
                    case ALIGN_CENTER_X:
                        if(isFirst) {
                            totalSpan      = (lastRect->x + lastRect->width / 2.0f) - (firstRect->x + firstRect->width / 2.0f);
                            increment      = totalSpan / numElements;
                            currentPos     = firstRect->x + (firstRect->width) / 2.0f;
                        } else {
                            r->x = (currentPos - r->width / 2.0f);
                        }
                        currentPos += increment;
                        break;
                    case ALIGN_JUSTIFY_X:
                        if(isFirst) {
                            totalRectSpan -= (firstRect->width + lastRect->width);
                            totalSpan      = (lastRect->x) - (firstRect->x + firstRect->width) - totalRectSpan;
                            increment      = totalSpan / numElements;
                            currentPos     = firstRect->x;
                        } else {
                            r->x = currentPos;
                        }
                        currentPos += (r->width + increment);
                        break;
                    // vertical alignment
                    case ALIGN_TOP:
                        if(isFirst) {
                            totalSpan      = lastRect->y - firstRect->y;
                            increment      = totalSpan / numElements;
                            currentPos     = r->y;
                        } else {
                            r->y = currentPos;
                        }
                        currentPos += increment;
                        break;
                    case ALIGN_BOTTOM:
                        if(isFirst) {
                            totalSpan      = (lastRect->y + lastRect->height) - (firstRect->y + firstRect->height);
                            increment      = totalSpan / numElements;
                            currentPos     = (firstRect->y + firstRect->height);
                        } else {
                            r->y = (currentPos - r->height);
                        }
                        currentPos += increment;
                        break;
                    case ALIGN_BASELINE: // BASELINE ALIGN IS NOT IMPLEMENTED, BUT COULD BE, FOR NOW, IT IS 
                                         // LIKE ALIGNING TO THE CENTER Y POSITION.
                    case ALIGN_CENTER_Y:
                        if(isFirst) {
                            totalSpan      = (lastRect->y + lastRect->height / 2.0f) - (firstRect->y + firstRect->height / 2.0f);
                            increment      = totalSpan / numElements;
                            currentPos     = firstRect->y + (firstRect->height) / 2.0f;
                        } else {
                            r->y = (currentPos - r->height / 2);
                        }
                        currentPos += increment;
                        break;
                    case ALIGN_JUSTIFY_Y:
                        if(isFirst) {
                            totalRectSpan -= (firstRect->height + lastRect->height);
                            totalSpan      = (lastRect->y) - (firstRect->y + firstRect->height) - totalRectSpan;
                            increment      = totalSpan / numElements;
                            currentPos     = firstRect->y;
                        } else {
                            r->y = (currentPos);
                        }
                        currentPos += (r->height + increment);
                        break;
                }   
                
            }
    }
}
//--------------------------------------------------------------
// like distribute, but doesn't rely on the max and min places to fit
void ofxGuiRectUtils::stack(vector<ofRectangle*>& rects, 
                            ofxGuiAlign selfAlign,
                            ofxGuiAlign hGroupAlign, 
                            ofxGuiAlign vGroupAlign,
                            float spacing,
                            ofPoint anchor,
                            bool reverseStackOrder) {

    ofRectangle bb = ofRectangle(anchor,0,0);

    bool isSelfAlignHorizontal = !isHorizontalAlignment(selfAlign); // opposite
    
    // self align the rects
    ofxGuiRectUtils::align(rects,selfAlign,ALIGN_LEFT,ALIGN_TO_BOUNDING_BOX,bb);

    int numElements = rects.size() - 1;
    float currentPos = 0;
    float totalSpan = 0;
    float increment = 0;
    
    if(isSelfAlignHorizontal) {
        currentPos = anchor.x;
    } else {
        currentPos = anchor.y;
    }
    
    // make a local copy that is ordered in reverse
    vector<ofRectangle*> selected = rects;
    if(reverseStackOrder) {
        reverse(selected.begin(), selected.end());
    }
    
    for(vector<ofRectangle*>::iterator it = selected.begin(); it != selected.end(); ++it) {
        ofRectangle* r = (*it); // get the pointer
        
        if(isSelfAlignHorizontal) {
            r->x = currentPos;
            increment = r->width + spacing;
            currentPos += increment;
        } else {
            r->y = currentPos;
            increment = r->height + spacing;
            currentPos += increment;                
        }
    }

    // now do group alignment
    ofRectangle groupBox;
    getBoundingBox(selected, groupBox);
    
    // do final vert and horz group adjustments and short circuit if needed
        for(vector<ofRectangle*>::iterator it = selected.begin(); it != selected.end(); ++it) {
            ofRectangle* r = (*it); // get the pointer

            // move everything to a common
            // vAlign TOP, hAlign LEFT situation
            if(selfAlign == ALIGN_BOTTOM) {
                r->y += groupBox.height;
            } else if(selfAlign == ALIGN_RIGHT) {
                r->x += groupBox.width;
            } else if(selfAlign == ALIGN_CENTER_X) {
                r->x += groupBox.width / 2.0f;
            } else if(selfAlign == ALIGN_CENTER_Y) {
                r->y += groupBox.height / 2.0f;
            }
            
            // now make group corrections
            if(hGroupAlign == ALIGN_RIGHT) {
                r->x -= groupBox.width;
            } else if(hGroupAlign == ALIGN_CENTER_X) {
                r->x -= groupBox.width / 2.0f;
            }
            
            if(vGroupAlign == ALIGN_TOP) {
                r->y -= groupBox.height;
            } else if(vGroupAlign == ALIGN_CENTER_Y) {
                r->y -= groupBox.height / 2.0f;
            }
        }
}


//--------------------------------------------------------------
void ofxGuiRectUtils::wrap(vector<ofRectangle*>& rects, 
                           ofRectangle& boundingBox,
                           float horizontalSpace,
                           float verticalSpace,
                           ofxGuiAlign hAlign,
                           ofxGuiAlign vLineAlign,
                           float lineHeight) {
    
    // a grid of rects.  each inner rect group represents a "line"
    vector< vector<ofRectangle*> > rows;
    vector<ofRectangle*>* currentLineRef;

    bool firstTime = true;
    float currentX = 0;
    float currentY = 0;
    
    // first pass is to go through and make lines of the appropriate length
    for(vector<ofRectangle*>::iterator it = rects.begin(); it != rects.end(); ++it) {
        ofRectangle* r = (*it); // get the pointer
        
        if(firstTime || (currentX + r->width) > boundingBox.width) {
            if(firstTime) {
                firstTime = false;
            } else {
                cout << "\tNUM COLS=" << currentLineRef->size() << endl;
            }
            

            
            vector<ofRectangle*> newLine;
            rows.push_back(newLine);
            currentLineRef = &newLine;
            
        }
        
        currentLineRef->push_back(r);
        currentX += (r->width + horizontalSpace);
    }
    
    
    cout << "NUM ROWS=" << rows.size() << endl;
    
    // second pass horizontal alignment
    
    
    // third pass vertical alignment
    
    
}
/*
//--------------------------------------------------------------
void ofxGuiRectUtils::tile(vector<ofRectangle*>& rects, ofRectangle& boundingBox) {
}
 */
//--------------------------------------------------------------
void ofxGuiRectUtils::cascade(vector<ofRectangle*>& rects, ofRectangle& boundingBox, ofPoint offset) {

    float currentX = boundingBox.x;
    float currentY = boundingBox.y;
    
    int currentRow = 0;
    int currentColumn = 0;
    
    for(vector<ofRectangle*>::iterator it = rects.begin(); it != rects.end(); ++it) {
        ofRectangle* r = (*it); // get the pointer
        
        if((currentY + r->height) > (boundingBox.y + boundingBox.height)) {
            // new row, new column
            currentColumn++;
            currentX = currentColumn * offset.x + boundingBox.x;
            currentRow = 0;//++;
            currentY = boundingBox.y;// = currentRow * offset.y + boundingBox.y;
        } 
        
        r->x = currentX;
        r->y = currentY;
        
        currentX += offset.x;
        currentY += offset.y;
    
    }
    
}
//--------------------------------------------------------------
void ofxGuiRectUtils::getExtrema(vector<ofRectangle*>& rects, ofxGuiRange& _x, ofxGuiRange& _y, ofxGuiRange& _width, ofxGuiRange& _height) {
    // set to min
    _x.invertExtrema();
    _y.invertExtrema();
    _width.invertExtrema();
    _height.invertExtrema();
    
    for(vector<ofRectangle*>::iterator it = rects.begin(); it != rects.end(); ++it) {
        _x.expandToFit((*it)->x);
        _y.expandToFit((*it)->y);
        _width.expandToFit((*it)->width);
        _height.expandToFit((*it)->height);
    }
}

//--------------------------------------------------------------
void ofxGuiRectUtils::getBoundingBox(vector<ofRectangle*>& rects, ofRectangle& boundingBox) {
    ofxGuiRange _x, _y;
    _x.invertExtrema(); // this sets MIN to abs max
    _y.invertExtrema(); // this sets MAX to abs min
    
    for(vector<ofRectangle*>::iterator it = rects.begin(); it != rects.end(); ++it) {
        _x.expandToFit((*it)->x);
        _y.expandToFit((*it)->y);
        _x.expandToFit((*it)->x + (*it)->width);
        _y.expandToFit((*it)->y + (*it)->height);
    }
    
    boundingBox.x = _x.getMin();
    boundingBox.y = _y.getMin();
    boundingBox.width = _x.getMax() -_x.getMin();
    boundingBox.height = _y.getMax() -_y.getMin();
}


//--------------------------------------------------------------
void ofxGuiRectUtils::selectRectangles(vector<ofRectangle*>& toTest, vector<ofRectangle*>& selected, const ofRectangle boundingBox, bool enclosed) {
    selected.clear();
    for(vector<ofRectangle*>::iterator it = toTest.begin(); it != toTest.end(); ++it) {
        if(enclosed) {
            if(contains(&boundingBox, (*it))) {
                selected.push_back((*it));
            }
        } else {
            if(intersect(&boundingBox, (*it))) {
                selected.push_back(*it);
            }
        }
    }
}

//--------------------------------------------------------------
void ofxGuiRectUtils::selectRectangles(vector<ofRectangle*>& toTest, vector<ofRectangle*>& selected, ofPoint pnt, bool findAll) {
    selected.clear();
    for(vector<ofRectangle*>::iterator it = toTest.begin(); it != toTest.end(); ++it) {
        if((*it)->inside(pnt)) {
            selected.push_back((*it));
            if(!findAll) break;
        }
    }
}

//--------------------------------------------------------------
void ofxGuiRectUtils::sortRectanglesByPosition(vector<ofRectangle*>& rects,
                           ofxGuiAlign _align) {

    switch(_align) {
        case ALIGN_NONE:
            // ALIGN is interpreted by 
            // HORIZONTAL ALIGNMENTS
        case ALIGN_LEFT:
            sort(rects.begin(), rects.end(), sortByLeftBorders);
            break;
        case ALIGN_RIGHT:
            sort(rects.begin(), rects.end(), sortByRightBorders);
            break;
        case ALIGN_JUSTIFY_X:
        case ALIGN_CENTER_X:
            sort(rects.begin(), rects.end(), sortByHorizontalCenters);
            break;
            // VERTICAL ALIGNMENTS
        case ALIGN_BASELINE:
        case ALIGN_TOP:
            sort(rects.begin(), rects.end(), sortByTopBorders);
            break;
        case ALIGN_BOTTOM:
            sort(rects.begin(), rects.end(), sortByBottomBorders);
            break;
        case ALIGN_JUSTIFY_Y:
        case ALIGN_CENTER_Y:
            sort(rects.begin(), rects.end(), sortByVerticalCenters);
            break;
    }            
}


//--------------------------------------------------------------
void ofxGuiRectUtils::sortRectanglesByWidth(vector<ofRectangle*>& rects) {
    sort(rects.begin(), rects.end(), sortByWidths);
}

//--------------------------------------------------------------
void ofxGuiRectUtils::sortRectanglesByHeight(vector<ofRectangle*>& rects) {
    sort(rects.begin(), rects.end(), sortByHeights);
}

//--------------------------------------------------------------
void ofxGuiRectUtils::sortRectanglesByArea(vector<ofRectangle*>& rects) {
    sort(rects.begin(), rects.end(), sortByArea);
}

//--------------------------------------------------------------
void ofxGuiRectUtils::sortRectanglesByPerimieter(vector<ofRectangle*>& rects) {
    sort(rects.begin(), rects.end(), sortByPerimeter);
}

//--------------------------------------------------------------
string ofxGuiRectUtils::toString(ofRectangle* rect) {
    string s = "";
    s += ofToString(rect->x) + ", " + ofToString(rect->y) + " | "; 
    s += ofToString(rect->width) + ", " + ofToString(rect->height);
    return s;
}

//--------------------------------------------------------------
bool ofxGuiRectUtils::isHorizontalAlignment(ofxGuiAlign align) {
    switch(align) {
        case ALIGN_NONE:
        case ALIGN_LEFT:
        case ALIGN_RIGHT:
        case ALIGN_JUSTIFY_X:
        case ALIGN_CENTER_X:
            return true;
        case ALIGN_BASELINE:
        case ALIGN_TOP:
        case ALIGN_BOTTOM:
        case ALIGN_JUSTIFY_Y:
        case ALIGN_CENTER_Y:
            return false;
    }            

}





