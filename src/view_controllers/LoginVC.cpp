#include "LoginVC.h"
#include "MainVC.h"
#include "AdminVC.h"
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
    if (overlay_ != NULL) {
        this->ViewDealloc();
    }
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
bool LoginView::OnLogin(const JSObject& obj, const JSArgs& args) {
    // Extract username
    ultralight::String rawUsername(args[0].ToString());
    std::string username;
    username += "\"";
    username += static_cast<std::string>(rawUsername.utf8().data());
    username += "\"";
    // Extract password
    ultralight::String rawPassword(args[1].ToString());
    std::string password(static_cast<std::string>(rawPassword.utf8().data()));

    // Try and select user
    try {
        Identity id = Database::Instance()->Select<Identity>("username", "IS", username).at(0);

        bool isCorrect = Utilities::Authenticate(password, id.password_);

        if (isCorrect) {
            if (id.access_level_ == AccessLevel::ADMINISTRATOR) {
                // Set next view and deallocate memory items
                NextView(new AdminView(window_.get(), id));
                ViewDealloc();
                return JSValue(true);
            }
            else {
                // Set next view and deallocate memory items
                NextView(new MainView(window_.get(), id));
                ViewDealloc();
                return JSValue(true);
            }          
        }
        else {
            // Password incorrect
            return JSValue(false);
        }
    } catch (...) { // User not found
        // Return false
        return JSValue(false);
    }
    
}