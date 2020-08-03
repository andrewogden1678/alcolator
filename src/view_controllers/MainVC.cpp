#include "MainVC.h"

MainView::MainView(Ref<Window> window) : ViewController::ViewController(window) {
    // Create overlay
    overlay_ = Overlay::Create(window_, 900, 600, 0, 0);

    // Set load and view listeners, then load the page
    GetView()->set_load_listener(this);
    GetView()->set_view_listener(this);
    GetView()->LoadURL("file:///main.html");
}

MainView::~MainView() {
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
void MainView::OnClose() {
    // Close database instance
    Database::Instance()->Disconnect();
}

void MainView::OnResize(uint32_t width, uint32_t height) {}

void MainView::OnDOMReady(View* caller, uint64_t frame_id, bool is_main_frame, const String& url) {
    // Lock and set the javascript context for all future calls
    Ref<JSContext> locked_context = GetView()->LockJSContext();
    SetJSContext(locked_context.get());
    JSObject global = JSGlobalObject();

    // Bind methods to be invoked from JS
    global["OnWindowClose"] = BindJSCallback(&MainView::OnWindowClose);
    global["OnLoadSubjects"] = BindJSCallbackWithRetval(&MainView::OnLoadSubjects);
    global["OnLoadPrevRecord"] = BindJSCallbackWithRetval(&MainView::OnLoadPrevRecord);

    // Load subjects on first load
    GetView()->EvaluateScript("vm.loadSubjects()");
}

///
/// Local JS-Invoked Methods
///
JSValue MainView::OnLoadSubjects(const JSObject& obj, const JSArgs& args) {

    // Get all subjects from database
    std::vector<Subject> subjects(Database::Instance()->Select<Subject>());

    // Javascript array
    JSArray jArray;
    
    // Loop through and push values to array
    for (std::vector<Subject>::iterator subject = subjects.begin(); subject != subjects.end(); subject++) { 
        // Temporary array
        JSArray tempArray;

        /// Assign to the temp array
        // [0] Primary key
        // [1] Subject code
        // [2] Created on
        tempArray.push(JSValue(JSString(std::to_string(subject->GetPK()).c_str())));
        tempArray.push(JSValue(JSString(subject->subject_code_.c_str())));
        tempArray.push(JSValue(JSString(subject->created_on_.c_str())));

        // Push the array to the main array
        jArray.push(JSValue(tempArray));
    }

    // Send to javascript
    return JSValue(jArray);
}

JSValue MainView::OnLoadPrevRecord(const JSObject& obj, const JSArgs& args) {

    // ID of subject to retrieve
    int64_t subId = args[0].ToInteger();

    
    try {
        // Get result and corresponding foreign keys
        Result res = Database::Instance()->Select<Result>("subject_id", "IS", to_string(subId)).at(0);

        // Javascript array
        JSArray jArray;

        /// Assign to the return array
        // [0] Primary key
        // [1] Subject code
        // [2] Age
        // [3] Height
        // [4] Weight
        // [5] Gender
        // [6] Created on
        // [7] Target BAC
        // [8] Target BAC time
        // [9] Amount (grams)
        // [10] Amount (beverage)
        // [11] Actual BAC
        // [12] Actual BAC time
        // [13] Beverage name
        // [14] Beverage concentration
        jArray.push(JSValue(JSString(std::to_string(res.subject_.GetPK()).c_str())));
        jArray.push(JSValue(JSString(res.subject_.subject_code_.c_str())));
        jArray.push(JSValue(JSString(std::to_string(res.subject_.age_).c_str())));
        jArray.push(JSValue(JSString(std::to_string(res.subject_.height_).c_str())));
        jArray.push(JSValue(JSString(std::to_string(res.subject_.weight_).c_str())));
        jArray.push(JSValue(JSString(std::to_string(res.subject_.gender_).c_str())));
        jArray.push(JSValue(JSString(res.subject_.created_on_.c_str())));
        jArray.push(JSValue(JSString(std::to_string(res.target_bac_).c_str())));
        jArray.push(JSValue(JSString(std::to_string(res.target_bac_time_).c_str())));
        jArray.push(JSValue(JSString(std::to_string(res.amount_grams_).c_str())));
        jArray.push(JSValue(JSString(std::to_string(res.amount_beverage_).c_str())));
        jArray.push(JSValue(JSString(std::to_string(res.actual_bac_).c_str())));
        jArray.push(JSValue(JSString(res.actual_bac_time_.c_str())));
        jArray.push(JSValue(JSString(res.beverage_.name_.c_str())));
        jArray.push(JSValue(JSString(std::to_string(res.beverage_.concentration_).c_str())));

        // Send to javascript
        return JSValue(jArray);
    } catch (std::exception &e) {
        // Return error code
        return JSValue(1);
    }
}