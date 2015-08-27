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


namespace ofx {
namespace MUI {


/// \brief The drag mode of the Widget.
///
/// The drag mode determines how the Pointer interacts with the Widget.
/// When in Mode::ABSOLUTE, the Widget will immediately jump to the location
/// of the pointer down.  In Mode::RELATIVE, the pointer will be offset
/// relative to the movemovement of the pointer's original pointer down
/// location.
enum class DragMode
{
	/// \brief Sets the position by the absolute position of the dragged pointer.
	ABSOLUTE,
	/// \brief Sets the position by the relative offset of the dragged pointer.
	RELATIVE
};


/// \brief The orientation of an Element.
enum class Orientation
{
	/// \brief Sets the Orientation based on the aspect ratio.
	AUTO,
	/// \brief Locks the Orientation to landscape.
	LANDSCAPE,
	/// \brief Locks the Orientation to portrait.
	PORTRAIT
};


} } // ofx::MUI
