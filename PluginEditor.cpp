/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
BabySynthAudioProcessorEditor::BabySynthAudioProcessorEditor (BabySynthAudioProcessor& p)
: AudioProcessorEditor (&p), mKeyboardComponent(p.getKeyboardState(), MidiKeyboardComponent::horizontalKeyboard) , processor (p)
{
    setSize (600, 400);
    bkImg = ImageFileFormat::loadFrom(File("~/JUCE/projects/SynthResources/Skin.png"));
    waveImg1[0] = ImageFileFormat::loadFrom(File("~/JUCE/projects/SynthResources/WaveOff.png"));
    waveImg1[1] = ImageFileFormat::loadFrom(File("~/JUCE/projects/SynthResources/WaveSine.png"));
    waveImg1[2] = ImageFileFormat::loadFrom(File("~/JUCE/projects/SynthResources/WaveSaw.png"));
    waveImg1[3] = ImageFileFormat::loadFrom(File("~/JUCE/projects/SynthResources/WaveTri.png"));
    waveImg1[4] = ImageFileFormat::loadFrom(File("~/JUCE/projects/SynthResources/WaveSqu.png"));
    waveImg1[5] = ImageFileFormat::loadFrom(File("~/JUCE/projects/SynthResources/WaveLfoSaw.png"));
    
    waveImg2[0] = ImageFileFormat::loadFrom(File("~/JUCE/projects/SynthResources/WaveOff.png"));
    waveImg2[1] = ImageFileFormat::loadFrom(File("~/JUCE/projects/SynthResources/WaveSine.png"));
    waveImg2[2] = ImageFileFormat::loadFrom(File("~/JUCE/projects/SynthResources/WaveSaw.png"));
    waveImg2[3] = ImageFileFormat::loadFrom(File("~/JUCE/projects/SynthResources/WaveTri.png"));
    waveImg2[4] = ImageFileFormat::loadFrom(File("~/JUCE/projects/SynthResources/WaveSqu.png"));
    waveImg2[5] = ImageFileFormat::loadFrom(File("~/JUCE/projects/SynthResources/WaveLfoSaw.png"));
    
    addAndMakeVisible(&mKeyboardComponent);
    
    // --- OSC
    mOsc1.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    mOsc1.setTextBoxStyle(juce::Slider::NoTextBox, false, 50, 20);
    mOsc1.setRange(0, 5, 1);
    mOsc1.addListener(this);
    mOsc1.setLookAndFeel(&laf);
    addAndMakeVisible(&mOsc1);
    
    mOsc2.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    mOsc2.setTextBoxStyle(juce::Slider::NoTextBox, false, 50, 20);
    mOsc2.setRange(0, 5, 1);
    mOsc2.addListener(this);
    mOsc2.setLookAndFeel(&laf);
    addAndMakeVisible(&mOsc2);
    // ---
    
    // --- ADSR
    mAttackKnob.setSliderStyle(Slider::LinearVertical);
    mAttackKnob.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 40, 20);
    mAttackKnob.setRange(0.001, 1.00, 0.001);
    mAttackKnob.setValue(0.01);
    mAttackKnob.addListener(this);
    mAttackKnob.setLookAndFeel(&laf);
    addAndMakeVisible(&mAttackKnob);
    
    mDecayKnob.setSliderStyle(Slider::LinearVertical);
    mDecayKnob.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 40, 20);
    mDecayKnob.setRange(0.001, 5.00, 0.001);
    mDecayKnob.setValue(0.50);
    mDecayKnob.addListener(this);
    mDecayKnob.setLookAndFeel(&laf);
    addAndMakeVisible(&mDecayKnob);
    
    mSustainKnob.setSliderStyle(Slider::LinearVertical);
    mSustainKnob.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 40, 20);
    mSustainKnob.setRange(0.01, 5.00, 0.01);
    mSustainKnob.setValue(0.10);
    mSustainKnob.addListener(this);
    mSustainKnob.setLookAndFeel(&laf);
    addAndMakeVisible(&mSustainKnob);
    
    mReleaseKnob.setSliderStyle(Slider::LinearVertical);
    mReleaseKnob.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 40, 20);
    mReleaseKnob.setRange(0.01, 5.00, 0.01);
    mReleaseKnob.setValue(1.00);
    mReleaseKnob.addListener(this);
    mReleaseKnob.setLookAndFeel(&laf);
    addAndMakeVisible(&mReleaseKnob);
    // ---
    
    // --- Filter
    mFilterModeKnob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    mFilterModeKnob.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 40, 20);
    mFilterModeKnob.setRange(0, 2, 1);
    mFilterModeKnob.setValue(0);
    mFilterModeKnob.addListener(this);
    mFilterModeKnob.setLookAndFeel(&laf);
    addAndMakeVisible(&mFilterModeKnob);
    
    mFilterCutOffKnob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    mFilterCutOffKnob.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 40, 20);
    mFilterCutOffKnob.setRange(0.00, 0.99, 0.01);
    mFilterCutOffKnob.setValue(0.99);
    mFilterCutOffKnob.addListener(this);
    mFilterCutOffKnob.setLookAndFeel(&laf);
    addAndMakeVisible(&mFilterCutOffKnob);
    
    mFilterResonance.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    mFilterResonance.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 40, 20);
    mFilterResonance.setRange(0.00, 1.00, 0.01);
    mFilterResonance.setValue(0.00);
    mFilterResonance.addListener(this);
    mFilterResonance.setLookAndFeel(&laf);
    addAndMakeVisible(&mFilterResonance);
}

BabySynthAudioProcessorEditor::~BabySynthAudioProcessorEditor()
{
}

//==============================================================================
void BabySynthAudioProcessorEditor::paint (Graphics& g)
{
    g.drawImage(bkImg, 0, 0, getWidth(), getHeight(), 0, 0, bkImg.getWidth(), bkImg.getHeight(), false);
    g.drawImage(waveImg1[currWaveIdx1], 130, 40, waveImg1[currWaveIdx1].getWidth(), waveImg1[currWaveIdx1].getHeight(), 0, 0,
                waveImg1[currWaveIdx1].getWidth(), waveImg1[currWaveIdx1].getHeight());
    g.drawImage(waveImg2[currWaveIdx2], 130, 185, waveImg2[currWaveIdx2].getWidth(), waveImg2[currWaveIdx2].getHeight(), 0, 0,
                waveImg2[currWaveIdx2].getWidth(), waveImg2[currWaveIdx2].getHeight());
}

void BabySynthAudioProcessorEditor::resized()
{
    int rotarySliderWidth = 85;
    int rotarySliderHeight = 85;
    int linearSliderWidth = 75;
    int linearSliderHeight = 100;
    
    int leftSidePadding = 35;
    
    Rectangle<int> rect (getLocalBounds());
    rect.removeFromLeft(leftSidePadding);
    rect.removeFromTop(50);
    mOsc1.setBounds(rect.getX(), rect.getY(), rotarySliderWidth, rotarySliderHeight);
    
    //--- ADSR
    rect.removeFromLeft(rotarySliderWidth * 2 + 65);
    mAttackKnob.setBounds(rect.getX(), rect.getY(), linearSliderWidth, linearSliderHeight);
    
    rect.removeFromLeft(linearSliderWidth);
    mDecayKnob.setBounds(rect.getX(), rect.getY(), linearSliderWidth, linearSliderHeight);
    
    rect.removeFromLeft(linearSliderWidth);
    mSustainKnob.setBounds(rect.getX(), rect.getY(), linearSliderWidth, linearSliderHeight);
    
    rect.removeFromLeft(linearSliderWidth);
    mReleaseKnob.setBounds(rect.getX(), rect.getY(), linearSliderWidth, linearSliderHeight);
    //---
    
    Rectangle<int> rect2 (getLocalBounds());
    rect2.removeFromTop(rotarySliderHeight * 2 + 25);
    rect2.removeFromLeft(leftSidePadding);
    mOsc2.setBounds(rect2.getX(), rect2.getY(), rotarySliderWidth, rotarySliderHeight);
    
    rect2.removeFromLeft(rotarySliderWidth * 3);
    mFilterModeKnob.setBounds(rect2.getX(), rect2.getY(), rotarySliderWidth, rotarySliderHeight);
    
    rect2.removeFromLeft(rotarySliderWidth);
    mFilterCutOffKnob.setBounds(rect2.getX(), rect2.getY(), rotarySliderWidth, rotarySliderHeight);
    
    rect2.removeFromLeft(rotarySliderWidth);
    mFilterResonance.setBounds(rect2.getX(), rect2.getY(), rotarySliderWidth, rotarySliderHeight);
    
    Rectangle<int> r (getLocalBounds().reduced(8));
    mKeyboardComponent.setBounds(r.removeFromBottom(70));
}

void BabySynthAudioProcessorEditor::buttonClicked (Button* button)
{
    
}

void BabySynthAudioProcessorEditor::sliderValueChanged (Slider* slider)
{
    if (slider == &mOsc1)
    {
        currWaveIdx1 = (int)mOsc1.getValue();
        repaint();
        processor.osc_1_Mode_Changed(oscModeArr[currWaveIdx1]);
    }
    
    if (slider == &mOsc2)
    {
        currWaveIdx2 = (int)mOsc2.getValue();
        repaint();
        processor.osc_2_Mode_Changed(oscModeArr[currWaveIdx2]);
    }
    
    if (slider == &mAttackKnob || slider == &mDecayKnob ||
        slider == &mSustainKnob || slider == &mReleaseKnob)
    {
        processor.ADSRchanged(mAttackKnob.getValue(),
                              mDecayKnob.getValue(),
                              mSustainKnob.getValue(),
                              mReleaseKnob.getValue());
    }
    
    if (slider == &mFilterModeKnob || slider == &mFilterCutOffKnob ||
        slider == &mFilterResonance)
    {
        processor.filterChanged(filtModeArr[(int)mFilterModeKnob.getValue()],
                                mFilterCutOffKnob.getValue(), mFilterResonance.getValue());
    }
}

OscillatorMode BabySynthAudioProcessorEditor::waveSelector(int val)
{
    return oscModeArr[val];
}
