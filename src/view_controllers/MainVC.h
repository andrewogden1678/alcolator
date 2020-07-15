#pragma once
#include <AppCore/AppCore.h>

using namespace ultralight;

// View for main page, content is permission dependent
class MainView : public LoadListener, // Various app-state dependent handlers
                public WindowListener, // Window handlers
                public ViewListener { // View handlers
    
    public:
        // Constructor & Destructor
        MainView(Ref<Window> window_);
        ~MainView();     


    protected:
        Ref<Window> window_; // Window ref
        Ref<Overlay> overlay_; // Overlay ref     
}