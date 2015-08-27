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


#include "ofColor.h"
#include "ofTrueTypeFont.h"


namespace ofx {
namespace MUI {


enum FontSize
{
	EXTRA_SMALL = 0,
	SMALL = 1,
	MEDIUM = 2,
	LARGE = 3,
	EXTRA_LARGE = 4
};


class TrueTypeFontSettings
{
public:
	TrueTypeFontSettings(const std::string& filename = DEFAULT_FONT,
						 int fontsize = defaultFontSize(FontSize::MEDIUM),
						 bool antiAliased = true,
						 bool fullCharacterSet = true,
						 bool makeContourss = false,
						 float simplifyAmt = 0.3f,
						 int dpi = 0);

	const std::string& filename() const;
	int fontSize() const;
	bool antiAliased() const;
	bool fullCharacterSet() const;
	bool makeContours() const;
	float simplifyAmount() const;
	int dpi() const;

	const static std::string DEFAULT_FONT;

	static int defaultFontSize(FontSize size = FontSize::MEDIUM);

	static TrueTypeFontSettings defaultFontSettings(FontSize size = FontSize::MEDIUM);

private:
	std::string _filename;
	int _fontsize;
	bool _antiAliased;
	bool _fullCharacterSet;
	bool _makeContours;
	float _simplifyAmt;
	int _dpi;

};


class Styles
{
public:
	enum Role
	{
		ROLE_FOREGROUND = 0,
		ROLE_BACKGROUND,
		ROLE_ACCENT,
		ROLE_BORDER,
		ROLE_TEXT
	};

	enum State
	{
		STATE_NORMAL = 0,
		STATE_OVER,
		STATE_DOWN,
		STATE_DISABLED
	};

	Styles();

    /// \brief Destroy this Widget.
    virtual ~Styles();

	void setColors(const ofColor& foreground,
				   const ofColor& background,
				   const ofColor& accent,
				   const ofColor& border,
				   const ofColor& text);

	const ofColor& getColor(Role role, State state) const;
	void setColor(const ofColor& color, Role role, State state);

	const ofTrueTypeFont& getFont(FontSize size = FontSize::MEDIUM) const;

	void setFont(FontSize size, std::shared_ptr<ofTrueTypeFont> font);

protected:
	std::vector<std::vector<ofColor>> _colors;

	mutable std::vector<std::shared_ptr<ofTrueTypeFont>> _fonts;

};


} } // ofx::MUI
