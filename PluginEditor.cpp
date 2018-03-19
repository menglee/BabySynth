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
    setSize (500, 350);
    addAndMakeVisible(&mKeyboardComponent);
    
    mOsc1.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    mOsc1.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 50, 20);
    mOsc1.setRange(0, 4, 1);
    mOsc1.addListener(this);
    addAndMakeVisible(&mOsc1);
    
    mOsc2.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    mOsc2.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 50, 20);
    mOsc2.setRange(0, 4, 1);
    mOsc2.addListener(this);
    addAndMakeVisible(&mOsc2);
    
    //--- ADSR
    mAttackKnob.setSliderStyle(Slider::LinearVertical);
    mAttackKnob.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 40, 20);
    mAttackKnob.setRange(0.001, 1.00, 0.001);
    mAttackKnob.setValue(0.01);
    mAttackKnob.addListener(this);
    addAndMakeVisible(&mAttackKnob);
    
    mDecayKnob.setSliderStyle(Slider::LinearVertical);
    mDecayKnob.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 40, 20);
    mDecayKnob.setRange(0.001, 5.00, 0.001);
    mDecayKnob.setValue(0.50);
    mDecayKnob.addListener(this);
    addAndMakeVisible(&mDecayKnob);
    
    mSustainKnob.setSliderStyle(Slider::LinearVertical);
    mSustainKnob.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 40, 20);
    mSustainKnob.setRange(0.01, 5.00, 0.01);
    mSustainKnob.setValue(0.10);
    mSustainKnob.addListener(this);
    addAndMakeVisible(&mSustainKnob);
    
    mReleaseKnob.setSliderStyle(Slider::LinearVertical);
    mReleaseKnob.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 40, 20);
    mReleaseKnob.setRange(0.01, 5.00, 0.01);
    mReleaseKnob.setValue(1.00);
    mReleaseKnob.addListener(this);
    addAndMakeVisible(&mReleaseKnob);
    //---
    
    //--- Filter
    mFilterModeKnob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    mFilterModeKnob.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 40, 20);
    mFilterModeKnob.setRange(0, 2, 1);
    mFilterModeKnob.setValue(0);
    mFilterModeKnob.addListener(this);
    addAndMakeVisible(&mFilterModeKnob);
    
    mFilterCutOffKnob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    mFilterCutOffKnob.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 40, 20);
    mFilterCutOffKnob.setRange(0.00, 0.99, 0.01);
    mFilterCutOffKnob.setValue(0.99);
    mFilterCutOffKnob.addListener(this);
    addAndMakeVisible(&mFilterCutOffKnob);
    
    mFilterResonance.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    mFilterResonance.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 40, 20);
    mFilterResonance.setRange(0.00, 1.00, 0.01);
    mFilterResonance.setValue(0.00);
    mFilterResonance.addListener(this);
    addAndMakeVisible(&mFilterResonance);
}

BabySynthAudioProcessorEditor::~BabySynthAudioProcessorEditor()
{
}

//==============================================================================
void BabySynthAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

void BabySynthAudioProcessorEditor::resized()
{
    int rotarySliderWidth = 100;
    int rotarySliderHeight = 100;
    int linearSliderWidth = 50;
    int linearSliderHeight = 100;
    
    Rectangle<int> rect (getLocalBounds());
    //rect.removeFromLeft(5);
    rect.removeFromTop(10);
    mOsc1.setBounds(rect.getX(), rect.getY(), rotarySliderWidth, rotarySliderHeight);
    
    //--- ADSR
    rect.removeFromLeft(rotarySliderWidth * 2);
    mAttackKnob.setBounds(rect.getX(), rect.getY(), linearSliderWidth, linearSliderHeight);
    
    rect.removeFromLeft(linearSliderWidth);
    mDecayKnob.setBounds(rect.getX(), rect.getY(), linearSliderWidth, linearSliderHeight);
    
    rect.removeFromLeft(linearSliderWidth);
    mSustainKnob.setBounds(rect.getX(), rect.getY(), linearSliderWidth, linearSliderHeight);
    
    rect.removeFromLeft(linearSliderWidth);
    mReleaseKnob.setBounds(rect.getX(), rect.getY(), linearSliderWidth, linearSliderHeight);
    //---
    
    Rectangle<int> rect2 (getLocalBounds());
    rect2.removeFromTop(rotarySliderHeight + 10);
    mOsc2.setBounds(rect2.getX(), rect2.getY(), rotarySliderWidth, rotarySliderHeight);
    
    rect2.removeFromLeft(rotarySliderWidth + linearSliderWidth);
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
        processor.osc_1_Mode_Changed(oscModeArr[(int)mOsc1.getValue()]);
    }
    
    if (slider == &mOsc2)
    {
        processor.osc_2_Mode_Changed(oscModeArr[(int)mOsc2.getValue()]);
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
