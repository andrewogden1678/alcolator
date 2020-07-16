#pragma once
#include <AppCore/AppCore.h>

using namespace ultralight;

// View for login page
class LoginView : public LoadListener, // Various app-state dependent handlers
                public WindowListener, // Window handlers
                public ViewListener 
{ // View handlers
    
    public:
        // Constructor & Destructor
        LoginView(Ref<Window> window);
        ~LoginView();     

        // Cursor changer
        virtual void OnChangeCursor(ultralight::View* caller, Cursor cursor) override { window_->SetCursor(cursor); }

        // Inherited from WindowListener
        virtual void OnClose() override;
        virtual void OnResize(uint32_t width, uint32_t height) override;

        // Inherited from LoadListener
        virtual void OnDOMReady(View* caller, uint64_t frame_id,
            bool is_main_frame, const String& url) override;

        // View getter
        RefPtr<View> view() { return overlay_->view(); }

    protected:
        Ref<Window> window_; // Window ref
        Ref<Overlay> overlay_; // Overlay ref     
};