#include "AdminVC.h"

AdminView::AdminView(Ref<Window> window) : ViewController::ViewController(window) {
    // Create overlay
    overlay_ = Overlay::Create(window_, 900, 600, 0, 0);

    // Set load and view listeners, then load the page
    GetView()->set_load_listener(this);
    GetView()->set_view_listener(this);
    GetView()->LoadURL("file:///admin_new.html");
}

AdminView::~AdminView() {
    // Destroy instances
    if (overlay_ != NULL) {
        GetView()->set_load_listener(nullptr);
        GetView()->set_view_listener(nullptr);
        overlay_ = nullptr;
    }
}

///
/// Listeners inherited from Ultralight
///
void AdminView::OnClose() {}

void AdminView::OnResize(uint32_t width, uint32_t height) {}

void AdminView::OnDOMReady(View* caller, uint64_t frame_id, bool is_main_frame, const String& url) {
    // Lock and set the javascript context for all future calls
    Ref<JSContext> locked_context = GetView()->LockJSContext();
    SetJSContext(locked_context.get());
    JSObject global = JSGlobalObject();

    // Bind methods to be invoked from JS
    global["OnWindowClose"] = BindJSCallback(&AdminView::OnWindowClose);
}

///
/// Local JS-Invoked Methods
///