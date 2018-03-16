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
    setSize (400, 300);
    addAndMakeVisible(&mKeyboardComponent);
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
    Rectangle<int> r (getLocalBounds().reduced(8));
    mKeyboardComponent.setBounds(r.removeFromBottom(70));
}
