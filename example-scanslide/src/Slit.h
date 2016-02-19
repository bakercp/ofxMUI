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


#include "SlitNode.h"


class Slit
{
public:
	Slit();
    ~Slit();

    void update();
    
    void draw() const;

	void addNode(SlitNode* slitNode);

	enum Type
	{
		LINEAR,
		CUBIC
	};

private:
	Type _lineType;

	std::vector<SlitNode*> _nodes;


	//void SlitEdge::slitScanSegment(const ofPixels& pixels, const ofPoint& p0, const ofPoint& p1) {
	//    //Bresenham's algorithm to get color @ pixel
	//
	////    int x0 = int(p0.x);
	////    int x1 = int(p1.x);
	////    int y0 = int(p0.y);
	////    int y1 = int(p1.y);
	////
	////    int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
	////    int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1;
	////    int err = (dx>dy ? dx : -dy)/2;
	////    int e2;
	////
	////    for (;;) {
	////        if (x0 >= 0 && x0 < pixels.width &&
	////            y0 >= 0 && y0 < pixels.height &&
	////            x1 >= 0 && x1 < width &&
	////            y1 >= 0 && y1 < height) {
	////            // only add it if it is in the pixel w/height
	////            pix[numPix] = pixels[y0*width+x0];
	////            numPix++;
	////        }
	////
	////        // make sure we have enough room to store it
	////        if (numPix < pix.length) {
	////            if (x0==x1 && y0==y1) break;
	////            e2 = err;
	////            if (e2 >-dx) {
	////                err -= dy;
	////                x0 += sx;
	////            }
	////            if (e2 < dy) {
	////                err += dx;
	////                y0 += sy;
	////            }
	////        }
	////        else {
	////            println("Pix array, exceeded the maximum number of pixels allocated.");
	////            break;
	////        }
	////    }
	////
	////    //updatePixels(); // no need for this
	//
	//}

};
