// =============================================================================
//
// Copyright (c) 2009-2015 Christopher Baker <http://christopherbaker.net>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// =============================================================================


#include "ofApp.h"


void ofApp::setup()
{
	ofSetBackgroundColor(0);
	ofAddListener(mui.pointerDown.event(), this, &ofApp::onPointerEvent);
	index = 0;


	std::string fn = ofGetTimestampString() + ".jpg";

	ofBuffer buffer("hello there");

	ofBufferToFile(fn, buffer);

}


void ofApp::update()
{
	slit.update();
}


void ofApp::draw()
{
	slit.draw();
}


void ofApp::onPointerEvent(DOM::PointerEvent& e)
{
	if (index >= 5) return;

	if (e.type() == PointerEventArgs::POINTER_DOWN)
	{
		DOM::Position localPosition = e.localPosition() - DOM::Size(SlitNode::DEFAULT_WIDTH,
																	SlitNode::DEFAULT_HEIGHT) / 2;

		slit.addNode(mui.addChild<SlitNode>(ofToString(index++),
											localPosition.x,
											localPosition.y));

		// release any pointer capture that was initiated on the mui.

		mui.releasePointerCapture(e.pointer().id());
	}
}
