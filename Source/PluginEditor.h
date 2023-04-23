/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class CircularBufferAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                            public juce::Slider::Listener
{
public:
    CircularBufferAudioProcessorEditor (CircularBufferAudioProcessor&);
    ~CircularBufferAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void sliderValueChanged(juce::Slider *slider) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    CircularBufferAudioProcessor& audioProcessor;
    juce::Slider gainSlider;
    juce::Label gainLabel;

    juce::Slider delayTimeSlider;
    juce::Label timeLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CircularBufferAudioProcessorEditor)
};
