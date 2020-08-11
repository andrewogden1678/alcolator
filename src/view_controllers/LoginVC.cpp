#include "LoginVC.h"
#include "MainVC.h"
#include "AdminVC.h"
#include <iostream>
#include <string>

using namespace std;

// View constructor
LoginView::LoginView(Ref<Window> window) : ViewController::ViewController(window) {
    // Create overlay
    overlay_ = Overlay::Create(window_, 900, 600, 0, 0);

    // Set load and view listeners, then load the page
    GetView()->set_load_listener(this);
    GetView()->set_view_listener(this);
    GetView()->LoadURL("file:///login.html");
}

// View destructor
LoginView::~LoginView() {
    // Destroy instances
    if (overlay_ != NULL) {
        this->ViewDealloc();
    }
}

///
/// Listeners inherited from Ultralight
///
// On window close (required inherit from AppCore)
void LoginView::OnClose() { 
    // Close database instance
    Database::Instance()->Disconnect();
}

// On window resize (required inherit from AppCore)
void LoginView::OnResize(uint32_t width, uint32_t height) {}

// On DOM ready
void LoginView::OnDOMReady(View* caller, uint64_t frame_id, bool is_main_frame, const String& url) {
    // Lock and set the javascript context for all future calls
    Ref<JSContext> locked_context = GetView()->LockJSContext();
    SetJSContext(locked_context.get());

    // Get the global javascript object
    JSObject global = JSGlobalObject();

    // Bind methods to be invoked from JS
    global["OnWindowClose"] = BindJSCallback(&LoginView::OnWindowClose);
    global["OnLogin"] = BindJSCallback(&LoginView::OnLogin);
}

///
/// Local JS-Invoked Methods
///
// On authentication
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
        // Get identity
        Identity id = Database::Instance()->Select<Identity>("username", "IS", username).at(0);

        // Store validation
        bool isCorrect = Utilities::Authenticate(password, id.password_);

        // If credentials are correct
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