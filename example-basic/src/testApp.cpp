#include "testApp.h"

//#include "gui.h"

//#include <unistd.h>


//--------------------------------------------------------------
void testApp::setup(){
	//ofSetFrameRate(30);
	ofSetVerticalSync(true);
    
    
    
     /*txt = "Az ZA AW wA AA TLOREM jIDd amet? CONectetur. adipiscing elit Crasporta lectus fermentum turpis bibendum in vehicula ligula pulvinar";.\nEtiam vitae lectus elit, ut aliquet dui. Sed odio eros, ultrices\nfacilisis rhoncus ac, viverra eget dolor. ";Vivamus ac erat a nisi laoreet ultricies. Donec tellus ligula,\ngravida quis laoreet non, scelerisque ac eros. Vestibulum \nelit orci, aliquet eget semper rutrum, aliquet nec arcu. Curabitur tempor iaculis ultricies. Proin vehicula mattis risus sit amet facilisis. Fusce quis pharetra elit. Nunc sodales sollicitudin consequat. Quisque a quam egestas arcu aliquet blandit sed a ligula.\nQuisAzque a sapien sed leo consequat hendrerit eget adipiscing justo. Donec id augue vitae mi dapibus congue. Suspendisse in metus a justo vestibulum ullamcorper\n vitae condimentum arcu. Sed volutpat laoreet odio eget gravida. Suspendisse quis quam quis velit vulputate dignissim. In quis purus placerat enim euismod ultrices. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; Maecenas quis dolor purus, ac congue magna. Sed sit amet justo sit amet dui varius volutpat. In pellentesque interdum arcu, vel aliquet neque faucibus nec. Mauris eget tellus augue. Nam nisl quam, convallis id egestas vel, fringilla ac metus. Quisque sodales purus et velit fringilla aliquam.\nPellentesque a lorem diam. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. Nullam accumsan neque in mauris dignissim eu dapibus diam ultrices. Ut rhoncus, justo a ullamcorper mattis, lectus neque vestibulum nisi, non bibendum justo elit id diam. Vestibulum vel sapien mi. Donec a tortor risus. Ut est neque, molestie accumsan aliquet in, dapibus eget mi. Nam et enim mauris, vitae porttitor nulla. Aenean porttitor leo quis diam mattis at aliquam ante rutrum. Morbi quis ante neque.";*/
      
    
    
  //  txt = "Think it your unique\n designs evaluated.";
//    txt = "Think it your unique\n      (designs) evaluated. ";
    txt = "Think it your unique                          \r\n(designs) evaluated. ";

    
    //    txt = "Think it your unique\n                                       (designs) evaluated. ";
   
//    txt = "Think it your unique                                       designs evaluated. ";
    //txt += "evaluated by experts in typography ";//+ "\n"; 
    
    //txt += "fabulous prizes, recognition and the ";//+ "\n"; 
    //txt += "envy of your peers! Not only that, your ";//+ "\n"; 
    //txt += "work will be offered for sale around ";//+ "\n"; 
    //txt += "the world by the best alternative type ";//+ "\n"; 
    //txt += "foundry going. And that would be ";//+ "\n"; 
    //txt += "us...GarageFonts.";
    
    /*
    txt = "Aay&<=>AbAG$1$2%=$3$4$$$5AXBXKLMN<&CXDXEXFXGXHXXIXJXK\n";
    txt += "XLXMXN?AKLMNXOXPXQXRXSXTXU\n";
*/
    
    
    ofxGuiFont::Settings settings;
    
    settings.fontFilename = "Calibri.ttf";//automat.ttf";//gui/default/fonts/ProggySquare.ttf";
    settings.fontSize = 30;
    settings.bAntiAliased = true;
    settings.bForceAutoHinting = false;
    settings.bUseKerning = true;
    
    ttf.loadFont(settings);
    
    bb = ofRectangle(0,0,82    ,300);
    offsets = ttf.getCharacterOffsets(txt,bb);
    
    /*
    cout << "in here: " << endl;
    for(int i = 0; i < offsets.size(); i++) {
        cout << (char)offsets[i].c << " " << offsets[i].offset << endl;
    }
    cout << "done." << endl;
    */
     
     
    /*
    settings.bUseKerning = false;
    ttf2.loadFont(settings);
    
    cout << "hasKerning=" << ttf.hasKerning() << endl;
    cout << "Az" << ttf.getHorizontalKerning('A','z') << endl;

    cout << "hasKerning=" << ttf2.hasKerning() << endl;
    cout << "Az" << ttf2.getHorizontalKerning('A','z') << endl;
*/
    
    
    //    ttf.loadFont("verdana.ttf",96,true,true,true);
//    ttf.loadFont("verdana.ttf",96,true,true,true);
//    ttf.loadFont("verdana.ttf",96,true,true,true);
//    ttf.loadFont("verdana.ttf",96,true,true,true);
  //  ttf.setLetterSpacing(3);
   // ttf.setSpaceSize(100);

    //    img.loadImage("tree.jpeg");
    
	gui = new ofxGui(ofGetWidth(), ofGetHeight());

    /*
    tb = new ofxGuiTextBlock(&ttf);
    tb->setBlockWidth(500);
    
    tb->setText(txt);
    
    tb->setLineBreakMode(LINE_BREAK_MODE_WORD);
    tb->setLineTruncationMode(LINE_TRUNCATION_MODE_CLIP);
    
//    tb->setCapsStyle(LABEL_CAPS_TITLE_CASE);
//    tb->setCapsStyle(LABEL_CAPS_TOGGLE_CASE);
      */
    float xPos = 600;
    float yPos = 0;
    float w = 300;
    float h = 50;
  
//    nb0 = new ofxGuiNumberBox("XXSMALL/DEFAULT",xPos,yPos);
//    gui->addGuiObject(nb0);

    knob0 = new ofxGuiKnob("The KNOB", xPos,yPos);
   knob0->setBounds(0,1024);
    knob0->setRange(255,768);
    gui->addGuiObject(knob0);
     
    
    
    
    lab0 = new ofxGuiLabel("XXSMALL/DEFAULT", xPos, yPos);//, w, h);
    lab0->setFontSize(SIZE_XXSMALL);
    //lab0->setOrientation(OF_ORIENTATION_90_LEFT);
    gui->addGuiObject(lab0);
    lab1 = new ofxGuiLabel("XSMALL/DEFAULT", xPos, lab0->getBottom());//,w, h);
    lab1->setFontSize(SIZE_XSMALL);
    gui->addGuiObject(lab1);
    lab2 = new ofxGuiLabel("SMALL/DEFAULT", xPos, lab1->getBottom());//,w, h);
    lab2->setFontSize(SIZE_SMALL);
    gui->addGuiObject(lab2);
    lab3 = new ofxGuiLabel("MED/DEFAULT", xPos, lab2->getBottom());//,w, h);
    lab3->setFontSize(SIZE_MEDIUM);
    gui->addGuiObject(lab3);
    lab4 = new ofxGuiLabel("LARGE/DEFAULT", xPos, lab3->getBottom());//,w, h);
    lab4->setFontSize(SIZE_LARGE);
    gui->addGuiObject(lab4);
    lab5 = new ofxGuiLabel("XLARGE/DEFAULT", xPos, lab4->getBottom());//,w, h);
    lab5->setFontSize(SIZE_XLARGE);
    gui->addGuiObject(lab5);
    lab6 = new ofxGuiLabel("XXLARGE/DEFAULT", xPos, lab5->getBottom());//,w, h);
    lab6->setFontSize(SIZE_XXLARGE);
    gui->addGuiObject(lab6);
    lab6->setOrientation(OF_ORIENTATION_180);

    
    lab0i = new ofxGuiLabel("LABEL 0", 250, 150);
    lab0i->setFontSize(SIZE_SMALL);
    lab0i->setOrientation(OF_ORIENTATION_DEFAULT);
    gui->addGuiObject(lab0i);
    lab1i = new ofxGuiLabel("LABEL 1", 250, 150 + 50);
    lab1i->setFontSize(SIZE_MEDIUM);
    lab1i->setOrientation(OF_ORIENTATION_DEFAULT);
    gui->addGuiObject(lab1i);
    lab2i = new ofxGuiLabel("LABEL 2", 250, 150 + 100);
    lab2i->setFontSize(SIZE_LARGE);
    lab2i->setOrientation(OF_ORIENTATION_DEFAULT);
    gui->addGuiObject(lab2i);
    

    
    button = new ofxGuiButton("MY BIG ASS BUTTON", ofGetWidth() / 2, ofGetHeight() / 2);
    gui->addGuiObject(button);

    
    
    sliderH = new ofxGuiSlider("SLIDER ONE AND A HALF",100,100);//,10,10);
    //sliderH->disableLabel();
    //sliderH->setSliderHeight(10);
    //sliderH->getLabel()->setFontSize(SIZE_XSMALL);
    //sliderH->getValueLabel()->setFontSize(SIZE_XSMALL);
    sliderH->setBoundsMin(-1);
    sliderH->setBoundsMax(1);
    sliderH->setRange(-.5, .8);
    sliderH->setValue(0.5);
    gui->addGuiObject(sliderH);
    
    sliderV = new ofxGuiSlider("SLIDER TWO",100,150);//,10,10);
    sliderV->setOrientation(OF_ORIENTATION_90_LEFT);
    sliderV->setBoundsMin(-1000);
    sliderV->setBoundsMax(1000);
    sliderV->setValue(0.5);
    gui->addGuiObject(sliderV);
    
    slider0 = new ofxGuiSlider("SLIDER TWO",400,50);//,10,10);
    slider0->setOrientation(OF_ORIENTATION_90_LEFT);
    slider0->setLabelPosition(ALIGN_RIGHT);
    slider0->setBoundsMin(-1000);
    slider0->setBoundsMax(1000);
    slider0->setValue(0.5);
    slider0->setRange(-900, 344);
    gui->addGuiObject(slider0);

    
    slider1 = new ofxGuiSlider("SLIDER TWO",400,300);//,10,10);
    slider1->setLabelPosition(ALIGN_TOP);
    slider1->setBoundsMin(-1000);
    slider1->setBoundsMax(1000);
    slider1->setValue(0.5);
    slider1->setRange(-900, 344);
    gui->addGuiObject(slider1);


    
    button = new ofxGuiButton("BUTTON 0", 10, 200);
    button0 = new ofxGuiButton("BUTTON 1", 10, 200+40);
    button0->setButtonIcon(ICON_TARGET);
    button0->setRoundFrame(true);
    
    button1 = new ofxGuiButton("BUTTON 2", 10, 200+80);
    button1->setButtonIcon(ICON_X);
    
    button2 = new ofxGuiButton("BUTTON 3", 10, 200+120);
    button2->setButtonIcon(ICON_PLUSMINUS);
    button3 = new ofxGuiButton("BUTTON 3", 10, 200+160);
    button3->setButtonIcon(ICON_CHECK);
    button4 = new ofxGuiButton("BUTTON 3", 10, 200+200);
    
    gui->addGuiObject(button);
    gui->addGuiObject(button0);
    gui->addGuiObject(button1);
    gui->addGuiObject(button2);
    gui->addGuiObject(button3);
    gui->addGuiObject(button4);
     
     
   
   // panel = gui->addWindow("TESTING PANEL", 10, 10);
    
    /*
	panel1 = gui->addWindow("TESTING PANEL 2", 20, 20);

    
	//picker = panel->addColorPicker("MCP");
	
    
    slider = panel->addSlider("My Slider");
	//slider->setUseHandle(true);
	//slider->setHandleSize(30);
	//slider->setOrientation(ORIENTATION_VERTICAL);

	slider = panel->addSlider("My Slider HORZ");

	knob = panel->addKnob("My Knob");
	nb = panel->addNumberBox("My NumberBox");

	//obj = new ofxGuiButton("BUTTON", 600,600);
	//obj->getLabel()->setName("b_U_TTTOON");
	//gui->addGuiObject(obj);

	slider = new ofxGuiSlider("MY SLIDER", 500, 500);
	slider->setSliderWidth(400);
	slider->setSliderHeight(50);
	//slider->setGlobalMinMax(0.0, 100.0);
	//slider->setMinMax(25.0f, 89.0f);
	slider->disableLabels();
	gui->addGuiObject(slider);

    */

	setupGui();
	bkg = 0;
	ofBackground(0); //35,42,43,10);//bkg);
    
}

void testApp::newButtonEvent(const void * sender, int & i){
	/*
	    //cout << "gout a callback ... " << endl;

	    if(sender == myButton) {
	            cout << "go ta new button events!!!" << endl;

	    } else {
	            cout << "got a button event, but it was from someone else ... ";
	    }
	 */
}



//--------------------------------------------------------------
void testApp::update(){
    //tb->update();
}
void testApp::draw(){
    
    
    /*
    ofPushMatrix();
    
    float xx = ofGetWidth() / 2.0f;
    float yy = ofGetHeight() / 2.0f;
    
    ofTranslate(xx,yy);
 
    
    ofFill();
    ofSetColor(255);
    
    if(true) {
        
        bb.set(0,0, mouseX - xx, mouseY - yy);
        
        ofFill();
        ofSetColor(255);
        ttf.drawString(txt,bb);
        
        ofNoFill();
        ofSetColor(255,255,0);
        ofRect(bb);
    } else {
        ttf.drawString(offsets);
        
        for(int i = 0; i < offsets.size(); i++) {
            ofNoFill();
            ofSetColor(255,255,0);
            ofCharacter vvv = offsets[i];
            if(vvv.c == ' ') {
                ofRect(vvv.offset, 5,10);
            } else {
                ofEllipse(vvv.offset, 5,5);
            }
        }
        
        ofNoFill();
        
        
        ofSetColor(255,255,0);
        ofRect(bb);
    }

    
    
    */
    
    
    /*
    ofRectangle bb = ttf.getStringBoundingBox(vv, true);
    ofRectangle bb2 = ttf.getStringBoundingBox(vv, false);
    
    ofNoFill();
    ofSetColor(255,255,0);
    ofRect(bb);
    ofSetColor(0,255,0);
    ofRect(bb2);
    ofFill();
    ofSetColor(255);
    */
    
    

    
    
  //  for(int i = 0; i < vv.size(); i++) {
  //      ofFill();
  //      ofSetColor(0,255,255);
  //      ofCharacter vvv = vv[i];
        
   //     cout << "VVV=" << (char)vvv.c << " VV=" << (char)offsets[i].c << endl;
        
        
  //      ttf.drawChar(vvv.c, vvv.offset);
        
  //      ofEllipse(vvv.offset, 5,5);
  //  }
    

    
    
  //  ofNoFill();
  //  ofSetColor(255,255,0);
  //  ofRect(bb);
    
    
    /*
    ofTranslate(0,mouseY);
    //tb->draw(0,0);
    ofRectangle bb3 = ttf2.getStringBoundingBox(t, 0,0, false);
    ofNoFill();
    ofSetColor(255,255,0);
    ofRect(bb3);
    ofFill();
    ofSetColor(255,255,0);
    vector<ofCharacterOffset> v = ttf2.drawString(t,0,0);
    */
    /*
    
    
    ofTranslate(0,200);
    ofNoFill();
    ofSetColor(255,255,0);
    ofRect(bb);
    ttf.drawStringAsShapes(t,0,0);
    
    ofTranslate(0,200);

    ofNoFill();
    ofSetColor(0,255,0);
    float stringWidth = ttf.singleLineWidth(t,s0,t.length());
    ofRect(0,-ttf.getSize(),stringWidth,ttf.getSize());
    ttf.drawString(t,0,0);
    
   // cout << stringWidth << "==" << bb.width << endl;
    */
    
    ofPopMatrix();
    
    
    
    
    
    //img.draw(0,0);
    
    
    /*
    ofFill();
    ofSetColor(255);
    //img.draw(0,0);
    
	//ofxGuiLabel* panelEDBValueLabel = panel->enableDisableButton->getValueLabel();
	//ofxGuiLabel* panelEDBLabel = panel->enableDisableButton->getLabel();

	ofSetColor(0,255,0);
	ofNoFill();
	//ofCircle(panelEDBValueLabel->getBoxScreenPosition(), 10);

	//panel->minMaxButton;

	ofSetColor(255,255,0);

	ofPushMatrix();
	ofTranslate(mouseX,mouseY); //zz);

//    obj->getLabel()->get
	//  ofRect(obj->getLabel()->getHitBox());

	ofPopMatrix();

	ofSetColor(0,255,0);
	ofFill();


	ofDrawBitmapString(ofToString(ofGetFrameRate()), ofGetWidth()-100, 20);

	ofSetColor(255,255,0);

    
    
    
    if( mouseX < 100) {
        ofSetColor(255,255,0);
    } else {
        ofSetColor(255,0,0);
    }
    
    ofLine(100,0,100,ofGetHeight());
    
    ofRect(0,300,100,100);
    
	string txt;
     */
	/*
	   txt = "";
	   txt += "NB >> " + nb->getName() + " : " + ofToString(nb->getHitBoxScreenPosition()) + "\n";
	   txt += "NB >> VALUE_LABEL >> " + nb->getValueLabel()->getParent()->getName() + "(" + ofToString(nb->getValueLabel()->getParent()->getHitBoxScreenPosition()) + ")" + " : " + ofToString(nb->getValueLabel()->getHitBoxScreenPosition()) + "\n";
	   txt += "NB >> LABEL >>" + nb->getLabel()->getParent()->getName() + " : " + ofToString(nb->getLabel()->getHitBoxScreenPosition()) + "\n";
	 */

//    txt += "";

	//ofDrawBitmapString(txt, 100,300);

    /*
	txt = "";
	txt += "SLIDER >> " + ofToString(slider->getHitBoxScreenPosition()) + "\n";
	txt += "SLIDER >> VALUE_LABEL >> " + ofToString(slider->getValueLabel()->getHitBoxScreenPosition()) + "\n";
	txt += "SLIDER >> LABEL >>" + ofToString(slider->getLabel()->getHitBoxScreenPosition()) + "\n";
     */
     
	//ofDrawBitmapString(txt, 600,300);
	/*
	   ofDrawBitmapString(          picker->getDebugString(), 100,400);
	   ofDrawBitmapString(obj->getLabel()->getDebugString(), 100,500);
	   ofDrawBitmapString(            obj->getDebugString(), 100,600);

	 */
    
    /*
    ofEnableAlphaBlending();
    ofFill();
    ofSetColor(255,127);
    
    for(int i = 0 ; i < rects.size(); i++) {
        ofRect(rects[i]);
    }
    
    ofNoFill();
    ofSetColor(0,255,0,127);
    ofRect(bb);
    ofDisableAlphaBlending();
     */
    
}

void testApp::printModifiers() {
    
    /*
    //cout << "NUM KEYS PRESSED => " << endl; 
    cout << "CTRL=" << ofGetModifierPressed(OF_KEY_CTRL) << " ";
    cout << "ALT="  << ofGetModifierPressed(OF_KEY_ALT) << " ";
    cout << "SHIFT=" << ofGetModifierPressed(OF_KEY_SHIFT) << " ";
    cout << endl;
     */
     

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    printModifiers();
    
    if(key == 'a') {
        sliderH->setBounds(ofxGuiRange(-1000,1000));
        sliderH->setRange(-100,100); 
    } else if(key == 'b') {
        sliderH->setBounds(ofxGuiRange(-1,1));
        sliderH->clearRange();
    } else if(key == 'c') {
        sliderH->enableLabels();
    } else if(key == 'd') {
        sliderH->disableLabel();
    }
    
    if(key == '-') {
        s1--;
        if(s1 < 0) s1 = 0;
    } else if (key == '+') {
        s1++;
    }
    
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    printModifiers();
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    printModifiers();
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    printModifiers();
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    printModifiers();
    
    /*
    
    ofRectangle oo = ofRectangle(x,y,ofRandom(30),ofRandom(30));
    rects.push_back(oo);
    
     */
   // ofxGuiBox::getBoundingBox(rects, bb);
    
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    printModifiers();
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


void testApp::setupGui(){
}


