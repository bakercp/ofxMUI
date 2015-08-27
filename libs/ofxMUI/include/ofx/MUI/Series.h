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
	

#include "ofParameter.h"


namespace ofx {
namespace MUI {

//
//template<typename DataType>
//class SeriesBuffer_: public Series_<DataType>
//{
//public:
//	SeriesBuffer_(std::size_t maxSize = 1024): _maxSize(maxSize)
//	{
//	}
//
//	virtual ~SeriesBuffer_()
//	{
//	}
//
//
//	void clear()
//	{
//		_buffer.clear();
//	}
//
//
//	void setMaxSize(std::size_t maxSize)
//	{
//		_maxSize = maxSize;
//	}
//
//
//	void getMaxSize() const
//	{
//		return _maxSize;
//	}
//
//	void attach(ofParameter<DataType>& parameter)
//	{
//		parameter.addListener(this, &nData);
//	}
//
//	void detatch(ofParameter<DataType>& parameter)
//	{
//		parameter.addListener(this, &onData);
//	}
//
//	void buffer(const DataType& data)
//	{
//		_buffer.push(data);
//
//		if (_buffer.size() > _maxSize)
//		{
//			_buffer.pop();
//		}
//	}
//
//
//	void onData(DataType& data)
//	{
//		buffer(data);
//	}
//
//
//	DataType get(std::size_t index, std::size_t dimension) const
//	{
//		if (index >= size())
//		{
//			throw std::out_of_range("Index is out of range.");
//		}
//		else if (dimension >= dimensions())
//		{
//			throw std::out_of_range("Dimension is out of range.");
//		}
//		else
//		{
//			return _buffer->at(index);
//		}
//	}
//
//	std::size_t dimensions() const
//	{
//		return 1;
//	}
//
//	std::size_t size() const
//	{
//		return _buffer.size();
//	}
//
//
//protected:
//	std::size_t _maxSize;
//	std::deque<DataType> _buffer;
//
//};
//


} } // ofx::MUI
