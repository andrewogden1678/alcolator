#pragma once
#include <AppCore/AppCore.h>

using namespace ultralight;

// View for admin page
class AdminView : public LoadListener, // Various app-state dependent handlers
                public WindowListener, // Window handlers
                public ViewListener { // View handlers
    
    public:
        // Constructor & Destructor
        AdminView(Ref<Window> window_);
        ~AdminView();     


    protected:
        Ref<Window> window_; // Window ref
        Ref<Overlay> overlay_; // Overlay ref     
}