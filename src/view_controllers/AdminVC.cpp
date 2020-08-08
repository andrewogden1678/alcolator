#include "AdminVC.h"

AdminView::AdminView(Ref<Window> window, Identity usr) : ViewController::ViewController(window), user_(usr) {
    // Create overlay
    overlay_ = Overlay::Create(window_, 900, 600, 0, 0);

    // Set load and view listeners, then load the page
    GetView()->set_load_listener(this);
    GetView()->set_view_listener(this);
    GetView()->LoadURL("file:///admin.html");
}

AdminView::~AdminView() {
    // Destroy instances
    if (overlay_ != NULL) {
        this->ViewDealloc();
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
    global["OnLoadUsers"] = BindJSCallbackWithRetval(&AdminView::OnLoadUsers);
    global["OnLoadExperiments"] = BindJSCallbackWithRetval(&AdminView::OnLoadExperiments);
    global["OnClickExperimenterMode"] = BindJSCallback(&AdminView::OnClickExperimenterMode);
    global["OnGetUser"] = BindJSCallbackWithRetval(&AdminView::OnGetUser);
    global["OnSaveUser"] = BindJSCallback(&AdminView::OnSaveUser);
    global["OnEditUser"] = BindJSCallback(&AdminView::OnEditUser);
    global["OnAddNewExperiment"] = BindJSCallback(&AdminView::OnAddNewExperiment);
    global["OnLogOut"] = BindJSCallback(&AdminView::OnLogOut);

    // Load initial data
    GetView()->EvaluateScript("vm.initialLoad()");
}

///
/// Local JS-Invoked Methods
///
JSValue AdminView::OnLoadUsers(const JSObject& obj, const JSArgs& args) {
    // Get all subjects
    std::vector<Identity> users(Database::Instance()->Select<Identity>());

    // Javascript array
    JSArray jArray;

    // Loop through and push values to array
    for (std::vector<Identity>::iterator user = users.begin(); user != users.end(); user++) {
        // Temporary array
        JSArray tempArray;

        /// Assign to the temp array
        // [0] Primary key
        // [1] First name
        // [2] Last name
        // [3] Access level
        // [4] Username
        tempArray.push(JSValue(JSString(std::to_string(user->GetPK()).c_str())));
        tempArray.push(JSValue(JSString(user->first_name_.c_str())));
        tempArray.push(JSValue(JSString(user->last_name_.c_str())));
        tempArray.push(JSValue(JSString(std::to_string(static_cast<int>(user->access_level_)).c_str())));
        tempArray.push(JSValue(JSString(user->username_.c_str())));

        // Push the array to the main array
        jArray.push(JSValue(tempArray));
    }

    // Send to javascript
    return JSValue(jArray);
}
JSValue AdminView::OnLoadExperiments(const JSObject& obj, const JSArgs& args) {
    // Get all experiments
    std::vector<Experiment> experiments(Database::Instance()->Select<Experiment>("is_concluded", "IS", std::to_string(0)));

    // JS Array
    JSArray jArray;

    // Loop through and push values to array
    for (std::vector<Experiment>::iterator experiment = experiments.begin(); experiment != experiments.end(); experiment++) {
        // Temporary array
        JSArray tempArray;

        /// Assign to the temp array
        // [0] Primary key
        // [1] Name
        tempArray.push(JSValue(JSString(std::to_string(experiment->GetPK()).c_str())));
        tempArray.push(JSValue(JSString(experiment->name_.c_str())));

        // Push the array to the main array
        jArray.push(JSValue(tempArray));
    }

    // Send to javascript
    return JSValue(jArray);
}
void AdminView::OnSaveUser(const JSObject& obj, const JSArgs& args) {
    // Parse args to JSArray and to respective values
    JSArray jArray(args[0].ToArray());
    // First name
    ultralight::String rawFirstName(jArray[0].ToString());
    std::string firstName(static_cast<std::string>(rawFirstName.utf8().data()));
    // Last name
    ultralight::String rawLastName(jArray[1].ToString());
    std::string lastName(static_cast<std::string>(rawLastName.utf8().data()));
    // Access level
    AccessLevel accessLevel(static_cast<AccessLevel>(jArray[2].ToInteger()));
    // Username
    ultralight::String rawUsername(jArray[3].ToString());
    std::string username(static_cast<std::string>(rawUsername.utf8().data()));
    // Hash the given password
    ultralight::String rawPassword(jArray[4].ToString());
    std::string password(Utilities::Hash(static_cast<std::string>(rawPassword.utf8().data())));

    // Create new Identity and add to database
    Identity identity(-1, firstName, lastName, accessLevel, username, password);
    Database::Instance()->Insert<Identity>(&identity);
}

void AdminView::OnEditUser(const JSObject& obj, const JSArgs& args) {
    // Parse args to JSArray and to respective values
    JSArray jArray(args[0].ToArray());
    // ID
    int id(jArray[0].ToInteger());
    // First name
    ultralight::String rawFirstName(jArray[1].ToString());
    std::string firstName(static_cast<std::string>(rawFirstName.utf8().data()));
    // Last name
    ultralight::String rawLastName(jArray[2].ToString());
    std::string lastName(static_cast<std::string>(rawLastName.utf8().data()));
    // Access level
    AccessLevel accessLevel(static_cast<AccessLevel>(jArray[3].ToInteger()));
    // Username
    ultralight::String rawUsername(jArray[4].ToString());
    std::string username(static_cast<std::string>(rawUsername.utf8().data()));
    // Username
    ultralight::String rawPassword(jArray[5].ToString());
    std::string password(static_cast<std::string>(rawPassword.utf8().data()));

    // Create Identity and update in DB
    if (password == "" || password == "undefined") { // If password not updated
        // Exclude the password
        Identity identity(id, firstName, lastName, accessLevel, username, "");      
        Database::Instance()->Update<Identity>(&identity, "password");
    } else {
        // Hash new password and edit
        Identity identity(id, firstName, lastName, accessLevel, username, Utilities::Hash(password));
        Database::Instance()->Update<Identity>(&identity);
    }  
}

void AdminView::OnAddNewExperiment(const JSObject& obj, const JSArgs& args) {
    // Get name
    ultralight::String rawCode(args[0].ToString());
    std::string code(static_cast<std::string>(rawCode.utf8().data()));

    // Send to DB
    Experiment exp(-1, code, false);
    Database::Instance()->Insert<Experiment>(&exp);
}

void AdminView::OnClickExperimenterMode(const JSObject& obj, const JSArgs& args) {
    // Set next view and deallocate memory items
    NextView(new MainView(window_.get(), this->user_));
    ViewDealloc();
}

JSValue AdminView::OnGetUser(const JSObject& obj, const JSArgs& args) {
    // Return array
    JSArray jArray;

    // Assign to return array
    // [0] ID
    // [1] First name
    // [2] Last name
    // [3] Username
    // [4] Access level
    jArray.push(JSValue(JSString(std::to_string(this->user_.GetPK()).c_str())));
    jArray.push(JSValue(JSString(this->user_.first_name_.c_str())));
    jArray.push(JSValue(JSString(this->user_.last_name_.c_str())));
    jArray.push(JSValue(JSString(this->user_.username_.c_str())));
    jArray.push(JSValue(JSString(std::to_string(static_cast<int>(this->user_.access_level_)).c_str())));

    // Return array
    return JSValue(jArray);
}

void AdminView::OnLogOut(const JSObject& obj, const JSArgs& args) {
    // Set login view and deallocate memory items
    NextView(new LoginView(window_.get()));
    ViewDealloc();
}