#pragma once
#include "ViewController.h"

using namespace ultralight;

///
/// Main Page View Controller
///
class MainView : public ViewController
{ 
    
    public:
        // Constructor/Destructor
        MainView(Ref<Window> window);
        ~MainView();   
        
        /// ViewController Events
        // Members inherited from ViewListener
        virtual void OnClose() override;
        virtual void OnResize(uint32_t width, uint32_t height) override;

        // Members inherited from LoadListener
        virtual void OnDOMReady(View* caller, uint64_t frame_id,
            bool is_main_frame, const String& url) override;

        /// Local JS-Invoked Methods
        JSArray OnClickFile(const JSObject& obj, const JSArgs& args);
};