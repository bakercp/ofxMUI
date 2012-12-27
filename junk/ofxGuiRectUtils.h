//
//  ofxGuiRectUtils.h
//  BasicExample
//
//  Created by Christopher Baker on 1/16/12.
//  Copyright (c) 2012 School of the Art Institute of Chicago. All rights reserved.
//

#pragma once

#include "ofMain.h"
#include "ofxGuiConstants.h"
#include "ofxGuiRange.h"

class ofxGuiRectUtils {
public:
    // alignment and distribution

    // utilities for rectangles
    
//    static ofRectangle  intersection(const ofRectangle* rect0, 
//                                     const ofRectangle* rect1); 
//    
//    static bool intersect(const ofRectangle* rect0, 
//                          const ofRectangle* rect1); 
//    
//    static bool contains(const ofRectangle* r0, 
//                         const ofRectangle* r1);

    
    // utilities for alignment and distribution

    static void vertAlign(ofRectangle* rect, 
                          ofxGuiAlign   align, 
                          const ofRectangle bb,
                          ofPoint rectAnchor = ofPoint(0,0));

    static void horzAlign(ofRectangle* rect, 
                      ofxGuiAlign   align, 
                      const ofRectangle bb,
                      ofPoint rectAnchor = ofPoint(0,0));

    
    static void align(ofRectangle* rect, 
                      ofxGuiAlign   _hAlign, 
                      ofxGuiAlign   _vAlign,
                      const ofRectangle bb,
                      ofPoint rectAnchor = ofPoint(0,0));

    static void align(vector<ofRectangle*>& rects, 
                      ofxGuiAlign   _objectAlign = ALIGN_LEFT,
                      ofxGuiAlign   _anchorAlign = ALIGN_LEFT, 
                      ofxGuiAlignTo    _alignTo = ALIGN_TO_SELECTION, 
                      const ofRectangle bb = ofRectangle(0,0,0,0));
    
    static void distribute(vector<ofRectangle*>& rects, 
                           ofxGuiAlign   _objectAlign = ALIGN_LEFT,
                           ofxGuiAlignTo _alignTo = ALIGN_TO_SELECTION, 
                           const ofRectangle bb = ofRectangle(0,0,0,0));
    
    // utilities for stacking and flowing
    static void stack(vector<ofRectangle*>& rects, 
                      ofxGuiAlign selfAlign = ALIGN_LEFT,
                      ofxGuiAlign hGroupAlign = ALIGN_LEFT, 
                      ofxGuiAlign vGroupAlign = ALIGN_TOP,
                      float spacing = 0,
                      ofPoint anchor = ofPoint(0,0),
                      bool reverseStackOrder = false);
    
    
    static void wrap(vector<ofRectangle*>& rects,
                     ofRectangle& boundingBox,
                     float horizontalSpace = 0,
                     float verticalSpace = 0,
                     ofxGuiAlign hAlign = ALIGN_LEFT,
                     ofxGuiAlign vLineAlign = ALIGN_TOP,
                     float lineHeight = 0);
    
    /*
    static void tile(vector<ofRectangle*>& rects, 
                     ofRectangle& boundingBox);
    */
    
    static void cascade(vector<ofRectangle*>& rects, 
                        ofRectangle& boundingBox, 
                        ofPoint offset = ofPoint(25,50));
    
    /*
     // TODO:
     // https://github.com/jakesgordon/bin-packing/

    static void pack(vector<ofRectangles*>& rects,
                     ofRectangle& boundingBox);
    */
    
    // statistical utilities
    static void getExtrema(vector<ofRectangle*>& rects, 
                           ofxGuiRange& _x, 
                           ofxGuiRange& _y, 
                           ofxGuiRange& _width, 
                           ofxGuiRange& _height);
    
    static void getBoundingBox(vector<ofRectangle*>& rects, 
                               ofRectangle& boundingBox);
    
    
    static void selectRectangles(vector<ofRectangle*>& toTest, 
                                 vector<ofRectangle*>& selected, 
                                 const ofRectangle boundingBox, 
                                 bool enclosed=true);
    
    static void selectRectangles(vector<ofRectangle*>& toTest, 
                                 vector<ofRectangle*>& selected, 
                                 const ofPoint pnt, 
                                 bool findAll = false);

    // sorting
    static void sortRectanglesByPosition(vector<ofRectangle*>& rects,
                               ofxGuiAlign _align = ALIGN_LEFT);
    static void sortRectanglesByWidth(vector<ofRectangle*>& rects);
    static void sortRectanglesByHeight(vector<ofRectangle*>& rects);
    static void sortRectanglesByArea(vector<ofRectangle*>& rects);
    static void sortRectanglesByPerimieter(vector<ofRectangle*>& rects);

    // utils
    static string toString(ofRectangle*);

    
    
protected:
    
    static bool isHorizontalAlignment(ofxGuiAlign align);
    
    static bool sortByLeftBorders(      ofRectangle* r0, ofRectangle* r1) { return (r0->x             ) < (r1->x             ); }
    static bool sortByTopBorders(       ofRectangle* r0, ofRectangle* r1) { return (r0->y             ) < (r1->y             ); }
    static bool sortByRightBorders(     ofRectangle* r0, ofRectangle* r1) { return (r0->x + r0->width ) < (r1->x + r1->width ); }
    static bool sortByBottomBorders(    ofRectangle* r0, ofRectangle* r1) { return (r0->y + r0->height) < (r1->y + r1->height); }
    static bool sortByHorizontalCenters(ofRectangle* r0, ofRectangle* r1) { return (r0->x             ) < (r1->x             ); }
    static bool sortByVerticalCenters(  ofRectangle* r0, ofRectangle* r1) { return (r0->y             ) < (r1->y             ); }
    static bool sortByWidths(           ofRectangle* r0, ofRectangle* r1) { return (r0->width         ) < (r1->width         ); }
    static bool sortByHeights(          ofRectangle* r0, ofRectangle* r1) { return (r0->height        ) < (r1->height        ); }
    static bool sortByArea(             ofRectangle* r0, ofRectangle* r1) { return (r0->width*r0->height) < (r1->width*r1->height); }
    static bool sortByPerimeter(        ofRectangle* r0, ofRectangle* r1) { return (2*(r0->width+r0->height)) < (2*(r1->width+r1->height)); }

};

