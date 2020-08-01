#include <AppCore/AppCore.h>
#include "view_controllers/ViewController.h"
#include "database/Database.h"

using namespace ultralight;

///
/// Application Instance
///
class Alcolator {

  public:
    // Constructor/Destructor
    Alcolator();
    virtual ~Alcolator();

    // Start the run loop
    virtual void Run();

  protected:
    RefPtr<App> app_; // Application
    RefPtr<Window> window_; // Window
    std::unique_ptr<ViewController> nextView_; // Next view
};
