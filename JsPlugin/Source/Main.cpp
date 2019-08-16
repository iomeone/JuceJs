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

class Vector3
{
public:
	int getx()
	{
		return x;
	}
	int x, y, z;

};

// Explicit convertor template specialization
template<>
struct v8pp::convert<Vector3>
{
	using from_type = Vector3;
	using to_type = v8::Local<v8::Array>;

	static bool is_valid(v8::Isolate*, v8::Local<v8::Value> value)
	{
		return !value.IsEmpty() && value->IsArray()
			&& value.As<v8::Array>()->Length() == 3;
	}

	static from_type from_v8(v8::Isolate* isolate, v8::Local<v8::Value> value)
	{
		if (!is_valid(isolate, value))
		{
			throw std::invalid_argument("expected [x, y, z] array");
		}

		v8::HandleScope scope(isolate);
		v8::Local<v8::Array> arr = value.As<v8::Array>();

		from_type result;
		result.x = v8pp::from_v8<float>(isolate, arr->Get(0));
		result.y = v8pp::from_v8<float>(isolate, arr->Get(1));
		result.z = v8pp::from_v8<float>(isolate, arr->Get(2));

		return result;
	}

	static to_type to_v8(v8::Isolate* isolate, Vector3 const& value)
	{
		v8::EscapableHandleScope scope(isolate);

		v8::Local<v8::Array> arr = v8::Array::New(isolate, 3);
		arr->Set(0, v8pp::to_v8(isolate, value.x));
		arr->Set(1, v8pp::to_v8(isolate, value.y));
		arr->Set(2, v8pp::to_v8(isolate, value.z));

		return scope.Escape(arr);
	}
};


Vector3 p{ 1,2,3 };

Vector3 getPoint()
{
	return p;	
}

//both work!
void getPoint2(v8::FunctionCallbackInfo<v8::Value> const& args)
{

	v8::HandleScope handle_scope(args.GetIsolate());
	args.GetReturnValue().Set(v8pp::to_v8<Vector3>(args.GetIsolate(), p));
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

	//template<typename T>
	//struct v8pp::is_wrapped_class<Vector3<T>> : std::false_type {};

	v8::Local<v8::Value> init(v8::Isolate* isolate)
	{


		//v8::Local<v8::Array> vec3_js = v8pp::to_v8(isolate, Vector3<int>{ 1, 2, 3 });
		//Vector3<int> vec3 = v8pp::from_v8<Vector3<int>>(isolate, vec3_js); // == { 1, 2, 3 }



		v8::EscapableHandleScope scope(isolate);


		v8pp::class_<Vector3> j_point(isolate);
		j_point
			.set("x", v8pp::property(&Vector3::getx))
			//.set("x", &Vector3::x)
			.set("y", &Vector3::y)
			.set("z", &Vector3::z)
			;



		v8pp::module m(isolate);
		m
			.set("j_point", j_point)
			.set("getPoint", &getPoint)
			.set("log", &log)
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
