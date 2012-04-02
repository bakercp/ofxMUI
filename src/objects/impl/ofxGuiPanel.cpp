
//--------------------------------------------------------------
#include "ofxGuiPanel.h"

//--------------------------------------------------------------
ofxGuiPanel::ofxGuiPanel(string _name, int _x, int _y, int _width, int _height, bool _enabled) : 
ofxGuiLabelledObject(_name, _x, _y, _width, _height, _enabled) {
    init();
}

//--------------------------------------------------------------
ofxGuiPanel::ofxGuiPanel(string _name, int _x, int _y,bool _enabled) : 
ofxGuiLabelledObject(_name, _x, _y, _enabled) {
    init();
}

//--------------------------------------------------------------
ofxGuiPanel::ofxGuiPanel(string _name,bool _enabled) :
ofxGuiLabelledObject(_name, _enabled) {
    init();
}

//--------------------------------------------------------------
ofxGuiPanel::ofxGuiPanel(bool _enabled) : 
ofxGuiLabelledObject(_enabled) {
    init();
}

//--------------------------------------------------------------
ofxGuiPanel::~ofxGuiPanel() {}

//--------------------------------------------------------------
void ofxGuiPanel::init() {
    setObjectType("PANEL");
    setTooltip("");
    requestBoxLayout();
}

//--------------------------------------------------------------
void ofxGuiPanel::draw() {
    
    ofPushStyle();
	ofPushMatrix(); // initial push
    
    ofTranslate(getHitBoxPosition());

    ofxRect(0, 0, width, height);
    ofNoFill();	
	
	ofPopMatrix();
    ofPopStyle();     
}

//--------------------------------------------------------------
ofxGuiButton* ofxGuiPanel::addButton(string name) {
    ofxGuiButton* button = new ofxGuiButton(name);
    addChild(button);
    return button;
}

//--------------------------------------------------------------
ofxGuiButton* ofxGuiPanel::addTrigger(string name) {
    ofxGuiButton* button = new ofxGuiButton(name);
    button->setButtonType(TYPE_TRIGGER);
    addChild(button);
    return button;
}

//--------------------------------------------------------------
ofxGuiButton* ofxGuiPanel::addSwitch(string name) {
    ofxGuiButton* button = new ofxGuiButton(name);
    button->setButtonType(TYPE_SWITCH);
    addChild(button);
    return button;
}


//--------------------------------------------------------------
ofxGuiColorPicker* ofxGuiPanel::addColorPicker(string name) {
    ofxGuiColorPicker* picker = new ofxGuiColorPicker(name);
    addChild(picker);
    return picker;
}
 
//--------------------------------------------------------------
ofxGuiSlider* ofxGuiPanel::addSlider(string name) {
    ofxGuiSlider* slider = new ofxGuiSlider(name);
    addChild(slider);
    return slider;
}

//--------------------------------------------------------------
ofxGuiKnob* ofxGuiPanel::addKnob(string name) {
    ofxGuiKnob* knob = new ofxGuiKnob(name);
    addChild(knob);
    return knob;
}

//--------------------------------------------------------------
ofxGuiNumberBox* ofxGuiPanel::addNumberBox(string name) {
    ofxGuiNumberBox* numberBox = new ofxGuiNumberBox(name);
    addChild(numberBox);
    return numberBox;
}


/*
ofxGuiSlider* ofxGuiPanel::addSlider(string _name, 
                                     int _width, int _height, 
                                     float _min, float _max, 
                                     float _value, 
                                     int _display, 
                                     int _steps)
{
	ofxGuiSlider* obj = new ofxGuiSlider();
	obj->init(_name, mBorder, height - mBorder + getOffset(), _width, _height, _min, _max, _value, _display, _steps);
	addChild(obj);
	return obj;
}
 */

//--------------------------------------------------------------
/*
ofxGuiXYPad* ofxGuiPanel::addXYPad(string _name, int _width, int _height, ofVec2f _min, ofVec2f _max, ofVec2f _value, int _display, int _steps)
{
	ofxGuiXYPad* obj = new ofxGuiXYPad();
	obj->init(_name, mBorder, height - mBorder + getOffset(), _width, _height, _min, _max, _value, _display, _steps);
	addChild(obj);
	return obj;
}
*/

//--------------------------------------------------------------
/*
ofxGuiPoints* ofxGuiPanel::addPoints(string _name, int _width, int _height, ofVec2f _min, ofVec2f _max, ofVec2f _value, int _display, int _steps)
{
	ofxGuiPoints* obj = new ofxGuiPoints();
	obj->init(_name, mBorder, height - mBorder + getOffset(), _width, _height, _min, _max, _value, _display, _steps);
	addChild(obj);
	return obj;
}
*/

/*
//--------------------------------------------------------------
ofxGuiLabelledButton* ofxGuiPanel::addButton(string _name, int _width, int _height, int _value, int _mode, string _image)
{
	ofxGuiLabelledButton* obj = new ofxGuiLabelledButton();
	obj->init(_name, mBorder, height - mBorder + getOffset(), _width, _height, _value, _mode, _image);
	addChild(obj);
	return obj;
}

//--------------------------------------------------------------
ofxGuiLabelledButton* ofxGuiPanel::addButtonTrigger(string name)
{
	return addButton(name, OFXGUI_BUTTON_WIDTH, OFXGUI_BUTTON_HEIGHT, ofxGuiButtonType_Off, ofxGuiButtonType_Trigger, "");
}

//--------------------------------------------------------------
ofxGuiLabelledButton* ofxGuiPanel::addButtonSwitch(string name)
{
	return addButton(name, OFXGUI_BUTTON_WIDTH, OFXGUI_BUTTON_HEIGHT, ofxGuiButtonType_Off, ofxGuiButtonType_Switch, "");
}
*/

//--------------------------------------------------------------

/*
ofxGuiFiles* ofxGuiPanel::addFiles(string name, int _width, int _height, string value, string subPath, string suffix)
{
	ofxGuiFiles* obj = new ofxGuiFiles();
	obj->init(name, mBorder, height - mBorder + getOffset(), _width, _height, value, subPath, suffix);
	addChild(obj);
	return obj;
}
 */

//--------------------------------------------------------------

/*
ofxGuiColor* ofxGuiPanel::addColor(string name, int _width, int _height, ofRGBA value, int mode)
{
	ofxGuiColor* obj = new ofxGuiColor();
	obj->init(name, mBorder, height - mBorder + getOffset(), _width, _height, value, mode);
	addChild(obj);
	return obj;
}
 */

//--------------------------------------------------------------

/*
ofxGuiMatrix* ofxGuiPanel::addMatrix(string name, int _width, int _height, int _xGrid, int _yGrid, int value, int mode, int spacing)
{
	ofxGuiMatrix* obj = new ofxGuiMatrix();
	obj->init(name, mBorder, height - mBorder + getOffset(), _width, _height, _xGrid, _yGrid, value, mode, spacing);
	addChild(obj);
	return obj;
}
*/
 
//--------------------------------------------------------------

/*
ofxGuiScope* ofxGuiPanel::addScope(string name, int _width, int _height, int _length, ofVec2f value, int mode)
{
	ofxGuiScope* obj = new ofxGuiScope();
	obj->init(name, mBorder, height - mBorder + getOffset(), _width, _height, _length, value, mode);
	addChild(obj);
	return obj;
}
 */


//--------------------------------------------------------------

/*
ofxGuiKnob* ofxGuiPanel::addKnob(string name, int _width, int _height, int _min, int _max, float value, int display, int steps)
{
	ofxGuiKnob* obj = new ofxGuiKnob();
	obj->init(name, mBorder, height - mBorder + getOffset(), _width, _height, _min, _max, value, display, steps);
	addChild(obj);
	return obj;
}

//--------------------------------------------------------------
ofxGuiRadar* ofxGuiPanel::addRadar(string name, int _width, int _height, int _min, int _max, float value, int display, int steps)
{
	//	todo
	return NULL;
}

//--------------------------------------------------------------
ofxGuiSwitch* ofxGuiPanel::addSwitch(string name, int _width, int _height, int _min, int _max, int value, const string* paramStrings)
{
	ofxGuiSwitch* obj = new ofxGuiSwitch();
	obj->init(name, mBorder, height - mBorder + getOffset(), _width, _height, _min, _max, value, paramStrings);
	addChild(obj);
	return obj;
}
*/



//--------------------------------------------------------------
void ofxGuiPanel::buildFromXml() {	
}

//--------------------------------------------------------------
void ofxGuiPanel::saveToXml()
{   /*
	ofxGuiObject* tmpObj;
	
	int id = name();
	
	mGlobals->mXml.setValue("OBJECT:BORDER", mBorder, id);
	mGlobals->mXml.setValue("OBJECT:SPACING", mSpacing, id);
	mGlobals->mXml.pushTag("OBJECT", id);
	
	for(int i = 0; i < childObjects.size(); i++)
	{
		tmpObj = (ofxGuiObject*)childObjects.at(i);
		tmpObj->saveToXml();
	}
	
	mGlobals->mXml.popTag();
     */
}


//--------------------------------------------------------------
void ofxGuiPanel::doContentBoxLayout() {

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



