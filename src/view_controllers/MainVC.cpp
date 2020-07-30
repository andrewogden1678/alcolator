#include "MainVC.h"
#include <string>

MainView::MainView(Ref<Window> window) : ViewController::ViewController(window) {
    // Create overlay
    overlay_ = Overlay::Create(window_, 900, 600, 0, 0);

    // Set load and view listeners, then load the page
    GetView()->set_load_listener(this);
    GetView()->set_view_listener(this);
    GetView()->LoadURL("file:///main.html");
}

MainView::~MainView() {
    // Destroy listener instances
    GetView()->set_load_listener(nullptr);
    GetView()->set_view_listener(nullptr);
    overlay_ = nullptr;
}

///
/// Listeners inherited from Ultralight
///
void MainView::OnClose() {}

void MainView::OnResize(uint32_t width, uint32_t height) {}

void MainView::OnDOMReady(View* caller, uint64_t frame_id, bool is_main_frame, const String& url) {
    // Lock and set the javascript context for all future calls
    Ref<JSContext> locked_context = GetView()->LockJSContext();
    SetJSContext(locked_context.get());
    JSObject global = JSGlobalObject();

    // Bind methods to be invoked from JS
    global["OnWindowClose"] = BindJSCallback(&MainView::OnWindowClose);
    global["OnWindowClose"] = BindJSCallbackWithRetval(&MainView::OnClickFile);
}

///
/// Local JS-Invoked Methods
///
JSValue MainView::OnClickFile(const JSObject& obj, const JSArgs& args) {
    std::string temp[2] = {"S123", "6/2/2020"} 
    return JSValue(temp);
}