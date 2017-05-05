//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofx/MUI/Styles.h"


namespace ofx {
namespace MUI {


const std::string TrueTypeFontSettings::DEFAULT_FONT = OF_TTF_SANS;


TrueTypeFontSettings::TrueTypeFontSettings(const std::string& filename,
										   int fontsize,
										   bool antiAliased,
										   bool fullCharacterSet,
										   bool makeContours,
										   float simplifyAmt,
										   int dpi):
	_filename(filename),
	_fontsize(fontsize),
	_antiAliased(antiAliased),
	_fullCharacterSet(fullCharacterSet),
	_makeContours(makeContours),
	_simplifyAmt(simplifyAmt),
	_dpi(dpi)
{
}


const std::string& TrueTypeFontSettings::filename() const
{
	return _filename;
}


int TrueTypeFontSettings::fontSize() const
{
	return _fontsize;
}


bool TrueTypeFontSettings::antiAliased() const
{
	return _antiAliased;
}


bool TrueTypeFontSettings::fullCharacterSet() const
{
	return _fullCharacterSet;
}


bool TrueTypeFontSettings::makeContours() const
{
	return _makeContours;
}


float TrueTypeFontSettings::simplifyAmount() const
{
	return _simplifyAmt;
}


int TrueTypeFontSettings::dpi() const
{
	return _dpi;
}


int TrueTypeFontSettings::defaultFontSize(FontSize size)
{
	switch (size)
	{
		case FontSize::EXTRA_SMALL:
			return 8;
		case FontSize::SMALL:
			return 10;
		case FontSize::MEDIUM:
			return 12;
		case FontSize::LARGE:
			return 20;
		case FontSize::EXTRA_LARGE:
			return 32;
		default:
			return 12;
	}
}


TrueTypeFontSettings TrueTypeFontSettings::defaultFontSettings(FontSize size)
{
	return TrueTypeFontSettings(DEFAULT_FONT, defaultFontSize(size));
}


Styles::Styles()
{
	_fonts.assign(EXTRA_LARGE + 1, nullptr);

	// https://color.adobe.com/Neutral-Blue-color-theme-22361/
	ofColor text = ofColor::fromHex(0xFCFFF5, 200); // text
	ofColor accent = ofColor::fromHex(0xD1DBBD, 200); // accent
	ofColor border = ofColor::fromHex(0x91AA9D, 200); // border
	ofColor foreground = ofColor::fromHex(0x3E606F, 200); // foreground
	ofColor background = ofColor::fromHex(0x193441, 200); // background

	setColors(foreground, background, accent, border, text);
}


Styles::~Styles()
{
}


const ofColor& Styles::getColor(Role role, State state) const
{
	return _colors[role][state];
}


void Styles::setColors(const ofColor& foreground,
					   const ofColor& background,
					   const ofColor& accent,
					   const ofColor& border,
					   const ofColor& text)
{
	std::vector<ofColor> _foreground(STATE_DISABLED + 1, ofColor());

	_foreground[STATE_NORMAL] = foreground;
	_foreground[STATE_OVER] = ofColor(foreground, 255);
	_foreground[STATE_DOWN] = ofColor(accent, 255);
	_foreground[STATE_DISABLED] = ofColor(foreground, 20);

	std::vector<ofColor> _background(STATE_DISABLED + 1, ofColor());

	_background[STATE_NORMAL] = background;
	_background[STATE_OVER] = background;
	_background[STATE_DOWN] = ofColor(background, 200);
	_background[STATE_DISABLED] = ofColor(background, 20);

	std::vector<ofColor> _accent(STATE_DISABLED + 1, ofColor());

	_accent[STATE_NORMAL] = accent;
	_accent[STATE_OVER] = ofColor(accent, 180);
	_accent[STATE_DOWN] = ofColor(accent, 255);
	_accent[STATE_DISABLED] = ofColor(accent, 20);

	std::vector<ofColor> _border(STATE_DISABLED + 1, ofColor());

	_border[STATE_NORMAL] = border;
	_border[STATE_OVER] = border;
	_border[STATE_DOWN] = border;
	_border[STATE_DISABLED] = ofColor(border, 20);

	std::vector<ofColor> _text(STATE_DISABLED + 1, ofColor());

	_text[STATE_NORMAL] = text;
	_text[STATE_OVER] = foreground[STATE_OVER];
	_text[STATE_DOWN] = foreground[STATE_DOWN];
	_text[STATE_DISABLED] = ofColor(text, 20);

	_colors.assign(ROLE_TEXT + 1, std::vector<ofColor>());

	_colors[ROLE_FOREGROUND] = _foreground;
	_colors[ROLE_BACKGROUND] = _background;
	_colors[ROLE_ACCENT] = _accent;
	_colors[ROLE_BORDER] = _border;
	_colors[ROLE_TEXT] = _text;
}

const ofTrueTypeFont& Styles::getFont(FontSize size) const
{
	std::shared_ptr<ofTrueTypeFont> font = _fonts[size];

	if (font == nullptr)
	{
		TrueTypeFontSettings settings = TrueTypeFontSettings::defaultFontSettings(size);

		font = std::make_shared<ofTrueTypeFont>();

		if (!font->load(settings.filename(),
						settings.fontSize(),
						settings.antiAliased(),
						settings.fullCharacterSet(),
						settings.makeContours(),
						settings.simplifyAmount(),
						settings.dpi()))
		{
			ofLogError("Styles::getFont") << "Unable to load font: " << settings.filename();
		}

		_fonts[size] = font;
	}

	return *font;
}


void Styles::setFont(FontSize size, std::shared_ptr<ofTrueTypeFont> font)
{
	_fonts[size] = font;
}


} } // namespace ofx::MUI
