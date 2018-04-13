/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "CustomLaf.h"

//==============================================================================
/**
*/
class BabySynthAudioProcessorEditor  : public AudioProcessorEditor,
    private Button::Listener, private Slider::Listener
{
public:
    BabySynthAudioProcessorEditor (BabySynthAudioProcessor&);
    ~BabySynthAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
    void buttonClicked (Button* button) override;
    void sliderValueChanged (Slider* slider) override;

private:
    MidiKeyboardComponent mKeyboardComponent;
    
    Image bkImg;
    Image waveImg1[6];
    Image waveImg2[6];
    int currWaveIdx1 = 0;
    int currWaveIdx2 = 0;
    
    Image filterMode[3];
    int filterModeIdx = 0;
    
    CustomLaf laf;
    
    Slider mOsc1;
    Slider mOsc2;
    
    Slider mAttackKnob;
    Slider mDecayKnob;
    Slider mSustainKnob;
    Slider mReleaseKnob;
    
    Slider mFilterModeKnob;
    Slider mFilterCutOffKnob;
    Slider mFilterResonance;
    
    OscillatorMode waveSelector(int val);
    
    OscillatorMode oscModeArr[kNumOscModes] = { OSCILLATOR_MODE_OFF,
                                                OSCILLATOR_MODE_SINE,
                                                OSCILLATOR_MODE_SAW,
                                                OSCILLATOR_MODE_TRIANGLE,
                                                OSCILLATOR_MODE_SQUARE,
                                                OSCILLATOR_MODE_LFO_SAW };
    
    FilterMode filtModeArr[kNumFilterModes] = { FILTER_MODE_LOWPASS,
                                                FILTER_MODE_HIGHPASS,
                                                FILTER_MODE_BANDPASS };
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    BabySynthAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BabySynthAudioProcessorEditor)
};
