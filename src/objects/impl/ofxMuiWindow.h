
#pragma once

#include "ofxMuiPanel.h"

class ofxMuiWindow : public ofxMuiPanel {
public:
    ofxMuiWindow(const string& _name, int _x, int _y, int _width, int _height, bool _enabled = true);
    ofxMuiWindow(const string& _name, int _x, int _y,bool _enabled = true);
    ofxMuiWindow(const string& _name, bool _enabled = true);
    ofxMuiWindow(bool _enabled = true);
    virtual ~ofxMuiWindow();
    
    void update();
    void draw();	// called every frame to draw object
    
    ofxMuiPanel*    addTab(const string& name = "");

    void    minimize();
    void    maximize();
    void    toggleMaxMin();

    void    setTab(int tabNumber);
    int     getNumTabs() const;
    
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
    
    ofxMuiButton*	enableDisableButton;
    ofxMuiButton*	minMaxButton;

private:
    
    int currentTab;
    vector<ofxMuiPanel*> tabs;

};