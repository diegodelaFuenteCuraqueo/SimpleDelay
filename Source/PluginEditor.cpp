/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

using namespace juce;

//==============================================================================
CircularBufferAudioProcessorEditor::CircularBufferAudioProcessorEditor (CircularBufferAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (350, 200);

    //gainSlider gui params ----------------------------------------------------
    gainSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    gainSlider.setTextBoxStyle(Slider::TextBoxLeft, false, 50, 20);
    gainSlider.setRange(0.0f, 1.0f);
    gainSlider.setValue(1.0f);
    gainSlider.addListener(this);
    addAndMakeVisible(gainSlider);

    //gainSlider label gui params ----------------------------------------------
    gainLabel.setText ("Delay gain", dontSendNotification);
    //gainLabel.attachToComponent (&gainSlider, true);
    gainLabel.setJustificationType (Justification::right);
    gainLabel.setColour (TextEditor::textColourId, Colours::white);
    gainLabel.setColour (Label::backgroundColourId, Colours::darkslateblue);
    addAndMakeVisible (gainLabel);

    //delayTimeSlider gui params ----------------------------------------------
    delayTimeSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    delayTimeSlider.setTextBoxStyle(Slider::TextBoxLeft, false, 50, 20);
    delayTimeSlider.setRange(1.0f, 3000.0f);
    delayTimeSlider.setValue(1000);
    delayTimeSlider.addListener(this);
    addAndMakeVisible(delayTimeSlider);

    //timeLabel label gui params ----------------------------------------------
    timeLabel.setText ("Delay time ms.", dontSendNotification);
    //timeLabel.attachToComponent (&delayTimeSlider, true);
    timeLabel.setJustificationType (Justification::right);
    timeLabel.setColour (TextEditor::textColourId, Colours::white);
    timeLabel.setColour (Label::backgroundColourId, Colours::darkslateblue);
    addAndMakeVisible (timeLabel);

    // FlexBox layout --------------------------------------------------------
    juce::FlexBox flexBox;
    flexBox.flexDirection = juce::FlexBox::Direction::column;
    flexBox.justifyContent = juce::FlexBox::JustifyContent::flexStart;
    flexBox.alignContent = juce::FlexBox::AlignContent::stretch;

    // Add the sliders to the FlexBox
    flexBox.items.add(juce::FlexItem(gainLabel).withFlex(1));
    flexBox.items.add(juce::FlexItem(gainSlider).withFlex(1));
    flexBox.items.add(juce::FlexItem(timeLabel).withFlex(1));
    flexBox.items.add(juce::FlexItem(delayTimeSlider).withFlex(1));

    // Set the size of the FlexBox to fill the available space
    flexBox.performLayout(getLocalBounds().toFloat());
}

CircularBufferAudioProcessorEditor::~CircularBufferAudioProcessorEditor()
{
}

//==============================================================================
void CircularBufferAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Very Simple delay", getLocalBounds(), Justification::topLeft, 1);
}

void CircularBufferAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    gainSlider.setBounds(getLocalBounds());
    delayTimeSlider.setBounds(getLocalBounds());

}

void CircularBufferAudioProcessorEditor::sliderValueChanged(Slider *slider)
{
    if (slider == &gainSlider)
    {
        audioProcessor.delayVolume = gainSlider.getValue();
    } else if (slider == &delayTimeSlider)
    {
        audioProcessor.delayTime = delayTimeSlider.getValue();
    }
}
