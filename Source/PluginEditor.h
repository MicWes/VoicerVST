/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
class DecibelSlider : public Slider {
public:
	DecibelSlider() {}

	double getValueFromText(const String& text) override
	{
		auto minusInfinitydb = -36.0;

		auto decibelText = text.upToFirstOccurrenceOf("db", false, false).trim();

		return decibelText.equalsIgnoreCase("-INF") ? minusInfinitydb
													: decibelText.getDoubleValue();
	}

	String getTextFromValue(double value) override 
	{
		return Decibels::toString(value);
	}

private:
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DecibelSlider)
};
//==============================================================================
/**
*/
class VoicerAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    VoicerAudioProcessorEditor (VoicerAudioProcessor&);
    ~VoicerAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

    //==============================================================================
	//
	

private:
    
	//==============================================================================
	// Elementos visuais
	//DecibelSlider gainSlider;

	Label gainLabel;
	Label pitchLabel;
	Label detuneLabel;
	Label voiceLabel;
	Label drywetLabel;

	Slider pitchKnob;
	Slider detuneKnob;
	Slider voiceKnob;
	DecibelSlider gainKnob;
	Slider drywetKnob;


	// Attachments
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> sliderAttachment;

    //==============================================================================
    
	// This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    VoicerAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VoicerAudioProcessorEditor)
};
