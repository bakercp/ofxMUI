//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


namespace ofx {
namespace MUI {


enum class Density
{
    LOW,
    MEDIUM,
    HIGH,
    EXTRA_HIGH,
    EXTRA_EXTRA_HIGH,
    EXTRA_EXTRA_EXTRA_HIGH
};


enum class Scale
{
    EXTRA_EXTRA_EXTRA_SMALL,
    EXTRA_EXTRA_SMALL,
    EXTRA_SMALL,
    SMALL,
    MEDIUM,
    LARGE,
    EXTRA_LARGE,
    EXTRA_EXTRA_LARGE,
    EXTRA_EXTRA_EXTRA_LARGE
};


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



//public class AbstractMap





} } // ofx::MUI
