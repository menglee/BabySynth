/*
  ==============================================================================

    Envelope.cpp
    Created: 15 Mar 2018 5:04:08pm
    Author:  Menglee Guy

  ==============================================================================
*/

#include "Envelope.h"
#include <iostream>

EnvelopeGenerator::EnvelopeGenerator()
{
    currentStage = ENV_OFF;
    currentLevel = minimumLevel;
    multiplier = 1.0;
    currentSampleIndex = 0;
    nextStageSampleIndex = 0;
    
    resetDefaults();
}

EnvelopeStage EnvelopeGenerator::getCurrentStage() const
{
    return currentStage;
}

void EnvelopeGenerator::enterStage(EnvelopeStage newStage)
{
    currentStage = newStage;
    currentSampleIndex = 0;
    if (currentStage == ENV_OFF ||
        currentStage == ENV_SEGMENT_SUSTAIN) {
        nextStageSampleIndex = 0;
    } else {
        nextStageSampleIndex = stageValue[currentStage] * sampleRate;
    }
    switch (newStage) {
        case ENV_OFF:
            currentLevel = 0.0;
            multiplier = 1.0;
            break;
        case ENV_SEGMENT_ATTACK:
            currentLevel = minimumLevel;
            calculateMultiplier(currentLevel, 1.0, nextStageSampleIndex);
            break;
        case ENV_SEGMENT_DECAY:
            currentLevel = 1.0;
            calculateMultiplier(currentLevel, fmax(stageValue[ENV_SEGMENT_SUSTAIN], minimumLevel), nextStageSampleIndex);
            break;
        case ENV_SEGMENT_SUSTAIN:
            currentLevel = stageValue[ENV_SEGMENT_SUSTAIN];
            multiplier = 1.0;
            break;
        case ENV_SEGMENT_RELEASE:
            calculateMultiplier(currentLevel, minimumLevel, nextStageSampleIndex);
            break;
        default:
            break;
    }
}

double EnvelopeGenerator::nextSample()
{
    if (currentStage != ENV_OFF &&
        currentStage != ENV_SEGMENT_SUSTAIN) {
        if (currentSampleIndex == nextStageSampleIndex) {
            EnvelopeStage newStage = static_cast<EnvelopeStage>((currentStage + 1) % ENV_SEGMENT_TOTAL);
            enterStage(newStage);
        }
        currentLevel *= multiplier;
        currentSampleIndex++;
    }
    return currentLevel;
}

void EnvelopeGenerator::calculateMultiplier(double startLevel, double endLevel, unsigned long long lengthInSamples)
{
    multiplier = 1.0 + (log(endLevel) - log(startLevel)) / (lengthInSamples);
}

void EnvelopeGenerator::setADSR(double attack, double decay, double sustain, double release)
{
    stageValue[ENV_OFF] = 0.0;
    stageValue[ENV_SEGMENT_ATTACK] = attack;
    stageValue[ENV_SEGMENT_DECAY] = decay;
    stageValue[ENV_SEGMENT_SUSTAIN] = sustain;
    stageValue[ENV_SEGMENT_RELEASE] = release;
}

void EnvelopeGenerator::resetDefaults()
{
    stageValue[ENV_OFF] = 0.0;
    stageValue[ENV_SEGMENT_ATTACK] = 0.01;
    stageValue[ENV_SEGMENT_DECAY] = 0.50;
    stageValue[ENV_SEGMENT_SUSTAIN] = 0.10;
    stageValue[ENV_SEGMENT_RELEASE] = 1.0;
    // need to sync with gui
}
