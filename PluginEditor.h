/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"


//==============================================================================
/**
*/
class CompreezorAudioProcessorEditor : public AudioProcessorEditor, public Slider::Listener,
	public Button::Listener
{
public:
    CompreezorAudioProcessorEditor (CompreezorAudioProcessor&);
    ~CompreezorAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
	void sliderValueChanged(Slider* sliderThatWasMoved) override;
	void buttonClicked(Button* buttonThatWasClicked) override;
	// Binary resources:
	static const char* brushedMetalShrunk_jpg;
	static const int brushedMetalShrunk_jpgSize;
	ScopedPointer<Slider> DetGainSlider;
	ScopedPointer<Slider> ThresholdSlider;
	ScopedPointer<Slider> AttackTimeSlider;
	ScopedPointer<Slider> ReleaseTimeSlider;
	ScopedPointer<Slider> RatioSlider;
	ScopedPointer<Slider> OutputGainSlider;
	ScopedPointer<Slider> KneeWidthSlider;
	ScopedPointer<ToggleButton> DigitalAnalogueButton;
	ScopedPointer<Drawable> drawable1;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    CompreezorAudioProcessor& processor;

	

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CompreezorAudioProcessorEditor)
};
