#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	gui = ofxSharedMui(new ofxMui());
    
    pad = ofxMultiTouchInput::Instance();

    int nObjects = 20;
    
    for(int i = 0; i < nObjects; i++) {
        
        int rw = ofRandom(100,200);
        int rh = ofRandom(100,200);
        
        int rx = ofRandom(0,ofGetWidth()-rw);
        int ry = ofRandom(0,ofGetHeight()-rh);
        
        ofxMuiObject* obj = new ofxMuiObject(rx,ry,rw,rh);
        
        obj->setIsDragMoveable(true);

        gui->addGuiObject(obj);
    }
    
}

//--------------------------------------------------------------
void testApp::update(){
}

//--------------------------------------------------------------
void testApp::draw(){
    ofSetColor(255);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo) {
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg) {
}