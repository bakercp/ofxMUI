//
//  ofxGuiObjectDefaults.h
//  BasicExample
//
//  Created by Christopher Baker on 7/24/11.
//  Copyright 2011 School of the Art Institute of Chicago. All rights reserved.
//

#pragma once

#include "ofMain.h"
#include "ofxGuiConstants.h"
#include "ofxGuiColor.h"
#include "ofxGuiIcon.h"
#include "ofxGuiBoxProperties.h"
#include "ofxGuiTrueTypeFont.h"

// The goal of this class is to provide an easy way for people to 
// set their own skins / default values for the gui.  It uses a standard
// Singleton pattern, which seems to be controversial ... but it
// seems to make the most sense for settings like this.

//--------------------------------------------------------------
static bool layoutDebug = true; // useful for viewing layout debugging
//--------------------------------------------------------------



class ofxGuiDefaults {
public:
    static ofxGuiDefaults& getInstance()
    {
        static ofxGuiDefaults instance; // Guaranteed to be destroyed.
        // Instantiated on first use.
        return instance;
    }

    
    bool loadDefaultsFromXML(string file) {
        // defaults can be loaded here statically!
        // ... someday
        return true;
    }
    
    //--------------------------------------------------------------
    // STATIC SHARED VARS FOR OFXGUIOBJECT /////////////////////////
    //--------------------------------------------------------------
    //      These variables are initialized in the .cpp file.
    //      They can be set during ofxGui initialization and all 
    //      subsequent objects will use them as defaults.
    //      See below for actual descriptions.
    
    bool enableContentBoxClipping; // should use GLSCISSORS to clip content to the content box 
    
    ofxGuiBoxProperties boxProperties;
    
    // COLORS
    ofxGuiColor cBox, cBorder, cPadding, cContent, cHit;
    
    ofxGuiColor cText;
    
    ofxGuiColor cActiveAreaForeground;
    ofxGuiColor cActiveAreaBackground;
    ofxGuiColor cActiveAreaFrame;
    
    ofxGuiColor cShadow;
    
    // SHADOWS
    bool        doShadow;
    ofVec2f     shadowOffset;
    
    // ALPHA
    float       alphaScale;

    // FONTS
    
    ofxGuiTrueTypeFont* getFont(ofxGuiSize fontSize);
    ofxGuiTrueTypeFont* getXXSmallFont();
    ofxGuiTrueTypeFont* getXSmallFont();
    ofxGuiTrueTypeFont* getSmallFont();
    ofxGuiTrueTypeFont* getMediumFont();
    ofxGuiTrueTypeFont* getLargeFont();
    ofxGuiTrueTypeFont* getXLargeFont();
    ofxGuiTrueTypeFont* getXXLargeFont();
    
    // SHARED
    ofxGuiBoxProperties sharedLabelBoxProperties;
    ofxGuiBoxProperties sharedLabelCleanBoxProperties;
    
    ofxGuiBoxProperties valueLabelBoxProperties;
    
    //--------------------------------------------------------------
    // MOUSE/KEYBOARD //////////////////////////////////////////////
    //--------------------------------------------------------------
    
    // are we looking for keyboard up or keyboard down?
    bool keyboardOnPress;
    
    char keyboardIncrease;
    char keyboardDecrease;
    char keyboardToggle;
    char keyboardMinMax;
    char keyboardEnableDisable;
    
    float incrementFloat;
    float incrementInt;
    
    int   displayPrecision;
    
    //--------------------------------------------------------------
    // XXXXXXXXXXXXXX //////////////////////////////////////////////
    //--------------------------------------------------------------
    
    // WINDOWS
    ofxGuiBoxProperties windowBoxProperties;
    ofxGuiIconName windowBoxMinMaxIcon;
    ofxGuiIconName windowBoxEnableDisableIcon;
    
    // HITS
    ofxGuiBoxProperties hitBoxProperties;
    
    // PANELS
    ofxGuiBoxProperties panelBoxProperties;
    
    // LABEL
    ofxGuiBoxProperties labelBoxProperties;
    
    // TOOLTIP
    ofxGuiBoxProperties tooltipBoxProperties;
    ofVec2f             tooltipOffset;
    int                 tooltipWaitDelay;
    int                 tooltipFadeDelay;

    // BUTTON
    ofxGuiBoxProperties buttonBoxProperties;
    int                 buttonWidth;  // TODO: obsolete?
    int                 buttonHeight; // TODO: obsolete?
    bool                buttonRoundFrame;
    
    // SLIDER
    ofxGuiBoxProperties sliderBoxProperties;
    ofxGuiBoxProperties sliderLabelBoxProperties;
    ofOrientation   sliderOrientation;
    bool                sliderUseHandle;
    int                 sliderHandleSize;
    int                 sliderWidth;
    int                 sliderHeight;
    
    bool                sliderEnableRange;
    int                 sliderRangeHandleSize;

    
    // COLOR PICKER
    ofxGuiBoxProperties colorPickerBoxProperties;
    int                 colorPickerWidth;
    int                 colorPickerHeight;
    int                 colorPickerPreviewHeight;
    int                 colorPickerEyeDropperZoom;
    int                 colorPickerEyeDropperWidth;
    int                 colorPickerEyeDropperHeight;
    
    // KNOB
    ofxGuiBoxProperties knobBoxProperties;
    int                 knobWidth;
    int                 knobHeight;

    // KNOB
    ofxGuiBoxProperties numberBoxBoxProperties;
    int                 numberBoxWidth;
    int                 numberBoxHeight;

    int                 dataHistoryLength;
    
    //--------------------------------------------------------------
    // SHARED IMAGES ///////////////////////////////////////////////
    //--------------------------------------------------------------

    void loadCustomIcon(ofxGuiIconName icon, string fileOn, string fileOff) {
        ofxGuiIcon* ico = getIcon(icon);
        
        if(ico != NULL) {
            ico->getIcon(true)->loadImage(fileOn);
            ico->getIcon(false)->loadImage(fileOff);
        } else {
            icons[icon] = ofxGuiIcon(fileOn,fileOff);
            icons[icon].getIcon(true)->loadImage(fileOn);
            icons[icon].getIcon(false)->loadImage(fileOff);
        }
    }
    
    ofxGuiIcon* getIcon(ofxGuiIconName icon) {
        iconsIterator = icons.find(icon);

        if(iconsIterator != icons.end()) {
            return &(*iconsIterator).second;
        } else {
            return NULL;
        }
    }
    
    // FONTS
    ofxGuiTrueTypeFont xxSmallFont;
    ofxGuiTrueTypeFont xSmallFont;
    ofxGuiTrueTypeFont smallFont;
    ofxGuiTrueTypeFont mediumFont;
    ofxGuiTrueTypeFont largeFont;
    ofxGuiTrueTypeFont xLargeFont;
    ofxGuiTrueTypeFont xxLargeFont;
    
    
private:
    
    ofxGuiDefaults();
    // Dont forget to declare these two. You want to make sure they
    // are unaccessable otherwise you may accidently get copies of
    // your singelton appearing.
    ofxGuiDefaults(ofxGuiDefaults const&); // Don't Implement
    void operator=(ofxGuiDefaults const&); // Don't implement
    
    void initWindow();
    void initKeyboard();
    void initShared();
    void initButton();
    void initPanel();
    void initLabel();
    void initTooltip();
    void initSlider();
    void initKnob();
    void initNumberBox();
    
    void initColorPicker();

    void initFonts();
    void initIcons();
    
    //--------------------------------------------------------------
    // STATIC SHARED ASSETS ////////////////////////////////////////
    //--------------------------------------------------------------
    map<ofxGuiIconName, ofxGuiIcon> icons;
    map<ofxGuiIconName, ofxGuiIcon>::iterator iconsIterator;
    
    string baseDir;
    string iconsDir;
    string fontsDir;
    
};