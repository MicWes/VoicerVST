/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

// CONSTRUTOR
//==============================================================================
VoicerAudioProcessorEditor::VoicerAudioProcessorEditor (VoicerAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
	//==============================================================================
	// Configuração dos elementos visuais

	// KNOBS and LABEL
	// GAIN
	gainKnob.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
	gainKnob.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
	gainKnob.setSkewFactorFromMidPoint(0);
	gainKnob.setRotaryParameters(-2.3561944902, 0.7853981634, true);
	
	gainLabel.attachToComponent(&gainKnob, false);
	gainLabel.setJustificationType(Justification::centredTop);
	gainLabel.setText("Gain", NotificationType::dontSendNotification);

	// PITCH
	pitchKnob.setSliderStyle(Slider::RotaryVerticalDrag);
	pitchKnob.setRange(-48.0f, +48.0f, 1.0f);
	pitchKnob.setTextBoxStyle(Slider::TextBoxBelow, false, 40, 20);

	pitchLabel.attachToComponent(&pitchKnob, false);
	pitchLabel.setJustificationType(Justification::centredTop);
	pitchLabel.setText("Pitch", NotificationType::dontSendNotification);

	// VOICE
	voiceKnob.setSliderStyle(Slider::LinearHorizontal);
	voiceKnob.setRange(1.0f, 8.0f, 1.0f);
	voiceKnob.setTextBoxStyle(Slider::TextBoxAbove, false, 50, 50);

	voiceLabel.attachToComponent(&voiceKnob, false);
	voiceLabel.setJustificationType(Justification::centredTop);
	voiceLabel.setText("Voices", NotificationType::dontSendNotification);

	// DETUNE
	detuneKnob.setSliderStyle(Slider::RotaryVerticalDrag);
	detuneKnob.setRange(0.0f, 100.0f, 1.0f);
	detuneKnob.setTextBoxStyle(Slider::TextBoxBelow, false, 40, 20);

	detuneLabel.attachToComponent(&detuneKnob, false);
	detuneLabel.setJustificationType(Justification::centredTop);
	detuneLabel.setText("Detune", NotificationType::dontSendNotification);

	// DRYWET
	drywetKnob.setSliderStyle(Slider::RotaryVerticalDrag);
	drywetKnob.setRange(0.0f, 100.0f, 1.0f);
	drywetKnob.setTextBoxStyle(Slider::TextBoxBelow, false, 40, 20);
	drywetKnob.setValue(100.0f);

	drywetLabel.attachToComponent(&drywetKnob, false);
	drywetLabel.setJustificationType(Justification::centredTop);
	drywetLabel.setText("Dry/Wet", NotificationType::dontSendNotification);

	// Incorporação propriamente dita dos elementos visuais
	addAndMakeVisible(gainKnob);
	addAndMakeVisible(pitchKnob);
	addAndMakeVisible(detuneKnob);
	addAndMakeVisible(voiceKnob);
	addAndMakeVisible(drywetKnob);

	// Attachments
	sliderAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (processor.getValueTree(), "GAIN", gainKnob);

	//==============================================================================

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (500, 350);
}

VoicerAudioProcessorEditor::~VoicerAudioProcessorEditor()
{
}

//==============================================================================
void VoicerAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);    
}

void VoicerAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

	// Posicionamento dos elementos visuais
	//gainKnob.setBoundsRelative(0.7f, 0.7f, 0.25f, 0.25f);
	pitchKnob.setBounds((getWidth() / 5) - 50, (getHeight()/2) - 120, 100, 100);
	gainKnob.setBounds(((getWidth() / 5) * 4) - 50, (getHeight()/2) - 120, 100, 100);
	detuneKnob.setBounds(((getWidth() / 5) * 2) - 150, getHeight() - 130, 100, 100);
	voiceKnob.setBounds(((getWidth() / 5) * 3) - 100, (getHeight()/3) + 50, 100, 100);
	drywetKnob.setBounds(((getWidth() / 5) * 4) - 50, getHeight() - 130, 100, 100);
	

}

//==============================================================================
//

