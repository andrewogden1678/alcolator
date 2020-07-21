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
        // Constructor/Destructor
        ViewController(Ref<Window> window) : window_(window) {};
        virtual ~ViewController() {};

        // Inherited from ViewListener
        virtual void OnChangeCursor(ultralight::View* caller, Cursor cursor) override;

        // Get view object from overlay
        RefPtr<View> GetView();

        // Go to next view
        template <class T> void NextView(T vc) {
            // Set the pointer to the specified view
            nextView_.reset(vc);

            // Set the view listener
            window_->set_listener(nextView_.get());
        }

        // Deallocate certain items in memory (for changing pages)
        void ViewDealloc();

        /// Shared JS-Invoked Methods
        void OnWindowClose(const JSObject& obj, const JSArgs& args);
        void OnWindowMove(const JSObject& obj, const JSArgs& args);

    protected:
        Ref<Window> window_; // Window ref
        RefPtr<Overlay> overlay_; // Overlay ref  
        std::unique_ptr<ViewController> nextView_; // Next view to 
}; 