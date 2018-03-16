/*
  ==============================================================================

    Envelope.h
    Created: 15 Mar 2018 5:04:08pm
    Author:  Menglee Guy

  ==============================================================================
*/

#pragma once

#include <cmath>

enum EnvelopeStage {
    ENV_OFF = 0,
    ENV_SEGMENT_ATTACK,
    ENV_SEGMENT_DECAY,
    ENV_SEGMENT_SUSTAIN,
    ENV_SEGMENT_RELEASE,
    ENV_SEGMENT_TOTAL
};

class EnvelopeGenerator {
public:
    EnvelopeGenerator();
    
    void enterStage(EnvelopeStage newStage);
    double nextSample();
    EnvelopeStage getCurrentStage() const;
    void setADSR(double attack, double decay, double sustain, double release);
    void resetDefaults();
    
private:
    EnvelopeStage currentStage;
    const double minimumLevel = 0.001;
    double sampleRate = 44100.0;
    double currentLevel;
    double multiplier;
    double stageValue[ENV_SEGMENT_TOTAL];
    unsigned long long currentSampleIndex;
    unsigned long long nextStageSampleIndex;
    
    void calculateMultiplier(double startLevel, double endLevel, unsigned long long lengthInSamples);
};
