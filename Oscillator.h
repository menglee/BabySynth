/*
  ==============================================================================

    Oscillator.h
    Created: 15 Mar 2018 5:03:58pm
    Author:  Menglee Guy

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "Envelope.h"
#include "Filter.h"
#include "functions.h"

enum OscillatorMode {
    OSCILLATOR_MODE_OFF,
    OSCILLATOR_MODE_SINE,
    OSCILLATOR_MODE_SAW,
    OSCILLATOR_MODE_TRIANGLE,
    OSCILLATOR_MODE_SQUARE,
    OSCILLATOR_MODE_LFO_SAW,
    
    kNumOscModes
};

class OscillatorSound : public SynthesiserSound
{
public:
    OscillatorSound() {}
    bool appliesToNote (int /*midiNoteNumber*/) override    { return true; }
    bool appliesToChannel (int /*midiChannel*/) override    { return true; }
};

class OscillatorVoice : public SynthesiserVoice
{
public:
    OscillatorVoice();
    bool canPlaySound (SynthesiserSound* sound) override;
    void startNote (int midiNoteNumber, float velocity, SynthesiserSound* /*sound*/,
                    int /*currentPitchWheelPosition*/) override;
    void stopNote (float /*velocity*/, bool allowTailOff) override;
    void pitchWheelMoved (int /*newValue*/) override;
    void controllerMoved (int /*controllerNumber*/, int /*newValue*/) override;
    void renderNextBlock (AudioSampleBuffer& outputBuffer, int startSample,
                          int numSamples) override;
    
    void updateOscMode(OscillatorMode oscMode);
    void updateADSR(double attack, double decay, double sustain, double release);
    void updateFilter(FilterMode filterMode, double cutOff, double resonance);
    
    void defaultValues();
    
private:
    double currentAngle;
    double angleDelta;
    double level;
    
    OscillatorMode mOscillatorMode;
    EnvelopeGenerator mEnvelopeGenerator;
    Filter mFilter;
    
    double twoPi;
    
    void incrementPhase();
};
