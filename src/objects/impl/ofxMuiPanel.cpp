
//--------------------------------------------------------------
#include "ofxMuiPanel.h"

//--------------------------------------------------------------
ofxMuiPanel::ofxMuiPanel(const string& _name, int _x, int _y, int _width, int _height, bool _enabled) : 
ofxMuiLabelledObject(_name, _x, _y, _width, _height, _enabled) {
    init();
}

//--------------------------------------------------------------
ofxMuiPanel::ofxMuiPanel(const string& _name, int _x, int _y,bool _enabled) : 
ofxMuiLabelledObject(_name, _x, _y, _enabled) {
    init();
}

//--------------------------------------------------------------
ofxMuiPanel::ofxMuiPanel(const string& _name,bool _enabled) :
ofxMuiLabelledObject(_name, _enabled) {
    init();
}

//--------------------------------------------------------------
ofxMuiPanel::ofxMuiPanel(bool _enabled) : 
ofxMuiLabelledObject(_enabled) {
    init();
}

//--------------------------------------------------------------
ofxMuiPanel::~ofxMuiPanel() {}

//--------------------------------------------------------------
void ofxMuiPanel::init() {
    setObjectType("PANEL");
    setTooltip("");
    requestBoxLayout();
}

//--------------------------------------------------------------
void ofxMuiPanel::draw() {
    
    ofPushStyle();
	ofPushMatrix(); // initial push
    
    ofTranslate(getHitBoxPosition());

    ofxRect(0, 0, width, height);
    ofNoFill();	
	
	ofPopMatrix();
    ofPopStyle();     
}

//--------------------------------------------------------------
ofxMuiButton* ofxMuiPanel::addButton(string name) {
    ofxMuiButton* button = new ofxMuiButton(name);
    addChild(button);
    return button;
}

//--------------------------------------------------------------
ofxMuiButton* ofxMuiPanel::addTrigger(string name) {
    ofxMuiButton* button = new ofxMuiButton(name);
    button->setButtonType(TYPE_TRIGGER);
    addChild(button);
    return button;
}

//--------------------------------------------------------------
ofxMuiButton* ofxMuiPanel::addSwitch(string name) {
    ofxMuiButton* button = new ofxMuiButton(name);
    button->setButtonType(TYPE_SWITCH);
    addChild(button);
    return button;
}


////--------------------------------------------------------------
//ofxMuiColorPicker* ofxMuiPanel::addColorPicker(string name) {
//    ofxMuiColorPicker* picker = new ofxMuiColorPicker(name);
//    addChild(picker);
//    return picker;
//}
 
//--------------------------------------------------------------
ofxMuiSlider* ofxMuiPanel::addSlider(string name) {
    ofxMuiSlider* slider = new ofxMuiSlider(name);
    addChild(slider);
    return slider;
}

//--------------------------------------------------------------
ofxMuiKnob* ofxMuiPanel::addKnob(string name) {
    ofxMuiKnob* knob = new ofxMuiKnob(name);
    addChild(knob);
    return knob;
}

//--------------------------------------------------------------
ofxMuiNumberBox* ofxMuiPanel::addNumberBox(string name) {
    ofxMuiNumberBox* numberBox = new ofxMuiNumberBox(name);
    addChild(numberBox);
    return numberBox;
}


/*
ofxMuiSlider* ofxMuiPanel::addSlider(string _name, 
                                     int _width, int _height, 
                                     float _min, float _max, 
                                     float _value, 
                                     int _display, 
                                     int _steps)
{
	ofxMuiSlider* obj = new ofxMuiSlider();
	obj->init(_name, mBorder, height - mBorder + getOffset(), _width, _height, _min, _max, _value, _display, _steps);
	addChild(obj);
	return obj;
}
 */

//--------------------------------------------------------------
/*
ofxMuiXYPad* ofxMuiPanel::addXYPad(string _name, int _width, int _height, ofVec2f _min, ofVec2f _max, ofVec2f _value, int _display, int _steps)
{
	ofxMuiXYPad* obj = new ofxMuiXYPad();
	obj->init(_name, mBorder, height - mBorder + getOffset(), _width, _height, _min, _max, _value, _display, _steps);
	addChild(obj);
	return obj;
}
*/

//--------------------------------------------------------------
/*
ofxMuiPoints* ofxMuiPanel::addPoints(string _name, int _width, int _height, ofVec2f _min, ofVec2f _max, ofVec2f _value, int _display, int _steps)
{
	ofxMuiPoints* obj = new ofxMuiPoints();
	obj->init(_name, mBorder, height - mBorder + getOffset(), _width, _height, _min, _max, _value, _display, _steps);
	addChild(obj);
	return obj;
}
*/

/*
//--------------------------------------------------------------
ofxMuiLabelledButton* ofxMuiPanel::addButton(string _name, int _width, int _height, int _value, int _mode, string _image)
{
	ofxMuiLabelledButton* obj = new ofxMuiLabelledButton();
	obj->init(_name, mBorder, height - mBorder + getOffset(), _width, _height, _value, _mode, _image);
	addChild(obj);
	return obj;
}

//--------------------------------------------------------------
ofxMuiLabelledButton* ofxMuiPanel::addButtonTrigger(string name)
{
	return addButton(name, ofxMui_BUTTON_WIDTH, ofxMui_BUTTON_HEIGHT, ofxMuiButtonType_Off, ofxMuiButtonType_Trigger, "");
}

//--------------------------------------------------------------
ofxMuiLabelledButton* ofxMuiPanel::addButtonSwitch(string name)
{
	return addButton(name, ofxMui_BUTTON_WIDTH, ofxMui_BUTTON_HEIGHT, ofxMuiButtonType_Off, ofxMuiButtonType_Switch, "");
}
*/

//--------------------------------------------------------------

/*
ofxMuiFiles* ofxMuiPanel::addFiles(string name, int _width, int _height, string value, string subPath, string suffix)
{
	ofxMuiFiles* obj = new ofxMuiFiles();
	obj->init(name, mBorder, height - mBorder + getOffset(), _width, _height, value, subPath, suffix);
	addChild(obj);
	return obj;
}
 */

//--------------------------------------------------------------

/*
ofxMuiColor* ofxMuiPanel::addColor(string name, int _width, int _height, ofRGBA value, int mode)
{
	ofxMuiColor* obj = new ofxMuiColor();
	obj->init(name, mBorder, height - mBorder + getOffset(), _width, _height, value, mode);
	addChild(obj);
	return obj;
}
 */

//--------------------------------------------------------------

/*
ofxMuiMatrix* ofxMuiPanel::addMatrix(string name, int _width, int _height, int _xGrid, int _yGrid, int value, int mode, int spacing)
{
	ofxMuiMatrix* obj = new ofxMuiMatrix();
	obj->init(name, mBorder, height - mBorder + getOffset(), _width, _height, _xGrid, _yGrid, value, mode, spacing);
	addChild(obj);
	return obj;
}
*/
 
//--------------------------------------------------------------

/*
ofxMuiScope* ofxMuiPanel::addScope(string name, int _width, int _height, int _length, ofVec2f value, int mode)
{
	ofxMuiScope* obj = new ofxMuiScope();
	obj->init(name, mBorder, height - mBorder + getOffset(), _width, _height, _length, value, mode);
	addChild(obj);
	return obj;
}
 */


//--------------------------------------------------------------

/*
ofxMuiKnob* ofxMuiPanel::addKnob(string name, int _width, int _height, int _min, int _max, float value, int display, int steps)
{
	ofxMuiKnob* obj = new ofxMuiKnob();
	obj->init(name, mBorder, height - mBorder + getOffset(), _width, _height, _min, _max, value, display, steps);
	addChild(obj);
	return obj;
}

//--------------------------------------------------------------
ofxMuiRadar* ofxMuiPanel::addRadar(string name, int _width, int _height, int _min, int _max, float value, int display, int steps)
{
	//	todo
	return NULL;
}

//--------------------------------------------------------------
ofxMuiSwitch* ofxMuiPanel::addSwitch(string name, int _width, int _height, int _min, int _max, int value, const string* paramStrings)
{
	ofxMuiSwitch* obj = new ofxMuiSwitch();
	obj->init(name, mBorder, height - mBorder + getOffset(), _width, _height, _min, _max, value, paramStrings);
	addChild(obj);
	return obj;
}
*/



//--------------------------------------------------------------
void ofxMuiPanel::buildFromXml() {	
}

//--------------------------------------------------------------
void ofxMuiPanel::saveToXml()
{   /*
	ofxMuiObject* tmpObj;
	
	int id = name();
	
	mGlobals->mXml.setValue("OBJECT:BORDER", mBorder, id);
	mGlobals->mXml.setValue("OBJECT:SPACING", mSpacing, id);
	mGlobals->mXml.pushTag("OBJECT", id);
	
	for(int i = 0; i < childObjects.size(); i++)
	{
		tmpObj = (ofxMuiObject*)childObjects.at(i);
		tmpObj->saveToXml();
	}
	
	mGlobals->mXml.popTag();
     */
}


//--------------------------------------------------------------
void ofxMuiPanel::doContentBoxLayout() {

    int currentX = 0;
    int currentY = 0;
    
    int maxX = 0;
    int maxY = 0;
        
    // TODO: center this
    int labelY = 0;
    label->setPosition(currentX, labelY);
    
    maxX = MAX(maxX, label->getPosition().x + label->getWidth());

    currentY+=label->getHeight();
     
    currentX = 0;


   for(int i = 0; i < childObjects.size(); i++) {
         if(childObjects[i] != label &&
             childObjects[i] != valueLabel) {
            currentX = 0;
             childObjects[i]->setPosition(currentX,currentY);
            currentY += childObjects[i]->getHeight();
             maxX = MAX(maxX,childObjects[i]->getWidth());
        }
    
    }
    
    setHitBox(0, 0, maxX, currentY);
    setContentBoxWidth(getHitBoxWidth());
    setContentBoxHeight(getHitBoxHeight());
}



