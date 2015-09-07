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


#include <algorithm>


namespace ofx {
namespace MUI {


template<typename DataType>
class Axis_
{
public:
	enum Scale
	{
		LINEAR,
		SEMILOG
	};

	Axis_();

	Axis_(const DataType& minimum,
		  const DataType& maximum,
		  Scale scale,
		  bool inverted,
		  bool autoRange,
		  bool clipped);

	virtual ~Axis_();

	DataType map(const DataType& value,
				 const DataType& outputMin,
				 const DataType& outputMax) const;

	void setRange(const DataType& minimum, const DataType& maximum);

	void setMinimum(const DataType& minimum);
	const DataType& getMinimum() const;

	void setMaximum(const DataType& maximum);
	const DataType& getMaximum() const;

	void setAutoRange(bool autoRange);
	bool isAutoRange() const;

	void setScale(Scale scale);
	Scale getScale() const;

	void setInverted(bool inverted);
	bool isInverted() const;

	void setClipped(bool clipped);
	bool isClipped() const;

private:
	DataType _minimum;
	DataType _maximum;

	Scale _scale;

	bool _autoRange;
	bool _inverted;
	bool _clipped;

};


template<typename DataType>
Axis_<DataType>::Axis_(): Axis_(0, 1, LINEAR, false, false, false)
{
}


template<typename DataType>
Axis_<DataType>::Axis_(const DataType& minimum,
					   const DataType& maximum,
					   Scale scale,
					   bool autoRange,
					   bool inverted,
					   bool clipped):
	_minimum(std::min(minimum, maximum)),
	_maximum(std::max(minimum, maximum)),
	_autoRange(autoRange),
	_scale(scale),
	_inverted(inverted),
	_clipped(clipped)
{
}


template<typename DataType>
Axis_<DataType>::~Axis_()
{
}


template<typename DataType>
DataType Axis_<DataType>::map(const DataType& value,
							  const DataType& outputMin,
							  const DataType& outputMax) const
{
	if (_inverted)
	{
		return ofMap(value, _minimum, _maximum, outputMax, outputMin, _clipped);
	}
	else
	{
		return ofMap(value, _minimum, _maximum, outputMin, outputMax, _clipped);
	}
}


template<typename DataType>
void Axis_<DataType>::setRange(const DataType& minimum, const DataType& maximum)
{
	setMinimum(minimum);
	setMaximum(maximum);
}


template<typename DataType>
void Axis_<DataType>::setMinimum(const DataType& minimum)
{
	_minimum = minimum;

	if (_minimum > _maximum)
	{
		std::swap(_minimum, _maximum);
	}
}

template<typename DataType>
const DataType& Axis_<DataType>::getMinimum() const
{
	return _minimum;
}


template<typename DataType>
void Axis_<DataType>::setMaximum(const DataType& maximum)
{
	_maximum = maximum;

	if (_minimum > _maximum)
	{
		std::swap(_minimum, _maximum);
	}
}


template<typename DataType>
const DataType& Axis_<DataType>::getMaximum() const
{
	return _maximum;
}


template<typename DataType>
void Axis_<DataType>::setScale(Scale scale)
{
	_scale = scale;
}


template<typename DataType>
typename Axis_<DataType>::Scale Axis_<DataType>::getScale() const
{
	return _scale;
}


template<typename DataType>
void Axis_<DataType>::setInverted(bool inverted)
{
	_inverted = inverted;
}


template<typename DataType>
bool Axis_<DataType>::isInverted() const
{
	return _inverted;
}


template<typename DataType>
void Axis_<DataType>::setClipped(bool clipped)
{
	_clipped = clipped;
}


template<typename DataType>
bool Axis_<DataType>::isClipped() const
{
	return _clipped;
}


} } // ofx::MUI
