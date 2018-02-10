/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
CompreezorAudioProcessorEditor::CompreezorAudioProcessorEditor (CompreezorAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
	bool DigitalAnalogue; //Digital/Analogue style compression
	addAndMakeVisible(DetGainSlider = new Slider("Det Gain"));
	DetGainSlider->setRange(-12, 12, 0.01 );
	DetGainSlider->setValue(processor.DetGain);
	DetGainSlider->setSliderStyle(Slider::RotaryVerticalDrag);
	DetGainSlider->setTextBoxStyle(Slider::TextBoxLeft, false, 80, 20);
	DetGainSlider->setColour(Slider::thumbColourId, Colour(0xffb5b5b5));
	DetGainSlider->addListener(this);
	DetGainSlider->setSkewFactorFromMidPoint(0.5);

	addAndMakeVisible(ThresholdSlider = new Slider("Threshold"));
	ThresholdSlider->setRange(-60, 0, 0.01);
	ThresholdSlider->setValue(processor.Threshold);
	ThresholdSlider->setSliderStyle(Slider::RotaryVerticalDrag);
	ThresholdSlider->setTextBoxStyle(Slider::TextBoxLeft, false, 80, 20);
	ThresholdSlider->setColour(Slider::thumbColourId, Colour(0xffb5b5b5));
	ThresholdSlider->addListener(this);
	ThresholdSlider->setSkewFactor(2);

	addAndMakeVisible(AttackTimeSlider = new Slider("Attack Time"));
	AttackTimeSlider->setRange(0.02, 300, 0.01);
	AttackTimeSlider->setValue(processor.AttackTime);
	AttackTimeSlider->setSliderStyle(Slider::RotaryVerticalDrag);
	AttackTimeSlider->setTextBoxStyle(Slider::TextBoxLeft, false, 80, 20);
	AttackTimeSlider->setColour(Slider::thumbColourId, Colour(0xffb5b5b5));
	AttackTimeSlider->addListener(this);
	AttackTimeSlider->setSkewFactor(0.5);


	addAndMakeVisible(ReleaseTimeSlider = new Slider("Release Time"));
	ReleaseTimeSlider->setRange(10, 5000, 0.01);
	ReleaseTimeSlider->setValue(processor.ReleaseTime);
	ReleaseTimeSlider->setSliderStyle(Slider::RotaryVerticalDrag);
	ReleaseTimeSlider->setTextBoxStyle(Slider::TextBoxLeft, false, 80, 20);
	ReleaseTimeSlider->setColour(Slider::thumbColourId, Colour(0xffb5b5b5));
	ReleaseTimeSlider->addListener(this);
	ReleaseTimeSlider->setSkewFactor(0.5);

	addAndMakeVisible(RatioSlider = new Slider("Ratio"));
	RatioSlider->setRange(1, 20, 0.01);
	RatioSlider->setValue(processor.Ratio);
	RatioSlider->setSliderStyle(Slider::RotaryVerticalDrag);
	RatioSlider->setTextBoxStyle(Slider::TextBoxLeft, false, 80, 20);
	RatioSlider->setColour(Slider::thumbColourId, Colour(0xffb5b5b5));
	RatioSlider->addListener(this);
	

	addAndMakeVisible(OutputGainSlider = new Slider("Makeup Gain"));
	OutputGainSlider->setRange(0, 40, 0.01);
	OutputGainSlider->setValue(processor.OutputGain);
	OutputGainSlider->setSliderStyle(Slider::RotaryVerticalDrag);
	OutputGainSlider->setTextBoxStyle(Slider::TextBoxLeft, false, 80, 20);
	OutputGainSlider->setColour(Slider::thumbColourId, Colour(0xffb5b5b5));
	OutputGainSlider->addListener(this);


	addAndMakeVisible(KneeWidthSlider = new Slider("Knee Width"));
	KneeWidthSlider->setRange(0, 20, 0.01);
	KneeWidthSlider->setValue(processor.KneeWidth);
	KneeWidthSlider->setSliderStyle(Slider::RotaryVerticalDrag);
	KneeWidthSlider->setTextBoxStyle(Slider::TextBoxLeft, false, 80, 20);
	KneeWidthSlider->setColour(Slider::thumbColourId, Colour(0xffb5b5b5));
	KneeWidthSlider->addListener(this);

	addAndMakeVisible(DigitalAnalogueButton = new ToggleButton("Digital/Analogue"));
	DigitalAnalogueButton->addListener(this);

	drawable1 = Drawable::createFromImageData(BinaryData::brushedMetalSHRUNK_jpg, BinaryData::brushedMetalSHRUNK_jpgSize);

	//cachedImage_brushedMetalShrunk_jpg_1 = ImageCache::getFromMemory(brushedMetalShrunk_jpg, brushedMetalShrunk_jpgSize);


	//[UserPreSize]
	//[/UserPreSize]

	setSize(880, 300);


	//[Constructor] You can add your own custom stuff here..
	//[/Constructor]
	// Make sure that before the constructor has finished, you've set the
	// editor's size to whatever you need it to be.

}

CompreezorAudioProcessorEditor::~CompreezorAudioProcessorEditor()
{
	DetGainSlider = nullptr;
	ThresholdSlider = nullptr;
	AttackTimeSlider = nullptr;
	ReleaseTimeSlider = nullptr;
	RatioSlider = nullptr;
	OutputGainSlider = nullptr;
	KneeWidthSlider = nullptr;
	DigitalAnalogueButton = nullptr;
	drawable1 = nullptr;
}

//==============================================================================
void CompreezorAudioProcessorEditor::paint (Graphics& g)
{
	// (Our component is opaque, so we must completely fill the background with a solid colour)
	g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));

	{
		int x = 8, y = -1, width = 880, height = 300;
		//[UserPaintCustomArguments] Customize the painting arguments here..
		//[/UserPaintCustomArguments]
		g.setColour(Colours::black);
		jassert(drawable1 != 0);
		if (drawable1 != 0)
			drawable1->drawWithin(g, juce::Rectangle<float>(x, y, width, height),
				RectanglePlacement::stretchToFit, 1.000f);
	}

	{
		int x = 36, y = 44, width = 200, height = 30;
		String text(TRANS("Input Gain"));
		Colour fillColour = Colour(0xffd4d4d4);
		//[UserPaintCustomArguments] Customize the painting arguments here..
		//[/UserPaintCustomArguments]
		g.setColour(fillColour);
		g.setFont(Font(23.70f, Font::plain).withTypefaceStyle("Regular"));
		g.drawText(text, x, y, width, height,
			Justification::centred, true);
	}

	{
		int x = 228, y = 44, width = 200, height = 30;
		String text(TRANS("Threshold"));
		Colour fillColour = Colour(0xffd4d4d4);
		//[UserPaintCustomArguments] Customize the painting arguments here..
		//[/UserPaintCustomArguments]
		g.setColour(fillColour);
		g.setFont(Font(23.70f, Font::plain).withTypefaceStyle("Regular"));
		g.drawText(text, x, y, width, height,
			Justification::centred, true);
	}

	{
		int x = 444, y = 44, width = 200, height = 30;
		String text(TRANS("Attack Time"));
		Colour fillColour = Colour(0xffd4d4d4);
		//[UserPaintCustomArguments] Customize the painting arguments here..
		//[/UserPaintCustomArguments]
		g.setColour(fillColour);
		g.setFont(Font(23.70f, Font::plain).withTypefaceStyle("Regular"));
		g.drawText(text, x, y, width, height,
			Justification::centred, true);
	}

	{
		int x = 636, y = 44, width = 200, height = 30;
		String text(TRANS("Release Time"));
		Colour fillColour = Colour(0xffd4d4d4);
		//[UserPaintCustomArguments] Customize the painting arguments here..
		//[/UserPaintCustomArguments]
		g.setColour(fillColour);
		g.setFont(Font(23.70f, Font::plain).withTypefaceStyle("Regular"));
		g.drawText(text, x, y, width, height,
			Justification::centred, true);
	}

	{
		int x = 36, y = 172, width = 200, height = 30;
		String text(TRANS("Ratio"));
		Colour fillColour = Colour(0xffb9b9b9);
		//[UserPaintCustomArguments] Customize the painting arguments here..
		//[/UserPaintCustomArguments]
		g.setColour(fillColour);
		g.setFont(Font(23.70f, Font::plain).withTypefaceStyle("Regular"));
		g.drawText(text, x, y, width, height,
			Justification::centred, true);
	}

	{
		int x = 236, y = 172, width = 200, height = 30;
		String text(TRANS("Makeup Gain"));
		Colour fillColour = Colour(0xffb9b9b9);
		//[UserPaintCustomArguments] Customize the painting arguments here..
		//[/UserPaintCustomArguments]
		g.setColour(fillColour);
		g.setFont(Font(23.70f, Font::plain).withTypefaceStyle("Regular"));
		g.drawText(text, x, y, width, height,
			Justification::centred, true);
	}

	{
		int x = 444, y = 172, width = 200, height = 30;
		String text(TRANS("Knee Width"));
		Colour fillColour = Colour(0xffb9b9b9);
		//[UserPaintCustomArguments] Customize the painting arguments here..
		//[/UserPaintCustomArguments]
		g.setColour(fillColour);
		g.setFont(Font(23.70f, Font::plain).withTypefaceStyle("Regular"));
		g.drawText(text, x, y, width, height,
			Justification::centred, true);
	}
}

void CompreezorAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
	DetGainSlider->setBounds(56, 56, 160, 112);
	ThresholdSlider->setBounds(256, 56, 160, 112);
	AttackTimeSlider->setBounds(464, 56, 160, 112);
	ReleaseTimeSlider->setBounds(656, 56, 160, 112);
	RatioSlider->setBounds(56, 184, 160, 112);
	OutputGainSlider->setBounds(256, 184, 160, 112);
	KneeWidthSlider->setBounds(464, 184, 160, 112);
	DigitalAnalogueButton->setBounds(680, 224, 150, 24);
}

void CompreezorAudioProcessorEditor::sliderValueChanged(Slider* sliderThatWasMoved)
{
	//[UsersliderValueChanged_Pre]
	//[/UsersliderValueChanged_Pre]

	if (sliderThatWasMoved == DetGainSlider)
	{
		//[UserSliderCode_slider] -- add your slider handling code here..
		//[/UserSliderCode_slider]

		processor.DetGain = pow(10.0, DetGainSlider->getValue() / 20.0);

	}

	else if (sliderThatWasMoved == ThresholdSlider)
	{
		//[UserSliderCode_slider2] -- add your slider handling code here..
		//[/UserSliderCode_slider2]
		processor.Threshold = ThresholdSlider->getValue();


	}

	else if (sliderThatWasMoved == AttackTimeSlider)
	{
		//[UserSliderCode_slider3] -- add your slider handling code here..
		//[/UserSliderCode_slider3]
		processor.AttackTime = AttackTimeSlider->getValue();
		processor.m_LeftDetector.setAttackTime(AttackTimeSlider->getValue());
	}

	else if (sliderThatWasMoved == ReleaseTimeSlider)
	{
		//[UserSliderCode_slider4] -- add your slider handling code here..
		//[/UserSliderCode_slider4]
		processor.ReleaseTime = ReleaseTimeSlider->getValue();
		processor.m_LeftDetector.setReleaseTime(ReleaseTimeSlider->getValue());
	}
	else if (sliderThatWasMoved == RatioSlider)
	{
		//[UserSliderCode_slider5] -- add your slider handling code here..
		//[/UserSliderCode_slider5]
		processor.Ratio = RatioSlider->getValue();

	}
	else if (sliderThatWasMoved == OutputGainSlider)
	{
		//[UserSliderCode_slider6] -- add your slider handling code here..
		//[/UserSliderCode_slider6]
		processor.OutputGain = pow(10.0, OutputGainSlider->getValue() / 20.0);
	}
	else if (sliderThatWasMoved == KneeWidthSlider)
	{
		//[UserSliderCode_slider7] -- add your slider handling code here..
		//[/UserSliderCode_slider7]
		processor.KneeWidth = KneeWidthSlider->getValue();
	}

	//[UsersliderValueChanged_Post]
	//[/UsersliderValueChanged_Post]
}

void CompreezorAudioProcessorEditor::buttonClicked(Button* buttonThatWasClicked)
{
	//[UserbuttonClicked_Pre]
	//[/UserbuttonClicked_Pre]

	if (buttonThatWasClicked == DigitalAnalogueButton)
	{
		//[UserButtonCode_toggleButton] -- add your button handler code here..
		//[/UserButtonCode_toggleButton]
		//processor.DigitalAnalogue = DigitalAnalogueButton.get()->getToggleStateValue;
	}

	//[UserbuttonClicked_Post]
	//[/UserbuttonClicked_Post]
}
