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

inline double custom_poly_blep(double t, double increment)
{

    double A = 0.95291360332021;
    double B = 2.00719985138105;
    double C = 1.0433842440854399;
    
    /*
    double A {1.02267292072765};
    double B {2.0091348555451};
    double C {0.977410992026602}; */
    
    double dt = increment / (2.0 * double_Pi);
    // 0 <= t < 1
    if (t < dt) {
        t /= dt;
        return B*t - A*t*t - C;
    }
    // -1 < t < 0
    else if (t > 1.0 - dt) {
        t = (t - 1.0) / dt;
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
