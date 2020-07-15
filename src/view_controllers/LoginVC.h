#pragma once
#include <AppCore/AppCore.h>

using namespace ultralight;

// View for login page
class LoginView : public LoadListener, // Various app-state dependent handlers
                public WindowListener, // Window handlers
                public ViewListener { // View handlers
    
    public:
        // Constructor & Destructor
        LoginView(Ref<Window> window_);
        ~LoginView();     


    protected:
        Ref<Window> window_; // Window ref
        Ref<Overlay> overlay_; // Overlay ref     

}