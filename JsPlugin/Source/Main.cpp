/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a JUCE application.

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "MainComponent.h"

#include <iostream>
#include <v8pp/module.hpp>
#include <v8pp/class.hpp>

#include <v8pp/config.hpp>


#pragma comment (lib, "v8.dll.lib")
#pragma comment (lib, "v8_libplatform.dll.lib")
#pragma comment (lib, "v8_libbase.dll.lib")

class CPoint
{
public:
	int get_x() const { return x; }

	int x;
	int y;
	int z;
};

CPoint getPoint()
{
	 return CPoint{ 1, 2, 3 };

}

void msg(String s)
{
		AlertWindow::showMessageBox(AlertWindow::AlertIconType::InfoIcon, "msg", s, "ok");
}
namespace console {

	void log(v8::FunctionCallbackInfo<v8::Value> const& args)
	{
		v8::HandleScope handle_scope(args.GetIsolate());

		for (int i = 0; i < args.Length(); ++i)
		{
			if (i > 0) std::cout << ' ';
			v8::String::Utf8Value const str(args.GetIsolate(), args[i]);
			std::cout << *str;
			msg(*str);
		}
		std::cout << std::endl;
		msg("endl");
	}

	v8::Local<v8::Value> init(v8::Isolate* isolate)
	{
		v8::EscapableHandleScope scope(isolate);


		v8pp::class_<CPoint> j_point(isolate);
		j_point
			.set("x", &CPoint::x)
			//.set("prop", v8pp::property(&CPoint::get_x))
			.set("y", &CPoint::y)
			.set("z", &CPoint::z)
			;



		v8pp::module m(isolate);
		m
			.set("getPoint", &getPoint)
			.set("log", &log)
			.set("j_point", j_point)
			;
			


		return scope.Escape(m.new_instance());
	}

} // namespace console

V8PP_PLUGIN_INIT(v8::Isolate* isolate)
{
	return console::init(isolate);
}


















//==============================================================================
class JsPluginApplication  : public JUCEApplication
{
public:
    //==============================================================================
    JsPluginApplication() {}

    const String getApplicationName() override       { return ProjectInfo::projectName; }
    const String getApplicationVersion() override    { return ProjectInfo::versionString; }
    bool moreThanOneInstanceAllowed() override       { return true; }

    //==============================================================================
    void initialise (const String& commandLine) override
    {
        // This method is where you should put your application's initialisation code..

        mainWindow.reset (new MainWindow (getApplicationName()));
    }

    void shutdown() override
    {
        // Add your application's shutdown code here..

        mainWindow = nullptr; // (deletes our window)
    }

    //==============================================================================
    void systemRequestedQuit() override
    {
        // This is called when the app is being asked to quit: you can ignore this
        // request and let the app carry on running, or call quit() to allow the app to close.
        quit();
    }

    void anotherInstanceStarted (const String& commandLine) override
    {
        // When another instance of the app is launched while this one is running,
        // this method is invoked, and the commandLine parameter tells you what
        // the other instance's command-line arguments were.
    }

    //==============================================================================
    /*
        This class implements the desktop window that contains an instance of
        our MainComponent class.
    */
    class MainWindow    : public DocumentWindow
    {
    public:
        MainWindow (String name)  : DocumentWindow (name,
                                                    Desktop::getInstance().getDefaultLookAndFeel()
                                                                          .findColour (ResizableWindow::backgroundColourId),
                                                    DocumentWindow::allButtons)
        {
            setUsingNativeTitleBar (true);
            setContentOwned (new MainComponent(), true);

           #if JUCE_IOS || JUCE_ANDROID
            setFullScreen (true);
           #else
            setResizable (true, true);
            centreWithSize (getWidth(), getHeight());
           #endif

            setVisible (true);
        }

        void closeButtonPressed() override
        {
            // This is called when the user tries to close this window. Here, we'll just
            // ask the app to quit when this happens, but you can change this to do
            // whatever you need.
            JUCEApplication::getInstance()->systemRequestedQuit();
        }

        /* Note: Be careful if you override any DocumentWindow methods - the base
           class uses a lot of them, so by overriding you might break its functionality.
           It's best to do all your work in your content component instead, but if
           you really have to override any DocumentWindow methods, make sure your
           subclass also calls the superclass's method.
        */

    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
    };

private:
    std::unique_ptr<MainWindow> mainWindow;
};

//==============================================================================
// This macro generates the main() routine that launches the app.
START_JUCE_APPLICATION (JsPluginApplication)
