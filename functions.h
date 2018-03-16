/*
  ==============================================================================

    functions.h
    Created: 15 Mar 2018 5:04:38pm
    Author:  Menglee Guy

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
//#include "tables.h"

inline double poly_blep(double t, double increment)
{
    double dt = increment / (2.0 * double_Pi);
    // 0 <= t < 1
    if (t < dt) {
        t /= dt;
        return t+t - t*t - 1.0;
    }
    // -1 < t < 0
    else if (t > 1.0 - dt) {
        t = (t - 1.0) / dt;
        return t*t + t+t + 1.0;
    }
    // 0 otherwise
    else return 0.0;
}

inline double doPolyBLEP(double currentAngle, double increment)
{
    double naive_saw = currentAngle / double_Pi - 1.0;
    double t = currentAngle / (2.0 * double_Pi);
    return naive_saw - poly_blep(t, increment);
}

inline double custom_poly_blep(double t, double increment)      // hardcoding coefficients
{
    double A = 0.976456801660105;
    double B = 2.007199851381053;
    double C = 1.021692122042724;
    double D = 1.0;
    double E = 2.0;
    double F = 1.0;
    
    double dt = increment / (2.0 * double_Pi);
    // 0 <= t < 1
    if (t < dt) {
        t /= dt;
        //return A*t*t*t*t*t - B*t*t*t*t + C*t*t*t - D*t*t + E*t - F;     //7k aliased
        return B*t - A*t*t - C;
    }
    // -1 < t < 0
    else if (t > 1.0 - dt) {
        t = (t - 1.0) / dt;
        //return A*t*t*t*t*t + B*t*t*t*t + C*t*t*t + D*t*t + E*t + F;
        return A*t*t + B*t + C;
    }
    // 0 otherwise
    else return 0.0;
}

inline double doCustomPolyBLEP(double currentAngle, double increment)
{
    double naive_saw = currentAngle / double_Pi - 1.0;
    double t = currentAngle / (2.0 * double_Pi);
    return naive_saw - custom_poly_blep(t, increment);
}
