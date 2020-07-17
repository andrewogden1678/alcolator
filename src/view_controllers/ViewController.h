#pragma once
#include <AppCore/AppCore.h>

using namespace ultralight;

///
/// View Controller ABC
///
class ViewController : public WindowListener, // Window handlers
                    public LoadListener, // App-state dependent handlers
                    public ViewListener // View handlers
{
    public:
        ViewController(Ref<Window> window) : window_(window) {};
        virtual ~ViewController() {};

        // Members inherited from ViewListener
        virtual void OnChangeCursor(ultralight::View* caller, Cursor cursor) override { window_->SetCursor(cursor); }
// Members inherited from ViewListener
        virtual void OnClose() override = 0;
        virtual void OnResize(uint32_t width, uint32_t height) override = 0;

        // Members inherited from LoadListener
        virtual void OnDOMReady(View* caller, uint64_t frame_id,
            bool is_main_frame, const String& url) override = 0;
        // Get view from overlay
        RefPtr<View> view() { return overlay_->view(); }

    protected:
        Ref<Window> window_; // Window ref
        RefPtr<Overlay> overlay_; // Overlay ref     
}; 
