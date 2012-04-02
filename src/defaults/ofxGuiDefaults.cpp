
#include "ofxGuiDefaults.h"

static int ofxGuiDebugIndentLevel = 0;

// handy colors
static int     ALPHA_OFF         = 0;
static int     ALPHA_LOW         = 30;
static int     ALPHA_MEDIUM      = 100;
static int     ALPHA_HIGH        = 200;
static int     ALPHA_ON          = 255;


static ofColor COLOR_LIGHT_BLUE  = ofColor(0,150,194);
static ofColor COLOR_MEDIUM_BLUE = ofColor(36,91,107);
static ofColor COLOR_MEDIUM_GRAY = ofColor(35,42,43);
static ofColor COLOR_DARK_RED    = ofColor(125,0,33);
static ofColor COLOR_LIGHT_RED   = ofColor(209,0,66);
static ofColor COLOR_YELLOW      = ofColor(204,162,65);

static ofColor COLOR_WHITE       = ofColor(255);
static ofColor COLOR_BLACK       = ofColor(0);

static ofColor DEFAULT_COLOR_NORMAL   = ofColor(COLOR_MEDIUM_GRAY,ALPHA_HIGH);
static ofColor DEFAULT_COLOR_HOVER    = ofColor(COLOR_YELLOW,ALPHA_HIGH);
static ofColor DEFAULT_COLOR_ACTIVE   = ofColor(COLOR_MEDIUM_BLUE,ALPHA_LOW);
static ofColor DEFAULT_COLOR_DISABLED = ofColor(COLOR_MEDIUM_GRAY,ALPHA_LOW);

//--------------------------------------------------------------
ofxGuiDefaults::ofxGuiDefaults() {
        
    initShared(); // MUST BE FIRST
    
    initFonts();  // RESOURCES SHOUDL COME SECOND
    initIcons();

    initWindow(); // THEN COMPONENTS
    initButton();
    initPanel();
    initLabel();
    initTooltip();
    initSlider();
    initKnob();
    initNumberBox();
    initColorPicker();
    
    initKeyboard();

}



//--------------------------------------------------------------
void ofxGuiDefaults::initShared() {
    
    
    enableContentBoxClipping = true;
    
    dataHistoryLength = 2; // must always be 2 or greater (i.e. one history value at all times)
    
    // NOT SURE WHY, but this thing is having a terrible time loading fonts ...
    // this was taken from here:
    // http://forum.openframeworks.cc/index.php?topic=3567.0
    #ifdef TARGET_OSX
        // Get the absolute location of the executable file in the bundle.
        CFBundleRef appBundle = CFBundleGetMainBundle();
        CFURLRef	executableURL = CFBundleCopyExecutableURL(appBundle);
        char execFile[4096];
        if (CFURLGetFileSystemRepresentation(executableURL, TRUE, (UInt8 *)execFile, 4096))
        {
            // Strip out the filename to just get the path
            string strExecFile = execFile;
            int found = strExecFile.find_last_of("/");
            string strPath = strExecFile.substr(0, found);
            
            // Change the working directory to that of the executable
            if(-1 == chdir(strPath.c_str())) {
                ofLog(OF_LOG_ERROR, "Unable to change working directory to executable's directory.");
            }
        }
        else {
            ofLog(OF_LOG_ERROR, "Unable to identify executable's directory.");
        }
        CFRelease(executableURL);
    #endif
    
    baseDir = "gui/default/";
    iconsDir = baseDir + "icons/";
    fontsDir = baseDir + "fonts/";
    //  sharedLabelBoxProperties
    //  sharedLabelCleanBoxProperties

    hitBoxProperties = ofxGuiBoxProperties(0);
    
    boxProperties = ofxGuiBoxProperties(2,2,2,2,
                                        4,4,4,4,
                                        2,2,2,2);
    
     
    sharedLabelBoxProperties = boxProperties;
 
    sharedLabelCleanBoxProperties = ofxGuiBoxProperties(3,3,3,3,
                                                        1,1,1,1,
                                                        0,0,0,0);
    
    valueLabelBoxProperties = ofxGuiBoxProperties(4,4,4,4,
                                                  4,4,4,4,
                                                  0,0,0,0);
    
    // default colors
    cBox      = ofxGuiColor(ofColor(255,0,0,50));//,ALPHA_OFF));
    //cBox      = ofxGuiColor(ofColor(255,ALPHA_OFF));
    
    //cBorder      = ofxGuiColor(COLOR_MEDIUM_GRAY);
    cBorder      = ofxGuiColor(ofColor(255,0,0,200));
    
    //cPadding  = ofxGuiColor(DEFAULT_COLOR_NORMAL);
    cPadding  = ofxGuiColor(DEFAULT_COLOR_NORMAL);

    // cContent  = ofxGuiColor(ofColor(COLOR_BLACK,ALPHA_OFF));
    cContent   = ofxGuiColor(ofColor(255,ALPHA_OFF));
    
    cHit   = ofxGuiColor(ofColor(255,ALPHA_OFF));
    
    cText = ofxGuiColor(COLOR_WHITE,
                          COLOR_WHITE, // hover
                          COLOR_WHITE, // active
                          DEFAULT_COLOR_DISABLED  // disabled
                          );
    
    cShadow  = ofxGuiColor(DEFAULT_COLOR_NORMAL, // normal
                           DEFAULT_COLOR_NORMAL, // hover
                           DEFAULT_COLOR_NORMAL, // active
                           DEFAULT_COLOR_DISABLED  // disabled
                           );

    cActiveAreaForeground = ofxGuiColor(COLOR_YELLOW);
    cActiveAreaBackground = ofxGuiColor(COLOR_MEDIUM_BLUE);
    cActiveAreaFrame      = ofxGuiColor(COLOR_LIGHT_BLUE);
    
    /*
    cActiveAreaForeground = ofxGuiColor(COLOR_MEDIUM_BLUE, // normal
                                          COLOR_LIGHT_BLUE, // hover
                                          COLOR_LIGHT_RED, // active
                                          DEFAULT_COLOR_DISABLED  // disabled
                                          );
    
    cActiveAreaBackground = ofxGuiColor(COLOR_MEDIUM_GRAY);
    
    cActiveAreaFrame = ofxGuiColor(COLOR_MEDIUM_GRAY, // normal
                                     COLOR_MEDIUM_BLUE, // hover
                                     COLOR_LIGHT_BLUE, // active
                                     DEFAULT_COLOR_DISABLED  // disabled
                                     );
     */
     
    doShadow = false;
    shadowOffset  = ofVec2f(2,2);
    alphaScale = 1.0;



}

//--------------------------------------------------------------
void ofxGuiDefaults::initWindow() {
    windowBoxProperties = boxProperties;
    windowBoxMinMaxIcon = ICON_PLUSMINUS;
    windowBoxEnableDisableIcon = ICON_X;
}


//--------------------------------------------------------------
void ofxGuiDefaults::initKeyboard() {
    keyboardOnPress = true; // mapped keyboard actions on press or release?
    keyboardIncrease      = '=';
    keyboardDecrease      = '-';
    keyboardToggle        = ' ';
    keyboardMinMax        = 'm';
    keyboardEnableDisable = 'e';
    
    incrementFloat        = 0.5f;
    incrementInt          = 1;
    
    displayPrecision      = 2;
    
}

//--------------------------------------------------------------
void ofxGuiDefaults::initPanel() {
    // PANELS
//    panelBoxProperties = ofxGuiBoxProperties(5,6,6,5,
  //                                          2,2,2,2,
    //                                        1,0,1,0);

    panelBoxProperties = ofxGuiBoxProperties(6,6,6,6,
                                             6,6,6,6,
                                             6,6,6,6);

}

//--------------------------------------------------------------
void ofxGuiDefaults::initLabel() {
    // label
//    labelBoxProperties = ofxGuiBoxProperties(2,2,2,2,
  //                                           2,2,2,2,
    //                                         4,4,4,4);

    labelBoxProperties = ofxGuiBoxProperties(6,6,6,6,
                                             6,6,6,6,
                                             6,6,6,6);

}

//--------------------------------------------------------------
void ofxGuiDefaults::initButton() {
    // BUTTON
    buttonBoxProperties = boxProperties;
    buttonWidth  = 16; // the actual image icon size will take precedence
    buttonHeight = 16; // the actual image icon size will take precedence
    buttonRoundFrame = false;
}

//--------------------------------------------------------------
void ofxGuiDefaults::initTooltip() {
    // TOOLTIP
    tooltipBoxProperties = ofxGuiBoxProperties(6,6,6,6,
                                              2,2,2,2,
                                              1,0,1,0);
    tooltipOffset = ofVec2f(0,25);
    tooltipWaitDelay  = 500;   // ms
    tooltipFadeDelay  = 1000;  // ms

}

//--------------------------------------------------------------
void ofxGuiDefaults::initSlider() {
    // SLIDER
    sliderOrientation = OF_ORIENTATION_DEFAULT;
    sliderBoxProperties = ofxGuiBoxProperties(0,0,0,0,//
                                              0,0,0,0,//
                                              0,0,0,0//
                                              );
    
    //boxProperties;
    sliderHandleSize = 3; // no handle by default;
    sliderUseHandle = true;
    sliderWidth = 120;
    sliderHeight = 20;
    
    sliderEnableRange = false;
    sliderRangeHandleSize = 20;
}

//--------------------------------------------------------------
void ofxGuiDefaults::initKnob() {
    // KNOB
/*
    knobBoxProperties = ofxGuiBoxProperties(0);
*/
    knobBoxProperties = ofxGuiBoxProperties(3);
    knobWidth = 50;
    knobHeight = 50;

}

//--------------------------------------------------------------
void ofxGuiDefaults::initNumberBox() {
    // KNOB
    numberBoxBoxProperties = boxProperties;
    numberBoxWidth = 50;
    numberBoxHeight = 18;
}


//--------------------------------------------------------------
void ofxGuiDefaults::initColorPicker() {
    // COLOR PICKER
    colorPickerBoxProperties = boxProperties;
    colorPickerWidth = 150;
    colorPickerHeight = 150;
    colorPickerPreviewHeight = 13;

    colorPickerEyeDropperZoom = 4;
    colorPickerEyeDropperWidth = 50;
    colorPickerEyeDropperHeight = 50;
}

//--------------------------------------------------------------
void ofxGuiDefaults::initFonts() {
    
    /*
    string xxSmallFontFile = fontsDir + "Lucida Grande.ttf";
    string xSmallFontFile = fontsDir + "Lucida Grande.ttf";
    string smallFontFile = fontsDir + "Lucida Grande.ttf";
    //string smallFontFile = fontsDir + "automat.ttf";
    string mediumFontFile = fontsDir + "verdana.ttf";
    string largeFontFile = fontsDir + "verdana.ttf";
    string xLargeFontFile = fontsDir + "verdana.ttf";
    string xxLargeFontFile = fontsDir + "verdana.ttf";
     */
    
    string xxSmallFontFile = fontsDir + "pf_arma_five.ttf";//automat.ttf";//"Lucida Grande.ttf";
    string xSmallFontFile = fontsDir + "verdana.ttf";//px_sans_nouveaux.ttf";
    string smallFontFile = fontsDir + "verdana.ttf";
    string mediumFontFile = fontsDir + "Lucida Grande.ttf";
    string largeFontFile = fontsDir + "Lucida Grande.ttf";
    string xLargeFontFile = fontsDir + "Lucida Grande.ttf";
    string xxLargeFontFile = fontsDir + "Lucida Grande.ttf";

    
    
    //cout << smallFontFile << endl;
    

    char cCurrentPath[FILENAME_MAX];
    
    if (!getcwd(cCurrentPath, sizeof(cCurrentPath)))
    {
        ofLog(OF_LOG_ERROR, "ofxGuiDefaults: Some error getting the current path.");
        return errno;
    }
    
    cCurrentPath[sizeof(cCurrentPath) - 1] = '\0'; /* not really required */
    
    ofxGuiFont::Settings settings;
    
    settings.bAntiAliased = false;
    settings.bForceAutoHinting = true;
    settings.bUseKerning = true;

    settings.fontFilename = xxSmallFontFile;
    settings.fontSize = 6;
    
    if(!xxSmallFont.loadFont(settings))
        ofLogError("ofxGuiDefaults::initFonts(): failed to load xxSmallFontFile="+xxSmallFontFile);
    
    settings.fontFilename = xSmallFontFile;
    settings.fontSize = 8;
    settings.bAntiAliased = false;
    settings.bForceAutoHinting = true;
    
    if(!xSmallFont.loadFont(settings))
        ofLogError("ofxGuiDefaults::initFonts(): failed to load xSmallFontFile="+xSmallFontFile);

    settings.fontFilename = smallFontFile;
    settings.fontSize = 10;
    settings.bAntiAliased = false;
    settings.bForceAutoHinting = true;

    if(!smallFont.loadFont(settings))
        ofLogError("ofxGuiDefaults::initFonts(): failed to load smallFontFile="+smallFontFile);
    //smallFont.loadFont(smallFontFile,6,true,true);
    
    settings.fontFilename = mediumFontFile;
    settings.fontSize = 12;
    settings.bAntiAliased = false;
    settings.bForceAutoHinting = true;
    
    if(!mediumFont.loadFont(settings))
        ofLogError("ofxGuiDefaults::initFonts(): failed to load mediumFontFile="+mediumFontFile);
    
    settings.fontFilename = largeFontFile;
    settings.fontSize = 14;
    settings.bAntiAliased = true;
    settings.bForceAutoHinting = false;
    
    if(!largeFont.loadFont(settings))
        ofLogError("ofxGuiDefaults::initFonts(): failed to load largeFontFile="+largeFontFile);
    
    settings.fontFilename = xLargeFontFile;
    settings.fontSize = 16;
    settings.bAntiAliased = true;
    settings.bForceAutoHinting = false;

    if(!xLargeFont.loadFont(settings))
        ofLogError("ofxGuiDefaults::initFonts(): failed to load xLargeFontFile="+xLargeFontFile);

    settings.fontFilename = xxLargeFontFile;
    settings.fontSize = 20;
    settings.bAntiAliased = true;
    settings.bForceAutoHinting = false;

    if(!xxLargeFont.loadFont(settings))
        ofLogError("ofxGuiDefaults::initFonts(): failed to load xxLargeFontFile="+xxLargeFontFile);
   }

//--------------------------------------------------------------
void ofxGuiDefaults::initIcons() {
    loadCustomIcon(ICON_DEFAULT,    iconsDir+"stop.gif",    iconsDir+"blank.gif");
    loadCustomIcon(ICON_X,          iconsDir+"close.gif",   iconsDir+"blank.gif");
    loadCustomIcon(ICON_PLUSMINUS,  iconsDir+"add.gif",     iconsDir+"subtract.gif");
    loadCustomIcon(ICON_CHECK,      iconsDir+"check.gif",   iconsDir+"blank.gif");
    loadCustomIcon(ICON_TARGET,      iconsDir+"target.gif",   iconsDir+"blank.gif");
}


//--------------------------------------------------------------
ofxGuiTrueTypeFont* ofxGuiDefaults::getFont(ofxGuiSize fontSize) {
    switch(fontSize) {
        case SIZE_XXSMALL:
            return getXXSmallFont();
        case SIZE_XSMALL:
            return getXSmallFont();
        case SIZE_SMALL:
            return getSmallFont();
        case SIZE_NONE:
        case SIZE_MEDIUM:
            return getMediumFont();
        case SIZE_LARGE:
            return getLargeFont();
        case SIZE_XLARGE:
            return getXLargeFont();
        case SIZE_XXLARGE:
            return getXXLargeFont();
    }
}
//--------------------------------------------------------------
ofxGuiTrueTypeFont* ofxGuiDefaults::getXXSmallFont() {
    return &xxSmallFont;
}
//--------------------------------------------------------------
ofxGuiTrueTypeFont* ofxGuiDefaults::getXSmallFont() {
    return &xSmallFont;
}
//--------------------------------------------------------------
ofxGuiTrueTypeFont* ofxGuiDefaults::getSmallFont() {
    return &smallFont;
}
//--------------------------------------------------------------
ofxGuiTrueTypeFont* ofxGuiDefaults::getMediumFont() {
    return &mediumFont;
}
//--------------------------------------------------------------
ofxGuiTrueTypeFont* ofxGuiDefaults::getLargeFont() {
    return &largeFont;
}
//--------------------------------------------------------------
ofxGuiTrueTypeFont* ofxGuiDefaults::getXLargeFont() {
    return &xLargeFont;
}
//--------------------------------------------------------------
ofxGuiTrueTypeFont* ofxGuiDefaults::getXXLargeFont() {
    return &xxLargeFont;
}


