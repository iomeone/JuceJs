/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.4.3

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2017 - ROLI Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "Js.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
#include "JsModule.h"
#include <thread>
void v8test();
//[/MiscUserDefs]

//==============================================================================
Js::Js ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    textButton.reset (new TextButton ("new button"));
    addAndMakeVisible (textButton.get());
    textButton->addListener (this);

    textButton->setBounds (64, 104, 150, 24);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

Js::~Js()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    textButton = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void Js::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void Js::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
	auto r = getLocalBounds();
	auto btnr = r.removeFromTop(proportionOfHeight(0.1));
	textButton->setBounds(btnr);
    //[/UserResized]
}

void Js::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == textButton.get())
    {
        //[UserButtonCode_textButton] -- add your button handler code here..
		
		//std::thread t([this]() {
		//	v8test();
		//});
		//t.detach();

		v8test();
        //[/UserButtonCode_textButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void v8test()
{
	CJsModule js;

	//login
	std::string src = u8R"(
		var console = require('JsPlugin');
		console.log("js work!!!!!!!!!!!!!!!!!!!!!!!");
	)";
	try
	{
		js.V8_execute(src.c_str());
		//js.V8_executeFile("demo.js");
	}
	catch (std::exception& msg)
	{
		AlertWindow::showMessageBox(AlertWindow::AlertIconType::WarningIcon, "error", msg.what(), "Ok");
	}
	

//	std::string strInput;
//	cin >> strInput;

	//login2
//	js.V8_executeFileFunction("login.js", "captcha_check", "%s", strInput.c_str());
//	js.V8_executeFileFunction("login.js", "login", "%s|%s", "wang70", "xxx");


}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="Js" componentName="" parentClasses="public Component"
                 constructorParams="" variableInitialisers="" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="0" initialWidth="600"
                 initialHeight="400">
  <BACKGROUND backgroundColour="ff323e44"/>
  <TEXTBUTTON name="new button" id="68928f5b961c5727" memberName="textButton"
              virtualName="" explicitFocusOrder="0" pos="64 104 150 24" buttonText="new button"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

