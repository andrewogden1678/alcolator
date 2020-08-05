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
    global["OnLoadExperiments"] = BindJSCallbackWithRetval(&MainView::OnLoadExperiments);
    global["OnLoadBeverages"] = BindJSCallbackWithRetval(&MainView::OnLoadBeverages);
    global["OnClickRecord"] = BindJSCallbackWithRetval(&MainView::OnClickRecord);
    global["OnAddNewBeverage"] = BindJSCallback(&MainView::OnAddNewBeverage);
    global["OnAddNewSubject"] = BindJSCallback(&MainView::OnAddNewSubject);

    // Load initial data
    GetView()->EvaluateScript("vm.initialLoad()");
}

///
/// Local JS-Invoked Methods
///
void MainView::OnAddNewBeverage(const JSObject& obj, const JSArgs& args) {
    // Parse args to JSArray and to respective values
    JSArray jArray(args[0].ToArray());
    // Existing ID
    int id(jArray[0].ToInteger());
    // New name
    ultralight::String rawNewName(jArray[1].ToString());
    std::string newName(static_cast<std::string>(rawNewName.utf8().data()));
    // New concentration
    ultralight::String rawNewConc(jArray[2].ToString());
    double newConc(atof(rawNewConc.utf8().data()));
    // Existing name
    ultralight::String rawName(jArray[3].ToString());
    std::string name(static_cast<std::string>(rawName.utf8().data()));
    // Existing concentration
    ultralight::String rawConc(jArray[4].ToString());
    double conc(atof(rawConc.utf8().data()));

    // Updated beverage
    if (jArray[5].ToBoolean()) { // If edited
        Beverage updatedBev(id, name, conc);
        Database::Instance()->Update<Beverage>(&updatedBev);
    }

    // New beverage
    if (jArray[6].ToBoolean()) { // If new added
        Beverage newBev(-1, newName, newConc);
        Database::Instance()->Insert<Beverage>(&newBev);
    }
}
void MainView::OnAddNewSubject(const JSObject& obj, const JSArgs& args) {
    // Parse args to JSArray and to respective values
    JSArray jArray(args[0].ToArray());
    // Subject code
    ultralight::String rawSubjectCode(jArray[0].ToString());
    std::string subjectCode(static_cast<std::string>(rawSubjectCode.utf8().data()));
    // Experimenter ID
    int experimenter(jArray[1].ToInteger());
    // Experiment ID
    int experiment(jArray[2].ToInteger());
    // Age
    int age(jArray[3].ToInteger());
    // Gender
    bool gender(jArray[4].ToBoolean());
    // Height
    ultralight::String rawHeight(jArray[5].ToString());
    double height(atof(rawHeight.utf8().data()));
    // Weight
    ultralight::String rawWeight(jArray[6].ToString());
    double weight(atof(rawWeight.utf8().data()));
    // Created on
    ultralight::String rawCreatedOn(jArray[7].ToString());
    std::string createdOn;
    createdOn += static_cast<std::string>(rawCreatedOn.utf8().data());
    // Beverage ID
    int beverage(jArray[8].ToInteger());
    // Target BAC
    ultralight::String rawTargetBAC(jArray[9].ToString());
    double targetBAC(atof(rawTargetBAC.utf8().data()));
    // Target BAC Time
    int targetBACTime(jArray[10].ToInteger());
    // Amount (grams)
    ultralight::String rawAmountGrams(jArray[11].ToString());
    double amountGrams(atof(rawAmountGrams.utf8().data()));
    // Amount (beverage)
    ultralight::String rawAmountBeverage(jArray[12].ToString());
    double amountBeverage(atof(rawAmountBeverage.utf8().data()));
    // Actual BAC
    ultralight::String rawActualBAC(jArray[13].ToString());
    double actualBAC(atof(rawActualBAC.utf8().data()));
    // Actual BAC recorded time
    ultralight::String rawActualBACTime(jArray[14].ToString());
    std::string actualBACTime(static_cast<std::string>(rawActualBACTime.utf8().data()));

    // Create and insert subject
    Subject subject(-1, subjectCode, experimenter, experiment, age, gender, height, weight, createdOn);
    Database::Instance()->Insert<Subject>(&subject);

    // Get ID for subject just inserted
    std::string condition;
    condition += "\"";
    condition += createdOn;
    condition += "\"";
    int subID(Database::Instance()->Select<Subject>("created_on", "IS", condition).at(0).GetPK());
    
    // Create and insert result
    Result result(-1, subID, beverage, targetBAC, targetBACTime, amountGrams, amountBeverage, actualBAC, actualBACTime);
    Database::Instance()->Insert<Result>(&result);
}
JSValue MainView::OnLoadExperiments(const JSObject& obj, const JSArgs& args) {
    // Get all experiments
    std::vector<Experiment> experiments(Database::Instance()->Select<Experiment>("is_concluded", "IS", to_string(0)));

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

JSValue MainView::OnLoadSubjects(const JSObject& obj, const JSArgs& args) {

    // Get all subjects
    std::vector<Subject> subjects(Database::Instance()->Select<Subject>("experiment_id", "IS", to_string(args[0].ToInteger())));

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

JSValue MainView::OnLoadBeverages(const JSObject& obj, const JSArgs& args) {

    // Get all beverages
    std::vector<Beverage> beverages(Database::Instance()->Select<Beverage>());

    // Javascript array
    JSArray jArray;
    
    // Loop through and push values to array
    for (std::vector<Beverage>::iterator beverage = beverages.begin(); beverage != beverages.end(); beverage++) { 
        // Temporary array
        JSArray tempArray;

        /// Assign to the temp array
        // [0] Primary key
        // [1] Name
        // [2] Concentration
        tempArray.push(JSValue(JSString(std::to_string(beverage->GetPK()).c_str())));
        tempArray.push(JSValue(JSString(beverage->name_.c_str())));
        tempArray.push(JSValue(JSString(std::to_string(beverage->concentration_).c_str())));

        // Push the array to the main array
        jArray.push(JSValue(tempArray));
    }

    // Send to javascript
    return JSValue(jArray);
}

JSValue MainView::OnClickRecord(const JSObject& obj, const JSArgs& args) {

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