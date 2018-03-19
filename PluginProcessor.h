/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Oscillator.h"

//==============================================================================
/**
*/
class BabySynthAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    BabySynthAudioProcessor();
    ~BabySynthAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    MidiKeyboardState& getKeyboardState();
    
    void osc_1_Mode_Changed(OscillatorMode oscMode);
    void ADSRchanged(double attack, double decay, double sustain, double release);
    void filterChanged(FilterMode filterMode, double cutoff, double resonance);
    void osc_2_Mode_Changed(OscillatorMode oscMode);

private:
    const static int MAX_VOICES = 8;
    MidiKeyboardState mKeyboardState;
    OscillatorVoice *mOsc_1_Voices[MAX_VOICES];
    OscillatorVoice *mOsc_2_Voices[MAX_VOICES];
    Synthesiser mSynth1;
    Synthesiser mSynth2;
    
    void osc_1_Mode_ChangedHelper(OscillatorMode oscMode);
    void osc_2_Mode_ChangedHelper(OscillatorMode oscMode);
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BabySynthAudioProcessor)
};
