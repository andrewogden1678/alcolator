#pragma once
#include "ViewController.h"
#include "AdminVC.h"
#include "LoginVC.h"
#include "../database/models/Subject.h"
#include "../database/models/Result.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace ultralight;
using namespace std;

///
/// Main Page View Controller
///
class MainView : public ViewController
{ 
    
    public:
        // Constructor/Destructor
        MainView(Ref<Window> window, Identity usr);
        ~MainView();   
        
        /// ViewController Events
        // Required overrides from ViewListener
        virtual void OnClose() override;
        virtual void OnResize(uint32_t width, uint32_t height) override;

        // Members inherited from LoadListener
        virtual void OnDOMReady(View* caller, uint64_t frame_id,
            bool is_main_frame, const String& url) override;

        /// Local JS-Invoked Methods
        JSValue OnLoadSubjects(const JSObject& obj, const JSArgs& args);
        JSValue OnClickRecord(const JSObject& obj, const JSArgs& args);
        JSValue OnLoadExperiments(const JSObject& obj, const JSArgs& args);
        JSValue OnLoadBeverages(const JSObject& obj, const JSArgs& args);
        JSValue OnClickCalculate(const JSObject& obj, const JSArgs& args);
        JSValue OnGetUser(const JSObject& obj, const JSArgs& args);
        JSValue OnClickDownloadReport(const JSObject& obj, const JSArgs& args);
        void OnAddNewBeverage(const JSObject& obj, const JSArgs& args);
        void OnAddNewSubject(const JSObject& obj, const JSArgs& args);
        void OnClickAdminMode(const JSObject& obj, const JSArgs& args);
        void OnLogOut(const JSObject& obj, const JSArgs& args);
        void OnDeleteBeverage(const JSObject& obj, const JSArgs& args);
        
        // Logged-in User
        Identity user_;
};