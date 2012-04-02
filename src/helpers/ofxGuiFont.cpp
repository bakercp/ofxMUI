#include "ofxGuiFont.h"
//--------------------------

#include "ft2build.h"
#include "freetype2/freetype/freetype.h"
#include "freetype2/freetype/ftglyph.h"
#include "freetype2/freetype/ftoutln.h"
#include "freetype2/freetype/fttrigon.h"

#include <algorithm>

#include "ofUtils.h"
#include "ofGraphics.h"

static bool printVectorInfo = false;
static int fontGlobalDpi = 96;

ofxGuiFont::Settings::Settings() {
    fontFilename        = ""; // must set on load
    fontSize            = 12;
    fontDpi             = 0;  // if <= 0 will default to fontGlobalDpi
    bAntiAliased        = true;
    bForceAutoHinting   = false;
    bUseKerning         = false;
    bFullCharacterSet   = false;
    bMakeContours       = false;
    contourSimplifyAmt  = 0.3;
    fallbackSpaceChar   = 'p';
    faceNum             = 0;
}

//--------------------------------------------------------
void ofxGuiFont::setGlobalDpi(int newDpi){
	fontGlobalDpi = newDpi;
}

//--------------------------------------------------------
static ofCharacter makeContoursForCharacter(FT_Face &face);
static ofCharacter makeContoursForCharacter(FT_Face &face){

		//int num			= face->glyph->outline.n_points;
		int nContours	= face->glyph->outline.n_contours;
		int startPos	= 0;

		char * tags		= face->glyph->outline.tags;
		FT_Vector * vec = face->glyph->outline.points;

		ofCharacter charOutlines;
		charOutlines.setUseShapeColor(false);

		for(int k = 0; k < nContours; k++){
			if( k > 0 ){
				startPos = face->glyph->outline.contours[k-1]+1;
			}
			int endPos = face->glyph->outline.contours[k]+1;

			if(printVectorInfo){
				ofLog(OF_LOG_NOTICE, "--NEW CONTOUR\n");
			}

			//vector <ofPoint> testOutline;
			ofPoint lastPoint;

			for(int j = startPos; j < endPos; j++){

				if( FT_CURVE_TAG(tags[j]) == FT_CURVE_TAG_ON ){
					lastPoint.set((float)vec[j].x, (float)-vec[j].y, 0);
					if(printVectorInfo){
						ofLog(OF_LOG_NOTICE, "flag[%i] is set to 1 - regular point - %f %f", j, lastPoint.x, lastPoint.y);
					}
					//testOutline.push_back(lastPoint);
					charOutlines.lineTo(lastPoint/64);

				}else{
					if(printVectorInfo){
						ofLog(OF_LOG_NOTICE, "flag[%i] is set to 0 - control point", j);
					}

					if( FT_CURVE_TAG(tags[j]) == FT_CURVE_TAG_CUBIC ){
						if(printVectorInfo){
							ofLog(OF_LOG_NOTICE, "- bit 2 is set to 2 - CUBIC");
						}

						int prevPoint = j-1;
						if( j == 0){
							prevPoint = endPos-1;
						}

						int nextIndex = j+1;
						if( nextIndex >= endPos){
							nextIndex = startPos;
						}

						ofPoint nextPoint( (float)vec[nextIndex].x,  -(float)vec[nextIndex].y );

						//we need two control points to draw a cubic bezier
						bool lastPointCubic =  ( FT_CURVE_TAG(tags[prevPoint]) != FT_CURVE_TAG_ON ) && ( FT_CURVE_TAG(tags[prevPoint]) == FT_CURVE_TAG_CUBIC);

						if( lastPointCubic ){
							ofPoint controlPoint1((float)vec[prevPoint].x,	(float)-vec[prevPoint].y);
							ofPoint controlPoint2((float)vec[j].x, (float)-vec[j].y);
							ofPoint nextPoint((float) vec[nextIndex].x,	-(float) vec[nextIndex].y);

							//cubic_bezier(testOutline, lastPoint.x, lastPoint.y, controlPoint1.x, controlPoint1.y, controlPoint2.x, controlPoint2.y, nextPoint.x, nextPoint.y, 8);
							charOutlines.bezierTo(controlPoint1.x/64, controlPoint1.y/64, controlPoint2.x/64, controlPoint2.y/64, nextPoint.x/64, nextPoint.y/64);
						}

					}else{

						ofPoint conicPoint( (float)vec[j].x,  -(float)vec[j].y );

						if(printVectorInfo){
							ofLog(OF_LOG_NOTICE, "- bit 2 is set to 0 - conic- ");
							ofLog(OF_LOG_NOTICE, "--- conicPoint point is %f %f", conicPoint.x, conicPoint.y);
						}

						//If the first point is connic and the last point is connic then we need to create a virutal point which acts as a wrap around
						if( j == startPos ){
							bool prevIsConnic = (  FT_CURVE_TAG( tags[endPos-1] ) != FT_CURVE_TAG_ON ) && ( FT_CURVE_TAG( tags[endPos-1]) != FT_CURVE_TAG_CUBIC );

							if( prevIsConnic ){
								ofPoint lastConnic((float)vec[endPos - 1].x, (float)-vec[endPos - 1].y);
								lastPoint = (conicPoint + lastConnic) / 2;

								if(printVectorInfo){
									ofLog(OF_LOG_NOTICE, "NEED TO MIX WITH LAST");
									ofLog(OF_LOG_NOTICE, "last is %f %f", lastPoint.x, lastPoint.y);
								}
							}
						}

						//bool doubleConic = false;

						int nextIndex = j+1;
						if( nextIndex >= endPos){
							nextIndex = startPos;
						}

						ofPoint nextPoint( (float)vec[nextIndex].x,  -(float)vec[nextIndex].y );

						if(printVectorInfo){
							ofLog(OF_LOG_NOTICE, "--- last point is %f %f", lastPoint.x, lastPoint.y);
						}

						bool nextIsConnic = (  FT_CURVE_TAG( tags[nextIndex] ) != FT_CURVE_TAG_ON ) && ( FT_CURVE_TAG( tags[nextIndex]) != FT_CURVE_TAG_CUBIC );

						//create a 'virtual on point' if we have two connic points
						if( nextIsConnic ){
							nextPoint = (conicPoint + nextPoint) / 2;
							if(printVectorInfo){
								ofLog(OF_LOG_NOTICE, "|_______ double connic!");
							}
						}
						if(printVectorInfo){
							ofLog(OF_LOG_NOTICE, "--- next point is %f %f", nextPoint.x, nextPoint.y);
						}

						//quad_bezier(testOutline, lastPoint.x, lastPoint.y, conicPoint.x, conicPoint.y, nextPoint.x, nextPoint.y, 8);
						charOutlines.quadBezierTo(lastPoint.x/64, lastPoint.y/64, conicPoint.x/64, conicPoint.y/64, nextPoint.x/64, nextPoint.y/64);

						if( nextIsConnic ){
							lastPoint = nextPoint;
						}
					}
				}

			//end for
			}
			charOutlines.close();
		}

	return charOutlines;
}

#ifdef TARGET_ANDROID
	#include <set>
	set<ofxGuiFont*> all_fonts;
	void ofUnloadAllFontTextures(){
		set<ofxGuiFont*>::iterator it;
		for(it=all_fonts.begin();it!=all_fonts.end();it++){
			(*it)->unloadTextures();
		}
	}
	void ofReloadAllFontTextures(){
		set<ofxGuiFont*>::iterator it;
		for(it=all_fonts.begin();it!=all_fonts.end();it++){
			(*it)->reloadTextures();
		}
	}

#endif

bool compare_cps(const ofCharacterProperty & c1, const ofCharacterProperty & c2){
	if(c1.tH == c2.tH) return c1.tW > c2.tW;
	else return c1.tH > c2.tH;
}

//------------------------------------------------------------------
ofxGuiFont::ofxGuiFont(){
	bLoadedOk		= false;
	#ifdef TARGET_ANDROID
		all_fonts.insert(this);
	#endif
	
    resetMetrics();

	// 3 pixel border around the glyph
	// We show 2 pixels of this, so that blending looks good.
	// 1 pixels is hidden because we don't want to see the real edge of the texture

	border			= 3;
	//visibleBorder	= 2;
	stringQuads.setMode(OF_PRIMITIVE_TRIANGLES);
	binded = false;
}

//------------------------------------------------------------------
ofxGuiFont::~ofxGuiFont(){

	if (bLoadedOk){
		unloadTextures();
	}

	#ifdef TARGET_ANDROID
		all_fonts.erase(this);
	#endif
}

void ofxGuiFont::unloadTextures(){
	if(!bLoadedOk) return;

	texAtlas.clear();
    resetMetrics();
	bLoadedOk = false;
}

void ofxGuiFont::reloadTextures(){
	loadFont(settings);
}

void ofxGuiFont::resetMetrics() {
    bHasKerning         = false; // even though we request kerning, it may not be supported in the font
    bHasContours        = false;

    fontFamilyName      = "";
    fontStyleName       = "";

    numFacesInFont      = -1;
    currentFaceIndex    = -1;
    maxAdvanceWidth     = -1; 
    maxAdvanceHeight    = -1;
    underlinePosition   = -1;
    underlineThickness  = -1;
    ascender            = -1;
    descender           = -1;
    height              = -1; 

    lineHeight = 1.0f;
    letterSpacing = 1.0f;
    spaceSize = 1.0f;
}


//-----------------------------------------------------------
bool ofxGuiFont::loadFont(string fontFilename, 
                              int fontSize, 
                              bool bAntiAliased, 
                              bool bFullCharacterSet, 
                              bool bMakeContours, 
                              float contourSimplifyAmt, 
                              int fontDpi) {

    settings.fontFilename       = fontFilename;
    settings.fontSize           = fontSize;
    settings.fontDpi            = fontDpi;
    settings.bAntiAliased       = bAntiAliased;
    settings.bFullCharacterSet  = bFullCharacterSet;
    settings.bMakeContours      = bMakeContours;
    settings.contourSimplifyAmt = contourSimplifyAmt;
    // all else is set in the default settings constructor
}
    

//-----------------------------------------------------------
bool ofxGuiFont::loadFont(Settings _settings) { 

    if(_settings.fontFilename.empty()) {
		ofLog(OF_LOG_ERROR,"ofxGuiFont::loadFont - No font name specified.");
		return false;
    }
    
    settings = _settings;

	//------------------------------------------------
	if (bLoadedOk == true){
		// we've already been loaded, try to clean up :
		unloadTextures();
	}
	//------------------------------------------------

    int fontDpi = settings.fontDpi;
    
	if( fontDpi == 0 ){
		settings.fontDpi = fontGlobalDpi;
	}

    string fontFilenameWithPath = ofToDataPath(settings.fontFilename);
    
	bLoadedOk 			= false;

	//--------------- load the library and typeface
	
    FT_Error err;
    
    FT_Library library;
    
    err = FT_Init_FreeType( &library );
    if (err){
		ofLog(OF_LOG_ERROR,"ofxGuiFont::loadFont - Error initializing freetype lib: FT_Error = %d", err);
		return false;
	}

	FT_Face face;
    
    err = FT_New_Face( library, fontFilenameWithPath.c_str(), 0, &face );
	if (err) {
        // simple error table in lieu of full table (see fterrors.h)
        string errorString = "unknown freetype";
        if(err == 1) errorString = "INVALID FILENAME";
        ofLog(OF_LOG_ERROR,"ofxGuiFont::loadFont - %s: %s: FT_Error = %d", errorString.c_str(), fontFilenameWithPath.c_str(), err);
		return false;
	}

    float fontSize = settings.fontSize << 6;
	FT_Set_Char_Size( face, fontSize, fontSize, fontDpi, fontDpi);
	lineHeight = settings.fontSize * 1.43f;
    
    nCharacters = settings.bFullCharacterSet ? 256 : 128 - NUM_CHARACTER_TO_START_;

	//------------------------------------------------------
	//kerning would be great to support:
	//ofLog(OF_LOG_NOTICE,"FT_HAS_KERNING ? %i", FT_HAS_KERNING(face));
	//------------------------------------------------------

    bHasKerning         = FT_HAS_KERNING(face) > 0 && settings.bUseKerning;

    bool isScalable = FT_IS_SCALABLE(face);  // does have scalable outlines?
                                             // true for TrueType, Type 1, Type 42, CID, OpenType/CFF, and PFR font formats.
    // parameters below only valid for scalable fonts;
    fontFamilyName      =      face->family_name;
    fontStyleName       =      face->style_name;
    maxAdvanceWidth     = (int)face->max_advance_width   >> 6;
    maxAdvanceHeight    = (int)face->max_advance_height  >> 6;
    underlinePosition   = (int)face->underline_position  >> 6;
    underlineThickness  = (int)face->underline_thickness >> 6;
    descender           = -1 * ((int)face->descender           >> 6); // free type descenders are negative
    ascender            = (int)face->ascender            >> 6;
    height              = (int)face->height              >> 6;
    
	//--------------- initialize character info and textures
	cps.resize(nCharacters);

    bHasContours = settings.bMakeContours;
	if(bHasContours){
		charOutlines.clear();
		charOutlines.assign(nCharacters, ofCharacter());
	}

	vector<ofPixels> expanded_data(nCharacters);

	long areaSum=0;

    FT_Int32         loadMode = settings.bForceAutoHinting ? FT_LOAD_DEFAULT       : FT_LOAD_TARGET_LIGHT;
    FT_Render_Mode renderMode = settings.bAntiAliased      ? FT_RENDER_MODE_NORMAL : FT_RENDER_MODE_MONO;

	//--------------------- load each char -----------------------
	for (int i = 0 ; i < nCharacters; i++){
        
		//------------------------------------------ anti aliased or not:

        int thisChar = indexToChar(i);

		err = FT_Load_Glyph( face, 
                            FT_Get_Char_Index( face, thisChar ), 
                            loadMode );
        if(err){
			ofLog(OF_LOG_ERROR,"ofxGuiFont::loadFont - Error with FT_Load_Glyph %i: FT_Error = %d", i, err);
		}

		FT_Render_Glyph(face->glyph, renderMode);
		
		//------------------------------------------
		FT_Bitmap& bitmap= face->glyph->bitmap;

		// prepare the texture:
		/*int width  = ofNextPow2( bitmap.width + border*2 );
		int height = ofNextPow2( bitmap.rows  + border*2 );


		// ------------------------- this is fixing a bug with small type
		// ------------------------- appearantly, opengl has trouble with
		// ------------------------- width or height textures of 1, so we
		// ------------------------- we just set it to 2...
		if (width == 1) width = 2;
		if (height == 1) height = 2;*/


		if(bHasContours){
			if( printVectorInfo ) {
                printf("\n\ncharacter %c: \n", char( thisChar ) );
            }
			charOutlines[i] = makeContoursForCharacter( face );
			if(settings.contourSimplifyAmt>0) {
				charOutlines[i].simplify(settings.contourSimplifyAmt);
            }
			charOutlines[i].getTessellation();
		}


		// -------------------------
		// info about the character:
		cps[i].characterIndex	= i;
        cps[i].character        = indexToChar(i);
		cps[i].height 			= face->glyph->bitmap_top;
		cps[i].width 			= face->glyph->bitmap.width;
		cps[i].setWidth 		= face->glyph->advance.x >> 6;
		cps[i].topExtent 		= face->glyph->bitmap.rows;
		cps[i].leftExtent		= face->glyph->bitmap_left;
        
		int width  = cps[i].width;
		int height = bitmap.rows;

		cps[i].tW				= width;
		cps[i].tH				= height;

		int fheight	= cps[i].height;
		int bwidth	= cps[i].width;
		int top		= cps[i].topExtent - cps[i].height;
		int lextent	= cps[i].leftExtent;

		float	corr, stretch;

		//this accounts for the fact that we are showing 2*visibleBorder extra pixels
		//so we make the size of each char that many pixels bigger
		stretch = 0;//(float)(visibleBorder * 2);

		corr	= (float)(( (settings.fontSize - fheight) + top) - settings.fontSize);

		cps[i].x1		= lextent + bwidth + stretch;
		cps[i].y1		= fheight + corr + stretch;
		cps[i].x2		= (float) lextent;
		cps[i].y2		= -top + corr;

        if(bHasKerning) {
            // build kerning table if possible and requested
            cps[i].kern.resize(nCharacters);
            
            FT_Vector  kerning;
            FT_UInt    kerning_mode = FT_KERNING_DEFAULT; // default for now
            FT_Error   kerningError;

            for (int j = 0 ; j < nCharacters; j++){
                kerningError = FT_Get_Kerning( face,          /* handle to face object */
                                               thisChar,      /* left glyph index      */
                                               indexToChar(j),/* right glyph index     */
                                               kerning_mode,  /* kerning mode          */
                                               &kerning );    /* target vector         */  

                if(!kerningError) {
                    ofVec2f k((kerning.x >> 6),(kerning.y >> 6));
                    if(k.x != 0 || k.y != 0) cps[i].kern[j] = k;
                } else {
                    ofLog(OF_LOG_ERROR,"ofxGuiFont::loadFont - Error with FT_Get_Kerning %i/%i: FT_Error = %d", i, j, kerningError);
                }
            }
        }
        
        
		// Allocate Memory For The Texture Data.
		expanded_data[i].allocate(width, height, 2);
		//-------------------------------- clear data:
		expanded_data[i].set(0,255); // every luminance pixel = 255
		expanded_data[i].set(1,0);

		if (settings.bAntiAliased == true){
			ofPixels bitmapPixels;
			bitmapPixels.setFromExternalPixels(bitmap.buffer,bitmap.width,bitmap.rows,1);
			expanded_data[i].setChannel(1,bitmapPixels);
		} else {
			//-----------------------------------
			// true type packs monochrome info in a
			// 1-bit format, hella funky
			// here we unpack it:
			unsigned char *src =  bitmap.buffer;
			for(int j=0; j <bitmap.rows;j++) {
				unsigned char b=0;
				unsigned char *bptr =  src;
				for(int k=0; k < bitmap.width ; k++){
					expanded_data[i][2*(k+j*width)] = 255;

					if (k%8==0){
						b = (*bptr++);
					}

					expanded_data[i][2*(k+j*width) + 1] = b&0x80 ? 255 : 0;
					b <<= 1;
				}
				src += bitmap.pitch;
			}
			//-----------------------------------
		}

		areaSum += (cps[i].width+border*2)*(cps[i].height+border*2);
	}

    // double check that space has a setWidth
    // if none, revert to the _width_ of an 'p'
    if(cps[charToIndex(' ')].setWidth <= 0) {
        cps[charToIndex(' ')].setWidth = cps[charToIndex(settings.fallbackSpaceChar)].width;
    }

	vector<ofCharacterProperty> sortedCopy = cps;
	sort(sortedCopy.begin(),sortedCopy.end(),&compare_cps);

	// pack in a texture, algorithm to calculate min w/h from
	// http://upcommons.upc.edu/pfc/bitstream/2099.1/7720/1/TesiMasterJonas.pdf
	//cout << areaSum << endl;

	bool packed = false;
	float alpha = logf(areaSum)*1.44269;

	int w;
	int h;
	while(!packed){
		w = pow(2,floor((alpha/2.f) + 0.5)); // there doesn't seem to be a round in cmath for windows.
		//w = pow(2,round(alpha/2.f));
		h = w;//pow(2,round(alpha - round(alpha/2.f)));
		int x=0;
		int y=0;
		int maxRowHeight = sortedCopy[0].tH + border*2;
		for(int i=0;i<(int)cps.size();i++){
			if(x+sortedCopy[i].tW + border*2>w){
				x = 0;
				y += maxRowHeight;
				maxRowHeight = sortedCopy[i].tH + border*2;
				if(y + maxRowHeight > h){
					alpha++;
					break;
				}
			}
			x+= sortedCopy[i].tW + border*2;
			if(i==(int)cps.size()-1) packed = true;
		}

	}

    // create the atlas
	ofPixels atlasPixels;
	atlasPixels.allocate(w,h,2);
	atlasPixels.set(0,255);
	atlasPixels.set(1,0);


	int x=0;
	int y=0;
	int maxRowHeight = sortedCopy[0].tH + border*2;
	for(int i=0;i<(int)cps.size();i++){
		ofPixels & charPixels = expanded_data[sortedCopy[i].characterIndex];

		if(x+sortedCopy[i].tW + border*2>w){
			x = 0;
			y += maxRowHeight;
			maxRowHeight = sortedCopy[i].tH + border*2;
		}

		cps[sortedCopy[i].characterIndex].t2		= float(x + border)/float(w);
		cps[sortedCopy[i].characterIndex].v2		= float(y + border)/float(h);
		cps[sortedCopy[i].characterIndex].t1		= float(cps[sortedCopy[i].characterIndex].tW + x + border)/float(w);
		cps[sortedCopy[i].characterIndex].v1		= float(cps[sortedCopy[i].characterIndex].tH + y + border)/float(h);
		charPixels.pasteInto(atlasPixels,x+border,y+border);
		x+= sortedCopy[i].tW + border*2;
	}


	texAtlas.allocate(atlasPixels.getWidth(),atlasPixels.getHeight(),GL_LUMINANCE_ALPHA,false);

	if(settings.bAntiAliased && settings.fontSize > 20){
		texAtlas.setTextureMinMagFilter(GL_LINEAR,GL_LINEAR);
	}else{
		texAtlas.setTextureMinMagFilter(GL_NEAREST,GL_NEAREST);
	}

	texAtlas.loadData(atlasPixels.getPixels(),atlasPixels.getWidth(),atlasPixels.getHeight(),GL_LUMINANCE_ALPHA);

	// ------------- close the library and typeface
	FT_Done_Face(face);
	FT_Done_FreeType(library);
  	bLoadedOk = true;
	return true;
}

//-----------------------------------------------------------
bool ofxGuiFont::isLoaded() {
	return bLoadedOk;
}

//-----------------------------------------------------------
bool ofxGuiFont::isAntiAliased() {
	return settings.bAntiAliased;
}

//-----------------------------------------------------------
bool ofxGuiFont::hasFullCharacterSet() {
	return settings.bFullCharacterSet;
}

//-----------------------------------------------------------
bool ofxGuiFont::hasKerning() {
	return bHasKerning;
}

//-----------------------------------------------------------
bool ofxGuiFont::hasContours() {
    return bHasContours;
}

//-----------------------------------------------------------
int ofxGuiFont::getSize() {
	return settings.fontSize;
}

//-----------------------------------------------------------
void ofxGuiFont::setLineHeight(float _newLineHeight) {
	lineHeight = _newLineHeight;
}

//-----------------------------------------------------------
float ofxGuiFont::getLineHeight(){
	return lineHeight;
}

//-----------------------------------------------------------
void ofxGuiFont::setLetterSpacing(float _letterSpacing) {
	letterSpacing = _letterSpacing;
}

//-----------------------------------------------------------
float ofxGuiFont::getLetterSpacing(){
	return letterSpacing;
}

//-----------------------------------------------------------
void ofxGuiFont::setSpaceSize(float _spaceSize) {
	spaceSize = _spaceSize;
}

//-----------------------------------------------------------
float ofxGuiFont::getSpaceSize(){
	return spaceSize;
}

//------------------------------------------------------------------
ofCharacter ofxGuiFont::getCharacterAsPoints(int character, float x, float y){
    return getCharacterAsPoints(character, ofPoint(x,y));
}

//------------------------------------------------------------------
ofCharacter ofxGuiFont::getCharacterAsPoints(int character, ofPoint p){
	if(bHasContours == false ){
		ofLog(OF_LOG_ERROR, "getCharacterAsPoints: contours not created,  call loadFont with makeContours set to true" );
	}
    
	if( bHasContours && !charOutlines.empty() && isInShapeCharacterSet(character) ){
		ofCharacter ch = charOutlines[charToIndex(character)];
        ch.translate(p); 
        return ch;
	}else{
		if(charOutlines.empty()) {
            charOutlines.push_back(ofCharacter());   
        }
		return charOutlines[0];
	}
}

//------------------------------------------------------------------
bool ofxGuiFont::isInCharacterSet(int character) {
    return character >= NUM_CHARACTER_TO_START_ && charToIndex(character) < nCharacters;
}

//------------------------------------------------------------------
bool ofxGuiFont::isInShapeCharacterSet(int character) {
    return character >= NUM_CHARACTER_TO_START_ && charToIndex(character) < (int)charOutlines.size();
}


//-----------------------------------------------------------
ofCharacter ofxGuiFont::drawChar(int character, float x, float y, bool asShapes) {

    bool alreadyBinded = binded;
    if(!alreadyBinded) bind();

    ofPoint p(x,y);

    ofTextAlignHorz hAlign = OF_TEXT_ALIGN_HORZ_LEFT;//ofGetTextAlignHorz(); // not part of ofStyles yet
    ofTextAlignVert vAlign = OF_TEXT_ALIGN_VERT_TOP;//ofGetTextAlignVert(); // not part of ofStyles yet
    
    // no adjustments if hAlign -> left and vAlign -> baseline

    // make horizontal adjustments
    if (hAlign == OF_TEXT_ALIGN_HORZ_CENTER) {
        p.x -= _widthChar(character) / 2.0f;
    } else if (hAlign == OF_TEXT_ALIGN_HORZ_RIGHT) {
        p.x -= _widthChar(character);
    }

    // make vertical adjustments
    if (vAlign == OF_TEXT_ALIGN_VERT_CENTER) {
        p.y += getAscender() / 2;
    } else if (vAlign == OF_TEXT_ALIGN_VERT_TOP) {
        p.y += getAscender();
    } else if (vAlign == OF_TEXT_ALIGN_VERT_BOTTOM) {
        p.y -= getDescender();
    }
    
    // render
    _drawChar(character, p, asShapes);

    // record and return actual offsets
    ofCharacter co;
    co.c = character;
    co.offset = p;
    
    if(!alreadyBinded) unbind();

    return co; 
    
}

//-----------------------------------------------------------
ofCharacter ofxGuiFont::drawChar(int character, ofPoint p, bool asShapes) {
    return drawChar(character,p.x,p.y,asShapes);
}

//-----------------------------------------------------------
ofCharacter ofxGuiFont::drawCharAsShapes(int character, float x, float y) {
    return drawChar(character, x, y, true);
}

//-----------------------------------------------------------
ofCharacter ofxGuiFont::drawCharAsShapes(int character, ofPoint p) {
    return drawChar(character, p.x, p.y, true);
}


//-----------------------------------------------------------
vector<ofCharacter> ofxGuiFont::getStringAsPoints(string s, float x, float y, float w, float h) {
    ofRectangle boundingBox(x,y,w,h);
    return getStringAsPoints(s,boundingBox);
}

//-----------------------------------------------------------
vector<ofCharacter> ofxGuiFont::getStringAsPoints(string s, ofRectangle boundingBox) {

	vector<ofCharacter> shapes;

	if (!bLoadedOk){
		ofLog(OF_LOG_ERROR,"Error : font not allocated -- line %d in %s", __LINE__,__FILE__);
		return shapes;
	};

    vector<ofCharacter> offsets = getCharacterOffsets(s, boundingBox);
    
    for(int i = 0; i < (int)offsets.size(); i++) {
        shapes.push_back(getCharacterAsPoints(s[i]));
        shapes.back().translate(offsets[i].offset);
    }
    
	return shapes;
}

//-----------------------------------------------------------
vector<ofCharacter>  ofxGuiFont::getCharacterOffsets(string s, float x, float y, float w, float h) {
    ofRectangle boundingBox(x,y,w,h);
    return getCharacterOffsets(s, boundingBox);
}

//-----------------------------------------------------------
vector<ofCharacter>  ofxGuiFont::getCharacterOffsets(string s, ofRectangle boundingBox) {
    return textLayout(s, boundingBox, false, false);
}

//-----------------------------------------------------------
float ofxGuiFont::stringWidth(string c) {
    float width = 0;
    int index = 0;
    int start = 0;
    int length = (int)c.length();
    
    while (index < length) {
        if (c[index] == '\n') {
            width = MAX(width, _widthString(c, start, index));
            start = index+1;
        }
        index++;
    }
    
    if (start < length) {
        width = MAX(width, _widthString(c, start, index));
    }
    
    return width;
}

//-----------------------------------------------------------
float ofxGuiFont::_widthChar(int character) {
    int charIndex = charToIndex(character);
    if(isInCharacterSet(character)) { // is it in our char set?
        float xScale = letterSpacing;
        if(character == ' ') xScale *= spaceSize; // respect legacy space size
        return cps[charIndex].setWidth * xScale; // no kerning for single
    } else {
        // char was not in our character set, zero width
        ofLogVerbose("ofxGuiFont::_widthChar character was not in set : " + ofToString((char)character));
        return 0.0f;
    }
}


//-----------------------------------------------------------
float ofxGuiFont::_widthString(string c, int start, int stop) {
    // assume no new lines
    float width = 0.0f;
    if(start >= 0 && stop < (int)c.length() - 1) {
        for (int i = start; i < stop; i++) {
            width += charWidth(c[i]); // scaling in charWidth
            if((i - 1) >= start) { // apply kerning if needed
                width += getHorizontalKerning(c[i-1], c[i]);
            }
        }
    } else {
       // start or stop were out of bounds
        ofLogWarning("ofxGuiFont::_widthString start / stop were out of bounds.");
    }
    return width;
}


//-----------------------------------------------------------
ofVec2f ofxGuiFont::getKerning(int leftChar, int rightChar) {
    ofVec2f k(0.0f,0.0f);
    
    if(bHasKerning && isInCharacterSet(leftChar) && isInCharacterSet(rightChar) ) {
        k = cps[charToIndex(leftChar)].kern[charToIndex(rightChar)];
    } 

    return k;
}

//-----------------------------------------------------------
float   ofxGuiFont::getHorizontalKerning(int leftChar, int rightChar) {
    return getKerning(leftChar, rightChar).x;
}

//-----------------------------------------------------------
float   ofxGuiFont::getVerticalKerning(int leftChar, int rightChar) {
    return getKerning(leftChar, rightChar).y;
}

//-----------------------------------------------------------
int ofxGuiFont::charToIndex(int character) {
    return (character - NUM_CHARACTER_TO_START_);
}

//-----------------------------------------------------------
int ofxGuiFont::indexToChar(int index) {
    return (index + NUM_CHARACTER_TO_START_);
}

//-----------------------------------------------------------
ofRectangle ofxGuiFont::getStringBoundingBox(vector<ofCharacter> offsets, bool shrinkToContours) {
    
    vector<ofCharacter>::iterator it = offsets.begin();

    // keep track of mins and maxs for bounding box
    // initialize to extremes for min/max calcs
    float minx, miny, maxx, maxy;
    miny = minx =  numeric_limits<float>::max();
    maxx = maxy = -numeric_limits<float>::max();

    while(it != offsets.end()) {
        
        int character = (*it).c;
        ofVec2f offset = (*it).offset;
        int charIndex = charToIndex(character);
        
        if(shrinkToContours) {
            minx = MIN(minx,(offset.x + cps[charIndex].x2)); // min x
            miny = MIN(miny,(offset.y + cps[charIndex].y2)); // min y
            maxx = MAX(maxx,(offset.x + cps[charIndex].x1)); // max x
            maxy = MAX(maxy,(offset.y + cps[charIndex].y1)); // max y
        } else {
            minx = 0;
            miny = 0;
            maxx = MAX(maxx,offset.x + cps[charIndex].setWidth); // max x
            maxy = MAX(maxy,offset.y + settings.fontSize);       // max y
        }
        
        ++it;
    }
    
    return ofRectangle(minx, miny, maxx-minx, maxy-miny);
}

//-----------------------------------------------------------
ofRectangle ofxGuiFont::getStringBoundingBox(string s, ofPoint p, bool shrinkToContours) {
    return getStringBoundingBox(s, p.x, p.y, shrinkToContours);
}

//-----------------------------------------------------------
ofRectangle ofxGuiFont::getStringBoundingBox(string s, float x, float y, bool shrinkToContours ){
    
    if ( s.empty() || cps.empty() ) return ofRectangle();
    return getStringBoundingBox(getCharacterOffsets(s, x, y), shrinkToContours);
    
    /*
	int         index	= 0;
	float		X       = 0.0f;
	float		Y       = 0.0f;

    int len = (int)s.length();
   
    while(index < len) {
        int charIndex = charToIndex(s[index]);
        
        if(s[index] == '\n') {
            Y += lineHeight; // go to next row
            X = 0.0f; //reset X Pos back to zero
        } else if(isInCharacterSet(s[index])) {
            // draw the character

            if(skrinkToContours) {
                minx = MIN(minx,(X + cps[charIndex].x2)); // min x
                miny = MIN(miny,(Y + cps[charIndex].y2)); // min y
                maxx = MAX(maxx,(X + cps[charIndex].x1)); // max x
                maxy = MAX(maxy,(Y + cps[charIndex].y1)); // max y
            } else {
                minx = 0;
                miny = 0;
                maxx = MAX(maxx,X + cps[charIndex].setWidth); // max x
                maxy = MAX(maxy,Y + settings.fontSize);       // max y
            }
            
            // calculate horizontal scaling 
            float xScale = letterSpacing;            // respect existing letter spacing scaler
            if(s[index] == ' ') xScale *= spaceSize; // respect existing space char scaler
            
            // advance the cursor
            X += (cps[charIndex].setWidth * xScale);
            
            // adjust the cursor for kerning if needed
            if(bHasKerning && ((index + 1) < len) && s[index+1] != '\n') {
                X += getKerning(s[index], s[index+1]).x;
            }
        } else {
            // unknown character
        }
        
        index++;
    }
     */
}


//-----------------------------------------------------------
float ofxGuiFont::stringHeight(string s) {
    ofRectangle rect = getStringBoundingBox(s, 0,0);
    return rect.height;
}

vector<ofCharacter> ofxGuiFont::drawString(string s, float x, float y, float w, float h, bool asShapes) {
    ofRectangle boundingBox(x,y,w,h);
    return textLayout(s, boundingBox, true, asShapes);
}

//=====================================================================
vector<ofCharacter> ofxGuiFont::drawString(string s, ofRectangle boundingBox, bool asShapes) {
    return textLayout(s, boundingBox, true, asShapes);
}


//=====================================================================
void ofxGuiFont::drawString(vector<ofCharacter> offsets, ofVec2f offset, bool asShapes) {
    ofPushMatrix();
    ofTranslate(offset);
    
    // enable binding for the group
    bool alreadyBinded = binded;
    if(!alreadyBinded) bind();
    
    for(int i = 0; i < (int)offsets.size(); i++) {
        _drawChar(offsets[i].c, offsets[i].offset, asShapes);
    }
    
    if(!alreadyBinded) unbind();
    
    ofPopMatrix();
}



//=====================================================================
vector<ofCharacter> ofxGuiFont::drawStringAsShapes(string s, float x, float y, float w, float h) {
    ofRectangle boundingBox(x,y,w,h);
    return textLayout(s, boundingBox, true, true);
}

//=====================================================================
vector<ofCharacter> ofxGuiFont::drawStringAsShapes(string s, ofRectangle boundingBox) {
    return textLayout(s, boundingBox, true, true);
}

//=====================================================================
void ofxGuiFont::drawStringAsShapes(vector<ofCharacter> offsets, ofVec2f offset) {
    return drawString(offsets,offset,true);
}

//=====================================================================
void ofxGuiFont::_drawChar(int character, ofPoint p, bool asShapes) {

    if(character == ' ' || character == '\r' || character == '\n') {
        return; // we never draw spaces (?)
    }

    if (!isInCharacterSet(character)){
		ofLog(OF_LOG_WARNING,"Error : char (%i) not allocated -- line %d in %s", character, __LINE__,__FILE__);
		return;
	}
    
    
    int charIndex = charToIndex(character);
    
    // bind here if needed
    
    if(asShapes) {
        ofCharacter & charRef = charOutlines[charIndex];
        charRef.setFilled(ofGetStyle().bFill);
        charRef.draw(p.x,p.y); // TODO, add draw(ofPoint) to ofPath
    } else {
        
        bool alreadyBinded = binded;
        if(!alreadyBinded) bind();
        
        float	x1, y1, x2, y2;
        float   t1, v1, t2, v2;
        t2		= cps[charIndex].t2;
        v2		= cps[charIndex].v2;
        t1		= cps[charIndex].t1;
        v1		= cps[charIndex].v1;
        
        x1		= cps[charIndex].x1+p.x;
        y1		= cps[charIndex].y1+p.y;
        x2		= cps[charIndex].x2+p.x;
        y2		= cps[charIndex].y2+p.y;
        
        int firstIndex = stringQuads.getVertices().size();
        
        stringQuads.addVertex(ofVec3f(x1,y1));
        stringQuads.addVertex(ofVec3f(x2,y1));
        stringQuads.addVertex(ofVec3f(x2,y2));
        stringQuads.addVertex(ofVec3f(x1,y2));
        
        stringQuads.addTexCoord(ofVec2f(t1,v1));
        stringQuads.addTexCoord(ofVec2f(t2,v1));
        stringQuads.addTexCoord(ofVec2f(t2,v2));
        stringQuads.addTexCoord(ofVec2f(t1,v2));
        
        stringQuads.addIndex(firstIndex);
        stringQuads.addIndex(firstIndex+1);
        stringQuads.addIndex(firstIndex+2);
        stringQuads.addIndex(firstIndex+2);
        stringQuads.addIndex(firstIndex+3);
        stringQuads.addIndex(firstIndex);

        if(!alreadyBinded) unbind();

    }
    

    
}



//-----------------------------------------------------------
vector<ofCharacter>  ofxGuiFont::textLayout(string s, 
                                              ofRectangle bb,
                                              bool draw,
                                              bool drawShapes) {
    
	vector<ofCharacter> offsets;
    
    if (!bLoadedOk){
    	ofLog(OF_LOG_ERROR,"ofxGuiFont::drawString - Error : font not allocated -- line %d in %s", __LINE__,__FILE__);
    	return offsets;
    }
    
	if (drawShapes && !bHasContours){
		ofLog(OF_LOG_ERROR,"ofxGuiFont::drawStringAsShapes - Error : contours not created for this font - call loadFont with makeContours set to true");
		return offsets;
	}

    ofTextAlignHorz hAlign = OF_TEXT_ALIGN_HORZ_LEFT;//ofGetTextAlignHorz();
    ofTextAlignVert vAlign = OF_TEXT_ALIGN_VERT_TOP;//ofGetTextAlignVert();
    
    // bind as a group of textures if we are drawing
    bool alreadyBinded = binded;
    if(draw && !drawShapes && !alreadyBinded) bind();

    float bbX = bb.x; // init @ the bounding box x
    float bbY = bb.y; // init @ the bounding box y
    float bbW = bb.width;
    float bbH = bb.height;
                    // nice to use an ofPoly instead of a ofRect for a variety of bounding shapes
    
    // word wrapping!
    int         index	= 0;
	float		X       = 0; // current x // will adjust all offsets
	float		Y       = 0; // current y // will adjust all offsets
    
    int len = (int)s.length();
    
    float lineHeight = getLineHeight();

    // iteration parameters
    int     lastWordStart   = 0;

    bool    isCharBreakMode = false;// (lineBreakMode == LINE_BREAK_MODE_NONE ||
                            //lineBreakMode == LINE_BREAK_MODE_CHARACTER);

    string inputString = s;
    
    vector< vector<ofCharacter*> > lines;
    vector< float > lineWidths;
    
    lines.push_back(vector<ofCharacter*>());
    
    for(int i = 0; i < len; i++) {
        
        bool hasNextChar = (i + 1) < len;
        bool hasLastChar = (i > 0);

        const int lastChar = hasLastChar ? inputString[i-1] : -1; 
        const int thisChar = inputString[i];
        const int nextChar = hasNextChar ? inputString[i+1] : -1; 
        
        float thisCharWidth    = _widthChar(thisChar);
        float thisCharKerning  = hasNextChar ? getHorizontalKerning(thisChar, nextChar) : 0.0f;
        
        bool isThisCharSpace   =                Poco::Ascii::isSpace(thisChar);
        bool isLastCharSpace   = hasLastChar && Poco::Ascii::isSpace(lastChar);

        bool isLastCharNewline = hasLastChar && (thisChar == '\n');
        bool isThisCharNewline =                (thisChar == '\n');
        
        // make this more complicated later
        // soft hyphens, etc
        bool canBreak = (i > 0) && (!isThisCharSpace);
        
        if((!isThisCharSpace && (isLastCharSpace))) {
            lastWordStart = i;
        }
        
        
        float thisCharOffset = (thisCharKerning + thisCharWidth);
        float proposedLineWidth = (X + thisCharOffset  );
        float currentWordLength = proposedLineWidth - ( ( i > 0 ) ? offsets[lastWordStart].offset.x : 0.0f);
        
        if(isThisCharNewline || (canBreak && proposedLineWidth > bbW)) {
            
            Y += lineHeight; // next line

            if(!isThisCharNewline && lastWordStart != i && currentWordLength <= bbW) {
                float wordStartOffset = offsets[lastWordStart].offset.x;
                // shift all letters
                for(int k = lastWordStart; k < i; k++) {
                    offsets[k].offset.x -= wordStartOffset;
                    offsets[k].offset.y = Y;
                }
                
                X -= wordStartOffset;
            } else {
                X = 0;
            }

            lines.push_back(vector<ofCharacter*>());
        
        }

        ofCharacter charOffset;
        charOffset.c = thisChar;
        charOffset.offset = ofVec2f(X,Y);
        offsets.push_back(charOffset);
        X += thisCharOffset;

        lines.back().push_back(&charOffset);
        
    }
    
    
    for(int i = 0; i < lines.size(); i++) {
        cout << "i=" << i << ">>" << lines[i].size() << "<<>>";
        for(int j = 0; j < lines[i].size(); j++) {
            ofCharacter* _char = lines[i].at(j);
            if(draw) {
                _drawChar(_char->c, _char->offset, drawShapes);
            }

            cout << "|" << _char->c;
        }
        cout << endl;
    }
    
    

    cout << "lines found = " << lines.size() << endl;

    
    /*
    float currentY = -FLT_MAX;
    int currentLineZ = -1;
    //cout << ">>";
    float lineMaxX = 0;
    for(int k = 0; k < offsets.size(); k++) {
        ofCharacter thisChar = offsets[k];
        
       if(thisChar.offset.y > currentY) {
           currentLineZ++;
           currentY = thisChar.offset.y;
    //       cout << endl;
    //       cout << currentLine << ": ";
       }

     //   cout << (char)thisChar.c;
        
        
        if(draw) {
            _drawChar(thisChar.c, thisChar.offset, drawShapes);
        }
    }
     */
     
    
   // cout << "-----------" << endl;
    
    // release textures if we previously bound them
    if(draw && !drawShapes && !alreadyBinded) unbind();
    
    return offsets;
}


//-----------------------------------------------------------
void ofxGuiFont::bind(){
	if(!binded){
	    // we need transparency to draw text, but we don't know
	    // if that is set up in outside of this function
	    // we "pushAttrib", turn on alpha and "popAttrib"
	    // http://www.opengl.org/documentation/specs/man_pages/hardcopy/GL/html/gl/pushattrib.html

	    // **** note ****
	    // I have read that pushAttrib() is slow, if used often,
	    // maybe there is a faster way to do this?
	    // ie, check if blending is enabled, etc...
	    // glIsEnabled().... glGet()...
	    // http://www.opengl.org/documentation/specs/man_pages/hardcopy/GL/html/gl/get.html
	    // **************
		// (a) record the current "alpha state, blend func, etc"
		#ifndef TARGET_OPENGLES
			glPushAttrib(GL_COLOR_BUFFER_BIT);
		#else
			blend_enabled = glIsEnabled(GL_BLEND);
			texture_2d_enabled = glIsEnabled(GL_TEXTURE_2D);
			glGetIntegerv( GL_BLEND_SRC, &blend_src );
			glGetIntegerv( GL_BLEND_DST, &blend_dst );
		#endif

	    // (b) enable our regular ALPHA blending!
	    glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		texAtlas.bind();
		stringQuads.clear();
		binded = true;
	}
}

//-----------------------------------------------------------
void ofxGuiFont::unbind(){
	if(binded){
		stringQuads.drawFaces();
		texAtlas.unbind();

		#ifndef TARGET_OPENGLES
			glPopAttrib();
		#else
			if( !blend_enabled )
				glDisable(GL_BLEND);
			if( !texture_2d_enabled )
				glDisable(GL_TEXTURE_2D);
			glBlendFunc( blend_src, blend_dst );
		#endif
		binded = false;
	}
}


//-----------------------------------------------------------
int ofxGuiFont::getNumCharacters() {
	return nCharacters;
}

//-----------------------------------------------------------
string ofxGuiFont::getFamilyName() {
    if (!bLoadedOk){
    	ofLog(OF_LOG_ERROR,"ofxGuiFont::getFamilyName - Error : font not allocated -- line %d in %s", __LINE__,__FILE__);
    }
    return fontFamilyName;
}
//-----------------------------------------------------------
string ofxGuiFont::getStyleName() {
    if (!bLoadedOk){
    	ofLog(OF_LOG_ERROR,"ofxGuiFont::getStyleName - Error : font not allocated -- line %d in %s", __LINE__,__FILE__);
    }
    return fontStyleName;
}
//-----------------------------------------------------------
int ofxGuiFont::getNumFacesInFont() {
    if (!bLoadedOk){
    	ofLog(OF_LOG_ERROR,"ofxGuiFont::getNumFacesInFont - Error : font not allocated -- line %d in %s", __LINE__,__FILE__);
    }
    return numFacesInFont;
}
//-----------------------------------------------------------
int ofxGuiFont::getCurrentFaceIndex() {
    if (!bLoadedOk){
    	ofLog(OF_LOG_ERROR,"ofxGuiFont::getCurrentFaceIndex - Error : font not allocated -- line %d in %s", __LINE__,__FILE__);
    }
    return currentFaceIndex;
}
//-----------------------------------------------------------
int ofxGuiFont::getMaxAdvanceWidth() {
    if (!bLoadedOk){
    	ofLog(OF_LOG_ERROR,"ofxGuiFont::getMaxAdvanceWidth - Error : font not allocated -- line %d in %s", __LINE__,__FILE__);
    }
    return maxAdvanceWidth;
}
//-----------------------------------------------------------
int ofxGuiFont::getMaxAdvanceHeight() {
    if (!bLoadedOk){
    	ofLog(OF_LOG_ERROR,"ofxGuiFont::getMaxAdvanceHeight - Error : font not allocated -- line %d in %s", __LINE__,__FILE__);
    }
    return maxAdvanceHeight;
}
//-----------------------------------------------------------
int ofxGuiFont::getUnderlinePosition() {
    if (!bLoadedOk){
    	ofLog(OF_LOG_ERROR,"ofxGuiFont::getUnderlinePosition - Error : font not allocated -- line %d in %s", __LINE__,__FILE__);
    }
    return underlinePosition;
}
//-----------------------------------------------------------
int ofxGuiFont::getUnderlineThickness() {
    if (!bLoadedOk){
    	ofLog(OF_LOG_ERROR,"ofxGuiFont::getUnderlineThickness - Error : font not allocated -- line %d in %s", __LINE__,__FILE__);
    }
    return underlineThickness;
}
//-----------------------------------------------------------
int ofxGuiFont::getAscender() {
    if (!bLoadedOk){
    	ofLog(OF_LOG_ERROR,"ofxGuiFont::getAscender - Error : font not allocated -- line %d in %s", __LINE__,__FILE__);
    }
    return ascender;
}
//-----------------------------------------------------------
int ofxGuiFont::getDescender() {
    if (!bLoadedOk){
    	ofLog(OF_LOG_ERROR,"ofxGuiFont::getDescender - Error : font not allocated -- line %d in %s", __LINE__,__FILE__);
    }
    return descender;
}
//-----------------------------------------------------------
int ofxGuiFont::getHeight() {
    if (!bLoadedOk){
    	ofLog(OF_LOG_ERROR,"ofxGuiFont::getHeight - Error : font not allocated -- line %d in %s", __LINE__,__FILE__);
    }
    return height;
}



