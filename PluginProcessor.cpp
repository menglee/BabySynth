/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
BabySynthAudioProcessor::BabySynthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

BabySynthAudioProcessor::~BabySynthAudioProcessor()
{
}

//==============================================================================
const String BabySynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool BabySynthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool BabySynthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool BabySynthAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double BabySynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int BabySynthAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int BabySynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void BabySynthAudioProcessor::setCurrentProgram (int index)
{
}

const String BabySynthAudioProcessor::getProgramName (int index)
{
    return {};
}

void BabySynthAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void BabySynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    mSynth1.setCurrentPlaybackSampleRate(sampleRate);
    mSynth2.setCurrentPlaybackSampleRate(sampleRate);
    mKeyboardState.reset();
    
    //--- test
    for (int i = 0; i < MAX_VOICES; i++)
    {
        mOsc_1_Voices[i] = new OscillatorVoice();
        mOsc_1_Voices[i]->defaultValues();
        mSynth1.addVoice(mOsc_1_Voices[i]);
        
        mOsc_2_Voices[i] = new OscillatorVoice();
        mOsc_2_Voices[i]->defaultValues();
        mSynth2.addVoice(mOsc_2_Voices[i]);
    }
    mSynth1.addSound(new OscillatorSound());
    mSynth2.addSound(new OscillatorSound());
}

void BabySynthAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
    mKeyboardState.reset();
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool BabySynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void BabySynthAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    const int numSamples = buffer.getNumSamples();
    mKeyboardState.processNextMidiBuffer(midiMessages, 0, numSamples, true);
    mSynth1.renderNextBlock(buffer, midiMessages, 0, numSamples);
    mSynth2.renderNextBlock(buffer, midiMessages, 0, numSamples);
}

void BabySynthAudioProcessor::osc_1_Mode_Changed(OscillatorMode oscMode)   //need to handle 2 osc
{
    switch (oscMode)
    {
        case OSCILLATOR_MODE_OFF:
            osc_1_Mode_ChangedHelper(OSCILLATOR_MODE_OFF);
            break;
        case OSCILLATOR_MODE_SINE:
            osc_1_Mode_ChangedHelper(OSCILLATOR_MODE_SINE);
            break;
        case OSCILLATOR_MODE_SAW:
            osc_1_Mode_ChangedHelper(OSCILLATOR_MODE_SAW);
            break;
        case OSCILLATOR_MODE_TRIANGLE:
            osc_1_Mode_ChangedHelper(OSCILLATOR_MODE_TRIANGLE);
            break;
        case OSCILLATOR_MODE_SQUARE:
            osc_1_Mode_ChangedHelper(OSCILLATOR_MODE_SQUARE);
            break;
        default:
            break;
    }
}

void BabySynthAudioProcessor::osc_2_Mode_Changed(OscillatorMode oscMode)
{
    switch (oscMode)
    {
        case OSCILLATOR_MODE_OFF:
            osc_2_Mode_ChangedHelper(OSCILLATOR_MODE_OFF);
            break;
        case OSCILLATOR_MODE_SINE:
            osc_2_Mode_ChangedHelper(OSCILLATOR_MODE_SINE);
            break;
        case OSCILLATOR_MODE_SAW:
            osc_2_Mode_ChangedHelper(OSCILLATOR_MODE_SAW);
            break;
        case OSCILLATOR_MODE_TRIANGLE:
            osc_2_Mode_ChangedHelper(OSCILLATOR_MODE_TRIANGLE);
            break;
        case OSCILLATOR_MODE_SQUARE:
            osc_2_Mode_ChangedHelper(OSCILLATOR_MODE_SQUARE);
            break;
        default:
            break;
    }
}

void BabySynthAudioProcessor::ADSRchanged(double attack, double decay, double sustain, double release)     // temporarily handles both osc
{
    for(int i = 0; i < MAX_VOICES; ++i)
    {
        mOsc_1_Voices[i]->updateADSR(attack, decay, sustain, release);
        
        mOsc_2_Voices[i]->updateADSR(attack, decay, sustain, release);
    }
}

void BabySynthAudioProcessor::filterChanged(FilterMode filterMode, double cutoff, double resonance)
{
    for(int i = 0; i < MAX_VOICES; ++i)
    {
        mOsc_1_Voices[i]->updateFilter(filterMode, cutoff, resonance);
        
        mOsc_2_Voices[i]->updateFilter(filterMode, cutoff, resonance);
    }
}

void BabySynthAudioProcessor::osc_1_Mode_ChangedHelper(OscillatorMode oscMode)
{
    for (int i = 0; i < MAX_VOICES; ++i)
    {
        mOsc_1_Voices[i]->updateOscMode(oscMode);
    }
}

void BabySynthAudioProcessor::osc_2_Mode_ChangedHelper(OscillatorMode oscMode)
{
    for (int i = 0; i < MAX_VOICES; ++i)
        mOsc_2_Voices[i]->updateOscMode(oscMode);
}

MidiKeyboardState& BabySynthAudioProcessor::getKeyboardState()
{
    return mKeyboardState;
}

//==============================================================================
bool BabySynthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* BabySynthAudioProcessor::createEditor()
{
    return new BabySynthAudioProcessorEditor (*this);
}

//==============================================================================
void BabySynthAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void BabySynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new BabySynthAudioProcessor();
}
