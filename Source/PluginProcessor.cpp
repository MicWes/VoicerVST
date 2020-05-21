/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
VoicerAudioProcessor::VoicerAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ), vAPVTS (*this, nullptr, "PARAMETERS", createParameters())
#endif
{
	vAPVTS.state.addListener(this);
	updateParameterValues();
}

VoicerAudioProcessor::~VoicerAudioProcessor()
{
}

//==============================================================================
const String VoicerAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool VoicerAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool VoicerAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool VoicerAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double VoicerAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int VoicerAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int VoicerAudioProcessor::getCurrentProgram()
{
    return 0;
}

void VoicerAudioProcessor::setCurrentProgram (int index)
{
}

const String VoicerAudioProcessor::getProgramName (int index)
{
    return {};
}

void VoicerAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void VoicerAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void VoicerAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool VoicerAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void VoicerAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
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

	if (updateParameters) {
		updateParameterValues();
	}

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);		

		for (auto sample = 0; sample < buffer.getNumSamples() ; sample++) {
			channelData[sample] = channelData[sample] * gain;
		}
        
    }
}

//==============================================================================
bool VoicerAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* VoicerAudioProcessor::createEditor()
{
    return new VoicerAudioProcessorEditor (*this);
}

//==============================================================================
void VoicerAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void VoicerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

// Função responsável por atualizar os valores dos parâmetros utilizados no Process Block
void VoicerAudioProcessor::updateParameterValues()
{
	//gain = vAPVTS.getRawParameterValue("GAIN")->load();
	gain = Decibels::decibelsToGain(vAPVTS.getRawParameterValue("GAIN")->load());
}


//==============================================================================
// 

// Funcão que cria os parâmetros os os organiza em um ParameterLayout
AudioProcessorValueTreeState::ParameterLayout VoicerAudioProcessor::createParameters() {
	
	std::vector<std::unique_ptr<RangedAudioParameter>> parameters;

	parameters.push_back(std::make_unique<AudioParameterFloat>("GAIN", "Gain", -36.0f, 12.0f, 0.0f));

	return { parameters.begin(), parameters.end() };
}

// Função que é chamada sempre que houver alterações no ValueTree
void VoicerAudioProcessor::valueTreePropertyChanged(ValueTree& treeWhosePropertyHasChanged, const Identifier& property) {
	updateParameters = true;
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new VoicerAudioProcessor();
}


