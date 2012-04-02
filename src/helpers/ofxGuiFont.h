#pragma once


#include <vector>
#include "ofPoint.h"
#include "ofRectangle.h"
#include "ofConstants.h"
#include "ofPath.h"
#include "ofTexture.h"
#include "ofMesh.h"

#include "ofxGuiConstants.h"

#include <Poco/String.h>
#include <Poco/Ascii.h>
#include <Poco/TextIterator.h>
#include <Poco/UTF8Encoding.h>

// from processing
static int EXTRA_CHARS[] = {
    0x0080, 0x0081, 0x0082, 0x0083, 0x0084, 0x0085, 0x0086, 0x0087,
    0x0088, 0x0089, 0x008A, 0x008B, 0x008C, 0x008D, 0x008E, 0x008F,
    0x0090, 0x0091, 0x0092, 0x0093, 0x0094, 0x0095, 0x0096, 0x0097,
    0x0098, 0x0099, 0x009A, 0x009B, 0x009C, 0x009D, 0x009E, 0x009F,
    0x00A0, 0x00A1, 0x00A2, 0x00A3, 0x00A4, 0x00A5, 0x00A6, 0x00A7,
    0x00A8, 0x00A9, 0x00AA, 0x00AB, 0x00AC, 0x00AD, 0x00AE, 0x00AF,
    0x00B0, 0x00B1, 0x00B4, 0x00B5, 0x00B6, 0x00B7, 0x00B8, 0x00BA,
    0x00BB, 0x00BF, 0x00C0, 0x00C1, 0x00C2, 0x00C3, 0x00C4, 0x00C5,
    0x00C6, 0x00C7, 0x00C8, 0x00C9, 0x00CA, 0x00CB, 0x00CC, 0x00CD,
    0x00CE, 0x00CF, 0x00D1, 0x00D2, 0x00D3, 0x00D4, 0x00D5, 0x00D6,
    0x00D7, 0x00D8, 0x00D9, 0x00DA, 0x00DB, 0x00DC, 0x00DD, 0x00DF,
    0x00E0, 0x00E1, 0x00E2, 0x00E3, 0x00E4, 0x00E5, 0x00E6, 0x00E7,
    0x00E8, 0x00E9, 0x00EA, 0x00EB, 0x00EC, 0x00ED, 0x00EE, 0x00EF,
    0x00F1, 0x00F2, 0x00F3, 0x00F4, 0x00F5, 0x00F6, 0x00F7, 0x00F8,
    0x00F9, 0x00FA, 0x00FB, 0x00FC, 0x00FD, 0x00FF, 0x0102, 0x0103,
    0x0104, 0x0105, 0x0106, 0x0107, 0x010C, 0x010D, 0x010E, 0x010F,
    0x0110, 0x0111, 0x0118, 0x0119, 0x011A, 0x011B, 0x0131, 0x0139,
    0x013A, 0x013D, 0x013E, 0x0141, 0x0142, 0x0143, 0x0144, 0x0147,
    0x0148, 0x0150, 0x0151, 0x0152, 0x0153, 0x0154, 0x0155, 0x0158,
    0x0159, 0x015A, 0x015B, 0x015E, 0x015F, 0x0160, 0x0161, 0x0162,
    0x0163, 0x0164, 0x0165, 0x016E, 0x016F, 0x0170, 0x0171, 0x0178,
    0x0179, 0x017A, 0x017B, 0x017C, 0x017D, 0x017E, 0x0192, 0x02C6,
    0x02C7, 0x02D8, 0x02D9, 0x02DA, 0x02DB, 0x02DC, 0x02DD, 0x03A9,
    0x03C0, 0x2013, 0x2014, 0x2018, 0x2019, 0x201A, 0x201C, 0x201D,
    0x201E, 0x2020, 0x2021, 0x2022, 0x2026, 0x2030, 0x2039, 0x203A,
    0x2044, 0x20AC, 0x2122, 0x2202, 0x2206, 0x220F, 0x2211, 0x221A,
    0x221E, 0x222B, 0x2248, 0x2260, 0x2264, 0x2265, 0x25CA, 0xF8FF,
    0xFB01, 0xFB02
};

/*static public char[] CHARSET;
static {
    CHARSET = new char[126-33+1 + EXTRA_CHARS.length];
    int index = 0;
    for (int i = 33; i <= 126; i++) {
        CHARSET[index++] = (char)i;
    }
    for (int i = 0; i < EXTRA_CHARS.length; i++) {
        CHARSET[index++] = EXTRA_CHARS[i];
    }
};
 */

//--------------------------------------------------
typedef struct {
    int characterIndex;
	int character;
	int height;
	int width;
	int setWidth;
	int topExtent;
	int leftExtent;
	float tW,tH;
	float x1,x2,y1,y2;
	float t1,t2,v1,v2;
    
    vector<ofVec2f> kern;
    
} ofCharacterProperty;

//typedef ofPath ofCharacter;

class ofCharacter : public ofPath {

public:
    int c;
    ofVec2f offset;
    bool isShape;
};

typedef vector<ofCharacter> ofTextLine;

class ofTextBlock {
public:
    ofTextBlock(string _text);
    ofTextBlock(string _text, float _x, float _y);
    ofTextBlock(string _text, float _x, float _y, float _w, float _h);
    ofTextBlock(string _text, ofRectangle const & _rect);
    virtual ~ofTextBlock();

    void draw();
    
    
    
private:
    ofRectangle rect;
    string text;
    

};


//--------------------------------------------------
#define NUM_CHARACTER_TO_START_		32		// 0 - 31 are control characters, no graphics needed.
                                            // include space to get the font's setWidth
class ofxGuiFont{

public:
	struct Settings;

	ofxGuiFont();
	virtual ~ofxGuiFont();
	
	//set the default dpi for all typefaces.
	static void setGlobalDpi(int newDpi);
			
    bool 		loadFont(Settings _settings); // no default b/c filename must be specified
    // 			-- default (without dpi), non-full char set, anti aliased, 96 dpi:
	bool 		loadFont(string filename, 
                         int fontsize, 
                         bool _bAntiAliased=true, 
                         bool _bFullCharacterSet=false, 
                         bool makeContours=false, 
                         float simplifyAmt=0.3, 
                         int dpi=0);
    
	bool		isLoaded();
	bool		isAntiAliased();
    bool        hasKerning();
    bool        hasContours();
	bool		hasFullCharacterSet();

    int         getSize();
    float       getLineHeight();
  	void 		setLineHeight(float height);
	float 		getLetterSpacing();
	void 		setLetterSpacing(float spacing);
	float 		getSpaceSize();
	void 		setSpaceSize(float size);
    
    // font properties
    // read only variables set by the font.  see below for details
    string      getFamilyName();
    string      getStyleName();
    int         getNumFacesInFont();
    int         getCurrentFaceIndex();
    int         getMaxAdvanceWidth();
    int         getMaxAdvanceHeight();
    int         getUnderlinePosition();
    int         getUnderlineThickness();
    int         getAscender();
    int         getDescender();
    int         getHeight();
    
    ofVec2f     getKerning(int leftChar, int rightChar);
    float       getHorizontalKerning(int leftChar, int rightChar);
    float       getVerticalKerning(int leftChar, int rightChar);

    //			get the num chars in the loaded char set
	int			getNumCharacters();	

    // measurements
	float 		stringWidth(string s);
	float 		stringHeight(string s);
	float       charWidth(int character);
    
    // bounding boxes
    ofRectangle     getStringBoundingBox(string s, float x = 0.0f, float y = 0.0f, bool shrinkToContours = true);
	ofRectangle     getStringBoundingBox(string s, ofPoint p, bool shrinkToContours = true);
    ofRectangle     getStringBoundingBox(vector<ofCharacter> offsets, bool shrinkToContours = true);
    
    // drawing!
    // characters
    ofCharacter drawChar(int character, float x, float y, bool asShapes = false);
    ofCharacter drawChar(int character, ofPoint p, bool asShapes = false);
    ofCharacter drawCharAsShapes(int character, float x, float y);
    ofCharacter drawCharAsShapes(int character, ofPoint p);
    
    
    // strings
    vector<ofCharacter> drawString(string s, float x = 0.0f, float y = 0.0f, float w = FLT_MAX, float h = FLT_MAX, bool asShapes = false);
    vector<ofCharacter> drawString(string s, ofRectangle boundingBox, bool asShapes = false);
    void                drawString(vector<ofCharacter> offsets, ofVec2f offset = ofVec2f(0,0), bool asShapes = false);
    vector<ofCharacter> drawStringAsShapes(string s, float x = 0.0f, float y = 0.0f, float w = FLT_MAX, float h = FLT_MAX);	
    vector<ofCharacter> drawStringAsShapes(string s, ofRectangle boundingBox);
    void                drawStringAsShapes(vector<ofCharacter> offsets, ofVec2f offset = ofVec2f(0,0));

    
    ofCharacter getCharacterAsPoints(int character, float x = 0.0f, float y = 0.0f);
    ofCharacter getCharacterAsPoints(int character, ofPoint p);

    vector<ofCharacter> getStringAsPoints(string s, float x = 0.0f, float y = 0.0f, float w = FLT_MAX, float h = FLT_MAX);
    vector<ofCharacter> getStringAsPoints(string s, ofRectangle boundingBox);
   
    vector<ofCharacter>  getCharacterOffsets(string s, float x = 0.0f, float y = 0.0f, float w = FLT_MAX, float h = FLT_MAX);
    vector<ofCharacter>  getCharacterOffsets(string s, ofRectangle boundingBox);
	
    // texture
	void bind();
	void unbind();
    
    struct Settings { // the settings critical for font allocation

        string  fontFilename;           // the font filename
        int     fontSize;               // the font file size
        int     fontDpi;                // the font dpi
        bool    bAntiAliased;           // should the font be created w/ antialiasing
        bool    bForceAutoHinting;      // should auto hinting be forced
        bool    bUseKerning;            // should a kerning table be generated
        bool    bFullCharacterSet;      // should the font be created w/ a full character set
        bool    bMakeContours;          // should the font be created with contourse
        float   contourSimplifyAmt;     // contour simplification factor
        int     fallbackSpaceChar;      // in the event that a font does not contain a setWidth 
                                        // for the space ' ' character, the width of this char
                                        // will be used.  Defaults to 'p';
		int     faceNum;                // for fonts that contain multiple faces
        Settings();
	};
    


protected:
    
    Settings        settings;    // all settings required for font allocation
    
	bool			bLoadedOk; // is the font ready to use
	bool            bHasKerning;
    bool            bHasContours;
    
    // read only variables, set by the font
    string          fontFamilyName;
    string          fontStyleName;
    
    int             numFacesInFont; // The number of faces in the font file.
    int             currentFaceIndex; // The currently loaded face index.  Usually 0
    
    int             maxAdvanceWidth; // The maximal advance width, in pixels, for all glyphs in this face. 
                                     // This can be used to make word wrapping computations faster.
    int             maxAdvanceHeight;   // The maximal advance height, in pixels, for all glyphs in this face. 
                                        // This is only relevant for vertical layouts, and is set to ‘height’ 
                                        // for fonts that do not provide vertical metrics.
    int             underlinePosition;  // The position, in pixels, of the underline line for this face. 
                                        // It's the center of the underlining stem.
    int             underlineThickness; // The thickness, in pixels, of the underline for this face.
    int             ascender;       // The typographic ascender of the face, expressed in pixels
    int             descender;      // The typographic descender of the face, expressed in pixels
    int             height;         // The height is the vertical distance between two consecutive baselines, 
                                    // expressed in pixels. It is always positive.

    
    // scaling parameters that do not affect font allocation
    float 			lineHeight;
	float			letterSpacing;
	float			spaceSize;

    void resetMetrics(); // will reset metrics
    
    // layout
    vector<ofCharacter>  textLayout(string s, ofRectangle bb, bool draw, bool drawShapes);
    
    // character properties
    int                 nCharacters;  // the size of the cps vector
    vector <ofCharacterProperty> cps;          // the character properties
    vector <ofCharacter> charOutlines; // character outlines

    // helper functions
    bool            isInShapeCharacterSet(int character);
    bool            isInCharacterSet(int character);
    
    int             indexToChar(int index);
    int             charToIndex(int character);

    // drawing helper functions
//	void 			drawChar(int c, ofPoint p, bool asShapes = false);
//	void			drawCharAsShape(int c, ofPoint p);
    
    // internal measurement functions
    float           _widthChar(int character);
    float           _widthString(string s, int start, int stop);

    // internal draw functions
    void            _drawChar(int character, ofPoint p, bool asShapes = false);        
    
	// texture related variables
	int         border;//, visibleBorder;
	bool        binded;
	ofTexture   texAtlas;
	ofMesh      stringQuads;

private:
#ifdef TARGET_ANDROID
	friend void ofUnloadAllFontTextures();
	friend void ofReloadAllFontTextures();
#endif
#ifdef TARGET_OPENGLES
	GLint blend_src, blend_dst;
	GLboolean blend_enabled;
	GLboolean texture_2d_enabled;
#endif
	void		unloadTextures();
	void		reloadTextures();
};


