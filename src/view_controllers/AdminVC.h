#pragma once
#include <AppCore/AppCore.h>
#include "ViewController.h"

using namespace ultralight;

///
/// Admin Page View Controller
///
class AdminView : public ViewController
{ 
    
    public:
        // Constructor/Destructor
        AdminView(Ref<Window> window);
        ~AdminView();   
        
        /// ViewController Events
        // Members inherited from ViewListener
        virtual void OnClose() override;
        virtual void OnResize(uint32_t width, uint32_t height) override;

        // Members inherited from LoadListener
        virtual void OnDOMReady(View* caller, uint64_t frame_id,
            bool is_main_frame, const String& url) override;

};