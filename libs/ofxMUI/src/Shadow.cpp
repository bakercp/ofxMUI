//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofx/MUI/Shadow.h"
#include "ofGraphics.h"
#include "ofVectorMath.h"


namespace ofx {
namespace MUI {


void Shadow::draw(const ofRectangle& rect,
                  float windowWidth,
                  float windowHeight,
                  float angleDeg,
                  float distancePx,
                  float spreadPct,
                  float sizePx,
                  const ofFloatColor& color,
                  float cornerRadius,
                  bool inset)
{
//    (180 - $angle) * pi() / 180;
    
    float angleRad = (180 - angleDeg) * glm::pi<float>() / 180;// / 180; glm::radians<float>(angleDeg);
    
    float offsetX = distancePx * cos(angleRad);
    float offsetY = distancePx * sin(angleRad);

    float spreadRadius = sizePx * spreadPct / 100.0;
    float blurRadius = sizePx - spreadRadius;

    
    std::cout << "offsetX: " << offsetX << std::endl;
    std::cout << "offsetY: " << offsetY << std::endl;
    std::cout << "angleRad: " << angleRad << std::endl;
    std::cout << "distancePx: " << distancePx << std::endl;
    std::cout << "spreadPct: " << spreadPct << std::endl;
    std::cout << "sizePx: " << sizePx << std::endl;

//    blurRadius *= 100;
    
    Shadow::draw(rect,
                 windowWidth,
                 windowHeight,
                 offsetX,
                 offsetY,
                 blurRadius,
                 spreadRadius,
                 ofColor(color),
                 cornerRadius,
                 inset);
}


    
    
void Shadow::draw(const ofRectangle& rect,
                  float windowWidth,
                  float windowHeight,
                  float horizontalOffset,
                  float verticalOffset,
                  float blurRadius,
                  float spreadRadius,
                  const ofColor& color,
                  float cornerRadius,
                  bool inset)
{
    ofFloatColor c(color);
    
    ofRectangle _rect = rect;
    _rect.setFromCenter(_rect.getCenter().x + horizontalOffset,
                        _rect.getCenter().y + verticalOffset,
                        _rect.getWidth()    + spreadRadius,
                        _rect.getHeight()   + spreadRadius);
    
    ofShader* shader = cornerRadius > 0 ? &instance().shaderRoundedBoxShadow : &instance().shaderBoxShadow;
    
    shader->begin();
    shader->setUniform4f("box", _rect.getMinX(), _rect.getMinY(), _rect.getMaxX(), _rect.getMaxY());
    shader->setUniform4f("color", c.r, c.g, c.b, c.a);
    shader->setUniform1f("blurRadius", blurRadius);
    shader->setUniform2f("window", windowWidth, windowHeight);
    
    shader->setUniform1f("corner", cornerRadius);

    
    ofFill();
    ofDrawRectangle(0, 0, 1, 1);
    shader->end();
}

Shadow& Shadow::instance()
{
    static Shadow shadow;
    return shadow;
}

    
Shadow::Shadow()
{
    
    shaderBoxShadow.load("boxShadow");
    shaderRoundedBoxShadow.load("roundedBoxShadow");
}

Shadow::~Shadow()
{
    
}

    
} } // namespace ofx::MUI



