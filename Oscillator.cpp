/*
  ==============================================================================

    Oscillator.cpp
    Created: 15 Mar 2018 5:03:58pm
    Author:  Menglee Guy

  ==============================================================================
*/

#include "Oscillator.h"

OscillatorVoice::OscillatorVoice()
{
    currentAngle = 0.0;
    angleDelta = 0.0;
    level = 0.0;
    
    twoPi = 2.0 * double_Pi;
}

bool OscillatorVoice::canPlaySound (SynthesiserSound* sound)
{
    return dynamic_cast<OscillatorSound*>(sound) != nullptr;
}

void OscillatorVoice::startNote (int midiNoteNumber, float velocity, SynthesiserSound* /*sound*/,
                                 int /*currentPitchWheelPosition*/)
{
    currentAngle = 0.0;
    level = velocity * 0.15;
    
    double frequency = MidiMessage::getMidiNoteInHertz (midiNoteNumber);
    double cyclesPerSample = frequency / getSampleRate();
    
    angleDelta = cyclesPerSample * twoPi;       // f*2*pi / fs
    
    mEnvelopeGenerator.enterStage(ENV_SEGMENT_ATTACK);
}

void OscillatorVoice::stopNote (float /*velocity*/, bool allowTailOff)
{
    mEnvelopeGenerator.enterStage(ENV_SEGMENT_RELEASE);
}

void OscillatorVoice::pitchWheelMoved (int /*newValue*/)
{
    
}

void OscillatorVoice::controllerMoved (int /*controllerNumber*/, int /*newValue*/)
{
    
}

void OscillatorVoice::renderNextBlock (AudioSampleBuffer& outputBuffer, int startSample, int numSamples)
{
    if (angleDelta != 0.0)
    {
        while (--numSamples >= 0)
        {
            float currentSample = 0.0f;
            switch (mOscillatorMode)
            {
                case OSCILLATOR_MODE_OFF:
                    
                    break;
                case OSCILLATOR_MODE_SINE:
                    currentSample = (float) (sin (currentAngle)) * level * mEnvelopeGenerator.nextSample();
                    break;
                case OSCILLATOR_MODE_SAW:
                    //currentSample = (float) mFilter.process(((currentAngle / double_Pi - 1.0)) * level * mEnvelopeGenerator.nextSample());
                    currentSample = (float)mFilter.process(doCustomPolyBLEP(currentAngle, angleDelta) * level * mEnvelopeGenerator.nextSample());
                    break;
                case OSCILLATOR_MODE_TRIANGLE:
                {
                    double triValue = -1.0 + (2.0 * currentAngle / twoPi);
                    currentSample = (float) mFilter.process((2.0 * (fabs(triValue) - 0.5)) * level * mEnvelopeGenerator.nextSample());
                    break;
                }
                case OSCILLATOR_MODE_SQUARE:
                {
                    double squareValue = 0.0;
                    if (currentAngle <= double_Pi)
                        squareValue = 1.0;
                    else
                        squareValue = -1.0;
                    
                    currentSample = (float) mFilter.process(squareValue * level * mEnvelopeGenerator.nextSample());
                    break;
                }
                default:
                    break;
            }
            
            for (int i = outputBuffer.getNumChannels(); --i >= 0;)
                outputBuffer.addSample(i, startSample, currentSample);
            
            incrementPhase();
            ++startSample;
            
            if(mEnvelopeGenerator.getCurrentStage() == ENV_OFF)
            {
                clearCurrentNote();
                angleDelta = 0.0;
                break;
            }
        }
    }
}

void OscillatorVoice::incrementPhase()
{
    if (mOscillatorMode == OSCILLATOR_MODE_SINE)
    {
        currentAngle += angleDelta;
    }
    else
    {
        if ((currentAngle += angleDelta) >= twoPi)
            currentAngle -= twoPi;
    }
}

void OscillatorVoice::updateOscMode(OscillatorMode oscMode)
{
    mOscillatorMode = oscMode;
}

void OscillatorVoice::updateADSR(double attack, double decay, double sustain, double release)
{
    mEnvelopeGenerator.setADSR(attack, decay, sustain, release);
}

void OscillatorVoice::updateFilter(FilterMode filterMode, double cutOff, double resonance)
{
    mFilter.setFilterMode(filterMode);
    mFilter.setCutoff(cutOff);
    mFilter.setResonance(resonance);
}

void OscillatorVoice::defaultValues()
{
    mOscillatorMode = OSCILLATOR_MODE_OFF;
    
    mEnvelopeGenerator.setADSR(0.01, 0.50, 0.10, 1.00);
}
