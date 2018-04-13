/*
  ==============================================================================

    CustomLaf.h
    Created: 11 Apr 2018 12:05:23pm
    Author:  Menglee Guy

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class CustomLaf : public LookAndFeel_V4
{
public:
    CustomLaf()
    {
        setColour (Slider::textBoxBackgroundColourId, Colours::black);
    }
    
    void drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPos,
                           const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider) override
    {
        auto radius = jmin (width / 2, height / 2) - 4.0f;
        auto centreX = x + width  * 0.5f;
        auto centreY = y + height * 0.5f;
        auto rx = centreX - radius;
        auto ry = centreY - radius;
        auto rw = radius * 2.0f;
        auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
        
        // fill
        g.setColour (Colours::navy);
        g.fillEllipse (rx, ry, rw, rw);
        // outline
        g.setColour (Colours::black);
        g.drawEllipse (rx, ry, rw, rw, 2.0f);
        
        Path p;
        auto pointerLength = radius * 0.15f;
        auto pointerThickness = 5.0f;
        //p.addRectangle (-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
        p.addEllipse (-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
        p.applyTransform (AffineTransform::rotation (angle).translated (centreX, centreY));
        
        // pointer
        g.setColour (Colours::whitesmoke);
        g.fillPath (p);
    }
};
