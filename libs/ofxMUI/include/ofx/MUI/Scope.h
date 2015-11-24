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


#pragma once
	

#include "ofx/MUI/Axis.h"
#include "ofx/MUI/Widget.h"
#include "ofx/MUI/Styles.h"


namespace ofx {
namespace MUI {


template<typename DataType>
class Scope: public Widget
{
public:
	Scope(float x,
		  float y,
		  float width,
		  float height);

	Scope(const std::string& id,
		  float x,
		  float y,
		  float width,
		  float height,
		  std::size_t maxSize);

	virtual ~Scope();

	void onDraw() const override;

	void setMaxSize(std::size_t maxSize);

	std::size_t getMaxSize() const;

	void setColor(const std::string& series, const ofColor& color);

	void add(const std::string& series, const DataType& value);

	void removeSeries(const std::string& series);

	void clear();

	Axis_<DataType> axes[2];

protected:
	typedef std::deque<DataType> Buffer;

	/// \brief The maximum number of data points to buffer.
	std::size_t _maxSize;

	std::unordered_map<std::string, std::pair<Buffer, ofColor>> _data;

};



template<typename DataType>
Scope<DataType>::Scope(float x,
					   float y,
					   float width,
					   float height):
	Scope<DataType>::Scope("", x, y, width, height, 128)
{
}
	

template<typename DataType>
Scope<DataType>::Scope(const std::string& id,
					   float x,
					   float y,
					   float width,
					   float height,
					   std::size_t maxSize):
	Widget(id, x, y, width, height),
	_maxSize(maxSize)
{
}


template<typename DataType>
Scope<DataType>::~Scope()
{
}



template<typename DataType>
void Scope<DataType>::onDraw() const
{
	ofSetColor(getStyles()->getColor(Styles::ROLE_TEXT, Styles::STATE_NORMAL));
	ofDrawBitmapString(getId(), 2, 12);

	ofFill();
	ofSetColor(getStyles()->getColor(Styles::ROLE_BACKGROUND, Styles::STATE_NORMAL));
	ofDrawRectangle(0, 0, getWidth(), getHeight());

	ofNoFill();
	ofSetColor(getStyles()->getColor(Styles::ROLE_BORDER, Styles::STATE_NORMAL));
	ofDrawRectangle(0, 0, getWidth(), getHeight());


	for (auto& i : _data)
	{
		const ofColor& color = i.second.second;
		const Buffer& buffer = i.second.first;

		ofMesh mesh;

		for (std::size_t j = 0; j < buffer.size(); ++j)
		{
			float x = 0;
			float y = 0;

			x = axes[0].map(j, 0, getWidth());
			y = axes[1].map(buffer[j], 0, getHeight());

			mesh.addVertex(ofVec2f(x, y));
		}

		mesh.setMode(OF_PRIMITIVE_LINE_STRIP);

		ofSetColor(color);
		mesh.draw();

	}
}


template<typename DataType>
void Scope<DataType>::setMaxSize(std::size_t maxSize)
{
	_maxSize = maxSize;
}


template<typename DataType>
std::size_t Scope<DataType>::getMaxSize() const
{
	return _maxSize;
}


template<typename DataType>
void Scope<DataType>::setColor(const std::string& series, const ofColor& value)
{
	auto a = _data.find(series);

	if (a != _data.end())
	{
		a->second.second = value;
	}
	else
	{
		_data[series] = std::pair<Buffer, ofColor>(Buffer(), value);
	}
}
	



template<typename DataType>
void Scope<DataType>::add(const std::string& series, const DataType& value)
{
	auto a = _data.find(series);

	if (a == _data.end())
	{
		_data[series] = std::make_pair<Buffer, ofColor>(Buffer(), ofColor(ofRandom(255),
																		  ofRandom(255),
																		  ofRandom(255)));
	}

	a->second.first.push_back(value);

	while (a->second.first.size() > _maxSize)
	{
		a->second.first.pop_front();
	}

}


template<typename DataType>
void Scope<DataType>::removeSeries(const std::string& series)
{
	_data.erase(_data.find(series));
}


template<typename DataType>
void Scope<DataType>::clear()
{
	_data.clear();
}



} } // ofx::MUI
