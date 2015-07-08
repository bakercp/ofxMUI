#include "ofApp.h"


void ofApp::setup()
{
    ofSetLogLevel(OF_LOG_VERBOSE);

    mui = std::make_unique<Layout::Document>();
    mui->addPointerDeviceFilter(ofx::PointerEventArgs::TYPE_MOUSE);

    float width = 100;
    float height = 100;
    float halfWidth = width / 2;
    float halfHeight = height / 2;
    float padding = 4;
    float halfPadding = padding / 2;

    auto panelA0 = std::make_unique<Panel>(64, 64, 512, 512);
    panelA0->setId("A0");
//
//    auto panelB0 = std::make_unique<Panel>(16, 16, 256, 256);
//    panelB0->setId("B0");
//
//    auto panelB1 = std::make_unique<Panel>(256, 0, 100, 100);
//    panelB1->setId("B1");
//
//    auto panelC0 = std::make_unique<Panel>(75, 75, 50, 50);
//    panelC0->setId("C0");
//
//    panelB1->attachChild(std::move(panelC0));
//    panelA0->attachChild(std::move(panelB0));
//    panelA0->attachChild(std::move(panelB1));
    mui->attachChild(std::move(panelA0));

    std::cout << ofToString(1, 3, '0') << endl;
    //    mui->doLayout();
}


void ofApp::draw()
{
    ofBackground(0);
}
