#pragma once
#include "ViewController.h"
#include "MainVC.h"
#include "LoginVC.h"
#include "../database/models/Identity.h"
#include "../database/models/Experiment.h"

using namespace ultralight;
using namespace std;

///
/// Admin Page View Controller
///
class AdminView : public ViewController
{ 
    
    public:
        // Constructor/Destructor
        AdminView(Ref<Window> window, Identity usr);
        ~AdminView();   
        
        /// ViewController Events
        // Members inherited from ViewListener
        virtual void OnClose() override;
        virtual void OnResize(uint32_t width, uint32_t height) override;

        // Members inherited from LoadListener
        virtual void OnDOMReady(View* caller, uint64_t frame_id,
            bool is_main_frame, const String& url) override;

        /// Local JS-Invoked Methods
        JSValue OnLoadUsers(const JSObject& obj, const JSArgs& args);
        JSValue OnLoadExperiments(const JSObject& obj, const JSArgs& args);
        JSValue OnGetUser(const JSObject& obj, const JSArgs& args);
        void OnSaveUser(const JSObject& obj, const JSArgs& args);
        void OnEditUser(const JSObject& obj, const JSArgs& args);
        void OnAddNewExperiment(const JSObject& obj, const JSArgs& args);
        void OnClickExperimenterMode(const JSObject& obj, const JSArgs& args);
        void OnLogOut(const JSObject& obj, const JSArgs& args);

        // User
        Identity user_;
};