#include "ViewController.h"

// Inherited from ViewListener
void ViewController::OnChangeCursor(ultralight::View* caller, Cursor cursor) { 
    window_->SetCursor(cursor); 
}

// Return the current view object
RefPtr<View> ViewController::GetView() { 
    if (overlay_ != NULL) {
        return overlay_->view();
    }
    else {
        // Return null
        return nullptr;
    }    
}

// Memory deallocator
void ViewController::ViewDealloc() {
    // Deallocate listeners and the view overlay
    GetView()->set_load_listener(nullptr);
    GetView()->set_view_listener(nullptr);
    overlay_ = nullptr;
}

// On close window (Shared method)
void ViewController::OnWindowClose(const JSObject& obj, const JSArgs& args) {
    // Safety check (does instance exist?)
    if (App::instance()) {
        // Quit instance
        App::instance()->Quit();
    }
}