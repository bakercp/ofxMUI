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

#pragma once

#include "ofMain.h"
#include "ofxMuiFont.h"
#include <Poco/RegularExpression.h>
#include <Poco/StringTokenizer.h>
#include <Poco/String.h>
#include <Poco/Ascii.h>

using Poco::toUpper;
using Poco::toLower;
using Poco::toUpperInPlace;
using Poco::toLowerInPlace;
using Poco::StringTokenizer;
using Poco::cat;
using Poco::RegularExpression;

enum ofxMuiCapsMode {
    LABEL_CAPS_NONE = 0,
    LABEL_CAPS_UPPER,
    LABEL_CAPS_LOWER,
    LABEL_CAPS_TITLE_CASE,
    LABEL_CAPS_SENTENCE_CASE,
    LABEL_CAPS_TOGGLE_CASE
};


enum ofxMuiLineTruncationMode {
    LINE_TRUNCATION_MODE_CLIP = 0, // Clip the text when the end of the drawing rectangle is reached. 
    // This option could result in a partially rendered character at the end of a string.
    LINE_TRUNCATION_MODE_HEAD, // Truncate text (as needed) from the beginning of the line. For multiple 
    // lines of text, only text on the first line is truncated.
    LINE_TRUNCATION_MODE_TAIL, // Truncate text (as needed) from the end of the line. For multiple 
    // lines of text, only text on the last line is truncated.
    LINE_TRUNCATION_MODE_MIDDLE // Truncate text (as needed) from the middle of the line. For multiple lines of text, 
    //text is truncated only at the midpoint of the line.
};



enum ofxMuiLineBreakMode {
    LINE_BREAK_MODE_NONE = 0, 
    LINE_BREAK_MODE_CHARACTER, // "Wrap or clip the string at the closest character boundary."
    LINE_BREAK_MODE_WORD, // "Wrap or clip the string only at word boundaries. This is the default wrapping option."
    //LINE_BREAK_MODE_SYLLABLE, // 
    //LINE_BREAK_MODE_WORD_KNUTH, // Knuth's paragraphing
};


//--------------------------------------------------------------
static void applyTruncation(ofxMuiFont* ttf,
                         string& stringToTruncate,
                         float& stringToTruncateWidth,
                         float maximumWidth,
                         ofxMuiLineTruncationMode lineTruncationMode,
                         string truncateString) {

    // TODO TODOD
    // TODO THIS STRING WIDTH FUNCTION GIVES THE WIDTH OF A BLOCK, NOT JSUT A SINGLE LINE
    // THEREFORE< IT PROBABLY WON"T WORK AS EXPECTED
    // PERHAPS replace all \n \r\n before truncating or 
    
    
    // shortcut everything if possible
    stringToTruncateWidth = ttf->stringWidth(stringToTruncate);
    if(stringToTruncateWidth <= maximumWidth) {
        return;
    }
    
    float truncationStringWidth = ttf->stringWidth(truncateString);
    string ss = stringToTruncate;
    
    /*
    if(lineBreakMode == LINE_BREAK_MODE_CLIP) {
        int i;
        for(i = 0; i < ss.length(); i++) {
            float totalWidth = truncationStringWidth + ttf->stringWidth(ss.substr(0,i));
            if(totalWidth > maximumWidth) {
                i--;
                break;
            }
        }
        stringToTruncate = ss.substr(0,i);
        stringToTruncateWidth = ttf->stringWidth(stringToTruncate);
        
    } else */
    if(lineTruncationMode == LINE_TRUNCATION_MODE_HEAD) {
        reverse(ss.begin(), ss.end());
        reverse(truncateString.begin(),truncateString.end());
        int i = 0;
        for(i = 0; i < ss.length(); i++) {
            float totalWidth = truncationStringWidth + ttf->stringWidth(ss.substr(0,i));
            if(totalWidth > maximumWidth) {
                i--;
                break;
            }
        }
        stringToTruncate = ss.substr(0,i) + truncateString; // add the trunc string
        reverse(stringToTruncate.begin(), stringToTruncate.end()); // put it back in the right order
        stringToTruncateWidth = ttf->stringWidth(stringToTruncate); // calculate the new width
        
    } else if(lineTruncationMode == LINE_TRUNCATION_MODE_TAIL) {
        int i  = 0;
        for(i = 0; i < ss.length(); i++) {
            float totalWidth = truncationStringWidth + ttf->stringWidth(ss.substr(0,i));
            if(totalWidth > maximumWidth) {
                i--;
                break;
            }
        }
        stringToTruncate = ss.substr(0,i) + truncateString; // add the trunc string
        stringToTruncateWidth = ttf->stringWidth(stringToTruncate);
        
    } else if(lineTruncationMode == LINE_TRUNCATION_MODE_MIDDLE) {

        float totalWidth = truncationStringWidth;

        int length = (int)(ss.length());
        int halfWayPoint = (int)(length / 2);
        string firstHalf = ss.substr(0,halfWayPoint);
        string secondHalf = ss.substr(halfWayPoint,length);

        bool first = true;
        int firstI = int(firstHalf.length());
        int secondI = int(0);

        for(int i = 0; i < halfWayPoint; i++) {
            if(first) {
                firstI--;
            } else {
                secondI++;
            }

            float totalWidth = truncationStringWidth;
            totalWidth += ttf->stringWidth(firstHalf.substr(0,firstI));
            totalWidth += ttf->stringWidth(secondHalf.substr(secondI,secondHalf.length()));

            //cout << "tot=" << totalWidth << " max=" << maximumWidth << "|" << firstI << "|" << secondI <<  endl;
            
            if(totalWidth <= maximumWidth) {
              //  cout << "IN HERE" << endl;
              //  cout << "tot=" << totalWidth << " max=" << maximumWidth << endl;
                
                /*
                if(first) {
                    firstI++;
                } else {
                    secondI--;
                }
                 */
                break;
            }

            first = !first; // toggle
        }

        //cout << firstI << "|" << secondI << endl;
        
        firstHalf = firstHalf.substr(0,firstI);
        secondHalf = secondHalf.substr(0,secondI);

        stringToTruncate = firstHalf + truncateString + secondHalf;
        stringToTruncateWidth = ttf->stringWidth(stringToTruncate);
        
    } else {
        // nothing to be done so just finish up here
        /// XXX
        return;
    }
};

static void applyCaps(string& displayText, ofxMuiCapsMode capsStyle) {

    string::iterator it = displayText.begin();
    string::iterator end = displayText.end();
    bool waiting = true;
    
    switch (capsStyle) {
        case LABEL_CAPS_NONE:
            break;
        case LABEL_CAPS_UPPER:
            while (it != end) { *it = Poco::Ascii::toUpper(*it); ++it; }
            break;
        case LABEL_CAPS_LOWER:
            while (it != end) { *it = Poco::Ascii::toLower(*it); ++it; }
            break;
        case LABEL_CAPS_TITLE_CASE:
            while (it != end) {
                *it = Poco::Ascii::toLower(*it); // all default lower
                if(waiting) *it = Poco::Ascii::toUpper(*it); 
                waiting = Poco::Ascii::isSpace(*it);
                ++it; 
            }
            break;
        case LABEL_CAPS_SENTENCE_CASE:
            while (it != end) {
                if(!Poco::Ascii::isSpace(*it)) {
                    if(waiting) {
                        // punctuation was waiting, so send it to upper case
                        *it = Poco::Ascii::toUpper(*it);
                        waiting = false;
                    } else {
                        if(*it == '.'  || *it == '!'  || 
                           *it == '?'  || *it == '\n' || 
                           *it == '\r' ) {
                            waiting = true;     
                        } else {
                            *it = Poco::Ascii::toLower(*it); 
                        }
                    }
                }
                ++it; 
            }            
            break;
        case LABEL_CAPS_TOGGLE_CASE:
            while (it != end) { 
                if(Poco::Ascii::isUpper(*it)) { 
                    *it = Poco::Ascii::toLower(*it); 
                } else {
                    *it = Poco::Ascii::toUpper(*it); 
                }
                ++it; 
            }
            break;
    }

};


//--------------------------------------------------------------
static void breakLines(ofxMuiFont* ttf,
                       string& stringToWrap,
                       vector<int>& breakPos,
                       vector<ofVec2f>& charPos,
                       vector<float>& lineWidths,
                       vector<string>& lines,
                       ofRectangle& boundingBox,
                       const ofRectangle& goalBox,
                       const ofxMuiLineBreakMode lineBreakMode = LINE_BREAK_MODE_NONE, 
                       const string delimiters = " ",
                       const ofxMuiLineTruncationMode lineTruncationMode = LINE_TRUNCATION_MODE_CLIP, 
                       const string truncationString = "",
                       int maxLines = numeric_limits<int>::max()) {

    
    // establish tokens
    vector<string> tokens;
    
    string delimiter;
    
    // TODO: currently this method requires two passes ... one for 
    // delimiting and one for breaking.  best to put it all
    // in a single smart pass.
    if(lineBreakMode == LINE_BREAK_MODE_NONE ||
       lineBreakMode == LINE_BREAK_MODE_CHARACTER) {
        delimiter = "";
        string::iterator it  = stringToWrap.begin();
        string::iterator end = stringToWrap.end();
        while(it != end) { tokens.push_back(ofToString(*it)); ++it;};
    } else if(lineBreakMode == LINE_BREAK_MODE_WORD) {
        delimiter = " ";
        StringTokenizer tok(stringToWrap, delimiter);
        StringTokenizer::Iterator it = tok.begin();
        StringTokenizer::Iterator end = tok.end();
        while(it != end) { tokens.push_back(*it); ++it;};
    }
    
    
    //string::iterator begin  = stringToWrap.begin();
    //string::iterator it     = begin;
    //string::iterator end    = stringToWrap.end();

    vector<string>::iterator begin = tokens.begin();
    vector<string>::iterator it = tokens.begin();
    vector<string>::iterator end = tokens.end();
    

    stringToWrap = ""; // clean it out
    string currentLine = "";
    float currentWidth = 0;
    /*
    bool isCharBreakMode = (lineBreakMode == LINE_BREAK_MODE_NONE ||
                            lineBreakMode == LINE_BREAK_MODE_CHARACTER);

    
    float height = ttf->getLineHeight();
    int len = (int)stringToWrap.size();
    int lastBreak = -1;
    
    float lineWidth = 0.0f;
    float x = 0.0f;
    float y = 0.0f;
    float w = goalBox.width;
    float h = goalBox.height;
    float textwidth = 0;
    
    bool isBreakable = false;
    bool wasBreakable = false;
    bool isParens = false;
    bool wasParens = false;
    
    string inputString = stringToWrap;
    
    for(int i = 0; i < len; i++) {
        
        const int c = inputString.at(i); // current char
        const float ww = ttf->charWidth(c); // current char width

        float bb = ttf->stringWidth(ofToString(c));
        cout << ">" << (char)c << "<" << ww << "|" << bb << endl;;
        
        // check for parens, b/c they need a special case
        isParens = ( c == '(' || c == '[' || c == '{' ); // test for start parens
        
        // we ca
        isBreakable = (( isCharBreakMode || 
                        Poco::Ascii::isSpace(c) || 
                        Poco::Ascii::isPunct(c) //also break @ symbols and other
                        ) 
                       && !isParens);
        
        // if there is a paren coming, then we break now
        if ( !isBreakable && i < len-1 ) {
            const int nextc = inputString.at(i + 1); // look at next char
            isBreakable = ( nextc == '(' || nextc == '[' || nextc == '{' );
        }
        
        // Special case for '/': after normal chars it's breakable (e.g. inside a path),
        // but after another breakable char it's not (e.g. "mounted at /foo")
        // Same thing after a parenthesis (e.g. "dfaure [/fool]")
        if ( c == '/' && (wasBreakable || wasParens) ) {
            isBreakable = false;
        }
  
        //cout << "c='" << ofToString((unsigned char)c) << "' i=" << i << "/" << len << " x=" << x << " ww=" << ww << " w=" << w << " lastBreak=" << lastBreak << " isBreakable=" << isBreakable << endl;
       
        int breakAt = -1;
                
        if ( x + ww > w && lastBreak != -1 ) // time to break and we know where
            breakAt = lastBreak;
        
        if ( x + ww > w - 4 && lastBreak == -1 ) // time to break but found nowhere [-> break here]
            breakAt = i;
        
        if (i == len - 2 && x + ww + ttf->charWidth(inputString.at(i + 1)) > w) // don't leave the last char alone
            breakAt = (lastBreak == -1) ? (i - 1) : lastBreak;
        
        if ( c == '\n' ) // Forced break here
        {
            if ( breakAt == -1 && lastBreak != -1) // only break if not already breaking
            {
                breakAt = i - 1;
                lastBreak = -1;
            }
            // remove the line feed from the string
            stringToWrap.erase(stringToWrap.begin()+i);
            inputString.erase(inputString.begin()+i);
            len--;
        }
        
        if ( breakAt != -1 )
        {
            //kDebug() << "KWordWrap::formatText breaking after " << breakAt;
            breakPos.push_back( breakAt );
            float thisLineWidth = lastBreak == -1 ? x + ww : lineWidth;
            lineWidths.push_back( thisLineWidth );
            textwidth = MAX( textwidth, thisLineWidth );
            x = 0;
            y += height;
            wasBreakable = true;
            wasParens = false;
            if ( lastBreak != -1 )
            {
                // Breakable char was found, restart from there
                i = lastBreak;
                lastBreak = -1;
                continue;
            }
        } else if ( isBreakable )
        {
            lastBreak = i;
            lineWidth = x + ww;
        }
        x += ww;
        wasBreakable = isBreakable;
        wasParens = isParens;
    }
    
    textwidth = MAX( textwidth, x );
    lineWidths.push_back( x );
    y += height;
    //kDebug() << "KWordWrap::formatText boundingRect:" << r.x() << "," << r.y() << " " << textwidth << "x" << y;
    if ( goalBox.height >= 0 && y > goalBox.height )
        textwidth = goalBox.width;
    int realY = y;
    if ( goalBox.height >= 0 )
    {
        while ( realY > goalBox.height )
            realY -= height;
        realY = MAX( realY, 0 );
    }
    
    boundingBox.set( 0, 0, textwidth, realY );
    */
    
    

    while (it != end) {
        // TODO: this is a problem b/c 
        // take care of \r\n && \n
        if(*it == "\r" || *it == "\n") {
            // take care of \r\n
            if((it+1) != end && *(it+1) == "\n") {
                currentLine += *it;
                ++it; // get the trailing '\n'
            }
            
            // take care of \r or \n alone
            currentLine += *it;
            lines.push_back(currentLine);
            stringToWrap += currentLine + "\n";
            currentLine.clear();
            //currentWidth = 0;

        } else {
            // no special case, so we just proceed normally
            currentWidth = ttf->stringWidth(currentLine + *it + delimiter);
            
            if(currentWidth < goalBox.width) {
                // it will fit so add it
                currentLine += (*it + delimiter);
                //currentWidth = proposedLineWidth;
            } else {
                // it won't fit, so push the last line and start a new one
                lines.push_back(currentLine);
                stringToWrap += currentLine + "\n";
                //currentLine.clear();
                // start a new line
                currentLine = (*it + delimiter);
                //currentWidth = proposedLineWidth;
            }
        }
                
        cout << currentWidth << "|" << goalBox.width << "|" << currentLine << endl;
        
        ++it; // keep moving
    }
    
    // push the rest
    lines.push_back(currentLine);
    stringToWrap += currentLine + "\n";

}

