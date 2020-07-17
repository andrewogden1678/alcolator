#pragma once
#include <AppCore/AppCore.h>
#include "ViewController.h"

using namespace ultralight;

// View for login page
class LoginView : public ViewController
{ 
    
    public:
        // Constructor & Destructor
        LoginView(Ref<Window> window);
        ~LoginView();   
        
        ///
        /// ViewController Events
        ///
        // Members inherited from ViewListener
        virtual void OnClose() override;
        virtual void OnResize(uint32_t width, uint32_t height) override;

        // Members inherited from LoadListener
        virtual void OnDOMReady(View* caller, uint64_t frame_id,
            bool is_main_frame, const String& url) override;

};