/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "EnvelopeDetector.h"

//==============================================================================
/**
*/
class CompreezorAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    CompreezorAudioProcessor();
    ~CompreezorAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect () const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

	bool GUIActive;

	float DetGain=1;  //Input Gain in dB
	float Threshold=0; //Compressor Threshold
	float AttackTime=10; //Attack Time in Milliseconds
	float ReleaseTime=200; //Release Time in Milliseconds
	float Ratio=4; //Compression Ratio
	float OutputGain=1; //Output Gain in dB
	float KneeWidth=0; //Compressor Knee Width
	bool DigitalAnalogue; //Digital/Analogue style compression


	UINT DETECT_MODE_PEAK = 0;
	UINT DETECT_MODE_MS = 1;
	UINT DETECT_MODE_RMS = 2;

	CEnvelopeDetector  m_LeftDetector;
	CEnvelopeDetector m_RightDetector;

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CompreezorAudioProcessor)
		float calcCompressorGain(float fDetectorValue, float fThreshold, float fRatio,
			float fKneeWidth, bool bLimit);
};
