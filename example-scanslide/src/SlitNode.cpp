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


#include "SlitNode.h"
#include "ofx/MUI/Styles.h"


SlitNode::SlitNode(const std::string& id, float x, float y):
	ofx::MUI::Widget(id, x, y, DEFAULT_WIDTH, DEFAULT_HEIGHT),
	_angle(0),
	_drag(0.95),
	_velocity(ofVec2f::zero())
{
	addEventListener(pointerDown, &SlitNode::onPointerEvent);
	addEventListener(pointerUp, &SlitNode::onPointerEvent);
	ofAddListener(move, this, &SlitNode::onMove);

	setDraggable(true);
}


SlitNode::~SlitNode()
{
	removeEventListener(pointerDown, &SlitNode::onPointerEvent);
	removeEventListener(pointerUp, &SlitNode::onPointerEvent);
	ofRemoveListener(move, this, &SlitNode::onMove);
}


void SlitNode::onUpdate()
{
	_velocity *= _drag;
	ofVec2f position = getPosition();
	position += _velocity;
	setPosition(position);
}


void SlitNode::onDraw() const
{
	ofx::MUI::Styles::State state = ofx::MUI::Styles::STATE_NORMAL;

	if (isDragging() || isPointerDown())
	{
		state = ofx::MUI::Styles::STATE_DOWN;
	}
	else if (isPointerOver())
	{
		state = ofx::MUI::Styles::STATE_OVER;
	}

	float halfWidth = getWidth() / 2;
	float halfHeight = getHeight() / 2;

	ofPushMatrix();
	ofTranslate(halfWidth, halfHeight);

	ofFill();
	ofSetColor(getStyles()->getColor(ofx::MUI::Styles::ROLE_BACKGROUND, state));
	ofDrawCircle(0, 0, halfWidth);

	ofNoFill();
	ofSetColor(getStyles()->getColor(ofx::MUI::Styles::ROLE_BORDER, state));
	ofDrawCircle(0, 0, halfWidth);

	ofFill();
	ofSetColor(getStyles()->getColor(ofx::MUI::Styles::ROLE_FOREGROUND, state));

	ofDrawCircle(0, 0, halfWidth - 2);

	ofPopMatrix();

	std::stringstream ss;

	ss << getId() << std::endl;

//	ss << "P: " << getPosition() << endl;
//	ss << "S: " << getScreenPosition() << endl;

	if (!capturedPointers().empty())
	{
		ss << "CP: " << ofToString(capturedPointers()) << std::endl;
	}

	ofSetColor(getStyles()->getColor(ofx::MUI::Styles::ROLE_TEXT, state));
	ofDrawBitmapString(ss.str(), 2, 12);


}


void SlitNode::onMove(ofx::DOM::MoveEvent& e)
{
//	cout
//	cout << "moved!" << e.position() << endl;

//	if (getGeometry().inside(e.position()))
//		{
//			_velocity *= -1;
//		}

}


bool SlitNode::hitTest(const ofx::DOM::Position& localPosition) const
{
	ofx::DOM::Position middle = (getPosition() + ofx::DOM::Position(getWidth(), getHeight()) / 2.0f);

	return localPosition.distance(middle) < getWidth() / 2;
}


void SlitNode::onPointerEvent(ofx::DOM::PointerEvent& e)
{
	if (e.type() == ofx::PointerEventArgs::POINTER_DOWN)
	{
//		_velocity = ofVec2f::zero();
	}
	else if (e.type() == ofx::PointerEventArgs::POINTER_UP)
	{
		if (!capturedPointers().empty())
		{
			_velocity = capturedPointers().begin()->velocity();
//			cout << "v=" << _velocity << endl;
		}
	}
}
