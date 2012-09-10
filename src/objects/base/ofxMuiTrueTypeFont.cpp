/*==============================================================================
 
 Copyright (c) 2009-2012 Christopher Baker <http://christopherbaker.net>
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 
 ==============================================================================*/

#include <ofxMuiTrueTypeFont.h>

#include "ft2build.h"
#include "freetype2/freetype/freetype.h"
#include "freetype2/freetype/ftglyph.h"
#include "freetype2/freetype/ftoutln.h"
#include "freetype2/freetype/fttrigon.h"

#include <algorithm>

#include "ofUtils.h"
#include "ofGraphics.h"
/*
static bool printVectorInfo = false;
static int fontGlobalDpi = 96;

//--------------------------------------------------------
static ofTTFCharacter makeContoursForCharacter(FT_Face &face);
static ofTTFCharacter makeContoursForCharacter(FT_Face &face){
    
    //int num			= face->glyph->outline.n_points;
    int nContours	= face->glyph->outline.n_contours;
    int startPos	= 0;
    
    char * tags		= face->glyph->outline.tags;
    FT_Vector * vec = face->glyph->outline.points;
    
    ofTTFCharacter charOutlines;
    charOutlines.setUseShapeColor(false);
    
    for(int k = 0; k < nContours; k++){
        if( k > 0 ){
            startPos = face->glyph->outline.contours[k-1]+1;
        }
        int endPos = face->glyph->outline.contours[k]+1;
        
        if( printVectorInfo )printf("--NEW CONTOUR\n\n");
        
        //vector <ofPoint> testOutline;
        ofPoint lastPoint;
        
        for(int j = startPos; j < endPos; j++){
            
            if( FT_CURVE_TAG(tags[j]) == FT_CURVE_TAG_ON ){
                lastPoint.set((float)vec[j].x, (float)-vec[j].y, 0);
                if( printVectorInfo )printf("flag[%i] is set to 1 - regular point - %f %f \n", j, lastPoint.x, lastPoint.y);
                //testOutline.push_back(lastPoint);
                charOutlines.lineTo(lastPoint/64);
                
            }else{
                if( printVectorInfo )printf("flag[%i] is set to 0 - control point \n", j);
                
                if( FT_CURVE_TAG(tags[j]) == FT_CURVE_TAG_CUBIC ){
                    if( printVectorInfo )printf("- bit 2 is set to 2 - CUBIC\n");
                    
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
                    
                    if( printVectorInfo )printf("- bit 2 is set to 0 - conic- \n");
                    if( printVectorInfo )printf("--- conicPoint point is %f %f \n", conicPoint.x, conicPoint.y);
                    
                    //If the first point is connic and the last point is connic then we need to create a virutal point which acts as a wrap around
                    if( j == startPos ){
                        bool prevIsConnic = (  FT_CURVE_TAG( tags[endPos-1] ) != FT_CURVE_TAG_ON ) && ( FT_CURVE_TAG( tags[endPos-1]) != FT_CURVE_TAG_CUBIC );
                        
                        if( prevIsConnic ){
                            ofPoint lastConnic((float)vec[endPos - 1].x, (float)-vec[endPos - 1].y);
                            lastPoint = (conicPoint + lastConnic) / 2;
                            
                            if( printVectorInfo )	printf("NEED TO MIX WITH LAST\n");
                            if( printVectorInfo )printf("last is %f %f \n", lastPoint.x, lastPoint.y);
                        }
                    }
                    
                    //bool doubleConic = false;
                    
                    int nextIndex = j+1;
                    if( nextIndex >= endPos){
                        nextIndex = startPos;
                    }
                    
                    ofPoint nextPoint( (float)vec[nextIndex].x,  -(float)vec[nextIndex].y );
                    
                    if( printVectorInfo )printf("--- last point is %f %f \n", lastPoint.x, lastPoint.y);
                    
                    bool nextIsConnic = (  FT_CURVE_TAG( tags[nextIndex] ) != FT_CURVE_TAG_ON ) && ( FT_CURVE_TAG( tags[nextIndex]) != FT_CURVE_TAG_CUBIC );
                    
                    //create a 'virtual on point' if we have two connic points
                    if( nextIsConnic ){
                        nextPoint = (conicPoint + nextPoint) / 2;
                        if( printVectorInfo )printf("|_______ double connic!\n");
                    }
                    if( printVectorInfo )printf("--- next point is %f %f \n", nextPoint.x, nextPoint.y);
                    
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

bool compare_cps(const charProps & c1, const charProps & c2){
	if(c1.tH == c2.tH) return c1.tW > c2.tW;
	else return c1.tH > c2.tH;
}

//-----------------------------------------------------------
vector<charProps> ofxMuiTrueTypeFont::getCharacterProperties() {
    return cps;
}
*/

