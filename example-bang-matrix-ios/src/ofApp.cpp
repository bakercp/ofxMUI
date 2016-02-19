#include "ofApp.h"


void ofApp::setup()
{
    ofEnableAlphaBlending();

    ofSetFrameRate(60);

    ofSetLogLevel(OF_LOG_VERBOSE);

    ofSetOrientation(OF_ORIENTATION_90_LEFT);

//    mui.setGeometry(ofRectangle(40,40,200,200));
//    mui.setAutoFillScreen(false);

    int bangWidth = 50;
    int bangHeight = 50;

    for (std::size_t w = 0; w < MATRIX_WIDTH; ++w)
    {
        for (std::size_t h = 0; h < MATRIX_HEIGHT; ++h)
        {
            std::string bangName = "bang_" + ofToString(w) + "x" + ofToString(h);

            int currentX = (bangWidth + 20) * w;
            int currentY = (bangHeight + 20) * h;

            MUI::Button* bang = mui.addChild<MUI::CheckBoxButton>(bangName, // name
                                                                  currentX,  // x-position
                                                                  currentY,  // y-position
                                                                  bangHeight,  // width
                                                                  bangHeight // height
                                                                  );

            bang->addListener(this, &ofApp::onBang);
            
            buttons.push_back(bang);
        }
    }

    ofSetBackgroundColor(0);
}


void ofApp::update()
{
}


void ofApp::draw()
{
}


void ofApp::exit()
{
}


#if defined(TARGET_OF_IOS)
void ofApp::lostFocus()
{
}


void ofApp::gotFocus()
{
}


void ofApp::gotMemoryWarning()
{
}


void ofApp::deviceOrientationChanged(int newOrientation)
{
    if (newOrientation == OF_ORIENTATION_90_LEFT)
    {
        ofSetOrientation(OF_ORIENTATION_90_LEFT);
    }
    else if (newOrientation == OF_ORIENTATION_90_RIGHT)
    {
        ofSetOrientation(OF_ORIENTATION_90_RIGHT);
    }
    
}
#endif


void ofApp::onBang(const void* sender, bool& value)
{
    cout << "got bang = > " << value << endl;
}

