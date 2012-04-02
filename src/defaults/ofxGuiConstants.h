//
//  ofxGuiConstants.h
//  BasicExample
//
//  Created by Christopher Baker on 7/21/11.
//  Copyright 2011 School of the Art Institute of Chicago. All rights reserved.
//


#pragma once

enum ofTextAlignHorz {
    OF_TEXT_ALIGN_HORZ_LEFT = 0      ,
    OF_TEXT_ALIGN_HORZ_RIGHT         ,
    OF_TEXT_ALIGN_HORZ_CENTER        ,
    OF_TEXT_ALIGN_HORZ_JUSTIFIED
};

enum ofTextAlignVert {
    OF_TEXT_ALIGN_VERT_TOP = 0       ,
    OF_TEXT_ALIGN_VERT_BOTTOM        ,
    OF_TEXT_ALIGN_VERT_CENTER        ,
    OF_TEXT_ALIGN_VERT_BASELINE
};



enum ofxGuiSize {
    SIZE_NONE = 0,
    SIZE_XXSMALL,
    SIZE_XSMALL,
    SIZE_SMALL,
    SIZE_MEDIUM,
    SIZE_LARGE,
    SIZE_XLARGE,
    SIZE_XXLARGE
};

static string ofxGuiGetSizeString(ofxGuiSize param) {
    switch(param) {
        case SIZE_NONE:
            return "SIZE_NONE";
        case SIZE_XXSMALL:
            return "SIZE_XXSMALL";
        case SIZE_XSMALL:
            return "SIZE_XSMALL";
        case SIZE_SMALL:
            return "SIZE_SMALL";
        case SIZE_MEDIUM:
            return "SIZE_MEDIUM";
        case SIZE_LARGE:
            return "SIZE_LARGE";
        case SIZE_XLARGE:
            return "SIZE_XLARGE";
        case SIZE_XXLARGE:
            return "SIZE_XXLARGE";
    }
}
/*
enum ofOrientation {
    ORIENTATION_NONE = 0,
    ORIENTATION_HORIZONTAL,
    ORIENTATION_VERTICAL
};

static string ofxGuiGetOrientationString(ofOrientation param) {
    switch(param) {
        case ORIENTATION_NONE:
            return "ORIENTATION_NONE";
        case ORIENTATION_HORIZONTAL:
            return "ORIENTATION_HORIZONTAL";
        case ORIENTATION_VERTICAL:
            return "ORIENTATION_VERTICAL";
    }
}
 */
/*
enum ofxGuiPosition {
    POSITION_NONE = 0,
    POSITION_LEFT,
    POSITION_TOP,
    POSITION_RIGHT,
    POSITION_BOTTOM,
    POSITION_CENTER
};

static string ofxGuiGetPositionString(ofxGuiPosition param) {
    switch(param) {
        case POSITION_NONE:
            return "POSITION_NONE";
        case POSITION_LEFT:
            return "POSITION_LEFT";
        case POSITION_TOP:
            return "POSITION_TOP";
        case POSITION_RIGHT:
            return "POSITION_RIGHT";
        case POSITION_BOTTOM:
            return "POSITION_BOTTOM";
    }
}
 */

enum ofxGuiAlign {
    ALIGN_NONE = 0,
    ALIGN_LEFT,
    ALIGN_CENTER_X,
    ALIGN_CENTER_Y,
    ALIGN_RIGHT,
    ALIGN_TOP,
    ALIGN_BOTTOM,
    ALIGN_BASELINE,
    ALIGN_JUSTIFY_X,
    ALIGN_JUSTIFY_Y,
};


static string ofxGuiGetAlignString(ofxGuiAlign param) {
    switch(param) {
        case ALIGN_NONE:
            return "ALIGN_NONE";
        case ALIGN_LEFT:
            return "ALIGN_LEFT";
        case ALIGN_CENTER_X:
            return "ALIGN_CENTER_X";
        case ALIGN_CENTER_Y:
            return "ALIGN_CENTER_Y";
        case ALIGN_RIGHT:
            return "ALIGN_RIGHT";
        case ALIGN_TOP:
            return "ALIGN_TOP"; 
        case ALIGN_BOTTOM:
            return "ALIGN_BOTTOM";
        case ALIGN_BASELINE:
            return "ALIGN_BASELINE";
        case ALIGN_JUSTIFY_X:
            return "ALIGN_JUSTIFY_X";
        case ALIGN_JUSTIFY_Y:
            return "ALIGN_JUSTIFY_Y";
    }
}

enum ofxGuiAlignTo {
    ALIGN_TO_NONE = 0,
    ALIGN_TO_SELECTION,
    ALIGN_TO_ANCHOR,
    ALIGN_TO_BOUNDING_BOX
};


static string ofxGuiGetAlignToString(ofxGuiAlignTo param) {
    switch(param) {
        case ALIGN_TO_NONE:
            return "ALIGN_TO_NONE";
        case ALIGN_TO_SELECTION:
            return "ALIGN_TO_SELECTION";
        case ALIGN_TO_ANCHOR:
            return "ALIGN_TO_ANCHOR";
        case ALIGN_TO_BOUNDING_BOX:
            return "ALIGN_TO_BOUNDINGBOX";

    }
}

