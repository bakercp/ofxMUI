//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier: MIT
//


#pragma once


#include <cmath>
#include <limits>
#include <algorithm>


namespace ofx {
namespace MUI {


class Math
{
public:
    static double lerp(double inputValue,
                       double inputMin,
                       double inputMax,
                       double outputMin,
                       double outputMax,
                       bool clampOutput = false)
    {
        if (std::fabs(inputMin - inputMax) < std::numeric_limits<double>::epsilon())
        {
            return outputMin;
        }
        else
        {
            double outputValue = ((inputValue - inputMin) / (inputMax - inputMin) * (outputMax - outputMin) + outputMin);

            if (clampOutput)
            {
                return clamp(outputValue, outputMin, outputMax);
            }
            else
            {
                return outputValue;
            }
        }
    }


    template <typename Type>
    static Type clamp(const Type& inputValue, const Type& inputMin, const Type& inputMax)
    {
        return std::max(inputMin, std::min(inputValue, inputMax));
    }

};


} } // ofx::MUI
