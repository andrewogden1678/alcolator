#include "LoginVC.h"
#include "MainVC.h"
#include <iostream>
#include <string>

using namespace std;

LoginView::LoginView(Ref<Window> window) : ViewController::ViewController(window) {
    // Create overlay
    overlay_ = Overlay::Create(window_, 900, 600, 0, 0);

    // Set load and view listeners, then load the page
    GetView()->set_load_listener(this);
    GetView()->set_view_listener(this);
    GetView()->LoadURL("file:///login.html");
}

LoginView::~LoginView() {
    // Destroy instances
    GetView()->set_load_listener(nullptr);
    GetView()->set_view_listener(nullptr);
    overlay_ = nullptr;
}

///
/// Listeners inherited from Ultralight
///
void LoginView::OnClose() {}

void LoginView::OnResize(uint32_t width, uint32_t height) {}

void LoginView::OnDOMReady(View* caller, uint64_t frame_id, bool is_main_frame, const String& url) {
    // Lock and set the javascript context for all future calls
    Ref<JSContext> locked_context = GetView()->LockJSContext();
    SetJSContext(locked_context.get());
    JSObject global = JSGlobalObject();

    // Bind methods to be invoked from JS
    global["OnWindowClose"] = BindJSCallback(&LoginView::OnWindowClose);
    global["OnLogin"] = BindJSCallback(&LoginView::OnLogin);
}

///
/// Local JS-Invoked Methods
///
// ARGS: Username (string), Password (string)
void LoginView::OnLogin(const JSObject& obj, const JSArgs& args) {
    /*
    ** Login code/handling here
    */  
    /*std::cout << static_cast<int>(args.size()) << std::endl;
    std::cout.flush();*/
    std::cout << "test"<< std::endl;
    std::cout.flush();

    // Set next view and deallocate memory items
    NextView(new MainView(window_.get()));
    ViewDealloc();
}