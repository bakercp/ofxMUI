
#pragma once

#include "ofxGuiPanel.h"

class ofxGuiWindow : public ofxGuiPanel {
public:
    ofxGuiWindow(string _name, int _x, int _y, int _width, int _height, bool _enabled = true);
    ofxGuiWindow(string _name, int _x, int _y,bool _enabled = true);
    ofxGuiWindow(string _name, bool _enabled = true);
    ofxGuiWindow(bool _enabled = true);
    virtual ~ofxGuiWindow();
    
    void update();
    void draw();	// called every frame to draw object
    
    ofxGuiPanel*    addTab(string name = "");

    void    minimize();
    void    maximize();
    void    toggleMaxMin();

    void    setTab(int tabNumber);
    int     getNumTabs();
    
protected:
    
    void init();
    
    //--------------------------------------------------------------
    // INHERITED FROM SUPERCLASS ///////////////////////////////////
    //--------------------------------------------------------------
    
    void doContentBoxLayout();
    void buildFromXml();
    void saveToXml();

	//--------------------------------------------------------------
    // VARIABLES ///////////////////////////////////////////////////
    //--------------------------------------------------------------
    
    ofRectangle		minimizedRect;
    bool			isMinimized;
    
    ofxGuiButton*	enableDisableButton;
    ofxGuiButton*	minMaxButton;

private:
    
    int currentTab;
    vector<ofxGuiPanel*> tabs;

};