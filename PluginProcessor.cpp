/*
==============================================================================

This file was auto-generated!

It contains the basic framework code for a JUCE plugin processor.

==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
CompreezorAudioProcessor::CompreezorAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
	: AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
		.withInput("Input", AudioChannelSet::stereo(), true)
#endif
		.withOutput("Output", AudioChannelSet::stereo(), true)
#endif
	)
#endif
{
}

CompreezorAudioProcessor::~CompreezorAudioProcessor()
{
}

//==============================================================================
const String CompreezorAudioProcessor::getName() const
{
	return JucePlugin_Name;
}

bool CompreezorAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
	return true;
#else
	return false;
#endif
}

bool CompreezorAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
	return true;
#else
	return false;
#endif
}

bool CompreezorAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
	return true;
#else
	return false;
#endif
}

double CompreezorAudioProcessor::getTailLengthSeconds() const
{
	return 0.0;
}

int CompreezorAudioProcessor::getNumPrograms()
{
	return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
				// so this should be at least 1, even if you're not really implementing programs.
}

int CompreezorAudioProcessor::getCurrentProgram()
{
	return 0;
}

void CompreezorAudioProcessor::setCurrentProgram(int index)
{
}

const String CompreezorAudioProcessor::getProgramName(int index)
{
	return {};
}

void CompreezorAudioProcessor::changeProgramName(int index, const String& newName)
{
}

float CompreezorAudioProcessor::calcCompressorGain(float fDetectorValue, float fThreshold,
	float fRatio, float fKneeWidth, bool bLimit)
{
	// slope variable
	float CS = 1.0 - 1.0 / fRatio; // [ Eq. 13.1 ]
								   // limiting is infinite ratio thus CS->1.0
								   //if (bLimit)
								   //CS = 1;

								   // soft-knee with detection value in range?
	if (fKneeWidth > 0 && fDetectorValue > (fThreshold - fKneeWidth / 2.0) &&
		fDetectorValue < fThreshold + fKneeWidth / 2.0)
	{
		// setup for Lagrange
		double x[2];
		double y[2];
		x[0] = fThreshold - fKneeWidth / 2.0;
		x[1] = fThreshold + fKneeWidth / 2.0;
		x[1] = min(0, x[1]); // top limit is 0dBFS
		y[0] = 0; // CS = 0 for 1:1 ratio
		y[1] = CS; // current CS

				   // interpolate & overwrite CS
		CS = lagrpol(&x[0], &y[0], 2, fDetectorValue);
	}
	// compute gain; threshold and detection values are in dB
	float yG = CS * (fThreshold - fDetectorValue); // [ Eq. 13.1 ]
												   // clamp; this allows ratios of 1:1 to still operate
	yG = min(0, yG);

	// convert back to linear
	return pow(10.0, yG / 20.0);
}

//==============================================================================
void CompreezorAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
	// Use this method as the place to do any pre-playback
	// initialisation that you need..
	// init the envelope detectors
	// set all params at once with this function; see function definition

	

	if (DigitalAnalogue == true) //Digit
	{
		m_LeftDetector.init((float)getSampleRate(), AttackTime = 0.0, ReleaseTime,
			false, DETECT_MODE_RMS, true);
		m_RightDetector.init((float)getSampleRate(), AttackTime,
			ReleaseTime, false, DETECT_MODE_RMS, true);
	}
	else
	{
		m_LeftDetector.init((float)getSampleRate(), AttackTime = 0.0, ReleaseTime,
			true, DETECT_MODE_RMS, true);
		m_RightDetector.init((float)getSampleRate(), AttackTime,
			ReleaseTime, true, DETECT_MODE_RMS, true);
	}

}

void CompreezorAudioProcessor::releaseResources()
{
	// When playback stops, you can use this as an opportunity to free up any
	// spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool CompreezorAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
	ignoreUnused(layouts);
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

void CompreezorAudioProcessor::processBlock(AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
	ScopedNoDenormals noDenormals;
	const int totalNumInputChannels = getTotalNumInputChannels();
	const int totalNumOutputChannels = getTotalNumOutputChannels();
	float fInputGain = pow(10.0, DetGain / 20.0);
	float fOutputGain = pow(10.0, OutputGain / 20.0);

	// In case we have more outputs than inputs, this code clears any output
	// channels that didn't contain input data, (because these aren't
	// guaranteed to be empty - they may contain garbage).
	// This is here to avoid people getting screaming feedback
	// when they first compile a plugin, but obviously you don't need to keep
	// this code if your algorithm always overwrites all the output channels.
	for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
		buffer.clear(i, 0, buffer.getNumSamples());

	// This is the place where you'd normally do the guts of your plugin's
	// audio processing...
	for (int channel = 0; channel < totalNumInputChannels; ++channel)
	{
		float* channelData = buffer.getWritePointer(channel);
		for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
		{       // ..do something to the data...			    

			channelData[sample] = channelData[sample] * DetGain;
			// detect left channel
			float fLeftDetector = m_LeftDetector.detect(channelData[sample]);
			// gain calc
			float fGn;
			// branch
			//if (m_uProcessorType == COMP) //always true for this project
			fGn = calcCompressorGain(fLeftDetector, Threshold, Ratio,
				KneeWidth, false);
			// form output and apply make up gain
			channelData[sample] = fGn*channelData[sample] * OutputGain;
		}
	}
}

//==============================================================================
bool CompreezorAudioProcessor::hasEditor() const
{
	return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* CompreezorAudioProcessor::createEditor()
{
	return new CompreezorAudioProcessorEditor(*this);
}

//==============================================================================
void CompreezorAudioProcessor::getStateInformation(MemoryBlock& destData)
{
	// You should use this method to store your parameters in the memory block.
	// You could do that either as raw data, or use the XML or ValueTree classes
	// as intermediaries to make it easy to save and load complex data.
}

void CompreezorAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
	// You should use this method to restore your parameters from this memory block,
	// whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
	return new CompreezorAudioProcessor();
}
