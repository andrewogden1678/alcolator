#pragma once
#include "ViewController.h"
#include "../database/models/Subject.h"
#include "../database/models/Result.h"
#include <vector>
#include <string>

using namespace ultralight;
using namespace std;

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
        JSValue OnLoadSubjects(const JSObject& obj, const JSArgs& args);
        JSValue OnLoadPrevRecord(const JSObject& obj, const JSArgs& args);
};